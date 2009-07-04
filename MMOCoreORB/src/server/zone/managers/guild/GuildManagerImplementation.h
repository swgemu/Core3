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

	bool createGuild(Player* player, String& tag, String& name);

	Guild* getGuild(String& tag, bool doLock = true);
	Guild* getGuild(uint32 gid, bool doLock = true);

	bool removeGuild(int gid);

	void removeGuilds();

	void removePlayersFromGuild(int gid);

	inline GuildMap* getGuildMap() {
		return guilds;
	}

	void handleGuildTag(uint32 boxID, Player* player, uint32 cancel, String returnString);
	void handleGuildName(uint32 boxID, Player* player, uint32 cancel, String returnString);
	void handleGuildCreationName(Player* player);

	void handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, String returnString);

	void handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel);
	void VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, String inviter, String guildname);

	void sendGuildMail(Player* player, String sender, String subject, String msg, bool excludeSender);
	void sendMailGuildLeader(Player* player, String sender, uint32 guildid, String subject, String body);

	void handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index);
	void handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index);
	void handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString);

	void removeOnlineFromGuild(Player* player, Player* removePlayer);
	void removeOfflineFromGuild(Player* player, String removeName);

	void handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, String returnString);
	void handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, String returnString);

	void handleGuildInformationMembers(Player* player);
	void handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index);

	void handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index);

	void handleRemoveFromGuild(Player* player, String kickee);
	void execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel);

	void callGuildPermissions(Player* player, String proband);

	void handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index);

	void declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter);

	void handleGuildInfo(Player* player);

	void handleGuildSponsoring(Player* player);

	void handleGuildRenaming(Player* player);

	void handleGuildTransferLeader(Player* player);
	void handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString);
	void handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel);

	uint32 insertGuildToDB (Player* player, String tag, String name, uint64 chardID);

	bool setupNewGuild(Player* player, uint32 gid, String name, String tag);

	bool checkGuildNameAndTag(String tempname, String tag, Player* player);

	bool checkGuildProfanity(String returnString, String tag, Player* player);

	bool checkPlayerInRange(Player* player, String proband, String selfname);

	bool insertSponsorshipDB(Player* inviter, uint64 otherPlayerID);

	bool updateCharIntoGuild(Player* proband, Player* player);

	bool updateDeclineGuild(Player* proband, Player* player);

	bool twoPlayersInSameGuild(Player* player, Player* removePlayer);

	void notifyOfGuildRemoval(Player* player, Player* removePlayer);

	void removeToonFromGuildDB(uint64 removeCharID);

	void updateGuildInDB(Player* player, String tag, String returnString);

	String getGuildLeaderName(Guild* playerGuild);

	uint64 getOfflineGuildMemberID(String name);

	void sendGuildListToPlayers(Guild* guild);

	uint32 getGuildPermissionsFromDB(String proband);

	void updateGuildPermissionsToDB(String proband, uint32 permissions);

	void deletePreviousSponsoringsFromDB(Player* declineePlayer);

	void checkPreviousSponsoringInDB(Player* inviter, Player* declineePlayer, uint32 inviteGuild);

	bool updateOfflineDeclineGuild(String probandName, Player* player);

	bool checkLastRenameTime(Player* player);

	String checkForNewLeader(Player* player, String proband);

	bool changeGuildLeader(Player* olPlayer, Player* player);

	uint32 totalMembersCount(Player* player);

	bool swapLeaderInDB(uint64 playerID, uint64 olPlayerID, uint32 guildID);

private:
	Player* checkInRange(Player* player, const String& proband, const String& selfname);

};

#endif /*GUILDMANAGERIMPLEMENTATION_H_*/
