require platform-util.inc

PROVIDES += "platform-util-${CHIP}"
RPROVIDES_${PN} += "platform-util-${CHIP}"

COMPATIBLE_MACHINE = "^(lunix4k)$"

PV="17.1"

S="${WORKDIR}/platform-util-lunix4k"

SRC_URI[md5sum] = "7db9b52968bd0b90cd0f6ba8bcb41862"
SRC_URI[sha256sum] = "9405257a6eff4472531ad9160327d536a9dceacf06a820c2c090f73c6c1918b6"
