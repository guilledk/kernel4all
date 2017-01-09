#ifndef _USB_DEV_H_
#define _USB_DEV_H_

#include "core/types.h"
#include "core/time.h"
#include "hardware/usb/usb_desc.h"
#include "hardware/usb/usb_req.h"

// USB Limits

#define USB_STRING_SIZE			127

// USB Speeds

#define USB_FULL_SPEED                  0x00
#define USB_LOW_SPEED                   0x01
#define USB_HIGH_SPEED                  0x02

// USB Endpoint

struct usb_end_point {

	struct usb_endp_desc desc;
	u8 toggle;

};

// USB Transfer

struct usb_transfer {

	struct usb_end_point * endp;
	struct usb_dev_req * req;
	void * data;
	u32 len;
	u8 complete;
	u8 success;

};

// USB Device

struct usb_dev {

	struct usb_dev * parent;
	u8 index;
	void * hc;
	void * drv;

	u32 port;
	u32 speed;
	u32 addr;
	u32 max_packet_size;

	struct usb_end_point endp;
	struct usb_intf_desc intf_desc;

	void (*hc_control)(struct usb_dev *dev, struct usb_transfer * t);
	void (*hc_intr)(struct usb_dev *dev, struct usb_transfer * t);
	void (*drv_poll)(struct usb_dev *dev);

};

#define MAX_USB_DEVS 32

extern struct usb_dev usb_device_list[MAX_USB_DEVS];
extern u32 udev_list_size;

// Functions

struct usb_dev * usb_dev_create(u8 index);
u8 usb_dev_init(struct usb_dev * dev);

u8 usb_dev_request(struct usb_dev * dev,
		   u8 type, u8 req,
		   u16 value, u16 index,
		   u16 len, void * data);

u8 usb_dev_get_langs(struct usb_dev * dev, u16 * langs);
u8 usb_dev_get_str(struct usb_dev * dev, char * str, u16 lang_id, u16 str_index);
u8 usb_dev_clear_halt(struct usb_dev * dev);

#endif
