#include "engine/engine.h"
#include "engine/log/Logger.h"

#include "server/zone/objects/creature/credits/CreditObject.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/credit/CreditManager.h"

void CreditObjectImplementation::setCashCredits(int credits, bool notifyClient) {
	if (cashCredits == credits)
		return;

	E3_ASSERT(credits >= 0);

	cashCredits = credits;

	if (notifyClient) {
		Reference<CreatureObject*> creo = owner.get();
		if (creo == nullptr)
			return;

		DeltaMessage *msg = new DeltaMessage(creo->getObjectID(), 'CREO', 1);
		msg->startUpdate(0x01);
		msg->insertInt(cashCredits);
		msg->close();
		creo->sendMessage(msg);
	}
}

WeakReference<CreatureObject*> CreditObjectImplementation::getOwner() {
	return owner;
}

void CreditObjectImplementation::setOwner(CreatureObject* obj) {
	ownerObjectID = obj->getObjectID();
	owner = obj;
}

uint64 CreditObjectImplementation::getOwnerObjectID() const {
	return ownerObjectID;
}

void CreditObjectImplementation::setBankCredits(int credits, bool notifyClient) {
	if (bankCredits == credits)
		return;

	E3_ASSERT(credits >= 0);

	bankCredits = credits;

	if (notifyClient) {
		Reference<CreatureObject*> creo = owner.get();
		if (creo == nullptr)
			return;

		DeltaMessage *msg = new DeltaMessage(creo->getObjectID(), 'CREO', 1);
		msg->startUpdate(0x00);
		msg->insertInt(bankCredits);
		msg->close();
		creo->sendMessage(msg);
	}
}

void CreditObjectImplementation::transferCredits(int cash, int bank, bool notifyClient) {
	if (cash < 0 || bank < 0 || cash > CreditObject::CREDITCAP || bank > CreditObject::CREDITCAP) {
		error() << "ERROR: invalid call to transferCredits(cash=" << cash << ", bank=" << bank << "), current: " << *this;
		return;
	}

	if ((uint32) cashCredits + (uint32) bankCredits != (uint32) cash + (uint32) bank) {
		error() << "WARNING: unbalanced call to transferCredits(cash=" << cash << ", bank=" << bank << "), current: " << *this;
		return;
	}

	setCashCredits(cash, notifyClient);
	setBankCredits(bank, notifyClient);
}

void CreditObjectImplementation::subtractBankCredits(int credits, bool notifyClient) {
	if (credits < 0) {
		error() << "WARNING: Negative subtractBankCredits(credits=" << credits << "), current: " << *this;
		return;
	}

	if (credits > bankCredits) {
		error() << "WARNING: Overdraft subtractBankCredits(credits=" << credits << "), current: " << *this;
		credits -= bankCredits;
		clearBankCredits(notifyClient);

		if (credits > cashCredits) {
			clearCashCredits(notifyClient);
			error() << "WARNING: Player is now bankrupt, current: " << *this;
		} else {
			subtractCashCredits(credits, notifyClient);
		}

		return;
	}

	setBankCredits(bankCredits - credits, notifyClient);
}

void CreditObjectImplementation::subtractCashCredits(int credits, bool notifyClient) {
	if (credits < 0) {
		error() << "WARNING: Negative subtractCashCredits(credits=" << credits << "), current: " << *this;
		return;
	}

	if (credits > cashCredits) {
		error() << "WARNING: Overdraft subtractCashCredits(credits=" << credits << "), current: " << *this;
		credits -= cashCredits;
		clearCashCredits(notifyClient);

		if (credits > bankCredits) {
			clearBankCredits(notifyClient);
			error() << "WARNING: Player is now bankrupt, current: " << *this;
		} else {
			subtractBankCredits(credits, notifyClient);
		}

		return;
	}

	setCashCredits(cashCredits - credits, notifyClient);
}

bool CreditObjectImplementation::subtractCredits(int credits, bool notifyClient, bool bankFirst) {
	if (credits < 0) {
		error() << "WARNING: Negative subtractCredits(credits=" << credits << "), current: " << *this;
		return false;
	}

	if (credits > cashCredits + bankCredits) {
		return false;
	}

	if (bankFirst) {
		if (bankCredits > credits) {
			subtractBankCredits(credits, notifyClient);
		} else {
			credits -= bankCredits;
			clearBankCredits(notifyClient);
			subtractCashCredits(credits, notifyClient);
		}
	} else {
		if (cashCredits > credits) {
			subtractCashCredits(credits, notifyClient);
		} else {
			credits -= cashCredits;
			clearCashCredits(notifyClient);
			subtractBankCredits(credits, notifyClient);
		}
	}

	return true;
}

void CreditObjectImplementation::addBankCredits(int credits, bool notifyClient) {
	if (credits < 0) {
		error() << "WARNING: Negative addBankCredits(credits=" << credits << "), current: " << *this;
		return;
	}

	uint64 newBalance = (uint64)bankCredits + (uint64)credits;

	if (newBalance > CreditObject::CREDITCAP) {
		error() << "WARNING: Overflow addBankCredits(credits=" << credits << "), current: " << *this;
		setBankCredits(CreditObject::CREDITCAP, notifyClient);
		newBalance -= CreditObject::CREDITCAP;

		if (newBalance + (uint64)cashCredits > CreditObject::CREDITCAP) {
			setCashCredits(CreditObject::CREDITCAP, notifyClient);
			error() << "WARNING: Player is at CREDITCAP both for Cash and Bank, current: " << *this;
		} else {
			addCashCredits(newBalance, notifyClient);
		}

		return;
	}

	setBankCredits(bankCredits + credits, notifyClient);
}

void CreditObjectImplementation::addCashCredits(int credits, bool notifyClient) {
	if (credits < 0) {
		error() << "WARNING: Negative addCashCredits(credits=" << credits << "), current: " << *this;
		return;
	}

	uint64 newBalance = (uint64)cashCredits + (uint64)credits;

	if (newBalance > CreditObject::CREDITCAP) {
		error() << "WARNING: Overflow addCashCredits(credits=" << credits << "), current: " << *this;
		setCashCredits(CreditObject::CREDITCAP, notifyClient);
		newBalance -= CreditObject::CREDITCAP;

		if (newBalance + (uint64)bankCredits > CreditObject::CREDITCAP) {
			setBankCredits(CreditObject::CREDITCAP, notifyClient);
			error() << "WARNING: Player is at CREDITCAP both for Cash and Bank, current: " << *this;
		} else {
			addBankCredits(newBalance, notifyClient);
		}

		return;
	}

	setCashCredits(cashCredits + credits, notifyClient);
}

void CreditObjectImplementation::notifyLoadFromDatabase() {
	ManagedObjectImplementation::notifyLoadFromDatabase();

	if (cashCredits < 0) {
		error() << "Fixing negative cashCredits on load, current: " << *this;
		cashCredits = 0;
	}

	if (bankCredits < 0) {
		error() << "Fixing negative bankCredits on load, current: " << *this;
		bankCredits = 0;
	}
}

LoggerHelper CreditObjectImplementation::error() const {
	StackTrace::printStackTrace();

	auto creo = owner.get();

	return creo == nullptr ? CreditManager::instance()->error() : creo->error();
}

LoggerHelper CreditObjectImplementation::info(int forced) const {
	auto creo = owner.get();

	return creo == nullptr ? CreditManager::instance()->info(forced) : creo->info(forced);
}

LoggerHelper CreditObjectImplementation::debug() const {
	auto creo = owner.get();

	return creo == nullptr ? CreditManager::instance()->debug() : creo->debug();
}

String CreditObjectImplementation::toStringData() const {
	JSONSerializationType jsonData;
	jsonData["ownerObjectID"] = getOwnerObjectID();
	jsonData["bankCredits"] = bankCredits;
	jsonData["cashCredits"] = cashCredits;
	jsonData["objectID"] = _this.getReferenceUnsafeStaticCast()->_getObjectID();
	return jsonData.dump();
}
