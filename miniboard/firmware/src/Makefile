MCU:= atmega2560
PROGRAMMER:= wiring
PROGRAMMER_PORT:= /dev/ttyACM0
PROGRAMMER_PORT_ALT:= /dev/ttyUSB0

SIMAVR:=simavr

CC:=avr-gcc
OBJCOPY:=avr-objcopy
AVRDUDE:=avrdude
CFLAGS:= -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wextra -Wall -Wstrict-prototypes -std=gnu99
LIBS:=


# Output filename, without extension
OUTFILE:=../build/miniboard
# Object file names
# NOTE: Order is important! For the weak-symbol based UART receive handler mapping,
# uart.o must come last.
OBJFILES:=commgen.o comm.o sabertooth.o adc.o  uart.o
# Main file
FILE:=miniboard.c

.PHONY: clean fuses download

# By default, compile and download.
all: $(OUTFILE).bin download

# Generate communication files
commgen.o: ../../../common/SPECIFICATION.md
	@$(/usr/bin/env python3) ../../../common/codegen.py ../../../common/SPECIFICATION.md commgen.c commgen.h
	@$(CC) -mmcu=$(MCU) $(CFLAGS) -I. -c commgen.c -o commgen.o $(LIBS)

# Compile source files
%.o: %.c %.h
	@$(CC) -mmcu=$(MCU) $(CFLAGS) -I. -c $< -o $@ $(LIBS)
	
# Compile & link
$(OUTFILE).bin: $(OBJFILES)
	@$(CC) -mmcu=$(MCU) $(CFLAGS) -I. $(FILE) $(OBJFILES) -o $(OUTFILE).elf $(LIBS)
	@$(OBJCOPY) -O binary -R .eeprom $(OUTFILE).elf $(OUTFILE).bin
	@$(OBJCOPY) -O ihex -R .eeprom $(OUTFILE).elf $(OUTFILE).hex

# Download firmware, without changing fuses or eeprom.
download:
	@if [ -c $(PROGRAMMER_PORT) ];\
	then \
		$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PROGRAMMER_PORT) -D -U flash:w:$(OUTFILE).bin:r;\
	else \
		if [ -c $(PROGRAMMER_PORT_ALT) ];\
		then \
			$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PROGRAMMER_PORT_ALT) -D -U flash:w:$(OUTFILE).bin:r; \
		else \
			echo "Port $(PROGRAMMER_PORT) or $(PROGRAMMER_PORT_ALT) not found; skipping programming."; \
		fi; \
	fi;

#Delete generated files
clean:
	@rm -f *.hex *.elf *.bin *.o $(OUTFILE).elf $(OUTFILE).bin commgen.c commgen.h
