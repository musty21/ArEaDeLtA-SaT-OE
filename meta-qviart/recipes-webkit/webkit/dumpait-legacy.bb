SUMMARY = "dumpait"
PRIORITY = "required"
LICENSE = "GPLv3"
LIC_FILES_CHKSUM = "file://LICENSE;md5=84dcc94da3adb52b53ae4fa38fe49e5d"
COMPATIBLE_MACHINE = "^(lunix3-4k|lunix4k)$"

inherit autotools-brokensep pkgconfig gitpkgv

SRCREV = "${AUTOREV}"
PV = "git${SRCPV}"
PKGV = "git${GITPKGV}"
PR = "r0"

PACKAGES += " ${PN}-src"

DEPENDS = "libdvbsi++"

SRC_URI = "git://github.com/oe-alliance/dumpait-legacy.git;protocol=https "


S = "${WORKDIR}/git"
DESTDIR = "enigma2/python/Plugins/Extensions/HbbTV"

do_install() {
    install -d ${D}/usr/lib/${DESTDIR}
    install -m 0755 ${S}/src/dumpait ${D}/usr/lib/${DESTDIR}
}

FILES_${PN} = "${libdir}/${DESTDIR}/dumpait"
FILES_${PN}-dbg = "${libdir}/${DESTDIR}/.debug"
FILES_${PN}-src = "/usr/src"
