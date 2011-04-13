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
	PingClient* lclient = (PingClient*) client;

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
	PingClient* lclient = (PingClient*) client;
	lclient->setError();

	lclient->disconnect();

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
