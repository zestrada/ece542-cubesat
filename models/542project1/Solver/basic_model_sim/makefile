OBJS=


#include common Makefile for default targets
include ../../Makefile.project
include $(MOBIUSROOT)/Cpp/BaseClasses/Makefile.common

BINDIR=
MAINLIB=-lsimMain
MAINLIB_debug=-lsimMain_debug
SIMLIB=sim
SIMLIB_debug=sim_debug
SIMLIB_trace=sim_trace
PROJECTLIBS=-lbasic_model_studyRangeStudy -lbasic_rewardPV -lbasic_modelRJ -lram_systemSAN -lflash_systemSAN 
PROJECTLIBS_debug=-lbasic_model_studyRangeStudy_debug -lbasic_rewardPV_debug -lbasic_modelRJ_debug -lram_systemSAN_debug -lflash_systemSAN_debug 
MOBIUSLIBS=-lTRex -lStudy -lPV -lComposer_RepJoin -lSAN -lbase -lstate -lmobutil -ldist 
MOBIUSLIBS_debug=-lTRex_debug -lStudy_debug -lPV_debug -lComposer_RepJoin_debug -lSAN_debug -lbase_debug -lstate_debug -lmobutil_debug -ldist_debug 
USERDEFLIBNAME=
USERDEFLIBDIR=

all: normal

opt \
basic_model_simSim_$(ARCH): SUBMODELS/opt
	$(MAKE) exec3 "TARGET=basic_model_simSim_$(ARCH)" "USERLIBDIR=-L$(MOBIUSROOT)/Cpp/lib/$(PLATFORM)$(FORCE_ARCH) $(USERDEFLIBDIR)" "USERLIB=$(MAINLIB) -l$(SIMLIB) $(USERDEFLIBNAME) $(PROJECTLIBS) $(USERDEFLIBNAME) $(MOBIUSLIBS)" 

normal debug \
basic_model_simSim_$(ARCH)_debug: SUBMODELS/debug
	$(MAKE) exec3 "TARGET=basic_model_simSim_$(ARCH)_debug" "USERLIBDIR=-L$(MOBIUSROOT)/Cpp/lib/$(PLATFORM)$(FORCE_ARCH) $(USERDEFLIBDIR)" "USERLIB=$(MAINLIB_debug) -l$(SIMLIB_debug) $(USERDEFLIBNAME) $(PROJECTLIBS_debug) $(USERDEFLIBNAME) $(MOBIUSLIBS_debug) " "BUILDTARGET=_debug"

trace \
basic_model_simSim_$(ARCH)_trace:
	$(MAKE) exec3 "TARGET=basic_model_simSim_$(ARCH)_trace" "USERLIBDIR=-L$(MOBIUSROOT)/Cpp/lib/$(PLATFORM)$(FORCE_ARCH) $(USERDEFLIBDIR)" "USERLIB=$(MAINLIB_debug) -l$(SIMLIB_trace) $(USERDEFLIBNAME) $(PROJECTLIBS_debug) $(USERDEFLIBNAME) $(MOBIUSLIBS_debug) " "BUILDTARGET=_debug"

clean_sub_dirs:
	cd ../../Atomic/flash_system/ && $(MAKE) clean
	cd ../../Atomic/ram_system/ && $(MAKE) clean
	cd ../../Composed/basic_model/ && $(MAKE) clean
	cd ../../Reward/basic_reward/ && $(MAKE) clean
	cd ../../Study/basic_model_study/ && $(MAKE) clean

SUBMODELS/opt SUBMODELS/debug:
	@echo "NEW_SUBMODEL_LIB:[flash_system]"
	cd ../../Atomic/flash_system/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[ram_system]"
	cd ../../Atomic/ram_system/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[basic_model]"
	cd ../../Composed/basic_model/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[basic_reward]"
	cd ../../Reward/basic_reward/ && $(MAKE) $(@F)
	@echo "NEW_SUBMODEL_LIB:[basic_model_study]"
	cd ../../Study/basic_model_study/ && $(MAKE) $(@F)


