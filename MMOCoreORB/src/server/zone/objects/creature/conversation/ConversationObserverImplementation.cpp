/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include <limits>
#include "ConversationObserver.h"
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
			ManagedReference<ConversationSession*> session = dynamic_cast<ConversationSession*>(npc->getActiveSession(SessionFacadeType::CONVERSATION));

			if (session != NULL) {
				ManagedReference<CreatureObject*> sessionNpc = session->getNPC();

				if (sessionNpc == NULL || npc->getDistanceTo(sessionNpc) > 7.f) {
					cancelConversationSession(npc, session->getNPC(), true);
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

	if (conversationScreen == NULL)
		cancelConversationSession(player, npc);

	//Keep the observer.
	return 0;
}

void ConversationObserverImplementation::createConversationSession(CreatureObject* conversingPlayer, CreatureObject* npc) {
	conversingPlayer->addActiveSession(SessionFacadeType::CONVERSATION, new ConversationSession(npc));
}

void ConversationObserverImplementation::createPositionObserver(CreatureObject* player) {
	player->registerObserver(ObserverEventType::POSITIONCHANGED, _this);
}

void ConversationObserverImplementation::cancelConversationSession(CreatureObject* conversingPlayer, CreatureObject* npc, bool forceClose) {
	ManagedReference<Facade*> session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION);

	if (session != NULL) {
		session->cancelSession();
	}

	conversingPlayer->dropActiveSession(SessionFacadeType::CONVERSATION);

	conversingPlayer->dropObserver(ObserverEventType::POSITIONCHANGED, _this);

	if (forceClose && npc != NULL)
		conversingPlayer->sendMessage(new StopNpcConversation(conversingPlayer, npc->getObjectID()));
}

ConversationScreen* ConversationObserverImplementation::getNextConversationScreen(CreatureObject* conversingPlayer, int selectedOption, CreatureObject* conversingNPC) {
	//Get screen ID from last conversation screen.
	Reference<ConversationSession*> session = cast<ConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
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
			modifiedScreen = screenHandlers.get(conversationScreen->getScreenID())->handleScreen(conversingPlayer, conversingNPC, selectedOption, new ConversationScreen(*conversationScreen));

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
		ConversationSession* session = cast<ConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
		if (session != NULL) {
			session->setLastConversationScreen(NULL);
		}

		conversingPlayer->sendMessage(new StopNpcConversation(conversingPlayer, conversingNPC->getObjectID()));
	}
}
