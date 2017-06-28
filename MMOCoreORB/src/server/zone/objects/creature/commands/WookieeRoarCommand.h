/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WOOKIEEROARCOMMAND_H_
#define WOOKIEEROARCOMMAND_H_

#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class WookieeRoarCommand : public CombatQueueCommand {
public:

	WookieeRoarCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getSpecies() != CreatureObject::WOOKIE)
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		Reference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target).castTo<TangibleObject*>();

		if (targetObject == NULL || !targetObject->isCreatureObject())
			return INVALIDTARGET;

		Locker locker(targetObject, creature);

		if (!targetObject->isAttackableBy(creature)) {
			return INVALIDTARGET;
		}

		locker.release();

		// Check to see if "innate_roar" Cooldown isPast();
		if (!player->checkCooldownRecovery("innate_roar")) {

			Time* cdTime = player->getCooldownTime("innate_roar");

			// Returns -time. Multiple by -1 to return positive.
			int timeLeft = floor((float)cdTime->miliDifference() / 1000) * -1;

			StringIdChatParameter stringId;
			stringId.setStringId("@innate:roar_wait"); // You are still recovering from your last roar. Command available in %DI seconds.
			stringId.setDI(timeLeft);
			player->sendSystemMessage(stringId);
			return GENERALERROR;
		}

		int res = doCombatAction(creature, target);

		if (res == TOOFAR) {
			CombatManager::instance()->broadcastCombatSpam(creature, targetObject, NULL, 0, "cbt_spam", "wookiee_roar_out_of_range", 0);
			return TOOFAR;
		}

		player->sendSystemMessage("@innate:roar_active"); // You let out a mighty roar.
		player->addCooldown("innate_roar", 300 * 1000); // 5min reuse time.

		// *There doesn't seem to be an 'INNATE_BUFF_ROAR' enum in BuffCRC.h
		uint32 buffcrc = STRING_HASHCODE("wookieeroar");
		ManagedReference<Buff*> buff = new Buff(player, buffcrc, 300, BuffType::OTHER); // Duration of 5min

		DeltaVector<ManagedReference<SceneObject*> >* roaredAt = player->getDefenderList();

		for (int i = 0; i < roaredAt->size(); i++) {
			ManagedReference<SceneObject*> object = roaredAt->get(i);

			TangibleObject* defender = cast<TangibleObject*>( object.get());

			if (defender == NULL)
				continue;

			if (res == GENERALERROR)
				defender->showFlyText("combat_effects", "wookiee_roar_miss", 0, 255, 0); // -Roar-

		}

		int minplusDefs = roaredAt->size() * 20;
		//if (res == SUCCESS) {
			Locker clocker(buff, player);
			buff->setAttributeModifier(CreatureAttribute::MIND, minplusDefs);
			buff->setAttributeModifier(CreatureAttribute::FOCUS, minplusDefs);
			buff->setAttributeModifier(CreatureAttribute::WILLPOWER, minplusDefs);
			player->addBuff(buff);
		//}

		return res;

	}

};

#endif //WOOKIEEROARCOMMAND_H_
