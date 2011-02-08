#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define FIRST_MINOR_NUMBER 0
#define COUNT_OF_CONTIGOUS_DEVICES 1

/* Device that we will use */
dev_t helloworld_device;


/* Initialization Function for the kernel module */
static int helloworld_driver_init(void)
{
        printk(KERN_INFO "Hello World");


	/* Allocate a dynamic device number for your driver. If you want to hardcode a fixed major number for your 
	 * driver, you should use different APIs 'register_chrdev_region', 'MKDEV'. But the following is better. */
	if (!alloc_chrdev_region(&helloworld_device, FIRST_MINOR_NUMBER, COUNT_OF_CONTIGOUS_DEVICES, "HelloWorldDriver")) {
		printk(KERN_INFO "Device Number successfully allocated.");

		/* If you do a cat /proc/devices you should be able to find our Driver registered. */
	
	} else
		printk(KERN_ALERT "HelloWorldDriver could not get a Device number");

        return 0;
}


/* Unloading function for the kernel module */
static void helloworld_driver_exit(void)
{
        printk(KERN_INFO "Goodbye World");

	/* Free the device number when the driver is no longer available */
	unregister_chrdev_region(helloworld_device, COUNT_OF_CONTIGOUS_DEVICES);

}

module_init(helloworld_driver_init);
module_exit(helloworld_driver_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sankar P");
MODULE_DESCRIPTION("A Simple Character Device Driver");
