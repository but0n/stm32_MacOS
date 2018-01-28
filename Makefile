# general Makefile
# make OptLIB=0 OptSRC=0 all tshow
include Makefile.common
LDFLAGS=$(COMMONFLAGS) -fno-exceptions -ffunction-sections -fdata-sections -L$(LIBDIR) -nostartfiles -Wl,--gc-sections,-Tlinker.ld

LDLIBS+=-lstm32
LDLIBS+=-lm

STARTUP=startup.c

all: libs src
	$(CC) -o $(PROGRAM).elf $(LDFLAGS) \
		-Wl,--whole-archive \
			src/app.a \
		-Wl,--no-whole-archive \
			$(LDLIBS)
	$(OBJCOPY) -O ihex $(PROGRAM).elf $(PROGRAM).hex
	$(OBJCOPY) -O binary $(PROGRAM).elf $(PROGRAM).bin
#Extract info contained in ELF to readable text-files:
	arm-none-eabi-readelf -a $(PROGRAM).elf > $(PROGRAM).info_elf
	arm-none-eabi-size -d -B -t $(PROGRAM).elf > $(PROGRAM).info_size
	arm-none-eabi-objdump -S $(PROGRAM).elf > $(PROGRAM).info_code
	arm-none-eabi-nm -t d -S --size-sort -s $(PROGRAM).elf > $(PROGRAM).info_symbol

.PHONY: libs src clean tshow

libs:
	$(MAKE) -C libs $@
src:
	$(MAKE) -C src $@
clean:
	$(MAKE) -C src $@
	$(MAKE) -C libs $@
	rm -f $(PROGRAM).elf $(PROGRAM).hex $(PROGRAM).bin $(PROGRAM).info_elf $(PROGRAM).info_size
	rm -f $(PROGRAM).info_code
	rm -f $(PROGRAM).info_symbol
	rm -f DUMP.s
tshow:
		@echo "=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_"
		@echo "=🍺====>> optimize settings: $(InfoTextLib), $(InfoTextSrc)"
		@echo "=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_"

isp: /dev/cu.SLAB_USBtoUART main.bin
	cat -u /dev/cu.SLAB_USBtoUART & stty -f /dev/cu.SLAB_USBtoUART 115200
	echo '>' > /dev/cu.SLAB_USBtoUART
	pkill cat -u /dev/cu.SLAB_USBtoUART
	make flash || make flash

flash: /dev/cu.SLAB_USBtoUART main.bin
	stm32flash -w $(TOP)/main.bin -v -g 0 /dev/tty.SLAB_USBtoUART
dump:
	$(OBJDUMP) -D main.elf > DUMP.s
	open DUMP.s
tty:
	screen /dev/tty.SLAB_USBtoUART 115200
dfu:
	dfu-util -d 0483:df11 -c 1 -a 0 -s 0x08000000:leave -D main.bin
install:
	brew tap px4/px4
	brew install gcc-arm-none-eabi
