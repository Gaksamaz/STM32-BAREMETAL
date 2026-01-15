TARGET = main
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -O2 -ffreestanding -nostdlib -nostartfiles -T stm32f103xb.ld
AS = arm-none-eabi-as
ASFLAGS = -mcpu=cortex-m3 -mthumb

all: $(TARGET).bin

$(TARGET).elf: startup.s main.c stm32f103xb.ld
	$(CC) $(CFLAGS) -o $@ startup.s main.c

$(TARGET).bin: $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -f *.o *.elf *.bin