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

#ifndef STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_
#define STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class StructurePayUncondemnMaintenanceSuiCallback : public SuiCallback {
public:
	StructurePayUncondemnMaintenanceSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isStructureObject()) {
			return; //TODO: What message should be shown here?
		}

		StructureObject* structure = cast<StructureObject*>(obj.get());

		if (structure == NULL) {
			return; //TODO: What message should be shown here?
		}

		//Creature is already locked (done in handleSuiEventNotification in SuiManager).
		Locker _lock(structure, creature);

		int uncondemnCost = -structure->getSurplusMaintenance();

		if (creature->getBankCredits() + creature->getCashCredits() < uncondemnCost) {
			//TODO: add error message;
			return;
		}

		structure->payMaintenance(uncondemnCost, creature, false);

		//Give the player 10 minutes to pay more maintenance before sending out new mails.
		structure->scheduleMaintenanceTask(10 * 60);

		if (structure->isBuildingObject()) {
			BuildingObject* building = cast<BuildingObject* >(structure);

			if (building != NULL) {
				//Remove ***** Condemned Structure ***** sign name.
				building->updateSignName(true);
			}
		}

		StringIdChatParameter message("@player_structure:structure_uncondemned");
		creature->sendSystemMessage(message);
	}
};

#endif /* STRUCTUREPAYUNCONDEMNMAINTENANCESUICALLBACK_H_ */
