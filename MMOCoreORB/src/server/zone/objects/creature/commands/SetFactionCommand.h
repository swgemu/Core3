/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

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

		if (faction == "neutral") {
			tano->setFaction(0);

			if (pobj != NULL) {
				pobj->setFactionRank(0);
			}
		}

		if (faction == "imperial" || faction == "rebel" || faction == "hutt") {
			if (pobj != NULL && faction.hashCode() != tano->getFaction()) {
				pobj->setFactionRank(0);
			}

			tano->setFaction(faction.hashCode());
		}

		if (targetPlayerObject != NULL) { // Cap off points to new caps
			targetPlayerObject->increaseFactionStanding("imperial", 0);
			targetPlayerObject->increaseFactionStanding("rebel", 0);
		}


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
