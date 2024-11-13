.ONESHELL:
clean:
	@rm -rf dist/*

.ONESHELL:
all:
	clean
	build

.ONESHELL:
build:
	clean
	@gcc -fdiagnostics-color=always -I. -o dist/testDynamicArr `find . -name '*.c'`

.PHONY: build, all, clean