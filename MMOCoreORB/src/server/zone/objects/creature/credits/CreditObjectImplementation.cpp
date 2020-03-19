#include "server/zone/objects/creature/credits/CreditObject.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

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
	owner = obj;
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
	if ((uint32) cashCredits + (uint32) bankCredits != (uint32) cash + (uint32) bank) {
		Reference<CreatureObject*> creo = owner.get();

		if (creo == nullptr)
			return;

		creo->error() << "WARNING: unbalanced call transferCredits(cash=" << cash << ", bank=" << bank << "), current: cashCredits=" << cashCredits << " bankCredits=" << bankCredits;
		return;
	}

	setCashCredits(cash, notifyClient);
	setBankCredits(bank, notifyClient);
}

void CreditObjectImplementation::subtractBankCredits(int credits, bool notifyClient) {
	if (credits > bankCredits) {
		Reference<CreatureObject*> creo = owner.get();

		if (creo == nullptr)
			return;

		creo->error() << "WARNING: Overdraft subtractBankCredits(credits=" << credits << "), current: cashCredits=" << cashCredits << " bankCredits=" << bankCredits;
		credits -= bankCredits;
		clearBankCredits(notifyClient);
		subtractCashCredits(credits, notifyClient);
		return;
	}

	setBankCredits(bankCredits - credits, notifyClient);
}

void CreditObjectImplementation::subtractCashCredits(int credits, bool notifyClient) {
	if (credits > cashCredits) {
		Reference<CreatureObject*> creo = owner.get();

		if (creo == nullptr)
			return;

		creo->error() << "WARNING: Overdraft subtractCashCredits(credits=" << credits << "), current: cashCredits=" << cashCredits << " bankCredits=" << bankCredits;
		credits -= cashCredits;
		clearCashCredits(notifyClient);
		subtractBankCredits(credits, notifyClient);
		return;
	}

	setCashCredits(cashCredits - credits, notifyClient);
}

bool CreditObjectImplementation::subtractCredits(int credits, bool notifyClient, bool bankFirst) {
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
	uint64 newBalance = (uint64)bankCredits + (uint64)credits;

	if (newBalance > CREDITCAP) {
		Reference<CreatureObject*> creo = owner.get();

		if (creo == nullptr)
			return;

		creo->error() << "WARNING: Overflow addBankCredits(credits=" << credits << "), current: cashCredits=" << cashCredits << " bankCredits=" << bankCredits;
		setBankCredits(CREDITCAP, notifyClient);
		addCashCredits(newBalance - CREDITCAP, notifyClient);
		return;
	}

	setBankCredits(bankCredits + credits, notifyClient);
}

void CreditObjectImplementation::addCashCredits(int credits, bool notifyClient) {
	uint64 newBalance = (uint64)cashCredits + (uint64)credits;

	if (newBalance > CREDITCAP) {
		Reference<CreatureObject*> creo = owner.get();

		if (creo == nullptr)
			return;

		creo->error() << "WARNING: Overflow addCashCredits(credits=" << credits << "), current: cashCredits=" << cashCredits << " bankCredits=" << bankCredits;
		setCashCredits(CREDITCAP, notifyClient);
		addBankCredits(newBalance - CREDITCAP, notifyClient);
		return;
	}

	setCashCredits(cashCredits + credits, notifyClient);
}

void CreditObjectImplementation::notifyLoadFromDatabase() {
	ManagedObjectImplementation::notifyLoadFromDatabase();

	if (cashCredits < 0)
		cashCredits = 0;

	if (bankCredits < 0)
		bankCredits = 0;
}
