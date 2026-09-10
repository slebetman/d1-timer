BOARD = esp8266:esp8266:d1_mini
PORT = /dev/ttyUSB0

all:
	arduino-cli compile -v --fqbn $(BOARD)

upload: all
	arduino-cli upload -v -p $(PORT) --fqbn $(BOARD) --discovery-timeout 1s

