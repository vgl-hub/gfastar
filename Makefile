CXX = g++
INCLUDE_DIR = -I./include
WARNINGS = -Wall -Wextra

CXXFLAGS = -g -std=gnu++14 -O3 $(INCLUDE_DIR) $(WARNINGS)

TARGET = gfastar
BUILD = build/bin
SOURCE = src
INCLUDE = include
LDFLAGS :=

GFASTATS_SUBDIR := $(CURDIR)/gfastats
GFASTATS_LIBSFILES := $(GFASTATS_SUBDIR)/$(SOURCE)/* $(GFASTATS_SUBDIR)/$(INCLUDE)/*

RDEVAL_SUBDIR := $(CURDIR)/rdeval
RDEVAL_LIBSFILES := $(RDEVAL_SUBDIR)/$(SOURCE)/* $(RDEVAL_SUBDIR)/$(INCLUDE)/*

GFALIGN_SUBDIR := $(CURDIR)/gfalign
GFALIGN_LIBSFILES := $(GFALIGN_SUBDIR)/$(SOURCE)/* $(GFALIGN_SUBDIR)/$(INCLUDE)/*

main: $(SOURCE)/main.cpp $(GFASTATS_LIBSFILES) $(RDEVAL_LIBSFILES) $(GFALIGN_LIBSFILES) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SOURCE)/main.cpp -o $(BUILD)/$(TARGET)

$(GFASTATS_LIBSFILES): gfastats
	@# Do nothing
	
$(RDEVAL_LIBSFILES): rdeval
	@# Do nothing
	
$(GFALIGN_LIBSFILES): gfalign
	@# Do nothing

.PHONY: gfastats
gfastats:
	$(MAKE) -j -C $(GFASTATS_SUBDIR)
	
.PHONY: rdeval
rdeval:
	$(MAKE) -j -C $(RDEVAL_SUBDIR)
	
.PHONY: gfalign
gfalign:
	$(MAKE) -j -C $(GFALIGN_SUBDIR)
	
$(BUILD):
	-mkdir -p $@
	
clean:
	$(MAKE) -j -C $(GFASTATS_SUBDIR) clean
	$(MAKE) -j -C $(RDEVAL_SUBDIR) clean
	$(MAKE) -j -C $(GFALIGN_SUBDIR) clean
	$(RM) -r build
