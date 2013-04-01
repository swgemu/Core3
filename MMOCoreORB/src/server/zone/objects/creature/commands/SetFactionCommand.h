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

#ifndef SETFACTIONCOMMAND_H_
#define SETFACTIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"

class SetFactionCommand : public QueueCommand {
public:

	SetFactionCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == NULL || !obj->isTangibleObject())
			return INVALIDTARGET;

		TangibleObject* tano = cast<TangibleObject*>( obj.get());

		uint32 pvpStatus = tano->getPvpStatusBitmask();
		uint32 optionsBitmask = tano->getOptionsBitmask();
		uint32 intFaction = tano->getFaction();

		ManagedReference<CreatureObject*> pobj = cast<CreatureObject*>( obj.get());
		ManagedReference<PlayerObject*> targetPlayerObject = NULL;



		if (pobj != NULL)
			targetPlayerObject = pobj->getPlayerObject();



		//First, check if they passed a name with the command.
		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		// if no parameters are given, just send the flags
		if (!tokenizer.hasMoreTokens()){
			StringBuffer msg;
			msg << "PvPStatusbitmask = " << String::valueOf(pvpStatus) << endl;
			msg << "Optionsbitmask = " << String::valueOf(optionsBitmask) << endl;
			msg <<  "Faction = " << String::valueOf(intFaction) << endl;


			if(targetPlayerObject != NULL)
				msg << "Faction Status: " << String::valueOf(targetPlayerObject->getFactionStatus());

			creature->sendSystemMessage(msg.toString());
			return SUCCESS;
		}


		String faction;
		tokenizer.getStringToken(faction);

		if(!tokenizer.hasMoreTokens()){
			creature->sendSystemMessage("SYNTAX: /setfaction <name> [imperial | rebel | neutral] [onleave | covert | overt ]");
			return INVALIDPARAMETERS;
		}
		Locker _lock(tano,creature);

		if (faction == "neutral")
			tano->setFaction(0);

		if (faction == "imperial" || faction == "rebel" || faction == "hutt")
			tano->setFaction(faction.hashCode());


		if (tokenizer.hasMoreTokens()) {
			//The next argument should be whether they are overt, onleave, or covert
			String status;
			tokenizer.getStringToken(status);



			if (targetPlayerObject != NULL) {

				if ( status == "overt") {
					targetPlayerObject->setFactionStatus(FactionStatus::OVERT);
				} else  if (status == "covert"){
					targetPlayerObject->setFactionStatus(FactionStatus::COVERT);
				} else if (status == "onleave") {
					targetPlayerObject->setFactionStatus(FactionStatus::ONLEAVE);
				}

			}  else {
				if (status == "overt")
					pvpStatus |= CreatureFlag::OVERT;

				if (status == "covert")
					pvpStatus &= ~CreatureFlag::OVERT;

				tano->setPvpStatusBitmask(pvpStatus);
			}
		} else {
			tano->broadcastPvpStatusBitmask();
		}


		return SUCCESS;
	}
};

#endif //SETFACTIONCOMMAND_H_
