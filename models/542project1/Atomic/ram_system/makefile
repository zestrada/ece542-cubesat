OBJS=ram_systemSAN.o 


#include common Makefile for default targets
include ../../Makefile.project
include $(MOBIUSROOT)/Cpp/BaseClasses/Makefile.common

all: normal
opt: $(ROOTDIR)/lib/$(PLATFORM)/libram_systemSAN.a
normal debug trace: $(ROOTDIR)/lib/$(PLATFORM)/libram_systemSAN_debug.a

$(ROOTDIR)/lib/$(PLATFORM)/libram_systemSAN.a: FORCE
	$(MAKE) lib TARGET=libram_systemSAN.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="" ROOTLIBDIR="."

$(ROOTDIR)/lib/$(PLATFORM)/libram_systemSAN_debug.a: FORCE
	$(MAKE) lib TARGET=libram_systemSAN_debug.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="_debug" ROOTLIBDIR="."

clean_sub_dirs:

