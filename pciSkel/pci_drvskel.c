#include <linux/module.h>
#include <linux/pci.h>

#define DRV_NAME    "PCI Demo Driver"
#define VENDOR_ID   0x8086
#define DEVICE_ID   0x1C20

/* Probe is Invoked when the device is found and this driver is loaded */
static int pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
  int retVal;
  unsigned long mmio_start, mmio_end, mmio_flags, mmio_len;

  pr_info("%s\r\n",__func__);

  retVal = pci_enable_device(pdev);
  if(retVal != 0)
  {
    pr_err("");
    return -1;
  }

  mmio_start = pci_resource_start(pdev,1);
  mmio_end   = pci_resource_end(pdev,1);
  mmio_flags = pci_resource_flags(pdev,1);
  mmio_len   = pci_resource_len(pdev,1);

  pr_info("MMIO Region Size = %02lX", mmio_len);

  return 0;
}

/* Remove is Invoked when the device is disconnected */
static void pci_remove(struct pci_dev *pdev)
{
  pr_info("%s\r\n",__func__);

  pci_disable_device(pdev);
}

/* Specify DEVICE_ID and VENDOR_ID of device */
/* This pci_device_id is used to create an id_table entry 
   which tells the kernel that this driver is managing the 
   matching device */
static struct pci_device_id pci_id_mtable[] = {
  {DEVICE_ID, VENDOR_ID, PCI_ANY_ID, PCI_ANY_ID},
  {}
};

/* Initialize the pci_driver */
static struct pci_driver pci_drv = {
  .name		= DRV_NAME,
  .id_table	= pci_id_mtable,
  .probe	= pci_probe,
  .remove	= pci_remove,
};

/* Directly Register and Unregister the pci_driver structure with pci core 
   in the Init and Exit Modules */
module_pci_driver(pci_drv);

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("PCI Skeleton Driver");
MODULE_LICENSE("GPL");

#if 0
Note - The device and vendor IDs of a PCI device can be found using the lspci
       command.
       $lspci -v      //Detailed Output
       Now if try to load our driver for an existing device then these are the
       things that we need to keep in mind:
       1. In case of multiple drivers for a device, the driver which registers 
          wih pci core first gains responsibility to manage it. 
       2. There must be some existing driver for the device which may be 
          statically compiled or modularized in the kernel. In any case it gets
          called before our test driver so our probe function does not get 
          invoked unless we disable the default driver.
       3. PCI does not support dynamic hotplugging. The bus scan happens only 
          during boot or if we do it using commands.
#endif

