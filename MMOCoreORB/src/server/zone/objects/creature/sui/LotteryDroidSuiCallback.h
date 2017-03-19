#ifndef LOTTERYDROIDSUICALLBACK_H_
#define LOTTERYDROIDSUICALLBACK_H_


#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/eventperk/LotteryDroid.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class LotteryDroidSuiCallback : public SuiCallback {
private:
	int optionalArg;
public:
	LotteryDroidSuiCallback(ZoneServer* server, int optArg)
		: SuiCallback(server) {
		optionalArg = optArg;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		int windowType = suiBox->getWindowType();

		if (cancelPressed) {
			if (windowType == SuiWindowType::LOTTERY_DURATION_SETUP || windowType == SuiWindowType::LOTTERY_PAYOUT_SETUP || windowType == SuiWindowType::LOTTERY_COST_SETUP)
				player->sendSystemMessage("@event_perk:race_setup_canceled");
			else if (windowType == SuiWindowType::LOTTERY_ADD_CREDITS || windowType == SuiWindowType::LOTTERY_ADD_CREDITS_CONFIRM)
				player->sendSystemMessage("@event_perk:lottery_add_credits_cancel");
			return;
		}

		ManagedReference<SceneObject*> droid = suiBox->getUsingObject().get();

		if (droid == NULL)
			return;

		ManagedReference<LotteryDroid*> lotteryDroid = cast<LotteryDroid*>(droid.get());

		if (lotteryDroid == NULL)
			return;

		Locker lotteryDroidGuard(lotteryDroid, player);

		if (args->size() < 1)
			return;

		if (windowType == SuiWindowType::LOTTERY_DURATION_SETUP) {
			int index = Integer::valueOf(args->get(0).toString());

			lotteryDroid->setGameDuration(index);
			player->sendSystemMessage("@event_perk:lottery_dur_feedback @event_perk:lottery_dur_hours_" + String::valueOf(lotteryDroid->getGameDuration()));
			lotteryDroid->sendPayoutSUI(player);
		} else if (windowType == SuiWindowType::LOTTERY_PAYOUT_SETUP) {
			int index = Integer::valueOf(args->get(0).toString());
			lotteryDroid->setPayoutPercent(index);

			player->sendSystemMessage("@event_perk:lottery_payout_feedback @event_perk:lottery_payout_percent_" + String::valueOf(lotteryDroid->getPayoutPercent() * 100));
			lotteryDroid->sendTicketCostSUI(player);
		} else if (windowType == SuiWindowType::LOTTERY_COST_SETUP) {
			String arg1 = args->get(0).toString();
			int costValue = Integer::valueOf(arg1);

			if (arg1 == "" || costValue < 1) {
				player->sendSystemMessage("@event_perk:race_setup_nothing_entered");
				lotteryDroid->sendTicketCostSUI(player);
			} else {
				lotteryDroid->setTicketPrice(costValue);
				String msg = "@event_perk:ticket_cost_feedback";
				UnicodeString newMsg = StringIdManager::instance()->getStringId(msg.hashCode());
				player->sendSystemMessage(String::valueOf(costValue) + " " + newMsg.toString());
			}
		} else if (windowType == SuiWindowType::LOTTERY_ADD_CREDITS) {
			String arg1 = args->get(0).toString();
			int creditAmt = Integer::valueOf(arg1);

			if (arg1 == "" || creditAmt < 1) {
				player->sendSystemMessage("@event_perk:lottery_add_credits_error");
				lotteryDroid->sendAddCreditsSUI(player);
			} else if (creditAmt > player->getCashCredits()) {
				player->sendSystemMessage("@event_perk:lottery_add_credits_nsf");
				lotteryDroid->sendAddCreditsSUI(player);
			} else {
				PlayerObject* ghost = player->getPlayerObject();

				if (ghost == NULL)
					return;

				ManagedReference<SuiMessageBox*> confirmBox = new SuiMessageBox(player, SuiWindowType::LOTTERY_ADD_CREDITS_CONFIRM);
				confirmBox->setCallback(new LotteryDroidSuiCallback(server, creditAmt));
				confirmBox->setPromptTitle("@event_perk:lottery_add_credits_confirm_t"); // Confirm Fund Transfer

				String msg = "@event_perk:lottery_add_credits_confirm";
				UnicodeString newMsg = StringIdManager::instance()->getStringId(msg.hashCode());

				confirmBox->setPromptText(String::valueOf(creditAmt) + newMsg.toString()); // X credits will be added to the pot from your personal funds. Once added, the money will NOT be able to be retrieved. If this amount is correct, hit OK. Otherwise you may cancel.
				confirmBox->setUsingObject(suiBox->getUsingObject().get());
				confirmBox->setForceCloseDistance(32.f);
				confirmBox->setCancelButton(true, "@cancel");

				ghost->addSuiBox(confirmBox);
				player->sendMessage(confirmBox->generateMessage());
			}
		} else if (windowType == SuiWindowType::LOTTERY_ADD_CREDITS_CONFIRM) {
			int creditAmt = optionalArg;

			if (creditAmt < 1) {
				player->sendSystemMessage("@event_perk:lottery_add_credits_error");
				lotteryDroid->sendAddCreditsSUI(player);
			} else if (creditAmt > player->getCashCredits()) {
				player->sendSystemMessage("@event_perk:lottery_add_credits_nsf");
				lotteryDroid->sendAddCreditsSUI(player);
			} else {
				lotteryDroid->addToCreditPool(creditAmt);
				player->subtractCashCredits(creditAmt);
			}
		} else if (windowType == SuiWindowType::LOTTERY_REGISTRATION) {
			int ticketPrice = lotteryDroid->getTicketPrice();
			if (lotteryDroid->isCurrentPlayer(player->getObjectID())) {
				player->sendSystemMessage("@event_perk:lottery_reg_purchase_already");
				return;
			} else if (player->getCashCredits() < ticketPrice) {
				player->sendSystemMessage("@event_perk:lottery_add_credits_nsf");
				return;
			} else {
				lotteryDroid->addNewPlayer(player->getObjectID());
				player->subtractCashCredits(ticketPrice);
				lotteryDroid->addToCreditPool(ticketPrice);
				player->sendSystemMessage("@event_perk:lottery_reg_purchase_confirm");
			}
		}
	}
};

#endif /* LOTTERYDROIDSUICALLBACK_H_ */
