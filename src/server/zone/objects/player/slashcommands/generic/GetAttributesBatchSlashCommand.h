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

#ifndef GETATTRIBUTESBATCHSLASHCOMMAND_H_
#define GETATTRIBUTESBATCHSLASHCOMMAND_H_

#include "../../../scene/SceneObject.h"
#include "../../../creature/Creature.h"

class GetAttributesBatchSlashCommand : public SlashCommand {
public:

	GetAttributesBatchSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: SlashCommand(name, server) {

	}

	bool doSlashCommand(Player* player, Message* packet) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;


		packet->shiftOffset(8);

		UnicodeString objectid;
		packet->parseUnicode(objectid);

		StringTokenizer ids(objectid.toString());

		while (ids.hasMoreTokens()) {
			uint64 objid = 0;

			try {
				objid = ids.getLongToken();
			} catch (...) {
			}

			if (objid == 0)
				return false;

			Zone* zone = (Zone*) player->getZone();

			if (zone == NULL)
				return false;

			SceneObject* object = zone->lookupObject(objid);

			if (object == NULL) {
				object = player->getPlayerItem(objid);

				if (object == NULL) {
					SceneObject* target = player->getTarget();

					if (target != NULL && target != player) {
						if (target->isPlayer()) {
							Player* targetPlayer = (Player*) target;

							try {
								targetPlayer->wlock(player);

								object = targetPlayer->getPlayerItem(objid);

								targetPlayer->unlock();
							} catch (...) {
								targetPlayer->unlock();
							}
						} else if (target->isNonPlayerCreature()) {
							Creature* creature = (Creature*) target;

							try {
								creature->wlock(player);

								object = creature->getLootItem(objid);

								creature->unlock();
							} catch (...) {
								creature->unlock();
							}
						}
					}
				}
			}

			if (object != NULL) {

				object->generateAttributes(player);

			} else {

				AttributeListMessage* msg = new AttributeListMessage(objid);
				player->sendMessage(msg);
			}
		}
		return true;
	}

};

#endif //GETATTRIBUTESBATCHSLASHCOMMAND_H_
