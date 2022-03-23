.PHONY: build init info user-setup

WORK_DIR := $(shell pwd)
QMK_HOME := $(WORK_DIR)/zsa/qmk_firmware

build:
	qmk compile -km default

init:
	git submodule sync --recursive
	git submodule update --init --recursive --progress

info:
	@echo QMK home: $(QMK_HOME)

user-setup:
	qmk config user.qmk_home=$(QMK_HOME)
	qmk config user.keyboard=moonlander
