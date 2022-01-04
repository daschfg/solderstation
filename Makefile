PORT = /dev/ttyACM0
TARGET = solderstation-fw.ino

PACKAGE = archlinux-arduino
ARCHITECTURE = avr
BOARD = uno

all: build

build:
	arduino --verify --board $(PACKAGE):$(ARCHITECTURE):$(BOARD) $(TARGET)

upload:
	arduino --upload --board $(PACKAGE):$(ARCHITECTURE):$(BOARD) --port $(PORT) $(TARGET)
