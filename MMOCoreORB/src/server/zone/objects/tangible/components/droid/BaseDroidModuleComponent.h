/*
 * Copyright (C) 2014 <SWGEmu>
 * This File is part of Core3.
 * This program is free software; you can redistribute
 * it and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program; if not, write to
 * the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Linking Engine3 statically or dynamically with other modules
 * is making a combined work based on Engine3.
 * Thus, the terms and conditions of the GNU Lesser General Public License
 * cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of Engine3
 * give you permission to combine Engine3 program with free software
 * programs or libraries that are released under the GNU LGPL and with
 * code included in the standard release of Core3 under the GNU LGPL
 * license (or modified versions of such code, with unchanged license).
 * You may copy and distribute such a system following the terms of the
 * GNU LGPL for Engine3 and the licenses of the other code concerned,
 * provided that you include the source code of that other code when
 * and as the GNU LGPL requires distribution of source code.
 *
 * Note that people who make modified versions of Engine3 are not obligated
 * to grant this special exception for their modified versions;
 * it is their choice whether to do so. The GNU Lesser General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 */

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
	static const uint8 AUTO_REPAIR_MODULE_TOGGLE = 180;
	static const uint8 ITEM_STORAGE_MODULE_OPEN  = 181;
	static const uint8 DATA_STORAGE_MODULE_OPEN  = 182;
	static const uint8 REPAIR_MODULE_ACTIVATE  = 183;
	static const uint8 REPAIR_MODULE_TRAIN  = 184;
	static const uint8 LOAD_STIMPACK = 185;
	static const uint8 REQUEST_STIMPACK = 186;
	static const uint8 MAINT_MODULE_ROOT = 187;
	static const uint8 MAINT_MODULE_PERFORM = 188;
	static const uint8 MAINT_MODULE_EDIT = 189;
	static const uint8 EFFECTS_MODULE_TOGGLE = 190;
	static const uint8 EFFECTS_MODULE_SLOT1 = 191;
	static const uint8 EFFECTS_MODULE_SLOT2 = 192;
	static const uint8 EFFECTS_MODULE_SLOT3 = 193;
	static const uint8 EFFECTS_MODULE_SLOT4 = 194;
	static const uint8 EFFECTS_MODULE_SLOT5 = 195;
	static const uint8 EFFECTS_MODULE_SLOT6 = 196;
	static const uint8 EFFECTS_MODULE_SLOT7 = 197;
	static const uint8 EFFECTS_MODULE_SLOT8 = 198;
	static const uint8 EFFECTS_MODULE_SLOT9 = 199;
	static const uint8 EFFECTS_MODULE_SLOT10 = 200;
	static const uint8 EFFECTS_MODULE_CONFIGURE = 201;
	static const uint8 DETONATE_DROID = 202;
	static const uint8 BARKER_STORE_WAYPOINT = 203;
	static const uint8 BARKER_RECORD_MESSAGE = 204;
	static const uint8 BARKER_TOGGLE = 205;
	static const uint8 PLAYBACK_ACCESS_MENU = 206;
	static const uint8 PLAYBACK_STOP_MENU = 207;
	static const uint8 TRAP_MODULE_CONTROLS = 208;
	static const uint8 TRAP_MODULE_CLEAR = 209;
	static const uint8 TRAP_MODULE_TRAIN = 210;
	static const uint8 HARVEST_MENU = 211;
	static const uint8 HARVEST_TOGGLE = 212;
	static const uint8 HARVEST_INTREST_RANDOM = 213;
	static const uint8 HARVEST_INTREST_MEAT = 214;
	static const uint8 HARVEST_INTREST_HIDE = 215;
	static const uint8 HARVEST_INTREST_BONE = 216;
	static const uint8 HARVEST_PROGRAM_COMMAND = 217;
	static const uint8 HARVEST_SET_INTEREST = 218;

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
