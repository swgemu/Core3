/*
 * LoginProcessServerImplementation.h
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#ifndef LOGINPROCESSSERVERIMPLEMENTATION_H_
#define LOGINPROCESSSERVERIMPLEMENTATION_H_

#include "engine/engine.h"

namespace server {
	namespace login {

		class LoginPacketHandler;
		class LoginServer;

		class LoginProcessServerImplementation {
			ManagedWeakReference<LoginServer*> server;

			LoginPacketHandler* loginPacketHandler;

		public:
			LoginProcessServerImplementation(LoginServer* serv);

			~LoginProcessServerImplementation();

			void initialize();

			inline LoginServer* getLoginServer() {
				return server;
			}

			inline LoginPacketHandler* getPacketHandler() {
				return loginPacketHandler;
			}
		};

	} // namspace login
} // namespace server

using namespace server::login;

#endif /* LOGINPROCESSSERVERIMPLEMENTATION_H_ */
