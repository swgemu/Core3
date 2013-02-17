/*
 * TurretControlSuiCallback.h
 *
 *  Created on: Jan 27, 2013
 *      Author: root
 */

#ifndef TURRETCONTROLSUICALLBACK_H_
#define TURRETCONTROLSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/installation/components/TurretFireManualTask.h"

class TurretControlSuiCallback : public SuiCallback {
	ManagedReference<TangibleObject*> turretObject;
	ManagedReference<SceneObject*> turretControl;
public:
	TurretControlSuiCallback(ZoneServer* server, TangibleObject* turret, SceneObject* terminal)
		: SuiCallback(server) {
		turretObject = turret;
		turretControl = terminal;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if(cancelPressed)
			return;

		DataObjectComponentReference* data  = turretObject->getDataObjectComponent();

		if(data == NULL)
			return;

		TurretDataComponent* turretData = cast<TurretDataComponent*>(data->get());

		if(turretData == NULL)
			return;

		if(turretData->getController() != player){
			player->sendSystemMessage("@hq:in_use");  //  This turret control terminal is already in use."
			return;
		}

		if(args->size() < 1)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());


		if(player->getZone() == NULL)
			return;

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if(gcwMan == NULL)
			return;


		if(index == -1 || otherPressed){
			gcwMan->sendTurretAttackListTo(player,turretControl);
			return;
		}

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);
		if(listBox == NULL)
			return;

		uint64 targetID = listBox->getMenuObjectID(index);
		ManagedReference<SceneObject*> target = server->getObject(targetID);
		if(target == NULL || !target->isCreatureObject())
			return;

		CreatureObject* targetCreature = cast<CreatureObject*>(target.get());

		if(targetCreature == NULL)
			return;


		StringIdChatParameter param;
		if(targetCreature == turretData->getManualTarget()){
			param.setStringId("hq","already_attacking"); //Your selected target is already being attacked by this turret.
		} else {
			param.setStringId("hq","attack_targets"); // "Turret is now attacking %TO.");
			param.setTO(targetCreature);
		}


		player->sendSystemMessage(param);
		if(turretData->getManualFireTask() == NULL) {
			Reference<TurretFireManualTask*> task = new TurretFireManualTask(turretObject.castTo<TangibleObject*>(), player, targetCreature);
			task->execute();
		}
		turretData->setManualTarget(targetCreature);
		gcwMan->sendTurretAttackListTo(player,turretControl);

	}

};



#endif /* TURRETCONTROLSUICALLBACK_H_ */
