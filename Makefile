# VitaSDK Makefile for PsvitaSpot (C++)
TARGET = PsvitaSpot
SRC = $(shell find src -name "*.cpp")   # <-- grabs all .cpp files
BUILD = build
RESOURCES = resources/*
PARAM_SFO = param.sfo

CXX = arm-vita-eabi-g++                 # Use g++ for C++ files
CXXFLAGS = -O2 -Wall -Iinclude
LDFLAGS =

all: $(BUILD)/$(TARGET).vpk

$(BUILD)/$(TARGET).vpk: $(BUILD)/$(TARGET).elf
	@echo "Packing VPK..."
	vita-mksfoex $(PARAM_SFO) $(BUILD)/$(TARGET).elf
	vita-pack-vpk $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).vpk $(RESOURCES)

$(BUILD)/$(TARGET).elf: $(SRC)
	@mkdir -p $(BUILD)
	@echo "Compiling ELF..."
	$(CXX) $(CXXFLAGS) -o $(BUILD)/$(TARGET).elf $(SRC) $(LDFLAGS)

clean:
	@echo "Cleaning build folder..."
	rm -rf $(BUILD)
