OBJS=basic_model_studyRangeStudy.o 


#include common Makefile for default targets
include ../../Makefile.project
include $(MOBIUSROOT)/Cpp/BaseClasses/Makefile.common

all: normal
opt: $(ROOTDIR)/lib/$(PLATFORM)/libbasic_model_studyRangeStudy.a
normal debug trace: $(ROOTDIR)/lib/$(PLATFORM)/libbasic_model_studyRangeStudy_debug.a

$(ROOTDIR)/lib/$(PLATFORM)/libbasic_model_studyRangeStudy.a: FORCE
	$(MAKE) lib TARGET=libbasic_model_studyRangeStudy.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="" ROOTLIBDIR="."

$(ROOTDIR)/lib/$(PLATFORM)/libbasic_model_studyRangeStudy_debug.a: FORCE
	$(MAKE) lib TARGET=libbasic_model_studyRangeStudy_debug.a OBJS="$(OBJS)" USERINCLUDE="$(USERINCLUDE)" TYPE="_debug" ROOTLIBDIR="."

clean_sub_dirs:

