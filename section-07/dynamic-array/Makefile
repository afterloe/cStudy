.PHONY: all
.ONESHELL:
all: clean build

.PHONY: clean
.ONESHELL:
clean:
	@rm -rf dist/*

.PHONY: build clean
.ONESHELL:
build: clean
	@gcc -fdiagnostics-color=always -I. -o dist/testDynamicArr `find . -name '*.c'`