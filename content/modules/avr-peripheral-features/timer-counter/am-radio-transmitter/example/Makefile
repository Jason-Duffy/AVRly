
##########-----------------------------------------------------------##########
##########                 Project-specific Details                  ##########
##########       Check these every time you start a new project      ##########
##########-----------------------------------------------------------##########

MCU   = atmega328p
F_CPU = 8000000UL  
BAUD  = 9600UL
## Also try BAUD = 19200 or 38400 if you're feeling lucky.

## A directory for common include files. 
LIBDIR = /usr/local/

##########-----------------------------------------------------------##########
##########                   Programmer Defaults                     ##########
##########            Set up once, then forget about it              ##########
##########          (Can override.  See bottom of file.)             ##########
##########-----------------------------------------------------------##########

PROGRAMMER_TYPE = avrisp
# extra arguments to avrdude: baud rate, chip type, -F flag, etc.
PROGRAMMER_ARGS = -b 19200 -P /dev/tty.usbmodem142201

##########-----------------------------------------------------------##########
##########                    Program Locations                      ##########
##########       Won't need to change if they're in your PATH        ##########
##########-----------------------------------------------------------##########

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

##########-----------------------------------------------------------##########
##########                     Makefile Magic!                       ##########
##########          Summary:                                         ##########
##########          We want a .hex file                              ##########
##########          Compile source files into .elf                   ##########
##########          Convert .elf file into .hex                      ##########
##########          You shouldn't need to edit below.                ##########
##########-----------------------------------------------------------##########

## The name of your project (without the .c)
# TARGET = blink
## Or name it automatically after the enclosing directory
TARGET = $(lastword $(subst /, ,$(CURDIR)))

# Object files: will find all .c/.h files in current directory
#  and in LIBDIR.  If you have any other (sub-)directories with code,
#  you can add them in to SOURCES below in the wildcard statement.
SOURCES=$(wildcard *.c $(LIBDIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)

## Compilation options, type man avr-gcc if you're curious.
CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I. -I$(LIBDIR)
CFLAGS = -Os -g -std=gnu99 -Wall
## Use short (8-bit) data types 
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
## Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections 
LDFLAGS = -Wl,-Map,$(TARGET).map 
## Optional, but often ends up with smaller code
LDFLAGS += -Wl,--gc-sections 
## Relax shrinks code even more, but makes disassembly messy
## LDFLAGS += -Wl,--relax
## LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm  ## for floating-point printf
## LDFLAGS += -Wl,-u,vfprintf -lprintf_min      ## for smaller printf
TARGET_ARCH = -mmcu=$(MCU)

## Explicit pattern rules:
##  To make .o files from .c files 
%.o: %.c $(HEADERS) Makefile
	 $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

## These targets don't have files named after them
.PHONY: all disassemble disasm eeprom size clean squeaky_clean flash fuses

all: $(TARGET).hex 

debug:
	@echo
	@echo "Source files:"   $(SOURCES)
	@echo "MCU, F_CPU, BAUD:"  $(MCU), $(F_CPU), $(BAUD)
	@echo	

# Optionally create listing file from .elf
# This creates approximate assembly-language equivalent of your code.
# Useful for debugging time-sensitive bits, 
# or making sure the compiler does what you want.
disassemble: $(TARGET).lst

disasm: disassemble

# Optionally show how big the resulting program is 
size:  $(TARGET).elf
	$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

squeaky_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~ *.eeprom

##########-----------------------------------------------------------##########
##########                Programmer-specific details                ##########
##########             Flashing code to AVR using avrdude            ##########
##########-----------------------------------------------------------##########

flash: $(TARGET).hex 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

## An alias
program: flash

flash_eeprom: $(TARGET).eeprom
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U eeprom:w:$<

avrdude_terminal:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nt

## If you've got multiple programmers that you use, 
## you can define them here so that it's easy to switch.
## To invoke, use something like `make flash_arduinoISP`
flash_usbtiny: PROGRAMMER_TYPE = usbtiny
flash_usbtiny: PROGRAMMER_ARGS =  # USBTiny works with no further arguments
flash_usbtiny: flash

flash_usbasp: PROGRAMMER_TYPE = usbasp
flash_usbasp: PROGRAMMER_ARGS =  # USBasp works with no further arguments
flash_usbasp: flash

flash_arduinoISP: PROGRAMMER_TYPE = avrisp
flash_arduinoISP: PROGRAMMER_ARGS = -b 19200 -P /dev/ttyACM0 
## (for windows) flash_arduinoISP: PROGRAMMER_ARGS = -b 19200 -P com5
flash_arduinoISP: flash

flash_109: PROGRAMMER_TYPE = avr109
flash_109: PROGRAMMER_ARGS = -b 9600 -P /dev/ttyUSB0
flash_109: flash

##########-----------------------------------------------------------##########
##########         Fuse settings and suitable defaults               ##########
##########-----------------------------------------------------------##########

## Mega 48, 88, 168, 328 default values are:
LFUSE = 0x62
HFUSE = 0xD9
EFUSE = 0xFF

## Set your custom fuse values here, then use "set_custom_fuses"
LFUSE_CUSTOM = 0xE2
HFUSE_CUSTOM = 0xD9
EFUSE_CUSTOM = 0xFF

## Generic 
FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 

fuses: 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) \
	           $(PROGRAMMER_ARGS) $(FUSE_STRING)
show_fuses:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nv	

## Called with no extra definitions, sets to defaults
set_default_fuses:  FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m \
-U efuse:w:$(EFUSE):m 
set_default_fuses:  fuses

## Called with no extra definitions, sets to defaults
set_custom_fuses:  FUSE_STRING = -U lfuse:w:$(LFUSE_CUSTOM):m \
-U hfuse:w:$(HFUSE_CUSTOM):m -U efuse:w:$(EFUSE_CUSTOM):m 
set_custom_fuses:  fuses

## Set the fuse byte for full-speed mode
## Note: can also be set in firmware for modern chips
set_fast_fuse: LFUSE = 0xE2
set_fast_fuse: FUSE_STRING = -U lfuse:w:$(LFUSE):m 
set_fast_fuse: fuses

## Set the EESAVE fuse byte to preserve EEPROM across flashes
set_eeprom_save_fuse: HFUSE = 0xD7
set_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
set_eeprom_save_fuse: fuses

## Clear the EESAVE fuse byte
clear_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
clear_eeprom_save_fuse: fuses


##########-----------------------------------------------------------##########
##########            Help options                                   ##########
##########            Type "make help" for a list of options.        ##########
##########-----------------------------------------------------------##########

help:
	@echo "\n\n"
	@echo "-------------------------------------------"
	@echo "-            Available Options.           -"
	@echo "-------------------------------------------"
	@echo "\n- Type 'make' followed by one or more of the following commands \
	to implement them."
	@echo "- The 'make' command is the only exception to this, and does not \
	need to be preceded with another 'make'."
	@echo "\n\n  Cleaning output files: \n"
	@echo '		clean 				- Remove generated files with the name of \
	the enclosing directory.'
	@echo '		squeaky_clean 			- Remove ALL files in current \
	directory with certain extensions.'
	@echo "\n\n  Compiling, linking and flashing your code \n"
	@echo '		make				- Compiles and links your source code \
	into a .hex file'
	@echo '		flash 				- Compiles and flashes the code to the \
	target MCU'
	@echo '		flash_eeprom 			- Flashes the contents of the eeprom \
	file to the target MCU.'
	@echo '		avrdude_terminal		- Initialises user communication with \
	AVR via terminal.'
	@echo "\n\n  Setting and clearing Fuses \n"
	@echo '		show_fuses			- Reads fuse registers and reports back \
	with the current settings'
	@echo '		set_default_fuses		- Sets LFUSE, HFUSE and EFUSE values \
	on MCU.'
	@echo '		set_custom_fuses		- Sets LFUSE_CUSTOM, HFUSE_CUSTOM and \
	EFUSE_CUSTOM values.'
	@echo '		set_fast_fuse			- Sets fuse value to divide internal \
	clock by 1 rather than 8.'
	@echo '		set_eeprom_save_fuse		- Set the EESAVE fuse byte to \
	preserve EEPROM across flashes.'
	@echo ' 		clear_eeprom_save_fuse		- Clears the EESAVE fuse, \
	data will be lost between flashes.'
	@echo "\n\n  Debugging: \n"
	@echo '		debug				- Prints the variables from the top of \
	the makefile and their values.'
	@echo '		disassemble			- Creates a .lst file containing an \
	approximate assembly version of the code.'
	@echo '		size 				- Prints a report on the memory usage of \
	the application.'
	@echo "\n\n"

