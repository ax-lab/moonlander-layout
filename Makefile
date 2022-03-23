.PHONY: build init info user-setup

WORK_DIR := $(shell pwd)
QMK_HOME := $(WORK_DIR)/zsa/qmk_firmware

KEYMAPS := $(QMK_HOME)/keyboards/moonlander/keymaps

build:
	$(call CLEAN)
	@echo Copying custom layouts...
	# @cp -p -r layouts/oryx-source $(KEYMAPS)
	# @qmk compile -km oryx-source
	@cp -p -r layouts/main $(KEYMAPS)
	@qmk compile -km main
	$(call COPY_BUILDS)
	$(call CLEAN)

clean:
	$(call CLEAN)
	@echo Removing .build dir...
	@rm -rf .build

init:
	git submodule sync --recursive
	git submodule update --init --recursive --progress

info:
	@echo "- QMK home: $(QMK_HOME)"
	@echo "- Keymaps:  $(KEYMAPS)"

user-setup:
	qmk config user.qmk_home=$(QMK_HOME)
	qmk config user.keyboard=moonlander

define COPY_BUILDS
	@echo Copying all build files to .build
	@mkdir -p .build
	@cp $(QMK_HOME)/.build/*.bin .build
endef

define CLEAN
	@echo Cleaning up custom layouts...
	@rm -rf $(KEYMAPS)/oryx-source
	@rm -rf $(KEYMAPS)/main
endef
