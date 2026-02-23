TARGET = PsvitaSpot
TITLEID = PSPOT0001
PROJECT_SRC = $(shell find src -name "*.cpp")
OBJS = $(PROJECT_SRC:.cpp=.o)
BUILD = build
RESOURCES = resources
VITASDK ?= /usr/local/vitasdk
PREFIX = $(VITASDK)/bin/arm-vita-eabi
CXX = $(PREFIX)-g++
STRIP = $(PREFIX)-strip

CXXFLAGS = -O2 -Wall -Iinclude -I$(VITASDK)/arm-vita-eabi/include -std=c++17

LDFLAGS = -L$(VITASDK)/arm-vita-eabi/lib \
	-lvitaGL \
	-lvitashark \
	-lSceShaccCgExt_stub \
	-lSceShaccCg_stub \
	-ltaihen_stub \
	-lSceAppMgr_stub \
	-lSceAppUtil_stub \
	-lSceAudio_stub \
	-lSceCtrl_stub \
	-lSceCommonDialog_stub \
	-lSceDisplay_stub \
	-lSceGxm_stub \
	-lSceSysmodule_stub \
	-lSceTouch_stub \
	-lSceNet_stub \
	-lSceNetCtl_stub \
	-lSceHttp_stub \
	-lm \
	-lpthread

all: $(BUILD)/$(TARGET).vpk

$(BUILD)/$(TARGET).vpk: $(BUILD)/eboot.bin $(BUILD)/sce_sys/param.sfo
	@echo "Packing VPK..."
	@mkdir -p $(BUILD)/sce_sys
	@if [ -d "$(RESOURCES)" ]; then cp -r $(RESOURCES)/* $(BUILD)/; fi
	cd $(BUILD) && zip -r $(TARGET).vpk . -i eboot.bin -i "sce_sys/*" $(shell [ -d "$(RESOURCES)" ] && echo "-i resources/*")

$(BUILD)/sce_sys/param.sfo: $(BUILD)/$(TARGET).velf
	@echo "Creating param.sfo..."
	@mkdir -p $(BUILD)/sce_sys
	vita-mksfoex -s TITLEID="$(TITLEID)" "$(TARGET)" $@

$(BUILD)/eboot.bin: $(BUILD)/$(TARGET).velf
	@echo "Creating eboot.bin..."
	vita-make-fself -c $< $@

$(BUILD)/$(TARGET).velf: $(BUILD)/$(TARGET).elf
	@echo "Creating VELF..."
	vita-elf-create $< $@

$(BUILD)/$(TARGET).elf: $(PROJECT_SRC)
	@mkdir -p $(BUILD)
	@echo "Compiling ELF..."
	$(CXX) $(CXXFLAGS) -o $@ $(PROJECT_SRC) $(LDFLAGS)

clean:
	@echo "Cleaning build folder..."
	@rm -rf $(BUILD)

.PHONY: all clean
