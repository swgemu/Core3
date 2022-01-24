/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/ZoneClientSession.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/objects/player/events/ClearClientEvent.h"
#include "server/zone/objects/player/events/DisconnectClientEvent.h"
#include "server/zone/managers/player/PlayerManager.h"

ZoneClientSessionImplementation::ZoneClientSessionImplementation(BaseClientProxy* session)
		:  ManagedObjectImplementation() {
	ZoneClientSessionImplementation::session = session;

	ipAddress = session != nullptr ? session->getIPAddress() : "";

	player = nullptr;

	pendingTasks = new PendingTasksMap();

	accountID = 0;

	disconnecting = false;

	commandCount = 0;

	characters.setNullValue(0);
	characters.setAllowDuplicateInsertPlan();

	bannedCharacters.setNullValue(0);
	bannedCharacters.setAllowDuplicateInsertPlan();

	setupLogging();

	//session->setDebugLogLevel();
}

void ZoneClientSessionImplementation::setupLogging() {
	auto clientLogLevel = ConfigManager::instance()->getInt("Core3.ZoneServer.ClientLogLevel", -1, accountID);

	if (clientLogLevel < 0) {
		return;
	}

	if (session == nullptr) {
		error() << "setupLogging failed: session == nullptr";
		return;
	}

	// Files should end up in: log/clients/YYYY-MM-DD/HH/{ip}/BaseClientProxy-{timeSecs}-{ip}-{port}.log
	auto addr = session->ServiceClient::getAddress();
	Time now;
	StringBuffer logFilename;
	logFilename << "log/clients/"
		<< now.getFormattedTime("%Y-%m-%d/%H")
		<< "/" << session->getIPAddress()
	    << "/BaseClientProxy-" << now.getTime() << "-" << addr.getIPAddress() << "-" << addr.getPort() << ".log";

	session->setFileLogger(logFilename.toString(), true, ConfigManager::instance()->getRotateLogAtStart());
	session->setLogSynchronized(true);
	session->setLogToConsole(false);
	session->setGlobalLogging(false);
	session->setLogLevel(static_cast<Logger::LogLevel>(clientLogLevel));

	if (accountID == 0) {
		session->reportStats("Client connected");
	} else {
		session->info() << "AccountID=" << accountID << "; ClientLogLevel=" << clientLogLevel;
		session->reportStats("account_id=" + String::valueOf(accountID));
	}

}

void ZoneClientSessionImplementation::setAccountID(unsigned int newAccountID) {
	accountID = newAccountID;

	if (session == nullptr) {
		error() << "setAccountID(" << newAccountID << ") session == nullptr";
		return;
	}

	setupLogging();
}

void ZoneClientSessionImplementation::disconnect() {
	session->reportStats("ZoneClientSessionImplementation::disconnect()");
	session->disconnect();
}

void ZoneClientSessionImplementation::sendMessage(BasePacket* msg) {
	session->sendPacket(msg);
}

//this needs to be run in a different thread
void ZoneClientSessionImplementation::disconnect(bool doLock) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (disconnecting) {
		return;
	}

	disconnecting = true;

	ManagedReference<CreatureObject*> player = this->player.get();
	Reference<ZoneClientSession*> zoneClientSession;
	if (session->hasError() || !session->isClientDisconnected()) {
		if (player != nullptr) {
			zoneClientSession = player->getClient();

			if (zoneClientSession == _this.getReferenceUnsafeStaticCast()) {
				//((CreatureObject*)player.get())->disconnect(false, true);
				Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(player, _this.getReferenceUnsafeStaticCast(), DisconnectClientEvent::DISCONNECT);
				Core::getTaskManager()->executeTask(task);
			}
		}

		closeConnection(true, false);
	} else if (player != nullptr) {
		zoneClientSession = player->getClient();

		Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (ghost->isLoggingOut() && zoneClientSession == _this.getReferenceUnsafeStaticCast()) {
			//((CreatureObject*)player.get())->logout(true);
			Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(player, _this.getReferenceUnsafeStaticCast(), DisconnectClientEvent::LOGOUT);
			Core::getTaskManager()->executeTask(task);
		}
		else {
			try {
				//player->wlock();
				zoneClientSession = player->getClient();

				if (zoneClientSession == _this.getReferenceUnsafeStaticCast()) {
					//((CreatureObject*)player.get())->setLinkDead();
					Reference<DisconnectClientEvent*> task = new DisconnectClientEvent(player, _this.getReferenceUnsafeStaticCast(), DisconnectClientEvent::SETLINKDEAD);
					Core::getTaskManager()->executeTask(task);
				}

				//player->unlock();
			} catch (Exception& e) {
				//player->unlock();
			}

			closeConnection(true, true);
		}
	}


	/*info("references left " + String::valueOf(_this.getReferenceUnsafeStaticCast()->getReferenceCount()), true);
	_this.getReferenceUnsafeStaticCast()->printReferenceHolders();*/
}

void ZoneClientSessionImplementation::setPlayer(CreatureObject* playerCreature) {
	ManagedReference<CreatureObject*> player = this->player.get();

	if (playerCreature != player) {
		if (playerCreature == nullptr && player != nullptr) {
			// TODO: find a proper way to acqure zone server
			ZoneServer* zoneServer = player->getZoneServer();

			if (zoneServer != nullptr) {
				zoneServer->decreaseOnlinePlayers();

				zoneServer->getPlayerManager()->decreaseOnlineCharCount(_this.getReferenceUnsafeStaticCast());

			}
		} else if (playerCreature != nullptr) {
			// TODO: find a proper way to acqure zone server
			ZoneServer* zoneServer = playerCreature->getZoneServer();

			if (zoneServer != nullptr) {
				zoneServer->increaseOnlinePlayers();
			}
		}
	}

	if (session != nullptr) {
		if (playerCreature != nullptr) {
			session->info() << "Player " << playerCreature->getObjectID() << " logged in.";
			session->reportStats("login character_oid=" + String::valueOf(playerCreature->getObjectID()));
		} else if (player != nullptr) {
			session->info() << "Player " << player->getObjectID() << " logged out.";
			session->reportStats("logout character_oid=" + String::valueOf(player->getObjectID()));
		} else {
			session->info() << "Cleared player from session.";
			session->reportStats("Player cleared from session");
		}
	}

	this->player = playerCreature;
}


void ZoneClientSessionImplementation::closeConnection(bool lockPlayer, bool doLock) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	Reference<BaseClientProxy* > session = this->session;

	if (session == nullptr)
		return;

	session->info("disconnecting client \'" + session->getIPAddress() + "\'");

	ZoneServer* server = nullptr;
	ManagedReference<CreatureObject*> play = player.get();

	if (play != nullptr) {
		server = play->getZoneServer();

		Reference<ClearClientEvent*> task = new ClearClientEvent(play, _this.getReferenceUnsafeStaticCast());
		Core::getTaskManager()->executeTask(task);

		setPlayer(nullptr); // we must call setPlayer to increase/decrease online player counter
	}

	session->disconnect();

	if (server != nullptr) {
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

void ZoneClientSessionImplementation::debug(const String& msg) {
	session->debug(msg);
}

void ZoneClientSessionImplementation::error(const String& msg) {
	session->error(msg);
}

String ZoneClientSessionImplementation::getAddress() const {
	return session->getAddress();
}

String ZoneClientSessionImplementation::getIPAddress() const {
	return ipAddress.isEmpty() ? "0.0.0.0" : ipAddress;
}

BaseClientProxy* ZoneClientSessionImplementation::getSession() {
	return session;
}

int ZoneClientSessionImplementation::getCharacterCount(int galaxyId) const {
	int count = 0;

	for (int i = 0; i < characters.size(); ++i) {
		if (characters.getKey(i) == galaxyId)
			++count;
	}

	for (int i = 0; i < bannedCharacters.size(); ++i) {
		if (bannedCharacters.getKey(i) == galaxyId)
			++count;
	}

	return count;
}

bool ZoneClientSessionImplementation::hasCharacter(uint64 cid, unsigned int galaxyId) const {
	for (int i = 0; i < characters.size(); ++i) {
		if (characters.getKey(i) == galaxyId &&
			characters.get(i) == cid)
			return true;
	}

	return false;
}

Reference<CreatureObject*> ZoneClientSessionImplementation::getPlayer() {
	return player.get();
}
