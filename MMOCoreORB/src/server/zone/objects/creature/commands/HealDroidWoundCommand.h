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

#ifndef HEALDROIDWOUNDCOMMAND_H_
#define HEALDROIDWOUNDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"

class HealDroidWoundCommand : public QueueCommand {
	int mindCost;
	float range;
public:

	HealDroidWoundCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		mindCost = 50;
		range = 6;
	}

	void deactivateWoundTreatment(CreatureObject* creature) {
		int delay = 20;

		StringIdChatParameter message("healing_response", "healing_response_59");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "woundTreatment");
		creature->addPendingTask("woundTreatment", task, delay * 1000);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* droid) {
		droid->playEffect("clienteffect/healing_healwound.cef", "");

		creature->doAnimation("heal_other");
	}

	void sendWoundMessage(CreatureObject* creature, DroidObject* droid, uint32 woundsHealed) {
		if (!creature->isPlayerCreature())
			return;

		StringIdChatParameter stringId("healing", "droid_repair_wound_self"); // You have repaired %TO and healed a total of %DI wounds.
		stringId.setTO(droid);
		stringId.setDI(woundsHealed);
		creature->sendSystemMessage(stringId);

		ManagedReference<CreatureObject*> droidOwner = droid->getLinkedCreature().get();

		if (droidOwner != NULL && droidOwner != creature) {
			StringIdChatParameter stringId("healing", "droid_repair_wound_other"); // %TT has repaired %TO and healed a total of %DI wounds.
			stringId.setTT(creature);
			stringId.setTO(droid);
			stringId.setDI(woundsHealed);
			droidOwner->sendSystemMessage(stringId);
		}
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* droid, WoundPack* woundPack) {
		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("@healing_response:enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (woundPack == NULL) {
			creature->sendSystemMessage("No valid droid reconstruction kit found.");
			return false;
		}

		int medicalRatingNotIncludingCityBonus = creature->getSkillMod("private_medical_rating") - creature->getSkillModOfType("private_medical_rating", SkillModManager::CITY);
		if (medicalRatingNotIncludingCityBonus <= 0) {
			creature->sendSystemMessage("@healing_response:must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		} else {
			// are we in a cantina? we have a private medical rating so either thats form a droid or camp or hospital
			ManagedReference<SceneObject*> root = creature->getRootParent();
			if (root != NULL && root->isStaticObject()) {
				uint32 gameObjectType = root->getGameObjectType();
				switch (gameObjectType) {
						case SceneObjectType::RECREATIONBUILDING:
						case SceneObjectType::HOTELBUILDING:
						case SceneObjectType::THEATERBUILDING:
							creature->sendSystemMessage("@healing_response:must_be_in_hospital"); // You must be in a hospital or at a campsite to do that.
							return false;
				}
			}
		}

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while in Combat.");
			return false;
		}

		if (droid->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while your target is in Combat.");
			return false;
		}

		if (!droid->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");  //It would be unwise to help such a patient.
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (!CollisionManager::checkLineOfSight(creature, droid)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint64& objectId) {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);

			objectId = tokenizer.getLongToken();
		} else {
			objectId = 0;
		}
	}

	uint8 findAttribute(CreatureObject* creature) {
		for (int i = 0; i < 9; ++i) {
			int wounds = creature->getWounds(i);

			if (wounds != 0)
				return i;
		}

		return CreatureAttribute::UNKNOWN;
	}

	WoundPack* findWoundPack(CreatureObject* creature) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = cast<TangibleObject*>( object);

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( item);

					if (pharma->isDroidReconstructionKit()) {
						WoundPack* woundPack = cast<WoundPack*>( pharma);

						return woundPack;
					}
				}
			}
		}

		return NULL;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isDroidObject()) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		DroidObject* droid = cast<DroidObject*>( object.get());

		Locker clocker(droid, creature);

		if (!droid->isPet() || droid->isDead() || droid->isAttackableBy(creature)) {
			creature->sendSystemMessage("Invalid Target.");
			return GENERALERROR;
		}

		if (!creature->isInRange(droid, range + droid->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

		uint8 attribute = findAttribute(droid);

		if (attribute == CreatureAttribute::UNKNOWN) {
			StringBuffer message;
			message << droid->getDisplayedName() << " has no wounds to heal.";
			creature->sendSystemMessage(message.toString());
			return 0;
		}

		uint64 objectId = 0;

		parseModifier(arguments.toString(), objectId);

		ManagedReference<WoundPack*> woundPack = NULL;

		if (objectId != 0) {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				woundPack = inventory->getContainerObject(objectId).castTo<WoundPack*>();
			}
		} else {
			woundPack = findWoundPack(creature);
		}

		if (!canPerformSkill(creature, droid, woundPack))
			return GENERALERROR;

		uint32 woundPower = woundPack->calculatePower(creature, droid, false);

		int woundHealed = droid->healWound(creature, attribute, woundPower);

		woundHealed = abs(woundHealed);

		sendWoundMessage(creature, droid, woundHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		deactivateWoundTreatment(creature);

		woundPack->decreaseUseCount();

		doAnimations(creature, droid);

		return SUCCESS;
	}

};

#endif //HEALDROIDWOUNDCOMMAND_H_
