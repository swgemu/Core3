/*
 * ClientCreateCharacterCallback.h
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#ifndef CLIENTCREATECHARACTERCALLBACK_H_
#define CLIENTCREATECHARACTERCALLBACK_H_

#include "server/zone/packets/MessageCallback.h"

class ClientCreateCharacterCallback : public MessageCallback {
	String customization;

	UnicodeString characterName;

	String racefile;
	String location;
	String hairobj;
	String haircust;
	String profession;

	int species;

	float height;
	UnicodeString bio;
	uint8 tutflag;

public:
	ClientCreateCharacterCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), species(0), height(0), tutflag(0) {

		setCustomTaskQueue("slowQueue");
	}

	void parse(Message* message);

	void run();

	inline void getRaceFile(String& file) const {
		file = racefile;
	}

	inline void getCustomizationString(String& customizationString) const {
		customizationString = customization;
	}

	inline void getLocation(String& location) const {
		location = ClientCreateCharacterCallback::location;
	}

	inline void getHairObject(String& hair) const {
		hair = hairobj;
	}

	inline void getHairCustomization(String& hairCustomization) const {
		hairCustomization = haircust;
	}

	inline void getSkill(String& profession) const {
		profession = this->profession;
	}

	inline float getHeight() const {
		return height;
	}

	inline void getBiography(UnicodeString& biography) const {
		biography = bio;
	}

	inline bool getTutorialFlag() const {
		if (tutflag)
			return true;
		else
			return false;
	}

	inline void getCharacterName(UnicodeString& name) const {
		name = characterName;
	}

	inline int getSpecies() const {
		return species;
	}
};

#endif /* CLIENTCREATECHARACTERCALLBACK_H_ */
