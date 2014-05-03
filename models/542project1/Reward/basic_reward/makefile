OBJS=basic_rewardPVNodes.o basic_rewardPVModel.o 


#include common Makefile for default targets
include ../../Makefile.project
include $(MOBIUSROOT)/Cpp/BaseClasses/Makefile.common

all: normal
opt: $(ROOTDIR)/lib/$(PLATFORM)/libbasic_rewardPV.a
normal debug trace: $(ROOTDIR)/lib/$(PLATFORM)/libbasic_rewardPV_debug.a

$(ROOTDIR)/lib/$(PLATFORM)/libbasic_rewardPV.a: FORCE
	$(MAKE) lib TARGET=libbasic_rewardPV.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="" ROOTLIBDIR="."

$(ROOTDIR)/lib/$(PLATFORM)/libbasic_rewardPV_debug.a: FORCE
	$(MAKE) lib TARGET=libbasic_rewardPV_debug.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="_debug" ROOTLIBDIR="."

clean_sub_dirs:

