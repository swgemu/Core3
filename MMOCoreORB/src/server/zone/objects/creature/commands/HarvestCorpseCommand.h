/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTCORPSECOMMAND_H_
#define HARVESTCORPSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/Zone.h"

class HarvestCorpseCommand : public QueueCommand {
public:

	HarvestCorpseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);

		StringTokenizer args(arguments.toString());

		if (object == NULL || !object->isCreatureObject() || player == NULL)
			return INVALIDTARGET;

		CreatureObject* creo = cast<CreatureObject*>( object.get());

		if (!creo->isCreature())
			return INVALIDTARGET;

		Creature* cr = cast<Creature*>( creo);

		Locker clocker(cr, player);

		String harvesttype = "";

		if (args.hasMoreTokens())
			args.getStringToken(harvesttype);

		harvesttype = harvesttype.toLowerCase();
		byte type = 0;

		if(harvesttype == "meat" && !cr->getMeatType().isEmpty())
			type = 234;
		else if(harvesttype == "hide" && !cr->getHideType().isEmpty())
			type = 235;
		else if(harvesttype == "bone" && !cr->getBoneType().isEmpty())
			type = 236;
		else {
			if (harvesttype != "") {
				player->sendSystemMessage("@error_message:no_resource");
				return GENERALERROR;
			}
			Vector<int> types;
			if(!cr->getMeatType().isEmpty()) {
				types.add(234);
			}

			if(!cr->getHideType().isEmpty()) {
				types.add(235);
			}

			if(!cr->getBoneType().isEmpty()) {
				types.add(236);
			}
			if(types.size() > 0)
				type = types.get(System::random(types.size() -1));
		}

		if(type == 0) {
			player->sendSystemMessage("This creature has no resources");
			return GENERALERROR;
		}

		if (cr->canHarvestMe(player)) {
			if (!cr->isDead())
				return GENERALERROR;

			if (cr->getZone() == NULL)
				return GENERALERROR;

			if (cr->getDnaState() == CreatureManager::DNADEATH) {
				player->sendSystemMessage("@skl_use:nothing_to_harvest");
				return GENERALERROR;
			}

			ManagedReference<CreatureManager*> manager = cr->getZone()->getCreatureManager();
			manager->harvest(cr, player, type);
		}


		return SUCCESS;
	}

};

#endif //HARVESTCORPSECOMMAND_H_
