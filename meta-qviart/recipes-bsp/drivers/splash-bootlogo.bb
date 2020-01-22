DESCRIPTION = "first bootlogo splash image"
SECTION = "base"
PRIORITY = "required"
PACKAGE_ARCH = "${MACHINE_ARCH}"
LICENSE = "CLOSED"

COMPATIBLE_MACHINE = "lunix|lunixco|lunix4k|lunix3_4k"

PV = "1.0"
PR = "r0"

S = "${WORKDIR}"

SRC_URI_append_lunix3-4k += "file://lunix3-4k_splash.bmp"
SRC_URI_append_lunix4k += "file://lunix4k_splash.bmp"
SRC_URI_append_lunix += " \
	file://${MACHINE}_splash.bmp \
	file://${MACHINE}_splash1.bmp \
	file://${MACHINE}_splash2.bmp \
	file://${MACHINE}_splash3.bmp \
"
SRC_URI_append_lunixco += " \
	file://${MACHINE}_splash.bmp \
	file://${MACHINE}_splash1.bmp \
	file://${MACHINE}_splash2.bmp \
	file://${MACHINE}_splash3.bmp \
"

inherit deploy

do_install() {
	mkdir -p ${DEPLOY_DIR_IMAGE}
	install -m 0644 ${WORKDIR}/*.bmp ${DEPLOY_DIR_IMAGE}/
}

do_deploy() {
}

addtask deploy before do_build after do_install
