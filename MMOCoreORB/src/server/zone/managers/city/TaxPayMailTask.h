/*
 * TaxNoPayMailTask.h
 *
 *  Created on: 16/11/2012
 *      Author: victor
 */

#ifndef TAXPAYMAILTASK_H_
#define TAXPAYMAILTASK_H_

#include "engine/engine.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/region/CityRegion.h"

class TaxPayMailTask : public Task {
	Vector<ManagedReference<CreatureObject*> > citizens;
	String mayorName;
	ManagedReference<ChatManager*> chatManager;
	ManagedReference<CityRegion*> city;

	int incomeTax;
public:
	TaxPayMailTask(int tax, const String& mayor, ManagedReference<ChatManager*> chat, ManagedReference<CityRegion*> cityRegion) {
		mayorName = mayor;
		chatManager = chat;
		incomeTax = tax;
		city = cityRegion;
	}

	void run() {
		int totalIncome = 0;

		StringIdChatParameter params("city/city", "income_tax_paid_body");
		params.setDI(incomeTax);

		for (int i = 0; i < citizens.size(); ++i) {
			CreatureObject* citizen = citizens.get(i);

			Locker lock(citizen);

			params.setTO(citizen->getDisplayedName());

			int bank = citizen->getBankCredits();

			if (bank < incomeTax) {
				lock.release();

				params.setStringId("city/city", "income_tax_nopay_body");
				chatManager->sendMail("@city/city:new_city_from", "@city/city:income_tax_nopay_subject", params, citizen->getFirstName(), NULL);

				params.setStringId("city/city", "income_tax_nopay_mayor_body");
				chatManager->sendMail("@city/city:new_city_from", "@city/city:income_tax_nopay_mayor_subject", params, mayorName, NULL);

				continue;
			}

			citizen->subtractBankCredits(incomeTax);

			lock.release();
			params.setStringId("city/city", "income_tax_paid_body");
			chatManager->sendMail("@city/city:new_city_from", "@city/city:income_tax_paid_subject", params, citizen->getFirstName(), NULL);

			totalIncome += incomeTax;
		}

		Locker clocker(city);

		city->addToCityTreasury(totalIncome);
	}

	void addCitizen(CreatureObject* citizen) {
		citizens.add(citizen);
	}

};



#endif /* TAXNOPAYMAILTASK_H_ */
