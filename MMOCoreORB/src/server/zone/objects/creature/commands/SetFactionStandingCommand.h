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

#ifndef SETFACTIONSTANDINGCOMMAND_H_
#define SETFACTIONSTANDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetFactionStandingCommand : public QueueCommand {
public:

	SetFactionStandingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	void sendInvalidParameterMessage(CreatureObject* creature){
		creature->sendSystemMessage("Invalid parameter. Format is /setFactionStanding <player> <rebel | imperial> <value>");
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//make sure that the target is a player
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == NULL || !obj->isPlayerCreature() ) {
			sendInvalidParameterMessage(creature);
			return INVALIDTARGET;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( obj.get());

		Locker _locker(targetCreature, creature);

		if ( targetCreature == NULL )
		{
			sendInvalidParameterMessage(creature);
			return GENERALERROR;
		}
		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		// try to get the faction
		if (!tokenizer.hasMoreTokens()) {
			sendInvalidParameterMessage(creature);
			return INVALIDPARAMETERS;
		}

		String faction;
		tokenizer.getStringToken(faction);

		// check for valid rebel/imperial faction specification
		if ( faction != "rebel" && faction != "imperial" ) {
			sendInvalidParameterMessage(creature);
			return INVALIDPARAMETERS;
		}

		// get the amount of faction points
		if (!tokenizer.hasMoreTokens())
		{
			sendInvalidParameterMessage(creature);
			return INVALIDPARAMETERS;
		}

		int factionValue = -1;

		try {
			factionValue = tokenizer.getIntToken();
		} catch ( Exception& err ) {
			error("error parsing faction value in setfactionstandingcommand");
		}

		PlayerObject* targetPlayer = targetCreature->getPlayerObject();

		if ( targetPlayer == NULL )
			return GENERALERROR;

		int intCurrentFaction = targetPlayer->getFactionStanding(faction);
		int factionDif = intCurrentFaction - factionValue;

		if ( factionValue >= 1 && factionValue <= 100000 && factionDif != 0) {
			if ( factionValue > intCurrentFaction)
				targetPlayer->increaseFactionStanding(faction,factionValue-intCurrentFaction);
			else
				targetPlayer->decreaseFactionStanding(faction, intCurrentFaction - factionValue);

			creature->sendSystemMessage("Faction standing set to " + String::valueOf(factionValue) + " for " + targetCreature->getFirstName());

		} else {
			if ( factionDif == 0 )
				creature->sendSystemMessage("No faction change");
			else
				creature->sendSystemMessage("Invalid faction amount.  Must be between 1 and 100k");
		}
		return SUCCESS;
	}

};

#endif //SETFACTIONSTANDINGCOMMAND_H_
