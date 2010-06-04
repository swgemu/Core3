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

#ifndef MOVEFURNITURECOMMAND_H_
#define MOVEFURNITURECOMMAND_H_

#include "../../scene/SceneObject.h"

class MoveFurnitureCommand : public QueueCommand {
public:

	MoveFurnitureCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		String dir;

		//TODO: Return a usage message?
		if (!tokenizer.hasMoreTokens())
			return false;

		tokenizer.getStringToken(dir);

		if (dir != "up" && dir != "down" && dir != "forward" && dir != "back")
			return false;

		if (!tokenizer.hasMoreTokens())
			return false;

		int dist = tokenizer.getIntToken();

		if (dist < 1 || dist > 10)
			return false;

		ZoneServer* zoneServer = creature->getZoneServer();
		ManagedReference<SceneObject*> obj = zoneServer->getObject(target);

		if (obj == NULL)
			return false;

		int degrees = creature->getDirectionAngle();

		float offsetX = dist * sin(Math::deg2rad(degrees));
		float offsetY = dist * cos(Math::deg2rad(degrees));

		float x = obj->getPositionX();
		float y = obj->getPositionY();
		float z = obj->getPositionZ();

		if (dir == "forward" || dir == "back") {
			x += offsetX;
			y += offsetY;
		} else {
			if (dir == "up")
				z += dist;
			else
				z -= dist;
		}

		//TODO: Check to make sure the item is not being moved outside the range of the cell.

		obj->setPosition(x, z, y);

		if (obj->getParent() != NULL)
			obj->updateZoneWithParent(obj->getParent(), true);
		else
			obj->updateZone(true);

		if (obj->getParent() != NULL)
			obj->updateZoneWithParent(obj->getParent(), true);
		else
			obj->updateZone(true);

		return SUCCESS;
	}

};

#endif //MOVEFURNITURECOMMAND_H_
