MCU=atmega32
F_CPU=1000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
OBJFILES = dhcp.o enc28j60.o ethernet.o http.o ip.o main.o socket.o tcp.o udp.o utils.o #arp.o
LIBDIR = drivers

all :build clear

build:
	$(CC) $(CFLAGS) -Os -c main.c
	#$(CC) $(CFLAGS) -Os -c $(LIBDIR)/arp.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/dhcp.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/enc28j60.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/ethernet.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/http.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/ip.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/socket.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/tcp.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/udp.c
	$(CC) $(CFLAGS) -Os -c $(LIBDIR)/utils.c
	$(CC) $(CFLAGS) -o ${TARGET}.out ${OBJFILES}
	$(OBJCOPY) -R .eeprom -O ihex ${TARGET}.out ${TARGET}.hex

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

clear:
	rm -f ${OBJFILES} ${TARGET}.out
