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
		if (!object->isInRange(creature, 16.0f + object->getTemplateRadius() + creature->getTemplateRadius())){
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
