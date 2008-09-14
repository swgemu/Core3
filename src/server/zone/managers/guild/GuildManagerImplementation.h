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

#ifndef GUILDMANAGERIMPLEMENTATION_H_
#define GUILDMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "GuildMapImplementation.h"
#include "GuildManager.h"

class ZoneServer;
class PlayerManager;

class GuildManagerImplementation : public GuildManagerServant, public Mutex {
	GuildMap* guilds;
	Guild* defaultGuild;

	ZoneServer* server;
	PlayerManager* playerManager;

public:
	GuildManagerImplementation(ZoneServer* serv);

	~GuildManagerImplementation();

	void load();

	bool createGuild(Player* player, string& tag, string& name);

	Guild* getGuild(string& tag, bool doLock = true);
	Guild* getGuild(uint32 gid, bool doLock = true);

	bool removeGuild(int gid);

	void removeGuilds();

	void removePlayersFromGuild(int gid);

	inline GuildMap* getGuildMap() {
		return guilds;
	}

	void handleGuildTag(uint32 boxID, Player* player, uint32 cancel, string returnString);
	void handleGuildName(uint32 boxID, Player* player, uint32 cancel, string returnString);
	void handleGuildCreationName(Player* player);

	void handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, string returnString);

	void handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel);
	void VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, string inviter, string guildname);

	void sendGuildMail(Player* player, string sender, string subject, string msg, bool excludeSender);
	void sendMailGuildLeader(Player* player, string sender, uint32 guildid, string subject, string body);

	void handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index);
	void handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index);
	void handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString);

	void removeFromGuild(Player* player, Player* removePlayer);

	void handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, string returnString);
	void handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString);

	void handleGuildInformationMembers(Player* player);
	void handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index);

	void handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index);

	void handleRemoveFromGuild(Player* player, string kickee);
	void execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel);

	void callGuildPermissions(Player* player, string proband);

	void handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index);

	void declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter);

	void handleGuildInfo(Player* player);

	void handleGuildSponsoring(Player* player);

	void handleGuildRenaming(Player* player);

	void handleGuildTransferLeader(Player* player);
	void handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString);
	void handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel);

};

#endif /*GUILDMANAGERIMPLEMENTATION_H_*/
