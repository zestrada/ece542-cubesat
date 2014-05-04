OBJS=


#include common Makefile for default targets
include ../../Makefile.project
include $(MOBIUSROOT)/Cpp/BaseClasses/Makefile.common

BINDIR=
MAINLIB=-lgenMain
MAINLIB_debug=-lgenMain_debug
SIMLIB=gen
SIMLIB_debug=gen_debug
SIMLIB_trace=gen_trace
PROJECTLIBS=-lredundant_flash_studyRangeStudy -lredundant_flash_rewardPV -lredundant_flash_modelRJ -lram_systemSAN -lflash_systemSAN -lredundant_flash_systemSAN 
PROJECTLIBS_debug=-lredundant_flash_studyRangeStudy_debug -lredundant_flash_rewardPV_debug -lredundant_flash_modelRJ_debug -lram_systemSAN_debug -lflash_systemSAN_debug -lredundant_flash_systemSAN_debug 
MOBIUSLIBS=-lTRex -lStudy -lPV -lComposer_RepJoin -lSAN -lbase -lstate -lmobutil -ldist 
MOBIUSLIBS_debug=-lTRex_debug -lStudy_debug -lPV_debug -lComposer_RepJoin_debug -lSAN_debug -lbase_debug -lstate_debug -lmobutil_debug -ldist_debug 
USERDEFLIBNAME=
USERDEFLIBDIR=

all: normal

opt \
redundant_flash_ssgGen_$(ARCH): SUBMODELS/opt
	$(MAKE) exec3 "TARGET=redundant_flash_ssgGen_$(ARCH)" "USERLIBDIR=-L$(MOBIUSROOT)/Cpp/lib/$(PLATFORM)$(FORCE_ARCH) $(USERDEFLIBDIR)" "USERLIB=$(MAINLIB) -l$(SIMLIB) $(USERDEFLIBNAME) $(PROJECTLIBS) $(USERDEFLIBNAME) $(MOBIUSLIBS)" 

normal debug \
redundant_flash_ssgGen_$(ARCH)_debug: SUBMODELS/debug
	$(MAKE) exec3 "TARGET=redundant_flash_ssgGen_$(ARCH)_debug" "USERLIBDIR=-L$(MOBIUSROOT)/Cpp/lib/$(PLATFORM)$(FORCE_ARCH) $(USERDEFLIBDIR)" "USERLIB=$(MAINLIB_debug) -l$(SIMLIB_debug) $(USERDEFLIBNAME) $(PROJECTLIBS_debug) $(USERDEFLIBNAME) $(MOBIUSLIBS_debug) " "BUILDTARGET=_debug"

trace \
redundant_flash_ssgGen_$(ARCH)_trace:
	$(MAKE) exec3 "TARGET=redundant_flash_ssgGen_$(ARCH)_trace" "USERLIBDIR=-L$(MOBIUSROOT)/Cpp/lib/$(PLATFORM)$(FORCE_ARCH) $(USERDEFLIBDIR)" "USERLIB=$(MAINLIB_debug) -l$(SIMLIB_trace) $(USERDEFLIBNAME) $(PROJECTLIBS_debug) $(USERDEFLIBNAME) $(MOBIUSLIBS_debug) " "BUILDTARGET=_debug"

clean_sub_dirs:
	cd ../../Atomic/redundant_flash_system/ && $(MAKE) clean
	cd ../../Atomic/flash_system/ && $(MAKE) clean
	cd ../../Atomic/ram_system/ && $(MAKE) clean
	cd ../../Composed/redundant_flash_model/ && $(MAKE) clean
	cd ../../Reward/redundant_flash_reward/ && $(MAKE) clean
	cd ../../Study/redundant_flash_study/ && $(MAKE) clean

SUBMODELS/opt SUBMODELS/debug:
	@echo "NEW_SUBMODEL_LIB:[redundant_flash_system]"
	cd ../../Atomic/redundant_flash_system/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[flash_system]"
	cd ../../Atomic/flash_system/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[ram_system]"
	cd ../../Atomic/ram_system/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[redundant_flash_model]"
	cd ../../Composed/redundant_flash_model/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[redundant_flash_reward]"
	cd ../../Reward/redundant_flash_reward/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[redundant_flash_study]"
	cd ../../Study/redundant_flash_study/ && $(MAKE) $(@F)


