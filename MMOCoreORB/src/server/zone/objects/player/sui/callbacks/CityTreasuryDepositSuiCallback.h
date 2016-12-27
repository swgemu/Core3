/*
 * CityTreasuryDepositSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYTREASURYDEPOSITSUICALLBACK_H_
#define CITYTREASURYDEPOSITSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/region/CityRegion.h"

class CityTreasuryDepositSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityTreasuryDepositSuiCallback(ZoneServer* server, CityRegion* region)
			: SuiCallback(server) {
		cityRegion = region;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isTransferBox() || player == NULL || cancelPressed || args->size() <= 0) {
			return;
		}

		int amount = Integer::valueOf(args->get(0).toString());

		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL)
			return;

		Locker lock(city, player);

		CityManager* cityManager = server->getCityManager();
		cityManager->depositToCityTreasury(city, player, amount);
	}
};

#endif /* CITYTREASURYDEPOSITSUICALLBACK_H_ */
