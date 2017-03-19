#ifndef REACTIONFINEPAYMENTSUICALLBACK_H_
#define REACTIONFINEPAYMENTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class ReactionFinePaymentSuiCallback : public SuiCallback {

public:

	ReactionFinePaymentSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isMessageBox() || creature == NULL)
			return;

		if(!creature->isPlayerCreature())
			return;

		ManagedReference<SceneObject*> object = sui->getUsingObject().get();
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (object == NULL || playerObject == NULL)
			return;

		ManagedReference<CreatureObject*> emoteTarget = (object).castTo<CreatureObject*>();

		if (emoteTarget == NULL)
			return;

		int playerCredits = creature->getCashCredits();
		int totalFine = playerObject->getReactionFines();

		ChatManager* chatManager = server->getChatManager();
		ReactionManager* reactionManager = server->getReactionManager();

		if (chatManager == NULL || reactionManager == NULL)
			return;

		Locker clocker(emoteTarget, creature);

		if (totalFine > playerCredits) {
			if (totalFine > 1000000) {
				totalFine = 1000000;
				chatManager->broadcastChatMessage(emoteTarget, reactionManager->getReactionQuip(41), 0, 0, emoteTarget->getMoodID());
			}

			creature->subtractCashCredits(playerCredits);
			playerObject->subtractFromReactionFines(playerCredits);

			emoteTarget->doAnimation("point_accusingly");
			String quip = reactionManager->getReactionQuip(6 + System::random(6));
			chatManager->broadcastChatMessage(emoteTarget, quip, 0, 0, emoteTarget->getMoodID());

		} else {
			int randomQuip = System::random(5);
			String tauntMsg = "laugh_pointing";

			if (playerCredits > totalFine * 1000) {
				totalFine += (totalFine / 10) * (5 + System::random(15)); // Steals 50% to 200% more
			} else if (playerCredits > totalFine * 100) {
				totalFine += (totalFine / 10) * (3 + System::random(12)); // Steals 30% to 150% more
			} else if (playerCredits > totalFine * 10) {
				totalFine += (totalFine / 10) * (1 + System::random(9)); // Steals 10% to 100% more
			} else {
				tauntMsg = "point_accusingly";
				randomQuip = 42 + System::random(3);
			}
			creature->subtractCashCredits(totalFine);
			playerObject->setReactionFines(0);

			emoteTarget->doAnimation(tauntMsg);
			String quip = reactionManager->getReactionQuip(randomQuip);
			chatManager->broadcastChatMessage(emoteTarget, quip, 0, 0, emoteTarget->getMoodID());

		}

	}
};

#endif /* REACTIONFINEPAYMENTSUICALLBACK_H_ */
