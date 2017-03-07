/*
 *  HID driver for Sony / PS2 / PS3 / PS4 BD devices.
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> for Concept2, Inc
 *  Copyright (c) 2008 Jiri Slaby
 *  Copyright (c) 2012 David Dillow <dave@thedillows.org>
 *  Copyright (c) 2006-2013 Jiri Kosina
 *  Copyright (c) 2013 Colin Leitner <colin.leitner@gmail.com>
 *  Copyright (c) 2014-2016 Frank Praznik <frank.praznik@gmail.com>
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

/*
 * NOTE: in order for the Sony PS3 BD Remote Control to be found by
 * a Bluetooth host, the key combination Start+Enter has to be kept pressed
 * for about 7 seconds with the Bluetooth Host Controller in discovering mode.
 *
 * There will be no PIN request from the device.
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/leds.h>
#include <linux/power_supply.h>
#include <linux/spinlock.h>
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/list.h>
#include <linux/idr.h>
<<<<<<< HEAD
=======
>>>>>>> e56062305069... HID: sony: add output events for the multi-touch pad on the Dualshock 4
=======
#include <linux/list.h>
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
#include <linux/input/mt.h>
=======
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
#include <linux/list.h>
#include <linux/idr.h>
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
#include <linux/input/mt.h>
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

#include "hid-ids.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
#define VAIO_RDESC_CONSTANT       BIT(0)
#define SIXAXIS_CONTROLLER_USB    BIT(1)
#define SIXAXIS_CONTROLLER_BT     BIT(2)
#define BUZZ_CONTROLLER           BIT(3)
#define PS3REMOTE                 BIT(4)
#define DUALSHOCK4_CONTROLLER_USB BIT(5)
#define DUALSHOCK4_CONTROLLER_BT  BIT(6)
<<<<<<< HEAD
<<<<<<< HEAD
=======
#define MOTION_CONTROLLER_USB     BIT(7)
#define MOTION_CONTROLLER_BT      BIT(8)
#define NAVIGATION_CONTROLLER_USB BIT(9)
#define NAVIGATION_CONTROLLER_BT  BIT(10)
#define SINO_LITE_CONTROLLER      BIT(11)
#define FUTUREMAX_DANCE_MAT       BIT(12)
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
#define DUALSHOCK4_DONGLE         BIT(7)
#define MOTION_CONTROLLER_USB     BIT(8)
#define MOTION_CONTROLLER_BT      BIT(9)
#define NAVIGATION_CONTROLLER_USB BIT(10)
#define NAVIGATION_CONTROLLER_BT  BIT(11)
#define SINO_LITE_CONTROLLER      BIT(12)
#define FUTUREMAX_DANCE_MAT       BIT(13)

>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device
#define SIXAXIS_CONTROLLER (SIXAXIS_CONTROLLER_USB | SIXAXIS_CONTROLLER_BT)
#define DUALSHOCK4_CONTROLLER (DUALSHOCK4_CONTROLLER_USB |\
				DUALSHOCK4_CONTROLLER_BT | \
				DUALSHOCK4_DONGLE)
#define SONY_LED_SUPPORT (SIXAXIS_CONTROLLER | BUZZ_CONTROLLER |\
<<<<<<< HEAD
				DUALSHOCK4_CONTROLLER)
#define SONY_BATTERY_SUPPORT (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER)
#define SONY_FF_SUPPORT (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER)
<<<<<<< HEAD
<<<<<<< HEAD
=======
#define SONY_LED_SUPPORT (SIXAXIS_CONTROLLER_USB | BUZZ_CONTROLLER | DUALSHOCK4_CONTROLLER_USB)
#define SONY_BATTERY_SUPPORT (SIXAXIS_CONTROLLER_USB | SIXAXIS_CONTROLLER_BT | DUALSHOCK4_CONTROLLER_USB)
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
#define DUALSHOCK4_CONTROLLER (DUALSHOCK4_CONTROLLER_USB |\
				DUALSHOCK4_CONTROLLER_BT)
#define SONY_LED_SUPPORT (SIXAXIS_CONTROLLER_USB | BUZZ_CONTROLLER |\
				DUALSHOCK4_CONTROLLER)
#define SONY_BATTERY_SUPPORT (SIXAXIS_CONTROLLER_USB | SIXAXIS_CONTROLLER_BT |\
				DUALSHOCK4_CONTROLLER)
>>>>>>> 68330d83c0b3... HID: sony: Add conditionals to enable all features in Bluetooth mode
=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
				DUALSHOCK4_CONTROLLER | MOTION_CONTROLLER |\
				NAVIGATION_CONTROLLER)
#define SONY_BATTERY_SUPPORT (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER |\
				MOTION_CONTROLLER_BT | NAVIGATION_CONTROLLER)
#define SONY_FF_SUPPORT (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER |\
				MOTION_CONTROLLER)
#define SONY_BT_DEVICE (SIXAXIS_CONTROLLER_BT | DUALSHOCK4_CONTROLLER_BT |\
			MOTION_CONTROLLER_BT | NAVIGATION_CONTROLLER_BT)
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

#define MAX_LEDS 4

static __u8 sixaxis_rdesc[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x04,         /*  Usage (Joystik),                    */
	0xA1, 0x01,         /*  Collection (Application),           */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0x01,         /*          Report ID (1),              */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x01,         /*          Report Count (1),           */
	0x15, 0x00,         /*          Logical Minimum (0),        */
	0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
	0x81, 0x03,         /*          Input (Constant, Variable), */
	0x75, 0x01,         /*          Report Size (1),            */
	0x95, 0x13,         /*          Report Count (19),          */
	0x15, 0x00,         /*          Logical Minimum (0),        */
	0x25, 0x01,         /*          Logical Maximum (1),        */
	0x35, 0x00,         /*          Physical Minimum (0),       */
	0x45, 0x01,         /*          Physical Maximum (1),       */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x13,         /*          Usage Maximum (13h),        */
	0x81, 0x02,         /*          Input (Variable),           */
	0x75, 0x01,         /*          Report Size (1),            */
	0x95, 0x0D,         /*          Report Count (13),          */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x81, 0x03,         /*          Input (Constant, Variable), */
	0x15, 0x00,         /*          Logical Minimum (0),        */
	0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x01,         /*          Usage (Pointer),            */
	0xA1, 0x00,         /*          Collection (Physical),      */
	0x75, 0x08,         /*              Report Size (8),        */
	0x95, 0x04,         /*              Report Count (4),       */
	0x35, 0x00,         /*              Physical Minimum (0),   */
	0x46, 0xFF, 0x00,   /*              Physical Maximum (255), */
	0x09, 0x30,         /*              Usage (X),              */
	0x09, 0x31,         /*              Usage (Y),              */
	0x09, 0x32,         /*              Usage (Z),              */
	0x09, 0x35,         /*              Usage (Rz),             */
	0x81, 0x02,         /*              Input (Variable),       */
	0xC0,               /*          End Collection,             */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x95, 0x13,         /*          Report Count (19),          */
	0x09, 0x01,         /*          Usage (Pointer),            */
	0x81, 0x02,         /*          Input (Variable),           */
	0x95, 0x0C,         /*          Report Count (12),          */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x10,         /*          Report Size (16),           */
	0x95, 0x04,         /*          Report Count (4),           */
	0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
	0x46, 0xFF, 0x03,   /*          Physical Maximum (1023),    */
	0x09, 0x01,         /*          Usage (Pointer),            */
	0x81, 0x02,         /*          Input (Variable),           */
	0xC0,               /*      End Collection,                 */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0x02,         /*          Report ID (2),              */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Pointer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0xEE,         /*          Report ID (238),            */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Pointer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0xEF,         /*          Report ID (239),            */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Pointer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xC0                /*  End Collection                      */
};
=======
#define VAIO_RDESC_CONSTANT     BIT(0)
#define SIXAXIS_CONTROLLER_USB  BIT(1)
#define SIXAXIS_CONTROLLER_BT   BIT(2)
#define BUZZ_CONTROLLER         BIT(3)
#define PS3REMOTE		BIT(4)
<<<<<<< HEAD
#define DUALSHOCK4_CONTROLLER   BIT(5)
<<<<<<< HEAD

#define SONY_LED_SUPPORT (SIXAXIS_CONTROLLER_USB | BUZZ_CONTROLLER | DUALSHOCK4_CONTROLLER)
=======
>>>>>>> 0bd88dd3dd5e... HID: sony: Add force-feedback support for the Dualshock 4
=======
#define DUALSHOCK4_CONTROLLER_USB BIT(5)
#define DUALSHOCK4_CONTROLLER_BT  BIT(6)

#define SONY_LED_SUPPORT (SIXAXIS_CONTROLLER_USB | BUZZ_CONTROLLER | DUALSHOCK4_CONTROLLER_USB)
>>>>>>> 8ab1676b614e... HID: sony: Use separate identifiers for USB and Bluetooth connected Dualshock 4 controllers.

<<<<<<< HEAD
#define MAX_LEDS 4
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
#define SONY_LED_SUPPORT (SIXAXIS_CONTROLLER_USB | BUZZ_CONTROLLER | DUALSHOCK4_CONTROLLER_USB)

#define MAX_LEDS 4
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
/*
 * The default descriptor doesn't provide mapping for the accelerometers
 * or orientation sensors.  This fixed descriptor maps the accelerometers
 * to usage values 0x40, 0x41 and 0x42 and maps the orientation sensors
 * to usage values 0x43, 0x44 and 0x45.
 */
static u8 dualshock4_usb_rdesc[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x05,         /*  Usage (Gamepad),                    */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x01,         /*      Report ID (1),                  */
	0x09, 0x30,         /*      Usage (X),                      */
	0x09, 0x31,         /*      Usage (Y),                      */
	0x09, 0x32,         /*      Usage (Z),                      */
	0x09, 0x35,         /*      Usage (Rz),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x04,         /*      Report Count (4),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x39,         /*      Usage (Hat Switch),             */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x07,         /*      Logical Maximum (7),            */
	0x35, 0x00,         /*      Physical Minimum (0),           */
	0x46, 0x3B, 0x01,   /*      Physical Maximum (315),         */
	0x65, 0x14,         /*      Unit (Degrees),                 */
	0x75, 0x04,         /*      Report Size (4),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x81, 0x42,         /*      Input (Variable, Null State),   */
	0x65, 0x00,         /*      Unit,                           */
	0x05, 0x09,         /*      Usage Page (Button),            */
	0x19, 0x01,         /*      Usage Minimum (01h),            */
	0x29, 0x0D,         /*      Usage Maximum (0Dh),            */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x01,         /*      Logical Maximum (1),            */
	0x75, 0x01,         /*      Report Size (1),                */
	0x95, 0x0E,         /*      Report Count (14),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x75, 0x06,         /*      Report Size (6),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x3F,         /*      Logical Maximum (63),           */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x09, 0x33,         /*      Usage (Rx),                     */
	0x09, 0x34,         /*      Usage (Ry),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x02,         /*      Report Count (2),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x19, 0x40,         /*      Usage Minimum (40h),            */
	0x29, 0x42,         /*      Usage Maximum (42h),            */
	0x16, 0x00, 0x80,   /*      Logical Minimum (-32768),       */
	0x26, 0x00, 0x7F,   /*      Logical Maximum (32767),        */
	0x75, 0x10,         /*      Report Size (16),               */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x19, 0x43,         /*      Usage Minimum (43h),            */
	0x29, 0x45,         /*      Usage Maximum (45h),            */
	0x16, 0x00, 0xE0,   /*      Logical Minimum (-8192),        */
	0x26, 0xFF, 0x1F,   /*      Logical Maximum (8191),         */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x27,         /*      Report Count (39),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x85, 0x05,         /*      Report ID (5),                  */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x1F,         /*      Report Count (31),              */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x04,         /*      Report ID (4),                  */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x02,         /*      Report ID (2),                  */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x08,         /*      Report ID (8),                  */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x10,         /*      Report ID (16),                 */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x04,         /*      Report Count (4),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x11,         /*      Report ID (17),                 */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x12,         /*      Report ID (18),                 */
	0x06, 0x02, 0xFF,   /*      Usage Page (FF02h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x13,         /*      Report ID (19),                 */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x16,         /*      Report Count (22),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x14,         /*      Report ID (20),                 */
	0x06, 0x05, 0xFF,   /*      Usage Page (FF05h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x10,         /*      Report Count (16),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x15,         /*      Report ID (21),                 */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x2C,         /*      Report Count (44),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x06, 0x80, 0xFF,   /*      Usage Page (FF80h),             */
	0x85, 0x80,         /*      Report ID (128),                */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x81,         /*      Report ID (129),                */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x82,         /*      Report ID (130),                */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x05,         /*      Report Count (5),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x83,         /*      Report ID (131),                */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x84,         /*      Report ID (132),                */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x04,         /*      Report Count (4),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x85,         /*      Report ID (133),                */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x86,         /*      Report ID (134),                */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x87,         /*      Report ID (135),                */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x23,         /*      Report Count (35),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x88,         /*      Report ID (136),                */
	0x09, 0x28,         /*      Usage (28h),                    */
	0x95, 0x22,         /*      Report Count (34),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x89,         /*      Report ID (137),                */
	0x09, 0x29,         /*      Usage (29h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x90,         /*      Report ID (144),                */
	0x09, 0x30,         /*      Usage (30h),                    */
	0x95, 0x05,         /*      Report Count (5),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x91,         /*      Report ID (145),                */
	0x09, 0x31,         /*      Usage (31h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x92,         /*      Report ID (146),                */
	0x09, 0x32,         /*      Usage (32h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x93,         /*      Report ID (147),                */
	0x09, 0x33,         /*      Usage (33h),                    */
	0x95, 0x0C,         /*      Report Count (12),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA0,         /*      Report ID (160),                */
	0x09, 0x40,         /*      Usage (40h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA1,         /*      Report ID (161),                */
	0x09, 0x41,         /*      Usage (41h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA2,         /*      Report ID (162),                */
	0x09, 0x42,         /*      Usage (42h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA3,         /*      Report ID (163),                */
	0x09, 0x43,         /*      Usage (43h),                    */
	0x95, 0x30,         /*      Report Count (48),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA4,         /*      Report ID (164),                */
	0x09, 0x44,         /*      Usage (44h),                    */
	0x95, 0x0D,         /*      Report Count (13),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA5,         /*      Report ID (165),                */
	0x09, 0x45,         /*      Usage (45h),                    */
	0x95, 0x15,         /*      Report Count (21),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA6,         /*      Report ID (166),                */
	0x09, 0x46,         /*      Usage (46h),                    */
	0x95, 0x15,         /*      Report Count (21),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF0,         /*      Report ID (240),                */
	0x09, 0x47,         /*      Usage (47h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF1,         /*      Report ID (241),                */
	0x09, 0x48,         /*      Usage (48h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF2,         /*      Report ID (242),                */
	0x09, 0x49,         /*      Usage (49h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA7,         /*      Report ID (167),                */
	0x09, 0x4A,         /*      Usage (4Ah),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA8,         /*      Report ID (168),                */
	0x09, 0x4B,         /*      Usage (4Bh),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA9,         /*      Report ID (169),                */
	0x09, 0x4C,         /*      Usage (4Ch),                    */
	0x95, 0x08,         /*      Report Count (8),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAA,         /*      Report ID (170),                */
	0x09, 0x4E,         /*      Usage (4Eh),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAB,         /*      Report ID (171),                */
	0x09, 0x4F,         /*      Usage (4Fh),                    */
	0x95, 0x39,         /*      Report Count (57),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAC,         /*      Report ID (172),                */
	0x09, 0x50,         /*      Usage (50h),                    */
	0x95, 0x39,         /*      Report Count (57),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAD,         /*      Report ID (173),                */
	0x09, 0x51,         /*      Usage (51h),                    */
	0x95, 0x0B,         /*      Report Count (11),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAE,         /*      Report ID (174),                */
	0x09, 0x52,         /*      Usage (52h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAF,         /*      Report ID (175),                */
	0x09, 0x53,         /*      Usage (53h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xB0,         /*      Report ID (176),                */
	0x09, 0x54,         /*      Usage (54h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0xC0                /*  End Collection                      */
};

<<<<<<< HEAD
<<<<<<< HEAD
/*
 * The default behavior of the Dualshock 4 is to send reports using report
 * type 1 when running over Bluetooth. However, when feature report 2 is
 * requested during the controller initialization it starts sending input
 * reports in report 17.  Since report 17 is undefined in the default HID
<<<<<<< HEAD
 * descriptor the button and axis definitions must be moved to report 17 or
 * the HID layer won't process the received input.
=======
/* The default behavior of the Dualshock 4 is to send reports using report
=======
/*
 * The default behavior of the Dualshock 4 is to send reports using report
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
 * type 1 when running over Bluetooth. However, as soon as it receives a
 * report of type 17 to set the LEDs or rumble it starts returning it's state
 * in report 17 instead of 1.  Since report 17 is undefined in the default HID
 * descriptor the button and axis definitions must be moved to report 17 or
 * the HID layer won't process the received input once a report is sent.
<<<<<<< HEAD
>>>>>>> d829674d29d7... HID: sony: Add modified Dualshock 4 Bluetooth HID descriptor
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
 * descriptor the button and axis definitions must be moved to report 17 or
 * the HID layer won't process the received input.
>>>>>>> 39520eea198a... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
 */
static u8 dualshock4_bt_rdesc[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x05,         /*  Usage (Gamepad),                    */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x01,         /*      Report ID (1),                  */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x0A,         /*      Report Count (9),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x04, 0xFF,   /*      Usage Page (FF04h),             */
	0x85, 0x02,         /*      Report ID (2),                  */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA3,         /*      Report ID (163),                */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x30,         /*      Report Count (48),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x05,         /*      Report ID (5),                  */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x28,         /*      Report Count (40),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x06,         /*      Report ID (6),                  */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x34,         /*      Report Count (52),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x07,         /*      Report ID (7),                  */
	0x09, 0x28,         /*      Usage (28h),                    */
	0x95, 0x30,         /*      Report Count (48),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x08,         /*      Report ID (8),                  */
	0x09, 0x29,         /*      Usage (29h),                    */
	0x95, 0x2F,         /*      Report Count (47),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x06, 0x03, 0xFF,   /*      Usage Page (FF03h),             */
	0x85, 0x03,         /*      Report ID (3),                  */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x26,         /*      Report Count (38),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x04,         /*      Report ID (4),                  */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x2E,         /*      Report Count (46),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF0,         /*      Report ID (240),                */
	0x09, 0x47,         /*      Usage (47h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF1,         /*      Report ID (241),                */
	0x09, 0x48,         /*      Usage (48h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF2,         /*      Report ID (242),                */
	0x09, 0x49,         /*      Usage (49h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x11,         /*      Report ID (17),                 */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x09, 0x30,         /*      Usage (X),                      */
	0x09, 0x31,         /*      Usage (Y),                      */
	0x09, 0x32,         /*      Usage (Z),                      */
	0x09, 0x35,         /*      Usage (Rz),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x04,         /*      Report Count (4),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x39,         /*      Usage (Hat Switch),             */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x07,         /*      Logical Maximum (7),            */
	0x75, 0x04,         /*      Report Size (4),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x81, 0x42,         /*      Input (Variable, Null State),   */
	0x05, 0x09,         /*      Usage Page (Button),            */
	0x19, 0x01,         /*      Usage Minimum (01h),            */
	0x29, 0x0D,         /*      Usage Maximum (0Dh),            */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x01,         /*      Logical Maximum (1),            */
	0x75, 0x01,         /*      Report Size (1),                */
	0x95, 0x0E,         /*      Report Count (14),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x75, 0x06,         /*      Report Size (6),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x81, 0x01,         /*      Input (Constant),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x09, 0x33,         /*      Usage (Rx),                     */
	0x09, 0x34,         /*      Usage (Ry),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x02,         /*      Report Count (2),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x19, 0x40,         /*      Usage Minimum (40h),            */
	0x29, 0x42,         /*      Usage Maximum (42h),            */
	0x16, 0x00, 0x80,   /*      Logical Minimum (-32768),       */
	0x26, 0x00, 0x7F,   /*      Logical Maximum (32767),        */
	0x75, 0x10,         /*      Report Size (16),               */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x19, 0x43,         /*      Usage Minimum (43h),            */
	0x29, 0x45,         /*      Usage Maximum (45h),            */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	0x16, 0x00, 0xE0,   /*      Logical Minimum (-8192),        */
	0x26, 0xFF, 0x1F,   /*      Logical Maximum (8191),         */
=======
	0x16, 0xFF, 0xBF,   /*      Logical Minimum (-16385),       */
	0x26, 0x00, 0x40,   /*      Logical Maximum (16384),        */
>>>>>>> d829674d29d7... HID: sony: Add modified Dualshock 4 Bluetooth HID descriptor
=======
	0x16, 0xFF, 0xBF,   /*      Logical Minimum (-16385),       */
	0x26, 0x00, 0x40,   /*      Logical Maximum (16384),        */
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	0x16, 0x00, 0xE0,   /*      Logical Minimum (-8192),        */
	0x26, 0xFF, 0x1F,   /*      Logical Maximum (8191),         */
>>>>>>> fb291cbd3f9f... HID: sony: Corrections for the DualShock 4 HID descriptor
=======
	0x16, 0x00, 0xE0,   /*      Logical Minimum (-8192),        */
	0x26, 0xFF, 0x1F,   /*      Logical Maximum (8191),         */
>>>>>>> 39520eea198a... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x31,         /*      Report Count (51),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x4D,         /*      Report Count (77),              */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x12,         /*      Report ID (18),                 */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x8D,         /*      Report Count (141),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x13,         /*      Report ID (19),                 */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0xCD,         /*      Report Count (205),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x14,         /*      Report ID (20),                 */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x96, 0x0D, 0x01,   /*      Report Count (269),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x15,         /*      Report ID (21),                 */
	0x09, 0x28,         /*      Usage (28h),                    */
	0x96, 0x4D, 0x01,   /*      Report Count (333),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x29,         /*      Usage (29h),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x16,         /*      Report ID (22),                 */
	0x09, 0x2A,         /*      Usage (2Ah),                    */
	0x96, 0x8D, 0x01,   /*      Report Count (397),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x2B,         /*      Usage (2Bh),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x17,         /*      Report ID (23),                 */
	0x09, 0x2C,         /*      Usage (2Ch),                    */
	0x96, 0xCD, 0x01,   /*      Report Count (461),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x2D,         /*      Usage (2Dh),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x18,         /*      Report ID (24),                 */
	0x09, 0x2E,         /*      Usage (2Eh),                    */
	0x96, 0x0D, 0x02,   /*      Report Count (525),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x2F,         /*      Usage (2Fh),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x19,         /*      Report ID (25),                 */
	0x09, 0x30,         /*      Usage (30h),                    */
	0x96, 0x22, 0x02,   /*      Report Count (546),             */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x31,         /*      Usage (31h),                    */
	0x91, 0x02,         /*      Output (Variable),              */
	0x06, 0x80, 0xFF,   /*      Usage Page (FF80h),             */
	0x85, 0x82,         /*      Report ID (130),                */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x83,         /*      Report ID (131),                */
	0x09, 0x23,         /*      Usage (23h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x84,         /*      Report ID (132),                */
	0x09, 0x24,         /*      Usage (24h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x90,         /*      Report ID (144),                */
	0x09, 0x30,         /*      Usage (30h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x91,         /*      Report ID (145),                */
	0x09, 0x31,         /*      Usage (31h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x92,         /*      Report ID (146),                */
	0x09, 0x32,         /*      Usage (32h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x93,         /*      Report ID (147),                */
	0x09, 0x33,         /*      Usage (33h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA0,         /*      Report ID (160),                */
	0x09, 0x40,         /*      Usage (40h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA4,         /*      Report ID (164),                */
	0x09, 0x44,         /*      Usage (44h),                    */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0xC0                /*  End Collection                      */
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
};

static __u8 ps3remote_rdesc[] = {
	0x05, 0x01,          /* GUsagePage Generic Desktop */
	0x09, 0x05,          /* LUsage 0x05 [Game Pad] */
	0xA1, 0x01,          /* MCollection Application (mouse, keyboard) */

	 /* Use collection 1 for joypad buttons */
	 0xA1, 0x02,         /* MCollection Logical (interrelated data) */

	  /* Ignore the 1st byte, maybe it is used for a controller
	   * number but it's not needed for correct operation */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Arr[1] Abs[2]) */

	  /* Bytes from 2nd to 4th are a bitmap for joypad buttons, for these
	   * buttons multiple keypresses are allowed */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x19, 0x01,        /* LUsageMinimum 0x01 [Button 1 (primary/trigger)] */
	  0x29, 0x18,        /* LUsageMaximum 0x18 [Button 24] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x25, 0x01,        /* GLogicalMaximum 0x01 [1] */
	  0x75, 0x01,        /* GReportSize 0x01 [1] */
	  0x95, 0x18,        /* GReportCount 0x18 [24] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Var[1] Abs[2]) */

	  0xC0,              /* MEndCollection */

	 /* Use collection 2 for remote control buttons */
	 0xA1, 0x02,         /* MCollection Logical (interrelated data) */

	  /* 5th byte is used for remote control buttons */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x18,              /* LUsageMinimum [No button pressed] */
	  0x29, 0xFE,        /* LUsageMaximum 0xFE [Button 254] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x26, 0xFE, 0x00,  /* GLogicalMaximum 0x00FE [254] */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x80,              /* MInput  */

	  /* Ignore bytes from 6th to 11th, 6th to 10th are always constant at
	   * 0xff and 11th is for press indication */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x06,        /* GReportCount 0x06 [6] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Arr[1] Abs[2]) */

	  /* 12th byte is for battery strength */
	  0x05, 0x06,        /* GUsagePage Generic Device Controls */
	  0x09, 0x20,        /* LUsage 0x20 [Battery Strength] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x25, 0x05,        /* GLogicalMaximum 0x05 [5] */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Var[1] Abs[2]) */

	  0xC0,              /* MEndCollection */

	 0xC0                /* MEndCollection [Game Pad] */
>>>>>>> d829674d29d7... HID: sony: Add modified Dualshock 4 Bluetooth HID descriptor
};

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/* The default descriptor doesn't provide mapping for the accelerometers
 * or orientation sensors.  This fixed descriptor maps the accelerometers
 * to usage values 0x40, 0x41 and 0x42 and maps the orientation sensors
 * to usage values 0x43, 0x44 and 0x45.
 */
static u8 dualshock4_usb_rdesc[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x05,         /*  Usage (Gamepad),                    */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x01,         /*      Report ID (1),                  */
	0x09, 0x30,         /*      Usage (X),                      */
	0x09, 0x31,         /*      Usage (Y),                      */
	0x09, 0x32,         /*      Usage (Z),                      */
	0x09, 0x35,         /*      Usage (Rz),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x04,         /*      Report Count (4),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x39,         /*      Usage (Hat Switch),             */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x07,         /*      Logical Maximum (7),            */
	0x35, 0x00,         /*      Physical Minimum (0),           */
	0x46, 0x3B, 0x01,   /*      Physical Maximum (315),         */
	0x65, 0x14,         /*      Unit (Degrees),                 */
	0x75, 0x04,         /*      Report Size (4),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x81, 0x42,         /*      Input (Variable, Null State),   */
	0x65, 0x00,         /*      Unit,                           */
	0x05, 0x09,         /*      Usage Page (Button),            */
	0x19, 0x01,         /*      Usage Minimum (01h),            */
	0x29, 0x0E,         /*      Usage Maximum (0Eh),            */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x01,         /*      Logical Maximum (1),            */
	0x75, 0x01,         /*      Report Size (1),                */
	0x95, 0x0E,         /*      Report Count (14),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x75, 0x06,         /*      Report Size (6),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x7F,         /*      Logical Maximum (127),          */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x09, 0x33,         /*      Usage (Rx),                     */
	0x09, 0x34,         /*      Usage (Ry),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x02,         /*      Report Count (2),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x19, 0x40,         /*      Usage Minimum (40h),            */
	0x29, 0x42,         /*      Usage Maximum (42h),            */
	0x16, 0x00, 0x80,   /*      Logical Minimum (-32768),       */
	0x26, 0x00, 0x7F,   /*      Logical Maximum (32767),        */
	0x75, 0x10,         /*      Report Size (16),               */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x19, 0x43,         /*      Usage Minimum (43h),            */
	0x29, 0x45,         /*      Usage Maximum (45h),            */
	0x16, 0xFF, 0xBF,   /*      Logical Minimum (-16385),       */
	0x26, 0x00, 0x40,   /*      Logical Maximum (16384),        */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0xFF,         /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x27,         /*      Report Count (39),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x85, 0x05,         /*      Report ID (5),                  */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x1F,         /*      Report Count (31),              */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x04,         /*      Report ID (4),                  */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x02,         /*      Report ID (2),                  */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x08,         /*      Report ID (8),                  */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x10,         /*      Report ID (16),                 */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x04,         /*      Report Count (4),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x11,         /*      Report ID (17),                 */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x12,         /*      Report ID (18),                 */
	0x06, 0x02, 0xFF,   /*      Usage Page (FF02h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x13,         /*      Report ID (19),                 */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x16,         /*      Report Count (22),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x14,         /*      Report ID (20),                 */
	0x06, 0x05, 0xFF,   /*      Usage Page (FF05h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x10,         /*      Report Count (16),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x15,         /*      Report ID (21),                 */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x2C,         /*      Report Count (44),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x06, 0x80, 0xFF,   /*      Usage Page (FF80h),             */
	0x85, 0x80,         /*      Report ID (128),                */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x81,         /*      Report ID (129),                */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x82,         /*      Report ID (130),                */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x05,         /*      Report Count (5),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x83,         /*      Report ID (131),                */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x84,         /*      Report ID (132),                */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x04,         /*      Report Count (4),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x85,         /*      Report ID (133),                */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x86,         /*      Report ID (134),                */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x87,         /*      Report ID (135),                */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x23,         /*      Report Count (35),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x88,         /*      Report ID (136),                */
	0x09, 0x28,         /*      Usage (28h),                    */
	0x95, 0x22,         /*      Report Count (34),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x89,         /*      Report ID (137),                */
	0x09, 0x29,         /*      Usage (29h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x90,         /*      Report ID (144),                */
	0x09, 0x30,         /*      Usage (30h),                    */
	0x95, 0x05,         /*      Report Count (5),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x91,         /*      Report ID (145),                */
	0x09, 0x31,         /*      Usage (31h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x92,         /*      Report ID (146),                */
	0x09, 0x32,         /*      Usage (32h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x93,         /*      Report ID (147),                */
	0x09, 0x33,         /*      Usage (33h),                    */
	0x95, 0x0C,         /*      Report Count (12),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA0,         /*      Report ID (160),                */
	0x09, 0x40,         /*      Usage (40h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA1,         /*      Report ID (161),                */
	0x09, 0x41,         /*      Usage (41h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA2,         /*      Report ID (162),                */
	0x09, 0x42,         /*      Usage (42h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA3,         /*      Report ID (163),                */
	0x09, 0x43,         /*      Usage (43h),                    */
	0x95, 0x30,         /*      Report Count (48),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA4,         /*      Report ID (164),                */
	0x09, 0x44,         /*      Usage (44h),                    */
	0x95, 0x0D,         /*      Report Count (13),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA5,         /*      Report ID (165),                */
	0x09, 0x45,         /*      Usage (45h),                    */
	0x95, 0x15,         /*      Report Count (21),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA6,         /*      Report ID (166),                */
	0x09, 0x46,         /*      Usage (46h),                    */
	0x95, 0x15,         /*      Report Count (21),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF0,         /*      Report ID (240),                */
	0x09, 0x47,         /*      Usage (47h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF1,         /*      Report ID (241),                */
	0x09, 0x48,         /*      Usage (48h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF2,         /*      Report ID (242),                */
	0x09, 0x49,         /*      Usage (49h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA7,         /*      Report ID (167),                */
	0x09, 0x4A,         /*      Usage (4Ah),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA8,         /*      Report ID (168),                */
	0x09, 0x4B,         /*      Usage (4Bh),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA9,         /*      Report ID (169),                */
	0x09, 0x4C,         /*      Usage (4Ch),                    */
	0x95, 0x08,         /*      Report Count (8),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAA,         /*      Report ID (170),                */
	0x09, 0x4E,         /*      Usage (4Eh),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAB,         /*      Report ID (171),                */
	0x09, 0x4F,         /*      Usage (4Fh),                    */
	0x95, 0x39,         /*      Report Count (57),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAC,         /*      Report ID (172),                */
	0x09, 0x50,         /*      Usage (50h),                    */
	0x95, 0x39,         /*      Report Count (57),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAD,         /*      Report ID (173),                */
	0x09, 0x51,         /*      Usage (51h),                    */
	0x95, 0x0B,         /*      Report Count (11),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAE,         /*      Report ID (174),                */
	0x09, 0x52,         /*      Usage (52h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAF,         /*      Report ID (175),                */
	0x09, 0x53,         /*      Usage (53h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xB0,         /*      Report ID (176),                */
	0x09, 0x54,         /*      Usage (54h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0xC0                /*  End Collection                      */
};

/* The default descriptor doesn't provide mapping for the accelerometers
 * or orientation sensors.  This fixed descriptor maps the accelerometers
 * to usage values 0x40, 0x41 and 0x42 and maps the orientation sensors
 * to usage values 0x43, 0x44 and 0x45.
 */
static u8 dualshock4_usb_rdesc[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x05,         /*  Usage (Gamepad),                    */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x01,         /*      Report ID (1),                  */
	0x09, 0x30,         /*      Usage (X),                      */
	0x09, 0x31,         /*      Usage (Y),                      */
	0x09, 0x32,         /*      Usage (Z),                      */
	0x09, 0x35,         /*      Usage (Rz),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x04,         /*      Report Count (4),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x09, 0x39,         /*      Usage (Hat Switch),             */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x07,         /*      Logical Maximum (7),            */
	0x35, 0x00,         /*      Physical Minimum (0),           */
	0x46, 0x3B, 0x01,   /*      Physical Maximum (315),         */
	0x65, 0x14,         /*      Unit (Degrees),                 */
	0x75, 0x04,         /*      Report Size (4),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x81, 0x42,         /*      Input (Variable, Null State),   */
	0x65, 0x00,         /*      Unit,                           */
	0x05, 0x09,         /*      Usage Page (Button),            */
	0x19, 0x01,         /*      Usage Minimum (01h),            */
	0x29, 0x0E,         /*      Usage Maximum (0Eh),            */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x01,         /*      Logical Maximum (1),            */
	0x75, 0x01,         /*      Report Size (1),                */
	0x95, 0x0E,         /*      Report Count (14),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x75, 0x06,         /*      Report Size (6),                */
	0x95, 0x01,         /*      Report Count (1),               */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0x7F,         /*      Logical Maximum (127),          */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x09, 0x33,         /*      Usage (Rx),                     */
	0x09, 0x34,         /*      Usage (Ry),                     */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x02,         /*      Report Count (2),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x05, 0x01,         /*      Usage Page (Desktop),           */
	0x19, 0x40,         /*      Usage Minimum (40h),            */
	0x29, 0x42,         /*      Usage Maximum (42h),            */
	0x16, 0x00, 0x80,   /*      Logical Minimum (-32768),       */
	0x26, 0x00, 0x7F,   /*      Logical Maximum (32767),        */
	0x75, 0x10,         /*      Report Size (16),               */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x19, 0x43,         /*      Usage Minimum (43h),            */
	0x29, 0x45,         /*      Usage Maximum (45h),            */
	0x16, 0xFF, 0xBF,   /*      Logical Minimum (-16385),       */
	0x26, 0x00, 0x40,   /*      Logical Maximum (16384),        */
	0x95, 0x03,         /*      Report Count (3),               */
	0x81, 0x02,         /*      Input (Variable),               */
	0x06, 0x00, 0xFF,   /*      Usage Page (FF00h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x15, 0x00,         /*      Logical Minimum (0),            */
	0x25, 0xFF,         /*      Logical Maximum (255),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x27,         /*      Report Count (39),              */
	0x81, 0x02,         /*      Input (Variable),               */
	0x85, 0x05,         /*      Report ID (5),                  */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x1F,         /*      Report Count (31),              */
	0x91, 0x02,         /*      Output (Variable),              */
	0x85, 0x04,         /*      Report ID (4),                  */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x02,         /*      Report ID (2),                  */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x24,         /*      Report Count (36),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x08,         /*      Report ID (8),                  */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x10,         /*      Report ID (16),                 */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x04,         /*      Report Count (4),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x11,         /*      Report ID (17),                 */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x12,         /*      Report ID (18),                 */
	0x06, 0x02, 0xFF,   /*      Usage Page (FF02h),             */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x13,         /*      Report ID (19),                 */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x16,         /*      Report Count (22),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x14,         /*      Report ID (20),                 */
	0x06, 0x05, 0xFF,   /*      Usage Page (FF05h),             */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x10,         /*      Report Count (16),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x15,         /*      Report ID (21),                 */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x2C,         /*      Report Count (44),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x06, 0x80, 0xFF,   /*      Usage Page (FF80h),             */
	0x85, 0x80,         /*      Report ID (128),                */
	0x09, 0x20,         /*      Usage (20h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x81,         /*      Report ID (129),                */
	0x09, 0x21,         /*      Usage (21h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x82,         /*      Report ID (130),                */
	0x09, 0x22,         /*      Usage (22h),                    */
	0x95, 0x05,         /*      Report Count (5),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x83,         /*      Report ID (131),                */
	0x09, 0x23,         /*      Usage (23h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x84,         /*      Report ID (132),                */
	0x09, 0x24,         /*      Usage (24h),                    */
	0x95, 0x04,         /*      Report Count (4),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x85,         /*      Report ID (133),                */
	0x09, 0x25,         /*      Usage (25h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x86,         /*      Report ID (134),                */
	0x09, 0x26,         /*      Usage (26h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x87,         /*      Report ID (135),                */
	0x09, 0x27,         /*      Usage (27h),                    */
	0x95, 0x23,         /*      Report Count (35),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x88,         /*      Report ID (136),                */
	0x09, 0x28,         /*      Usage (28h),                    */
	0x95, 0x22,         /*      Report Count (34),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x89,         /*      Report ID (137),                */
	0x09, 0x29,         /*      Usage (29h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x90,         /*      Report ID (144),                */
	0x09, 0x30,         /*      Usage (30h),                    */
	0x95, 0x05,         /*      Report Count (5),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x91,         /*      Report ID (145),                */
	0x09, 0x31,         /*      Usage (31h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x92,         /*      Report ID (146),                */
	0x09, 0x32,         /*      Usage (32h),                    */
	0x95, 0x03,         /*      Report Count (3),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0x93,         /*      Report ID (147),                */
	0x09, 0x33,         /*      Usage (33h),                    */
	0x95, 0x0C,         /*      Report Count (12),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA0,         /*      Report ID (160),                */
	0x09, 0x40,         /*      Usage (40h),                    */
	0x95, 0x06,         /*      Report Count (6),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA1,         /*      Report ID (161),                */
	0x09, 0x41,         /*      Usage (41h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA2,         /*      Report ID (162),                */
	0x09, 0x42,         /*      Usage (42h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA3,         /*      Report ID (163),                */
	0x09, 0x43,         /*      Usage (43h),                    */
	0x95, 0x30,         /*      Report Count (48),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA4,         /*      Report ID (164),                */
	0x09, 0x44,         /*      Usage (44h),                    */
	0x95, 0x0D,         /*      Report Count (13),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA5,         /*      Report ID (165),                */
	0x09, 0x45,         /*      Usage (45h),                    */
	0x95, 0x15,         /*      Report Count (21),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA6,         /*      Report ID (166),                */
	0x09, 0x46,         /*      Usage (46h),                    */
	0x95, 0x15,         /*      Report Count (21),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF0,         /*      Report ID (240),                */
	0x09, 0x47,         /*      Usage (47h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF1,         /*      Report ID (241),                */
	0x09, 0x48,         /*      Usage (48h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xF2,         /*      Report ID (242),                */
	0x09, 0x49,         /*      Usage (49h),                    */
	0x95, 0x0F,         /*      Report Count (15),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA7,         /*      Report ID (167),                */
	0x09, 0x4A,         /*      Usage (4Ah),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA8,         /*      Report ID (168),                */
	0x09, 0x4B,         /*      Usage (4Bh),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xA9,         /*      Report ID (169),                */
	0x09, 0x4C,         /*      Usage (4Ch),                    */
	0x95, 0x08,         /*      Report Count (8),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAA,         /*      Report ID (170),                */
	0x09, 0x4E,         /*      Usage (4Eh),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAB,         /*      Report ID (171),                */
	0x09, 0x4F,         /*      Usage (4Fh),                    */
	0x95, 0x39,         /*      Report Count (57),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAC,         /*      Report ID (172),                */
	0x09, 0x50,         /*      Usage (50h),                    */
	0x95, 0x39,         /*      Report Count (57),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAD,         /*      Report ID (173),                */
	0x09, 0x51,         /*      Usage (51h),                    */
	0x95, 0x0B,         /*      Report Count (11),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAE,         /*      Report ID (174),                */
	0x09, 0x52,         /*      Usage (52h),                    */
	0x95, 0x01,         /*      Report Count (1),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xAF,         /*      Report ID (175),                */
	0x09, 0x53,         /*      Usage (53h),                    */
	0x95, 0x02,         /*      Report Count (2),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0x85, 0xB0,         /*      Report ID (176),                */
	0x09, 0x54,         /*      Usage (54h),                    */
	0x95, 0x3F,         /*      Report Count (63),              */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0xC0                /*  End Collection                      */
};

static __u8 ps3remote_rdesc[] = {
	0x05, 0x01,          /* GUsagePage Generic Desktop */
	0x09, 0x05,          /* LUsage 0x05 [Game Pad] */
	0xA1, 0x01,          /* MCollection Application (mouse, keyboard) */

	 /* Use collection 1 for joypad buttons */
	 0xA1, 0x02,         /* MCollection Logical (interrelated data) */

	  /* Ignore the 1st byte, maybe it is used for a controller
	   * number but it's not needed for correct operation */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Arr[1] Abs[2]) */

	  /* Bytes from 2nd to 4th are a bitmap for joypad buttons, for these
	   * buttons multiple keypresses are allowed */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x19, 0x01,        /* LUsageMinimum 0x01 [Button 1 (primary/trigger)] */
	  0x29, 0x18,        /* LUsageMaximum 0x18 [Button 24] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x25, 0x01,        /* GLogicalMaximum 0x01 [1] */
	  0x75, 0x01,        /* GReportSize 0x01 [1] */
	  0x95, 0x18,        /* GReportCount 0x18 [24] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Var[1] Abs[2]) */

	  0xC0,              /* MEndCollection */

	 /* Use collection 2 for remote control buttons */
	 0xA1, 0x02,         /* MCollection Logical (interrelated data) */

	  /* 5th byte is used for remote control buttons */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x18,              /* LUsageMinimum [No button pressed] */
	  0x29, 0xFE,        /* LUsageMaximum 0xFE [Button 254] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x26, 0xFE, 0x00,  /* GLogicalMaximum 0x00FE [254] */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x80,              /* MInput  */

	  /* Ignore bytes from 6th to 11th, 6th to 10th are always constant at
	   * 0xff and 11th is for press indication */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x06,        /* GReportCount 0x06 [6] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Arr[1] Abs[2]) */

	  /* 12th byte is for battery strength */
	  0x05, 0x06,        /* GUsagePage Generic Device Controls */
	  0x09, 0x20,        /* LUsage 0x20 [Battery Strength] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x25, 0x05,        /* GLogicalMaximum 0x05 [5] */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Var[1] Abs[2]) */

	  0xC0,              /* MEndCollection */

	 0xC0                /* MEndCollection [Game Pad] */
};

=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
static const unsigned int ps3remote_keymap_joypad_buttons[] = {
	[0x01] = KEY_SELECT,
	[0x02] = BTN_THUMBL,		/* L3 */
	[0x03] = BTN_THUMBR,		/* R3 */
	[0x04] = BTN_START,
	[0x05] = KEY_UP,
	[0x06] = KEY_RIGHT,
	[0x07] = KEY_DOWN,
	[0x08] = KEY_LEFT,
	[0x09] = BTN_TL2,		/* L2 */
	[0x0a] = BTN_TR2,		/* R2 */
	[0x0b] = BTN_TL,		/* L1 */
	[0x0c] = BTN_TR,		/* R1 */
	[0x0d] = KEY_OPTION,		/* options/triangle */
	[0x0e] = KEY_BACK,		/* back/circle */
	[0x0f] = BTN_0,			/* cross */
	[0x10] = KEY_SCREEN,		/* view/square */
	[0x11] = KEY_HOMEPAGE,		/* PS button */
	[0x14] = KEY_ENTER,
};
static const unsigned int ps3remote_keymap_remote_buttons[] = {
	[0x00] = KEY_1,
	[0x01] = KEY_2,
	[0x02] = KEY_3,
	[0x03] = KEY_4,
	[0x04] = KEY_5,
	[0x05] = KEY_6,
	[0x06] = KEY_7,
	[0x07] = KEY_8,
	[0x08] = KEY_9,
	[0x09] = KEY_0,
	[0x0e] = KEY_ESC,		/* return */
	[0x0f] = KEY_CLEAR,
	[0x16] = KEY_EJECTCD,
	[0x1a] = KEY_MENU,		/* top menu */
	[0x28] = KEY_TIME,
	[0x30] = KEY_PREVIOUS,
	[0x31] = KEY_NEXT,
	[0x32] = KEY_PLAY,
	[0x33] = KEY_REWIND,		/* scan back */
	[0x34] = KEY_FORWARD,		/* scan forward */
	[0x38] = KEY_STOP,
	[0x39] = KEY_PAUSE,
	[0x40] = KEY_CONTEXT_MENU,	/* pop up/menu */
	[0x60] = KEY_FRAMEBACK,		/* slow/step back */
	[0x61] = KEY_FRAMEFORWARD,	/* slow/step forward */
	[0x63] = KEY_SUBTITLE,
	[0x64] = KEY_AUDIO,
	[0x65] = KEY_ANGLE,
	[0x70] = KEY_INFO,		/* display */
	[0x80] = KEY_BLUE,
	[0x81] = KEY_RED,
	[0x82] = KEY_GREEN,
	[0x83] = KEY_YELLOW,
};

static const unsigned int buzz_keymap[] = {
	/*
	 * The controller has 4 remote buzzers, each with one LED and 5
	 * buttons.
	 * 
	 * We use the mapping chosen by the controller, which is:
	 *
	 * Key          Offset
	 * -------------------
	 * Buzz              1
	 * Blue              5
	 * Orange            4
	 * Green             3
	 * Yellow            2
	 *
	 * So, for example, the orange button on the third buzzer is mapped to
	 * BTN_TRIGGER_HAPPY14
	 */
	[ 1] = BTN_TRIGGER_HAPPY1,
	[ 2] = BTN_TRIGGER_HAPPY2,
	[ 3] = BTN_TRIGGER_HAPPY3,
	[ 4] = BTN_TRIGGER_HAPPY4,
	[ 5] = BTN_TRIGGER_HAPPY5,
	[ 6] = BTN_TRIGGER_HAPPY6,
	[ 7] = BTN_TRIGGER_HAPPY7,
	[ 8] = BTN_TRIGGER_HAPPY8,
	[ 9] = BTN_TRIGGER_HAPPY9,
	[10] = BTN_TRIGGER_HAPPY10,
	[11] = BTN_TRIGGER_HAPPY11,
	[12] = BTN_TRIGGER_HAPPY12,
	[13] = BTN_TRIGGER_HAPPY13,
	[14] = BTN_TRIGGER_HAPPY14,
	[15] = BTN_TRIGGER_HAPPY15,
	[16] = BTN_TRIGGER_HAPPY16,
	[17] = BTN_TRIGGER_HAPPY17,
	[18] = BTN_TRIGGER_HAPPY18,
	[19] = BTN_TRIGGER_HAPPY19,
	[20] = BTN_TRIGGER_HAPPY20,
};

static enum power_supply_property sony_battery_props[] = {
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_STATUS,
};

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
struct sixaxis_led {
	__u8 time_enabled; /* the total time the led is active (0xff means forever) */
	__u8 duty_length;  /* how long a cycle is in deciseconds (0 means "really fast") */
	__u8 enabled;
	__u8 duty_off; /* % of duty_length the led is off (0xff means 100%) */
	__u8 duty_on;  /* % of duty_length the led is on (0xff mean 100%) */
} __packed;

struct sixaxis_rumble {
	__u8 padding;
	__u8 right_duration; /* Right motor duration (0xff means forever) */
	__u8 right_motor_on; /* Right (small) motor on/off, only supports values of 0 or 1 (off/on) */
	__u8 left_duration;    /* Left motor duration (0xff means forever) */
	__u8 left_motor_force; /* left (large) motor, supports force values from 0 to 255 */
} __packed;

struct sixaxis_output_report {
	__u8 report_id;
	struct sixaxis_rumble rumble;
	__u8 padding[4];
	__u8 leds_bitmap; /* bitmap of enabled LEDs: LED_1 = 0x02, LED_2 = 0x04, ... */
	struct sixaxis_led led[4];    /* LEDx at (4 - x) */
	struct sixaxis_led _reserved; /* LED5, not actually soldered */
} __packed;

union sixaxis_output_report_01 {
	struct sixaxis_output_report data;
	__u8 buf[36];
};

static spinlock_t sony_dev_list_lock;
static LIST_HEAD(sony_device_list);
static DEFINE_IDA(sony_device_id_allocator);

struct sony_sc {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	spinlock_t lock;
	struct list_head list_node;
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
struct sony_sc {
	spinlock_t lock;
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
static spinlock_t sony_dev_list_lock;
static LIST_HEAD(sony_device_list);

struct sony_sc {
	spinlock_t lock;
	struct list_head list_node;
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	spinlock_t lock;
	struct list_head list_node;
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
	spinlock_t lock;
	struct list_head list_node;
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
	spinlock_t lock;
	struct list_head list_node;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	struct hid_device *hdev;
	struct led_classdev *leds[MAX_LEDS];
	unsigned long quirks;
	struct work_struct state_worker;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	struct power_supply battery;
	int device_id;
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	struct power_supply battery;
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
struct sony_sc {
	spinlock_t lock;
=======
static spinlock_t sony_dev_list_lock;
static LIST_HEAD(sony_device_list);

struct sony_sc {
	spinlock_t lock;
	struct list_head list_node;
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
	struct hid_device *hdev;
	struct led_classdev *leds[MAX_LEDS];
	unsigned long quirks;
	struct work_struct state_worker;
	struct power_supply battery;
<<<<<<< HEAD
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
	struct power_supply battery;
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	struct power_supply battery;
	int device_id;
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
	struct power_supply battery;
	int device_id;
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
	struct power_supply battery;
	int device_id;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

#ifdef CONFIG_SONY_FF
	__u8 left;
	__u8 right;
#endif

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	__u8 mac_address[6];
=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
	__u8 mac_address[6];
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
	__u8 mac_address[6];
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	__u8 mac_address[6];
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
	__u8 mac_address[6];
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
	__u8 mac_address[6];
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	__u8 worker_initialized;
	__u8 cable_state;
	__u8 battery_charging;
	__u8 battery_capacity;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	__u8 led_state[MAX_LEDS];
<<<<<<< HEAD
<<<<<<< HEAD
	__u8 led_delay_on[MAX_LEDS];
	__u8 led_delay_off[MAX_LEDS];
=======
	__u8 led_state[MAX_LEDS];
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
	__u8 led_count;
};

static __u8 *sixaxis_fixup(struct hid_device *hdev, __u8 *rdesc,
			     unsigned int *rsize)
{
	*rsize = sizeof(sixaxis_rdesc);
	return sixaxis_rdesc;
}
=======
=======
	__u8 cable_state;
	__u8 battery_charging;
	__u8 battery_capacity;
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	__u8 led_state[MAX_LEDS];
	__u8 led_count;
};
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

=======
	__u8 led_count;
};

>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
	__u8 led_count;
};

>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
	__u8 led_state[MAX_LEDS];
	__u8 led_count;
};

>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	__u8 led_state[MAX_LEDS];
	__u8 led_delay_on[MAX_LEDS];
	__u8 led_delay_off[MAX_LEDS];
	__u8 led_count;
};

<<<<<<< HEAD
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
static __u8 *ps3remote_fixup(struct hid_device *hdev, __u8 *rdesc,
			     unsigned int *rsize)
{
	*rsize = sizeof(ps3remote_rdesc);
	return ps3remote_rdesc;
}

static int ps3remote_mapping(struct hid_device *hdev, struct hid_input *hi,
			     struct hid_field *field, struct hid_usage *usage,
			     unsigned long **bit, int *max)
{
	unsigned int key = usage->hid & HID_USAGE;

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		return -1;

	switch (usage->collection_index) {
	case 1:
		if (key >= ARRAY_SIZE(ps3remote_keymap_joypad_buttons))
			return -1;

		key = ps3remote_keymap_joypad_buttons[key];
		if (!key)
			return -1;
		break;
	case 2:
		if (key >= ARRAY_SIZE(ps3remote_keymap_remote_buttons))
			return -1;

		key = ps3remote_keymap_remote_buttons[key];
		if (!key)
			return -1;
		break;
	default:
		return -1;
	}

	hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
	return 1;
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

/* Sony Vaio VGX has wrongly mouse pointer declared as constant */
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======

/* Sony Vaio VGX has wrongly mouse pointer declared as constant */
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======

/* Sony Vaio VGX has wrongly mouse pointer declared as constant */
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======

/* Sony Vaio VGX has wrongly mouse pointer declared as constant */
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======

/* Sony Vaio VGX has wrongly mouse pointer declared as constant */
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
static __u8 *sony_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);

	/*
	 * Some Sony RF receivers wrongly declare the mouse pointer as a
	 * a constant non-data variable.
	 */
	if ((sc->quirks & VAIO_RDESC_CONSTANT) && *rsize >= 56 &&
	    /* usage page: generic desktop controls */
	    /* rdesc[0] == 0x05 && rdesc[1] == 0x01 && */
	    /* usage: mouse */
	    rdesc[2] == 0x09 && rdesc[3] == 0x02 &&
	    /* input (usage page for x,y axes): constant, variable, relative */
	    rdesc[54] == 0x81 && rdesc[55] == 0x07) {
		hid_info(hdev, "Fixing up Sony RF Receiver report descriptor\n");
		/* input: data, variable, relative */
		rdesc[55] = 0x06;
	}

	/*
	 * The default Dualshock 4 USB descriptor doesn't assign
	 * the gyroscope values to corresponding axes so we need a
	 * modified one.
	 */
	if ((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && *rsize == 467) {
<<<<<<< HEAD
<<<<<<< HEAD
		hid_info(hdev, "Using modified Dualshock 4 report descriptor with gyroscope axes\n");
		rdesc = dualshock4_usb_rdesc;
		*rsize = sizeof(dualshock4_usb_rdesc);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
		hid_info(hdev, "Using modified Dualshock 4 report descriptor with gyroscope axes\n");
		rdesc = dualshock4_usb_rdesc;
		*rsize = sizeof(dualshock4_usb_rdesc);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	} else if ((sc->quirks & DUALSHOCK4_CONTROLLER_BT) && *rsize == 357) {
		hid_info(hdev, "Using modified Dualshock 4 Bluetooth report descriptor\n");
		rdesc = dualshock4_bt_rdesc;
		*rsize = sizeof(dualshock4_bt_rdesc);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	}

	/* The HID descriptor exposed over BT has a trailing zero byte */
	if ((((sc->quirks & SIXAXIS_CONTROLLER_USB) && *rsize == 148) ||
			((sc->quirks & SIXAXIS_CONTROLLER_BT) && *rsize == 149)) &&
			rdesc[83] == 0x75) {
		hid_info(hdev, "Fixing up Sony Sixaxis report descriptor\n");
		memcpy((void *)&rdesc[83], (void *)&sixaxis_rdesc_fixup,
			sizeof(sixaxis_rdesc_fixup));
	} else if (sc->quirks & SIXAXIS_CONTROLLER_USB &&
		   *rsize > sizeof(sixaxis_rdesc_fixup2)) {
		hid_info(hdev, "Sony Sixaxis clone detected. Using original report descriptor (size: %d clone; %d new)\n",
			 *rsize, (int)sizeof(sixaxis_rdesc_fixup2));
		*rsize = sizeof(sixaxis_rdesc_fixup2);
		memcpy(rdesc, &sixaxis_rdesc_fixup2, *rsize);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> ed19d8cf28b2... HID: sony: Map gyroscopes and accelerometers to axes
	}

	if (sc->quirks & SIXAXIS_CONTROLLER)
		return sixaxis_fixup(hdev, rdesc, rsize);

=======
	}

>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
	}

>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
	}

>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	if (sc->quirks & PS3REMOTE)
		return ps3remote_fixup(hdev, rdesc, rsize);

	return rdesc;
}

static void sixaxis_parse_report(struct sony_sc *sc, __u8 *rd, int size)
{
	static const __u8 sixaxis_battery_capacity[] = { 0, 1, 25, 50, 75, 100 };
	unsigned long flags;
	__u8 cable_state, battery_capacity, battery_charging;

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * The sixaxis is charging if the battery value is 0xee
=======
	/* The sixaxis is charging if the battery value is 0xee
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
	/*
	 * The sixaxis is charging if the battery value is 0xee
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
	/*
	 * The sixaxis is charging if the battery value is 0xee
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
	/*
	 * The sixaxis is charging if the battery value is 0xee
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	 * and it is fully charged if the value is 0xef.
	 * It does not report the actual level while charging so it
	 * is set to 100% while charging is in progress.
	 */
	if (rd[30] >= 0xee) {
		battery_capacity = 100;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
		battery_charging = !(rd[30] & 0x01);
		cable_state = 1;
=======
		battery_charging = !(rd[30] & 0x01);
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	} else {
		__u8 index = rd[30] <= 5 ? rd[30] : 5;
		battery_capacity = sixaxis_battery_capacity[index];
		battery_charging = 0;
<<<<<<< HEAD
		cable_state = 0;
	}
=======
		battery_charging = rd[30] & 0x01;
	} else {
		battery_capacity = sixaxis_battery_capacity[rd[30]];
		battery_charging = 0;
	}
	cable_state = (rd[31] >> 4) & 0x01;
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
	}
	cable_state = !(rd[31] & 0x04);
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

	spin_lock_irqsave(&sc->lock, flags);
	sc->cable_state = cable_state;
	sc->battery_capacity = battery_capacity;
	sc->battery_charging = battery_charging;
	spin_unlock_irqrestore(&sc->lock, flags);
}

static void dualshock4_parse_report(struct sony_sc *sc, __u8 *rd, int size)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	struct hid_input *hidinput = list_entry(sc->hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;
	unsigned long flags;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	int n, offset;
=======
	int n, offset = 35;
>>>>>>> e56062305069... HID: sony: add output events for the multi-touch pad on the Dualshock 4
=======
	int n, offset;
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	__u8 cable_state, battery_capacity, battery_charging;
=======
	int n, m, offset, num_touch_data, max_touch_data;
	u8 cable_state, battery_capacity, battery_charging;
	u16 timestamp;

	/* When using Bluetooth the header is 2 bytes longer, so skip these. */
	int data_offset = (sc->quirks & DUALSHOCK4_CONTROLLER_BT) ? 2 : 0;

	/* Second bit of third button byte is for the touchpad button. */
	offset = data_offset + DS4_INPUT_REPORT_BUTTON_OFFSET;
	input_report_key(sc->touchpad, BTN_LEFT, rd[offset+2] & 0x2);
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device

	/*
	 * Battery and touchpad data starts at byte 30 in the USB report and
	 * 32 in Bluetooth report.
	 */
	offset = (sc->quirks & DUALSHOCK4_CONTROLLER_USB) ? 30 : 32;

	/*
	 * The lower 4 bits of byte 30 contain the battery level
	 * and the 5th bit contains the USB cable state.
	 */
	cable_state = (rd[offset] >> 4) & 0x01;
	battery_capacity = rd[offset] & 0x0F;

	/*
	 * When a USB power source is connected the battery level ranges from
	 * 0 to 10, and when running on battery power it ranges from 0 to 9.
	 * A battery level above 10 when plugged in means charge completed.
	 */
	if (!cable_state || battery_capacity > 10)
<<<<<<< HEAD
=======
	unsigned long flags;
	__u8 cable_state, battery_capacity, battery_charging;

	/* The lower 4 bits of byte 30 contain the battery level
	 * and the 5th bit contains the USB cable state.
	 */
	cable_state = (rd[30] >> 4) & 0x01;
	battery_capacity = rd[30] & 0x0F;

	/* On USB the Dualshock 4 battery level goes from 0 to 11.
	 * A battery level of 11 means fully charged.
	 */
	if (cable_state && battery_capacity == 11)
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		battery_charging = 0;
	else
		battery_charging = 1;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (!cable_state)
		battery_capacity++;
	if (battery_capacity > 10)
		battery_capacity = 10;

<<<<<<< HEAD
=======
	if (battery_capacity > 10)
		battery_capacity--;
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	battery_capacity *= 10;

	spin_lock_irqsave(&sc->lock, flags);
	sc->cable_state = cable_state;
	sc->battery_capacity = battery_capacity;
	sc->battery_charging = battery_charging;
	spin_unlock_irqrestore(&sc->lock, flags);
<<<<<<< HEAD
<<<<<<< HEAD

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
	/*
	 * The Dualshock 4 multi-touch trackpad data starts at offset 33 on USB
	 * and 35 on Bluetooth.
	 * The first byte indicates the number of touch data in the report.
	 * Trackpad data starts 2 bytes later (e.g. 35 for USB).
	 */
	offset = data_offset + DS4_INPUT_REPORT_TOUCHPAD_OFFSET;
	max_touch_data = (sc->quirks & DUALSHOCK4_CONTROLLER_BT) ? 4 : 3;
	if (rd[offset] > 0 && rd[offset] <= max_touch_data)
		num_touch_data = rd[offset];
	else
		num_touch_data = 1;
	offset += 1;

	for (m = 0; m < num_touch_data; m++) {
		/* Skip past timestamp */
		offset += 1;
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device

>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	offset += 5;

	/*
	 * The Dualshock 4 multi-touch trackpad data starts at offset 35 on USB
	 * and 37 on Bluetooth.
<<<<<<< HEAD
=======
	/* The Dualshock 4 multi-touch trackpad data starts at offset 35 on USB.
>>>>>>> e56062305069... HID: sony: add output events for the multi-touch pad on the Dualshock 4
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	 * The first 7 bits of the first byte is a counter and bit 8 is a touch
	 * indicator that is 0 when pressed and 1 when not pressed.
	 * The next 3 bytes are two 12 bit touch coordinates, X and Y.
	 * The data for the second touch is in the same format and immediatly
	 * follows the data for the first.
	 */
	for (n = 0; n < 2; n++) {
		__u16 x, y;

		x = rd[offset+1] | ((rd[offset+2] & 0xF) << 8);
		y = ((rd[offset+2] & 0xF0) >> 4) | (rd[offset+3] << 4);

		input_mt_slot(input_dev, n);
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER,
					!(rd[offset] >> 7));
		input_report_abs(input_dev, ABS_MT_POSITION_X, x);
		input_report_abs(input_dev, ABS_MT_POSITION_Y, y);

		offset += 4;
	}
<<<<<<< HEAD
=======
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

static int sony_raw_event(struct hid_device *hdev, struct hid_report *report,
		__u8 *rd, int size)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);

	/*
	 * Sixaxis HID report has acclerometers/gyro with MSByte first, this
	 * has to be BYTE_SWAPPED before passing up to joystick interface
	 */
	if ((sc->quirks & SIXAXIS_CONTROLLER) && rd[0] == 0x01 && size == 49) {
		swap(rd[41], rd[42]);
		swap(rd[43], rd[44]);
		swap(rd[45], rd[46]);
		swap(rd[47], rd[48]);

		sixaxis_parse_report(sc, rd, size);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	} else if (((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) || ((sc->quirks & DUALSHOCK4_CONTROLLER_BT)
			&& rd[0] == 0x11 && size == 78)) {
=======
	} else if ((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) {
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
	} else if (((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) || ((sc->quirks & DUALSHOCK4_CONTROLLER_BT)
			&& rd[0] == 0x11 && size == 78)) {
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	} else if ((sc->quirks & MOTION_CONTROLLER_BT) && rd[0] == 0x01 && size == 49) {
		sixaxis_parse_report(sc, rd, size);
	} else if ((sc->quirks & NAVIGATION_CONTROLLER) && rd[0] == 0x01 &&
			size == 49) {
		sixaxis_parse_report(sc, rd, size);
	} else if ((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) {
		dualshock4_parse_report(sc, rd, size);
	} else if (((sc->quirks & DUALSHOCK4_CONTROLLER_BT) && rd[0] == 0x11 &&
			size == 78)) {
		/* CRC check */
		u8 bthdr = 0xA1;
		u32 crc;
		u32 report_crc;

		crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
		crc = ~crc32_le(crc, rd, DS4_INPUT_REPORT_0x11_SIZE-4);
		report_crc = get_unaligned_le32(&rd[DS4_INPUT_REPORT_0x11_SIZE-4]);
		if (crc != report_crc) {
			hid_dbg(sc->hdev, "DualShock 4 input report's CRC check failed, received crc 0x%0x != 0x%0x\n",
				report_crc, crc);
			return -EILSEQ;
		}

		dualshock4_parse_report(sc, rd, size);
	} else if ((sc->quirks & DUALSHOCK4_DONGLE) && rd[0] == 0x01 &&
			size == 64) {
		/*
		 * In the case of a DS4 USB dongle, bit[2] of byte 31 indicates
		 * if a DS4 is actually connected (indicated by '0').
		 * For non-dongle, this bit is always 0 (connected).
		 */
		bool connected = (rd[31] & 0x04) ? false : true;

		if (!sc->ds4_dongle_connected && connected) {
			hid_info(sc->hdev, "DualShock 4 USB dongle: controller connected\n");
			sony_set_leds(sc);
			sc->ds4_dongle_connected = true;
		} else if (sc->ds4_dongle_connected && !connected) {
			hid_info(sc->hdev, "DualShock 4 USB dongle: controller disconnected\n");
			sc->ds4_dongle_connected = false;
			/* Return 0, so hidraw can get the report. */
			return 0;
		} else if (!sc->ds4_dongle_connected) {
			/* Return 0, so hidraw can get the report. */
			return 0;
		}

>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device
		dualshock4_parse_report(sc, rd, size);
	}

	return 0;
}

static int sony_mapping(struct hid_device *hdev, struct hid_input *hi,
			struct hid_field *field, struct hid_usage *usage,
			unsigned long **bit, int *max)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);

	if (sc->quirks & BUZZ_CONTROLLER) {
		unsigned int key = usage->hid & HID_USAGE;

		if ((usage->hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
			return -1;

		switch (usage->collection_index) {
		case 1:
			if (key >= ARRAY_SIZE(buzz_keymap))
				return -1;

			key = buzz_keymap[key];
			if (!key)
				return -1;
			break;
		default:
			return -1;
		}

		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
		return 1;
	}

	if (sc->quirks & PS3REMOTE)
		return ps3remote_mapping(hdev, hi, field, usage, bit, max);

	/* Let hid-core decide for the others */
	return 0;
}

<<<<<<< HEAD
static int sony_register_touchpad(struct hid_input *hi, int touch_count,
					int w, int h)
{
	struct input_dev *input_dev = hi->input;
	int ret;

	ret = input_mt_init_slots(input_dev, touch_count, 0);
	if (ret < 0)
		return ret;

	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0, w, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0, h, 0, 0);

	return 0;
}

static int sony_input_configured(struct hid_device *hdev,
					struct hid_input *hidinput)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);
	int ret;

	/*
	 * The Dualshock 4 touchpad supports 2 touches and has a
	 * resolution of 1920x942 (44.86 dots/mm).
	 */
	if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		ret = sony_register_touchpad(hidinput, 2, 1920, 942);
		if (ret) {
			hid_err(sc->hdev,
				"Unable to initialize multi-touch slots: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}

=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
/*
 * Sending HID_REQ_GET_REPORT changes the operation mode of the ps3 controller
 * to "operational".  Without this, the ps3 controller will not report any
 * events.
 */
<<<<<<< HEAD
static int sixaxis_set_operational_usb(struct hid_device *hdev)
{
	int ret;
	char *buf = kmalloc(18, GFP_KERNEL);

	if (!buf)
		return -ENOMEM;

	ret = hid_hw_raw_request(hdev, 0xf2, buf, 17, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);

	if (ret < 0)
		hid_err(hdev, "can't set operational mode\n");

	kfree(buf);

	return ret;
}

static int sixaxis_set_operational_bt(struct hid_device *hdev)
{
	unsigned char buf[] = { 0xf4,  0x42, 0x03, 0x00, 0x00 };
	return hid_hw_raw_request(hdev, buf[0], buf, sizeof(buf),
				  HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
/*
 * Requesting feature report 0x02 in Bluetooth mode changes the state of the
 * controller so that it sends full input reports of type 0x11.
 */
static int dualshock4_set_operational_bt(struct hid_device *hdev)
{
<<<<<<< HEAD
	__u8 buf[37] = { 0 };
=======
	u8 *buf;
	int ret;
	short gyro_pitch_bias, gyro_pitch_plus, gyro_pitch_minus;
	short gyro_yaw_bias, gyro_yaw_plus, gyro_yaw_minus;
	short gyro_roll_bias, gyro_roll_plus, gyro_roll_minus;
	short gyro_speed_plus, gyro_speed_minus;
	short acc_x_plus, acc_x_minus;
	short acc_y_plus, acc_y_minus;
	short acc_z_plus, acc_z_minus;
	int speed_2x;
	int range_2g;

	/* For Bluetooth we use a different request, which supports CRC.
	 * Note: in Bluetooth mode feature report 0x02 also changes the state
	 * of the controller, so that it sends input reports of type 0x11.
	 */
	if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) {
		buf = kmalloc(DS4_FEATURE_REPORT_0x02_SIZE, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		ret = hid_hw_raw_request(sc->hdev, 0x02, buf,
					 DS4_FEATURE_REPORT_0x02_SIZE,
					 HID_FEATURE_REPORT,
					 HID_REQ_GET_REPORT);
		if (ret < 0)
			goto err_stop;
	} else {
		u8 bthdr = 0xA3;
		u32 crc;
		u32 report_crc;
		int retries;

		buf = kmalloc(DS4_FEATURE_REPORT_0x05_SIZE, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		for (retries = 0; retries < 3; retries++) {
			ret = hid_hw_raw_request(sc->hdev, 0x05, buf,
						 DS4_FEATURE_REPORT_0x05_SIZE,
						 HID_FEATURE_REPORT,
						 HID_REQ_GET_REPORT);
			if (ret < 0)
				goto err_stop;

			/* CRC check */
			crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
			crc = ~crc32_le(crc, buf, DS4_FEATURE_REPORT_0x05_SIZE-4);
			report_crc = get_unaligned_le32(&buf[DS4_FEATURE_REPORT_0x05_SIZE-4]);
			if (crc != report_crc) {
				hid_warn(sc->hdev, "DualShock 4 calibration report's CRC check failed, received crc 0x%0x != 0x%0x\n",
					report_crc, crc);
				if (retries < 2) {
					hid_warn(sc->hdev, "Retrying DualShock 4 get calibration report request\n");
					continue;
				} else {
					ret = -EILSEQ;
					goto err_stop;
				}
			} else {
				break;
			}
		}
	}

	gyro_pitch_bias  = get_unaligned_le16(&buf[1]);
	gyro_yaw_bias    = get_unaligned_le16(&buf[3]);
	gyro_roll_bias   = get_unaligned_le16(&buf[5]);
	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		gyro_pitch_plus  = get_unaligned_le16(&buf[7]);
		gyro_pitch_minus = get_unaligned_le16(&buf[9]);
		gyro_yaw_plus    = get_unaligned_le16(&buf[11]);
		gyro_yaw_minus   = get_unaligned_le16(&buf[13]);
		gyro_roll_plus   = get_unaligned_le16(&buf[15]);
		gyro_roll_minus  = get_unaligned_le16(&buf[17]);
	} else {
		/* BT + Dongle */
		gyro_pitch_plus  = get_unaligned_le16(&buf[7]);
		gyro_yaw_plus    = get_unaligned_le16(&buf[9]);
		gyro_roll_plus   = get_unaligned_le16(&buf[11]);
		gyro_pitch_minus = get_unaligned_le16(&buf[13]);
		gyro_yaw_minus   = get_unaligned_le16(&buf[15]);
		gyro_roll_minus  = get_unaligned_le16(&buf[17]);
	}
	gyro_speed_plus  = get_unaligned_le16(&buf[19]);
	gyro_speed_minus = get_unaligned_le16(&buf[21]);
	acc_x_plus       = get_unaligned_le16(&buf[23]);
	acc_x_minus      = get_unaligned_le16(&buf[25]);
	acc_y_plus       = get_unaligned_le16(&buf[27]);
	acc_y_minus      = get_unaligned_le16(&buf[29]);
	acc_z_plus       = get_unaligned_le16(&buf[31]);
	acc_z_minus      = get_unaligned_le16(&buf[33]);

	/* Set gyroscope calibration and normalization parameters.
	 * Data values will be normalized to 1/DS4_GYRO_RES_PER_DEG_S degree/s.
	 */
	speed_2x = (gyro_speed_plus + gyro_speed_minus);
	sc->ds4_calib_data[0].abs_code = ABS_RX;
	sc->ds4_calib_data[0].bias = gyro_pitch_bias;
	sc->ds4_calib_data[0].sens_numer = speed_2x*DS4_GYRO_RES_PER_DEG_S;
	sc->ds4_calib_data[0].sens_denom = gyro_pitch_plus - gyro_pitch_minus;

	sc->ds4_calib_data[1].abs_code = ABS_RY;
	sc->ds4_calib_data[1].bias = gyro_yaw_bias;
	sc->ds4_calib_data[1].sens_numer = speed_2x*DS4_GYRO_RES_PER_DEG_S;
	sc->ds4_calib_data[1].sens_denom = gyro_yaw_plus - gyro_yaw_minus;

	sc->ds4_calib_data[2].abs_code = ABS_RZ;
	sc->ds4_calib_data[2].bias = gyro_roll_bias;
	sc->ds4_calib_data[2].sens_numer = speed_2x*DS4_GYRO_RES_PER_DEG_S;
	sc->ds4_calib_data[2].sens_denom = gyro_roll_plus - gyro_roll_minus;

	/* Set accelerometer calibration and normalization parameters.
	 * Data values will be normalized to 1/DS4_ACC_RES_PER_G G.
	 */
	range_2g = acc_x_plus - acc_x_minus;
	sc->ds4_calib_data[3].abs_code = ABS_X;
	sc->ds4_calib_data[3].bias = acc_x_plus - range_2g / 2;
	sc->ds4_calib_data[3].sens_numer = 2*DS4_ACC_RES_PER_G;
	sc->ds4_calib_data[3].sens_denom = range_2g;

	range_2g = acc_y_plus - acc_y_minus;
	sc->ds4_calib_data[4].abs_code = ABS_Y;
	sc->ds4_calib_data[4].bias = acc_y_plus - range_2g / 2;
	sc->ds4_calib_data[4].sens_numer = 2*DS4_ACC_RES_PER_G;
	sc->ds4_calib_data[4].sens_denom = range_2g;

	range_2g = acc_z_plus - acc_z_minus;
	sc->ds4_calib_data[5].abs_code = ABS_Z;
	sc->ds4_calib_data[5].bias = acc_z_plus - range_2g / 2;
	sc->ds4_calib_data[5].sens_numer = 2*DS4_ACC_RES_PER_G;
	sc->ds4_calib_data[5].sens_denom = range_2g;
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device

	return hid_hw_raw_request(hdev, 0x02, buf, sizeof(buf),
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
<<<<<<< HEAD
}

<<<<<<< HEAD
static void sixaxis_set_leds_from_id(int id, __u8 values[MAX_LEDS])
{
	static const __u8 sixaxis_leds[10][4] = {
				{ 0x01, 0x00, 0x00, 0x00 },
				{ 0x00, 0x01, 0x00, 0x00 },
				{ 0x00, 0x00, 0x01, 0x00 },
				{ 0x00, 0x00, 0x00, 0x01 },
				{ 0x01, 0x00, 0x00, 0x01 },
				{ 0x00, 0x01, 0x00, 0x01 },
				{ 0x00, 0x00, 0x01, 0x01 },
				{ 0x01, 0x00, 0x01, 0x01 },
				{ 0x00, 0x01, 0x01, 0x01 },
				{ 0x01, 0x01, 0x01, 0x01 }
	};

	BUG_ON(MAX_LEDS < ARRAY_SIZE(sixaxis_leds[0]));

	if (id < 0)
		return;

	id %= 10;
	memcpy(values, sixaxis_leds[id], sizeof(sixaxis_leds[id]));
}

static void dualshock4_set_leds_from_id(int id, __u8 values[MAX_LEDS])
{
	/* The first 4 color/index entries match what the PS4 assigns */
	static const __u8 color_code[7][3] = {
			/* Blue   */	{ 0x00, 0x00, 0x01 },
			/* Red	  */	{ 0x01, 0x00, 0x00 },
			/* Green  */	{ 0x00, 0x01, 0x00 },
			/* Pink   */	{ 0x02, 0x00, 0x01 },
			/* Orange */	{ 0x02, 0x01, 0x00 },
			/* Teal   */	{ 0x00, 0x01, 0x01 },
			/* White  */	{ 0x01, 0x01, 0x01 }
	};

	BUG_ON(MAX_LEDS < ARRAY_SIZE(color_code[0]));

	if (id < 0)
		return;

	id %= 7;
	memcpy(values, color_code[id], sizeof(color_code[id]));
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

=======
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
static void buzz_set_leds(struct hid_device *hdev, const __u8 *leds)
{
	struct list_head *report_list =
		&hdev->report_enum[HID_OUTPUT_REPORT].report_list;
	struct hid_report *report = list_entry(report_list->next,
		struct hid_report, list);
	__s32 *value = report->field[0]->value;

	value[0] = 0x00;
	value[1] = leds[0] ? 0xff : 0x00;
	value[2] = leds[1] ? 0xff : 0x00;
	value[3] = leds[2] ? 0xff : 0x00;
	value[4] = leds[3] ? 0xff : 0x00;
	value[5] = 0x00;
	value[6] = 0x00;
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
}

<<<<<<< HEAD
<<<<<<< HEAD
static void sony_set_leds(struct sony_sc *sc, const __u8 *leds, int count)
{
=======
static void sony_set_leds(struct hid_device *hdev, const __u8 *leds, int count)
{
	struct sony_sc *drv_data = hid_get_drvdata(hdev);
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
static void sony_set_leds(struct hid_device *hdev, const __u8 *leds, int count)
{
	struct sony_sc *drv_data = hid_get_drvdata(hdev);
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	int n;

	BUG_ON(count > MAX_LEDS);

<<<<<<< HEAD
<<<<<<< HEAD
	if (sc->quirks & BUZZ_CONTROLLER && count == 4) {
		buzz_set_leds(sc->hdev, leds);
	} else {
		for (n = 0; n < count; n++)
			sc->led_state[n] = leds[n];
		schedule_work(&sc->state_worker);
=======
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (drv_data->quirks & BUZZ_CONTROLLER && count == 4) {
		buzz_set_leds(hdev, leds);
	} else {
		for (n = 0; n < count; n++)
			drv_data->led_state[n] = leds[n];
		schedule_work(&drv_data->state_worker);
<<<<<<< HEAD
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	}
}

static void sony_led_set_brightness(struct led_classdev *led,
				    enum led_brightness value)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);
	struct sony_sc *drv_data;

	int n;
	int force_update;

	drv_data = hid_get_drvdata(hdev);
	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * The Sixaxis on USB will override any LED settings sent to it
	 * and keep flashing all of the LEDs until the PS button is pressed.
	 * Updates, even if redundant, must be always be sent to the
	 * controller to avoid having to toggle the state of an LED just to
	 * stop the flashing later on.
	 */
<<<<<<< HEAD
	force_update = !!(drv_data->quirks & SIXAXIS_CONTROLLER_USB);

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n] && (force_update ||
			(value != drv_data->led_state[n] ||
			drv_data->led_delay_on[n] ||
			drv_data->led_delay_off[n]))) {

			drv_data->led_state[n] = value;

			/* Setting the brightness stops the blinking */
			drv_data->led_delay_on[n] = 0;
			drv_data->led_delay_off[n] = 0;

			sony_set_leds(drv_data, drv_data->led_state,
					drv_data->led_count);
=======
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n]) {
			if (value != drv_data->led_state[n]) {
				drv_data->led_state[n] = value;
				sony_set_leds(hdev, drv_data->led_state, drv_data->led_count);
			}
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
			break;
		}
=======
	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		hid_info(hdev, "Using modified Dualshock 4 report descriptor with gyroscope axes\n");
		rdesc = dualshock4_usb_rdesc;
		*rsize = sizeof(dualshock4_usb_rdesc);
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER_BT) {
		hid_info(hdev, "Using modified Dualshock 4 Bluetooth report descriptor\n");
		rdesc = dualshock4_bt_rdesc;
		*rsize = sizeof(dualshock4_bt_rdesc);
>>>>>>> b71b5578a84d... HID: sony: Remove the size check for the Dualshock 4 HID Descriptor
	}
}

static enum led_brightness sony_led_get_brightness(struct led_classdev *led)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);
	struct sony_sc *drv_data;

	int n;

	drv_data = hid_get_drvdata(hdev);
	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return LED_OFF;
	}
=======
#define DS4_INPUT_REPORT_BUTTON_OFFSET    5
#define DS4_INPUT_REPORT_BATTERY_OFFSET  30
#define DS4_INPUT_REPORT_TOUCHPAD_OFFSET 33

#define DS4_TOUCHPAD_SUFFIX " Touchpad"

static DEFINE_SPINLOCK(sony_dev_list_lock);
static LIST_HEAD(sony_device_list);
static DEFINE_IDA(sony_device_id_allocator);

struct sony_sc {
	spinlock_t lock;
	struct list_head list_node;
	struct hid_device *hdev;
	struct input_dev *touchpad;
	struct led_classdev *leds[MAX_LEDS];
	unsigned long quirks;
	struct work_struct state_worker;
	void (*send_output_report)(struct sony_sc *);
	struct power_supply *battery;
	struct power_supply_desc battery_desc;
	int device_id;
	u8 *output_report_dmabuf;
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device

<<<<<<< HEAD
	for (n = 0; n < drv_data->led_count; n++) {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		if (led == drv_data->leds[n])
			return drv_data->led_state[n];
	}

	return LED_OFF;
=======
	u8 mac_address[6];
	u8 worker_initialized;
	u8 defer_initialization;
	u8 cable_state;
	u8 battery_charging;
	u8 battery_capacity;
	u8 led_state[MAX_LEDS];
	u8 resume_led_state[MAX_LEDS];
	u8 led_delay_on[MAX_LEDS];
	u8 led_delay_off[MAX_LEDS];
	u8 led_count;
};

static inline void sony_schedule_work(struct sony_sc *sc)
{
	if (!sc->defer_initialization)
		schedule_work(&sc->state_worker);
}

static u8 *sixaxis_fixup(struct hid_device *hdev, u8 *rdesc,
			     unsigned int *rsize)
{
	*rsize = sizeof(sixaxis_rdesc);
	return sixaxis_rdesc;
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

static int sony_led_blink_set(struct led_classdev *led, unsigned long *delay_on,
				unsigned long *delay_off)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);
	struct sony_sc *drv_data = hid_get_drvdata(hdev);
	int n;
	__u8 new_on, new_off;

<<<<<<< HEAD
	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return -EINVAL;
=======
	/*
	 * The sixaxis is charging if the battery value is 0xee
	 * and it is fully charged if the value is 0xef.
	 * It does not report the actual level while charging so it
	 * is set to 100% while charging is in progress.
	 */
	if (rd[30] >= 0xee) {
		battery_capacity = 100;
		battery_charging = !(rd[30] & 0x01);
		cable_state = 1;
	} else {
		__u8 index = rd[30] <= 5 ? rd[30] : 5;
		battery_capacity = sixaxis_battery_capacity[index];
		battery_charging = 0;
		cable_state = 0;
>>>>>>> 39520eea198a... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	}

	/* Max delay is 255 deciseconds or 2550 milliseconds */
	if (*delay_on > 2550)
		*delay_on = 2550;
	if (*delay_off > 2550)
		*delay_off = 2550;

	/* Blink at 1 Hz if both values are zero */
	if (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	new_on = *delay_on / 10;
	new_off = *delay_off / 10;

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n])
=======
		if (led == drv_data->leds[n]) {
			on = !!(drv_data->led_state[n]);
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
		if (led == drv_data->leds[n]) {
			on = !!(drv_data->led_state[n]);
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
			break;
	}

	/* This LED is not registered on this device */
	if (n >= drv_data->led_count)
		return -EINVAL;

	/* Don't schedule work if the values didn't change */
	if (new_on != drv_data->led_delay_on[n] ||
		new_off != drv_data->led_delay_off[n]) {
		drv_data->led_delay_on[n] = new_on;
		drv_data->led_delay_off[n] = new_off;
		schedule_work(&drv_data->state_worker);
	}

	return 0;
}

<<<<<<< HEAD
static void sony_leds_remove(struct sony_sc *sc)
{
	struct led_classdev *led;
	int n;

<<<<<<< HEAD
	BUG_ON(!(sc->quirks & SONY_LED_SUPPORT));
=======
	if (sc->quirks & (SINO_LITE_CONTROLLER | FUTUREMAX_DANCE_MAT))
		return rdesc;
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

<<<<<<< HEAD
	for (n = 0; n < sc->led_count; n++) {
		led = sc->leds[n];
		sc->leds[n] = NULL;
=======
	for (n = 0; n < drv_data->led_count; n++) {
		led = drv_data->leds[n];
		drv_data->leds[n] = NULL;
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
		if (!led)
			continue;
		led_classdev_unregister(led);
		kfree(led);
	}

<<<<<<< HEAD
	sc->led_count = 0;
=======
	drv_data->led_count = 0;
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
		if (led == drv_data->leds[n])
			return drv_data->led_state[n];
	}

	return LED_OFF;
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

static int sony_leds_init(struct sony_sc *sc)
{
	struct hid_device *hdev = sc->hdev;
	int n, ret = 0;
<<<<<<< HEAD
	int use_ds4_names;
=======
	int max_brightness;
<<<<<<< HEAD
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
	int use_colors;
>>>>>>> 61ebca937f26... HID: sony: Use colors for the Dualshock 4 LED names
=======
static void sony_leds_remove(struct hid_device *hdev)
{
	struct sony_sc *drv_data;
	struct led_classdev *led;
	int n;

	drv_data = hid_get_drvdata(hdev);
	BUG_ON(!(drv_data->quirks & SONY_LED_SUPPORT));

	for (n = 0; n < drv_data->led_count; n++) {
		led = drv_data->leds[n];
		drv_data->leds[n] = NULL;
		if (!led)
			continue;
		led_classdev_unregister(led);
		kfree(led);
	}

	drv_data->led_count = 0;
}

static int sony_leds_init(struct hid_device *hdev)
{
<<<<<<< HEAD
	struct sony_sc *drv_data;
	int n, ret = 0;
	int max_brightness;
	int use_colors;
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	struct led_classdev *led;
	size_t name_sz;
	char *name;
	size_t name_len;
	const char *name_fmt;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	static const char * const ds4_name_str[] = { "red", "green", "blue",
						  "global" };
	__u8 initial_values[MAX_LEDS] = { 0 };
	__u8 max_brightness[MAX_LEDS] = { [0 ... (MAX_LEDS - 1)] = 1 };
	__u8 use_hw_blink[MAX_LEDS] = { 0 };
=======
=======
	static const char * const color_str[] = { "red", "green", "blue" };
>>>>>>> 61ebca937f26... HID: sony: Use colors for the Dualshock 4 LED names
	static const __u8 initial_values[MAX_LEDS] = { 0x00, 0x00, 0x00, 0x00 };
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4

	BUG_ON(!(sc->quirks & SONY_LED_SUPPORT));

<<<<<<< HEAD
	if (sc->quirks & BUZZ_CONTROLLER) {
		sc->led_count = 4;
		use_ds4_names = 0;
=======
	if (drv_data->quirks & BUZZ_CONTROLLER) {
		drv_data->led_count = 4;
		max_brightness = 1;
		use_colors = 0;
>>>>>>> 61ebca937f26... HID: sony: Use colors for the Dualshock 4 LED names
		name_len = strlen("::buzz#");
		name_fmt = "%s::buzz%d";
		/* Validate expected report characteristics. */
		if (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 0, 0, 7))
			return -ENODEV;
<<<<<<< HEAD
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		dualshock4_set_leds_from_id(sc->device_id, initial_values);
		initial_values[3] = 1;
		sc->led_count = 4;
		memset(max_brightness, 255, 3);
		use_hw_blink[3] = 1;
		use_ds4_names = 1;
		name_len = 0;
		name_fmt = "%s:%s";
	} else {
		sixaxis_set_leds_from_id(sc->device_id, initial_values);
		sc->led_count = 4;
		memset(use_hw_blink, 1, 4);
		use_ds4_names = 0;
		name_len = strlen("::sony#");
		name_fmt = "%s::sony%d";
	}

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Clear LEDs as we have no way of reading their initial state. This is
	 * only relevant if the driver is loaded after somebody actively set the
	 * LEDs to on
	 */
<<<<<<< HEAD
	sony_set_leds(sc, initial_values, sc->led_count);
=======
	if ((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && *rsize == 467) {
=======
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
		hid_info(hdev, "Using modified Dualshock 4 report descriptor with gyroscope axes\n");
		rdesc = dualshock4_usb_rdesc;
		*rsize = sizeof(dualshock4_usb_rdesc);
	} else if ((sc->quirks & DUALSHOCK4_CONTROLLER_BT) && *rsize == 357) {
		hid_info(hdev, "Using modified Dualshock 4 Bluetooth report descriptor\n");
		rdesc = dualshock4_bt_rdesc;
		*rsize = sizeof(dualshock4_bt_rdesc);
	}
>>>>>>> d829674d29d7... HID: sony: Add modified Dualshock 4 Bluetooth HID descriptor

<<<<<<< HEAD
	name_sz = strlen(dev_name(&hdev->dev)) + name_len + 1;
=======
	struct hid_input *hidinput = list_entry(sc->hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;
=======
static void dualshock4_parse_report(struct sony_sc *sc, u8 *rd, int size)
{
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device
	unsigned long flags;
	int n, offset;
	__u8 cable_state, battery_capacity, battery_charging;

	/* Battery and touchpad data starts at byte 30 in the USB report and
	 * 32 in Bluetooth report.
	 */
	offset = (sc->quirks & DUALSHOCK4_CONTROLLER_USB) ? 30 : 32;

<<<<<<< HEAD
	/* The lower 4 bits of byte 30 contain the battery level
=======
	/* Second bit of third button byte is for the touchpad button. */
	offset = data_offset + DS4_INPUT_REPORT_BUTTON_OFFSET;
	input_report_key(sc->touchpad, BTN_LEFT, rd[offset+2] & 0x2);

	/*
	 * The lower 4 bits of byte 30 (or 32 for BT) contain the battery level
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device
	 * and the 5th bit contains the USB cable state.
	 */
	cable_state = (rd[offset] >> 4) & 0x01;
	battery_capacity = rd[offset] & 0x0F;

	/* When a USB power source is connected the battery level ranges from
	 * 0 to 10, and when running on battery power it ranges from 0 to 9.
	 * A battery level above 10 when plugged in means charge completed.
	 */
	if (!cable_state || battery_capacity > 10)
		battery_charging = 0;
	else
		battery_charging = 1;

	if (!cable_state)
		battery_capacity++;
	if (battery_capacity > 10)
		battery_capacity = 10;

	battery_capacity *= 10;
>>>>>>> 6c5f860d3f65... HID: sony: Add Dualshock 4 Bluetooth battery and touchpad parsing

	for (n = 0; n < sc->led_count; n++) {

<<<<<<< HEAD
		if (use_ds4_names)
			name_sz = strlen(dev_name(&hdev->dev)) + strlen(ds4_name_str[n]) + 2;
=======
	offset += 5;

	/* The Dualshock 4 multi-touch trackpad data starts at offset 35 on USB
	 * and 37 on Bluetooth.
	 * The first 7 bits of the first byte is a counter and bit 8 is a touch
	 * indicator that is 0 when pressed and 1 when not pressed.
	 * The next 3 bytes are two 12 bit touch coordinates, X and Y.
	 * The data for the second touch is in the same format and immediatly
	 * follows the data for the first.
	 */
	for (n = 0; n < 2; n++) {
		__u16 x, y;
>>>>>>> 6c5f860d3f65... HID: sony: Add Dualshock 4 Bluetooth battery and touchpad parsing

=======
	if (drv_data->quirks & DUALSHOCK4_CONTROLLER) {
=======
	if (drv_data->quirks & DUALSHOCK4_CONTROLLER_USB) {
>>>>>>> 8ab1676b614e... HID: sony: Use separate identifiers for USB and Bluetooth connected Dualshock 4 controllers.
=======
	} else if (drv_data->quirks & DUALSHOCK4_CONTROLLER_USB) {
>>>>>>> 61ebca937f26... HID: sony: Use colors for the Dualshock 4 LED names
=======
	static const char * const color_str[] = { "red", "green", "blue" };
	static const __u8 initial_values[MAX_LEDS] = { 0x00, 0x00, 0x00, 0x00 };

	drv_data = hid_get_drvdata(hdev);
	BUG_ON(!(drv_data->quirks & SONY_LED_SUPPORT));

	if (drv_data->quirks & BUZZ_CONTROLLER) {
		drv_data->led_count = 4;
		max_brightness = 1;
		use_colors = 0;
		name_len = strlen("::buzz#");
		name_fmt = "%s::buzz%d";
		/* Validate expected report characteristics. */
		if (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 0, 0, 7))
			return -ENODEV;
<<<<<<< HEAD
	} else if (drv_data->quirks & DUALSHOCK4_CONTROLLER_USB) {
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	} else if (drv_data->quirks & DUALSHOCK4_CONTROLLER) {
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		drv_data->led_count = 3;
		max_brightness = 255;
		use_colors = 1;
		name_len = 0;
		name_fmt = "%s:%s";
	} else {
		drv_data->led_count = 4;
		max_brightness = 1;
		use_colors = 0;
		name_len = strlen("::sony#");
		name_fmt = "%s::sony%d";
	}

	/*
	 * Clear LEDs as we have no way of reading their initial state. This is
	 * only relevant if the driver is loaded after somebody actively set the
	 * LEDs to on
	 */
	sony_set_leds(hdev, initial_values, drv_data->led_count);

	name_sz = strlen(dev_name(&hdev->dev)) + name_len + 1;
<<<<<<< HEAD

	for (n = 0; n < drv_data->led_count; n++) {
<<<<<<< HEAD
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======

		if (use_colors)
			name_sz = strlen(dev_name(&hdev->dev)) + strlen(color_str[n]) + 2;

>>>>>>> 61ebca937f26... HID: sony: Use colors for the Dualshock 4 LED names
=======

	for (n = 0; n < drv_data->led_count; n++) {

		if (use_colors)
			name_sz = strlen(dev_name(&hdev->dev)) + strlen(color_str[n]) + 2;

>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		led = kzalloc(sizeof(struct led_classdev) + name_sz, GFP_KERNEL);
		if (!led) {
			hid_err(hdev, "Couldn't allocate memory for LED %d\n", n);
			ret = -ENOMEM;
			goto error_leds;
		}

		name = (void *)(&led[1]);
<<<<<<< HEAD
<<<<<<< HEAD
		if (use_ds4_names)
			snprintf(name, name_sz, name_fmt, dev_name(&hdev->dev),
			ds4_name_str[n]);
=======
		if (use_colors)
			snprintf(name, name_sz, name_fmt, dev_name(&hdev->dev), color_str[n]);
>>>>>>> 61ebca937f26... HID: sony: Use colors for the Dualshock 4 LED names
=======
		if (use_colors)
			snprintf(name, name_sz, name_fmt, dev_name(&hdev->dev), color_str[n]);
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		else
			snprintf(name, name_sz, name_fmt, dev_name(&hdev->dev), n + 1);
		led->name = name;
<<<<<<< HEAD
		led->brightness = initial_values[n];
		led->max_brightness = max_brightness[n];
=======
		led->brightness = 0;
		led->max_brightness = max_brightness;
<<<<<<< HEAD
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
		led->brightness_get = sony_led_get_brightness;
		led->brightness_set = sony_led_set_brightness;

<<<<<<< HEAD
		if (use_hw_blink[n])
			led->blink_set = sony_led_blink_set;

		sc->leds[n] = led;

=======
		led->brightness_get = sony_led_get_brightness;
		led->brightness_set = sony_led_set_brightness;
=======
			active = !(rd[offset] >> 7);
			input_mt_slot(sc->touchpad, n);
			input_mt_report_slot_state(sc->touchpad, MT_TOOL_FINGER, active);

			if (active) {
				input_report_abs(sc->touchpad, ABS_MT_POSITION_X, x);
				input_report_abs(sc->touchpad, ABS_MT_POSITION_Y, y);
			}
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device

>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		ret = led_classdev_register(&hdev->dev, led);
		if (ret) {
			hid_err(hdev, "Failed to register LED %d\n", n);
			sc->leds[n] = NULL;
			kfree(led);
			goto error_leds;
		}
<<<<<<< HEAD
<<<<<<< HEAD
=======

		drv_data->leds[n] = led;
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
		input_mt_sync_frame(sc->touchpad);
		input_sync(sc->touchpad);
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device
	}

	return ret;

error_leds:
<<<<<<< HEAD
	sony_leds_remove(sc);
=======
	sony_leds_remove(hdev);
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

	return ret;
}

static void sixaxis_state_worker(struct work_struct *work)
<<<<<<< HEAD
{
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	int n;
	union sixaxis_output_report_01 report = {
		.buf = {
			0x01,
			0x00, 0xff, 0x00, 0xff, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0x00, 0x00, 0x00, 0x00, 0x00
		}
	};

#ifdef CONFIG_SONY_FF
<<<<<<< HEAD
	report.data.rumble.right_motor_on = sc->right ? 1 : 0;
	report.data.rumble.left_motor_force = sc->left;
=======
	buf[3] = sc->right ? 1 : 0;
	buf[5] = sc->left;
>>>>>>> 0bd88dd3dd5e... HID: sony: Add force-feedback support for the Dualshock 4
#endif

<<<<<<< HEAD
	report.data.leds_bitmap |= sc->led_state[0] << 1;
	report.data.leds_bitmap |= sc->led_state[1] << 2;
	report.data.leds_bitmap |= sc->led_state[2] << 3;
	report.data.leds_bitmap |= sc->led_state[3] << 4;

	/* Set flag for all leds off, required for 3rd party INTEC controller */
	if ((report.data.leds_bitmap & 0x1E) == 0)
		report.data.leds_bitmap |= 0x20;
=======
	buf[10] |= sc->led_state[0] << 1;
	buf[10] |= sc->led_state[1] << 2;
	buf[10] |= sc->led_state[2] << 3;
	buf[10] |= sc->led_state[3] << 4;
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4

	/*
	 * The LEDs in the report are indexed in reverse order to their
	 * corresponding light on the controller.
	 * Index 0 = LED 4, index 1 = LED 3, etc...
	 *
	 * In the case of both delay values being zero (blinking disabled) the
	 * default report values should be used or the controller LED will be
	 * always off.
	 */
	for (n = 0; n < 4; n++) {
		if (sc->led_delay_on[n] || sc->led_delay_off[n]) {
			report.data.led[3 - n].duty_off = sc->led_delay_off[n];
			report.data.led[3 - n].duty_on = sc->led_delay_on[n];
		}
	}

<<<<<<< HEAD
	hid_hw_raw_request(sc->hdev, report.data.report_id, report.buf,
			sizeof(report), HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
}

static void dualshock4_state_worker(struct work_struct *work)
{
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	struct hid_device *hdev = sc->hdev;
	int offset;

<<<<<<< HEAD
	__u8 buf[78] = { 0 };

	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
=======
	/*
	 * NOTE: The buf[1] field of the Bluetooth report controls
	 * the Dualshock 4 reporting rate.
	 *
	 * Known values include:
	 *
	 * 0x80 - 1000hz (full speed)
	 * 0xA0 - 31hz
	 * 0xB0 - 20hz
	 * 0xD0 - 66hz
	 */
	if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) {
		memset(buf, 0, DS4_OUTPUT_REPORT_0x05_SIZE);
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device
		buf[0] = 0x05;
		buf[1] = 0xFF;
		offset = 4;
	} else {
		buf[0] = 0x11;
		buf[1] = 0xB0;
		buf[3] = 0x0F;
		offset = 6;
=======
		sixaxis_parse_report(sc, rd, size);
	} else if (((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) || ((sc->quirks & DUALSHOCK4_CONTROLLER_BT)
			&& rd[0] == 0x11 && size == 78)) {
		dualshock4_parse_report(sc, rd, size);
>>>>>>> 68330d83c0b3... HID: sony: Add conditionals to enable all features in Bluetooth mode
	}

<<<<<<< HEAD
#ifdef CONFIG_SONY_FF
	buf[offset++] = sc->right;
	buf[offset++] = sc->left;
#else
	offset += 2;
#endif

<<<<<<< HEAD
	/* LED 3 is the global control */
	if (sc->led_state[3]) {
		buf[offset++] = sc->led_state[0];
		buf[offset++] = sc->led_state[1];
		buf[offset++] = sc->led_state[2];
	} else {
		offset += 3;
	}

	/* If both delay values are zero the DualShock 4 disables blinking. */
	buf[offset++] = sc->led_delay_on[3];
	buf[offset++] = sc->led_delay_off[3];

<<<<<<< HEAD
	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB)
		hid_hw_output_report(hdev, buf, 32);
	else
		hid_hw_raw_request(hdev, 0x11, buf, 78,
				HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
=======
	buf[6] = sc->led_state[0];
	buf[7] = sc->led_state[1];
	buf[8] = sc->led_state[2];

	sc->hdev->hid_output_raw_report(sc->hdev, buf, sizeof(buf),
					HID_OUTPUT_REPORT);
>>>>>>> 60781cf487e3... HID: sony: Add LED controls for the Dualshock 4
=======
	if (sc->defer_initialization) {
		sc->defer_initialization = 0;
		sony_schedule_work(sc);
=======
	if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE))
		hid_hw_output_report(hdev, buf, DS4_OUTPUT_REPORT_0x05_SIZE);
	else {
		/* CRC generation */
		u8 bthdr = 0xA2;
		u32 crc;

		crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
		crc = ~crc32_le(crc, buf, DS4_OUTPUT_REPORT_0x11_SIZE-4);
		put_unaligned_le32(crc, &buf[74]);
		hid_hw_output_report(hdev, buf, DS4_OUTPUT_REPORT_0x11_SIZE);
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device
	}

	return 0;
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

static void dualshock4_state_worker(struct work_struct *work)
{
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	struct hid_device *hdev = sc->hdev;
	struct hid_report *report = sc->output_report;
	__s32 *value = report->field[0]->value;

	value[0] = 0x03;

#ifdef CONFIG_SONY_FF
	value[3] = sc->right;
	value[4] = sc->left;
#endif
=======
{
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	unsigned char buf[] = {
		0x01,
		0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0x00, 0x00, 0x00, 0x00, 0x00
	};

#ifdef CONFIG_SONY_FF
	buf[3] = sc->right ? 1 : 0;
	buf[5] = sc->left;
#endif

	buf[10] |= sc->led_state[0] << 1;
	buf[10] |= sc->led_state[1] << 2;
	buf[10] |= sc->led_state[2] << 3;
	buf[10] |= sc->led_state[3] << 4;
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

<<<<<<< HEAD
	sc->hdev->hid_output_raw_report(sc->hdev, buf, sizeof(buf),
					HID_OUTPUT_REPORT);
=======
	value[5] = sc->led_state[0];
	value[6] = sc->led_state[1];
	value[7] = sc->led_state[2];

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
>>>>>>> 0da8ea6581d5... HID: sony: Use standard output reports instead of raw reports to send data to the Dualshock 4.
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
static void dualshock4_state_worker(struct work_struct *work)
=======
static int sony_register_touchpad(struct hid_input *hi, int touch_count,
=======
static int sony_register_touchpad(struct sony_sc *sc, int touch_count,
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device
					int w, int h)
{
	size_t name_sz;
	char *name;
	int ret;

	sc->touchpad = input_allocate_device();
	if (!sc->touchpad)
		return -ENOMEM;

	input_set_drvdata(sc->touchpad, sc);
	sc->touchpad->dev.parent = &sc->hdev->dev;
	sc->touchpad->phys = sc->hdev->phys;
	sc->touchpad->uniq = sc->hdev->uniq;
	sc->touchpad->id.bustype = sc->hdev->bus;
	sc->touchpad->id.vendor = sc->hdev->vendor;
	sc->touchpad->id.product = sc->hdev->product;
	sc->touchpad->id.version = sc->hdev->version;

	/* Append a suffix to the controller name as there are various
	 * DS4 compatible non-Sony devices with different names.
	 */
	name_sz = strlen(sc->hdev->name) + sizeof(DS4_TOUCHPAD_SUFFIX);
	name = kzalloc(name_sz, GFP_KERNEL);
	if (!name) {
		ret = -ENOMEM;
		goto err;
	}
	snprintf(name, name_sz, "%s" DS4_TOUCHPAD_SUFFIX, sc->hdev->name);
	sc->touchpad->name = name;

	ret = input_mt_init_slots(sc->touchpad, touch_count, 0);
	if (ret < 0)
		goto err;

	/* We map the button underneath the touchpad to BTN_LEFT. */
	__set_bit(EV_KEY, sc->touchpad->evbit);
	__set_bit(BTN_LEFT, sc->touchpad->keybit);
	__set_bit(INPUT_PROP_BUTTONPAD, sc->touchpad->propbit);

	input_set_abs_params(sc->touchpad, ABS_MT_POSITION_X, 0, w, 0, 0);
	input_set_abs_params(sc->touchpad, ABS_MT_POSITION_Y, 0, h, 0, 0);

	ret = input_register_device(sc->touchpad);
	if (ret < 0)
		goto err;

	return 0;

err:
	kfree(sc->touchpad->name);
	sc->touchpad->name = NULL;

	input_free_device(sc->touchpad);
	sc->touchpad = NULL;

	return ret;
}

<<<<<<< HEAD
static void sony_input_configured(struct hid_device *hdev,
					struct hid_input *hidinput)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);

	/*
	 * The Dualshock 4 touchpad supports 2 touches and has a
	 * resolution of 1920x942 (44.86 dots/mm).
	 */
	if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		if (sony_register_touchpad(hidinput, 2, 1920, 942) != 0)
			hid_err(sc->hdev,
				"Unable to initialize multi-touch slots\n");
	}
=======
static void sony_unregister_touchpad(struct sony_sc *sc)
{
	if (!sc->touchpad)
		return;

	kfree(sc->touchpad->name);
	sc->touchpad->name = NULL;

	input_unregister_device(sc->touchpad);
	sc->touchpad = NULL;
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device
}

/*
 * Sending HID_REQ_GET_REPORT changes the operation mode of the ps3 controller
 * to "operational".  Without this, the ps3 controller will not report any
 * events.
 */
static int sixaxis_set_operational_usb(struct hid_device *hdev)
>>>>>>> 39520eea198a... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
{
<<<<<<< HEAD
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	struct hid_device *hdev = sc->hdev;
	struct hid_report *report = sc->output_report;
	__s32 *value = report->field[0]->value;
=======
	if ((sc->quirks & SIXAXIS_CONTROLLER) ||
			(sc->quirks & NAVIGATION_CONTROLLER))
		sc->output_report_dmabuf =
			kmalloc(sizeof(union sixaxis_output_report_01),
				GFP_KERNEL);
	else if (sc->quirks & DUALSHOCK4_CONTROLLER_BT)
		sc->output_report_dmabuf = kmalloc(DS4_OUTPUT_REPORT_0x11_SIZE,
						GFP_KERNEL);
	else if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE))
		sc->output_report_dmabuf = kmalloc(DS4_OUTPUT_REPORT_0x05_SIZE,
						GFP_KERNEL);
	else if (sc->quirks & MOTION_CONTROLLER)
		sc->output_report_dmabuf = kmalloc(MOTION_REPORT_0x02_SIZE,
						GFP_KERNEL);
	else
		return 0;
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device

	value[0] = 0x03;

#ifdef CONFIG_SONY_FF
	value[3] = sc->right;
	value[4] = sc->left;
#endif

	value[5] = sc->led_state[0];
	value[6] = sc->led_state[1];
	value[7] = sc->led_state[2];

<<<<<<< HEAD
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
=======
	/*
	 * The Dualshock 4 touchpad supports 2 touches and has a
	 * resolution of 1920x942 (44.86 dots/mm).
	 */
	if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		if (sony_register_touchpad(hidinput, 2, 1920, 942) != 0)
			hid_err(sc->hdev,
				"Unable to initialize multi-touch slots\n");
	}
>>>>>>> 981c5b4a3b37... HID: sony: Update the DualShock 4 touchpad resolution
}

>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
#ifdef CONFIG_SONY_FF
static int sony_play_effect(struct input_dev *dev, void *data,
			    struct ff_effect *effect)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct sony_sc *sc = hid_get_drvdata(hid);

	if (effect->type != FF_RUMBLE)
		return 0;

	sc->left = effect->u.rumble.strong_magnitude / 256;
	sc->right = effect->u.rumble.weak_magnitude / 256;

	schedule_work(&sc->state_worker);
	return 0;
}

static int sony_init_ff(struct sony_sc *sc)
{
	struct hid_input *hidinput = list_entry(sc->hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;

	input_set_capability(input_dev, EV_FF, FF_RUMBLE);
	return input_ff_create_memless(input_dev, NULL, sony_play_effect);
}

<<<<<<< HEAD
#else
static int sony_init_ff(struct sony_sc *sc)
=======
/* Requesting feature report 0x02 in Bluetooth mode changes the state of the
 * controller so that it sends full input reports of type 0x11.
 */
static int dualshock4_set_operational_bt(struct hid_device *hdev)
{
	__u8 buf[37] = { 0 };

	return hid_hw_raw_request(hdev, 0x02, buf, sizeof(buf),
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
}

static void sixaxis_set_leds_from_id(int id, __u8 values[MAX_LEDS])
<<<<<<< HEAD
=======
{
	static const __u8 sixaxis_leds[10][4] = {
				{ 0x01, 0x00, 0x00, 0x00 },
				{ 0x00, 0x01, 0x00, 0x00 },
				{ 0x00, 0x00, 0x01, 0x00 },
				{ 0x00, 0x00, 0x00, 0x01 },
				{ 0x01, 0x00, 0x00, 0x01 },
				{ 0x00, 0x01, 0x00, 0x01 },
				{ 0x00, 0x00, 0x01, 0x01 },
				{ 0x01, 0x00, 0x01, 0x01 },
				{ 0x00, 0x01, 0x01, 0x01 },
				{ 0x01, 0x01, 0x01, 0x01 }
	};

	BUG_ON(MAX_LEDS < ARRAY_SIZE(sixaxis_leds[0]));

	if (id < 0)
		return;

	id %= 10;
	memcpy(values, sixaxis_leds[id], sizeof(sixaxis_leds[id]));
}

static void dualshock4_set_leds_from_id(int id, __u8 values[MAX_LEDS])
{
	/* The first 4 color/index entries match what the PS4 assigns */
	static const __u8 color_code[7][3] = {
			/* Blue   */	{ 0x00, 0x00, 0x01 },
			/* Red	  */	{ 0x01, 0x00, 0x00 },
			/* Green  */	{ 0x00, 0x01, 0x00 },
			/* Pink   */	{ 0x02, 0x00, 0x01 },
			/* Orange */	{ 0x02, 0x01, 0x00 },
			/* Teal   */	{ 0x00, 0x01, 0x01 },
			/* White  */	{ 0x01, 0x01, 0x01 }
	};

	BUG_ON(MAX_LEDS < ARRAY_SIZE(color_code[0]));

	if (id < 0)
		return;

	id %= 7;
	memcpy(values, color_code[id], sizeof(color_code[id]));
}

static void buzz_set_leds(struct hid_device *hdev, const __u8 *leds)
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
{
	static const __u8 sixaxis_leds[10][4] = {
				{ 0x01, 0x00, 0x00, 0x00 },
				{ 0x00, 0x01, 0x00, 0x00 },
				{ 0x00, 0x00, 0x01, 0x00 },
				{ 0x00, 0x00, 0x00, 0x01 },
				{ 0x01, 0x00, 0x00, 0x01 },
				{ 0x00, 0x01, 0x00, 0x01 },
				{ 0x00, 0x00, 0x01, 0x01 },
				{ 0x01, 0x00, 0x01, 0x01 },
				{ 0x00, 0x01, 0x01, 0x01 },
				{ 0x01, 0x01, 0x01, 0x01 }
	};

	BUG_ON(MAX_LEDS < ARRAY_SIZE(sixaxis_leds[0]));

	if (id < 0)
		return;

	id %= 10;
	memcpy(values, sixaxis_leds[id], sizeof(sixaxis_leds[id]));
}

<<<<<<< HEAD
static void dualshock4_set_leds_from_id(int id, __u8 values[MAX_LEDS])
{
	/* The first 4 color/index entries match what the PS4 assigns */
	static const __u8 color_code[7][3] = {
			/* Blue   */	{ 0x00, 0x00, 0x01 },
			/* Red	  */	{ 0x01, 0x00, 0x00 },
			/* Green  */	{ 0x00, 0x01, 0x00 },
			/* Pink   */	{ 0x02, 0x00, 0x01 },
			/* Orange */	{ 0x02, 0x01, 0x00 },
			/* Teal   */	{ 0x00, 0x01, 0x01 },
			/* White  */	{ 0x01, 0x01, 0x01 }
	};
=======
static void sony_set_leds(struct sony_sc *sc, const __u8 *leds, int count)
{
	int n;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

	BUG_ON(MAX_LEDS < ARRAY_SIZE(color_code[0]));

	if (id < 0)
		return;

	id %= 7;
	memcpy(values, color_code[id], sizeof(color_code[id]));
}

static void buzz_set_leds(struct hid_device *hdev, const __u8 *leds)
>>>>>>> 68330d83c0b3... HID: sony: Add conditionals to enable all features in Bluetooth mode
{
	return 0;
}

#endif

static int sony_battery_get_property(struct power_supply *psy,
				     enum power_supply_property psp,
				     union power_supply_propval *val)
{
<<<<<<< HEAD
	struct sony_sc *sc = container_of(psy, struct sony_sc, battery);
	unsigned long flags;
	int ret = 0;
	u8 battery_charging, battery_capacity, cable_state;

	spin_lock_irqsave(&sc->lock, flags);
	battery_charging = sc->battery_charging;
	battery_capacity = sc->battery_capacity;
	cable_state = sc->cable_state;
	spin_unlock_irqrestore(&sc->lock, flags);

<<<<<<< HEAD
<<<<<<< HEAD
	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_SCOPE:
		val->intval = POWER_SUPPLY_SCOPE_DEVICE;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = battery_capacity;
		break;
	case POWER_SUPPLY_PROP_STATUS:
		if (battery_charging)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			if (battery_capacity == 100 && cable_state)
				val->intval = POWER_SUPPLY_STATUS_FULL;
			else
				val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	default:
		ret = -EINVAL;
		break;
=======
	if (drv_data->quirks & BUZZ_CONTROLLER && count == 4) {
		buzz_set_leds(hdev, leds);
	} else if ((drv_data->quirks & SIXAXIS_CONTROLLER_USB) ||
		   (drv_data->quirks & DUALSHOCK4_CONTROLLER)) {
		for (n = 0; n < count; n++)
			drv_data->led_state[n] = leds[n];
		schedule_work(&drv_data->state_worker);
>>>>>>> 68330d83c0b3... HID: sony: Add conditionals to enable all features in Bluetooth mode
=======
	if (sc->quirks & BUZZ_CONTROLLER && count == 4) {
		buzz_set_leds(sc->hdev, leds);
	} else {
		for (n = 0; n < count; n++)
			sc->led_state[n] = leds[n];
		schedule_work(&sc->state_worker);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	}
	return ret;
=======
	if (!(sc->quirks & BUZZ_CONTROLLER))
		sony_schedule_work(sc);
	else
		buzz_set_leds(sc);
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

static int sony_battery_probe(struct sony_sc *sc)
{
	struct hid_device *hdev = sc->hdev;
	int ret;

<<<<<<< HEAD
	/*
	 * Set the default battery level to 100% to avoid low battery warnings
	 * if the battery is polled before the first device report is received.
	 */
	sc->battery_capacity = 100;
=======
	int n;
	int force_update;
<<<<<<< HEAD
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

	sc->battery.properties = sony_battery_props;
	sc->battery.num_properties = ARRAY_SIZE(sony_battery_props);
	sc->battery.get_property = sony_battery_get_property;
	sc->battery.type = POWER_SUPPLY_TYPE_BATTERY;
	sc->battery.use_for_apm = 0;
	sc->battery.name = kasprintf(GFP_KERNEL, "sony_controller_battery_%pMR",
				     sc->mac_address);
	if (!sc->battery.name)
		return -ENOMEM;

<<<<<<< HEAD
	ret = power_supply_register(&hdev->dev, &sc->battery);
	if (ret) {
		hid_err(hdev, "Unable to register battery device\n");
		goto err_free;
=======
	/*
	 * The Sixaxis on USB will override any LED settings sent to it
	 * and keep flashing all of the LEDs until the PS button is pressed.
	 * Updates, even if redundant, must be always be sent to the
	 * controller to avoid having to toggle the state of an LED just to
	 * stop the flashing later on.
	 */
	force_update = !!(drv_data->quirks & SIXAXIS_CONTROLLER_USB);

	/*
	 * The Sixaxis on USB will override any LED settings sent to it
	 * and keep flashing all of the LEDs until the PS button is pressed.
	 * Updates, even if redundant, must be always be sent to the
	 * controller to avoid having to toggle the state of an LED just to
	 * stop the flashing later on.
	 */
	force_update = !!(drv_data->quirks & SIXAXIS_CONTROLLER_USB);

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n] && (force_update ||
			(value != drv_data->led_state[n] ||
			drv_data->led_delay_on[n] ||
			drv_data->led_delay_off[n]))) {

			drv_data->led_state[n] = value;

			/* Setting the brightness stops the blinking */
			drv_data->led_delay_on[n] = 0;
			drv_data->led_delay_off[n] = 0;

			sony_set_leds(drv_data, drv_data->led_state,
					drv_data->led_count);
			break;
		}
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
	}

	power_supply_powers(&sc->battery, &hdev->dev);
	return 0;

err_free:
	kfree(sc->battery.name);
	sc->battery.name = NULL;
	return ret;
}

static void sony_battery_remove(struct sony_sc *sc)
{
	if (!sc->battery.name)
		return;

	power_supply_unregister(&sc->battery);
	kfree(sc->battery.name);
	sc->battery.name = NULL;
}

<<<<<<< HEAD
/*
 * If a controller is plugged in via USB while already connected via Bluetooth
 * it will show up as two devices. A global list of connected controllers and
 * their MAC addresses is maintained to ensure that a device is only connected
 * once.
 */
static int sony_check_add_dev_list(struct sony_sc *sc)
=======
static int sony_led_blink_set(struct led_classdev *led, unsigned long *delay_on,
				unsigned long *delay_off)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);
	struct sony_sc *drv_data = hid_get_drvdata(hdev);
	int n;
	__u8 new_on, new_off;

	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return -EINVAL;
	}

	/* Max delay is 255 deciseconds or 2550 milliseconds */
	if (*delay_on > 2550)
		*delay_on = 2550;
	if (*delay_off > 2550)
		*delay_off = 2550;

	/* Blink at 1 Hz if both values are zero */
	if (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	new_on = *delay_on / 10;
	new_off = *delay_off / 10;

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n])
			break;
	}

	/* This LED is not registered on this device */
	if (n >= drv_data->led_count)
		return -EINVAL;

	/* Don't schedule work if the values didn't change */
	if (new_on != drv_data->led_delay_on[n] ||
		new_off != drv_data->led_delay_off[n]) {
		drv_data->led_delay_on[n] = new_on;
		drv_data->led_delay_off[n] = new_off;
		schedule_work(&drv_data->state_worker);
	}

	return 0;
}

<<<<<<< HEAD
static void sony_leds_remove(struct sony_sc *sc)
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
{
	struct sony_sc *entry;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&sony_dev_list_lock, flags);

	list_for_each_entry(entry, &sony_device_list, list_node) {
		ret = memcmp(sc->mac_address, entry->mac_address,
				sizeof(sc->mac_address));
		if (!ret) {
			ret = -EEXIST;
			hid_info(sc->hdev, "controller with MAC address %pMR already connected\n",
				sc->mac_address);
			goto unlock;
		}
	}

	ret = 0;
	list_add(&(sc->list_node), &sony_device_list);

unlock:
	spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	return ret;
}

static void sony_remove_dev_list(struct sony_sc *sc)
{
<<<<<<< HEAD
	unsigned long flags;
=======
=======
static int sony_led_blink_set(struct led_classdev *led, unsigned long *delay_on,
				unsigned long *delay_off)
{
	struct device *dev = led->dev->parent;
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);
	struct sony_sc *drv_data = hid_get_drvdata(hdev);
	int n;
	__u8 new_on, new_off;

	if (!drv_data) {
		hid_err(hdev, "No device data\n");
		return -EINVAL;
	}

	/* Max delay is 255 deciseconds or 2550 milliseconds */
	if (*delay_on > 2550)
		*delay_on = 2550;
	if (*delay_off > 2550)
		*delay_off = 2550;

	/* Blink at 1 Hz if both values are zero */
	if (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	new_on = *delay_on / 10;
	new_off = *delay_off / 10;

	for (n = 0; n < drv_data->led_count; n++) {
		if (led == drv_data->leds[n])
			break;
	}

	/* This LED is not registered on this device */
	if (n >= drv_data->led_count)
		return -EINVAL;

	/* Don't schedule work if the values didn't change */
	if (new_on != drv_data->led_delay_on[n] ||
		new_off != drv_data->led_delay_off[n]) {
		drv_data->led_delay_on[n] = new_on;
		drv_data->led_delay_off[n] = new_off;
		sony_schedule_work(drv_data);
	}

	return 0;
}

static void sony_leds_remove(struct sony_sc *sc)
{
	struct led_classdev *led;
	int n;

	BUG_ON(!(sc->quirks & SONY_LED_SUPPORT));

	for (n = 0; n < sc->led_count; n++) {
		led = sc->leds[n];
		sc->leds[n] = NULL;
		if (!led)
			continue;
		led_classdev_unregister(led);
		kfree(led);
	}

	sc->led_count = 0;
}

static int sony_leds_init(struct sony_sc *sc)
{
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	struct hid_device *hdev = sc->hdev;
	int n, ret = 0;
	int use_ds4_names;
	struct led_classdev *led;
	size_t name_sz;
	char *name;
	size_t name_len;
	const char *name_fmt;
	static const char * const ds4_name_str[] = { "red", "green", "blue",
						  "global" };
	__u8 initial_values[MAX_LEDS] = { 0 };
	__u8 max_brightness[MAX_LEDS] = { [0 ... (MAX_LEDS - 1)] = 1 };
	__u8 use_hw_blink[MAX_LEDS] = { 0 };

	BUG_ON(!(sc->quirks & SONY_LED_SUPPORT));
<<<<<<< HEAD
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value

<<<<<<< HEAD
<<<<<<< HEAD
	if (sc->list_node.next) {
		spin_lock_irqsave(&sony_dev_list_lock, flags);
		list_del(&(sc->list_node));
		spin_unlock_irqrestore(&sony_dev_list_lock, flags);
=======
	if (drv_data->quirks & BUZZ_CONTROLLER) {
		drv_data->led_count = 4;
		max_brightness = 1;
		use_colors = 0;
=======
	if (sc->quirks & BUZZ_CONTROLLER) {
		sc->led_count = 4;
		use_ds4_names = 0;
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======

	if (sc->quirks & BUZZ_CONTROLLER) {
		sc->led_count = 4;
		use_ds4_names = 0;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
		name_len = strlen("::buzz#");
		name_fmt = "%s::buzz%d";
		/* Validate expected report characteristics. */
		if (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 0, 0, 7))
			return -ENODEV;
<<<<<<< HEAD
<<<<<<< HEAD
	} else if (drv_data->quirks & DUALSHOCK4_CONTROLLER) {
		drv_data->led_count = 3;
=======
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		dualshock4_set_leds_from_id(sc->device_id, initial_values);
<<<<<<< HEAD
		sc->led_count = 3;
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
		max_brightness = 255;
		use_colors = 1;
=======
=======
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		dualshock4_set_leds_from_id(sc->device_id, initial_values);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
		initial_values[3] = 1;
		sc->led_count = 4;
		memset(max_brightness, 255, 3);
		use_hw_blink[3] = 1;
		use_ds4_names = 1;
<<<<<<< HEAD
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
		name_len = 0;
		name_fmt = "%s:%s";
	} else {
<<<<<<< HEAD
		drv_data->led_count = 4;
=======
		sixaxis_set_leds_from_id(sc->device_id, initial_values);
		sc->led_count = 4;
<<<<<<< HEAD
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
		max_brightness = 1;
		use_colors = 0;
=======
		memset(use_hw_blink, 1, 4);
		use_ds4_names = 0;
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
		name_len = 0;
		name_fmt = "%s:%s";
	} else {
		sixaxis_set_leds_from_id(sc->device_id, initial_values);
		sc->led_count = 4;
		memset(use_hw_blink, 1, 4);
		use_ds4_names = 0;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
		name_len = strlen("::sony#");
		name_fmt = "%s::sony%d";
>>>>>>> 68330d83c0b3... HID: sony: Add conditionals to enable all features in Bluetooth mode
	}
}

<<<<<<< HEAD
static int sony_get_bt_devaddr(struct sony_sc *sc)
{
	int ret;
=======
	/*
	 * Clear LEDs as we have no way of reading their initial state. This is
	 * only relevant if the driver is loaded after somebody actively set the
	 * LEDs to on
	 */
	sony_set_leds(sc, initial_values, sc->led_count);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

	/* HIDP stores the device MAC address as a string in the uniq field. */
	ret = strlen(sc->hdev->uniq);
	if (ret != 17)
		return -EINVAL;

<<<<<<< HEAD
	ret = sscanf(sc->hdev->uniq,
		"%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		&sc->mac_address[5], &sc->mac_address[4], &sc->mac_address[3],
		&sc->mac_address[2], &sc->mac_address[1], &sc->mac_address[0]);

	if (ret != 6)
		return -EINVAL;
=======
	for (n = 0; n < sc->led_count; n++) {

		if (use_ds4_names)
			name_sz = strlen(dev_name(&hdev->dev)) + strlen(ds4_name_str[n]) + 2;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

<<<<<<< HEAD
	return 0;
}
=======
		if (use_ds4_names)
			name_sz = strlen(dev_name(&hdev->dev)) + strlen(ds4_name_str[n]) + 2;
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs

static int sony_check_add(struct sony_sc *sc)
{
	int n, ret;

	if ((sc->quirks & DUALSHOCK4_CONTROLLER_BT) ||
	    (sc->quirks & SIXAXIS_CONTROLLER_BT)) {
		/*
		 * sony_get_bt_devaddr() attempts to parse the Bluetooth MAC
		 * address from the uniq string where HIDP stores it.
		 * As uniq cannot be guaranteed to be a MAC address in all cases
		 * a failure of this function should not prevent the connection.
		 */
		if (sony_get_bt_devaddr(sc) < 0) {
			hid_warn(sc->hdev, "UNIQ does not contain a MAC address; duplicate check skipped\n");
			return 0;
		}
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		__u8 buf[7];

<<<<<<< HEAD
		/*
		 * The MAC address of a DS4 controller connected via USB can be
		 * retrieved with feature report 0x81. The address begins at
		 * offset 1.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0x81, buf, sizeof(buf),
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);

		if (ret != 7) {
			hid_err(sc->hdev, "failed to retrieve feature report 0x81 with the DualShock 4 MAC address\n");
			return ret < 0 ? ret : -EINVAL;
		}

		memcpy(sc->mac_address, &buf[1], sizeof(sc->mac_address));
	} else if (sc->quirks & SIXAXIS_CONTROLLER_USB) {
		__u8 buf[18];
=======
		name = (void *)(&led[1]);
		if (use_ds4_names)
			snprintf(name, name_sz, name_fmt, dev_name(&hdev->dev),
			ds4_name_str[n]);
		else
			snprintf(name, name_sz, name_fmt, dev_name(&hdev->dev), n + 1);
		led->name = name;
		led->brightness = initial_values[n];
		led->max_brightness = max_brightness[n];
		led->brightness_get = sony_led_get_brightness;
		led->brightness_set = sony_led_set_brightness;

		if (use_hw_blink[n])
			led->blink_set = sony_led_blink_set;

		sc->leds[n] = led;

		ret = led_classdev_register(&hdev->dev, led);
		if (ret) {
			hid_err(hdev, "Failed to register LED %d\n", n);
			sc->leds[n] = NULL;
			kfree(led);
			goto error_leds;
		}
	}
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value

		/*
		 * The MAC address of a Sixaxis controller connected via USB can
		 * be retrieved with feature report 0xf2. The address begins at
		 * offset 4.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0xf2, buf, sizeof(buf),
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);

<<<<<<< HEAD
		if (ret != 18) {
			hid_err(sc->hdev, "failed to retrieve feature report 0xf2 with the Sixaxis MAC address\n");
			return ret < 0 ? ret : -EINVAL;
		}
=======
error_leds:
	sony_leds_remove(sc);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

		/*
		 * The Sixaxis device MAC in the report is big-endian and must
		 * be byte-swapped.
		 */
		for (n = 0; n < 6; n++)
			sc->mac_address[5-n] = buf[4+n];
	} else {
		return 0;
	}

	return sony_check_add_dev_list(sc);
}

static int sony_set_device_id(struct sony_sc *sc)
{
<<<<<<< HEAD
	int ret;
=======
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	int n;
	union sixaxis_output_report_01 report = {
		.buf = {
			0x01,
			0x00, 0xff, 0x00, 0xff, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0x00, 0x00, 0x00, 0x00, 0x00
		}
	};

#ifdef CONFIG_SONY_FF
	report.data.rumble.right_motor_on = sc->right ? 1 : 0;
	report.data.rumble.left_motor_force = sc->left;
#endif
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Only DualShock 4 or Sixaxis controllers get an id.
	 * All others are set to -1.
	 */
	if ((sc->quirks & SIXAXIS_CONTROLLER) ||
	    (sc->quirks & DUALSHOCK4_CONTROLLER)) {
		ret = ida_simple_get(&sony_device_id_allocator, 0, 0,
					GFP_KERNEL);
		if (ret < 0) {
			sc->device_id = -1;
			return ret;
		}
		sc->device_id = ret;
	} else {
		sc->device_id = -1;
	}

<<<<<<< HEAD
	return 0;
=======
	hid_hw_raw_request(sc->hdev, 0x01, buf, sizeof(buf), HID_OUTPUT_REPORT,
			HID_REQ_SET_REPORT);
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
=======
	report.data.leds_bitmap |= sc->led_state[0] << 1;
	report.data.leds_bitmap |= sc->led_state[1] << 2;
	report.data.leds_bitmap |= sc->led_state[2] << 3;
	report.data.leds_bitmap |= sc->led_state[3] << 4;

	/* Set flag for all leds off, required for 3rd party INTEC controller */
	if ((report.data.leds_bitmap & 0x1E) == 0)
		report.data.leds_bitmap |= 0x20;

>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	/*
	 * The LEDs in the report are indexed in reverse order to their
	 * corresponding light on the controller.
	 * Index 0 = LED 4, index 1 = LED 3, etc...
	 *
	 * In the case of both delay values being zero (blinking disabled) the
	 * default report values should be used or the controller LED will be
	 * always off.
	 */
	for (n = 0; n < 4; n++) {
		if (sc->led_delay_on[n] || sc->led_delay_off[n]) {
			report.data.led[3 - n].duty_off = sc->led_delay_off[n];
			report.data.led[3 - n].duty_on = sc->led_delay_on[n];
		}
	}

	hid_hw_raw_request(sc->hdev, report.data.report_id, report.buf,
			sizeof(report), HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
<<<<<<< HEAD
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
}

static void sony_release_device_id(struct sony_sc *sc)
{
<<<<<<< HEAD
	if (sc->device_id >= 0) {
		ida_simple_remove(&sony_device_id_allocator, sc->device_id);
		sc->device_id = -1;
	}
}
=======
	struct sony_sc *sc = container_of(work, struct sony_sc, state_worker);
	struct hid_device *hdev = sc->hdev;
	int offset;

<<<<<<< HEAD
<<<<<<< HEAD
	__u8 buf[78] = { 0 };
<<<<<<< HEAD

	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		buf[0] = 0x05;
		buf[1] = 0xFF;
		offset = 4;
	} else {
		buf[0] = 0x11;
		buf[1] = 0xB0;
		buf[3] = 0x0F;
		offset = 6;
	}
>>>>>>> fdcf105d3d96... HID: sony: Add Dualshock 4 Bluetooth output report formatting

static inline void sony_init_work(struct sony_sc *sc,
					void (*worker)(struct work_struct *))
{
	if (!sc->worker_initialized)
		INIT_WORK(&sc->state_worker, worker);

	sc->worker_initialized = 1;
}

<<<<<<< HEAD
static inline void sony_cancel_work_sync(struct sony_sc *sc)
{
	if (sc->worker_initialized)
		cancel_work_sync(&sc->state_worker);
=======
=======

=======
=======
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	/*
	 * NOTE: The buf[1] field of the Bluetooth report controls
	 * the Dualshock 4 reporting rate.
	 *
	 * Known values include:
	 *
	 * 0x80 - 1000hz (full speed)
	 * 0xA0 - 31hz
	 * 0xB0 - 20hz
	 * 0xD0 - 66hz
	 */
<<<<<<< HEAD
>>>>>>> c4425c8f26aa... HID: sony: Update copyright and add Dualshock 4 rate control note
=======
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		buf[0] = 0x05;
		buf[1] = 0xFF;
		offset = 4;
	} else {
		buf[0] = 0x11;
		buf[1] = 0x80;
		buf[3] = 0x0F;
		offset = 6;
	}

#ifdef CONFIG_SONY_FF
	buf[offset++] = sc->right;
	buf[offset++] = sc->left;
#else
	offset += 2;
#endif

<<<<<<< HEAD
<<<<<<< HEAD
	buf[offset++] = sc->led_state[0];
	buf[offset++] = sc->led_state[1];
	buf[offset++] = sc->led_state[2];
=======
	/* LED 3 is the global control */
	if (sc->led_state[3]) {
		buf[offset++] = sc->led_state[0];
		buf[offset++] = sc->led_state[1];
		buf[offset++] = sc->led_state[2];
	} else {
		offset += 3;
	}

	/* If both delay values are zero the DualShock 4 disables blinking. */
	buf[offset++] = sc->led_delay_on[3];
	buf[offset++] = sc->led_delay_off[3];
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	/* LED 3 is the global control */
	if (sc->led_state[3]) {
		buf[offset++] = sc->led_state[0];
		buf[offset++] = sc->led_state[1];
		buf[offset++] = sc->led_state[2];
	} else {
		offset += 3;
	}

	/* If both delay values are zero the DualShock 4 disables blinking. */
	buf[offset++] = sc->led_delay_on[3];
	buf[offset++] = sc->led_delay_off[3];

>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
	if (sc->quirks & DUALSHOCK4_CONTROLLER_USB)
		hid_hw_output_report(hdev, buf, 32);
	else
		hid_hw_raw_request(hdev, 0x11, buf, 78,
				HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> fdcf105d3d96... HID: sony: Add Dualshock 4 Bluetooth output report formatting
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
}

#ifdef CONFIG_SONY_FF
static int sony_play_effect(struct input_dev *dev, void *data,
			    struct ff_effect *effect)
{
	unsigned char buf[] = {
		0x01,
		0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x03,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0xff, 0x27, 0x10, 0x00, 0x32,
		0x00, 0x00, 0x00, 0x00, 0x00
	};
	__u8 left;
	__u8 right;
	struct hid_device *hid = input_get_drvdata(dev);

	if (effect->type != FF_RUMBLE)
		return 0;

	left = effect->u.rumble.strong_magnitude / 256;
	right = effect->u.rumble.weak_magnitude ? 1 : 0;

	buf[3] = right;
	buf[5] = left;

	return hid->hid_output_raw_report(hid, buf, sizeof(buf),
					  HID_OUTPUT_REPORT);
}

static int sony_init_ff(struct hid_device *hdev)
{
	struct hid_input *hidinput = list_entry(hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;

	input_set_capability(input_dev, EV_FF, FF_RUMBLE);
	return input_ff_create_memless(input_dev, NULL, sony_play_effect);
<<<<<<< HEAD
=======
	cancel_work_sync(&sc->state_worker);
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
}

#else
static int sony_init_ff(struct hid_device *hdev)
{
	return 0;
}

#endif

<<<<<<< HEAD
<<<<<<< HEAD
static int sony_set_output_report(struct sony_sc *sc, int req_id, int req_size)
{
	struct list_head *head, *list;
	struct hid_report *report;
	struct hid_device *hdev = sc->hdev;

	list = &hdev->report_enum[HID_OUTPUT_REPORT].report_list;

	list_for_each(head, list) {
		report = list_entry(head, struct hid_report, list);

		if (report->id == req_id) {
			if (report->size < req_size) {
				hid_err(hdev, "Output report 0x%02x (%i bits) is smaller than requested size (%i bits)\n",
					req_id, report->size, req_size);
				return -EINVAL;
			}
			sc->output_report = report;
			return 0;
		}
	}

	hid_err(hdev, "Unable to locate output report 0x%02x\n", req_id);

	return -EINVAL;
}
=======
#endif
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues

static int sony_battery_get_property(struct power_supply *psy,
				     enum power_supply_property psp,
				     union power_supply_propval *val)
{
	struct sony_sc *sc = container_of(psy, struct sony_sc, battery);
	unsigned long flags;
	int ret = 0;
	u8 battery_charging, battery_capacity, cable_state;

	spin_lock_irqsave(&sc->lock, flags);
	battery_charging = sc->battery_charging;
	battery_capacity = sc->battery_capacity;
	cable_state = sc->cable_state;
	spin_unlock_irqrestore(&sc->lock, flags);

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_SCOPE:
		val->intval = POWER_SUPPLY_SCOPE_DEVICE;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = battery_capacity;
		break;
	case POWER_SUPPLY_PROP_STATUS:
		if (battery_charging)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			if (battery_capacity == 100 && cable_state)
				val->intval = POWER_SUPPLY_STATUS_FULL;
			else
				val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
=======
>>>>>>> b3ed458c1c24... HID: sony: Add blink support to the Sixaxis and DualShock 4 LEDs
}

static int sony_battery_probe(struct sony_sc *sc)
{
	static atomic_t power_id_seq = ATOMIC_INIT(0);
	unsigned long power_id;
	struct hid_device *hdev = sc->hdev;
	int ret;

	power_id = (unsigned long)atomic_inc_return(&power_id_seq);

	sc->battery.properties = sony_battery_props;
	sc->battery.num_properties = ARRAY_SIZE(sony_battery_props);
	sc->battery.get_property = sony_battery_get_property;
	sc->battery.type = POWER_SUPPLY_TYPE_BATTERY;
	sc->battery.use_for_apm = 0;
	sc->battery.name = kasprintf(GFP_KERNEL, "sony_controller_battery_%lu",
				     power_id);
	if (!sc->battery.name)
		return -ENOMEM;

	ret = power_supply_register(&hdev->dev, &sc->battery);
	if (ret) {
		hid_err(hdev, "Unable to register battery device\n");
		goto err_free;
	}

<<<<<<< HEAD
	power_supply_powers(&sc->battery, &hdev->dev);
=======
	sony_schedule_work(sc);
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	return 0;
<<<<<<< HEAD
=======
}

static int sony_init_ff(struct sony_sc *sc)
{
	struct hid_input *hidinput = list_entry(sc->hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

err_free:
	kfree(sc->battery.name);
	sc->battery.name = NULL;
	return ret;
}

<<<<<<< HEAD
static void sony_battery_remove(struct sony_sc *sc)
=======
#else
static int sony_init_ff(struct sony_sc *sc)
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
{
	if (!sc->battery.name)
		return;

	power_supply_unregister(&sc->battery);
	kfree(sc->battery.name);
	sc->battery.name = NULL;
}

static int sony_set_output_report(struct sony_sc *sc, int req_id, int req_size)
=======
static int sony_battery_get_property(struct power_supply *psy,
				     enum power_supply_property psp,
				     union power_supply_propval *val)
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
{
	struct sony_sc *sc = container_of(psy, struct sony_sc, battery);
	unsigned long flags;
	int ret = 0;
	u8 battery_charging, battery_capacity, cable_state;

	spin_lock_irqsave(&sc->lock, flags);
	battery_charging = sc->battery_charging;
	battery_capacity = sc->battery_capacity;
	cable_state = sc->cable_state;
	spin_unlock_irqrestore(&sc->lock, flags);

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_SCOPE:
		val->intval = POWER_SUPPLY_SCOPE_DEVICE;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = battery_capacity;
		break;
	case POWER_SUPPLY_PROP_STATUS:
		if (battery_charging)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			if (battery_capacity == 100 && cable_state)
				val->intval = POWER_SUPPLY_STATUS_FULL;
			else
				val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

static int sony_battery_probe(struct sony_sc *sc, int append_dev_id)
{
<<<<<<< HEAD
=======
	const char *battery_str_fmt = append_dev_id ?
		"sony_controller_battery_%pMR_%i" :
		"sony_controller_battery_%pMR";
	struct power_supply_config psy_cfg = { .drv_data = sc, };
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	struct hid_device *hdev = sc->hdev;
	int ret;

	/*
	 * Set the default battery level to 100% to avoid low battery warnings
	 * if the battery is polled before the first device report is received.
	 */
	sc->battery_capacity = 100;

<<<<<<< HEAD
	sc->battery.properties = sony_battery_props;
	sc->battery.num_properties = ARRAY_SIZE(sony_battery_props);
	sc->battery.get_property = sony_battery_get_property;
	sc->battery.type = POWER_SUPPLY_TYPE_BATTERY;
	sc->battery.use_for_apm = 0;
	sc->battery.name = kasprintf(GFP_KERNEL, "sony_controller_battery_%pMR",
				     sc->mac_address);
	if (!sc->battery.name)
=======
	sc->battery_desc.properties = sony_battery_props;
	sc->battery_desc.num_properties = ARRAY_SIZE(sony_battery_props);
	sc->battery_desc.get_property = sony_battery_get_property;
	sc->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	sc->battery_desc.use_for_apm = 0;
	sc->battery_desc.name = kasprintf(GFP_KERNEL, battery_str_fmt,
					  sc->mac_address, sc->device_id);
	if (!sc->battery_desc.name)
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		return -ENOMEM;

	ret = power_supply_register(&hdev->dev, &sc->battery);
	if (ret) {
		hid_err(hdev, "Unable to register battery device\n");
		goto err_free;
	}

	power_supply_powers(&sc->battery, &hdev->dev);
	return 0;

err_free:
	kfree(sc->battery.name);
	sc->battery.name = NULL;
	return ret;
}

static void sony_battery_remove(struct sony_sc *sc)
{
	if (!sc->battery.name)
		return;

	power_supply_unregister(&sc->battery);
	kfree(sc->battery.name);
	sc->battery.name = NULL;
}

/*
 * If a controller is plugged in via USB while already connected via Bluetooth
 * it will show up as two devices. A global list of connected controllers and
 * their MAC addresses is maintained to ensure that a device is only connected
 * once.
 */
static int sony_check_add_dev_list(struct sony_sc *sc)
{
	struct sony_sc *entry;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&sony_dev_list_lock, flags);

	list_for_each_entry(entry, &sony_device_list, list_node) {
		ret = memcmp(sc->mac_address, entry->mac_address,
				sizeof(sc->mac_address));
		if (!ret) {
			ret = -EEXIST;
			hid_info(sc->hdev, "controller with MAC address %pMR already connected\n",
				sc->mac_address);
			goto unlock;
		}
	}

	ret = 0;
	list_add(&(sc->list_node), &sony_device_list);

unlock:
	spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	return ret;
}

static void sony_remove_dev_list(struct sony_sc *sc)
{
	unsigned long flags;

	if (sc->list_node.next) {
		spin_lock_irqsave(&sony_dev_list_lock, flags);
		list_del(&(sc->list_node));
		spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	}
}

<<<<<<< HEAD
static int sony_register_touchpad(struct sony_sc *sc, int touch_count,
					int w, int h)
{
	struct hid_input *hidinput = list_entry(sc->hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;
	int ret;

	ret = input_mt_init_slots(input_dev, touch_count, 0);
	if (ret < 0) {
		hid_err(sc->hdev, "Unable to initialize multi-touch slots\n");
		return ret;
	}

	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0, w, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0, h, 0, 0);

	return 0;
}

/*
 * If a controller is plugged in via USB while already connected via Bluetooth
 * it will show up as two devices. A global list of connected controllers and
 * their MAC addresses is maintained to ensure that a device is only connected
 * once.
 *
 * Some USB-only devices masquerade as Sixaxis controllers and all have the
 * same dummy Bluetooth address, so a comparison of the connection type is
 * required.  Devices are only rejected in the case where two devices have
 * matching Bluetooth addresses on different bus types.
 */
static inline int sony_compare_connection_type(struct sony_sc *sc0,
						struct sony_sc *sc1)
{
	const int sc0_not_bt = !(sc0->quirks & SONY_BT_DEVICE);
	const int sc1_not_bt = !(sc1->quirks & SONY_BT_DEVICE);

	return sc0_not_bt == sc1_not_bt;
}

static int sony_check_add_dev_list(struct sony_sc *sc)
{
	struct sony_sc *entry;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&sony_dev_list_lock, flags);

	list_for_each_entry(entry, &sony_device_list, list_node) {
		ret = memcmp(sc->mac_address, entry->mac_address,
				sizeof(sc->mac_address));
		if (!ret) {
			if (sony_compare_connection_type(sc, entry)) {
				ret = 1;
			} else {
				ret = -EEXIST;
				hid_info(sc->hdev,
				"controller with MAC address %pMR already connected\n",
				sc->mac_address);
			}
			goto unlock;
		}
	}

	ret = 0;
	list_add(&(sc->list_node), &sony_device_list);

unlock:
	spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	return ret;
}

static void sony_remove_dev_list(struct sony_sc *sc)
{
	unsigned long flags;

	if (sc->list_node.next) {
		spin_lock_irqsave(&sony_dev_list_lock, flags);
		list_del(&(sc->list_node));
		spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	}
}

=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
static int sony_get_bt_devaddr(struct sony_sc *sc)
{
	int ret;

	/* HIDP stores the device MAC address as a string in the uniq field. */
	ret = strlen(sc->hdev->uniq);
	if (ret != 17)
		return -EINVAL;

	ret = sscanf(sc->hdev->uniq,
		"%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		&sc->mac_address[5], &sc->mac_address[4], &sc->mac_address[3],
		&sc->mac_address[2], &sc->mac_address[1], &sc->mac_address[0]);

	if (ret != 6)
		return -EINVAL;

	return 0;
}

static int sony_check_add(struct sony_sc *sc)
{
	int n, ret;

	if ((sc->quirks & DUALSHOCK4_CONTROLLER_BT) ||
	    (sc->quirks & SIXAXIS_CONTROLLER_BT)) {
		/*
		 * sony_get_bt_devaddr() attempts to parse the Bluetooth MAC
		 * address from the uniq string where HIDP stores it.
		 * As uniq cannot be guaranteed to be a MAC address in all cases
		 * a failure of this function should not prevent the connection.
		 */
		if (sony_get_bt_devaddr(sc) < 0) {
			hid_warn(sc->hdev, "UNIQ does not contain a MAC address; duplicate check skipped\n");
			return 0;
		}
<<<<<<< HEAD
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		__u8 buf[7];
=======
	} else if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) {
		buf = kmalloc(DS4_FEATURE_REPORT_0x81_SIZE, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device

		/*
		 * The MAC address of a DS4 controller connected via USB can be
		 * retrieved with feature report 0x81. The address begins at
		 * offset 1.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0x81, buf, sizeof(buf),
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);

		if (ret != 7) {
			hid_err(sc->hdev, "failed to retrieve feature report 0x81 with the DualShock 4 MAC address\n");
			return ret < 0 ? ret : -EINVAL;
		}

		memcpy(sc->mac_address, &buf[1], sizeof(sc->mac_address));
	} else if (sc->quirks & SIXAXIS_CONTROLLER_USB) {
		__u8 buf[18];

		/*
		 * The MAC address of a Sixaxis controller connected via USB can
		 * be retrieved with feature report 0xf2. The address begins at
		 * offset 4.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0xf2, buf, sizeof(buf),
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);

		if (ret != 18) {
			hid_err(sc->hdev, "failed to retrieve feature report 0xf2 with the Sixaxis MAC address\n");
			return ret < 0 ? ret : -EINVAL;
		}

		/*
		 * The Sixaxis device MAC in the report is big-endian and must
		 * be byte-swapped.
		 */
		for (n = 0; n < 6; n++)
			sc->mac_address[5-n] = buf[4+n];
	} else {
		return 0;
	}

	return sony_check_add_dev_list(sc);
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
static int sony_set_device_id(struct sony_sc *sc)
{
	int ret;

	/*
	 * Only DualShock 4 or Sixaxis controllers get an id.
	 * All others are set to -1.
	 */
	if ((sc->quirks & SIXAXIS_CONTROLLER) ||
	    (sc->quirks & DUALSHOCK4_CONTROLLER)) {
		ret = ida_simple_get(&sony_device_id_allocator, 0, 0,
					GFP_KERNEL);
		if (ret < 0) {
			sc->device_id = -1;
			return ret;
		}
		sc->device_id = ret;
	} else {
		sc->device_id = -1;
	}

	return 0;
}

static void sony_release_device_id(struct sony_sc *sc)
{
	if (sc->device_id >= 0) {
		ida_simple_remove(&sony_device_id_allocator, sc->device_id);
		sc->device_id = -1;
	}
}

static inline void sony_init_work(struct sony_sc *sc,
					void (*worker)(struct work_struct *))
{
	if (!sc->worker_initialized)
		INIT_WORK(&sc->state_worker, worker);

	sc->worker_initialized = 1;
}

static inline void sony_cancel_work_sync(struct sony_sc *sc)
{
	if (sc->worker_initialized)
		cancel_work_sync(&sc->state_worker);
}
<<<<<<< HEAD
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

static int sony_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	int append_dev_id;
	unsigned long quirks = id->driver_data;
	struct sony_sc *sc;
	unsigned int connect_mask = HID_CONNECT_DEFAULT;

	if (!strcmp(hdev->name, "FutureMax Dance Mat"))
		quirks |= FUTUREMAX_DANCE_MAT;

	sc = devm_kzalloc(&hdev->dev, sizeof(*sc), GFP_KERNEL);
	if (sc == NULL) {
		hid_err(hdev, "can't alloc sony descriptor\n");
		return -ENOMEM;
	}

	sc->quirks = quirks;
	hid_set_drvdata(hdev, sc);
	sc->hdev = hdev;

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		return ret;
	}

	if (sc->quirks & VAIO_RDESC_CONSTANT)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;
	else if (sc->quirks & SIXAXIS_CONTROLLER)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;

	ret = hid_hw_start(hdev, connect_mask);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		return ret;
	}

	ret = sony_set_device_id(sc);
	if (ret < 0) {
		hid_err(hdev, "failed to allocate the device id\n");
		goto err_stop;
	}

	if (sc->quirks & SIXAXIS_CONTROLLER_USB) {
		/*
		 * The Sony Sixaxis does not handle HID Output Reports on the
		 * Interrupt EP like it could, so we need to force HID Output
		 * Reports to use HID_REQ_SET_REPORT on the Control EP.
		 *
		 * There is also another issue about HID Output Reports via USB,
		 * the Sixaxis does not want the report_id as part of the data
		 * packet, so we have to discard buf[0] when sending the actual
		 * control message, even for numbered reports, humpf!
		 *
		 * Additionally, the Sixaxis on USB isn't properly initialized
		 * until the PS logo button is pressed and as such won't retain
		 * any state set by an output report, so the initial
		 * configuration report is deferred until the first input
		 * report arrives.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
		hdev->quirks |= HID_QUIRK_SKIP_OUTPUT_REPORT_ID;
		sc->defer_initialization = 1;
		ret = sixaxis_set_operational_usb(hdev);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		sony_init_work(sc, sixaxis_state_worker);
=======
		sc->worker_initialized = 1;
		INIT_WORK(&sc->state_worker, sixaxis_state_worker);
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
	} else if (sc->quirks & SIXAXIS_CONTROLLER_BT) {
		/*
		 * The Sixaxis wants output reports sent on the ctrl endpoint
		 * when connected via Bluetooth.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
		ret = sixaxis_set_operational_bt(hdev);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		sony_init_work(sc, sixaxis_state_worker);
=======
		sc->worker_initialized = 1;
		INIT_WORK(&sc->state_worker, sixaxis_state_worker);
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		if (sc->quirks & DUALSHOCK4_CONTROLLER_BT) {
			/*
			 * The DualShock 4 wants output reports sent on the ctrl
			 * endpoint when connected via Bluetooth.
			 */
			hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
			ret = dualshock4_set_operational_bt(hdev);
			if (ret < 0) {
				hid_err(hdev, "failed to set the Dualshock 4 operational mode\n");
				goto err_stop;
			}
		}

		sony_init_work(sc, dualshock4_state_worker);
	} else {
		ret = 0;
=======
	else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
=======
	else if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
<<<<<<< HEAD
>>>>>>> 8ab1676b614e... HID: sony: Use separate identifiers for USB and Bluetooth connected Dualshock 4 controllers.
		ret = 0;
=======
		/* Report 5 (31 bytes) is used to send data to the controller via USB */
		ret = sony_set_output_report(sc, 0x05, 248);
		if (ret < 0)
			goto err_stop;

>>>>>>> c4e1ddf2680b... HID: sony: Cache the output report for the Dualshock 4
		INIT_WORK(&sc->state_worker, dualshock4_state_worker);
	} else {
		ret = 0;
>>>>>>> 0bd88dd3dd5e... HID: sony: Add force-feedback support for the Dualshock 4
=======
		INIT_WORK(&sc->state_worker, sixaxis_state_worker);
	}
	else if (sc->quirks & SIXAXIS_CONTROLLER_BT)
		ret = sixaxis_set_operational_bt(hdev);
<<<<<<< HEAD
	else if (sc->quirks & DUALSHOCK4_CONTROLLER_USB) {
		/* Report 5 (31 bytes) is used to send data to the controller via USB */
		ret = sony_set_output_report(sc, 0x05, 248);
=======
		sc->worker_initialized = 1;
		INIT_WORK(&sc->state_worker, sixaxis_state_worker);
=======
		sony_init_work(sc, sixaxis_state_worker);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	} else if (sc->quirks & SIXAXIS_CONTROLLER_BT) {
		/*
		 * The Sixaxis wants output reports sent on the ctrl endpoint
		 * when connected via Bluetooth.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
		ret = sixaxis_set_operational_bt(hdev);
		sony_init_work(sc, sixaxis_state_worker);
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		if (sc->quirks & DUALSHOCK4_CONTROLLER_BT) {
			/*
			 * The DualShock 4 wants output reports sent on the ctrl
			 * endpoint when connected via Bluetooth.
			 */
			hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
			ret = dualshock4_set_operational_bt(hdev);
			if (ret < 0) {
				hid_err(hdev, "failed to set the Dualshock 4 operational mode\n");
				goto err_stop;
			}
		}
<<<<<<< HEAD
		/*
		 * The Dualshock 4 touchpad supports 2 touches and has a
		 * resolution of 1920x940.
		 */
<<<<<<< HEAD
		ret = sony_register_touchpad(sc, 2, 1920, 940);
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
		if (ret < 0)
			goto err_stop;

=======
	else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		if (sc->quirks & DUALSHOCK4_CONTROLLER_BT) {
			ret = dualshock4_set_operational_bt(hdev);
			if (ret < 0) {
				hid_err(hdev, "failed to set the Dualshock 4 operational mode\n");
				goto err_stop;
			}
=======
		ret = sony_register_touchpad(sc, 2, 1920, 942);
		if (ret) {
			hid_err(sc->hdev,
			"Unable to initialize multi-touch slots: %d\n",
			ret);
			return ret;
>>>>>>> 42027eecaedf... UPSTREAM: HID: sony: Make the DS4 touchpad a separate device
		}
>>>>>>> 68330d83c0b3... HID: sony: Add conditionals to enable all features in Bluetooth mode
		/* The Dualshock 4 touchpad supports 2 touches and has a
		 * resolution of 1920x940.
		 */
		ret = sony_register_touchpad(sc, 2, 1920, 940);
		if (ret < 0)
			goto err_stop;
=======
>>>>>>> 39520eea198a... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

		sony_init_work(sc, dualshock4_state_worker);
	} else {
		ret = 0;
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	}

	if (ret < 0)
		goto err_stop;

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	ret = sony_check_add(sc);
=======
	ret = append_dev_id = sony_check_add(sc);
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (ret < 0)
		goto err_stop;

<<<<<<< HEAD
<<<<<<< HEAD
	if (sc->quirks & SONY_LED_SUPPORT) {
		ret = sony_leds_init(sc);
		if (ret < 0)
			goto err_stop;
	}

	if (sc->quirks & SONY_BATTERY_SUPPORT) {
		ret = sony_battery_probe(sc);
		if (ret < 0)
			goto err_stop;

		/* Open the device to receive reports with battery info */
		ret = hid_hw_open(hdev);
		if (ret < 0) {
			hid_err(hdev, "hw open failed\n");
			goto err_stop;
		}
	}

	if (sc->quirks & SONY_FF_SUPPORT) {
		ret = sony_init_ff(sc);
		if (ret < 0)
			goto err_close;
	}

=======
=======
=======
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (sc->quirks & SONY_LED_SUPPORT) {
		ret = sony_leds_init(sc);
		if (ret < 0)
			goto err_stop;
	}

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (sc->quirks & SONY_BATTERY_SUPPORT) {
		ret = sony_battery_probe(sc, append_dev_id);
		if (ret < 0)
			goto err_stop;

		/* Open the device to receive reports with battery info */
		ret = hid_hw_open(hdev);
		if (ret < 0) {
			hid_err(hdev, "hw open failed\n");
			goto err_stop;
		}
	}

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
	ret = sony_init_ff(hdev);
	if (ret < 0)
		goto err_close;
=======
=======
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	if (sc->quirks & SONY_FF_SUPPORT) {
		ret = sony_init_ff(sc);
		if (ret < 0)
			goto err_close;
	}
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues

>>>>>>> a08c22c0df0a... HID: sony: Add force feedback support for Dualshock3 USB
	return 0;
err_close:
	hid_hw_close(hdev);
err_stop:
	if (sc->quirks & SONY_LED_SUPPORT)
<<<<<<< HEAD
<<<<<<< HEAD
		sony_leds_remove(sc);
	if (sc->quirks & SONY_BATTERY_SUPPORT)
		sony_battery_remove(sc);
	sony_cancel_work_sync(sc);
	sony_remove_dev_list(sc);
	sony_release_device_id(sc);
<<<<<<< HEAD
=======
		sony_leds_remove(hdev);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	if (sc->quirks & SONY_BATTERY_SUPPORT)
		sony_battery_remove(sc);
<<<<<<< HEAD
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
	if (sc->worker_initialized)
		cancel_work_sync(&sc->state_worker);
<<<<<<< HEAD
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
	sony_remove_dev_list(sc);
>>>>>>> d2d782fccee4... HID: sony: Prevent duplicate controller connections.
=======
=======
		sony_leds_remove(sc);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	if (sc->quirks & SONY_BATTERY_SUPPORT)
		sony_battery_remove(sc);
	sony_cancel_work_sync(sc);
	sony_remove_dev_list(sc);
<<<<<<< HEAD
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
>>>>>>> 8025087acf9d... HID: sony: Initialize the controller LEDs with a device ID value
=======
	sony_release_device_id(sc);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next
	hid_hw_stop(hdev);
	return ret;
}

static void sony_remove(struct hid_device *hdev)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);

	hid_hw_close(hdev);

	if (sc->quirks & SONY_LED_SUPPORT)
<<<<<<< HEAD
<<<<<<< HEAD
		sony_leds_remove(sc);

	if (sc->quirks & SONY_BATTERY_SUPPORT)
		sony_battery_remove(sc);

	if (sc->touchpad)
		sony_unregister_touchpad(sc);

	sony_cancel_work_sync(sc);

	sony_remove_dev_list(sc);
=======
		sony_leds_remove(hdev);
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

<<<<<<< HEAD
	sony_release_device_id(sc);
=======
	if (sc->quirks & SONY_BATTERY_SUPPORT) {
		hid_hw_close(hdev);
		sony_battery_remove(sc);
	}
=======
		sony_leds_remove(sc);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

<<<<<<< HEAD
	sony_destroy_ff(hdev);
>>>>>>> d902f4724ccd... HID: sony: add battery status reporting for the Sixaxis and Dualshock 4
=======
	if (sc->worker_initialized)
		cancel_work_sync(&sc->state_worker);
<<<<<<< HEAD
>>>>>>> c8de9dbb35d3... HID: sony: Fix work queue issues
=======
	if (sc->quirks & SONY_BATTERY_SUPPORT) {
		hid_hw_close(hdev);
		sony_battery_remove(sc);
	}

<<<<<<< HEAD
	if (sc->worker_initialized)
		cancel_work_sync(&sc->state_worker);
>>>>>>> 0f1b1e6d73cb... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
	sony_cancel_work_sync(sc);
>>>>>>> d6b92c2c373e... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid into next

<<<<<<< HEAD
	sony_remove_dev_list(sc);
=======
		/*
		 * The Sixaxis and navigation controllers on USB need to be
		 * reinitialized on resume or they won't behave properly.
		 */
		if ((sc->quirks & SIXAXIS_CONTROLLER_USB) ||
			(sc->quirks & NAVIGATION_CONTROLLER_USB)) {
			sixaxis_set_operational_usb(sc->hdev);
			sc->defer_initialization = 1;
		}
>>>>>>> bc75450cc3db... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid

	sony_release_device_id(sc);

	hid_hw_stop(hdev);
}

static const struct hid_device_id sony_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_USB },
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_NAVIGATION_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_USB },
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_BT },
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_VAIO_VGX_MOUSE),
		.driver_data = VAIO_RDESC_CONSTANT },
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_VAIO_VGP_MOUSE),
		.driver_data = VAIO_RDESC_CONSTANT },
	/* Wired Buzz Controller. Reported as Sony Hub from its USB ID and as
	 * Logitech joystick from the device descriptor. */
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_BUZZ_CONTROLLER),
		.driver_data = BUZZ_CONTROLLER },
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_WIRELESS_BUZZ_CONTROLLER),
		.driver_data = BUZZ_CONTROLLER },
	/* PS3 BD Remote Control */
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_BDREMOTE),
		.driver_data = PS3REMOTE },
	/* Logitech Harmony Adapter for PS3 */
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_HARMONY_PS3),
		.driver_data = PS3REMOTE },
<<<<<<< HEAD
<<<<<<< HEAD
	/* SMK-Link PS3 BD Remote Control */
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SMK, USB_DEVICE_ID_SMK_PS3_BDREMOTE),
		.driver_data = PS3REMOTE },
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
	/* Sony Dualshock 4 controllers for PS4 */
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
		.driver_data = DUALSHOCK4_CONTROLLER_USB },
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
		.driver_data = DUALSHOCK4_CONTROLLER_BT },
<<<<<<< HEAD
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_2),
		.driver_data = DUALSHOCK4_CONTROLLER_USB },
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_2),
		.driver_data = DUALSHOCK4_CONTROLLER_BT },
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_DONGLE),
<<<<<<< HEAD
		.driver_data = DUALSHOCK4_CONTROLLER_USB },
=======
	/* Sony Dualshock 4 controllers for PS4 */
	{ HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
		.driver_data = DUALSHOCK4_CONTROLLER_USB },
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
<<<<<<< HEAD
		.driver_data = DUALSHOCK4_CONTROLLER },
>>>>>>> 0bd88dd3dd5e... HID: sony: Add force-feedback support for the Dualshock 4
=======
		.driver_data = DUALSHOCK4_CONTROLLER_BT },
>>>>>>> 8ab1676b614e... HID: sony: Use separate identifiers for USB and Bluetooth connected Dualshock 4 controllers.
=======
>>>>>>> 4988abf17492... Merge branch 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/jikos/hid
=======
		.driver_data = DUALSHOCK4_DONGLE },
	/* Nyko Core Controller for PS3 */
	{ HID_USB_DEVICE(USB_VENDOR_ID_SINO_LITE, USB_DEVICE_ID_SINO_LITE_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_USB | SINO_LITE_CONTROLLER },
>>>>>>> 8f1d47009e8e... UPSTREAM: HID: sony: Treat the ds4 dongle as a separate device
	{ }
};
MODULE_DEVICE_TABLE(hid, sony_devices);

static struct hid_driver sony_driver = {
	.name             = "sony",
	.id_table         = sony_devices,
	.input_mapping    = sony_mapping,
	.input_configured = sony_input_configured,
	.probe            = sony_probe,
	.remove           = sony_remove,
	.report_fixup     = sony_report_fixup,
	.raw_event        = sony_raw_event
};

static int __init sony_init(void)
{
	dbg_hid("Sony:%s\n", __func__);

	return hid_register_driver(&sony_driver);
}

static void __exit sony_exit(void)
{
	dbg_hid("Sony:%s\n", __func__);

	ida_destroy(&sony_device_id_allocator);
	hid_unregister_driver(&sony_driver);
}
module_init(sony_init);
module_exit(sony_exit);

MODULE_LICENSE("GPL");
