/*
 * BankTerminalSuiCallback.h
 *
 * Created on: October 13, 2013
 * by: zaphod
 */

#ifndef BANKTERMINALSUICALLBACK_H_
#define BANKTERMINALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class BankTerminalSuiCallback : public SuiCallback {
public:
	BankTerminalSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isBankTransferBox() || player == NULL || cancelPressed) {
			return;
		}

		if (args->size() < 2)
			return;

		int cash = Integer::valueOf(args->get(0).toString());
		int bank = Integer::valueOf(args->get(1).toString());

		SuiBankTransferBox* suiBank = cast<SuiBankTransferBox*>( sui);

		ManagedReference<SceneObject*> bankObject = suiBank->getBank();

		if (bankObject == NULL)
			return;

		if (!player->isInRange(bankObject, 5))
			return;

		uint32 currentCash = player->getCashCredits();
		uint32 currentBank = player->getBankCredits();

		if ((currentCash + currentBank) == ((uint32) cash + (uint32) bank)) {
			player->setCashCredits(cash);
			player->setBankCredits(bank);
		}

		player->sendSystemMessage("@base_player:bank_success");
	}
};

#endif /* BANKTERMINALSUICALLBACK_H_ */
