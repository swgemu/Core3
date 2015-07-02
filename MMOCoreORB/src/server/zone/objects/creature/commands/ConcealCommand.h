/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONCEALCOMMAND_H_
#define CONCEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/templates/tangible/CamoKitTemplate.h"

class ConcealCommand : public QueueCommand {
public:

	ConcealCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CreatureObject*> targetPlayer = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

		if(targetPlayer == NULL || creature->getZone() == NULL || !targetPlayer->isPlayerCreature()) {
			creature->sendSystemMessage("@skl_use:sys_conceal_notplayer"); // You can only conceal yourself or another player.
			return INVALIDTARGET;
		}

		Locker clocker(targetPlayer, creature);

		if(targetPlayer->getDistanceTo(creature) > 10.0) {
			return GENERALERROR;
		}

		uint32 crc = STRING_HASHCODE("skill_buff_mask_scent");

		if(targetPlayer->hasBuff(crc) || targetPlayer->getSkillModFromBuffs("private_conceal") > 0) {
			creature->sendSystemMessage("@skl_use:sys_target_concealed"); // Your target is already concealed.
			return false;
		}

		if(targetPlayer->hasBuff(STRING_HASHCODE("skill_buff_mask_scent_self")) || (targetPlayer->getOptionsBitmask() & CreatureState::MASKSCENT)) {
			creature->sendSystemMessage("@skl_use:sys_conceal_scentmasked"); // You can't Conceal while Scent Masked.
			return GENERALERROR;
		}

		/// Check if anything is attackable in range
		SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
		CloseObjectsVector* closeObjectsVector = (CloseObjectsVector*) creature->getCloseObjects();

		if (closeObjectsVector == NULL) {
			creature->getZone()->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), 32, &objects, true);
		} else {
			closeObjectsVector->safeCopyTo(objects);
		}

		for (int i = 0; i < objects.size(); ++i) {
			SceneObject* object = cast<SceneObject*>(objects.get(i).get());

			if (object->isCreatureObject() && creature->isInRange(object, 32)) {
				CreatureObject* creo = cast<CreatureObject*>(object);

				if(!creo->isDead() && (creo->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE)) {
					creature->sendSystemMessage("@skl_use:sys_conceal_othersclose"); // You can't conceal yourself because you are too close to a potentially hostile creature or NPC.
					return GENERALERROR;
				}
			}
		}

		String zoneName = creature->getZone()->getZoneName();

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");
		if(inventory == NULL)
			return GENERALERROR;

		ManagedReference<TangibleObject*> usableKit = NULL;

		for(int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			Reference<TangibleObject*> item = inventory->getContainerObject(i).castTo<TangibleObject*>();

			if(item == NULL || !item->isCamoKit())
				continue;

			SharedObjectTemplate* templateData =
					TemplateManager::instance()->getTemplate(
							item->getServerObjectCRC());
			if (templateData == NULL) {
				error("No template for: " + String::valueOf(item->getServerObjectCRC()));
				return GENERALERROR;
			}

			CamoKitTemplate* camoKitData = cast<CamoKitTemplate*> (templateData);
			if (camoKitData == NULL) {
				error("No camoKitData for: " + String::valueOf(camoKitData->getServerObjectCRC()));
				return GENERALERROR;
			}

			if(zoneName == camoKitData->getEffectiveZone()
					&& item->getUseCount() >= 1) {

				usableKit = item;
				break;
			}
		}

		if(usableKit == NULL) {
			creature->sendSystemMessage("@skl_use:sys_conceal_nokit"); // You need to have a Camouflage Kit in your inventory to Conceal.
			return GENERALERROR;
		}

		StringIdChatParameter startStringId("skl_use", "sys_conceal_start"); // You are now concealed from view by complex camouflage.
		StringIdChatParameter endStringId("skl_use", "sys_conceal_stop"); // You are no longer concealed from view.

		int camoMod = creature->getSkillMod("camouflage");
		int cdReduction = ((float)(camoMod / 100.0f)) * 45;
		int duration = 60 + (((float)(camoMod / 100.0f)) * 200);


		ManagedReference<Buff*> buff = new Buff(targetPlayer, crc, duration, BuffType::SKILL);

		Locker blocker(buff);

		buff->addState(CreatureState::MASKSCENT);
		buff->setSkillModifier("private_conceal", camoMod);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);

		if(targetPlayer != creature) {
			StringIdChatParameter param("skl_use","sys_conceal_apply"); // You carefully apply the camouflage to %TT.
			param.setTT(targetPlayer->getFirstName());
			creature->sendSystemMessage(param);
		}

		targetPlayer->addBuff(buff);

		blocker.release();

		Locker ulocker(usableKit);
		usableKit->decreaseUseCount();

		return SUCCESS;
	}

};

#endif //CONCEALCOMMAND_H_
