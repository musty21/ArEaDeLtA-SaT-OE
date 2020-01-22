KV = "3.14-1.17"
DRIVERDATE = "20180222"

require dreambox-dvb-modules-new.inc

PR = "${INC_PR}.0"

SRC_URI[dm920.md5sum] = "c62048cdd9b59871241ab747ca588376"
SRC_URI[dm920.sha256sum] = "b21df39f620834299246cd85a371316af5e5aaddd615170e82bc8f4419435dfd"

COMPATIBLE_MACHINE = "dm920"

MD5SUM = "${@d.getVarFlag('SRC_URI', 'dm920.md5sum', True)}"
