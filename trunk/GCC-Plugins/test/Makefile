GCC=gcc-4.5.0
PLUGIN_SOURCE_FILES=test-plugin.c
PLUGIN_OBJECT_FILES=$(patsubst %.c,%.o,$(PLUGIN_SOURCE_FILES))
GCCPLUGINS_DIR:=$(shell $(GCC) -print-file-name=plugin)
CFLAGS+=-I$(GCCPLUGINS_DIR)/include -fPIC -O2 -ggdb3

plugin.so: $(PLUGIN_OBJECT_FILES)
	$(GCC) -shared $^ -o $@

.PHONY: all
all: plugin.so

.PHONY: tags
tags:
	ctags  -R --c-kinds=+pxl --fields=+aiKSz --extra=+fq `gcc-4.5.0 -print-file-name=plugin`/include

.PHONY: clean
clean:
	rm -f test-plugin.o
	rm -f test-plugin.so

.PHONY: prog
prog:
	$(GCC) -fplugin=./plugin.so -fplugin-arg-plugin-ref-pass-name=cfg -o fibonacci fibonacci.c fibonacci_main.c
