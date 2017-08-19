/*
 * TaxNoPayMailTask.h
 *
 *  Created on: 16/11/2012
 *      Author: victor
 */

#ifndef TAXPAYMAILTASK_H_
#define TAXPAYMAILTASK_H_

#include "server/chat/ChatManager.h"
#include "server/zone/objects/region/CityRegion.h"

class TaxPayMailTask : public Task {
	Vector<uint64> citizens;
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

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		int totalIncome = 0;

		StringIdChatParameter params("city/city", "income_tax_paid_body");
		params.setDI(incomeTax);

		auto zoneServer = chatManager->getZoneServer();

		for (int i = 0; i < citizens.size(); ++i) {
			uint64 citizenOID = citizens.get(i);

			ManagedReference<SceneObject*> obj = zoneServer->getObject(citizenOID);

			if (obj == NULL)
				continue;

			CreatureObject* citizen = obj->asCreatureObject();

			if (citizen == NULL || !citizen->isPlayerCreature())
				continue;

			Locker lock(citizen);

			params.setTO(citizen->getDisplayedName());

			int bank = citizen->getBankCredits();

			if (bank < incomeTax) {
				lock.release();

				// Failed to Pay Income Tax!
				params.setStringId("city/city", "income_tax_nopay_body");
				chatManager->sendMail("@city/city:new_city_from", "@city/city:income_tax_nopay_subject", params, citizen->getFirstName(), NULL);

				// Citizen Failed to Pay Income Tax
				params.setStringId("city/city", "income_tax_nopay_mayor_body");
				chatManager->sendMail("@city/city:new_city_from", "@city/city:income_tax_nopay_mayor_subject", params, mayorName, NULL);

				continue;
			}

			citizen->subtractBankCredits(incomeTax);

			lock.release();

			// City Income Tax Paid
			params.setStringId("city/city", "income_tax_paid_body");
			chatManager->sendMail("@city/city:new_city_from", "@city/city:income_tax_paid_subject", params, citizen->getFirstName(), NULL);

			totalIncome += incomeTax;
		}

		Locker clocker(city);

		city->addToCityTreasury(totalIncome);
	}

	void addCitizen(uint64 citizen) {
		citizens.add(citizen);
	}

};

#endif /* TAXNOPAYMAILTASK_H_ */
