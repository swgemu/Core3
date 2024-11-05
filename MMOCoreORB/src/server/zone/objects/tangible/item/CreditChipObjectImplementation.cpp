/*
 * CreditChipObjectImplementation.cpp
 *
 * Created on: 2024-11-05
 * Author: Hakry
 */

#include "server/zone/objects/tangible/item/CreditChipObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/transaction/TransactionLog.h"

void CreditChipObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr) {
		return;
	}

	menuResponse->addRadialMenuItem(RadialOptions::ITEM_USE, 3, "@space/space_loot:use_credit_chip"); // "Transfer credits to bank account"
}

int CreditChipObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr || selectedID != RadialOptions::ITEM_USE) {
		return 0;
	}

	if (!isASubChildOf(player)) {
		return 0;
	}

	auto thisCreditChip = _this.getReferenceUnsafeStaticCast();

	Locker clock(player, thisCreditChip);

	int totalValue = getUseCount();

	if (totalValue < 1) {
		destroyObjectFromWorld(true);
		destroyObjectFromDatabase(true);
		return 1;
	}

	// Clear the value so its worthless
	setUseCount(0);

	{
		TransactionLog trx(thisCreditChip, player, TrxCode::CREDITCHIPCLAIM, totalValue, false);
		player->addBankCredits(totalValue, true);
		trx.commit();
	}

	clock.release();

	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);

	return 1;
}

void CreditChipObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	TangibleObjectImplementation::fillAttributeList(alm, player);
}