TARGET := sourcmappings_finder
BIN_DIR := bin
TESTS_DIR := $(BIN_DIR)/tests

all: createdirs build 

OS = linux
ARCH = amd64

MAIN_PACKAGE_FILES := main.go
OBJECTS := $(MAIN_PACKAGE_FILES)
build: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	GOOS=$(OS) GOARCH=$(ARCH) go build -o $@ -v $^ 

.PHONY: clean
clean:
	@rm $(BIN_DIR)/$(TARGET)

.PHONY: createdirs
createdirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(TESTS_DIR)

.PHONY: mrproper
mrproper:
	@rm -rf $(BIN_DIR)
	@rm -rf vendor
