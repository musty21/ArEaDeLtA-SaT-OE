inherit image_types

IMAGE_ROOTFS = "${WORKDIR}/rootfs/linuxrootfs1"

do_image_axasemmc[depends] = " \
	e2fsprogs-native:do_populate_sysroot \
	parted-native:do_populate_sysroot \
	dosfstools-native:do_populate_sysroot \
	mtools-native:do_populate_sysroot \
	virtual/kernel:do_populate_sysroot \
"

EMMC_IMAGE = "${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img"
BLOCK_SIZE = "512"
BLOCK_SECTOR = "2"
IMAGE_ROOTFS_ALIGNMENT = "1024"
BOOT_PARTITION_SIZE = "3072"
KERNEL_PARTITION_SIZE = "8192"
ROOTFS_PARTITION_SIZE = "1048576"
EMMC_IMAGE_SIZE = "3817472"

KERNEL_PARTITION_OFFSET = "$(expr ${IMAGE_ROOTFS_ALIGNMENT} \+ ${BOOT_PARTITION_SIZE})"
ROOTFS_PARTITION_OFFSET = "$(expr ${KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})"
SECOND_KERNEL_PARTITION_OFFSET = "$(expr ${ROOTFS_PARTITION_OFFSET} \+ ${ROOTFS_PARTITION_SIZE})"
THRID_KERNEL_PARTITION_OFFSET = "$(expr ${SECOND_KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})"
FOURTH_KERNEL_PARTITION_OFFSET = "$(expr ${THRID_KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})"
MULTI_ROOTFS_PARTITION_OFFSET = "$(expr ${FOURTH_KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})"

IMAGE_CMD_axasemmc () {
    eval local COUNT=\"0\"
    eval local MIN_COUNT=\"60\"
    if [ $ROOTFS_SIZE -lt $MIN_COUNT ]; then
        eval COUNT=\"$MIN_COUNT\"
    fi
    dd if=/dev/zero of=${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ext4 seek=${IMAGE_ROOTFS_SIZE} count=$COUNT bs=1024
    mkfs.ext4 -F -i 4096 ${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ext4 -d ${WORKDIR}/rootfs
    dd if=/dev/zero of=${EMMC_IMAGE} bs=${BLOCK_SIZE} count=0 seek=$(expr ${EMMC_IMAGE_SIZE} \* ${BLOCK_SECTOR})
    parted -s ${EMMC_IMAGE} mklabel gpt
    parted -s ${EMMC_IMAGE} unit KiB mkpart boot fat16 ${IMAGE_ROOTFS_ALIGNMENT} $(expr ${IMAGE_ROOTFS_ALIGNMENT} \+ ${BOOT_PARTITION_SIZE})
    parted -s ${EMMC_IMAGE} unit KiB mkpart linuxkernel ${KERNEL_PARTITION_OFFSET} $(expr ${KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})
    parted -s ${EMMC_IMAGE} unit KiB mkpart linuxrootfs ext4 ${ROOTFS_PARTITION_OFFSET} $(expr ${ROOTFS_PARTITION_OFFSET} \+ ${ROOTFS_PARTITION_SIZE})
    parted -s ${EMMC_IMAGE} unit KiB mkpart linuxkernel2 ${SECOND_KERNEL_PARTITION_OFFSET} $(expr ${SECOND_KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})
    parted -s ${EMMC_IMAGE} unit KiB mkpart linuxkernel3 ${THRID_KERNEL_PARTITION_OFFSET} $(expr ${THRID_KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})
    parted -s ${EMMC_IMAGE} unit KiB mkpart linuxkernel4 ${FOURTH_KERNEL_PARTITION_OFFSET} $(expr ${FOURTH_KERNEL_PARTITION_OFFSET} \+ ${KERNEL_PARTITION_SIZE})
    parted -s ${EMMC_IMAGE} unit KiB mkpart userdata ext4 ${MULTI_ROOTFS_PARTITION_OFFSET} 100%
    dd if=/dev/zero of=${WORKDIR}/boot.img bs=${BLOCK_SIZE} count=$(expr ${BOOT_PARTITION_SIZE} \* ${BLOCK_SECTOR})
    mkfs.msdos -S 512 ${WORKDIR}/boot.img
    echo "boot emmcflash0.linuxkernel 'root=/dev/mmcblk0p3 rootsubdir=linuxrootfs1 kernel=/dev/mmcblk0p2 rw rootwait'" > ${WORKDIR}/STARTUP
    echo "boot emmcflash0.linuxkernel 'root=/dev/mmcblk0p3 rootsubdir=linuxrootfs1 kernel=/dev/mmcblk0p2 rw rootwait'" > ${WORKDIR}/STARTUP_LINUX_1
    echo "boot emmcflash0.linuxkernel2 'root=/dev/mmcblk0p7 rootsubdir=linuxrootfs2 kernel=/dev/mmcblk0p4 rw rootwait'" > ${WORKDIR}/STARTUP_LINUX_2
    echo "boot emmcflash0.linuxkernel3 'root=/dev/mmcblk0p7 rootsubdir=linuxrootfs3 kernel=/dev/mmcblk0p5 rw rootwait'" > ${WORKDIR}/STARTUP_LINUX_3
    echo "boot emmcflash0.linuxkernel4 'root=/dev/mmcblk0p7 rootsubdir=linuxrootfs4 kernel=/dev/mmcblk0p6 rw rootwait'" > ${WORKDIR}/STARTUP_LINUX_4
    mcopy -i ${WORKDIR}/boot.img -v ${WORKDIR}/STARTUP ::
    mcopy -i ${WORKDIR}/boot.img -v ${WORKDIR}/STARTUP_LINUX_1 ::
    mcopy -i ${WORKDIR}/boot.img -v ${WORKDIR}/STARTUP_LINUX_2 ::
    mcopy -i ${WORKDIR}/boot.img -v ${WORKDIR}/STARTUP_LINUX_3 ::
    mcopy -i ${WORKDIR}/boot.img -v ${WORKDIR}/STARTUP_LINUX_4 ::
    dd conv=notrunc if=${WORKDIR}/boot.img of=${EMMC_IMAGE} bs=${BLOCK_SIZE} seek=$(expr ${IMAGE_ROOTFS_ALIGNMENT} \* ${BLOCK_SECTOR})
    dd conv=notrunc if=${DEPLOY_DIR_IMAGE}/zImage of=${EMMC_IMAGE} bs=${BLOCK_SIZE} seek=$(expr ${KERNEL_PARTITION_OFFSET} \* ${BLOCK_SECTOR})
    dd if=${IMGDEPLOYDIR}/${IMAGE_NAME}.rootfs.ext4 of=${EMMC_IMAGE} bs=${BLOCK_SIZE} seek=$(expr ${ROOTFS_PARTITION_OFFSET} \* ${BLOCK_SECTOR})
}
