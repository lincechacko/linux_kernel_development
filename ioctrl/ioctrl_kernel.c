#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/err.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>


/*defining the IOCTL Control command*/
#define WR_VALUE _IOW('a','a',int32_t *)
#define RD_VALUE _IOR('a','b',int32_t *)



dev_t device;
static struct class * device_class;
static struct cdev device_cdev;
static struct file_operartions = 
{
	.owner = THIS_MODULE,
	.read = ,
	.write = ,
	.open = ,
	.release ,
	.unlocked_ioctl,
};


static int __inti init_function(void)
{
	if(alloc_chrdev_region(&device,0,1,"chr_dev")<0)
	{
		pr_err("allocation of major and minor number has been failed\n");
		return(-1);
	}
	pr_info("allocation of major and minor number is success\n");

	/*after the successfull allocation of the major and the minor number lets init the cdev structure*/

	cdev_init(&device_cdev , &fops);
	return (0);
}

static void __exit exit_function(void)
{
}


module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LINCE");
MODULE_DESCRIPTION("SIMPLE DRIVER TO MAKE THE USE OF IOCTL");

