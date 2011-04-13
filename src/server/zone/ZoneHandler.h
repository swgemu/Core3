/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef ZONEHANDLER_H_
#define ZONEHANDLER_H_

#include "ZoneServer.h"

#include "ZoneClientSession.h"

namespace server {
  namespace zone {

	class ZoneSessionMap : public HashTable<uint64, ZoneClientSession*>,
			public HashTableIterator<uint64, ZoneClientSession*> {

		int maxConnections;

	public:
		ZoneSessionMap(int maxconn = 10000) : HashTable<uint64, ZoneClientSession*>((int) (maxconn * 1.25f)),
				HashTableIterator<uint64, ZoneClientSession*>(this) {
			maxConnections = maxconn;
		}

		bool add(ZoneClientSession* client) {
			if (HashTable<uint64, ZoneClientSession*>::put(client->getSession()->getNetworkID(), client) == NULL) {
				client->acquire();

				return true;
			} else
				return false;
		}

		bool remove(ZoneClientSession* client) {
			if (HashTable<uint64, ZoneClientSession*>::remove(client->getSession()->getNetworkID()) != NULL) {
				client->release();

				return true;
			} else
				return false;
		}

	};

	class ZoneHandler: public ServiceHandler {
		ManagedReference<ZoneServer*> zoneServerRef;

		ZoneSessionMap clients;

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

			ZoneClientSession* client = server->createConnection(sock, addr);

			clients.add(client);

			return client->getSession();
		}

		bool deleteConnection(ServiceClient* session) {
			ZoneClientSession* client = getClientSession(session);

			client->disconnect();

			client->disconnect(true);

			clients.remove(client);

			return false;
		}

		void handleMessage(ServiceClient* session, Packet* message) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			ManagedReference<ZoneClientSession*> client = getClientSession(session);

			return server->handleMessage(client, message);
		}

		void processMessage(Message* message) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			return server->processMessage(message);
		}

		bool handleError(ServiceClient* session, Exception& e) {
			ZoneServer* server =  zoneServerRef.getForUpdate();

			ZoneClientSession* client = getClientSession(session);

			return server->handleError(client, e);
		}

		ZoneClientSession* getClientSession(ServiceClient* session) {
				return clients.get(session->getNetworkID());
			}
	};

  } // namespace zone
} // namespace server

using namespace server::zone;

#endif /* ZONEHANDLER_H_ */
