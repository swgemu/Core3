/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONEHANDLER_H_
#define ZONEHANDLER_H_

#include "server/zone/ZoneServer.h"

#include "server/zone/ZoneClientSession.h"

namespace server {
  namespace zone {

	class ZoneSessionMap : public HashTable<uint64, Reference<ZoneClientSession*> >,
			public HashTableIterator<uint64, Reference<ZoneClientSession*> > {

		int maxConnections;

	public:
		ZoneSessionMap(int maxconn = 10000) : HashTable<uint64, Reference<ZoneClientSession*> >((int) (maxconn * 1.25f)),
				HashTableIterator<uint64, Reference<ZoneClientSession*> >(this) {
			maxConnections = maxconn;
		}

		bool add(ZoneClientSession* client) {
			if (HashTable<uint64, Reference<ZoneClientSession*> >::put(client->getSession()->getNetworkID(), client) == NULL) {
				return true;
			} else
				return false;
		}

		bool remove(ZoneClientSession* client) {
			if (HashTable<uint64, Reference<ZoneClientSession*> >::remove(client->getSession()->getNetworkID()) != NULL) {
				return true;
			} else
				return false;
		}

	};

	class ZoneHandler: public ServiceHandler {
		ManagedReference<ZoneServer*> zoneServerRef;

		ZoneSessionMap clients;

		ReadWriteLock guard;

	public:
		ZoneHandler(ZoneServer* server) {
			zoneServerRef = server;
		}

		void initialize() {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			server->initialize();
		}

		ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			Reference<ZoneClientSession*> client = server->createConnection(sock, addr);

			Locker locker(&guard);

			clients.add(client);

			return client->getSession();
		}

		bool deleteConnection(ServiceClient* session) {
			Reference<ZoneClientSession*> client = getClientSession(session);

			client->disconnect();
			client->disconnect(true);

			Locker locker(&guard);

			clients.remove(client);

			return false;
		}

		void handleMessage(ServiceClient* session, Packet* message) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			ManagedReference<ZoneClientSession*> client = getClientSession(session);

			if (client != NULL)
				server->handleMessage(client, message);
		}

		void processMessage(Message* message) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			return server->processMessage(message);
		}

		bool handleError(ServiceClient* session, Exception& e) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			Reference<ZoneClientSession*> client = getClientSession(session);

			return server->handleError(client, e);
		}

		Reference<ZoneClientSession*> getClientSession(ServiceClient* session) {
			ReadLocker locker(&guard);
			return clients.get(session->getNetworkID());
		}
	};

  } // namespace zone
} // namespace server

using namespace server::zone;

#endif /* ZONEHANDLER_H_ */
