/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GIVEITEMCOMMAND_H_
#define GIVEITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

#include "server/zone/objects/tangible/attachment/Attachment.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidStimpackModuleDataComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidTrapModuleDataComponent.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

class GiveItemCommand : public QueueCommand {
public:
	GiveItemCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		StringTokenizer args(arguments.toString());

		ManagedReference<SceneObject*> giveObject = zoneServer->getObject(target);

		if (giveObject == nullptr) {
			return INVALIDTARGET;
		}

		if (!args.hasMoreTokens()) {
			return GENERALERROR;
		}

		uint64 targetObjectID = 0;

		try {
			targetObjectID = args.getLongToken();
		} catch (Exception& e) {
			error("could not get long token in " + arguments.toString());
			error(e.getMessage());

			return GENERALERROR;
		}

		ManagedReference<SceneObject*> objectsParent = giveObject->getParent().get();

		if (objectsParent == nullptr) {
			return GENERALERROR;
		}

		if (!objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT)) {
			return GENERALERROR;
		}

		if (!giveObject->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER)) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(targetObjectID);

		if (targetObject == nullptr) {
			return GENERALERROR;
		}

		// For NPC Actor Event Perks
		const ContainerPermissions* permissions = targetObject->getContainerPermissions();
		SceneObject* parentPerk = nullptr;

		if (permissions != nullptr) {
			uint64 parentID = permissions->getOwnerID();
			parentPerk = zoneServer->getObject(parentID);
		}

		// Attempting to add attachment to item
		if (giveObject->isAttachment()) {
			auto attachment = cast<Attachment*>(giveObject.get());

			if (attachment == nullptr) {
				return GENERALERROR;
			}

			if (!targetObject->isWearableObject() || !targetObject->isASubChildOf(creature)) {
				return GENERALERROR;
			}

			auto wearable = cast<WearableObject*>(targetObject.get());

			if (wearable == nullptr) {
				return GENERALERROR;
			}

			wearable->applyAttachment(creature, attachment);

			return SUCCESS;
		// Target is a npc/creature style vendor or event perk
		} else if (targetObject->isCreatureObject() && (targetObject->isVendor() || (parentPerk != nullptr && parentPerk->isEventPerk()))) {
			Locker clocker(targetObject, creature);

			// Check that the item is wearable or is a weapon
			if (!giveObject->isWearableObject() && !giveObject->isWeaponObject()) {
				return GENERALERROR;
			}

			auto targetCreature = targetObject->asCreatureObject();

			if (targetCreature == nullptr) {
				return GENERALERROR;
			}

			ManagedReference<TangibleObject*> giveTanO = giveObject->asTangibleObject();

			if (giveTanO == nullptr) {
				return GENERALERROR;
			}

			if (targetCreature->isVendor()) {
				if (!giveItemToVendor(creature, targetCreature, giveTanO)) {
					return GENERALERROR;
				}
			} else if (parentPerk != nullptr && parentPerk->isEventPerk()) {
				if (!giveItemToActorNpc(creature, targetCreature, giveTanO)) {
					return GENERALERROR;
				}
			}

			auto zone = creature->getZone();

			if (zone == nullptr) {
				return GENERALERROR;
			}

			auto creatureManager = zone->getCreatureManager();

			if (creatureManager == nullptr || !creatureManager->addWearableItem(targetCreature, giveTanO, targetCreature->isVendor())) {
				return GENERALERROR;
			}

			return SUCCESS;
		} else if (targetObject->isPet() && giveObject->getGameObjectType() == SceneObjectType::FOOD) {
			ManagedReference<AiAgent*> petAgent = targetObject->asAiAgent();

			if (petAgent == nullptr) {
				return GENERALERROR;
			}

			Locker crossLocker(petAgent, creature);

			PetManager* petManager = zoneServer->getPetManager();

			if (petManager == nullptr) {
				return GENERALERROR;
			}

			petManager->enqueueOwnerOnlyPetCommand(creature, petAgent, STRING_HASHCODE("petfeed"), String::valueOf(giveObject->getObjectID()));
		} else if (targetObject->isPet() && targetObject->isDroidObject() && giveObject->getGameObjectType() == SceneObjectType::STIMPACK) {
			Reference<DroidObject*> droid = targetObject.castTo<DroidObject*>();

			if (droid != nullptr) {
				Locker cross(targetObject, creature);

				StimPack* medicine = cast<StimPack*>(giveObject.get());

				if (medicine != nullptr) {
					auto module = droid->getModule("stimpack_module").castTo<DroidStimpackModuleDataComponent*>();

					if (module != nullptr) {
						module->handleInsertStimpack(creature, medicine);
					} else {
						creature->sendSystemMessage("@pet/droid_modules:not_stimpack_droid");
					}
				} else {
					return GENERALERROR;
				}
			}
		} else if (targetObject->isPet() && targetObject->isDroidObject() && giveObject->isTrapObject()) {
			Reference<DroidObject*> droid = giveObject.castTo<DroidObject*>();

			if (droid != nullptr) {
				Locker cross(targetObject, creature);

				TangibleObject* trap = cast<TangibleObject*>(giveObject.get());

				if (trap != nullptr) {
					auto module = droid->getModule("trap_module").castTo<DroidTrapModuleDataComponent*>();

					if (module != nullptr) {
						module->handleInsertTrap(creature, trap);
					}
				} else {
					return GENERALERROR;
				}
			}
		} else if (targetObject->isCreatureObject()) {
			String err;
			Locker objLocker(giveObject);

			if (targetObject->canAddObject(giveObject, -1, err) == 0) {
				targetObject->transferObject(giveObject, -1, true);
			}
		}

		return SUCCESS;
	}

	bool giveItemToVendor(CreatureObject* player, CreatureObject* vendor, TangibleObject* giveItem) const {
		if (player == nullptr || vendor == nullptr || giveItem == nullptr) {
			return false;
		}

		// info(true) << "giveItemToVendor -- Player: " << player->getDisplayedName() << " giving item: " << giveItem->getDisplayedName() << " to " << vendor->getDisplayedName();

		if (player->getSkillMod("hiring") < 90) {
			UnicodeString message("@player_structure:wear_noway");

			auto chatManager = server->getChatManager();

			if (chatManager != nullptr) {
				chatManager->broadcastChatMessage(vendor, message, player->getObjectID(), 0, vendor->getMoodID());
			}

			return false;
		}

		DataObjectComponentReference* data = vendor->getDataObjectComponent();

		if (data == nullptr || data->get() == nullptr || !data->get()->isVendorData()) {
			error("Vendor has no data component");
			return false;
		}

		VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());

		if (vendorData == nullptr) {
			error("Vendor has invalid data component");
			return false;
		}

		if (player->getObjectID() != vendorData->getOwnerId()) {
			return false;
		}

		return true;
	}

	bool giveItemToActorNpc(CreatureObject* player, CreatureObject* npcActor, TangibleObject* giveItem) const {
		if (player == nullptr || npcActor == nullptr || giveItem == nullptr) {
			return false;
		}

		// info(true) << "giveItemToActorNpc -- Player: " << player->getDisplayedName() << " giving item: " << giveItem->getDisplayedName() << " to " << npcActor->getDisplayedName();

		const ContainerPermissions* permissions = npcActor->getContainerPermissions();

		if (permissions == nullptr) {
			return false;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return false;
		}

		uint64 parentID = permissions->getOwnerID();
		auto parentPerk = zoneServer->getObject(parentID);

		if (parentPerk == nullptr) {
			return false;
		}

		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(parentPerk->getDataObjectComponent()->get());

		if (data == nullptr) {
			return false;
		}

		EventPerkDeed* deed = data->getDeed();

		if (deed == nullptr) {
			return false;
		}

		auto owner = deed->getOwner().get();

		if (owner == nullptr) {
			return false;
		}

		auto ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return false;
		}

		bool privilegedAccess = ghost->isPrivileged();

		if (!privilegedAccess && owner->getObjectID() != player->getObjectID()) {
			return false;
		}

		return true;
	}
};

#endif //GIVEITEMCOMMAND_H_
