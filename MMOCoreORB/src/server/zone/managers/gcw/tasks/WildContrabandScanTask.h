/*
 * WildContrabandScanTask.h
 *
 *  Created on: Aug 30, 2020
 *      Author: loshult
 */

#ifndef WILDCONTRABANDSCANTASK_H_
#define WILDCONTRABANDSCANTASK_H_

#include "server/zone/managers/gcw/sessions/WildContrabandScanSession.h"
#include "server/zone/objects/creature/CreatureObject.h"

class WildContrabandScanTask : public Task {
	WeakReference<CreatureObject*> weakPlayer;

public:
	WildContrabandScanTask(CreatureObject* player) {
		weakPlayer = player;
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player != nullptr) {
			ManagedReference<WildContrabandScanSession*> scanSession = player->getActiveSession(SessionFacadeType::WILDCONTRABANDSCAN).castTo<WildContrabandScanSession*>();
			if (scanSession != nullptr) {
				scanSession->runWildContrabandScan();
			}
		}
	}
};

#endif /* WILDCONTRABANDSCANTASK_H_ */
