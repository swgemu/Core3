/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PURCHASETICKETCOMMAND_H_
#define PURCHASETICKETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/objects/player/sui/callbacks/TravelCouponUseSuiCallback.h"

class PurchaseTicketCommand : public QueueCommand {
public:

	PurchaseTicketCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SortedVector<QuadTreeEntry*> closeObjects;
		CloseObjectsVector* vec = (CloseObjectsVector*) creature->getCloseObjects();
		vec->safeCopyTo(closeObjects);

		bool nearTravelTerminal = false;
		SceneObject* travelTerminal = nullptr;

		for (int i = 0; i < closeObjects.size(); i++) {
			SceneObject* object = cast<SceneObject*>( closeObjects.get(i));
			if (object != nullptr && object->getGameObjectType() == SceneObjectType::TRAVELTERMINAL && checkDistance(creature, object, 8)) {
				nearTravelTerminal = true;
				travelTerminal = object;
				break;
			}

		}

		if (!nearTravelTerminal) {
			creature->sendSystemMessage("@travel:too_far"); // You are too far from the terminal to purchase a ticket.
			return GENERALERROR;
		}

		ManagedReference<CityRegion*> currentCity = creature->getCityRegion().get();

		int departureTax = 0;

		if (currentCity != nullptr){
			if (currentCity->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:city_cant_purchase_ticket"); //You are banned from using the services of this city. You cannot purchase a ticket.
				return GENERALERROR;
			}
			if(!currentCity->isClientRegion()){
				departureTax = currentCity->getTravelTax();
			}
		}

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr)
			return GENERALERROR;

		String departurePlanet, departurePoint, arrivalPlanet, arrivalPoint, type;
		bool roundTrip = true;

		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(departurePlanet);
			tokenizer.getStringToken(departurePoint);
			tokenizer.getStringToken(arrivalPlanet);
			tokenizer.getStringToken(arrivalPoint);
			if(tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(type);
				if (type == "single" || type == "0")
					roundTrip = false;
			}

		} catch(Exception& e) {
			return INVALIDPARAMETERS;
		}

		departurePlanet = departurePlanet.replaceAll("_", " ");
		departurePoint = departurePoint.replaceAll("_", " ");
		arrivalPlanet = arrivalPlanet.replaceAll("_", " ");
		arrivalPoint = arrivalPoint.replaceAll("_", " ");

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<Zone*> departureZone = zoneServer->getZone(departurePlanet);
		ManagedReference<Zone*> arrivalZone = zoneServer->getZone(arrivalPlanet);

		if (departureZone == nullptr)
			return GENERALERROR;

		if (arrivalZone == nullptr)
			return GENERALERROR;

		ManagedReference<PlanetManager*> pmDeparture = departureZone->getPlanetManager();
		ManagedReference<PlanetManager*> pmArrival = arrivalZone->getPlanetManager();

		if (!pmArrival->isExistingPlanetTravelPoint(arrivalPoint)) {
			creature->sendSystemMessage("@travel:no_location_found"); //No location was found for your destination.
			return INVALIDPARAMETERS;
		}

		if (!pmDeparture->isExistingPlanetTravelPoint(departurePoint)) {
			creature->sendSystemMessage("The given departure point was not found.");
			return INVALIDPARAMETERS;
		}

		Reference<PlanetTravelPoint*>  destPoint = pmArrival->getPlanetTravelPoint(arrivalPoint);

		if (destPoint == nullptr)
			return GENERALERROR;

		ManagedReference<CreatureObject*> arrivalShuttle = destPoint->getShuttle();

		if (arrivalShuttle == nullptr)
			return GENERALERROR;


		ManagedReference<CityRegion*> destCity = arrivalShuttle->getCityRegion().get();

		if (destCity != nullptr){
			if (destCity.get()->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:banned_from_that_city");  // You have been banned from traveling to that city by the city militia
				return GENERALERROR;
			}
		}

		//Check to see if this point can be reached from this location.
		if (!pmDeparture->isTravelToLocationPermitted(departurePoint, arrivalPlanet, arrivalPoint))
			return GENERALERROR;

		if (roundTrip && !pmArrival->isTravelToLocationPermitted(arrivalPoint, departurePlanet, departurePoint))
			return GENERALERROR; //If they are doing a round trip, make sure they can travel back.

		int baseFare = pmDeparture->getTravelFare(departurePlanet, arrivalPlanet);

		if (baseFare == 0) { // Make sure that the travel route is valid
			creature->sendSystemMessage("Invalid travel route specified.");
			return GENERALERROR;
		}

		//Make sure they have space in the inventory for the tickets before purchasing them.
		Locker _lock(inventory, creature);

		int inventorySize = inventory->getContainerObjectsSize();
		int spaceNeeded = roundTrip ? 2 : 1;

		if ((inventorySize + spaceNeeded) > (inventory->getContainerVolumeLimit() - 1)) {
			creature->sendSystemMessage("@error_message:inv_full"); //Your inventory is full.
			return GENERALERROR;
		}

		int fare = baseFare + departureTax;

		if (!roundTrip) {
			// New Player Travel Coupon
			bool hasCoupon = false;
			ManagedReference<SceneObject*> voucher = nullptr;

			uint32 couponCRC = STRING_HASHCODE("object/tangible/item/new_player/new_player_travel_coupon.iff");

			for (int i = 0; i < inventorySize; i++) {
				SceneObject* sceneO = inventory->getContainerObject(i);

				if (sceneO == nullptr)
					continue;

				if (sceneO->getServerObjectCRC() == couponCRC) {
					hasCoupon = true;
					voucher = sceneO;
				}
			}

			if (hasCoupon && creature->isPlayerCreature()) {
				_lock.release();

				PlayerObject* ghost = creature->getPlayerObject();

				if (ghost == nullptr)
					return GENERALERROR;

				ManagedReference<SuiMessageBox*> couponSui = new SuiMessageBox(creature, SuiWindowType::TRAVEL_TICKET_SELECTION);
				couponSui->setCallback(new TravelCouponUseSuiCallback(zoneServer, voucher, fare, departurePlanet, departurePoint, arrivalPlanet, arrivalPoint));
				couponSui->setPromptTitle("@new_player:travel_coupon");
				StringBuffer prompt;
				prompt << "@new_player:travel_coupon_use_text_option" <<  " " << fare;
				couponSui->setPromptText(prompt.toString());
				couponSui->setOkButton(true, "@new_player:travel_coupon_use_coupon_button");
				couponSui->setCancelButton(true, "@new_player:travel_coupon_pay_credits_button");
				couponSui->setUsingObject(travelTerminal);
				couponSui->setForceCloseDistance(10);
				ghost->addSuiBox(couponSui);
				creature->sendMessage(couponSui->generateMessage());

				return GENERALERROR;
			}
		}

		if (roundTrip)
			fare *= 2;

		//Check if they have funds.
		int bank = creature->getBankCredits();
		int cash = creature->getCashCredits();

		if (bank < fare) {
			int diff = fare - bank;

			if (diff > cash) {
				ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, 0);
				suiBox->setPromptTitle("");
				suiBox->setPromptText("You do not have sufficient funds for that.");

				creature->sendMessage(suiBox->generateMessage());
				creature->sendSystemMessage("@travel:short_funds"); //You do not have enough money to complete the ticket purchase.
				return GENERALERROR;
			}

			TransactionLog trxBank(creature, TrxCode::TRAVELSYSTEM, bank, false);
			trxBank.addState("departurePlanet", departurePlanet);
			trxBank.addState("departurePoint", departurePoint);
			trxBank.addState("arrivalPlanet", arrivalPlanet);
			trxBank.addState("arrivalPoint", arrivalPoint);

			creature->subtractBankCredits(bank); //Take all from the bank, since they didn't have enough to cover.

			TransactionLog trxCash(creature, TrxCode::TRAVELSYSTEM, diff, true);
			trxCash.groupWith(trxBank);
			trxCash.addState("departurePlanet", departurePlanet);
			trxCash.addState("departurePoint", departurePoint);
			trxCash.addState("arrivalPlanet", arrivalPlanet);
			trxCash.addState("arrivalPoint", arrivalPoint);

			creature->subtractCashCredits(diff); //Take the rest from the cash.
			trxCash.groupWith(trxBank);
			trxBank.commit();
		} else {
			TransactionLog trx(creature, TrxCode::TRAVELSYSTEM, fare, false);
			trx.addState("departurePlanet", departurePlanet);
			trx.addState("departurePoint", departurePoint);
			trx.addState("arrivalPlanet", arrivalPlanet);
			trx.addState("arrivalPoint", arrivalPoint);

			creature->subtractBankCredits(fare); //Take all of the fare from the bank.
			trx.commit();
		}


		StringIdChatParameter params("@base_player:prose_pay_acct_success"); //You successfully make a payment of %DI credits to %TO.
		params.setDI(baseFare + (roundTrip * baseFare));
		params.setTO("@money/acct_n:travelsystem"); //the Galactic Travel Commission

		creature->sendSystemMessage(params);

		ManagedReference<SceneObject*> ticket1 = pmDeparture->createTicket(departurePoint, arrivalPlanet, arrivalPoint);

		if (ticket1 == nullptr) {
			creature->sendSystemMessage("Error creating travel ticket.");
			return GENERALERROR;
		}

		if (inventory->transferObject(ticket1, -1, true)) {
			ticket1->sendTo(creature, true);
		} else {
			ticket1->destroyObjectFromDatabase(true);
			creature->sendSystemMessage("Error transferring travel ticket to inventory.");
			return GENERALERROR;
		}

		if (roundTrip) {
			ManagedReference<SceneObject*> ticket2 = pmArrival->createTicket(arrivalPoint, departurePlanet, departurePoint);

			if (inventory->transferObject(ticket2, -1, true)) {
				ticket2->sendTo(creature, true);
			} else {
				ticket2->destroyObjectFromDatabase(true);
				creature->sendSystemMessage("Error transferring round-trip travel ticket to inventory.");
				return GENERALERROR;
			}
		}
		_lock.release();

		if(currentCity != nullptr && !currentCity->isClientRegion() && departureTax > 0) {
			Locker clocker(currentCity, creature);
			int taxPaid = departureTax + (roundTrip * departureTax);
			currentCity->addToCityTreasury(taxPaid);

			StringIdChatParameter param("@city/city:city_ticket_pay"); // You pay a tax of %DI credits to the local City Travel Authority.
			param.setDI(taxPaid);

			creature->sendSystemMessage(param);
		}

		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, 0);
		suiBox->setPromptTitle("");
		suiBox->setPromptText("@travel:ticket_purchase_complete"); //Ticket purchase complete

		creature->sendMessage(suiBox->generateMessage());

		return SUCCESS;
	}

};

#endif //PURCHASETICKETCOMMAND_H_
