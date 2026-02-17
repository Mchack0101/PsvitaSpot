# PsvitaSpot Makefile (C++ / VitaGL in VitaSDK include)
TARGET = PsvitaSpot
PROJECT_SRC = $(shell find src -name "*.cpp")
VITAGL_SRC = $(shell find $(VITASDK)/include/vitaGL/source -name "*.c" -o -name "*.cpp")
SRC = $(PROJECT_SRC) $(VITAGL_SRC)
BUILD = build
RESOURCES = resources/*
PARAM_SFO = param.sfo

CXX = arm-vita-eabi-g++               # C++ compiler
VITASDK ?= /usr/local/vitasdk

# Include paths
CXXFLAGS = -O2 -Wall -Iinclude -I$(VITASDK)/include -I$(VITASDK)/include/vitaGL
LDFLAGS =                              # no separate lib needed

all: $(BUILD)/$(TARGET).vpk

# Package VPK
$(BUILD)/$(TARGET).vpk: $(BUILD)/$(TARGET).elf
	@echo "Packing VPK..."
	vita-mksfoex $(PARAM_SFO) $(BUILD)/$(TARGET).elf
	vita-pack-vpk $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).vpk $(RESOURCES)

# Compile ELF
$(BUILD)/$(TARGET).elf: $(SRC)
	@mkdir -p $(BUILD)
	@echo "Compiling ELF..."
	$(CXX) $(CXXFLAGS) -o $(BUILD)/$(TARGET).elf $(SRC) $(LDFLAGS)

# Clean build folder
clean:
	@echo "Cleaning build folder..."
	rm -rf $(BUILD)
