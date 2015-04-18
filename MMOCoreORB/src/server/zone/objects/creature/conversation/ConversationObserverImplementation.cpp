/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include <limits>
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/objects/player/sessions/ConversationSession.h"
#include "server/zone/packets/object/StopNpcConversation.h"

ConversationObserverImplementation::ConversationObserverImplementation(ConversationTemplate* conversationTemplate) {
	this->conversationTemplate = conversationTemplate;
}

int ConversationObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	//Verify needed parameters
	if (eventType != ObserverEventType::CONVERSE && eventType != ObserverEventType::STARTCONVERSATION &&
		eventType != ObserverEventType::SELECTCONVERSATION && eventType != ObserverEventType::STOPCONVERSATION &&
		eventType != ObserverEventType::POSITIONCHANGED) {
		//Incorrect event type.
		return 0;
	}

	if (observable == NULL)
		return 0;

	if (arg1 == NULL && eventType != ObserverEventType::POSITIONCHANGED)
		return 0;

	//Try to convert parameters to correct types.
	CreatureObject* npc = NULL;
	CreatureObject* player = NULL;
	int selectedOption;
	try {
		npc = cast<CreatureObject* >(observable);

		if (arg1 != NULL)
			player = cast<CreatureObject* >(arg1);

		if (arg2 < std::numeric_limits<int>::min()) {
			selectedOption = std::numeric_limits<int>::min();
		} else if (arg2 > std::numeric_limits<int>::max()) {
			selectedOption = std::numeric_limits<int>::max();
		} else {
			selectedOption = arg2;
		}
	} catch (...) {
		//Failed to convert parameters. Keep observer.
		return 0;
	}

	switch (eventType) {
	case ObserverEventType::POSITIONCHANGED:
		if (npc != NULL) { //the observable in this case is the player
			ManagedReference<ConversationSession*> session = npc->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession*>();

			if (session != NULL) {
				ManagedReference<CreatureObject*> sessionNpc = session->getNPC();

				if (sessionNpc == NULL || npc->getDistanceTo(sessionNpc) > 7.f) {
					cancelConversationSession(npc, session->getNPC().get(), true);
					return 0;
				}
			}

		}

		return 0;

	case ObserverEventType::STOPCONVERSATION:
		cancelConversationSession(player, npc);
		//Keep observer.
		return 0;

	case ObserverEventType::STARTCONVERSATION: {
		//Cancel any existing sessions.
		cancelConversationSession(player, npc);
		//Create a new session.
		createConversationSession(player, npc);
		createPositionObserver(player);
		break;
	}
	default:
		break;
	}

	//Select next conversation screen.
	Reference<ConversationScreen*> conversationScreen = getNextConversationScreen(player, selectedOption, npc);

	if (conversationScreen != NULL) {
		//Modify the conversation screen.
		conversationScreen = runScreenHandlers(player, npc, selectedOption, conversationScreen);
	}

	//Send the conversation screen to the player.
	sendConversationScreenToPlayer(player, npc, conversationScreen);

	if (conversationScreen == NULL) {
		cancelConversationSession(player, npc);
	}

	//Keep the observer.
	return 0;
}

void ConversationObserverImplementation::createConversationSession(CreatureObject* conversingPlayer, CreatureObject* npc) {
	conversingPlayer->addActiveSession(SessionFacadeType::CONVERSATION, new ConversationSession(npc));
}

void ConversationObserverImplementation::createPositionObserver(CreatureObject* player) {
	player->registerObserver(ObserverEventType::POSITIONCHANGED, _this.get());
}

void ConversationObserverImplementation::cancelConversationSession(CreatureObject* conversingPlayer, CreatureObject* npc, bool forceClose) {
	ManagedReference<Facade*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION);

	if (session != NULL) {
		session->cancelSession();
	}

	conversingPlayer->dropActiveSession(SessionFacadeType::CONVERSATION);

	conversingPlayer->dropObserver(ObserverEventType::POSITIONCHANGED, _this.get());

	if (forceClose && npc != NULL)
		conversingPlayer->sendMessage(new StopNpcConversation(conversingPlayer, npc->getObjectID()));
}

ConversationScreen* ConversationObserverImplementation::getNextConversationScreen(CreatureObject* conversingPlayer, int selectedOption, CreatureObject* conversingNPC) {
	//Get screen ID from last conversation screen.
	Reference<ConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession* >();
	/*String lastScreenId = "";
	if (session != NULL) {
		lastScreenId = session->getLastConversationScreenName();
	}*/

	//Get last conversation screen.
	Reference<ConversationScreen* > lastConversationScreen;

	if (session != NULL)
		lastConversationScreen = session->getLastConversationScreen();

	Reference<ConversationScreen* > nextConversationScreen;

	if (lastConversationScreen != NULL) {
		//Get the linked screen for the selected option.
		nextConversationScreen = conversationTemplate->getScreen(lastConversationScreen->getOptionLink(selectedOption));
	} else {
		//Get the initial screen.
		nextConversationScreen = conversationTemplate->getInitialScreen();
	}
	return nextConversationScreen;
}

ConversationScreen* ConversationObserverImplementation::runScreenHandlers(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	ConversationScreen* modifiedScreen = NULL;

	//Loop until a screen has been modified.
	while (modifiedScreen == NULL) {
		//Call appropriate screen handler.
		if (screenHandlers.contains(conversationScreen->getScreenID())) {
			//Copy the conversation screen to preserve the template.
			modifiedScreen = screenHandlers.get(conversationScreen->getScreenID())->handleScreen(conversingPlayer, conversingNPC, selectedOption, conversationScreen->cloneScreen());

			//Check if another screen should be handled
			if (modifiedScreen == NULL) {
				//Get next screen.
				String screenId = screenHandlers.get(conversationScreen->getScreenID())->getNextScreenId();
				conversationScreen = getConversationScreen(screenId);
				if (conversationScreen == NULL) {
					//No new screen found.
					return NULL;
				}
			}
		} else {
			//No screen handler found for this screen, exit loop and return it unmodified.
			modifiedScreen = conversationScreen;
		}
	}

	return modifiedScreen;
}

void ConversationObserverImplementation::sendConversationScreenToPlayer(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, ConversationScreen* conversationScreen) {
	if (conversationScreen != NULL) {
		//Send the screen to the player.
		conversationScreen->sendTo(conversingPlayer, conversingNPC);
	} else {
		//Clear screen ID from last conversation screen.
		Reference<ConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession* >();
		if (session != NULL) {
			session->setLastConversationScreen(NULL);
		}

		conversingPlayer->sendMessage(new StopNpcConversation(conversingPlayer, conversingNPC->getObjectID()));
	}
}
