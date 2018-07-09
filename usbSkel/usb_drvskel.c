#include <linux/module.h>
#include <linux/usb.h>

/* Sandisk Cruzer Data Flash Identification Codes */
#define VENDOR_ID 0x0781
#define DEVICE_ID 0x5567

/* Probe is Invoked when the device is found and this driver is loaded */
static int usb_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
  /* Get the usb_device structure reference from the interface */
  /* This structure is the kernel's representation of a usb device */
  struct usb_device *dev = interface_to_usbdev(intf);

  pr_info("Interface Driver : %s Invoked\r\n", __func__);

  /* Access the fields of the usb device */
  pr_info("Device Number   = %d\r\n",dev->devnum);
  pr_info("Device Speed    = %d\r\n",dev->speed);  
  pr_info("Vendor ID       = 0x%4hX\r\n",dev->descriptor.idVendor); 
  pr_info("Product ID      = 0x%4hX\r\n",dev->descriptor.idProduct);
  pr_info("Device BCD      = 0x%hX\r\n",dev->descriptor.bcdDevice);  
  pr_info("Device Class    = 0x%hX\r\n",dev->descriptor.bDeviceClass);
  pr_info("Device SubClass = 0x%hX\r\n",dev->descriptor.bDeviceSubClass);
  pr_info("Device Protocol = 0x%hX\r\n",dev->descriptor.bDeviceProtocol);
  pr_info("PacketSize      = %hu\r\n",dev->descriptor.bMaxPacketSize0);
  pr_info("Manufacturer    = %s\r\n",dev->manufacturer);
  pr_info("Product         = %s\r\n",dev->product);
  pr_info("Serial          = %s\r\n",dev->serial);
  /* There are also separate iManufacturer, iProduct and iSerialNumber 
     Fields inside the descriptor structure field of the usb_device structure */
  return 0;
}

/* Remove is Invoked when the device is disconnected */
static void usb_disconnect(struct usb_interface *intf)
{ 
  pr_info("Interface Driver : %s Invoked\r\n", __func__);
}

/* Specify DEVICE_ID and VENDOR_ID of device */
/* This usb_device_id is used to create an id_table entry 
   which tells the kernel that this driver is managing the 
   matching device */
static struct usb_device_id usb_drv_mtable[] =
{
  {USB_DEVICE(VENDOR_ID, DEVICE_ID)},
  {}
};

/* Initialize the usb_driver */
static struct usb_driver usb_drv =
{
  .name       = "usb_probe_drv",
  .probe      = usb_probe,
  .disconnect = usb_disconnect,
  .id_table   = usb_drv_mtable,
};

/* Directly Register and Unregister the usb_driver structure with usb core 
   in the Init and Exit Modules */
module_usb_driver(usb_drv);

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("USB Skeleton Driver");
MODULE_LICENSE("GPL");

#if 0
Note - The device and vendor IDs of an USB device can be found using the lsusb
       command.
       $lsusb -v      //Detailed Output
       Now if try to load our driver for an existing device then these are the
       things that we need to keep in mind:
       1. In case of multiple drivers for a device, the driver which registers 
          wih usb core first gains responsibility to manage it. 
       2. There must be some existing driver for the device which may be 
          statically compiled or modularized in the kernel. In any case it gets
          called before our test driver so our probe function does not get 
          invoked unless we disable the default driver.
       
       Commands to Invoke this driver is in attached file commands.txt
#endif

