/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERDESTROYOBJECTCOMMAND_H_
#define SERVERDESTROYOBJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/tool/antidecay/AntiDecayKit.h"
#include "server/zone/managers/auction/AuctionsMap.h"
#include "server/zone/objects/transaction/TransactionLog.h"


class ServerDestroyObjectCommand : public QueueCommand {
public:

	ServerDestroyObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//creature->info("serverdestroy arguments: " + arguments.toString(), true);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == nullptr)
			return GENERALERROR;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		Locker crossLocker(object, creature);

		if (object->canBeDestroyed(creature) != 0)
			return GENERALERROR;

		// need to add checks.. inventory, datapad, bank, waypoint

		if (object->isWaypointObject()) {
			Reference<PlayerObject*> playerObject = creature->getSlottedObject("ghost").castTo<PlayerObject*>( );

			if (playerObject != nullptr)
				playerObject->removeWaypoint(target);

			return SUCCESS;
		}

		ManagedReference<SceneObject*> objectParent = object->getParent().get();

		if (!object->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER))
			return GENERALERROR;

		if (objectParent != nullptr && !objectParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT))
			return GENERALERROR;

		for (int i = 0; i < object->getArrangementDescriptorSize(); ++i) {
			const Vector<String>* descriptors = object->getArrangementDescriptor(i);
			for (int j = 0; j < descriptors->size(); ++j) {
				const String& descriptor = descriptors->get(j);

				if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
						|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair")
					return GENERALERROR;
			}
		}

		TransactionLog trx(creature, TrxCode::SERVERDESTROYOBJECT, object);

		if (object->isASubChildOf(creature)){

			if(object->isTangibleObject()){
				ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object.get());

				if(tano->hasAntiDecayKit()){
					ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

					if(inventory == nullptr){
						creature->sendSystemMessage("@veteran_new:failed_kit_create"); // "This item has Anti Decay applied to it but there was a failure to recreate the Anti Decay Kit."
						return GENERALERROR;
					}

					if(inventory->isContainerFullRecursive()){
						creature->sendSystemMessage("@veteran_new:inventory_full"); // The item can not be deleted because it has Anti Decay applied to it but you do not have room in your inventory to retrieve the Anti Decay Kit that will be created after destroying this item.
						return GENERALERROR;
					}

					ManagedReference<SceneObject*> adkSceno = tano->removeAntiDecayKit();

					if(adkSceno == nullptr){
						creature->sendSystemMessage("@veteran_new:failed_kit_create"); // "This item has Anti Decay applied to it but there was a failure to recreate the Anti Decay Kit."
						return GENERALERROR;
					}

					AntiDecayKit* adk = adkSceno.castTo<AntiDecayKit*>();

					if(adk == nullptr){
						creature->sendSystemMessage("@veteran_new:failed_kit_create"); // "This item has Anti Decay applied to it but there was a failure to recreate the Anti Decay Kit."
						return GENERALERROR;
					}

					if (adk->getParent().get() == nullptr) {
						AuctionManager* auctionManager = server->getZoneServer()->getAuctionManager();

						if (auctionManager != nullptr) {
							AuctionsMap* auctionsMap = auctionManager->getAuctionMap();

							if (auctionsMap != nullptr && !auctionsMap->containsItem(adk->getObjectID())) {
								Locker adkLocker(adk);
								adk->setUsed(false);

								TransactionLog trxADK(object, creature, adk, TrxCode::ADKREMOVE);
								trxADK.groupWith(trx);

								inventory->transferObject(adk, -1, false);
								adk->sendTo(creature, true);
								creature->sendSystemMessage("@veteran_new:kit_created"); // "This item had Anti Decay applied to it. A new Anti Decay Kit has been placed in your inventory."
							}
						}
					}
				}
			}

			if (trx.isVerbose()) {
				// Force a synchronous export because the object will be deleted before we can export it!
				trx.addRelatedObject(object, true);
				trx.setExportRelatedObjects(true);
				trx.exportRelated();
			}

			destroyObject(object, creature);
		}

		return SUCCESS;
	}

	void destroyObject(SceneObject* object, CreatureObject* creature) const {
		object->destroyObjectFromWorld(true);

		object->destroyObjectFromDatabase(true);
	}

};

#endif //SERVERDESTROYOBJECTCOMMAND_H_
