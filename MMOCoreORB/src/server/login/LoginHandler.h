/*
 * LoginHandler.h
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#ifndef LOGINHANDLER_H_
#define LOGINHANDLER_H_

#include "server/login/LoginClient.h"
#include "server/login/LoginServer.h"

namespace server {
  namespace login {

	class LoginSessionMap : private HashTable<uint64, Reference<LoginClient*> > {
		int maxConnections;

	public:
		LoginSessionMap(int maxconn = 10000) : HashTable<uint64, Reference<LoginClient*> >((int) (maxconn * 1.25f)) {
			maxConnections = maxconn;
		}

		bool add(LoginClient* client) {
			if (HashTable<uint64, Reference<LoginClient*> >::put(client->getSession()->getNetworkID(), client) == nullptr) {
				return true;
			} else
				return false;
		}

		bool remove(LoginClient* client) {
			if (HashTable<uint64, Reference<LoginClient*> >::remove(client->getSession()->getNetworkID()) != nullptr) {
				return true;
			} else
				return false;
		}

		LoginClient* get(uint64 id) {
			return HashTable<uint64, Reference<LoginClient*> >::get(id);
		}

	};

	class LoginHandler: public ServiceHandler {
		Reference<LoginServer*> server;

		LoginSessionMap clients;

	public:
		LoginHandler() {
		}

		void initialize() {
			server->initialize();
		}

		ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
			LoginClient* client =  server->createConnection(sock, addr);

			clients.add(client);

			return client->getSession();
		}

		bool deleteConnection(ServiceClient* session) {
			Reference<LoginClient*> client = getClient(session);

			if (client != nullptr) {
				client->disconnect();

				clients.remove(client);
			}

			return false;
		}

		void handleMessage(ServiceClient* session, Packet* message) {
			Reference<LoginClient*> client = getClient(session);

			server->handleMessage(client, message);
		}

		void processMessage(Message* message) {
			return server->processMessage(message);
		}

		bool handleError(ServiceClient* client, Exception& e) {
			return server->handleError(client, e);
		}

		void setLoginSerrver(LoginServer* server) {
			this->server = server;
		}

		LoginClient* getClient(ServiceClient* session) {
			return clients.get(session->getNetworkID());
		}
	};

  } // namespace login
} // namespace server

using namespace server::login;

#endif /* LOGINHANDLER_H_ */
