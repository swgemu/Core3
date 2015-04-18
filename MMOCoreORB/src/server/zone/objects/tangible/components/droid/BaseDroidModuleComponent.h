/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef BASEDROIDMODULECOMPONENT_H_
#define BASEDROIDMODULECOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {

class BaseDroidModuleComponent : public DataObjectComponent, public Logger {

protected:
	int species;

	// Radial IDs
	enum {
		AUTO_REPAIR_MODULE_TOGGLE = 180,
		ITEM_STORAGE_MODULE_OPEN  = 181,
		DATA_STORAGE_MODULE_OPEN  = 182,
		REPAIR_MODULE_ACTIVATE    = 183,
		REPAIR_MODULE_TRAIN       = 184,
		LOAD_STIMPACK             = 185,
		REQUEST_STIMPACK          = 186,
		MAINT_MODULE_ROOT         = 187,
		MAINT_MODULE_PERFORM      = 188,
		MAINT_MODULE_EDIT         = 189,
		EFFECTS_MODULE_TOGGLE     = 190,
		EFFECTS_MODULE_SLOT1      = 191,
		EFFECTS_MODULE_SLOT2      = 192,
		EFFECTS_MODULE_SLOT3      = 193,
		EFFECTS_MODULE_SLOT4      = 194,
		EFFECTS_MODULE_SLOT5      = 195,
		EFFECTS_MODULE_SLOT6      = 196,
		EFFECTS_MODULE_SLOT7      = 197,
		EFFECTS_MODULE_SLOT8      = 198,
		EFFECTS_MODULE_SLOT9      = 199,
		EFFECTS_MODULE_SLOT10     = 200,
		EFFECTS_MODULE_CONFIGURE  = 201,
		DETONATE_DROID            = 202,
		BARKER_STORE_WAYPOINT     = 203,
		BARKER_RECORD_MESSAGE     = 204,
		BARKER_TOGGLE             = 205,
		PLAYBACK_ACCESS_MENU      = 206,
		PLAYBACK_STOP_MENU        = 207,
		TRAP_MODULE_CONTROLS      = 208,
		TRAP_MODULE_CLEAR         = 209,
		TRAP_MODULE_TRAIN         = 210,
		HARVEST_MENU              = 211,
		HARVEST_TOGGLE            = 212,
		HARVEST_INTREST_RANDOM    = 213,
		HARVEST_INTREST_MEAT      = 214,
		HARVEST_INTREST_HIDE      = 215,
		HARVEST_INTREST_BONE      = 216,
		HARVEST_PROGRAM_COMMAND   = 217,
		HARVEST_SET_INTEREST      = 218
	};

public:
	BaseDroidModuleComponent();
	~BaseDroidModuleComponent();
	virtual String getModuleName();
	void initializeTransientMembers();
	// initialize the model based on the over all droid
	virtual void initialize(CreatureObject* droid);
	// attribultes to be added by module
	virtual void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	// add some object response menus
	virtual void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	// handle menu selections
	virtual int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	// add some skills to the player when active
	virtual void loadSkillMods(CreatureObject* player);
	// remove some skills mod when not active
	virtual void unloadSkillMods(CreatureObject* player);
	// check if skil mods of the module are based on range to the pet
	virtual bool skillsByRange();
	// Interface for Pet Manager to pass spacial commands to the droid for component processing
	virtual void handlePetCommand(String cmd, CreatureObject* speaker) ;
	// get drain amount when this module is active
	virtual int getBatteryDrain();
	// toggle this module form active to inactive i.e. auto harvest modules, barkers etc..
	virtual void deactivate();
	// does this module provide some kind of station effect
	virtual bool actsAsCraftingStation();
	// string rep of the module
	virtual String toString();
	virtual void onCall();
	virtual void onStore();
	virtual bool isDroidModuleData() { return true; }
	virtual bool isStackable() { return false; }
	virtual bool isCombatModule() { return false; }
	virtual void addToStack(BaseDroidModuleComponent* other) {}
	virtual void copy(BaseDroidModuleComponent* other){}
	ManagedReference<DroidObject*> getDroidObject();
	virtual void updateCraftingValues(CraftingValues* values, bool firstUpdate);
	virtual void setSpecies(int s) { species = s;}
};

} //droid
} //components
} //tangible
} //objects
} //zone
} //server
using namespace server::zone::objects::tangible::components::droid;
#endif /*BASEDROIDMODULECOMPONENT_H_*/
