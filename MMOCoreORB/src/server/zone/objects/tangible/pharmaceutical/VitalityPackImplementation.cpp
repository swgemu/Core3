/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "server/zone/objects/tangible/pharmaceutical/VitalityPack.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

void VitalityPackImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* player){
	TangibleObjectImplementation::fillAttributeList(msg, player);

	msg->insertAttribute("power", effectiveness);

}


int VitalityPackImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (player == NULL)
		return 0;

	if (!isASubChildOf(player))
		return 0;

	if (selectedID != 20)
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

	uint64 targetID = player->getTargetID();
	ZoneServer* server = player->getZoneServer();
	if (server == NULL)
		return 0;

	// Target must be a pet
	ManagedReference<TangibleObject*> target = server->getObject(targetID, true).castTo<TangibleObject*>();
	if (target == NULL || !target->isPet() ) {
		player->sendSystemMessage("You can only use this to restore vitality to pets");
		return 0;
	}

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(target.get());
	if( pet == NULL )
		return 0;

	ManagedReference<PetControlDevice*> controlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();
	if( controlDevice == NULL )
		return 0;

	// Check pet type
	Locker crossLock(controlDevice, _this.get() );
	if( controlDevice->getPetType() == PetManager::FACTIONPET ){
		player->sendSystemMessage("You cannot use this to restore vitality to that type of pet");
		return 0;
	}

	// Check owner
	uint64 ownerID = pet->getCreatureLinkID();
	if ( ownerID != player->getObjectID()){
		player->sendSystemMessage("You cannot revitalize another player's pet");
		return 0;
	}

	// Check pet and player states
	if( pet->isInCombat() || pet->isDead() || pet->isIncapacitated() || player->isInCombat() || player->isDead() || player->isIncapacitated()){
		player->sendSystemMessage("You can't restore vitality to your pet right now");
		return 0;
	}

	// Check that some vitality has been lost
	if( controlDevice->getVitality() >= controlDevice->getMaxVitality() ){
		player->sendSystemMessage("Pet is already at maximum vitality");
		return 0;
	}

	// Calculate vitality loss
	int vitalityLost = controlDevice->getMaxVitality() - controlDevice->getVitality();
	int vitalityLoss = 1;

	if (effectiveness < 45){
		vitalityLoss += (vitalityLost / 9) + (vitalityLost / 13);
	} else if (effectiveness < 75) {
		vitalityLoss += (vitalityLost / 19) + (vitalityLost / 28);
	} else {
		vitalityLoss += (vitalityLost / 29) + (vitalityLost / 43);
	}

	vitalityLoss *= ((vitalityLost - 1) / effectiveness) + 1;

	if( vitalityLoss >= controlDevice->getMaxVitality() ){
		vitalityLoss = controlDevice->getMaxVitality() - 1;
	}

	// Reduce max vitality
	controlDevice->setMaxVitality( controlDevice->getMaxVitality() - vitalityLoss );

	// Restore vitality to new max
	controlDevice->setVitality( controlDevice->getMaxVitality() );

	// Use a charge
	decreaseUseCount();

	player->sendSystemMessage("You restore your pet to " + String::valueOf( controlDevice->getMaxVitality() ) +
							  " vitality but it permanently lost " + String::valueOf( vitalityLoss ) + " vitality." );

	return 0;

}
