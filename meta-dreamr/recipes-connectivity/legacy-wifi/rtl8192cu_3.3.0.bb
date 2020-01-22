SUMMARY = "driver for Realtek USB wireless devices"
SECTION = "kernel/modules"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://hal/hal_init.c;beginline=1;endline=19;md5=f8d10a6bd2fdfa240c0634a7c660c57f"

RREPLACES_${PN} = "kernel-module-rtl8192cu"

DEPENDS = "firmware-rtl8192cu"


COMPATIBLE_MACHINE = "dm800$"

inherit module

SRC_URI = "http://downloads.pli-images.org/misc/rtl8188C_8192C_8192D_usb_linux_v3.3.0_2971.20111128.tar.gz \
    file://additional_productids.patch \
    file://fix_linking.patch \
    file://add-3.8-support.patch \
    "

S = "${WORKDIR}/rtl8188C_8192C_8192D_usb_linux_v3.3.0_2971.20111128"

inherit module

EXTRA_OEMAKE = "KSRC=${STAGING_KERNEL_DIR} KDIR=${STAGING_KERNEL_DIR}"

export MB="${MACHINEBUILD}"
export TM="${MACHINE}"

do_install() {
    install -d ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/net/wireless
    install -m 0644 ${S}/8192cu.ko ${D}${base_libdir}/modules/${KERNEL_VERSION}/kernel/drivers/net/wireless
    if [ "$TM" = "dm800" ] && [ "$MB" = "estar" ]
    then
         echo "Not autoloading for estar!"
    else
         install -d ${D}/etc/modules-load.d
         echo "8192cu" > ${D}/etc/modules-load.d/wlan8192cu.conf
    fi
}

FILES_${PN}_append = " \
        ${sysconfdir}/Wireless \
        ${sysconfdir}/modules-load.d \
"

SRC_URI[md5sum] = "6d5bd5f94d9d6d6667393839c1861101"
SRC_URI[sha256sum] = "fab0db3ee9fa60beff5ca18248e0ed20bf439873f94461c47e0deda28d184b2b"
