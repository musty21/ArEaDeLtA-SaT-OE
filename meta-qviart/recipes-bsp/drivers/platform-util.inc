SECTION = "base"
LICENSE = "CLOSED"

PR="${SRCDATE}"

SRC_URI = " \
    http://en3homeftp.net/pub/down/platform-util-${CHIP}.tar.gz \
    file://${INITSCRIPT_NAME}.sysvinit \
"

S="${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/* ${D}${bindir}
    install -d ${D}/etc/init.d
    install -m 0755 ${WORKDIR}/${INITSCRIPT_NAME}.sysvinit ${D}/etc/init.d/${INITSCRIPT_NAME}
}

do_package_qa[noexec] = "1"

PACKAGE_ARCH := "${MACHINE_ARCH}"
FILES_${PN}="/"

inherit update-rc.d

INITSCRIPT_PARAMS = "start 65 S . stop 90 0 ."
INITSCRIPT_NAME = "dags-platform-util"

INSANE_SKIP_${PN} += "already-stripped"
