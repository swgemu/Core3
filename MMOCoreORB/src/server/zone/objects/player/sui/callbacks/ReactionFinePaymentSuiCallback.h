#ifndef REACTIONFINEPAYMENTSUICALLBACK_H_
#define REACTIONFINEPAYMENTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class ReactionFinePaymentSuiCallback : public SuiCallback {

public:

	ReactionFinePaymentSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed || creature == NULL)
			return;

		if(!creature->isPlayerCreature())
			return;

		ManagedReference<SceneObject*> object = sui->getUsingObject();
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (object == NULL || playerObject == NULL)
			return;

		ManagedReference<CreatureObject*> emoteTarget = (object).castTo<CreatureObject*>();

		if (emoteTarget == NULL)
			return;

		int playerCredits = creature->getCashCredits();
		int totalFine = playerObject->getReactionFines();

		ChatManager* chatManager = server->getChatManager();
		CreatureManager* creatureManager = creature->getZone()->getCreatureManager();

		if (totalFine > playerCredits) {
			if (totalFine > 1000000) {
				totalFine = 1000000;
				chatManager->broadcastMessage(emoteTarget, creatureManager->getReactionQuip(41), 0, 0, 0);
			}

			creature->subtractCashCredits(playerCredits);
			int remainingFine = totalFine - playerCredits;
			playerObject->setReactionFines(remainingFine);

			String quip = creatureManager->getReactionQuip(6 + System::random(6));
			chatManager->broadcastMessage(emoteTarget, quip, 0, 0, 0);

		} else {
			// TODO: subtract additional credits if player can afford (see st_response_00 - st_response_05)
			creature->subtractCashCredits(totalFine);
			playerObject->setReactionFines(0);

			String quip = creatureManager->getReactionQuip(42 + System::random(3));
			chatManager->broadcastMessage(emoteTarget, quip, 0, 0, 0);

		}

	}
};

#endif /* REACTIONFINEPAYMENTSUICALLBACK_H_ */
