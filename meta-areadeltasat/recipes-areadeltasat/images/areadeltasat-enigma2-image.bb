require areadeltasat-image.bb

WIFI_DRIVERS = " \
	firmware-carl9170 \
	firmware-htc7010 \
	firmware-htc9271 \
	firmware-rt2870 \
	firmware-rt73 \
	firmware-rtl8712u \
	firmware-rtl8188eu \
	firmware-rtl8192cu \
	firmware-zd1211 \
	\
	kernel-module-8192eu \
	kernel-module-ath9k-htc \
	kernel-module-carl9170 \
	kernel-module-r8712u \
	kernel-module-rt2500usb \
	kernel-module-rt2800usb \
	kernel-module-rt73usb \
	kernel-module-rtl8187 \
	kernel-module-rtl8192cu \
	kernel-module-zd1211rw \
	"

ENIGMA2_PLUGINS = " \
	enigma2-plugin-extensions-audiosync \
	enigma2-plugin-extensions-autobackup \
	enigma2-plugin-extensions-cutlisteditor \
	enigma2-plugin-extensions-graphmultiepg \
	enigma2-plugin-extensions-mediaplayer \
	enigma2-plugin-extensions-mediascanner \
	enigma2-plugin-extensions-moviecut \
	enigma2-plugin-extensions-openwebif \
	enigma2-plugin-extensions-pictureplayer \
	enigma2-plugin-extensions-ppanel \
	\
	enigma2-plugin-systemplugins-fastscan \
	enigma2-plugin-systemplugins-hotplug \
	enigma2-plugin-systemplugins-networkbrowser \
	enigma2-plugin-systemplugins-positionersetup \
	enigma2-plugin-systemplugins-satfinder \
	enigma2-plugin-systemplugins-skinselector \
	enigma2-plugin-systemplugins-softwaremanager \
	enigma2-plugin-systemplugins-videomode \
	enigma2-plugin-systemplugins-videotune \
	enigma2-plugin-systemplugins-osdpositionsetup \
	\
	${@bb.utils.contains("MACHINE_FEATURES", "3dtv", "enigma2-plugin-systemplugins-osd3dsetup" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "dvb-c", "enigma2-plugin-systemplugins-cablescan" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "hdmicec", "enigma2-plugin-systemplugins-hdmicec" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "wlan", "enigma2-plugin-systemplugins-wirelesslan", "", d)} \
	\
	${@bb.utils.contains('AREADELTASAT_FEATURES', 'ci', 'enigma2-plugin-systemplugins-commoninterfaceassignment', '', d)} \
	${@bb.utils.contains('AREADELTASAT_FEATURES', 'dvd', 'enigma2-plugin-extensions-cdinfo enigma2-plugin-extensions-dvdplayer', '', d)} \
	${@bb.utils.contains('AREADELTASAT_FEATURES', 'fan', 'enigma2-plugin-systemplugins-tempfancontrol', '', d)} \
	${@bb.utils.contains('AREADELTASAT_FEATURES', '7seg', 'enigma2-plugin-systemplugins-vfdcontrol', '', d)} \
	"

DEPENDS += " \
	enigma2 \
	enigma2-pliplugins \
	enigma2-plugins \
	"

IMAGE_INSTALL += " \
	aio-grab \
	enigma2 \
	libavahi-client \
	settings-autorestore \
	tuxbox-common \
	ofgwrite \
	${ENIGMA2_PLUGINS} \
	\
	${WIFI_DRIVERS} \
	\
	${@bb.utils.contains_any('MACHINE', 'vuuno vuduo vuultimo vusolo vusolo2 vuduo2 vusolose vuzero vuuno4k vuuno4kse vuzero4k vuultimo4k vusolo4k vuduo4k', 'vuplus-tuner-turbo', '', d)} \
	${@bb.utils.contains_any('MACHINE', 'vuuno4kse vuultimo4k vuduo4k', 'vuplus-hdmi-in-helper', '', d)} \
	\
	${@bb.utils.contains_any('MACHINE', 'gbquad4k gbue4k', 'kernel-module-8812au', '', d)} \
	${@bb.utils.contains_any('MACHINE', 'gbquad4k gbue4k', 'enigma2-plugin-systemplugins-wirelesslan', '', d)} \
	\
	${@bb.utils.contains("MACHINE_FEATURES", "chromium", "enigma2-plugin-extensions-chromium", "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "transcoding", "enigma2-plugin-systemplugins-transcodingsetup", "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "streamproxy", "streamproxy", "", d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'ctrlrc', "enigma2-plugin-systemplugins-remotecontrolcode", "", d)} \
	\
	${@bb.utils.contains('AREADELTASAT_FEATURES', 'dvd', 'cdtextinfo', '', d)} \
	"

export IMAGE_BASENAME = "ArEaDeLtA-SaT-E2"
