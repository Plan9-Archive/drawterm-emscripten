# Unix
PTHREAD=-pthread	# for Mac
TOOLS=$(HOME)/Downloads/emsdk/emscripten/1.38.11
AR=ar
AS=NOPE
RANLIB=$(TOOLS)/emranlib
CC=$(TOOLS)/emcc
CFLAGS=-I$(ROOT) -I$(ROOT)/include -I$(ROOT)/kern -c  -O2
O=o
OS=js
GUI=js
LDADD=-lSDL
LDFLAGS=$(PTHREAD) -O2
TARG=drawterm.html
AUDIO=none

all: default

libmachdep.a:
	(cd js &&  make)
