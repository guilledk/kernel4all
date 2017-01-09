#ifndef _USB_DESC_H_
#define _USB_DESC_H_

#include "core/types.h"

// USB Base Descriptor Types

#define USB_DESC_DEVICE                 0x01
#define USB_DESC_CONF                   0x02
#define USB_DESC_STRING                 0x03
#define USB_DESC_INTF                   0x04
#define USB_DESC_ENDP                   0x05

// USB HID Descriptor Types

#define USB_DESC_HID                    0x21
#define USB_DESC_REPORT                 0x22
#define USB_DESC_PHYSICAL               0x23

// USB HUB Descriptor Types

#define USB_DESC_HUB                    0x29

// USB Device Descriptor

struct usb_dev_desc {

	u8 len;
	u8 type;
	u16 usb_ver;
	u8 dev_class;
	u8 dev_subclass;
	u8 dev_protocol;
	u8 max_packet_size;
	u16 vendorID;
	u16 productID;
	u16 dev_ver;
	u8 vendor_str;
	u8 product_str;
	u8 serial_str;
	u8 conf_count;

} __attribute__((packed));

// USB Configuration Descriptor

struct usb_conf_desc {

	u8 len;
	u8 type;
	u16 total_len;
	u8 intf_count;
	u8 conf_val;
	u8 conf_str;
	u8 attributes;
	u8 max_power;

} __attribute__((packed));

// USB Interface Descriptor

struct usb_intf_desc {

	u8 len;
	u8 type;
	u8 intf_index;
	u8 alt_setting;
	u8 endp_count;
	u8 intf_class;
	u8 intf_subclass;
	u8 intf_protocol;
	u8 intf_str;

} __attribute__((packed));

// USB Endpoint Descriptor

struct usb_endp_desc {

	u8 len;
	u8 type;
	u8 addr;
	u8 attributes;
	u16 max_packet_size;
	u8 interval;

} __attribute__((packed));

// USB HID Descriptor

struct usb_hid_desc {

	u8 len;
	u8 type;
	u16 hid_ver;
	u8 country_code;
	u8 desc_count;
	u8 desc_type;
	u16 desc_len;

} __attribute__((packed));

// USB Hub Descriptor

struct usb_hub_desc {

	u8 len;
	u8 type;
	u8 port_count;
	u16 chars;
	u8 port_pow_time;
	u8 current;

} __attribute__((packed));

// Hub Characteristics
#define HUB_POWER_MASK                  0x03        // Logical Power Switching Mode
#define HUB_POWER_GLOBAL                0x00
#define HUB_POWER_INDIVIDUAL            0x01
#define HUB_COMPOUND                    0x04        // Part of a Compound Device
#define HUB_CURRENT_MASK                0x18        // Over-current Protection Mode
#define HUB_TT_TTI_MASK                 0x60        // TT Think Time
#define HUB_PORT_INDICATORS             0x80        // Port Indicators

void usb_print_dev_desc(struct usb_dev_desc * desc);
void usb_print_conf_desc(struct usb_conf_desc * desc);
void usb_print_intf_desc(struct usb_intf_desc * desc);
void usb_print_endp_desc(struct usb_endp_desc * desc);

void usb_print_hid_desc(struct usb_hid_desc * desc);
void usb_print_hub_desc(struct usb_hub_desc * desc);

#endif
