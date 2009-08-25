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

#include "ZoneClientSession.h"

#include "ZoneServer.h"

#include "Zone.h"

#include "objects/player/PlayerCreature.h"

ZoneClientSessionImplementation::ZoneClientSessionImplementation(DatagramServiceThread* serv, Socket* sock, SocketAddress* addr)
		:  ManagedObjectImplementation(), BaseClientProxy(sock, *addr) {
	init(serv);

	player = NULL;
	sessionKey = 0;
	accountID = 0;

	disconnecting = false;

	StringBuffer loggingname;
	loggingname << "ZoneClientSession " << addr->getFullIPAddress();

	setLoggingName(loggingname.toString());
	setLogging(false);
}

void ZoneClientSessionImplementation::disconnect() {
	BaseClient::disconnect();
}

void ZoneClientSessionImplementation::lock(bool doLock) {
	BaseClient::lock(doLock);
}

void ZoneClientSessionImplementation::unlock(bool doLock) {
	BaseClient::unlock(doLock);
}

void ZoneClientSessionImplementation::sendMessage(BasePacket* msg) {
	BaseClientProxy::sendPacket(msg);
}

void ZoneClientSessionImplementation::disconnect(bool doLock) {
	lock(doLock);

	if (disconnecting) {
		unlock(doLock);
		return;
	}

	disconnecting = true;

	if (hasError || !clientDisconnected) {
		if (player != NULL) {
			unlock(true);

			((PlayerCreature*)player.get())->disconnect(false, true);

			lock(true);
		}

		closeConnection(true, false);
	} else if (player != NULL) {
		unlock(true);

		if (((PlayerCreature*)player.get())->isLoggingOut())
			((PlayerCreature*)player.get())->logout(true);
		else {
			try {
				//player->wlock();

				((PlayerCreature*)player.get())->setLinkDead();

				//player->unlock();
			} catch (...) {
				//player->unlock();
			}

			closeConnection(true, true);
		}

		lock(true);
	}

	unlock(doLock);
}

void ZoneClientSessionImplementation::closeConnection(bool lockPlayer, bool doLock) {
	try {
		lock(doLock);

		info("disconnecting client \'" + ip + "\'");

		ZoneServer* server = NULL;

		if (player != NULL) {
			ZoneServer* srv = NULL;

			ManagedReference<PlayerCreature*> play = (PlayerCreature*)player.get();

			if (lockPlayer)
				unlock(true);

			try {
				play->wlock(lockPlayer);

				if (play->getZone() != NULL)
					srv = play->getZone()->getZoneServer();

				play->setClient(NULL);

				play->unlock(lockPlayer);
			} catch (...) {
				play->unlock(lockPlayer);
			}

			if (lockPlayer)
				lock(true);

			server = srv;

			setPlayer(NULL); // we must call setPlayer to increase/decrease online player counter
		}

		BaseClient::disconnect(false);

		if (server != NULL) {
			server->addTotalSentPacket(getSentPacketCount());
			server->addTotalResentPacket(getResentPacketCount());
		}

		unlock(doLock);
	} catch (...) {
		unlock(doLock);
	}
}

