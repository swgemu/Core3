/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "MoneyManager.h"
#include "server/zone/managers/object/ObjectManager.h"

MoneyManager::MoneyManager() {
	setLoggingName("MoneyManager");
	setGlobalLogging(false);
	setLogging(false);
}

void MoneyManager::loadData() {
	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* statDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("statistics", true);

	if (statDatabase == NULL) {
		error("Could not load the statistic database.");
		return;
	}

	try {
		ObjectDatabaseIterator iterator(statDatabase);

		uint64 objectID;

		while (iterator.getNextKey(objectID)) {
			Reference<MoneyAccount*> acct = Core::getObjectBroker()->lookUp(objectID).castTo<MoneyAccount*>();

			if (acct == NULL) {
				printf("Grabbed money acct obj with oid of %lld is null\n", objectID);
			} else {
				printf("Grabbed money acct with oid of %lld and id of %i \n", objectID, acct->getAccountId());
			}

			if (acct != NULL && !moneyAccounts.contains(acct->getAccountId())) {
				printf("Database found money account id %i with stringid %s\n", acct->getAccountId(), acct->getStringId().toCharArray());
				moneyAccounts.put(acct->getAccountId(), acct);
			}
		}
	} catch (DatabaseException& e) {
		error("Database exception in MoneyManager::loadAccountObjects(): "	+ e.getMessage());
	}

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/money_manager.lua");

	LuaObject luaObject = lua->getGlobalObject("moneyAccountData");

	if (luaObject.isValidTable()) {
		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject accountData = luaObject.getObjectAt(i);

			if (accountData.isValidTable()) {
				int accountID = accountData.getIntAt(1);
				String stringID = accountData.getStringAt(2);

				if (!moneyAccounts.contains(accountID)) {
					ManagedReference<MoneyAccount*> acct = new MoneyAccount(accountID, 0, stringID);
					ObjectManager::instance()->persistObject(acct, 1, "statistics");
					printf("LUA added money account id %i with stringid %s, oid %lld\n", accountID, stringID.toCharArray(), acct->_getObjectID());
					moneyAccounts.put(accountID, acct);
				}
			}

			accountData.pop();
		}
	}

	luaObject.pop();

	info(String::valueOf(moneyAccounts.size()) + " money accounts loaded.", true);
}
