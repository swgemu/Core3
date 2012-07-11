/*
 * ClientCreateCharacterCallback.h
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#ifndef CLIENTCREATECHARACTERCALLBACK_H_
#define CLIENTCREATECHARACTERCALLBACK_H_

#include "../MessageCallback.h"

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
		MessageCallback(client, server) {

		taskqueue = 8;

	}

	void parse(Message* message);

	void run();

	inline void getRaceFile(String& file) {
		file = racefile;
	}

	inline void getCustomizationString(String& customizationString) {
		customizationString = customization;
	}

	inline void getLocation(String& location) {
		location = ClientCreateCharacterCallback::location;
	}

	inline void getHairObject(String& hair) {
		hair = hairobj;
	}

	inline void getHairCustomization(String& hairCustomization) {
		hairCustomization = haircust;
	}

	inline void getSkill(String& profession) {
		profession = this->profession;
	}

	inline float getHeight() {
		return height;
	}

	inline void getBiography(UnicodeString& biography) {
		biography = bio;
	}

	inline bool getTutorialFlag() {
		if (tutflag)
			return true;
		else
			return false;
	}

	inline void getCharacterName(UnicodeString& name) {
		name = characterName;
	}

	inline int getSpecies() {
		return species;
	}
};


#endif /* CLIENTCREATECHARACTERCALLBACK_H_ */
