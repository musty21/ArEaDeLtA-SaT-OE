require conf/machine/include/bmips.inc
require conf/machine/include/build-extras.inc

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "os-dvb-modules-${MACHINE}"
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "rt8723bs"
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "kernel-module-hci-uart"
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "kernel-module-rt2800usb"

MACHINE_EXTRA_RRECOMMENDS += "enigma2-plugin-drivers-dvb-usb-opticombo"
MACHINE_EXTRA_RRECOMMENDS += "${@bb.utils.contains("GST_VERSION", "1.0", "gstreamer1.0-plugin-dvbmediasink", "gst-plugin-dvbmediasink", d)}"
MACHINE_EXTRA_RRECOMMENDS += "edision-splash"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3"

PREFERRED_PROVIDER_virtual/kernel = "linux-os"

KERNEL_IMAGETYPE = "vmlinux.gz"
KERNEL_CONSOLE = "ttyS0,115200n8"

KERNEL_MODULE_AUTOLOAD += "r8723bs"
KERNEL_MODULE_AUTOLOAD += "hci_uart"

MACHINE_FEATURES += "alsa wlan 3dtv switchoff osdposition hdmicec textlcd dvb-c videoenhancement"

require conf/machine/include/autoload-filesystems.inc
require conf/machine/include/rootfs-ubi.inc
