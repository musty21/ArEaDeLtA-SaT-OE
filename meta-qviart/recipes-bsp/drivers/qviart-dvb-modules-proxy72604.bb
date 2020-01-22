SUMMARY = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE}"

SRCDATE = "20190522"
KV = "4.1.20"
PV = "${KV}+${SRCDATE}"
PR = "r0"

SRC_URI[md5sum] = "2c3ed8452e826be8b5dfaf715df823aa"
SRC_URI[sha256sum] = "3c2d2c74c268134ee41e27c787e44b169441a9a658a58752a69273b22f9b8fa2"

SRC_URI = "http://en3homeftp.net/release/images/oedrivers/bcmlinuxdvb_72604-${KV}-${SRCDATE}.tar.gz"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

do_compile() {
}

do_populate_sysroot() {
}

do_install() {
    install -d ${D}/lib/modules/${KV}/extra
    cp -Rf ${WORKDIR}/lib/modules/${KV}/extra/*.ko ${D}/lib/modules/${KV}/extra/
}

FILES_${PN} += "/lib/modules/${KV}/extra"
