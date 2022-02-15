FIRMWARE_DIR=firmware
SRC_DIR=src

FIRMWARE_VERSION=1.18
FIRMWARE=esp8266-20220117-v${FIRMWARE_VERSION}.bin
FIRMWARE_URL=https://micropython.org/resources/firmware/${FIRMWARE}

ESP_TOOL=esptool.py
CHIP=esp8266
PORT=/dev/ttyUSB0
BAUDRATE=115200

.PHONY: init
venv:
	python3 -m venv venv
	source venv/bin/activate
	pip3 install -r requirements.txt

init: venv
	make download

download:
	@if [ ! -d ${FIRMWARE_DIR} ]; then \
		@mkdir ${FIRMWARE_DIR}; \
	fi

	@if [ ! -f  ${FIRMWARE_DIR}/${FIRMWARE} ]; then \
		wget --progress=dot --tries=3 -P ${FIRMWARE_DIR}/ ${FIRMWARE_URL}; \
	fi

erase_flash: download
	${ESP_TOOL} --chip ${CHIP} --port ${PORT} erase_flash

flash_firmware:
	${ESP_TOOL} --chip ${CHIP} --port ${PORT} --baud ${BAUDRATE} \
	write_flash --flash_size=4MB 0x0 ${FIRMWARE_DIR}/${FIRMWARE}

clean:
	rm -rf ${FIRMWARE_DIR}/*
	# rm -rf ${GENERATED_DIR}
