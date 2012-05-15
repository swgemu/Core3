/*
 * LightsaberCrystalTuneSuiCallback.h
 *
 *  Created on: Apr 12, 2012
 *      Author: katherine
 */

#ifndef LIGHTSABERCRYSTALTUNESUICALLBACK_H_
#define LIGHTSABERCRYSTALTUNESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class LightsaberCrystalTuneSuiCallback: public SuiCallback {

public:
	LightsaberCrystalTuneSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed,
			Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		SuiMessageBox* messageBox = cast<SuiMessageBox*>(sui);

		if (!creature->isPlayerCreature())
			return;

		if (!cancelPressed) {
			ManagedReference<LightsaberCrystalComponent*> crystal = cast<LightsaberCrystalComponent*>(sui->getUsingObject());

			crystal->tuneCrystal(creature);
		}
	}
};


#endif /* LIGHTSABERCRYSTALTUNESUICALLBACK_H_ */
