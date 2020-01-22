SRCDATE = "20190409"
CHIPNAME = "7260a0"
require qviart-initrd.inc

do_install() {
    install -d ${D}/boot
    install -m 0755 ${WORKDIR}/vmlinuz-initrd-7260a0 ${D}/boot/initrd_run.bin
}

SRC_URI[md5sum] = "a5379eecc112ed35b6a5a798987df74c"
SRC_URI[sha256sum] = "4c592aa46a19075d4da1cc6819c5dd9e22f7df8d0ce50bee8dcb4a188cf2e845"
