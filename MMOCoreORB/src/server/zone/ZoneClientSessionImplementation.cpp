/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/ZoneClientSession.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/Zone.h"

#include "server/zone/objects/creature/CreatureObject.h"

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
		Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

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
	Reference<BaseClientProxy* > session = this->session;

	if (session == NULL)
		return;

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
