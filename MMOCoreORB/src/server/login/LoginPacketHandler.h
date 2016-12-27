/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINPACKETHANDLER_H_
#define LOGINPACKETHANDLER_H_

#include "LoginClient.h"

namespace server {
namespace login {

	class LoginServer;
	class LoginProcessServerImplementation;

	class LoginPacketHandler : public Logger {
		LoginProcessServerImplementation* processServer;
		ManagedReference<LoginServer*> server;

	public:

		LoginPacketHandler() : Logger() {
			server = NULL;
			processServer = NULL;
		}

		LoginPacketHandler(const String& s, LoginProcessServerImplementation* serv);

		~LoginPacketHandler() {
		}

		void handleMessage(Message* pack);

		void handleClientPermissionsMessage(Message* pack);
		void handleSelectCharacter(Message* pack);
		void handleCmdSceneReady(Message* packet);
		void handleLoginClientID(LoginClient* client, Message* packet);
		void handleDeleteCharacterMessage(LoginClient* client, Message* pack);

	};
}
}

using namespace server::login;

#endif /*LOGINPACKETHANDLER_H_*/
