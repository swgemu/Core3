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

#ifndef PLAYEROBJECTIMPLEMENTATION_H_
#define PLAYEROBJECTIMPLEMENTATION_H_

#include "PlayerObject.h"
#include "../../../ZoneClientSession.h"

class CreatureObject;
class PlayerObjectImplementation : public PlayerObjectServant {
protected:
	ManagedReference<ZoneClientSession> zoneClient;
	ManagedReference<CreatureObject> linkedCreature;
	//WaypointList* waypointList;
	//FriendsList* friendsList;
	//IgnoreList* ignoreList;

	uint8 onlineStatus;
	uint8 accessLevel;

public:
	static const uint8 ONLINE = 1;
	static const uint8 OFFLINE = 2;
	static const uint8 LINKDEAD = 3;
	static const uint8 LOGGINGIN = 4;
	static const uint8 LOGGINGOUT = 5;
	static const uint8 LOADING = 6;

	//Client side permissions - 0 = Player
	static const uint8 CSR = 1;
	static const uint8 DEVELOPER = 2;

public:
	PlayerObjectImplementation(uint64 objectid, CreatureObject* linkedcreature);
	~PlayerObjectImplementation();

	virtual void sendMessage(BaseMessage* msg);
	virtual void sendMessage(StandaloneBaseMessage* msg);

	//Setters
	inline void setClient(ZoneClientSession* client) {
		zoneClient = client;
	}

	inline void setAccessLevel(uint8 level) {
		accessLevel = level;
	}

	//Getters
	inline ZoneClientSession* getClient() {
		return zoneClient;
	}

	inline uint8 getAccessLevel() {
		return accessLevel;
	}

	inline bool isOnline() {
		return (onlineStatus != OFFLINE && onlineStatus != LINKDEAD);
	}

	inline bool isOffline() {
		return (onlineStatus == OFFLINE);
	}

	inline bool isLoading() {
		return (onlineStatus == LOADING || onlineStatus == LOGGINGIN);
	}

	inline bool isLinkDead() {
		return (onlineStatus == LINKDEAD);
	}

	inline bool isLoggingIn() {
		return (onlineStatus == LOGGINGIN);
	}

	inline bool isLoggingOut() {
		return (onlineStatus == LOGGINGOUT);
	}

	inline bool isPrivileged() {
		return (accessLevel > 0);
	}
};

#endif /*PLAYEROBJECTIMPLEMENTATION_H_*/
