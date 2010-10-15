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
		class LoginMessageProcessorThread;

		class LoginProcessServerImplementation : public ServiceMessageHandlerThread {
			ManagedWeakReference<LoginServer*> server;

			LoginPacketHandler* loginphandler;

			LoginMessageProcessorThread** processors;
			int procThreadCount;

		public:
			static LoginProcessServerImplementation* instance;

		public:
			LoginProcessServerImplementation(LoginServer* serv, int processingThreads);

			~LoginProcessServerImplementation();

			void init();

			void run();

			void stop();

			ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
				return NULL;
			}

			inline LoginServer* getLoginServer() {
				return server;
			}
		};
	}
}

using namespace server::login;

#endif /* LOGINPROCESSSERVERIMPLEMENTATION_H_ */
