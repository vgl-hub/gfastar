CXX = g++
INCLUDE_DIR = -I./include
WARNINGS = -Wall -Wextra

CXXFLAGS = -g -std=gnu++14 -O3 $(INCLUDE_DIR) $(WARNINGS)

TARGET = gfastar
BUILD = build/bin
SOURCE = src
INCLUDE = include

GFASTATS_SUBDIR := $(CURDIR)/gfastats
LDFLAGS :=

GFASTATS_LIBSFILES := $(GFASTATS_SUBDIR)/$(SOURCE)/* $(GFASTATS_SUBDIR)/$(INCLUDE)/*

main: $(SOURCE)/main.cpp $(GFASTATS_LIBSFILES) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SOURCE)/main.cpp -o $(BUILD)/$(TARGET)

$(GFASTATS_LIBSFILES): gfastats
	@# Do nothing

.PHONY: gfastats
gfastats:
	$(MAKE) -C $(GFASTATS_SUBDIR)
	
$(BUILD):
	-mkdir -p $@
	
clean:
	$(MAKE) -C $(GFASTATS_SUBDIR) clean
	$(RM) -r build
