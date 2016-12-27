/*
 * TurretControlSuiCallback.h
 *
 *  Created on: Jan 27, 2013
 *      Author: root
 */

#ifndef TURRETCONTROLSUICALLBACK_H_
#define TURRETCONTROLSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/installation/components/TurretFireTask.h"

class TurretControlSuiCallback : public SuiCallback {
	ManagedWeakReference<TangibleObject*> turretObject;
	ManagedWeakReference<TangibleObject*> turretControl;
public:
	TurretControlSuiCallback(ZoneServer* server, TangibleObject* turret, TangibleObject* terminal)
		: SuiCallback(server) {
		turretObject = turret;
		turretControl = terminal;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		if (args->size() < 1)
			return;

		Zone* zone = player->getZone();

		if (zone == NULL)
			return;

		GCWManager* gcwMan = zone->getGCWManager();

		if (gcwMan == NULL)
			return;

		ManagedReference<TangibleObject*> turret = turretObject.get();

		if (turret == NULL)
			return;

		TurretDataComponent* turretData  = cast<TurretDataComponent*>(turret->getDataObjectComponent()->get());

		if (turretData == NULL)
			return;

		ManagedReference<TangibleObject*> control = turretControl.get();

		if (control == NULL)
			return;

		TurretControlTerminalDataComponent* controlData = cast<TurretControlTerminalDataComponent*>(control->getDataObjectComponent()->get());

		if (controlData == NULL)
			return;

		if (!gcwMan->canUseTurret(turret, control, player)) {
			player->sendSystemMessage("@hq:in_use");  //  This turret control terminal is already in use."
			return;
		}

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());

		if (index == -1 || otherPressed) {
			Locker clocker(control, player);
			gcwMan->sendTurretAttackListTo(player, control);
			return;
		}

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);
		if (listBox == NULL)
			return;

		uint64 targetID = listBox->getMenuObjectID(index);
		ManagedReference<CreatureObject*> targetCreature = server->getObject(targetID).castTo<CreatureObject*>();

		if (targetCreature == NULL)
			return;

		Locker clocker(turret, player);

		turretData->setController(player);

		TurretFireTask* fireTask = cast<TurretFireTask*>(turretData->getFireTask());

		StringIdChatParameter param;

		if (fireTask != NULL && fireTask->isManualFireTask()) {
			if (targetCreature == turretData->getManualTarget()) {
				param.setStringId("hq","already_attacking"); //Your selected target is already being attacked by this turret.
				player->sendSystemMessage(param);

				clocker.release();

				Locker clock(control, player);

				gcwMan->sendTurretAttackListTo(player, control);
				return;
			}
		}

		turretData->scheduleFireTask(targetCreature, control);
		param.setStringId("hq","attack_targets"); // "Turret is now attacking %TO.");
		param.setTO(targetCreature->getObjectID());
		player->sendSystemMessage(param);

		clocker.release();

		Locker clock(control, player);
		gcwMan->sendTurretAttackListTo(player, control);

	}
};

#endif /* TURRETCONTROLSUICALLBACK_H_ */
