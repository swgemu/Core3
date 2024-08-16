/*
 * DefuseMineTask.h
 *
 * Created on: 2024-08-15
 * Author: Hakry
 */

#ifndef DEFUSEMINETASK_H_
#define DEFUSEMINETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/installation/components/MinefieldAttackTask.h"

class DefuseMineTask : public Task {
	const static uint32 MAX_CHANCE = 1000;
	const static uint32 ROLL_CHANCE = 750;

	ManagedWeakReference<CreatureObject*> weakPlayer;
	ManagedWeakReference<WeaponObject*> weakWeapon;
	ManagedWeakReference<TangibleObject*> weakMinefield;

public:
	DefuseMineTask(CreatureObject* player, WeaponObject* weapon, TangibleObject* minefield) {
		weakPlayer = player;
		weakWeapon = weapon;
		weakMinefield = minefield;
	}

	void run() {
		auto player = weakPlayer.get();

		if (player == nullptr) {
			return;
		}

		Locker lock(player);

		auto minefield = weakMinefield.get();

		if (minefield == nullptr) {
			return;
		}

		Locker cLock(minefield, player);

		if (!minefield->isInRange(player, 5.f)) {
			player->sendSystemMessage("@container_error_message:container09"); // "You are out of range."
			return;
		}

		auto weapon = weakWeapon.get();

		if (weapon == nullptr) {
			return;
		}

		// Lets do some form of roll on this
		if ((System::random(MAX_CHANCE) > ROLL_CHANCE) || (player->getPosture() != CreaturePosture::CROUCHED)) {
			// Player has failed to defuse the mine
			player->sendSystemMessage("You have failed to defuse the mine...");

			// Schedule an attack task
			Reference<MinefieldAttackTask*> task = new MinefieldAttackTask(minefield, player);

			if (task != nullptr) {
				task->schedule(250);
			}

			return;
		}

		Locker weaponLock(weapon, player);

		// Destroy the mine
		weapon->destroyObjectFromWorld(true);
		weapon->destroyObjectFromDatabase(true);

		// Send player the success message
		player->sendSystemMessage("You succesffully disarm and dismantle an enemy mine.");

		// Set their posture upright
		player->setPosture(CreaturePosture::UPRIGHT, true, true);
	}
};

#endif /* DEFUSEMINETASK_H_ */
