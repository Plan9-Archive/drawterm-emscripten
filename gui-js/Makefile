ROOT=..
include ../Make.config
LIB=libgui.a

OFILES=\
	js.$O\

default: $(LIB)
$(LIB): $(OFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

