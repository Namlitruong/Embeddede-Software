OBJ    = main.o
COURSE   = /courses/TDDI11/sw
LDSCRIPT = $(COURSE)/lib/link.cmd
BOOTSECT = $(COURSE)/lib/bootload.bin
INCLUDES = -I "$(COURSE)/include" -I "$(COURSE)/include/djgpp" $(EXTRA_INCLUDES)
CC       = $(COURSE)/i386-elf-gcc-7.3.0/bin/i386-elf-gcc
CFLAGS  += -Wall -g $(INCLUDES)
LD       = $(COURSE)/i386-elf-gcc-7.3.0/bin/i386-elf-ld
LDFLAGS  = -T$(LDSCRIPT) -static -ustart -Map link.map

embedded.bin: $(OBJ)
	$(LD) $(OBJ) $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	\rm -f link.map embedded.bin *~ *.o 
