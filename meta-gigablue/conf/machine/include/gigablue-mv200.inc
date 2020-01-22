require conf/machine/include/gigablue-oem.inc

MTD_KERNEL = "mmcblk0p12"
MTD_ROOTFS = "mmcblk0p13"
MTD_BLACK  = "mmcblk0"

DISTRO_FEATURES_remove = "x11 wayland"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    gigablue-dvb-modules-${MACHINE} \
    gigablue-loadmodules-gbmv200 \ 
    gigablue-libs-gbmv200 \
    gigablue-hihalt-gbmv200 \
    gigablue-reader-gbmv200 \
    gigablue-libreader-gbmv200 \
    gigablue-buildimage \
    e2fsprogs-resize2fs \
    gptfdisk \
"

MACHINE_FEATURES += "switchoff 7segment hdmicec textlcd emmc mmc blindscan-dvbs alsa hisi"

IMAGE_CLASSES  += "gigablue-emmc_image"
IMAGE_FSTYPES += "gigablueemmc"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

PREFERRED_VERSION_linux-gigablue = "4.4.35"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "gigablue-blindscan-gbmv200"
PREFERRED_RPROVIDER_showiframe = "gigablue-showiframe-gbmv200"
PREFERRED_RPROVIDER_aio-grab = "gigablue-grab-gbmv200"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"
PREFERRED_VERSION_ffmpeg = "3.4.2"

require conf/machine/include/tune-cortexa15.inc

DVBSKYPROVIDER = "kernel"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

IMAGE_CMD_gigablueemmc_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    cp ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
    echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
    mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_mmc.zip ${IMAGEDIR}/*; \
    zip -j ${IMAGE_NAME}_mmc.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.json; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
    rm -Rf ${IMAGEDIR}; \
    "
