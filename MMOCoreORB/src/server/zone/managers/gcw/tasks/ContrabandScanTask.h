/*
 * ContrabandScanTask.h
 *
 *  Created on: Nov 3, 2016
 *      Author: loshult
 */

#ifndef CONTRABANDSCANTASK_H_
#define CONTRABANDSCANTASK_H_

#include "server/zone/managers/gcw/sessions/ContrabandScanSession.h"
#include "server/zone/objects/creature/CreatureObject.h"

class ContrabandScanTask : public Task {
	WeakReference<CreatureObject*> weakPlayer;

public:
	ContrabandScanTask(CreatureObject* player) {
		weakPlayer = player;
	}

	void run() {
		ManagedReference<CreatureObject*> player = weakPlayer.get();

		if (player != NULL) {
			ManagedReference<ContrabandScanSession*> scanSession = player->getActiveSession(SessionFacadeType::CONTRABANDSCAN).castTo<ContrabandScanSession*>();
			if (scanSession != NULL) {
				scanSession->runContrabandScan();
			}
		}
	}
};

#endif /* CONTRABANDSCANTASK_H_ */
