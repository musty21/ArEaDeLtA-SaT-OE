require conf/machine/include/gigablue-arm.inc

MACHINE_EXTRA_RRECOMMENDS = " \
    ${@bb.utils.contains("GST_VERSION", "1.0", "gstreamer1.0-plugin-dvbmediasink", "gst-plugin-dvbmediasink", d)} \
    ntfs-3g \
"

### Logitech keyboard ###
KERNEL_MODULE_AUTOLOAD += "hid-logitech"
KERNEL_MODULE_AUTOLOAD += "hid-logitech-dj"

DVBSKYPROVIDER = "kernel"

MACHINE_FEATURES += "colorlcd gigabluelcd gigabluelcd220 mmc ci omb blindscan-dvbs blindscan-dvbc transcoding dvb-c mountboot bluetooth"

CHIPSET = "bcm72604"

MTD_KERNEL = "mmcblk0p4"
MTD_ROOTFS = "mmcblk0p5"
MTD_BLACK  = "mmcblk0"

SRCDATE_BOLT = "20190926"

PREFERRED_VERSION_linux-gigablue = "4.1.20"
PREFERRED_PROVIDER_virtual/kernel = "linux-gigablue"
PREFERRED_PROVIDER_virtual/egl = "gb-v3ddriver-gb72604"
PREFERRED_PROVIDER_virtual/libgles2 = "gb-v3ddriver-gb72604"

PACKAGECONFIG_GL_pn-qtbase = " gles2 eglfs linuxfb"

IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_tar_prepend = "\
    mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_boot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/boot.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_gpt.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/gpt.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_rescue.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/rescue.bin; \
    ${@bb.utils.contains("MACHINE_FEATURES", "bolt", "cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_bolt_${SRCDATE_BOLT}.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/bolt_${SRCDATE_BOLT}.bin;" , "", d)} \
    cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
    echo ${IMAGE_NAME} > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${IMGDEPLOYDIR}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${IMGDEPLOYDIR}/rootfs.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
    cd ${IMGDEPLOYDIR}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -Rf gigablue; \
"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = " \
    gigablue-platform-util-gb72604 \
    gigablue-ddbootup \
    gigablue-swapcreate \
"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = " \
    gb-v3ddriver-gb72604 \
    gb-qteglfs-platform \
    "

EXTRA_IMAGEDEPENDS = "\
    gigablue-initrd-cfe-${MACHINE} \
    "

IMAGE_INSTALL_append += "\
    bluetoothsetup-gb72604 \
    "
