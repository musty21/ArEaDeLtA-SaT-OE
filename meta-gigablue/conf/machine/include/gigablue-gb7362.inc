SOC_FAMILY = "bcm7362"

require gigablue-mips.inc

MACHINE_FEATURES += "gbsoftwol osdanimation blindscan-dvbs middleflash"

# Broken bootloader can only flash around 100 MB
FLASHSIZE = "96"

### Logitech keyboard ###
KERNEL_MODULE_AUTOLOAD += "hid-logitech"
KERNEL_MODULE_AUTOLOAD += "hid-logitech-dj"

DVBSKYPROVIDER = "kernel"

PREFERRED_VERSION_linux-gigablue = "4.8.3"

IMAGE_FSTYPES ?= "ubi"
UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    gigablue-dvb-modules-gb7362 \
"

DVBMEDIASINK_CONFIG = "--with-wmv --with-wma --with-pcm --with-dts --with-eac3 --with-amr"

GLIBC_EXTRA_OECONF = "--with-tls --with-__thread"
