/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "PingClient.h"
#include "PingServer.h"

PingServer::PingServer() : DatagramServiceThread("PingServer") {
	//setLockName("PingServerLock");

	setHandler(this);

	setLogging(false);
}

PingServer::~PingServer() {
}

void PingServer::initialize() {
}

void PingServer::run() {
	// recieve messages
	receiveMessages();

	shutdown();
}

void PingServer::shutdown() {
	// shutting down
}

PingClient* PingServer::createConnection(Socket* sock, SocketAddress& addr) {
	PingClient* client = new PingClient(this, sock, addr);

	info("client connected from \'" + client->getAddress() + "\'");

	return client;
}

void PingServer::handleMessage(ServiceClient* client, Packet* message) {
	PingClient* lclient = cast<PingClient*>(client);

	try {

		if (lclient->isAvailable() && (message->size() == 4)) {
			lclient->updateNetStatus();

			Packet* mess = message->clone();

			lclient->send(mess);
		}

	} catch (PacketIndexOutOfBoundsException& e) {
		System::out << e.getMessage();

		error("incorrect packet - " + message->toStringData());
	} catch (Exception& e) {
		error(e.getMessage());
	}
}

bool PingServer::handleError(ServiceClient* client, Exception& e) {
	PingClient* lclient = cast<PingClient*>(client);

	if (lclient != NULL) {
		lclient->setError();

		lclient->disconnect();
	}

	return true;
}

void PingServer::processMessage(Message* message) {

}

void PingServer::printInfo() {
	lock();

	StringBuffer msg;
	msg << "MessageQueue - size = " << messageQueue.size();
	info(msg, true);

	unlock();
}
