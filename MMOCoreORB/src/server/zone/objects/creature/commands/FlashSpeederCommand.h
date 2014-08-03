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

#ifndef FLASHSPEEDERCOMMAND_H_
#define FLASHSPEEDERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/ReplaceFlashSpeederSuiCallback.h"

class FlashSpeederCommand : public QueueCommand {
public:

	FlashSpeederCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		if( !player->isPlayerCreature() )
			return GENERALERROR;

		if( player->getPlayerObject() == NULL )
			return GENERALERROR;

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");
		if (datapad == NULL)
			return GENERALERROR;

		// Find the first disabled flash speeder in player's datapad
		bool hasFlash = false;
		VehicleControlDevice* device;
		ManagedReference<SceneObject*> sceno;
		ManagedReference<VehicleObject*> vehicle;
		for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

			if (object->isVehicleControlDevice()) {
				device = cast<VehicleControlDevice*>( object.get());

				sceno = device->getControlledObject();
				if (sceno != NULL && sceno->getObjectTemplate()->getFullTemplateString() == "object/mobile/vehicle/speederbike_flash.iff") {

					vehicle = cast<VehicleObject*>(sceno.get());
					if( vehicle != NULL && vehicle->isDestroyed() ){
						hasFlash = true;
						break;
					}
				}
			}
		}

		// Player must have a disabled flash speeder in their datapad
		if( !hasFlash ){
			player->sendSystemMessage( "@veteran:flash_speeder_not_eligible" ); //	"You are not eligible to receive a Flash Speeder"
			return GENERALERROR;
		}

		// Player must have 20k credits
		if( player->getBankCredits() < 20000 ){
			player->sendSystemMessage( "@veteran:flash_speeder_no_credits" ); // "You do not have enough credits to receive a replacement."
			return GENERALERROR;
		}

		// Build and send confirmation window
		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::CONFIRM_FLASH_SPEEDER_REPAIR);
		suiBox->setCallback(new ReplaceFlashSpeederSuiCallback(server->getZoneServer()));
		suiBox->setPromptTitle("Confirm Flash Speeder Replacement");
		suiBox->setPromptText( "@veteran:flash_speeder_replace_prompt" );  // "A replacement Flash Speeder is available at the cost of 20000 credits. Are you sure you want a new speeder?"
		suiBox->setCancelButton(true, "@no");
		suiBox->setOkButton(true, "@yes");
		suiBox->setUsingObject(device);

		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());

		return SUCCESS;
	}

};

#endif //FLASHSPEEDERCOMMAND_H_
