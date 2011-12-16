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

ConversationObserverImplementation::ConversationObserverImplementation(ConversationTemplate* conversationTemplate) {
	this->conversationTemplate = conversationTemplate;
}

int ConversationObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2) {
	//Verify needed parameters
	if (eventType != ObserverEventType::CONVERSE && eventType != ObserverEventType::STARTCONVERSATION &&
		eventType != ObserverEventType::SELECTCONVERSATION && eventType != ObserverEventType::STOPCONVERSATION) {
		//Incorrect event type.
		return 0;
	}
	if (observable == NULL || arg1 == NULL) {
		return 0;
	}

	//Try to convert parameters to correct types.
	CreatureObject* npc;
	CreatureObject* player;
	int selectedOption;
	try {
		npc = cast<CreatureObject* >(observable);
		player = cast<CreatureObject* >(arg1);
		if (arg2 < std::numeric_limits<int>::min()) {
			selectedOption = std::numeric_limits<int>::min();
		} else if (arg2 > std::numeric_limits<int>::max()) {
			selectedOption = std::numeric_limits<int>::max();
		} else {
			selectedOption = arg2;
		}
	}
	catch (...) {
		//Failed to convert parameters. Keep observer.
		return 0;
	}

	//Call event method if conversation ended.
	if (eventType == ObserverEventType::STOPCONVERSATION) {
		//Cancel any active session.
		cancelConversationSession(player);
		//Keep observer.
		return 0;
	} else {
		if (eventType == ObserverEventType::STARTCONVERSATION) {
			//Cancel any existing sessions.
			cancelConversationSession(player);
			//Create a new session.
			createConversationSession(player);
		}
		//Select next conversation screen.
		ConversationScreen* conversationScreen = getNextConversationScreen(player, selectedOption);

		if (conversationScreen != NULL) {
			//Modify the conversation screen.
			conversationScreen = runScreenHandlers(player, npc, selectedOption, conversationScreen);
		}

		//Send the conversation screen to the player.
		sendConversationScreenToPlayer(player, npc, conversationScreen);
	}

	//Keep the observer.
	return 0;
}

void ConversationObserverImplementation::createConversationSession(CreatureObject* conversingPlayer) {
	conversingPlayer->addActiveSession(SessionFacadeType::CONVERSATION, new ConversationSession());
}

void ConversationObserverImplementation::cancelConversationSession(CreatureObject* conversingPlayer) {
	Facade* session = conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION);
	if (session != NULL) {
		session->cancelSession();
	}
	conversingPlayer->dropActiveSession(SessionFacadeType::CONVERSATION);
}

ConversationScreen* ConversationObserverImplementation::getNextConversationScreen(CreatureObject* conversingPlayer, int selectedOption) {
	//Get screen ID from last conversation screen.
	ConversationSession* session = cast<ConversationSession* >(conversingPlayer->getActiveSession(SessionFacadeType::CONVERSATION));
	String lastScreenId = "";
	if (session != NULL) {
		lastScreenId = session->getLastConversationScreenName();
	}

	//Get last conversation screen.
	Reference<ConversationScreen* > lastConversationScreen = conversationTemplate->getScreen(lastScreenId);
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
			session->setLastConversationScreenName("");
		}
	}
}
