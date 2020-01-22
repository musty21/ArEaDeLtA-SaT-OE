include conf/machine/include/autoload-filesystems.inc
# We know about rtc
include conf/machine/include/build-extras.inc

MTD_KERNEL = "mmcblk0p12"
MTD_ROOTFS = "mmcblk0p13"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    octagon-dvb-modules-${MACHINE} \
    octagon-loadmodules-${MACHINE} \ 
    octagon-opengl-${MACHINE} \
    octagon-libs-${MACHINE} \
    octagon-hihalt-${MACHINE} \
    octagon-reader-${MACHINE} \
    octagon-libreader-${MACHINE} \
    ${@bb.utils.contains("MACHINE_FEATURES", "blindscan", "octagon-blindscan-${MACHINE}" , "", d)} \    
    octagon-partitions-${MACHINE} \
    octagon-buildimage \
    e2fsprogs-resize2fs \
    gptfdisk \
"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
	kernel-module-cdfs \
	firmware-carl9170 \
	firmware-htc7010 \
	firmware-htc9271 \
	firmware-mt7601u \
	firmware-rt2870 \
	firmware-rt73 \
	firmware-rtl8712u \
	firmware-rtl8188eu \
	firmware-rtl8192eu \
	firmware-rtl8192cu \
	firmware-rtl8xxxu \
	firmware-zd1211 \
	\
	rtl8192eu \
	\
	kernel-module-ath9k-htc \
	kernel-module-carl9170 \
	kernel-module-mt7601u \
	kernel-module-r8712u \
	kernel-module-r8723au \
	kernel-module-r8188eu \
	kernel-module-rt2500usb \
	kernel-module-rt2800usb \
	kernel-module-rt73usb \
	kernel-module-rtl8187 \
	kernel-module-rtl8192cu \
	kernel-module-rtl8xxxu \
	kernel-module-zd1211rw \
	"
	
MACHINE_FEATURES += " alsa usbhost wlan switchoff osdposition hdmicec"

IMAGE_CLASSES  += "octagon-emmc_image"
IMAGE_FSTYPES += "octagonemmc"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

PREFERRED_VERSION_linux-octagon = "4.4.35"

PREFERRED_PROVIDER_virtual/kernel = "linux-octagon"
PREFERRED_PROVIDER_virtual/egl = "octagon-opengl-${MACHINE}" 
PREFERRED_PROVIDER_virtual/libgles1 = "octagon-opengl-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 = "octagon-opengl-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "octagon-blindscan-${MACHINE}"

PREFERRED_RPROVIDER_showiframe = "octagon-showiframe-${MACHINE}"
PREFERRED_RPROVIDER_aio-grab = "octagon-grab-${MACHINE}"

require conf/machine/include/tune-cortexa15.inc

# Qt
PACKAGECONFIG_GL_pn-qtbase = "no-opengl linuxfb"

# Kodi
EXTRA_OECONF_append_pn-kodi += " --with-gpu=mali --enable-player=hiplayer"

MACHINE_EXTRA_RRECOMMENDS = " \
	ffmpeg \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-opus --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

IMAGEDIR ?= "octagon/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"
IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"

IMAGE_CMD_octagonemmc_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ext4 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
    if [ -e ${DEPLOY_DIR_IMAGE}/logo-${DISTRO_NAME}.img ]; then \
        cp -f ${DEPLOY_DIR_IMAGE}/logo-${DISTRO_NAME}.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/logo.img; \
    fi; \
    echo ${IMAGEVERSION} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
    mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \ 
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_multiboot.zip ${IMAGEDIR}/*; \
    zip -j ${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_usb.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
    rm -f -f ${DEPLOY_DIR_IMAGE}/*.json; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
    rm -Rf ${IMAGEDIR}; \
    "
