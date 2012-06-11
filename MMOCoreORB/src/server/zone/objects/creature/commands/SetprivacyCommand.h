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

#ifndef SETPRIVACYCOMMAND_H_
#define SETPRIVACYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetprivacyCommand : public QueueCommand {
public:

	SetprivacyCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> obj = creature->getRootParent();

		if (obj == NULL || !obj->isBuildingObject()) {
			creature->sendSystemMessage("@player_structure:must_be_in_building"); //You must be in a building to do that.
			return INVALIDTARGET;
		}

		BuildingObject* building = cast<BuildingObject*>( obj.get());

		Locker clocker(building, creature);

		if (!building->isOnAdminList(creature)) {
			creature->sendSystemMessage("@player_structure:must_be_admin"); //You must be a building admin to do that.
			return INSUFFICIENTPERMISSION;
		}

		Reference<SharedBuildingObjectTemplate*> ssot = dynamic_cast<SharedBuildingObjectTemplate*>(building->getObjectTemplate());

		if (ssot == NULL || ssot->isAlwaysPublic()) {
			creature->sendSystemMessage("@player_structure:force_public"); //This structure is always public.
			return GENERALERROR;
		}

		for (int i = 1; i < building->getTotalCellNumber(); ++i) {
			ManagedReference<CellObject*> cell = building->getCell(i);

			if(cell == NULL)
				continue;

			for(int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				ManagedReference<SceneObject*> obj = cell->getContainerObject(j);

				if(obj != NULL && obj->isVendor()) {
					creature->sendSystemMessage("@player_structure:vendor_no_private"); // A structure hosting a vendor cannot be declared private
					return GENERALERROR;
				}
			}
		}

		if (building->togglePrivacy()) {
			creature->sendSystemMessage("@player_structure:structure_now_public"); //This structure is now public
		} else {
			creature->sendSystemMessage("@player_structure:structure_now_private"); //This structure is now private
		}

		building->broadcastCellPermissions();

		//TODO: Implement Messages
		//("@player_structure:vendor_no_private"); //A structure hosting a vendor cannot be declared private.
		//("@player_structure:no_privacy_faction_hq"); //You may not alter privacy of a factional headquarters.

		return SUCCESS;
	}

};

#endif //SETPRIVACYCOMMAND_H_
