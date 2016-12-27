/*
 * PayCityTaxTask.h
 *
 *  Created on: Jul 30, 2013
 *      Author: swgemu
 */

#ifndef PAYCITYTAXTASK_H_
#define PAYCITYTAXTASK_H_

#include "server/zone/objects/region/CityRegion.h"

class PayPropertyTaxTask : public Task {
	ManagedWeakReference<CityRegion*> cityObject;
	float amount;
public:
	PayPropertyTaxTask(CityRegion* city, float tax) {

		cityObject = city;
		amount = tax;
	}

	void run() {

		ManagedReference<CityRegion*> strongRefCity = cityObject.get();

		if (strongRefCity == NULL)
			return;

		Locker lock(strongRefCity);
		strongRefCity->addToCityTreasury(amount);
	}
};

#endif /* PAYCITYTAXTASK_H_ */
