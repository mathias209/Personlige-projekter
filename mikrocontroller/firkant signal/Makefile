#
# AVR Makefile
#
# Lavet af Mathias Ø. Selander
# 2026
#


# platformio's avr-gcc binary skal bruges til OLED driver, ellers kan normal bare bruges
GCCBIN=/home/$(USER)/.platformio/packages/toolchain-atmelavr/bin/avr-gcc
# GCCBIN=avr-gcc

INCDIR=../include
LIBDIR=../lib

LDFLAGS=-mmcu=$(PART) -Os -std=gnu11 -fno-fat-lto-objects -Wall -ffunction-sections -fdata-sections -flto -I$(INCDIR) -L$(LIBDIR)

targets = $(patsubst %.c,%.o,$(wildcard *.c))
libtargets = $(patsubst %.c,%.so,$(wildcard $(LIBDIR)/*.c))

# programmar options
PART=atmega2560
PROGRAMMER=stk500v2
PORT=/dev/ttyUSB0
PBAUD=115200

# serial options
SBAUD=19200
SPORT=/dev/ttyUSB0

all: upload

clean:
	$(RM) $(targets) main.elf main.hex

build: main.elf

bear:
	bear -- make

upload: main.hex
	avrdude -p $(PART) -c $(PROGRAMMER) -P $(PORT) -b $(PBAUD) -D -U flash:w:main.hex:i

main.hex: main.elf
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

main.elf: $(targets) $(libtargets)
	$(GCCBIN) -o main.elf $(LDFLAGS) $(targets) $(libtargets)

$(targets): %.o: %.c
	$(GCCBIN) $(LDFLAGS) -c $< -o $@

$(libtargets): %.so: %.c
	$(GCCBIN) $(LDFLAGS) -c $< -o $@

serial: upload
	picocom -b $(SBAUD) $(SPORT)
