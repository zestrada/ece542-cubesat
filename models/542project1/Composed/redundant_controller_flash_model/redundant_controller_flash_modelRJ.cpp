#include "Composed/redundant_controller_flash_model/redundant_controller_flash_modelRJ.h"
char * redundant_controller_flash_modelRJ__SharedNames[] = {"flash_corrupted"};

redundant_controller_flash_modelRJ::redundant_controller_flash_modelRJ():Join("Join", 2, 1,redundant_controller_flash_modelRJ__SharedNames) {
  ram_system = new ram_systemSAN();
  ModelArray[0] = (BaseModelClass*) ram_system;
  ModelArray[0]->DefineName("ram_system");
  flash_rep = new redundant_controller_flash_modelRJ__flash_rep();
  ModelArray[1] = (BaseModelClass*) flash_rep;
  ModelArray[1]->DefineName("flash_rep");

  SetupActions();
  if (AllChildrenEmpty())
    NumSharedStateVariables = 0;
  else {
    //**************  State sharing info  **************
    //Shared variable 0
    flash_corrupted = new Place("flash_corrupted");
    addSharedPtr(flash_corrupted, "flash_corrupted" );
    if (ram_system->NumStateVariables > 0) {
      flash_corrupted->ShareWith(ram_system->flash_corrupted);
      addSharingInfo(ram_system->flash_corrupted, flash_corrupted, ram_system);
    }
    if (flash_rep->NumStateVariables > 0) {
      flash_corrupted->ShareWith(flash_rep->flash_corrupted);
      addSharingInfo(flash_rep->flash_corrupted, flash_corrupted, flash_rep);
    }

  }

  Setup();
}

redundant_controller_flash_modelRJ::~redundant_controller_flash_modelRJ() {
  if (!AllChildrenEmpty()) {
    delete flash_corrupted;
  }
  delete ram_system;
  delete flash_rep;
}
