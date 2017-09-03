//
// Created by vagrant on 9/2/17.
//

#ifndef CORE3_CREDITMANAGER_H
#define CORE3_CREDITMANAGER_H
#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/credits/CreditObject.h"

class CreditManager : public Singleton<CreditManager>, public Logger, public Object {
public:
	static void addBankCredits(uint64 creatureID, int amount, bool notifyClient = true);
	static void addCashCredits(uint64 creatureID, int amount, bool notifyClient = true);
	static bool subtractBankCredits(uint64 creatureID, int amount, bool notifyClient = true);
	static bool subtractCashCredits(uint64 creatureID, int amount, bool notifyClient = true);
	static bool verifyBankCredits(uint64 creatureID, int amount);
	static bool verifyCashCredits(uint64 creatureID, int amount);
	static ManagedReference<CreditObject*> getCreditObject(uint64 creoID);
};


#endif //CORE3_CREDITMANAGER_H
