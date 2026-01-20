#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/err.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define MEMORY_SIZE 1024

dev_t device;
static struct class * device_class;
static struct cdev device_cdev;
uint8_t kernal_buffer;

static ssize_t read_device(struct file * new_file , char * buffer , size_t size , loff_t * offt);
static ssize_t write_device(struct file * new_file , const char * buffer , size_t size , loff_t  *offt);
static int open_device(struct inode *new_node , struct file * new_file);
static int close_device(struct inode *new_node , struct file * new_file);


static struct file_operations fops = 
{
	.owner   = THIS_MODULE,
	.read    = read_device,
        .write	 = write_device,
	.open    = open_device,
	.release = close_device,
};



static int __init init_function(void)
{
	/*allocate the major and minor number*/
	if(alloc_chrdev_region(&dev,0,1,"new_dev")<1)
	{
		/*major  and minor number allocation failed*/
		pr_err("allocation of major and minor numbeer has been failed\n");
		return(-1);
	}
	pr_info("allocated major and minor number is %d %d\n",MAJOR(dev),MINOR(dev));

	/*cdev initialization creating the cdev structure*/
	cdev_init(&device_cdev , &fops);

	/*adding the character device into the system */ 
	if(cdev_add(&device_cdev,device,1) < 0)
	{
		unregister_chrdev_region(device, 1);
		pr_err("char device adding is failed\n");
		return(-1);
	}
	pr_info("device added successfully\n");

	/*creating the struct class*/
	if(IS_ERROR(device_class = create_class("device_class")))
	{
		unregister_chrdev_region(device);
		pr_err("struct class creation failed\n");
		return(-1);
	}
	/*creating the device*/
	if(IS_ERROR(device_create(device_class,NULL ,dev, NULL,"new_device")))
	{
		class_destroy(device_class);
		unregister_chrdev_region(device);
		pr_err("device creation failed\n");
		return(-1);
	}
	/*the device creation is success*/
	if(kernel_buffer =  kmalloc(MEMORY_SIZE ,  GFP_KERNEL)==0)
	{
		class_destroy(device_class);
		unregister_chrdev_region(device);
		pr_err("memory allocation failed\n");
		return(-1);

	}

	return(0);

}

static void __exit exit_function(void)
{
}


module_init(init_function);
module_exit(exit_function);

dMODULE_LICENSE("GPL");
MODULE_AUTHOR("LINCE");
MODULE_DESCRIPTION("A DUMMY DRIVER WHICH ACT LIKE A HARDWARE");
