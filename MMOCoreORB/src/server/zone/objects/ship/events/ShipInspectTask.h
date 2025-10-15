/*
 *	Copyright <SWGEmu>
 *	See file COPYING for copying conditions.
 *
 *	ShipInspectTask.h
 *
 *	Created on: 2025-10-14
 *	Author: Hakry
 */

#ifndef SHIPINSPECTTASK_H_
#define SHIPINSPECTTASK_H_

#include "server/zone/objects/ship/ShipObject.h"

class ShipInspectTask: public Task, public Logger {

protected:
	ManagedWeakReference<CreatureObject*> weakPlayer;
	ManagedWeakReference<ShipObject*> weakTargetShip;

public:
	ShipInspectTask(CreatureObject* player, ShipObject* targetShip) : Task() {
		setLoggingName("ShipInspectTask");

		weakPlayer = player;
		weakTargetShip = targetShip;
	}

	void run();
};

#endif // SHIPINSPECTTASK_H_