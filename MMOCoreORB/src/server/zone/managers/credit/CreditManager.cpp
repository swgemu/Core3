//
// Created by vagrant on 9/2/17.
//

#include "CreditManager.h"


void CreditManager::addBankCredits(uint64 creatureID, int amount, bool notifyClient) {
	ManagedReference<CreditObject*> obj = CreditManager::getCreditObject(creatureID);

	if (obj == NULL)
		return;

	Locker locker(obj);
	obj->setBankCredits(obj->getBankCredits()+amount, notifyClient);
}
void CreditManager::addCashCredits(uint64 creatureID, int amount, bool notifyClient) {
	ManagedReference<CreditObject*> obj = CreditManager::getCreditObject(creatureID);

	if (obj == NULL)
		return;

	Locker locker(obj);
	obj->setCashCredits(obj->getCashCredits()+amount, notifyClient);
}

bool CreditManager::subtractBankCredits(uint64 creatureID, int amount, bool notifyClient) {
	ManagedReference<CreditObject*> obj = CreditManager::getCreditObject(creatureID);

	if (obj == NULL)
		return false;

	Locker locker(obj);
	int newCredits = obj->getBankCredits() - amount;

	if(newCredits < 0)
		return false;

	obj->setBankCredits(newCredits, notifyClient);

	return true;
}

bool CreditManager::subtractCashCredits(uint64 creatureID, int amount, bool notifyClient) {
	ManagedReference<CreditObject*> obj = CreditManager::getCreditObject(creatureID);

	if (obj == NULL)
		return false;

	Locker locker(obj);

	int newCredits = obj->getCashCredits() - amount;

	if (newCredits < 0)
		return false;

	obj->setCashCredits(newCredits, notifyClient);

	return true;
}

bool CreditManager::verifyBankCredits(uint64 creatureID, int amount) {
	ManagedReference<CreditObject*> obj = CreditManager::getCreditObject(creatureID);

	if (obj == NULL)
		return false;

	if (amount < 0)
		return false;

	if (obj->getBankCredits() < amount)
		return false;

	return true;
}

bool CreditManager::verifyCashCredits(uint64 creatureID, int amount) {
	ManagedReference<CreditObject*> obj = CreditManager::getCreditObject(creatureID);

	if (obj == NULL)
		return false;

	if (amount < 0)
		return false;

	if (obj->getCashCredits() < amount)
		return false;

	return true;
}

ManagedReference<CreditObject*> CreditManager::getCreditObject(uint64 creoID) {
	static const uint64 databaseID = ObjectDatabaseManager::instance()->getDatabaseID("credits");

	uint64 oid = ((creoID & 0x0000FFFFFFFFFFFFull) | (databaseID << 48));

	ManagedReference<CreditObject*> creditObj =  Core::getObjectBroker()->lookUp(oid).castTo<CreditObject*>();

	if (creditObj == NULL) {
		ManagedReference<CreatureObject*> creo = Core::getObjectBroker()->lookUp(creoID).castTo<CreatureObject*>();
		if (creo == NULL)
			return NULL;

		Locker locker(creo);
		creditObj = creo->getCreditObject();
	}

	return creditObj;
}