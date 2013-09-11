/*
 * AdBarkingPhraseSuiCallback.h
 *
 *  Created on: July 5, 2012
 *      Author: Kyle
 */

#ifndef ADBARKINGPHRASESUICALLBACK_H_
#define ADBARKINGPHRASESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/vendor/VendorAdBarkingSession.h"

class AdBarkingPhraseSuiCallback : public SuiCallback {


public:
	AdBarkingPhraseSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		ManagedReference<VendorAdBarkingSession*> session = creature->getActiveSession(SessionFacadeType::VENDORADBARKING).castTo<VendorAdBarkingSession*>();
		if(session == NULL)
			return;

		if(sui->getWindowType() == SuiWindowType::VENDOR_PHRASES)
			handleSelectPhrase(session.get(), creature, sui, cancelPressed, args);

		if(sui->getWindowType() == SuiWindowType::VENDOR_MOODS)
			handleSelectMood(session, creature, sui, cancelPressed, args);

		if(sui->getWindowType() == SuiWindowType::VENDOR_CUSTOM_PHRASE)
			handleCustomMessage(session, creature, sui, cancelPressed, args);

		if(sui->getWindowType() == SuiWindowType::VENDOR_ANIMATION)
			handleSelectAnimation(session, creature, sui, cancelPressed, args);
	}

	void handleSelectPhrase(VendorAdBarkingSession* session, CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		SuiListBox* listBox = cast<SuiListBox*>(sui);
		int index = Integer::valueOf(args->get(0).toString());

		if(cancelPressed || listBox == NULL || (index < 0 || index > 14)) {
			session->cancelSession();
			return;
		}

		int id = listBox->getMenuObjectID(index);

		if(id == 0) {
			session->sendCustomMessageInput();
			return;
		}

		String type = listBox->getMenuItemName(index).replaceFirst("@map_loc_cat_n:vendor_", "");
		session->setMessage("@player_structure:areabark_" + type);
	}

	void handleCustomMessage(VendorAdBarkingSession* session, CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		SuiInputBox* inputBox = cast<SuiInputBox*>(sui);

		if(cancelPressed || inputBox == NULL) {
			session->sendPhraseOptions();
			return;
		}

		String message = args->get(0).toString();

		if(NameManager::instance()->isProfane(message)) {
			session->sendPhraseOptions();
			creature->sendSystemMessage("Phrase rejected by filter, please try again");
			return;
		}

		session->setMessage(message);
	}

	void handleSelectMood(VendorAdBarkingSession* session, CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		SuiListBox* listBox = cast<SuiListBox*>(sui);

		int index = Integer::valueOf(args->get(0).toString());

		if(cancelPressed || listBox == NULL || (index < 0 || index > 16)) {
			session->sendPhraseOptions();
			return;
		}

		String mood = listBox->getMenuItemName(index).replaceFirst("@player_structure:", "");
		session->setMood(mood);
	}

	void handleSelectAnimation(VendorAdBarkingSession* session, CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		SuiListBox* listBox = cast<SuiListBox*>(sui);

		int index = Integer::valueOf(args->get(0).toString());

		if(cancelPressed || listBox == NULL || (index < 0 || index > 16)) {
			session->sendPhraseOptions();
			return;
		}

		String animation = listBox->getMenuItemName(index).replaceFirst("@player_structure:", "");
		session->setAnimation(animation);
	}
};

#endif /* ADBARKINGPHRASESUICALLBACK_H_ */
