SUMMARY = "SF8008 partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

SRCDATE = "20191225"

COMPATIBLE_MACHINE = "^(sf8008)$"

S = "${WORKDIR}/patitions"

SRC_URI = "http://source.mynonpublic.com/octagon/${MACHINE}-partitions-${SRCDATE}.zip"

SRC_URI[md5sum] = "02213d79b2d1d1a14476b0702bfcea25"
SRC_URI[sha256sum] = "40facad26d573f1697391e92569b6871cfaa341edd7a7020a37581e91bf806d5"

ALLOW_EMPTY_${PN} = "1"
do_configure[nostamp] = "1"

do_install() {
    install -d ${D}${datadir}
    install -m 0644 ${S}/bootargs.bin ${D}${datadir}/bootargs.bin
    install -m 0644 ${S}/fastboot.bin ${D}${datadir}/fastboot.bin
    install -m 0644 ${S}/apploader.bin ${D}${datadir}/apploader.bin
}

FILES_${PN} = "${datadir}"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/boot.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/apploader.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/pq_param.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/emmc_partitions.xml ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/baseparam.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/logo.img ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
    install -m 0755 ${S}/deviceinfo.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions
}

addtask deploy before do_build after do_install

INSANE_SKIP_${PN} += "already-stripped"
