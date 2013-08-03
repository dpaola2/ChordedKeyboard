#!/bin/sh

sudo dfu-programmer at90usb82 erase && sudo dfu-programmer at90usb82 flash --debug 1 --suppress-bootloader-mem UNO-dfu_and_usbserial_combined.hex && sudo dfu-programmer at90usb82 reset
