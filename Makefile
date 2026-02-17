# PsvitaSpot full Makefile (C++ / VitaGL)

TARGET = PsvitaSpot
SRC = $(shell find src -name "*.cpp")        # all cpp files recursively
BUILD = build
RESOURCES = resources/*
PARAM_SFO = param.sfo

CXX = arm-vita-eabi-g++                     # use g++ for C++ sources
VITASDK ?= /usr/local/vitasdk

# Include paths for headers
CXXFLAGS = -O2 -Wall -Iinclude -I$(VITASDK)/include -I$(VITASDK)/include/vitagl
# Link paths for libraries
LDFLAGS = -L$(VITASDK)/lib -lvitagl

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
