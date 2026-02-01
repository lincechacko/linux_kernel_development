#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/err.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/ioctl.h>
#include<linux/proc_fs.h>

char dataBuffer[50] = {0};
static int len = 1;

static int device_proc_open(struct inode *newNode , struct file * newFile);
static int device_proc_close(struct inode *newNode , struct file *newFile);
static ssize_t device_proc_read(struct file * newFile , char __user *buffer , size_t lenght , loff_t * offt);
static ssize_t device_proc_write(struct file *newFile , const char __user *buffer , size_t length , loff_t *offt);

static int device_open(struct inode *newNode , struct file * newFile);
static int device_close(struct inode *newNode , struct file *newFile);
static ssize_t device_read(struct file * newFile , char __user *buffer , size_t length , loff_t *offt);
static ssize_t device_write(struct file *newFile , const char __user *buffer , size_t length , loff_t *offt);


dev_t device; /*For major and minor number*/
static struct class *device_class; /*for creating the struct class*/
static struct cdev device_cdev;
static struct proc_dir_entry *parent;

static struct file_operations fops= 
{
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_close,
	.read = device_read,
	.write = device_write
};


static struct proc_ops proc_fops = 
{
	.proc_open = device_proc_open,
	.proc_release = device_proc_close,
	.proc_read = device_proc_read,
	.proc_write = device_proc_write
};

static int device_open(struct inode *newNode , struct file * newFile)
{
	pr_info("device open called\n");
	return 0;
}

static int device_close(struct inode *newNode , struct file *newFile)
{
	pr_info("device close called\n");
	return 0;
}

static ssize_t device_read(struct file * newFile , char __user *buffer , size_t length , loff_t * offt)
{
	pr_info("device read called\n");
	return length;
}

static ssize_t device_write(struct file *newFile , const char __user *buffer , size_t length , loff_t *offt)
{
	pr_info("device write called\n");
	return length;
}

static int device_proc_open(struct inode *newNode , struct file * newFile)
{
	pr_info("proccess file open called\n");
	return 0;
}

static int device_proc_close(struct inode *newNode , struct file *newFile)
{
	pr_info("process file close called\n");
	return 0;
}

static ssize_t device_proc_read(struct file * newFile , char __user *buffer , size_t length , loff_t * offt)
{
	if(len)
    	{
        	len=0;
        }
    	else
    	{
         	len=1;
        	return 0;
   	}
	if(copy_to_user(buffer , &dataBuffer , 50))
	{
		pr_err("proc file read failed\n");
	}
	return length;
}

static ssize_t device_proc_write(struct file *newFile , const char __user *buffer , size_t length , loff_t *offt)
{
	if(copy_from_user(&dataBuffer , buffer ,  length))
	{
		pr_err("process file write failed\n");
	}
	return length;
}

static int __init init_function(void)
{
	if(alloc_chrdev_region(&device ,0, 1 , "chr_device")<0)
	{
		pr_err("error in assigning major and minor number\n");
		return -1;
	}
	pr_info("major and minor number creation success\n");

	/*initializing the character device with the file operation structure*/
	cdev_init(&device_cdev ,  &fops);
	pr_info("cdev init success\n");

	if(cdev_add(&device_cdev , device , 1)<0)
	{
		pr_err("adding the device to the system failed\n");
		unregister_chrdev_region(device , 1);
		return -1;
	}
	pr_info("adding the character driver to the system is success\n");

	if(IS_ERR(device_class = class_create("New device class")))
	{
		pr_err("struct class creation failed\n");
		unregister_chrdev_region(device , 1);
		return -1;
	}
	pr_info("struct class creation success\n");

	if(IS_ERR(device_create(device_class , NULL , device , NULL ,"new_device")))
	{
		pr_err("creating the device has been failed\n");
		class_destroy(device_class);
		unregister_chrdev_region(device , 1);
		return -1;
	}
	
	parent = proc_mkdir("new_dir",NULL);
	if(parent == NULL)
	{
		pr_err("process directory creation has been failed\n");
		class_destroy(device_class);
		unregister_chrdev_region(device , 1);
		return -1;
	}
	 proc_create("lince",0666,parent,&proc_fops);

	 pr_info("module has been added succssfully\n");

	return 0;
}

static void __exit exit_function(void)
{
	proc_remove(parent);
	device_destroy(device_class , device);
	class_destroy(device_class);
	cdev_del(&device_cdev);
	unregister_chrdev_region(device , 1);
}


module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LINCE");
MODULE_DESCRIPTION("SAMPLE MODULE FOR THE PROCFS");
