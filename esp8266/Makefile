PIO = platformio
BAUDRATE = 9600

filesystem:
	$(PIO) run --target buildfs
	$(PIO) run --target uploadfs

source:
	$(PIO) run --target upload

debug:
	$(PIO) device monitor -b $(BAUDRATE)

all:
	$(PIO) run --target buildfs
	$(PIO) run --target uploadfs
	$(PIO) run --target upload
