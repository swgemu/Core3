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

		if(targetPlayer->getDistanceTo(creature) > 10.0) {
			return GENERALERROR;
		}

		if(targetPlayer->hasBuff(String("skill_buff_mask_scent").hashCode()) || targetPlayer->getSkillModFromBuffs("private_conceal") > 0) {
			creature->sendSystemMessage("@skl_use:sys_target_concealed"); // Your target is already concealed.
			return false;
		}

		if(targetPlayer->hasBuff(String("skill_buff_mask_scent_self").hashCode()) || (targetPlayer->getOptionsBitmask() & CreatureState::MASKSCENT)) {
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

		uint32 crc = String("skill_buff_mask_scent").hashCode();
		int camoMod = creature->getSkillMod("camouflage");
		int cdReduction = ((float)(camoMod / 100.0f)) * 45;
		int duration = 60 + (((float)(camoMod / 100.0f)) * 200);


		ManagedReference<Buff*> buff = new Buff(targetPlayer, crc, duration, BuffType::SKILL);
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

		usableKit->decreaseUseCount();

		return SUCCESS;
	}

};

#endif //CONCEALCOMMAND_H_
