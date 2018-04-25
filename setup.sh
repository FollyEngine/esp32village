#!/bin/bash -ex

if ! which sudo; then
	echo "run apt-get install sudo"
	exit
fi

sudo sed 's/main$/main contrib non-free/g' /etc/apt/sources.list
sudo apt-get update
sudo apt-get install -yq sudo flashrom mosquitto mosquitto-clients vim git firmware-linux-free python-serial firmware-iwlwifi

export fromdir=$(pwd)
export basedir='/usr/local/'
export ver='arduino-1.8.5'
export arduinodir="${basedir}${ver}"

if [[ ! -d "$arduinodir" ]]; then
	#if [[ -d "${fromdir}/${ver}" ]]; then
	#	sudo cp -r "${fromdir}/$ver" "${arduinodir}"
	#else
		cd $basedir
		sudo tar xvf "${fromdir}/${ver}-linux64.tar.xz"
	#fi
	sudo chmod 777 $arduinodir
	cd $arduinodir
	./install.sh
	ln -s /usr/local/arduino-1.8.5/arduino /usr/local/bin/
fi


if [[ ! -d "${arduinodir}/hardware/espressif" ]]; then
	mkdir -p ${arduinodir}/hardware/espressif
	cd ${arduinodir}/hardware/espressif
	if [[ -d "${fromdir}/esp32" ]]; then
		cp -r "$fromdir/esp32" .
	else
		git clone https://github.com/espressif/arduino-esp32.git esp32
	fi
	cd esp32/tools/
	python get.py
fi

# install the MQTT lib
arduino --install-library PubSubClient

sudo adduser $USER sudo
sudo adduser $USER dialout