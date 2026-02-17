# VitaSDK Makefile for PsvitaSpot
TARGET = PsvitaSpot
SRC = $(wildcard src/*.c)
BUILD = build
RESOURCES = resources/*
PARAM_SFO = param.sfo

CFLAGS = -O2 -Wall -Iinclude
LDFLAGS =

all: $(BUILD)/$(TARGET).vpk

$(BUILD)/$(TARGET).vpk: $(BUILD)/$(TARGET).elf
	@echo "Packing VPK..."
	vita-mksfoex $(PARAM_SFO) $(BUILD)/$(TARGET).elf
	vita-pack-vpk $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).vpk $(RESOURCES)

$(BUILD)/$(TARGET).elf: $(SRC)
	@mkdir -p $(BUILD)
	@echo "Compiling ELF..."
	arm-vita-eabi-gcc $(CFLAGS) -o $(BUILD)/$(TARGET).elf $(SRC) $(LDFLAGS)

clean:
	@echo "Cleaning build folder..."
	rm -rf $(BUILD)
