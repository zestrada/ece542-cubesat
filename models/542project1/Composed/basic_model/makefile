OBJS=basic_modelRJ.o 


#include common Makefile for default targets
include ../../Makefile.project
include $(MOBIUSROOT)/Cpp/BaseClasses/Makefile.common

all: normal
opt: $(ROOTDIR)/lib/$(PLATFORM)/libbasic_modelRJ.a
normal debug trace: $(ROOTDIR)/lib/$(PLATFORM)/libbasic_modelRJ_debug.a

$(ROOTDIR)/lib/$(PLATFORM)/libbasic_modelRJ.a: FORCE
	$(MAKE) lib TARGET=libbasic_modelRJ.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="" ROOTLIBDIR="."

$(ROOTDIR)/lib/$(PLATFORM)/libbasic_modelRJ_debug.a: FORCE
	$(MAKE) lib TARGET=libbasic_modelRJ_debug.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="_debug" ROOTLIBDIR="."

clean_sub_dirs:

