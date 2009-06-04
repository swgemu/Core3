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
#include <iostream>
#include <fstream>

//#include "engine/service/proto/BaseMessage.h"
//#include "engine/service/proto/StandaloneBaseMessage.h"

//#include "../zone/packets/chat/ChatInstantMessageToCharacter.h"
//#include "../zone/packets/chat/ChatInstantMessageToClient.h"
//#include "../zone/packets/chat/ChatOnSendInstantMessage.h"
//#include "../zone/packets/chat/ChatOnCreateRoom.h"
//#include "../zone/packets/chat/ChatOnDestroyRoom.h"
//#include "../zone/packets/chat/ChatOnSendRoomMessage.h"
//#include "../zone/packets/chat/ChatPersistentMessageToClient.h"
//#include "../zone/packets/chat/ChatRoomMessage.h"
//#include "../zone/packets/chat/ChatSystemMessage.h"
//#include "../zone/packets/creature/CreatureObjectDeltaMessage6.h"
//#include "../zone/packets/object/Emote.h"
//#include "../zone/packets/object/SpatialChat.h"

//#include "../zone/Zone.h"
//#include "../zone/ZoneClientSession.h"
//#include "../zone/ZoneServer.h"

//#include "../zone/managers/creature/CreatureManager.h"
//#include "../zone/managers/player/ProfessionManager.h"

//#include "../zone/managers/player/PlayerManager.h"
//#include "../zone/managers/user/UserManager.h"

//#include "../zone/managers/item/ItemManager.h"

//#include "../zone/managers/guild/GuildManager.h"

//#include "ChatManager.h"
#include "ChatManagerImplementation.h"

//#include "room/ChatRoomImplementation.h"

//#include "room/ChatRoom.h"
//#include "room/ChatRoomMap.h"

//#include "../zone/managers/player/PlayerMapImplementation.h"

//#include "../zone/objects/tangible/creature/player/sui/listbox/SuiListBoxImplementation.h"
//#include "../zone/objects/tangible/creature/player/sui/colorpicker/SuiColorPickerImplementation.h"

//#include "../zone/objects/tangible/CustomizationVariables.h"

//#include "../zone/managers/planet/PlanetManager.h"

ChatManagerImplementation::ChatManagerImplementation(ZoneServer* serv) : ChatManagerServant(), Mutex("ChatManager") {
	server = serv;
}

ChatManagerImplementation::~ChatManagerImplementation() {
}
