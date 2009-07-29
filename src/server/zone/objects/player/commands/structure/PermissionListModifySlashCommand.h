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

#ifndef PERMISSIONLISTMODIFYSLASHCOMMAND_H_

#define PERMISSIONLISTMODIFYSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
//#include "../../../structure/building/BuildingObject.h"
//#include "../../../structure/installation/InstallationObject.h"
//#include "../../../structure/StructurePermissionList.h"

class PermissionListModifySlashCommand : public QueueCommand {
public:

	PermissionListModifySlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	bool doSlashCommand(PlayerCreature* player, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;

		/*packet->shiftOffset(8); //Skip players objectid.

		UnicodeString arguments;
		packet->parseUnicode(arguments);

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		String playername;
		String listname;
		String action;

		tokenizer.getStringToken(playername);
		tokenizer.getStringToken(listname);
		tokenizer.getStringToken(action);

		bool add = (action.compareTo("add") == 0);

		SceneObject* targetObject = player->getTarget();

		//Check to see if they have an installation targetted first.
		if (targetObject != NULL && targetObject->isTangible() && ((TangibleObject*)targetObject)->isInstallation()) {
			InstallationObject* installation = (InstallationObject*) targetObject;

			if (installation->isOnAdminList(player)) {
				//Found a targetted installation and player is on the adminlist.
				installation->modifyPermissionList(player, listname, playername, add);
				return true;
			}
		}

		//If they are in a building, try to use it.
		if (player->isInBuilding()) {
			BuildingObject* building = (BuildingObject*) player->getBuilding();

			if (building != NULL && building->isOnAdminList(player)) {
				building->modifyPermissionList(player, listname, playername, add);
				return true;
			}
		}

		//Search for a nearby installation that they might be referring to.
		for (int i = 0; i < player->inRangeObjectCount(); i++) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (object->isTangible() && ((TangibleObject*)object)->isInstallation()) {
				InstallationObject* installation = (InstallationObject*) object;

				if (installation->isOnAdminList(player)) {
					//Found a nearby installation that player is on the admin list.
					installation->modifyPermissionList(player, listname, playername, add);
					return true;
				}
			}
		}

		player->sendSystemMessage("@player_structure:no_building"); //You must be in a building, be near an installation, or have one targeted to do that.
		*/return false;
	}

};

#endif //PERMISSIONLISTMODIFYSLASHCOMMAND_H_

