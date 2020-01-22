SECTION = "base"
LICENSE = "CLOSED"
PRIORITY = "required"

PR = "r7"

SRCDATE = "20170801"

SRC_URI = "http://en3homeftp.net/pub/down/vmlinuz-initrd_${MACHINE}_${SRCDATE}.tar.gz"

FILES_${PN} = "/boot"

INHIBIT_PACKAGE_STRIP = "1"
PACKAGE_ARCH := "${MACHINE_ARCH}"

do_install() {
    install -d ${D}/boot
    install -m 0755 ${WORKDIR}/vmlinuz-initrd-7439b0 ${D}/boot/initrd_run.bin
}

SRC_URI[md5sum] = "90c5d6df77953d15c5a015715862d358"
SRC_URI[sha256sum] = "a613de89759fd32a957c2492b35f55cd49af8a42133acbb11cf5ca9f8f7f883f"
