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

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/packets/chat/ChatRoomList.h"
#include "server/zone/packets/chat/ChatOnDestroyRoom.h"
#include "server/zone/packets/chat/ChatOnLeaveRoom.h"
#include "server/zone/packets/chat/ChatOnEnteredRoom.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

void ChatRoomImplementation::sendTo(CreatureObject* player) {
	ChatRoomList* crl = new ChatRoomList();
	crl->addChannel(_this.get());

	crl->insertChannelListCount();
	player->sendMessage(crl);
}

void ChatRoomImplementation::sendDestroyTo(CreatureObject* player) {
	ChatOnDestroyRoom* msg = new ChatOnDestroyRoom("SWG", server->getGalaxyName(), roomID);
	player->sendMessage(msg);
}

void ChatRoomImplementation::addPlayer(CreatureObject* player, bool doLock) {
	Locker locker(_this.get());

	if (playerList.put(player->getFirstName(), player) == -1) {
		//return;
	}

	ChatOnEnteredRoom* coer = new ChatOnEnteredRoom(server->getGalaxyName(), player->getFirstName(), roomID);
	player->sendMessage(coer);

	locker.release();

	Locker locker2(player);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->addChatRoom(_this.get());


	/*ChatOnReceiveRoomInvitation* corri = new ChatOnReceiveRoomInvitation(name);
	player->sendMessage(corri);*/


}

void ChatRoomImplementation::removePlayer(CreatureObject* player, bool doLock) {
	Locker locker(player);

	PlayerObject* ghost = player->getPlayerObject();

	ghost->removeChatRoom(_this.get());

	locker.release();

	Locker locker2(_this.get());

	playerList.drop(player->getFirstName());

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.get(), player);
	player->sendMessage(msg);
}

void ChatRoomImplementation::removePlayer(const String& player) {
	// Pre: player unlocked
	Locker locker(_this.get());

	CreatureObject* play = playerList.get(player);
	playerList.drop(player);

	locker.release();

	if (play == NULL)
		return;

	Locker locker2(play);

	PlayerObject* ghost = play->getPlayerObject();

	ghost->removeChatRoom(_this.get());

	ChatOnLeaveRoom* msg = new ChatOnLeaveRoom(_this.get(), play);
	play->sendMessage(msg);
}

void ChatRoomImplementation::broadcastMessage(BaseMessage* msg) {
	for (int i = 0; i < playerList.size(); ++i) {
		CreatureObject* player = playerList.get(i);
		player->sendMessage(msg->clone());
	}

	delete msg;
}

void ChatRoomImplementation::removeAllPlayers() {
	Locker locker(_this.get());

	for (int i = 0; i < playerList.size(); i++) {
		CreatureObject* player = playerList.get(i);

		Locker clocker(player, _this.get());

		PlayerObject* ghost = player->getPlayerObject();

		ghost->removeChatRoom(_this.get());
	}

	playerList.removeAll();
}


String ChatRoomImplementation::getGalaxyName() {
	return server->getGalaxyName();
}
