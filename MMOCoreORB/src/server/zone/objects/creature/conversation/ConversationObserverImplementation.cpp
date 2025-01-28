/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include <limits>
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/player/sessions/ConversationSession.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

ConversationObserverImplementation::ConversationObserverImplementation(uint32 convoTemplateCRC) {
	conversationTemplateCRC = convoTemplateCRC;
}

int ConversationObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	// info(true) << "ConversationObserverImplementation::notifyObserverEvent -- Observer event type: " << eventType;

	//Verify needed parameters
	if (eventType != ObserverEventType::CONVERSE && eventType != ObserverEventType::STARTCONVERSATION &&
		eventType != ObserverEventType::SELECTCONVERSATION && eventType != ObserverEventType::STOPCONVERSATION &&
		eventType != ObserverEventType::POSITIONCHANGED) {
		//Incorrect event type.
		return 0;
	}

	if (observable == nullptr) {
		return 0;
	}

	if (arg1 == nullptr && eventType != ObserverEventType::POSITIONCHANGED) {
		return 0;
	}

	//Try to convert parameters to correct types.
	SceneObject* conversingObject = nullptr;
	CreatureObject* player = nullptr;
	int selectedOption = 0;

	try {
		conversingObject = cast<SceneObject* >(observable);

		if (arg1 != nullptr)
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

	if (conversingObject == nullptr)
		return 0;

	switch (eventType) {
	case ObserverEventType::POSITIONCHANGED: {
		// the observable (conversingObject) in this case is the player
		ManagedReference<ConversationSession*> session = conversingObject->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession*>();

		if (session == nullptr)
			return 1;

		ManagedReference<SceneObject*> sessionNpc = session->getNPC().get();

		if (sessionNpc == nullptr || (sessionNpc->isAiAgent() && !sessionNpc->checkInConversationRange(conversingObject))) {
			cancelConversationSession(conversingObject->asCreatureObject(), sessionNpc, true);
		} else if (sessionNpc->isShipAiAgent()) {
			auto spaceCommTask = conversingObject->getPendingTask("SpaceCommTimer");

			// Player already has a pending cancellation task
			if (spaceCommTask != nullptr && spaceCommTask->isScheduled()) {
				return 1;
			}

			if (!sessionNpc->checkInConversationRange(conversingObject)) {
				cancelConversationSession(conversingObject->asCreatureObject(), sessionNpc, true);
			}
		}

		return 0;
	}
	case ObserverEventType::STOPCONVERSATION: {
		if (player != nullptr) {
			cancelConversationSession(player, conversingObject, conversingObject->isShipObject());
		}

		if (conversingObject->isAiAgent()) {
			auto agent = conversingObject->asAiAgent();

			if (agent != nullptr && agent->getMovementState() == AiAgent::CONVERSING) {
				if (agent->getFollowObject().get() == nullptr) {
					agent->setMovementState(AiAgent::OBLIVIOUS);
				} else {
					agent->setMovementState(AiAgent::FOLLOWING);
				}
			}
		}

		//Keep observer.
		return 0;
	}
	case ObserverEventType::STARTCONVERSATION: {
		if (player != nullptr) {
			//Cancel any existing sessions.
			cancelConversationSession(player, conversingObject);

			//Create a new session.
			createConversationSession(player, conversingObject);

			createPositionObserver(player);
		}

		break;
	}
	default:
		break;
	}

	if (player == nullptr)
		return 0;

	// Select next conversation screen.
	Reference<ConversationScreen*> conversationScreen = getNextConversationScreen(player, selectedOption, conversingObject);

	if (conversationScreen != nullptr) {
		//Modify the conversation screen.
		conversationScreen = runScreenHandlers(player, conversingObject, selectedOption, conversationScreen);

		//Send the conversation screen to the player.
		sendConversationScreenToPlayer(player, conversingObject, conversationScreen);
	// Do not run cancel for ship agents due to taunts
	} else if (!conversingObject->isShipAiAgent()) {
		cancelConversationSession(player, conversingObject);
	}

	//Keep the observer.
	return 0;
}

void ConversationObserverImplementation::createConversationSession(CreatureObject* conversingPlayer, SceneObject* conversingNPC) {
	conversingPlayer->addActiveSession(SessionFacadeType::CONVERSATION, new ConversationSession(conversingNPC));
}

void ConversationObserverImplementation::createPositionObserver(CreatureObject* player) {
	player->registerObserver(ObserverEventType::POSITIONCHANGED, _this.getReferenceUnsafeStaticCast());
}

void ConversationObserverImplementation::cancelConversationSession(CreatureObject* conversingPlayer, SceneObject* conversingNPC, bool forceClose) {
	ManagedReference<Facade*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION);

	if (session != nullptr) {
		session->cancelSession();
	}

	conversingPlayer->dropActiveSession(SessionFacadeType::CONVERSATION);

	conversingPlayer->dropObserver(ObserverEventType::POSITIONCHANGED, _this.getReferenceUnsafeStaticCast());

	if (forceClose && conversingNPC != nullptr) {
		conversingPlayer->sendMessage(new StopNpcConversation(conversingPlayer, conversingNPC->getObjectID()));
	}

	// If the player manually ends the conversation, cancel their pending SpaceCommTimer task
	auto spaceCommTask = conversingPlayer->getPendingTask("SpaceCommTimer");

	if (spaceCommTask != nullptr) {
		if (spaceCommTask->isScheduled())
			spaceCommTask->cancel();

		conversingPlayer->removePendingTask("SpaceCommTimer");
	}
}

ConversationScreen* ConversationObserverImplementation::getNextConversationScreen(CreatureObject* conversingPlayer, int selectedOption, SceneObject* conversingNPC) {
	//Get screen ID from last conversation screen.
	Reference<ConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession* >();
	/*String lastScreenId = "";
	if (session != nullptr) {
		lastScreenId = session->getLastConversationScreenName();
	}*/

	ConversationTemplate* convoTemp = getConversationTemplate();

	//Get last conversation screen.
	Reference<ConversationScreen* > lastConversationScreen;

	if (session != nullptr)
		lastConversationScreen = session->getLastConversationScreen();

	Reference<ConversationScreen* > nextConversationScreen;

	if (lastConversationScreen != nullptr) {
		//Get the linked screen for the selected option.
		nextConversationScreen = convoTemp->getScreen(lastConversationScreen->getOptionLink(selectedOption));
	} else {
		//Get the initial screen.
		nextConversationScreen = convoTemp->getInitialScreen();
	}
	return nextConversationScreen;
}

ConversationScreen* ConversationObserverImplementation::runScreenHandlers(CreatureObject* conversingPlayer, SceneObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	ConversationScreen* modifiedScreen = nullptr;

	//Loop until a screen has been modified.
	while (modifiedScreen == nullptr) {
		//Call appropriate screen handler.
		if (screenHandlers.contains(conversationScreen->getScreenID())) {
			//Copy the conversation screen to preserve the template.
			modifiedScreen = screenHandlers.get(conversationScreen->getScreenID())->handleScreen(conversingPlayer, conversingNPC, selectedOption, conversationScreen->cloneScreen());

			//Check if another screen should be handled
			if (modifiedScreen == nullptr) {
				//Get next screen.
				String screenId = screenHandlers.get(conversationScreen->getScreenID())->getNextScreenId();
				conversationScreen = getConversationScreen(screenId);
				if (conversationScreen == nullptr) {
					//No new screen found.
					return nullptr;
				}
			}
		} else {
			//No screen handler found for this screen, exit loop and return it unmodified.
			modifiedScreen = conversationScreen;
		}
	}

	return modifiedScreen;
}

void ConversationObserverImplementation::sendConversationScreenToPlayer(CreatureObject* conversingPlayer, SceneObject* conversingNPC, ConversationScreen* conversationScreen) {
	if (conversationScreen != nullptr) {
		//Send the screen to the player.
		conversationScreen->sendTo(conversingPlayer, conversingNPC);
	} else {
		//Clear screen ID from last conversation screen.
		Reference<ConversationSession*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession* >();
		if (session != nullptr) {
			session->setLastConversationScreen(nullptr);
		}

		conversingPlayer->sendMessage(new StopNpcConversation(conversingPlayer, conversingNPC->getObjectID()));
	}
}

ConversationTemplate* ConversationObserverImplementation::getConversationTemplate() {
	return CreatureTemplateManager::instance()->getConversationTemplate(conversationTemplateCRC);
}
