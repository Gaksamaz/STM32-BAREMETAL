CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m3 -mthumb -Wall -O2 -nostdlib -nostartfiles -ffreestanding

all: main.elf

main.elf: startup.o main.o
	$(CC) $(CFLAGS) -T stm32f103xb.ld -o main.elf startup.o main.o

startup.o: startup.s
	$(CC) $(CFLAGS) -c startup.s -o startup.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o *.elf
