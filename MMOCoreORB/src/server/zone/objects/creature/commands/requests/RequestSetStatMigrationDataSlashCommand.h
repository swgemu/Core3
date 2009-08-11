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

#ifndef REQUESTSETSTATMIGRATIONDATASLASHCOMMAND_H_

#define REQUESTSETSTATMIGRATIONDATASLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"

class RequestSetStatMigrationDataSlashCommand : public QueueCommand {
public:

	RequestSetStatMigrationDataSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	/**
	 * This method is fired when a player has requested that stat migration data be changed.
	 * For example: They have changed the data in the stat migration window, and have pressed
	 * okay rather than cancel.
	 * \param player The player that has set that stat migration data request.
	 * \param pack The packet.
	 */
	bool doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return false;

		if (!checkInvalidPostures(creature))
			return false;

		//This appears to be the ID of the target who's data is being set.
		/*uint64 targetID = packet->parseLong();

		UnicodeString stats = UnicodeString("");
		packet->parseUnicode(stats);

		StringTokenizer tokenizer(stats.toString());
		tokenizer.setDelimeter(" ");

		uint32 targetPointsTotal = 0;
		uint32 targetAttributes[9] = {0};

		for (int i = 0; tokenizer.hasMoreTokens(); i++) {
			uint32 value = tokenizer.getIntToken();

			if (value < player->getMinAttribute(i) && value > player->getMaxAttribute(i)) {
				player->info("Suspected stat migration hacking attempt.");
				return false;
			}

			targetAttributes[i] = value;
			targetPointsTotal += value;
		}

		//Here we set the stat migration target attributes.
		//NOTE: We aren't actually migrating the stats at this point.
		if (targetPointsTotal == player->getTotalAttribPoints()) {
			player->setMigrationHealth(targetAttributes[0]);
			player->setMigrationStrength(targetAttributes[1]);
			player->setMigrationConstitution(targetAttributes[2]);
			player->setMigrationAction(targetAttributes[3]);
			player->setMigrationQuickness(targetAttributes[4]);
			player->setMigrationStamina(targetAttributes[5]);
			player->setMigrationMind(targetAttributes[6]);
			player->setMigrationFocus(targetAttributes[7]);
			player->setMigrationWillpower(targetAttributes[8]);
		} else {
			player->error("Trying to set migratory stats without assigning all available points.");
			return false;
		}

		//Player is in the tutorial zone and is allowed to migrate stats.
		if (player->getZoneID() == 42)
			player->migrateStats();*/
		return true;
	}

};

#endif //REQUESTSETSTATMIGRATIONDATASLASHCOMMAND_H_

