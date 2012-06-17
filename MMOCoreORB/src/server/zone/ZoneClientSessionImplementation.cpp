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

#include "objects/creature/CreatureObject.h"

#include "server/zone/objects/player/events/ClearClientEvent.h"
#include "server/zone/objects/player/events/DisconnectClientEvent.h"
#include "server/zone/managers/player/PlayerManager.h"

ZoneClientSessionImplementation::ZoneClientSessionImplementation(BaseClientProxy* session)
		:  ManagedObjectImplementation() {
	ZoneClientSessionImplementation::session = session;

	player = NULL;
	sessionID = 0;

	accountID = 0;

	disconnecting = false;

	commandCount = 0;

	characters.setNullValue(0);
	characters.setAllowDuplicateInsertPlan();

	bannedCharacters.setNullValue(0);
	bannedCharacters.setAllowDuplicateInsertPlan();

	//session->setDebugLogLevel();
}

void ZoneClientSessionImplementation::disconnect() {
	session->disconnect();
}

void ZoneClientSessionImplementation::sendMessage(BasePacket* msg) {
	session->sendPacket(msg);
}


//this needs to be run in a different thread
void ZoneClientSessionImplementation::disconnect(bool doLock) {
	Locker locker(_this.get());

	if (disconnecting) {
		return;
	}

	disconnecting = true;

	ManagedReference<SceneObject*> player = this->player.get();

	if (session->hasError() || !session->isClientDisconnected()) {
		if (player != NULL) {

			if (player->getClient() == _this.get().get()) {
				//((CreatureObject*)player.get())->disconnect(false, true);
				Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(cast<CreatureObject*>(player.get()), _this.get(), DisconnectClientEvent::DISCONNECT);
				Core::getTaskManager()->executeTask(task);
			}
		}

		closeConnection(true, false);
	} else if (player != NULL) {
		PlayerObject* ghost = cast<PlayerObject*>( player->getSlottedObject("ghost"));

		if (ghost->isLoggingOut() && player->getClient() == _this.get().get()) {
			//((CreatureObject*)player.get())->logout(true);
			Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(cast<CreatureObject*>(player.get()), _this.get(), DisconnectClientEvent::LOGOUT);
			Core::getTaskManager()->executeTask(task);
		}
		else {
			try {
				//player->wlock();

				if (player->getClient() == _this.get()) {
					//((CreatureObject*)player.get())->setLinkDead();
					Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(cast<CreatureObject*>(player.get()), _this.get(), DisconnectClientEvent::SETLINKDEAD);
					Core::getTaskManager()->executeTask(task);
				}

				//player->unlock();
			} catch (Exception& e) {
				//player->unlock();
			}

			closeConnection(true, true);
		}
	}
	

	/*info("references left " + String::valueOf(_this.get()->getReferenceCount()), true);
	_this.get()->printReferenceHolders();*/
}

void ZoneClientSessionImplementation::setPlayer(SceneObject* playerCreature) {
	ManagedReference<SceneObject*> player = this->player.get();

	if (playerCreature != player) {
		if (playerCreature == NULL && player != NULL) {
			// TODO: find a proper way to acqure zone server
			ZoneServer* zoneServer = player->getZoneServer();

			if (zoneServer != NULL) {
				zoneServer->decreaseOnlinePlayers();

				zoneServer->getPlayerManager()->decreaseOnlineCharCount(_this.get());

			}
		} else if (playerCreature != player) {
			// TODO: find a proper way to acqure zone server
			ZoneServer* zoneServer = playerCreature->getZoneServer();

			if (zoneServer != NULL) {
				zoneServer->increaseOnlinePlayers();
			}
		}
	}

	this->player = playerCreature;
}


void ZoneClientSessionImplementation::closeConnection(bool lockPlayer, bool doLock) {
	Locker locker(_this.get());

	session->info("disconnecting client \'" + session->getIPAddress() + "\'");

	ZoneServer* server = NULL;
	ManagedReference<CreatureObject*> play = cast<CreatureObject*>(player.get().get());

	if (play != NULL) {
		server = play->getZoneServer();

		Reference<ClearClientEvent*> task = new ClearClientEvent(play, _this.get());
		Core::getTaskManager()->executeTask(task);

		setPlayer(NULL); // we must call setPlayer to increase/decrease online player counter
	}

	session->disconnect();

	if (server != NULL) {
		server->addTotalSentPacket(session->getSentPacketCount());
		server->addTotalResentPacket(session->getResentPacketCount());
	}
}

void ZoneClientSessionImplementation::balancePacketCheckupTime() {
	session->balancePacketCheckupTime();
}

void ZoneClientSessionImplementation::resetPacketCheckupTime() {
	session->resetPacketCheckupTime();
}

void ZoneClientSessionImplementation::info(const String& msg, bool force) {
	session->info(msg, force);
}

void ZoneClientSessionImplementation::error(const String& msg) {
	session->error(msg);
}

String ZoneClientSessionImplementation::getAddress() {
	return session->getAddress();
}

BaseClientProxy* ZoneClientSessionImplementation::getSession() {
	return session;
}

int ZoneClientSessionImplementation::getCharacterCount(int galaxyId) {
	int count = 0;

	for (int i = 0; i < characters.size(); ++i) {
		if (characters.elementAt(i).getKey() == galaxyId)
			++count;
	}

	for (int i = 0; i < bannedCharacters.size(); ++i) {
		if (bannedCharacters.elementAt(i).getKey() == galaxyId)
			++count;
	}

	return count;
}

bool ZoneClientSessionImplementation::hasCharacter(uint64 cid, unsigned int galaxyId) {
/*	int lowerBound = characters.lowerBound(VectorMapEntry<uint32, uint64>(galaxyId));

	if (lowerBound < 0)
		return false;

	for (int i = lowerBound; i < characters.size(); ++i) {
		if (characters.elementAt(i).getKey() != galaxyId)
			break;

		if (characters.elementAt(i).getValue() == cid)
			return true;
	}
	
	*/
	
	for (int i = 0; i < characters.size(); ++i) {
		if (characters.elementAt(i).getKey() == galaxyId && 
			characters.elementAt(i).getValue() == cid)
			return true;
	}
	

	return false;
}
