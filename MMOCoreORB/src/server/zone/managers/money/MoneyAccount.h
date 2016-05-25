#ifndef MONEYACCOUNT_H_
#define MONEYACCOUNT_H_

#include "engine/engine.h"
#include "engine/core/ManagedObject.h"

class MoneyAccount : public ManagedObject {
	int accountId;
	int64 accountBalance;

	String accountStringId;

public:
	MoneyAccount(int id, int64 balance, String stringId) {
		accountId = id;
		accountBalance = balance;
		accountStringId = stringId;
	}

	~MoneyAccount() {
	}

	int getAccountId() {
		return accountId;
	}

	int64 getBalance() {
		return accountBalance;
	}

	void setBalance(int64 bal) {
		accountBalance = bal;
	}

	void setStringId(String id) {
		accountStringId = id;
	}

	String getStringId() {
		return accountStringId;
	}
};


#endif /* MONEYACCOUNT_H_ */
