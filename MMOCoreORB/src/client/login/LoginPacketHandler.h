/*
 * LoginPacketHandler.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef LOGINPACKETHANDLER_H_
#define LOGINPACKETHANDLER_H_

#include "engine/engine.h"


class LoginPacketHandler : public Logger {

public:
	LoginPacketHandler() : Logger("LoginPacketHandler") {

	}

	LoginPacketHandler(const String& s) : Logger(s) {

	}

	~LoginPacketHandler() {
	}

	void handleMessage(Message* pack);
	void handleEnumerateCharacterId(Message* pack);
	void handleLoginClientToken(Message* pack);
	void handleErrorMessage(Message* pack);

	/*void handleSceneObjectCreateMessage(Message* pack);

	void handleCharacterCreateSucessMessage(Message* pack);

	void handleUpdateTransformMessage(Message* pack);*/
};



#endif /* LOGINPACKETHANDLER_H_ */
