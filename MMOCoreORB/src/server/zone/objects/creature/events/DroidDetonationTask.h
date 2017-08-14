/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROIDEFFECTSTASK_H_
#define DROIDEFFECTSTASK_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidDetonationModuleDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidDetonationTask : public Task, public Logger {

private:
	ManagedReference<DroidDetonationModuleDataComponent*> module;
	ManagedReference<CreatureObject*> player;
	int detonationStep;
public:
	DroidDetonationTask(DroidDetonationModuleDataComponent* module, CreatureObject* player) : Task() {
		this->module = module;
		this->player = player;
		detonationStep = 0;
	}

	void run() {
		if (module == NULL || player == NULL) {
			return;
		}

		ManagedReference<DroidObject*> droid = module->getDroidObject();

		if (droid == NULL) {
			return;
		}

		Locker locker(droid);
		Locker crossLocker(player, droid);

		// Check if droid is spawned
		if (droid->getLocalZone() == NULL) {  // Not outdoors
			ManagedReference<SceneObject*> parent = droid->getParent().get();
			if (parent == NULL || !parent->isCellObject()) { // Not indoors either
				droid->removePendingTask("droid_detonation");
				return;
			}
		}

		if (droid->isDead() || droid->isIncapacitated()) {
			module->stopCountDown();
			droid->showFlyText("pet/droid_modules","detonation_disabled", 204, 0, 0);
			module->deactivate();
			droid->removePendingTask("droid_detonation");
			return;
		}

		// if droid gets incapped while started it will disable but be able to be restarted
		switch(detonationStep) {
			case 0:{
				// 3
				droid->showFlyText("pet/droid_modules","countdown_3", 204, 0, 0);
				detonationStep = 1;
				reschedule(1000);
				break;
			}
			case 1: {
				// 2
				droid->showFlyText("pet/droid_modules","countdown_2", 204, 0, 0);
				detonationStep = 2;
				reschedule(1000);
				break;
			}
			case 2:{
				// 1
				droid->showFlyText("pet/droid_modules","countdown_1", 204, 0, 0);
				detonationStep = 3;
				reschedule(1000);
				break;
			}
			case 3: {
				// BOOM
				int areaDamage = module->calculateDamage(droid);
				bool shouldGcwTef = false, shouldBhTef = false;

				// find all valid targets in 17 m range and hit them with the damage
				CloseObjectsVector* vec = (CloseObjectsVector*) droid->getCloseObjects();
				SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;

				if (vec != NULL) {
					closeObjects.removeAll(vec->size(), 10);
					vec->safeCopyTo(closeObjects);
				} else {
#ifdef COV_DEBUG
					droid->info("Null closeobjects vector in DroudDetonationTask::run", true);
#endif
					droid->getZone()->getInRangeObjects(droid->getWorldPositionX(), droid->getWorldPositionY(), 40, &closeObjects, true);
				}

				PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/combat_explosion_lair_large.cef", droid->getZone()->getZoneName(), droid->getPositionX(), droid->getPositionZ(), droid->getPositionY());
				droid->broadcastMessage(explodeLoc, false);

				crossLocker.release();

				for (int i = 0; i < closeObjects.size(); ++i) {
					ManagedReference<SceneObject*> object = cast<SceneObject*>(closeObjects.get(i).get());

					if (!object->isCreatureObject() || object == droid) {
						continue;
					}

					CreatureObject* creo = object->asCreatureObject();

					if (creo == NULL || creo->isDead() || !creo->isAttackableBy(droid) || !droid->isInRange(object, 17)) {
						continue;
					}

					if (creo->isIncapacitated() && !creo->isFeigningDeath()) {
						continue;
					}

					try {
						Locker defenderLocker(creo, droid);

						// apply the damage to the target and send themessage
						if (CollisionManager::checkLineOfSight(object, droid)) {
							// apply the damage
							float amount = CombatManager::instance()->doDroidDetonation(droid, creo, areaDamage);

							if (amount > 0) {
								if (creo->isPlayerCreature()) {
									StringIdChatParameter stringId;
									stringId.setStringId("@pet/droid_modules:hit_by_detonation");
									stringId.setDI((int)amount);
									creo->sendSystemMessage(stringId);
								}

								StringIdChatParameter tomaster;
								tomaster.setStringId("@pet/droid_modules:hit_by_detonation_master");
								tomaster.setTT(object->getObjectID());
								tomaster.setDI((int)amount);
								player->sendSystemMessage(tomaster);

								CombatManager::instance()->checkForTefs(player, creo, &shouldGcwTef, &shouldBhTef);
							}

						}
					} catch (Exception& e) {
						error(e.getMessage());
					} catch (...) {
						throw;
					}
				}

				droid->removePendingTask("droid_detonation");

				Locker clocker(player, droid);

				// nuke the droid from the world
				ManagedReference<PetControlDevice*> petControlDevice = droid->getControlDevice().get().castTo<PetControlDevice*>();
				if (petControlDevice != NULL) {
					Locker deviceLocker(petControlDevice);

					petControlDevice->storeObject(player, true);

					petControlDevice->destroyObjectFromWorld(true);
					petControlDevice->destroyObjectFromDatabase(true);
				}

				// Update PvP TEF Duration
				if (shouldGcwTef || shouldBhTef) {
					PlayerObject* ghost = player->getPlayerObject();

					if (ghost != NULL) {
						ghost->updateLastPvpCombatActionTimestamp(shouldGcwTef, shouldBhTef);
					}
				}

				break;
			}
		}
	}

};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDEFFECTSTASK_H_*/
