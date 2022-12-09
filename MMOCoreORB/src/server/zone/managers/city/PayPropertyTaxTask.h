/*
 * PayCityTaxTask.h
 *
 *  Created on: Jul 30, 2013
 *      Author: swgemu
 */

#ifndef PAYCITYTAXTASK_H_
#define PAYCITYTAXTASK_H_

#include "server/zone/objects/region/NewCityRegion.h"

class PayPropertyTaxTask : public Task {
	ManagedWeakReference<NewCityRegion*> cityObject;
	float amount;
public:
	PayPropertyTaxTask(NewCityRegion* city, float tax) {

		cityObject = city;
		amount = tax;
	}

	void run() {

		ManagedReference<NewCityRegion*> strongRefCity = cityObject.get();

		if (strongRefCity == nullptr)
			return;

		Locker lock(strongRefCity);
		strongRefCity->addToCityTreasury(amount);
	}
};

#endif /* PAYCITYTAXTASK_H_ */
