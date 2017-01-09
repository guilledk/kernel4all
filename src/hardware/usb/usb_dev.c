#include "hardware/usb/usb_dev.h"

struct usb_dev usb_device_list[32];
u32 udev_list_size;

static u32 next_usb_addr;

struct usb_dev * usb_dev_create(u8 index) {

	if(udev_list_size == MAX_USB_DEVS || index >= MAX_USB_DEVS)
		return 0;

	struct usb_dev * udev = &(usb_device_list[index]);
	
	udev->parent = (struct usb_dev *)0;
	udev->index = index;
	udev->hc = (void *)0;
	udev->drv = (void *)0;

	udev->port = 0;
	udev->speed = 0;
	udev->addr = 0;
	udev->max_packet_size = 0;
	udev->endp.toggle = 0;
	
	udev->hc_control = 0;
	udev->hc_intr = 0;
	udev->drv_poll = 0;

	return udev;

}

u8 usb_dev_request(struct usb_dev * dev,
		   u8 type, u8 req,
		   u16 value, u16 index,
		   u16 len, void * data) {

	struct usb_dev_req req_s;
	req_s.type = type;
	req_s.req = req;
	req_s.value = value;
	req_s.index = index;
	req_s.len = len;

	struct usb_transfer t;
	t.endp = 0;
	t.req = &req_s;
	t.data = data;
	t.len = len;
	t.complete = 0;
	t.success = 0;
	
	dev->hc_control(dev, &t);

	return t.success;

}

u8 usb_dev_init(struct usb_dev * dev) {

	struct usb_dev_desc dev_desc;
	if(!usb_dev_request(dev, RT_DEV_TO_HOST | RT_STANDARD | RT_DEV, 
				 REQ_GET_DESC, (USB_DESC_DEVICE << 8) | 0,
				 0, 8, &dev_desc)) {
		return 0;
	}

	dev.max_packet_size = dev_desc.max_packet_size;
	u32 addr = ++next_usb_addr;

	if(!usb_dev_request(dev, RT_HOST_TO_DEV | RT_STANDARD | RT_DEV, 
				 REQ_SET_ADDR, addr, 
				 0, 0, 0)) {
		return 0;
	}
	dev.addr = addr;
	waitt(2);

}
