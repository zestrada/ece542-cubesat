#include "Composed/basic_model/basic_modelRJ.h"
char * basic_modelRJ__SharedNames[] = {"flash_corrupted"};

basic_modelRJ::basic_modelRJ():Join("Join1", 2, 1,basic_modelRJ__SharedNames) {
  flash_system = new flash_systemSAN();
  ModelArray[0] = (BaseModelClass*) flash_system;
  ModelArray[0]->DefineName("flash_system");
  ram_system = new ram_systemSAN();
  ModelArray[1] = (BaseModelClass*) ram_system;
  ModelArray[1]->DefineName("ram_system");

  SetupActions();
  if (AllChildrenEmpty())
    NumSharedStateVariables = 0;
  else {
    //**************  State sharing info  **************
    //Shared variable 0
    flash_corrupted = new Place("flash_corrupted");
    addSharedPtr(flash_corrupted, "flash_corrupted" );
    if (flash_system->NumStateVariables > 0) {
      flash_corrupted->ShareWith(flash_system->flash_corrupted);
      addSharingInfo(flash_system->flash_corrupted, flash_corrupted, flash_system);
    }
    if (ram_system->NumStateVariables > 0) {
      flash_corrupted->ShareWith(ram_system->flash_corrupted);
      addSharingInfo(ram_system->flash_corrupted, flash_corrupted, ram_system);
    }

  }

  Setup();
}

basic_modelRJ::~basic_modelRJ() {
  if (!AllChildrenEmpty()) {
    delete flash_corrupted;
  }
  delete flash_system;
  delete ram_system;
}
