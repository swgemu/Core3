/*
 * LoginHandler.h
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#ifndef LOGINHANDLER_H_
#define LOGINHANDLER_H_

#include "LoginClient.h"
#include "LoginServer.h"

namespace server {
  namespace login {

	class LoginSessionMap : public HashTable<uint64, LoginClient*>,
			public HashTableIterator<uint64, LoginClient*> {

		int maxConnections;
	public:
		LoginSessionMap(int maxconn = 10000) : HashTable<uint64, LoginClient*>((int) (maxconn * 1.25f)),
				HashTableIterator<uint64, LoginClient*>(this) {
			maxConnections = maxconn;
		}

		bool add(LoginClient* client) {
			if (HashTable<uint64, LoginClient*>::put(client->getSession()->getNetworkID(), client) == NULL) {
				client->acquire();

				return true;
			} else
				return false;
		}

		bool remove(LoginClient* client) {
			if (HashTable<uint64, LoginClient*>::remove(client->getSession()->getNetworkID()) != NULL) {
				client->release();

				return true;
			} else
				return false;
		}

	};

	class LoginHandler: public ServiceHandler {
		ManagedReference<LoginServer*> loginServerRef;

		LoginSessionMap clients;

	public:
		LoginHandler() {
		}

		void initialize() {
			LoginServer* server =  loginServerRef.getForUpdate();

			server->initialize();
		}

		ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
			LoginServer* server =  loginServerRef.getForUpdate();

			LoginClient* client =  server->createConnection(sock, addr);

			clients.add(client);

			return client->getSession();
		}

		bool deleteConnection(ServiceClient* session) {
			Reference<LoginClient*> client = getClient(session);

			client->disconnect();

			clients.remove(client);

			return false;
		}

		void handleMessage(ServiceClient* session, Packet* message) {
			LoginServer* server =  loginServerRef.getForUpdate();

			Reference<LoginClient*> client = getClient(session);

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

		LoginClient* getClient(ServiceClient* session) {
			return clients.get(session->getNetworkID());
		}
	};

  } // namespace login
} // namespace server

using namespace server::login;

#endif /* LOGINHANDLER_H_ */
