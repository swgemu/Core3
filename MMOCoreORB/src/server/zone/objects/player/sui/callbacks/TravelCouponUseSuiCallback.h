#ifndef TRAVELCOUPONUSESUICALLBACK_H_
#define TRAVELCOUPONUSESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class TravelCouponUseSuiCallback : public SuiCallback {
	ManagedReference<SceneObject*> voucher;
	int fare;
	String departurePlanet;
	String departurePoint;
	String arrivalPlanet;
	String arrivalPoint;

public:
	TravelCouponUseSuiCallback(ZoneServer* server, SceneObject* vouch, int travelFare, String departurePl, String departurePo, String arrivalPl, String arrivalPo) : SuiCallback(server) {
		voucher = vouch;
		fare = travelFare;
		departurePlanet = departurePl;
		departurePoint = departurePo;
		arrivalPlanet = arrivalPl;
		arrivalPoint = arrivalPo;
	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (player == nullptr || voucher == nullptr || server == nullptr)
			return;

		ManagedReference<Zone*> departureZone = server->getZone(departurePlanet);

		if (departureZone == nullptr)
			return;

		ManagedReference<PlanetManager*> pmDeparture = departureZone->getPlanetManager();

		if (pmDeparture == nullptr)
			return;

		Locker lock(player);

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory == nullptr)
			return;

		Locker clock(inventory, player);

		int inventorySize = inventory->getContainerObjectsSize();

		if (inventorySize + 1 > inventory->getContainerVolumeLimit()) {
			player->sendSystemMessage("@error_message:inv_full"); //Your inventory is full.
			return;
		}

		ManagedReference<SceneObject*> ticket = pmDeparture->createTicket(departurePoint, arrivalPlanet, arrivalPoint);

		if (ticket == nullptr) {
			return ;
		}

		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed) {
			// Player selected to use credits instead of their voucher
			int bank = player->getBankCredits();
			int cash = player->getCashCredits();

			if (bank < fare) {
				int diff = fare - bank;

				if (diff > cash) {
					ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, 0);
					suiBox->setPromptTitle("");
					suiBox->setPromptText("You do not have sufficient funds for that.");

					player->sendMessage(suiBox->generateMessage());
					player->sendSystemMessage("@travel:short_funds"); //You do not have enough money to complete the ticket purchase.
					return;
				}

				TransactionLog trxBank(player, TrxCode::TRAVELSYSTEM, bank, false);
				trxBank.addState("departurePlanet", departurePlanet);
				trxBank.addState("departurePoint", departurePoint);
				trxBank.addState("arrivalPlanet", arrivalPlanet);
				trxBank.addState("arrivalPoint", arrivalPoint);

				player->subtractBankCredits(bank); //Take all from the bank, since they didn't have enough to cover.

				TransactionLog trxCash(player, TrxCode::TRAVELSYSTEM, diff, true);
				trxCash.groupWith(trxBank);
				trxCash.addState("departurePlanet", departurePlanet);
				trxCash.addState("departurePoint", departurePoint);
				trxCash.addState("arrivalPlanet", arrivalPlanet);
				trxCash.addState("arrivalPoint", arrivalPoint);

				player->subtractCashCredits(diff); //Take the rest from the cash.
				trxCash.groupWith(trxBank);
				trxBank.commit();
			} else {
				TransactionLog trx(player, TrxCode::TRAVELSYSTEM, fare, false);
				trx.addState("departurePlanet", departurePlanet);
				trx.addState("departurePoint", departurePoint);
				trx.addState("arrivalPlanet", arrivalPlanet);
				trx.addState("arrivalPoint", arrivalPoint);

				player->subtractBankCredits(fare); //Take all of the fare from the bank.
				trx.commit();
			}
		} else {
			TransactionLog trx(player, TrxCode::TRAVELSYSTEM, false);
			trx.addState("departurePlanet", departurePlanet);
			trx.addState("departurePoint", departurePoint);
			trx.addState("arrivalPlanet", arrivalPlanet);
			trx.addState("arrivalPoint", arrivalPoint);
			trx.addState("travelCoupon", true);
			trx.addState("travelCouponId", voucher->getObjectID());

			Locker vlock(voucher, inventory);

			voucher->destroyObjectFromWorld(true);
			voucher->destroyObjectFromDatabase();
			trx.commit();
		}

		if (inventory->transferObject(ticket, -1, true)) {
			ticket->sendTo(player, true);
		} else {
			ticket->destroyObjectFromDatabase(true);
			return;
		}

		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, 0);
		suiBox->setPromptTitle("");
		suiBox->setPromptText("@travel:ticket_purchase_complete"); //Ticket purchase complete

		player->sendMessage(suiBox->generateMessage());
	}
};

#endif /* TRAVELCOUPONUSESUICALLBACK_H_ */