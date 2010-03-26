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

#include "ChatRoom.h"

#include "../../zone/objects/player/PlayerCreature.h"
#include "../../zone/objects/creature/CreatureObject.h"

#include "../../zone/ZoneServer.h"

#include "../../zone/packets/chat/ChatRoomList.h"
#include "../../zone/packets/chat/ChatOnDestroyRoom.h"
#include "../../zone/packets/chat/ChatOnLeaveRoom.h"
#include "../../zone/packets/chat/ChatOnEnteredRoom.h"

void ChatRoomImplementation::sendTo(PlayerCreature* player) {
	ChatRoomList* crl = new ChatRoomList();
	crl->addChannel((ChatRoom*) _this);

	crl->insertChannelListCount();
	player->sendMessage(crl);
}

void ChatRoomImplementation::sendDestroyTo(PlayerCreature* player) {
	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getServerName(), roomID);
	player->sendMessage(msg);
}

void ChatRoomImplementation::addPlayer(PlayerCreature* player, bool doLock) {
	wlock();

	if (playerList.put(player->getFirstName(), player) == -1) {
		unlock();
		return;
	}

	ChatOnEnteredRoom* coer = new ChatOnEnteredRoom(server->getServerName(), player->getFirstName(), roomID);
	player->sendMessage(coer);

	unlock();

	player->wlock(doLock);

	player->addChatRoom((ChatRoom*) _this);

	player->unlock(doLock);

	/*ChatOnReceiveRoomInvitation* corri = new ChatOnReceiveRoomInvitation(name);
	player->sendMessage(corri);*/


}

void ChatRoomImplementation::removePlayer(PlayerCreature* player, bool doLock) {
	player->wlock(doLock);

	player->removeChatRoom((ChatRoom*) _this);

	player->unlock(doLock);

	wlock();

	playerList.drop(player->getFirstName());

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom((ChatRoom*) _this, player);
	player->sendMessage(msg);

	unlock();
}

void ChatRoomImplementation::removePlayer(const String& player) {
	// Pre: player unlocked
	wlock();

	PlayerCreature* play = playerList.get(player);
	playerList.drop(player);

	unlock();

	if (play == NULL)
		return;

	try {
		play->wlock();

		play->removeChatRoom((ChatRoom*) _this);

		ChatOnLeaveRoom* msg = new ChatOnLeaveRoom((ChatRoom*) _this, play);
		play->sendMessage(msg);

		play->unlock();
	} catch (...) {
		System::out << "unreported Exception in ChatRoom::removePlayer(const String& player)\n";
		play->unlock();
	}
}

void ChatRoomImplementation::broadcastMessage(BaseMessage* msg) {
	for (int i = 0; i < playerList.size(); ++i) {
		PlayerCreature* player = playerList.get(i);
		player->sendMessage(msg->clone());
	}

	delete msg;
}

void ChatRoomImplementation::removeAllPlayers() {
	wlock();

	for (int i = 0; i < playerList.size(); i++) {
		PlayerCreature* player = playerList.get(i);

		try {
			player->wlock(_this);

			player->removeChatRoom((ChatRoom*) _this);

			player->unlock();
		} catch (...) {
			System::out << "unreported Exception in ChatRoom::removeAllPlayers(Player* lockedPlayer)\n";
			player->unlock();
		}

	}

	playerList.removeAll();
	unlock();
}


String ChatRoomImplementation::getServerName() {
	return server->getServerName();
}
