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

#ifndef GUILDIMPLEMENTATION_H_
#define GUILDIMPLEMENTATION_H_

#include "../scene/SceneObject.h"
#include "../scene/SceneObjectImplementation.h"

//#include "../../managers/player/PlayerMap.h"

#include "../../../chat/room/ChatRoom.h"

class GuildManager;
class Player;

#include "Guild.h"

class GuildImplementation : public GuildServant {
	GuildManager* guildManager;
	ChatRoom* guildChannel;

	uint32 guildID;

	String guildName;
	String guildTag;
	uint32 guildLeader;

	Vector<String> sponsoredMap;


public:
	GuildImplementation(uint32 gid, const String& name, const String& tag);

	void sendGuildListTo(Player* player, bool doLock = true);

	void updateGuildFor(Player* player);
	void deleteGuildFor(Player* player);

	inline void setGuildManager(GuildManager* gmanager) {
		guildManager = gmanager;
	}

	inline void setGuildLeader(uint32 guleader) {
		guildLeader = guleader;
	}

	inline uint32 getGuildID() {
		return guildID;
	}

	inline String& getGuildName() {
		return guildName;
	}

	inline void setGuildName(const String& nom) {
		guildName = nom;
	}

	inline uint32 getGuildLeader() {
		return guildLeader;
	}

	inline String& getGuildTag() {
		return guildTag;
	}

	inline void setGuildTag(const String& nom) {
		guildTag = nom;
	}


	ChatRoom* getGuildChat() {
		return guildChannel;
	}

	inline void setGuildChat(ChatRoom* guildchat) {
		guildChannel = guildchat;
	}

	inline void putSponsoredMap(const String& nom) {
		sponsoredMap.add(nom);
	}

	inline int getSponsoredMapSize() {
		return sponsoredMap.size();
	}

	inline String& getSponsoredMap(int i) {
		return sponsoredMap.get(i);
	}

	inline void clearSponsoredMap() {
		sponsoredMap.removeAll();
	}


};

#endif /*GUILDIMPLEMENTATION_H_*/
