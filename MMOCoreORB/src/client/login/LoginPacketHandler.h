/*
 * LoginPacketHandler.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef LOGINPACKETHANDLER_H_
#define LOGINPACKETHANDLER_H_

#include "engine/engine.h"
#include "LoginSession.h"

class LoginPacketHandler : public Logger {
	Reference<LoginSession*> loginSession;

public:
	LoginPacketHandler(LoginSession* session) : Logger("LoginPacketHandler") {
		loginSession = session;

		setLogging(true);
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
