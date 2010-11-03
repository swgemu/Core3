/*
 * LoginHandler.h
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#ifndef LOGINHANDLER_H_
#define LOGINHANDLER_H_

#include "LoginServer.h"

namespace server {
  namespace login {

	class LoginHandler: public ServiceHandler {
		ManagedReference<LoginServer*> loginServerRef;

	public:
		LoginHandler() {
		}

		void initialize() {
			LoginServer* server =  loginServerRef.getForUpdate();

			server->initialize();
		}

		ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
			LoginServer* server =  loginServerRef.getForUpdate();

			return server->createConnection(sock, addr);
		}

		bool deleteConnection(ServiceClient* client) {
			return false;
		}

		void handleMessage(ServiceClient* client, Packet* message) {
			LoginServer* server =  loginServerRef.getForUpdate();

			return server->handleMessage(client, message);
		}

		void processMessage(Message* message) {
			LoginServer* server =  loginServerRef.getForUpdate();

			return server->processMessage(message);
		}

		bool handleError(ServiceClient* client, Exception& e) {
			LoginServer* server =  loginServerRef.getForUpdate();

			return server->handleError(client, e);
		}

		void setLoginSerrver(LoginServer* server) {
			loginServerRef = server;
		}
	};

  } // namespace login
} // namespace server

using namespace server::login;

#endif /* LOGINHANDLER_H_ */
