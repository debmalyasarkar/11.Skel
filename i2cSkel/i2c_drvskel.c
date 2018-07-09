#include <linux/module.h>
#include <linux/i2c.h>

#define DRV_NAME   "I2C Demo Driver"
#define DEVICE     "24C08"
#define ADDRESS    0x50

/* Probe is Invoked when the device is found and this driver is loaded */
static int i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
  pr_info("%s\r\n",__func__);
  return 0;
}

/* Remove is Invoked when the device is disconnected */
static int i2c_remove(struct i2c_client *client)
{
  pr_info("%s\r\n",__func__);
  return 0;
}

/* Specify DEVICE_ID and VENDOR_ID of device */
/* This i2c_device_id is used to create an id_table entry 
   which tells the kernel that this driver is managing the 
   matching device */
static struct i2c_device_id i2c_id_mtable[] = {
  {DEVICE, ADDRESS},
  {}
};

/* Initialize the i2c_driver */
static struct i2c_driver i2c_drv = {
  .driver   = {
    .name  = DRV_NAME,
    .owner = THIS_MODULE,
  },
  .id_table	= i2c_id_mtable,
  .probe	= i2c_probe,
  .remove	= i2c_remove,
};

/* Directly Register and Unregister the i2c_driver structure with i2c core 
   in the Init and Exit Modules */
module_i2c_driver(i2c_drv);

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("I2C Skeleton Driver");
MODULE_LICENSE("GPL");

#if 0
Note - If try to load our driver for an existing device then these are the
       things that we need to keep in mind:
       1. In case of multiple drivers for a device, the driver which registers 
          wih i2c core first gains responsibility to manage it. 
       2. There must be some existing driver for the device which may be 
          statically compiled or modularized in the kernel. In any case it gets
          called before our test driver so our probe function does not get 
          invoked unless we disable the default driver.
       3. I2C does not support hotplugging.
       4. This driver is for an EEPROM device.
#endif

