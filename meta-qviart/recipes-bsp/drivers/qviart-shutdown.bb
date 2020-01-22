require conf/license/areadeltasat-gplv2.inc

PV = "1.0"
PR = "r2"

SRC_URI = " \
    file://turnoff_power \
    file://qviart-shutdown.sh "

INITSCRIPT_NAME = "qviart-shutdown"
INITSCRIPT_PARAMS = "start 89 0 ."

inherit pkgconfig update-rc.d

S = "${WORKDIR}"

do_install() {
    install -d ${D}/etc/init.d/
    install -m 0755 ${WORKDIR}/qviart-shutdown.sh ${D}/etc/init.d/qviart-shutdown
    install -d ${D}/usr/bin
    install -m 0755 ${WORKDIR}/turnoff_power ${D}/usr/bin
}

pkg_preinst_${PN}_prepend() {
	chmod 000 "$D/etc/init.d/qviart-shutdown" || true
}

pkg_postinst_${PN}_append() {
	chmod 755 "$D/etc/init.d/qviart-shutdown"
}

PACKAGE_ARCH = "${MACHINE_ARCH}"
