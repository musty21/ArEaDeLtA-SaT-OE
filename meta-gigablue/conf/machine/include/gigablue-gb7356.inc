SOC_FAMILY = "bcm7356"

require gigablue-mips.inc

MACHINE_FEATURES += "gigabluelcd blindscan-dvbc transcoding ci gigabluemipsbootvideo osdanimation blindscan-dvbs YUV RCA"

### Logitech keyboard ###
KERNEL_MODULE_AUTOLOAD += "hid-logitech"
KERNEL_MODULE_AUTOLOAD += "hid-logitech-dj"

DVBSKYPROVIDER = "kernel"

PREFERRED_VERSION_linux-gigablue = "4.8.3"

IMAGE_FSTYPES ?= "ubi"
UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096 -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    gigablue-dvb-modules-gb7356 \
"

DVBMEDIASINK_CONFIG = "--with-wmv --with-wma --with-pcm --with-dts --with-eac3 --with-amr"

GLIBC_EXTRA_OECONF = "--with-tls --with-__thread"
