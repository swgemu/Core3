/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONCEALCOMMAND_H_
#define CONCEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "templates/tangible/CamoKitTemplate.h"
#include "server/zone/objects/creature/buffs/ConcealBuff.h"

class ConcealCommand : public QueueCommand {
public:
	ConcealCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	void doAnimations(CreatureObject* creature, CreatureObject* targetPlayer) const {
		if (creature == targetPlayer)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	bool checkHostileInRange(Zone* zone, CreatureObject* player) const {
		if (zone == nullptr || player == nullptr)
			return true;

		/// Check if anything is attackable in range
		SortedVector<QuadTreeEntry*> objects(512, 512);
		CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*)player->getCloseObjects();

		if (closeObjectsVector == nullptr) {
			zone->getInRangeObjects(player->getPositionX(), player->getPositionY(), 32, &objects, true);
		} else {
			closeObjectsVector->safeCopyReceiversTo(objects, CloseObjectsVector::CREOTYPE);
		}

		for (int i = 0; i < objects.size(); ++i) {
			SceneObject* object = static_cast<SceneObject*>(objects.get(i));

			if (object == nullptr || !object->isAiAgent())
				continue;

			if (!checkDistance(player, object, 32))
				continue;

			AiAgent* nearbyAgent = object->asAiAgent();

			if (nearbyAgent == nullptr || nearbyAgent->isDead() || !nearbyAgent->isAggressiveTo(player))
				continue;

			return true;
		}

		return false;
	}

	ManagedReference<TangibleObject*> getCamoKit(Zone* zone, CreatureObject* player) const {
		if (zone == nullptr || player == nullptr)
			return nullptr;

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory == nullptr)
			return nullptr;

		ManagedReference<TangibleObject*> usableKit = nullptr;
		String zoneName = zone->getZoneName();

		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			Reference<TangibleObject*> item = inventory->getContainerObject(i).castTo<TangibleObject*>();

			if (item == nullptr || !item->isCamoKit())
				continue;

			SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(item->getServerObjectCRC());

			if (templateData == nullptr) {
				error("No template for: " + String::valueOf(item->getServerObjectCRC()));
				return nullptr;
			}

			CamoKitTemplate* camoKitData = cast<CamoKitTemplate*>(templateData);

			if (camoKitData == nullptr) {
				error("No camoKitData for: " + String::valueOf(camoKitData->getServerObjectCRC()));
				return nullptr;
			}

			if (zoneName == camoKitData->getEffectiveZone() && item->getUseCount() >= 1) {
				usableKit = item;
				break;
			}
		}

		return usableKit;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);
		CreatureObject* targetPlayer = nullptr;

		if (targetObject != nullptr) {
			if (!targetObject->isPlayerCreature()) {
				creature->sendSystemMessage("@skl_use:sys_conceal_notplayer"); // You can only conceal yourself or another player.
				return INVALIDTARGET;
			}

			targetPlayer = targetObject->asCreatureObject();
		} else {
			targetPlayer = creature;
		}

		if (targetPlayer == nullptr || !targetPlayer->isPlayerCreature()) {
			creature->sendSystemMessage("@skl_use:sys_conceal_notplayer"); // You can only conceal yourself or another player.
			return INVALIDTARGET;
		}

		auto zone = creature->getZone();

		if (zone == nullptr) {
			return GENERALERROR;
		}

		uint32 crc = STRING_HASHCODE("skill_buff_mask_scent");

		// Ranger is targetting themselves
		if (creature->getObjectID() == targetPlayer->getObjectID()) {
			// Rangers can remove their own conceal buff by targeting nothing.
			if (targetPlayer->hasBuff(crc)) {
				creature->sendSystemMessage("@skl_use:sys_conceal_remove"); // You remove the camouflage. You are no longer concealed.
				creature->removeBuff(crc);

				return SUCCESS;
			}
		} else {
			// Target is another player, do distance check
			if (!checkDistance(creature, targetPlayer, 10.0f)) {
				StringIdChatParameter tooFar("cmd_err", "target_range_prose"); // Your target is too far away to %TO.
				tooFar.setTO("conceal");
				creature->sendSystemMessage(tooFar);

				return GENERALERROR;
			}

			if (targetPlayer->hasBuff(crc) || targetPlayer->getSkillModFromBuffs("private_conceal") > 0) {
				creature->sendSystemMessage("@skl_use:sys_target_concealed"); // Your target is already concealed.
				return GENERALERROR;
			}
		}

		uint32 maskCrc = STRING_HASHCODE("skill_buff_mask_scent_self");

		if (targetPlayer->hasBuff(maskCrc)) {
			targetPlayer->sendSystemMessage("@skl_use:sys_conceal_scentmasked"); // You can't Conceal while Scent Masked.
			return GENERALERROR;
		}

		if (!targetPlayer->checkCooldownRecovery("skill_buff_mask_scent_self")) {
			StringIdChatParameter waitTime("@skl_use:sys_scentmask_delay"); // You must wait %DI seconds to mask your scent again.
			int timeLeft = (targetPlayer->getCooldownTime("skill_buff_mask_scent_self")->getMiliTime() / 1000) - System::getTime();
			waitTime.setDI(timeLeft);

			targetPlayer->sendSystemMessage(waitTime);

			return GENERALERROR;
		}

		if (checkHostileInRange(zone, targetPlayer)) {
			targetPlayer->sendSystemMessage("@skl_use:sys_conceal_othersclose"); // You can't conceal yourself because you are too close to a potentially hostile creature or NPC.
			return GENERALERROR;
		}

		ManagedReference<TangibleObject*> usableKit = getCamoKit(zone, creature);

		if (usableKit == nullptr) {
			creature->sendSystemMessage("@skl_use:sys_conceal_nokit"); // You need to have a Camouflage Kit in your inventory to Conceal.
			return GENERALERROR;
		}

		StringIdChatParameter startStringId("skl_use", "sys_conceal_start"); // You are now concealed from view by complex camouflage.
		StringIdChatParameter endStringId("skl_use", "sys_conceal_stop");	// You are no longer concealed from view.

		String zoneName = zone->getZoneName();
		int camoMod = creature->getSkillMod("camouflage") / 2;
		int duration = 40 * camoMod;

		ManagedReference<ConcealBuff*> buff = new ConcealBuff(targetPlayer, creature, crc, duration, zoneName);

		Locker blocker(buff, creature);

		buff->addState(CreatureState::MASKSCENT);
		buff->setSkillModifier("private_conceal", camoMod);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);

		if (targetPlayer->getObjectID() != creature->getObjectID()) {
			Locker clock(targetPlayer, creature);

			targetPlayer->addBuff(buff);

			StringIdChatParameter param("skl_use", "sys_conceal_apply"); // You carefully apply the camouflage to %TT.
			param.setTT(targetPlayer->getFirstName());
			creature->sendSystemMessage(param);
		} else {
			creature->addBuff(buff);
		}

		blocker.release();

		doAnimations(creature, targetPlayer);

		// Decrease use count
		Locker ulocker(usableKit, creature);
		usableKit->decreaseUseCount();

		return SUCCESS;
	}
};

#endif // CONCEALCOMMAND_H_
