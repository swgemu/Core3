//
// Created by vagrant on 9/2/17.
//

#include "CreditManager.h"

CreditManager::CreditManager() {
	Logger::setLoggingName("CreditManager");
}

void CreditManager::addBankCredits(uint64 creatureID, int amount, bool notifyClient) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return;

	Locker locker(obj);
	obj->addBankCredits(amount, notifyClient);
}

void CreditManager::addCashCredits(uint64 creatureID, int amount, bool notifyClient) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return;

	Locker locker(obj);
	obj->addCashCredits(amount, notifyClient);
}

bool CreditManager::subtractBankCredits(uint64 creatureID, int amount, bool notifyClient) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return false;

	Locker locker(obj);

	if (!obj->verifyBankCredits(amount)) {
		return false;
	}

	obj->subtractBankCredits(amount);

	return true;
}

bool CreditManager::subtractCashCredits(uint64 creatureID, int amount, bool notifyClient) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return false;

	Locker locker(obj);

	if (!obj->verifyCashCredits(amount)) {
		return false;
	}

	obj->subtractCashCredits(amount);

	return true;
}

void CreditManager::transferCredits(uint64 creatureID, int cash, int bank, bool notifyClient) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return;

	Locker locker(obj);

	obj->transferCredits(cash, bank, notifyClient);
}

bool CreditManager::verifyBankCredits(uint64 creatureID, int amount) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return false;

	return obj->verifyBankCredits(amount);
}

bool CreditManager::verifyCashCredits(uint64 creatureID, int amount) {
	auto obj = CreditManager::getCreditObject(creatureID);

	if (obj == nullptr)
		return false;

	return obj->verifyCashCredits(amount);
}

Reference<CreditObject*> CreditManager::getCreditObject(uint64 creoID) {
	static const uint64 databaseID = ObjectDatabaseManager::instance()->getDatabaseID("credits");

	uint64 oid = ((creoID & 0x0000FFFFFFFFFFFFull) | (databaseID << 48));

	Reference<CreditObject*> creditObj =  Core::getObjectBroker()->lookUp(oid).castTo<CreditObject*>();

	if (creditObj != nullptr && creditObj->getOwnerObjectID() == 0) {
		creditObj = nullptr;
	}

	if (creditObj == nullptr) {
		Reference<CreatureObject*> creo = Core::getObjectBroker()->lookUp(creoID).castTo<CreatureObject*>();

		if (creo == nullptr) {
			instance()->error() << "Failed to find credit object for creoID " << creoID;
			return nullptr;
		}

		Locker locker(creo);
		creditObj = creo->getCreditObject();
	}

	return creditObj;
}
