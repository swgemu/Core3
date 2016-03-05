/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SAMPLEDNACOMMAND_H_
#define SAMPLEDNACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SampleDNACommand : public QueueCommand {
public:

	SampleDNACommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isDead()){
			return INVALIDTARGET;
		}

		if (creature->isPlayerCreature()){
			if (creature->getPlayerObject() && creature->getPlayerObject()->isAFK()) {
				return GENERALERROR;
			}
		}

		ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		if (player && !player->hasSkill("outdoors_bio_engineer_novice")) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_skill_too_low"); // You are not sufficiently skilled to take DNA samples.
			return GENERALERROR;
		}

		if (object == NULL) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_need_target"); // You need to target the creature you wish to take a DNA sample from.
			return INVALIDTARGET;
		}

		if (!object->isCreatureObject() || object == player){
			player->sendSystemMessage("@bio_engineer:harvest_dna_invalid_target"); // You cannot sample DNA from that target.
			return INVALIDTARGET;
		}

		CreatureObject* creo = cast<CreatureObject*>( object.get());
		Creature* cr = cast<Creature*>( creo);
		Locker crosslocker(creo,creature);

		if (!CollisionManager::checkLineOfSight(creature, creo)) {
			player->sendSystemMessage("@container_error_message:container18"); // You can't see that object. You may have to move closer to it.
			return GENERALERROR;
		}

		if (cr == NULL || !cr->isAttackableBy(player)){
			player->sendSystemMessage("@bio_engineer:harvest_dna_invalid_target"); // You cannot sample DNA from that target.
			return INVALIDTARGET;
		}

		// Sample DNa is a 16M max range
		if (!checkDistance(object, creature, 16.0f)){
			player->sendSystemMessage("@bio_engineer:harvest_dna_out_of_range"); // Your target is too far away to be able to sample from.
			return TOOFAR;
		}

		//if (creature->)
		// At this point we know its a living creature we are targetting
		if (cr->isDead()){
			player->sendSystemMessage("@bio_engineer:harvest_dna_target_corpse"); // You cannot sample DNA from a corpse.
			return INVALIDTARGET;
		}

		if (cr->isBaby()) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_target_baby"); // That creature is too young to get a viable DNA sample.
			return INVALIDTARGET;
		}
		// SOE Pathc notes Sept 4, 2003 all pet sampling disabled, added as radial to pet deed
		if (cr->isPet()) {
			// allow them to sample their own be pets
			player->sendSystemMessage("@bio_engineer:harvest_dna_target_pet"); // You cannot sample DNA from that pet.
			return INVALIDTARGET;
		}

		if (cr->isInCombat()) {
			player->sendSystemMessage("@bio_engineer:harvest_dna_creature_in_combat"); // It is too dangerous to sample DNA from a creature while it's in combat.
			return INVALIDTARGET;
		}

		if (cr->canCollectDna(player)) {

			if (cr->getZone() == NULL){
				return GENERALERROR;
			}

			ManagedReference<CreatureManager*> manager = cr->getZone()->getCreatureManager();
			manager->sample(cr, player);
		} else {
			player->sendSystemMessage("@bio_engineer:harvest_dna_cant_harvest"); // You cannot sample DNA from that target.
		}

		return SUCCESS;
	}
};

#endif //SAMPLEDNACOMMAND_H_
