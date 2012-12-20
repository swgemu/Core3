/*
 * MinefieldAttackTask.h
 *
 *  Created on: 20/12/2012
 *      Author: victor
 */

#ifndef MINEFIELDATTACKTASK_H_
#define MINEFIELDATTACKTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"

class MinefieldAttackTask : public Task {
	ManagedReference<SceneObject*> sceneObject;
	ManagedReference<CreatureObject*> player;
	ManagedReference<WeaponObject*> mine;

public:
	MinefieldAttackTask(SceneObject* scene, CreatureObject* player, WeaponObject* mine) {
		sceneObject = scene;
		this->mine = mine;
		this->player = player;
	}

	void run() {
		Locker locker(sceneObject);

		Locker clocker(player, sceneObject);

		if(sceneObject->hasObjectInContainer(mine->getObjectID())){
			sceneObject->removeObject(mine, NULL, true);

			PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", sceneObject->getZone()->getZoneName(), sceneObject->getPositionX(), sceneObject->getPositionZ(), sceneObject->getPositionY());
			sceneObject->broadcastMessage(explodeLoc, false);
		}

		ManagedReference<WeaponObject*> weapon = NULL;

		if (sceneObject->getContainerObjectsSize() > 0)
			weapon = cast<WeaponObject*>(sceneObject->getContainerObject(0));

		if (weapon == NULL)
			return;

		locker.release();

		Locker clockerm(mine, player);

		if(sceneObject->getZoneServer() != NULL){
			ManagedReference<ObjectController*> objectController = sceneObject->getZoneServer()->getObjectController();
			QueueCommand* command = objectController->getQueueCommand(String("defaultattack").hashCode());

			if(command != NULL){
				CombatQueueCommand* combatCommand = cast<CombatQueueCommand*>(command);
				if(combatCommand != NULL){
					combatCommand->setAreaAction(true);
					combatCommand->setAreaRange(mine->getMaxRange());
					CombatManager::instance()->doCombatAction(mine, weapon, player, combatCommand);

				}
			}

		}

		mine->destroyObjectFromWorld(true);
		mine->destroyObjectFromDatabase(true);
	}


};


#endif /* MINEFIELDATTACKTASK_H_ */
