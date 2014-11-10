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

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {

class BaseDroidModuleComponent : public DataObjectComponent, public Logger {
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
	virtual void handlePetCommand(String cmd, CreatureObject* owner) ;
	// get drain amount when this module is active
	virtual int getBatteryDrain();
	// toggle this module form active to inactive i.e. auto harvest modules, barkers etc..
	virtual void toggleActive();
	// does this module provide some kind of station effect
	virtual bool actsAsCraftingStation();
	// string rep of the module
	virtual String toString();
	virtual void onCall();
	virtual void onStore();
	virtual bool isDroidModuleData() { return true; }
};

} //droid
} //components
} //tangible
} //objects
} //zone
} //server
using namespace server::zone::objects::tangible::components::droid;
#endif /*BASEDROIDMODULECOMPONENT_H_*/
