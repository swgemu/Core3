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

#include "../../ZoneProcessServerImplementation.h"
#include "../../ZoneServer.h"
#include "../../Zone.h"

#include "../player/PlayerManager.h"
#include "../../objects/player/Player.h"
#include "../player/PlayerMap.h"

#include "../../objects/guild/Guild.h"
#include "../../objects/guild/GuildImplementation.h"
#include "GuildManagerImplementation.h"

#include "../../../login/packets/ErrorMessage.h"

#include "../sui/SuiManager.h"
#include "../../objects/player/sui/messagebox/SuiMessageBox.h"
#include "../../objects/player/sui/inputbox/SuiInputBox.h"
#include "../../objects/player/sui/listbox/SuiListBox.h"

#include "../../../chat/ChatManager.h"

#include "../../packets.h"


GuildManagerImplementation::GuildManagerImplementation(ZoneServer* serv) : GuildManagerServant(), Mutex("GuildManager") {
	server = serv;

	playerManager = server->getPlayerManager();

	guilds = new GuildMap();

	guilds->deploy("GuildMap");

}

GuildManagerImplementation::~GuildManagerImplementation() {
	removeGuilds();

	guilds->finalize();
	guilds = NULL;
}

void GuildManagerImplementation::load() {
	lock();

	ResultSet* guildList;

	StringBuffer query;
	query << "SELECT * FROM guilds";

	guildList = ServerDatabase::instance()->executeQuery(query);

	while (guildList->next()) {
		uint32 gid = guildList->getInt(0);

		String tag = guildList->getString(1);
		String name = guildList->getString(2);

		Guild* guild = new Guild(gid, name, tag);

		guild->setGuildManager((GuildManager*) _this);
		guild->setGuildLeader(guildList->getInt(5));

		guilds->add(guild);
	}

	delete guildList;

	Guild* defaultGuild = new Guild(0, "", "");

	defaultGuild->setGuildManager((GuildManager*) _this);

	guilds->add(defaultGuild);

	unlock();
}

uint32 GuildManagerImplementation::insertGuildToDB (Player* player, String tag, String name, uint64 charID) {
	player->info("Entering GuildManagerImplementation::insertGuildToDB (Player* player, String tag, String name, uint64 charID)");

	String tagString = tag;
	MySqlDatabase::escapeString(tagString);

	String nameString = name;
	MySqlDatabase::escapeString(nameString);

	StringBuffer query;
	Time systemTime;

	uint64 gid = 0;

	try {
		query << "INSERT INTO `guilds` "
			<< "(`guild_tag`,`guild_name`, members, created, leader,last_name_change) "
			<< "VALUES ('" << tagString << "','" << nameString << "'"
			<< ",0," << systemTime.getMiliTime() / 1000 << "," << charID << ","
			<< systemTime.getMiliTime() / 1000 << ");";


		ResultSet* resins = ServerDatabase::instance()->executeQuery(query);
		gid = resins->getLastAffectedRow();

		StringBuffer query2;
		query2 << "UPDATE characters set guild = " << gid << ", guildpermission=255 "
			<< "WHERE character_id = " << charID << ";";

		ServerDatabase::instance()->executeStatement(query2);


		delete resins;

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		player->info("DB Exception in GuildManagerImplementation::insertGuildToDB (Player* player, String tag, String name, uint64 charID)");

		return gid;
	}

	player->info("Clean exit from GuildManagerImplementation::insertGuildToDB (Player* player, String tag, String name, uint64 charID)");
	return gid;
}


bool GuildManagerImplementation::createGuild(Player* player, String& tag, String& name) {
	player->info("ENTERING GuildManagerImplementation::createGuild(Player* player, String& tag, String& name)");

	uint64 charID;

	try {
		player->wlock();

		charID = player->getCharacterID();

		if (player->getGuildID() != 0) {
			player->sendSystemMessage("You cannot create a guild while already in a guild.");

			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::createGuild(Player* player, String& tag, String& name)");
			return false;
		}

		player->unlock();

	} catch (...) {
		player->unlock();
	}

	uint32 gid = insertGuildToDB(player, tag, name, charID);
	if (gid == 0)
		return false;


	//Delete all sponsoring for this character
	declineSponsoring(player->getFirstName(), gid, player);

	if ( !setupNewGuild(player, gid, name, tag) )
		return false;

	player->info("Clean exit from GuildManagerImplementation::createGuild(Player* player, String& tag, String& name)");

	return true;
}


bool GuildManagerImplementation::setupNewGuild(Player* player, uint32 gid, String name, String tag) {
	player->info("Entering GuildManagerImplementation::setupNewGuild(Player* player, uint32 gid, String name, String tag)");

	Guild* guild = NULL;

	try {
		server->lock();

		guild = new Guild(gid, name, tag);

		guild->setGuildManager((GuildManager*) _this);
		guild->setGuildLeader(player->getCharacterID());
		guilds->add(guild);

		player->setGuildPermissions(255);
		player->setGuildLeader(true);

		server->unlock();
	} catch (...) {
		player->info("Clean exit in catch #1 GuildManagerImplementation::setupNewGuild(Player* player, uint32 gid, String name, String tag)");

		server->unlock();
		return false;
	}

	sendGuildListToPlayers(guild);

	player->info("Exit GuildManagerImplementation::setupNewGuild(Player* player, uint32 gid, String name, String tag)");

	return true;
}

void GuildManagerImplementation::sendGuildListToPlayers(Guild* guild) {
	PlayerMap* players = playerManager->getPlayerMap();

	try {
		players->lock();

		players->resetIterator(false);

		while (players->hasNext(false)) {
			Player* player = players->getNextValue(false);

			guild->sendGuildListTo(player);
		}

		players->unlock();
	} catch (...) {
		players->unlock();

		return;
	}
}

String GuildManagerImplementation::getGuildLeaderName(Guild* playerGuild) {
	String leaderName = "";

	ResultSet* guildq;

	try {
		lock();

		StringBuffer query;

		query << "SELECT characters.firstname FROM characters "
			<< "Inner Join guilds ON guilds.leader = characters.character_id "
			<< "Where guilds.guild_id = " << playerGuild->getGuildID() << ";";

		guildq= ServerDatabase::instance()->executeQuery(query);

		if (guildq->next())
			leaderName = guildq->getString(0);

		unlock();

	} catch (...) {
		delete guildq;

		unlock();
		return leaderName;
	}

	delete guildq;
	return leaderName;
}

uint64 GuildManagerImplementation::getOfflineGuildMemberID(String name) {
	String checkName = name.toLowerCase();

	uint64 charID = 0;

	ResultSet* guildq;

	try {
		lock();

		StringBuffer query;

		query << "SELECT character_id FROM characters "
			<< "Where lcase(firstname) = '" << checkName << "';";

		guildq= ServerDatabase::instance()->executeQuery(query);

		if (guildq->next())
			charID = guildq->getLong(0);

		unlock();

	} catch (...) {
		delete guildq;

		unlock();
		return charID;
	}

	delete guildq;
	return charID;
}

Guild* GuildManagerImplementation::getGuild(String& tag, bool doLock) {
	lock(doLock);

	Guild* guild = guilds->get(tag);

	unlock(doLock);

	return guild;
}

Guild* GuildManagerImplementation::getGuild(uint32 gid, bool doLock) {
	lock(doLock);

	Guild* guild = guilds->get(gid);

	unlock(doLock);

	return guild;
}

bool GuildManagerImplementation::removeGuild(int gid) {
	if (gid == 0 )
		return false;

	removePlayersFromGuild(gid);

	StringBuffer query;

	try {
		query << "DELETE FROM guilds WHERE guild_id = '" << gid <<"';";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		return false;
	}

	try {
		query.deleteAll();
		query << "DELETE FROM guilds_sponsoring WHERE guild_id = '" << gid <<"';";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		return false;
	}

	lock();

	guilds->remove(gid);

	unlock();

	return true;
}

void GuildManagerImplementation::removeGuilds() {
	for (int i = 0; i < guilds->size(); ++i) {
		Guild* guild = guilds->get(i);
		guild->finalize();
	}

	guilds->removeAll();
}

void GuildManagerImplementation::removePlayersFromGuild(int gid) {
	uint64 defGuild = 0;

	PlayerMap* players = playerManager->getPlayerMap();
	Player* player;

	Guild* playerGuild;
	ChatRoom* room;

	playerGuild = getGuild(gid);
	if (playerGuild == NULL)
		return;

	room = playerGuild->getGuildChat();


	// TODO: TA: fix this
	try {
		players->lock();

		players->resetIterator(false);

		while (players->hasNext(false)) {
			player = players->getNextValue(false);

			players->unlock();

			try {
				player->wlock();

				if (player->getGuildID() == gid) {

					player->setGuild(defGuild);
					player->updateGuild(defGuild);
					player->setGuildLeader(false);
					player->setGuildPermissions(0);

					if (room != NULL)
						room->removePlayer(player, false);
				}

				player->unlock();
			} catch (...) {
				player->unlock();
			}

			players->lock();
		}

		players->unlock();

	} catch (...) {
		players->unlock();
	}


	try {
		StringBuffer query;
		query << "UPDATE characters set guild = 0, guildpermission = 0 where guild = " << gid << ";";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	player->info("ENTERING GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, String returnString)");

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, String returnString)");
			return;
		}

		player->setInputBoxReturnBuffer(returnString);

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		if (cancel == 1 || returnString == "") {
			player->setInputBoxReturnBuffer("");
			player->info("Clean exit from GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, String returnString)");
			player->unlock();
			return;
		}

		player->unlock();

	} catch (Exception& e) {
		StringBuffer msg;
		player->info("Exception in GuildManagerImplementation::handleGuildTag " + e.getMessage());
		player->unlock();
	} catch (...) {
		player->info("Unreported exception caught in GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, String returnString)");
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, String returnString)");

	handleGuildCreationName(player);
}


void GuildManagerImplementation::handleGuildCreationName(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildCreationName(Player* player)");

	SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7271, 0);

	suiInpBox->setPromptTitle("@guild:create_name_title");
	suiInpBox->setPromptText("@guild:create_name_prompt");
	suiInpBox->setCancelButton(true);
	suiInpBox->setMaxInputSize(25);

	try {
		player->wlock();

		player->addSuiBox(suiInpBox);
		player->sendMessage(suiInpBox->generateMessage());

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildCreationName(Player* player)");
}

void GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	player->info("ENTERING GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, String returnString)");

	String tag;
	String tempName = returnString.toLowerCase();

	GuildManager* myGuildmanager;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			player->info("DEBUG INFO:Player has no SuiBox ?! Exit GuildManager::handleGuildName(uint32 boxID, Player* player, String returnString)");
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		tag = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	if (cancel)
		return;


	if ( ! checkGuildNameAndTag(tempName, tag, player) )
		return;


	if ( ! checkGuildProfanity(returnString, tag, player) )
		return;


	myGuildmanager = server->getGuildManager();

	if (myGuildmanager == NULL) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, String returnString)");
			return;
		}

	if (!myGuildmanager->createGuild(player, tag, returnString) ) {
		ErrorMessage* errMsg = new ErrorMessage("Error:", "There was an error creating the guild, please contact support.", 0);
		player->sendMessage(errMsg);

		player->info("Clean exit from GuildManagerImplementation::checkProfanity(String returnString, String tag, Player* player)");
		return;
	}


	try {
		player->wlock();

		StringBuffer msg;
		msg << "The guild: <" <<  tag << "> " << returnString << " has been created and you are the leader.";
		player->sendSystemMessage(msg.toString());

		player->setGuildLeader(true);

		Guild* myGuild = myGuildmanager->getGuild(tag,true);

		if (myGuild != NULL ) {
			player->setGuild(myGuild);
			player->updateGuild(myGuild);
		}

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	player->info("Clean exit from GuildManager::handleGuildName(uint32 boxID, Player* player, String returnString)");

	player->loadGuildChat();
}


bool GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player) {
	player->info("ENTERING GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");

	Guild* myGuild;

	if (tempName == "") {
		player->info("Clean exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
		return false;
	}

	if (tag.length() > 5) {
		ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_abbrev_bad_length", "", 0);
		player->sendMessage(errMsg);

		player->info("Clean exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
		return false;
	}

	if (tempName.length() > 25) {
		ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_name_bad_length", "", 0);
		player->sendMessage(errMsg);

		player->info("Clean exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
		return false;
	}

	try {
		server->lock();

		for (int i = 0; i < guilds->size(); ++i) {
			myGuild = guilds->get(i);

			if (myGuild != NULL) {
				myGuild->wlock();

				String guildname = myGuild->getGuildName().toLowerCase();

				if (tempName == guildname) {
					server->unlock();
					myGuild->unlock();

					ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_name_in_use", "", 0);
					player->sendMessage(errMsg);

					player->info("Clean exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
					return false;
				}


				String tagName = myGuild->getGuildTag().toLowerCase();
				String tagTemp = tag.toLowerCase();

				if (tagTemp == tagName) {
					server->unlock();
					myGuild->unlock();

					ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_abbrev_in_use","", 0);
					player->sendMessage(errMsg);
					player->info("Clean exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
					return false;
				}
				myGuild->unlock();
			}
		}

		server->unlock();

	} catch (...) {
		server->unlock();
		myGuild->unlock();

		player->info("Exception exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
		return false;
	}

	player->info("Clean exit from GuildManagerImplementation::checkGuildNameAndTag(String tempName, String tag, Player* player)");
	return true;
}


bool GuildManagerImplementation::checkGuildProfanity(String returnString, String tag, Player* player) {

	player->info("Entering GuildManagerImplementation::checkProfanity(String returnString, String tag, Player* player)");

	try {
		player->wlock();

		String name = tag + returnString;

		//Since we are "misusing" the character-name-check here for the guildname profanity check,
		//we need to fake the species to human, o/w the check complains if a (eg.) wookie creates a
		// two word guild name (Wookies are not allowed to have a surname ( = two words)

		String species = "human"; //player->getSpeciesName();

		if ( playerManager != NULL) {
			playerManager->wlock();

			BaseMessage* msg = playerManager->checkPlayerName(name, species);

			playerManager->unlock();

			if (msg != NULL) {
				player->sendMessage(msg);

				player->unlock();
				player->info("Clean exit from GuildManagerImplementation::checkProfanity(String returnString, String tag, Player* player)");

				return false;
			}

		}

		player->unlock();
	} catch (...) {
		player->unlock();

		return false;
	}

	return true;
}


void GuildManagerImplementation::handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	player->info("ENTERING GuildManager::handleGuildSponsor(uint32 boxID, Player* player, String returnString)");

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			player->info("DEBUG INFO:This Player has no SuiBox ?! Exit GuildManager::handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, String returnString)");
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	if (cancel) {
		player->setInputBoxReturnBuffer("");

		player->info("DEBUG INFO:Clean Exit due to cancel button in GuildManager::handleGuildSponsor(uint32 boxID, Player* player, String returnString)");
		return;
	}

	String proband;
	String name = player->getFirstName();

	proband = returnString.toLowerCase();

	String myOwnName = name.toLowerCase();

	if (myOwnName == proband)
		return;

	if (!checkPlayerInRange(player, proband, name))
		return;

	Player* otherPlayer = playerManager->getPlayer(proband);

	if (otherPlayer == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, String returnString)");
		return;
	}

	VerifyBoxSponsorTargetforGuildMembership(otherPlayer, name, player->getGuildName());
}

Player* GuildManagerImplementation::checkInRange(Player* player, const String& proband, const String& selfname) {
	Zone* zone = NULL;

	try {
		player->wlock();

		zone = player->getZone();

		if (zone == NULL) {
			player->unlock();
			return NULL;
		}

		zone->lock();

		for (int i = 0; i < player->inRangeObjectCount(); ++i) {
			SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (obj->isPlayer()) {
				Player* otherPlayer = (Player*) obj;

				String otherName = otherPlayer->getFirstName().toLowerCase();

				if (otherName != selfname && otherName == proband && (player->isInRange(otherPlayer, 8))) {
					player->sendSystemMessage("You sponsor " + otherName + " for membership in <" + (player->getGuild()->getGuildTag()) + ">.");

					zone->unlock();

					player->unlock();

					return otherPlayer;
				}

			}
		}

		zone->unlock();

		player->unlock();
	} catch (...) {
		zone->unlock();
		player->unlock();

		return NULL;
	}

	return NULL;
}


bool GuildManagerImplementation::checkPlayerInRange(Player* player, String proband, String selfname) {
	player->info("Entering GuildManagerImplementation::checkPlayerInRange(Player* player, String proband, String selfname)");

	Player* otherPlayer = checkInRange(player, proband, selfname);

	if (otherPlayer == NULL) {
		ErrorMessage* errMsg = new ErrorMessage("@base_player:swg", "@guild:sponsor_not_found", 0);
		player->sendMessage(errMsg);

		player->info("Clean exit from GuildManagerImplementation::checkPlayerInRange(Player* player, String proband, String selfname)");

		return false;
	}

	try {
		otherPlayer->wlock();

		uint32 othersGuild = otherPlayer->getGuildID();
		String toSponsor = otherPlayer->getFirstName().toLowerCase();

		if (othersGuild != 0) {
			ErrorMessage* errMsg = new ErrorMessage("Guild:", toSponsor + " is already in a guild.", 0);
			player->sendMessage(errMsg);

			otherPlayer->unlock();

			return false;
		}

		otherPlayer->setInputBoxReturnBuffer(selfname);

		otherPlayer->unlock();
	} catch (...) {
		otherPlayer->unlock();
		return false;
	}

	return true;
}

void GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel) {
	otherPlayer->info("Entering GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");

	String inviterName, toSponsor, guildTag;
	uint32 inviteGuild;
	uint64 otherPlayerID;

	try {
		otherPlayer->wlock();

		if (!otherPlayer->hasSuiBox(boxID)) {
			otherPlayer->unlock();

			otherPlayer->info("DEBUG INFO:This Player has no SuiBox ?! Exit GuildManager::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
			return;
		}

		SuiBox* sui = otherPlayer->getSuiBox(boxID);
		otherPlayer->removeSuiBox(boxID);
		sui->finalize();

		//Code in the calling function makes already sure, that inviter and proband are not the same player
		inviterName = otherPlayer->getInputBoxReturnBuffer();
		otherPlayer->setInputBoxReturnBuffer("");

		toSponsor = otherPlayer->getFirstName();
		otherPlayerID = otherPlayer->getCharacterID();


		otherPlayer->unlock();

	} catch (...) {
		otherPlayer->unlock();
		otherPlayer->info("Exit in catch #1 GuildManager::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
	}


	Player* inviter;

	if (inviterName != "" ) {
		inviter = playerManager->getPlayer(inviterName);

		if (inviter == NULL) {
			otherPlayer->info("Inviter player NULL - Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
			return;
		}
	} else {
		otherPlayer->info("Inviter player NULL - Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
		otherPlayer->sendSystemMessage("Sponsoring canceled (InvN_NULL)! Please sponsor the player again.");
		return;
	}


	try {
		inviter->wlock();

		if (cancel) {
			SuiMessageBox* sui = new SuiMessageBox(otherPlayer, 0x1234); //Make it an unknown Box so its handled by default (clean up)

			sui->setPromptTitle("Sponsor For Membership");
			sui->setPromptText(toSponsor + " has declined your sponsorship.");

			inviter->addSuiBox(sui);
			inviter->sendMessage(sui->generateMessage());

			inviter->unlock();

			inviter ->info("Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
			return;
		}

		Guild* guild = inviter->getGuild();

		if ( guild != NULL) {
			try {
				guild->wlock();

				inviteGuild = guild->getGuildID();
				guildTag = guild->getGuildTag();

				guild->unlock();
			} catch (...) {
				guild->unlock();
			}
		}

		inviter->unlock();

	} catch (...) {
		inviter->unlock();
	}


	//delete all previous sponsoring
	declineSponsoring(toSponsor, inviteGuild, inviter);

	//insert to DB
	if ( !insertSponsorshipDB(inviter, otherPlayerID) ) {
		otherPlayer->info("Exit due to failing insert sponsorship to DB in GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
		return;
	}

	StringBuffer message;
	message << inviterName << " has sponsored " << toSponsor  << " for membership in the guild.";
	sendGuildMail(inviter, "Guild manager", "Guild Sponsorship", message.toString(), false);

	otherPlayer->sendSystemMessage("Sponsoring accepted for membership in <" + guildTag + ">.");

	otherPlayer->info("Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
}


bool GuildManagerImplementation::insertSponsorshipDB(Player* inviter, uint64 otherPlayerID) {
	inviter->info("Entering GuildManagerImplementation::insertSponsorshipDB(Player* inviter, uint64 otherPlayerID)");

	try {
		inviter->wlock();

		StringBuffer inmqry;

		inmqry << "INSERT into guilds_sponsoring set guild_id = " << inviter->getGuildID()
			<< ",guild_name ='" << inviter->getGuild()->getGuildTag() << "', sponsored_time = 0, "
			<< "sponsored_by = " << inviter->getCharacterID() << ", sponsored = " << otherPlayerID << ";";

		ServerDatabase::instance()->executeStatement(inmqry);

		inviter->unlock();

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		inviter->info("Exit CATCH in GuildManagerImplementation::insertSponsorshipDB(Player* inviter, uint64 otherPlayerID)");

		inviter->unlock();
		return false;
	}

	return true;
}


void GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, String inviter, String guildname) {
	otherPlayer->info("Entering GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, String inviter, String guildname)");

	try {
		otherPlayer->wlock();

		if (otherPlayer->hasSuiBoxType(0x7273)) {
			otherPlayer->unlock();
			otherPlayer->info("Clean exit from GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, String inviter, String guildname)");
			return;
		}

		SuiMessageBox* sui = new SuiMessageBox(otherPlayer, 0x7273);
		sui->setPromptTitle("Sponsor For Membership");
		sui->setPromptText(inviter + " wishes to sponsor you for membership in " + guildname + "."
						+ " Accepting this will cancel your sponsorship for any other guilds.  Do you accept sponsorship?");

		sui->setCancelButton(true);

		otherPlayer->addSuiBox(sui);
		otherPlayer->sendMessage(sui->generateMessage());

		otherPlayer->unlock();
	} catch (...) {
		otherPlayer->unlock();

		otherPlayer->info("Exit via CATCH in GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, String inviter, String guildname)");
		return;
	}

	otherPlayer->info("Clean exit from GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, String inviter, String guildname)");
}

void GuildManagerImplementation::sendGuildMail(Player* player, String sender, String subject, String body, bool excludeSender) {
	player->info("Entering GuildManagerImplementation::sendGuildMail(Player* player, String sender, String subject, String body, bool excludeSender)");

	int32 guildid;
	String playerName;
	StringBuffer inmqry;

	ChatManager * cm;

	try {
		player->wlock();

		cm = player->getZone()->getChatManager();

		if (cm == NULL) {
			player->unlock();

			player->info("Clean exit from GuildManagerImplementation::sendGuildMail(Player* player, String sender, String subject, String body, bool excludeSender)");
			return;
		}

		guildid = player->getGuildID();

		playerName = player->getFirstName().toLowerCase();

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	inmqry << "SELECT characters.guild, characters.firstname, guilds.guild_tag "
		<< "FROM guilds Inner Join characters ON guilds.guild_id = characters.guild "
		<< "WHERE guilds.guild_id = " << guildid << ";";

	ResultSet* inform;


	try {
		inform = ServerDatabase::instance()->executeQuery(inmqry);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		player->info("DB Exception in GuildManagerImplementation::sendGuildMail(Player* player, String sender, String subject, String body, bool excludeSender)");

		delete inform;
		return;
	}


	while (inform->next()) {
		String receiver = String(inform->getString(1)).toLowerCase();

		UnicodeString uSubject(subject);
		UnicodeString uBody(body);

		if (!((playerName == receiver) && excludeSender)) {
			cm->sendMail(sender, uSubject, uBody, receiver);
		}
	}

	delete inform;

	player->info("Clean exit from GuildManagerImplementation::sendGuildMail(Player* player, String sender, String subject, String body, bool excludeSender)");

}

void GuildManagerImplementation::sendMailGuildLeader(Player* player, String sender, uint32 guildid, String subject, String body) {
	player->info("Entering GuildManagerImplementation::sendMailGuildLeader(Player* player, String sender, uint32 guildid, String subject, String body)");

	ChatManager * cm;

	Guild* playerGuild = NULL;

	try {
		player->wlock();

		playerGuild = player->getGuild();

		cm = player->getZone()->getChatManager();

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	if (cm == NULL || playerGuild == NULL ) {
		player->info("Clean exit from GuildManagerImplementation::sendMailGuildLeader(Player* player, String sender, uint32 guildid, String subject, String body)");
		return;
	}


	String receiver = getGuildLeaderName(playerGuild);
	if (receiver == "") {
		player->info("Clean exit from GuildManagerImplementation::sendMailGuildLeader(Player* player, String sender, uint32 guildid, String subject, String body)");
		return;
	}

	UnicodeString uSubject(subject.toCharArray());
	UnicodeString uBody(body.toCharArray());

	cm->sendMail(sender, uSubject, uBody, receiver);

	player->info("Clean exit from GuildManagerImplementation::sendMailGuildLeader(Player* player, String sender, uint32 guildid, String subject, String body)");
}

void GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->info("Entering GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		if (cancel || index == -1) {
			player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

			player->unlock();
			return;
		}

		Guild* playerGuild = player->getGuild();

		try {
			playerGuild->wlock();

			int size = playerGuild->getSponsoredMapSize();

			if (index < size) {
				player->setInputBoxReturnBuffer( (playerGuild->getSponsoredMap(index)) );

			} else {
				playerGuild->unlock();
				player->unlock();

				player->info("Out of SponsoredMap boundary - Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

				return;
			}

			playerGuild->unlock();

		} catch (...) {
			playerGuild->unlock();
			player->unlock();
			return;
		}

		SuiListBox* sponsoredAcceptBox = new SuiListBox(player, 0x7275);

		sponsoredAcceptBox->setPromptTitle("@guild:sponsor_title");
		sponsoredAcceptBox->setPromptText("@guild:sponsor_verify_title : " + (playerGuild->getSponsoredMap(index)) );
		sponsoredAcceptBox->addMenuItem("@guild:accept");
		sponsoredAcceptBox->addMenuItem("@guild:decline");
		sponsoredAcceptBox->setCancelButton(true);

		player->addSuiBox(sponsoredAcceptBox);
		player->sendMessage(sponsoredAcceptBox->generateMessage());

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");
}

void GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->info("Entering GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	String probandName;
	uint64 probandID;

	try {
		player->wlock();

		probandName = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		return;
	}

	Player* proband = playerManager->getPlayer(probandName);

	if (index == 0) { //sponsored toon accepted into the guild

		if (proband == NULL) {
			player->sendSystemMessage("@guild:ml_not_loaded");
			return;
		}

		if ( !updateCharIntoGuild(proband, player) ) {
			return;
		}

	} else {
		if (proband != NULL) {
			updateDeclineGuild(proband, player);

		} else {
			updateOfflineDeclineGuild(probandName, player);

		}
	}
	player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
}


bool GuildManagerImplementation::updateDeclineGuild(Player* proband, Player* player) {
	proband->info("Entering GuildManagerImplementation::UpdateDeclineGuild(Player* proband, Player* player");

	ChatManager* cm;

	StringBuffer body, subject;

	String guildName, name, probandName;

	try {
		player->wlock();
		proband->wlock(player);

		StringBuffer query;
		query << "DELETE from guilds_sponsoring where sponsored = " << proband->getCharacterID() << ";";

		ServerDatabase::instance()->executeStatement(query.toString());

		guildName = player->getGuildName();

		name = player->getFirstName();
		probandName = proband->getFirstName();

		cm = player->getZone()->getChatManager();

		proband->unlock();
		player->unlock();
	} catch (...) {
		proband->unlock();
		player->unlock();

		return false;
	}

	//Mail for sponsored target
	body << name << " has declined your sponsorship for " << guildName << ".";
	UnicodeString uBody(body.toString());

	subject << "@guildmail:decline_target_subject";
	UnicodeString uSubject(subject.toString());

	if (cm != NULL)
		cm->sendMail("Guild manager", uSubject, uBody, probandName);

	//Mail for guild
	body.deleteAll();
	body << name << " has turned down " << probandName << " for membership in the guild.";

	sendGuildMail(player, "Guild manager", "@guildmail:decline_subject", body.toString(), false);

	return true;
}


bool GuildManagerImplementation::updateOfflineDeclineGuild(String probandName, Player* player) {
	player->info("Entering GuildManagerImplementation::UpdateOfflienDeclineGuild(Player* proband, Player* player");

	ChatManager* cm;

	StringBuffer body, subject;

	String guildName, name;

	uint64 probandID = getOfflineGuildMemberID(probandName);

	if (probandID == 0 )
		return false;

	try {
		player->wlock();

		StringBuffer query;
		query << "DELETE from guilds_sponsoring where sponsored = " << probandID << ";";

		ServerDatabase::instance()->executeStatement(query.toString());

		guildName = player->getGuildName();
		name = player->getFirstName();
		cm = player->getZone()->getChatManager();

		player->unlock();
	} catch (...) {
		player->unlock();
		return false;
	}

	//Mail for sponsored target
	body << name << " has declined your sponsorship for " << guildName << ".";
	UnicodeString uBody(body.toString());

	subject << "@guildmail:decline_target_subject";
	UnicodeString uSubject(subject.toString());

	if (cm != NULL)
		cm->sendMail("Guild manager", uSubject, uBody, probandName);

	//Mail for guild
	body.deleteAll();
	body << name << " has turned down " << probandName << " for membership in the guild.";

	sendGuildMail(player, "Guild manager", "@guildmail:decline_subject", body.toString(), false);

	return true;
}


bool GuildManagerImplementation::updateCharIntoGuild(Player* proband, Player* player) {
	player->info("Entering GuildManagerImplementation::updateCharIntoGuild(Player* proband, Player* player)");

	String name, probandName, guildName;
	StringBuffer query, body, subject;

	uint32 guildID;
	uint64 probandID;

	Guild* guild;
	ChatRoom* guildChat = NULL;

	ChatManager* cm;

	try {
		proband->wlock();
		player->wlock(proband);

		name = player->getFirstName();

		guildName = player->getGuildName();
		guildID = player->getGuildID();
		guild = player->getGuild();

		try {
			guild->wlock();

			guildChat = guild->getGuildChat();

			guild->unlock();
		} catch (...) {
			guild->unlock();
		}

		probandID = proband->getCharacterID();
		probandName = proband->getFirstName();

		cm = player->getZone()->getChatManager();

		player->unlock();
		proband->unlock();

	} catch (...) {
		player->unlock();
		proband->unlock();
	}

	body << name << " has accepted " << probandName << " into the guild as a member.";
	sendGuildMail(player, "Guild manager", "@guildmail:accept_subject", body.toString(), false);

	body.deleteAll();
	body << name << " has accepted you into " << guildName << " as a member.";
	UnicodeString uBody(body.toString());

	subject << "Accepted to guild";
	UnicodeString uSubject(subject.toString());

	if (cm != NULL)
		cm->sendMail("Guild manager", uSubject, uBody, probandName);


	body.deleteAll();
	body << name << " has accepted you for membership in " << guildName << ".";
	proband->sendSystemMessage(body.toString());

	body.deleteAll();
	body << "You accept " << probandName << " for membership in " << guildName << ".";
	player->sendSystemMessage(body.toString());


	try {
		proband->wlock();

		proband->setGuild(guild);
		proband->updateGuild(guild);

		proband->unlock();
	} catch (...) {
		proband->unlock();
		return false;
	}

	if (guildChat != NULL) {
		guildChat->sendTo(proband);
		guildChat->addPlayer(proband, true);
	}


	try {
		query.deleteAll();

		query << "UPDATE characters SET " << "guild = "  << guildID
			  << ", guildpermission = 0 WHERE character_id= " << probandID << ";";

		ServerDatabase::instance()->executeStatement(query.toString());

		//Delete sponsoring from table
		query.deleteAll();
		query << "DELETE from guilds_sponsoring where sponsored = " << probandID << ";";
		ServerDatabase::instance()->executeStatement(query.toString());

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		player->info("DB Exception #2 in GuildManagerImplementation::updateCharIntoGuild(uint64 probandID, Player* player)");

		return false;
	}

	return true;
}

void GuildManagerImplementation::removeOfflineFromGuild(Player* player, String kickee) {
	player->info("Entering GuildManagerImplementation::removeOfflineFromGuild(Player* player, String kickee)");

	String leaderName;
	UnicodeString playerName;
	String checkName = kickee.toLowerCase();

	Guild* playerGuild;

	uint64 removeCharID = 0;

	try {
		player->wlock();

		playerGuild = player->getGuild();
		playerName = player->getCharacterName();

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	leaderName = getGuildLeaderName(playerGuild).toLowerCase();

	if (leaderName == "") {
		player->info("Clean exit from GuildManagerImplementation::removeOfflineFromGuild(Player* player, String kickee)");

		return;
	}

	if (leaderName == checkName) {
		ErrorMessage* errMsg = new ErrorMessage("Guild:", "The guild leader cannot be removed from the guild.", 0);
		player->sendMessage(errMsg);

		player->info("Clean exit from GuildManagerImplementation::removeOfflineFromGuild(Player* player, String kickee)");

		return;
	}

	removeCharID = getOfflineGuildMemberID(checkName);

	if (removeCharID != 0) {
		removeToonFromGuildDB(removeCharID);

		StringBuffer body;
		body << playerName.toString() << " has removed " << kickee << " from the guild.";

		sendGuildMail(player, "Guild manager", "@guildmail:kick_subject", body.toString(), false);
	}

}

void GuildManagerImplementation::removeOnlineFromGuild(Player* player, Player* removePlayer) {
	player->info("Entering GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

	Guild* playerGuild;
	ChatRoom* room;

	uint64 removeCharID;
	uint32 defGuild = 0, playerGuildID;

	try {
		player->wlock();

		if (player != removePlayer)
			removePlayer->wlock(player);

		if (player->getGuildID() == 0) {
			player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

			if (player != removePlayer)
				removePlayer->unlock();

			player->unlock();

			return;
		}


		if ( ! twoPlayersInSameGuild(player, removePlayer)) {
			player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

			if (player != removePlayer)
				removePlayer->unlock();

			player->unlock();

			return;
		}


		playerGuild = player->getGuild();

		removeCharID = removePlayer->getCharacterID();

		room = playerGuild->getGuildChat();


		if (removeCharID == playerGuild->getGuildLeader()) {
			ErrorMessage* errMsg = new ErrorMessage("Guild:", "The guild leader cannot be removed from the guild.", 0);
			player->sendMessage(errMsg);

			player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

			if (player != removePlayer)
				removePlayer->unlock();

			player->unlock();

			return;
		}

		if (player != removePlayer)
			removePlayer->unlock();

		player->unlock();

	} catch (...) {
		if (player != removePlayer)
			removePlayer->unlock();

		player->unlock();
	}


	if (room != NULL)
		room->removePlayer(removePlayer, true);


	notifyOfGuildRemoval(player, removePlayer);

	removePlayer->setGuild(defGuild);
	removePlayer->updateGuild(defGuild);
	removePlayer->setGuildLeader(false);
	removePlayer->setGuildPermissions(0);

	removeToonFromGuildDB(removeCharID);

}

void GuildManagerImplementation::notifyOfGuildRemoval(Player* player, Player* removePlayer) {
	String removeName, guildName, playerName;
	StringBuffer body;
	uint64 removeCharID;
	ChatManager* cm;

	try {
		player->wlock();

		if (player != removePlayer)
			removePlayer->wlock(player);

		cm = removePlayer->getZone()->getChatManager();
		if (cm == NULL) {
			if (player != removePlayer)
				removePlayer->unlock();

			player->unlock();

			return;
		}

		removeName = removePlayer->getFirstName();
		removeCharID = removePlayer->getCharacterID();
		guildName = player->getGuildName();
		playerName = player->getFirstName();

		if (player != removePlayer)
			removePlayer->unlock();

		player->unlock();

	} catch (...) {
		if (player != removePlayer)
			removePlayer->unlock();

		player->unlock();

		return;
	}


	if (player == removePlayer) {
		player->sendSystemMessage("You remove yourself from the guild.");

		body << removeName << " has removed themselves from the guild.";
		sendGuildMail(removePlayer, "Guild manager", "@guildmail:leave_subject", body.toString(), true);

		UnicodeString uSubject("@guildmail:kick_subject");

		body.deleteAll();
		body << "You remove yourself from " << guildName << ".";
		UnicodeString uBody(body.toString());

		cm->sendMail("Guild manager", uSubject, uBody, removeName);

	} else {

		body << "You remove " << removeName << " from " << guildName << ".";
		player->sendSystemMessage(body.toString());

		body.deleteAll();
		body << playerName << " has removed you from " << guildName << ".";
		removePlayer->sendSystemMessage(body.toString());

		body.deleteAll();
		body << playerName << " has removed " << removeName << " from the guild.";
		sendGuildMail(removePlayer, "Guild manager", "@guildmail:kick_subject", body.toString(), true);

		body.deleteAll();
		body << playerName << " has removed you from " << guildName << ".";
		UnicodeString uBody(body.toString());

		UnicodeString uSubject("@guildmail:kick_subject");

		cm->sendMail("Guild manager", uSubject, uBody, removeName);

	}
}

void GuildManagerImplementation::removeToonFromGuildDB(uint64 removeCharID) {
	try {
		StringBuffer update;

		update << "UPDATE `characters` SET `guild` = 0, guildpermission = 0 WHERE character_id = " << removeCharID << ";";

		ServerDatabase::instance()->executeStatement(update);
	} catch (...) {
		System::out << "DB exception in GuildManagerImplementation::removeToonFromGuildDB(removeCharID)" << endl;
		return;
	}
}


bool GuildManagerImplementation::twoPlayersInSameGuild(Player* player, Player* removePlayer) {
	//pre: both players locked

	uint32 playerGuildID = player->getGuildID();
	uint32 removeGuildID = removePlayer->getGuildID();

	if (playerGuildID != removeGuildID)
		return false;

	return true;
}


void GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	player->info("Entering GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

	String name;

	uint32 removeGuildID;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		name = player->getFirstName();
		removeGuildID = player->getGuildID();

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	if (cancel) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");
		return;
	}

	if (returnString != "disband guild") {
		player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");
		return;
	}

	StringBuffer subject;
	StringBuffer body;

	subject << "@guildmail:disband_subject";
	body << "The guild has been disbanded by " << name;

	sendGuildMail(player, "Guild manager", subject.toString(), body.toString(), false);

	removeGuild(removeGuildID);

	player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

}

void GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	//ToDO: After "Guild alpha" on TC is due: Change to allowed only once a week

	player->info("Entering GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, String returnString)");

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, String returnString)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->setInputBoxReturnBuffer(returnString);

		player->removeSuiBox(boxID);
		sui->finalize();

		if (cancel == 1 || returnString == "") {
			player->setInputBoxReturnBuffer("");
			player->info("Clean exit from GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, String returnString)");

			player->unlock();
			return;
		}

		//Create inputbox for renaming the guild
		SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7279, 0);

		suiInpBox->setPromptTitle("@guild:namechange_name_title");
		suiInpBox->setPromptText("@guild:namechange_name_prompt");
		suiInpBox->setCancelButton(true);
		suiInpBox->setMaxInputSize(25);

		player->addSuiBox(suiInpBox);
		player->sendMessage(suiInpBox->generateMessage());

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, String returnString)");
}

void GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	player->info("Entering GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, String returnString)");

	String tag;
	String tempName = returnString.toLowerCase();

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, String returnString)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		tag = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	if (cancel) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, String returnString)");
		return;
	}

	if (!checkGuildNameAndTag(tempName, tag, player))
		return;


	if (!checkGuildProfanity(returnString, tag, player))
		return;

	StringBuffer msg;
	msg << "You have set your guild's name and abbreviation to be changed to '<" << tag << ">' and '" << returnString << "' "
		<< "respectively.  The change will take place in approximately 7 days, if there are no conflicts at that time.";

	player->sendSystemMessage(msg.toString());

	updateGuildInDB(player, tag, returnString);
}


void GuildManagerImplementation::updateGuildInDB(Player* player, String tag, String returnString) {
	player->info("Entering GuildManagerImplementation::updateGuildInDB(Player* player)");

	Guild* myGuild;
	uint32 guildid;
	UnicodeString fullName;

	try {
		player->wlock();

		myGuild = player->getGuild();
		guildid = player->getGuildID();

		fullName = player->getCharacterName();

		String tagString = tag;
		MySqlDatabase::escapeString(tagString);

		String nameString = returnString;
		MySqlDatabase::escapeString(nameString);

		StringBuffer update;
		Time systemTime;

		update << "UPDATE guilds SET `guild_tag` = '" << tagString
				<< "', guild_name = '" << nameString << "', last_name_change ='" << systemTime.getMiliTime() / 1000 << "' "
				<< "WHERE guild_id = " << guildid << ";";

		ServerDatabase::instance()->executeStatement(update);

		player->unlock();
	} catch (...) {
		System::out << "DB Error in GuildManagerImplementation::updateGuildInDB(Player* player)\n";
		player->info("DB Error in GuildManagerImplementation::updateGuildInDB(Player* player)");

		player->unlock();
		return;
	}


	try {
		server->lock();

		myGuild->setGuildTag(tag);
		myGuild->setGuildName(returnString);

		guilds->remove(guildid);
		guilds->add(myGuild);

		server->unlock();
	} catch (...) {
		player->info("ERROR: Exit from catch in GuildManagerImplementation::updateGuildInDB(Player* player)");

		server->unlock();
		return;
	}

	sendGuildListToPlayers(myGuild);

	StringBuffer message;
	message << fullName.toString() << " has renamed the guild to '" << returnString << "' <" << tag << ">.";

	sendGuildMail(player, "Guild manager", "@guildmail:namechange_subject", message.toString(), false);

	player->info("Clean exit from GuildManagerImplementation::updateGuildInDB(Player* player)");
}


void GuildManagerImplementation::handleGuildInformationMembers(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildInformationMembers(Player* player)");

	Guild* playerGuild;
	uint32 playerGuildID;

	SuiListBox* suiListBox = NULL;

	try {
		player->wlock();

		playerGuild = player->getGuild();
		playerGuildID = player->getGuildID();

		playerGuild->clearSponsoredMap();

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	StringBuffer query;
	ResultSet* guildInfo;

	try {
		query << "SELECT firstname, surname FROM characters "
			<< "WHERE guild = " << playerGuildID << " order by firstname;";

		guildInfo = ServerDatabase::instance()->executeQuery(query);

	} catch (...) {
		player->info("DB Error in: void GuildManagerImplementation::handleGuildInformationMembers(Player* player)");

		delete guildInfo;
		return;
	}


	StringBuffer entry;

	try {
		server->lock();

		suiListBox = new SuiListBox(player, 0x7280);

		suiListBox->setPromptTitle("@guild:members_title");
		suiListBox->setPromptText("@guild:members_prompt");
		suiListBox->setCancelButton(true);

		while (guildInfo->next()) {
			entry.deleteAll();
			entry << guildInfo->getString(0) << " " << guildInfo->getString(1);

			suiListBox->addMenuItem(entry.toString());

			playerGuild->putSponsoredMap(guildInfo->getString(0));
		}

		server->unlock();

	} catch (...) {
		player->info("Error in: void GuildManagerImplementation::handleGuildInformationMembers(Player* player)");
		server->unlock();

		delete guildInfo;

		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembers(Player* player)");
		return;
	}



	try {
		player->wlock();

		player->addSuiBox(suiListBox);
		player->sendMessage(suiListBox->generateMessage());

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	delete guildInfo;

	player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembers(Player* player)");
}

void GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->info("Entering GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	Guild* playerGuild;

	String firstname;
	String oFirstname;

	SuiListBox* suiListBox;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		playerGuild = player->getGuild();

		try {
			playerGuild->wlock();

			int size = playerGuild->getSponsoredMapSize();

			if (index < size) {
				player->setInputBoxReturnBuffer( (playerGuild->getSponsoredMap(index)) );
				oFirstname = playerGuild->getSponsoredMap(index);
			} else {
				playerGuild->unlock();
				player->unlock();
				player->info("Out of SponsoredMap boundary - Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

				return;
			}

			firstname = player->getFirstName();

			playerGuild->unlock();
		} catch (...) {
			playerGuild->unlock();
		}

		player->unlock();

	} catch (...) {
		player->unlock();
	}


	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		return;
	}

	firstname = firstname.toLowerCase();
	oFirstname = oFirstname.toLowerCase();

	if (firstname == oFirstname) {
		player->sendSystemMessage("You cannot perform actions on yourself.");
		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

		return;
	}

	StringBuffer prompt;

	try {
		player->wlock();

		suiListBox = new SuiListBox(player, 0x7281);

		prompt << "Select an operation from the list you want to perform on " << playerGuild->getSponsoredMap(index) << " and press Ok.";

		suiListBox->setPromptTitle("@guild:member_options_title");
		suiListBox->setPromptText(prompt.toString());
		suiListBox->addMenuItem("@guild:title");
		suiListBox->addMenuItem("@guild:kick");
		suiListBox->addMenuItem("@guild:permissions");
		suiListBox->setCancelButton(true);

		player->addSuiBox(suiListBox);
		player->sendMessage(suiListBox->generateMessage());

		player->unlock();

	} catch (...) {
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");
}

void GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->info("Entering GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");

	String proband;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		proband = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");

		return;
	}

	switch (index) {
	case (0): //Set Titel
		player->sendSystemMessage("This feature is not implemented yet. Thank you for choosing SWGEmu(C).");
		break;
	case (1): //Kick
		handleRemoveFromGuild(player, proband);
		break;
	case (2): //Set permissions
		callGuildPermissions(player, proband);
		break;
	default:
		player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");
		return;
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");
}

void GuildManagerImplementation::handleRemoveFromGuild(Player* player, String kickee) {
	player->info("Entering GuildManagerImplementation::handleRemoveFromGuild(Player* player, String kickee)");

	String playerName, kickeeName;

	try {
		player->wlock();

		playerName = player->getFirstName().toLowerCase();
		kickeeName = kickee.toLowerCase();

		if (kickeeName != playerName) {
			if (!(player->getGuildPermissions() & PlayerImplementation::GUILDKICK)) {
				player->sendSystemMessage("@guild:generic_fail_no_permission");

				player->unlock();
				return;
			}
		}

		player->setInputBoxReturnBuffer(kickee);

		StringBuffer prompt;
		SuiMessageBox* suiMessageBox = new SuiMessageBox(player, 0x7283);
		prompt << "Are you sure you want kick " << kickee << " out of the guild?";

		suiMessageBox->setPromptTitle("@guild:kick_title");
		suiMessageBox->setPromptText(prompt.toString());
		suiMessageBox->setCancelButton(true);

		player->addSuiBox(suiMessageBox);
		player->sendMessage(suiMessageBox->generateMessage());

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleRemoveFromGuild(Player* player, String kickee)");
}

void GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel) {
	player->info("Entering GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");

	String kickee;

	Player* removePlayer;

	try {
		player->wlock();

		kickee = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		player->unlock();
	} catch (...) {
		player->unlock();
	}


	if (cancel || kickee == "") {
		player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");

		return;
	}


	try {
		removePlayer = playerManager->getPlayer(kickee);

		if (removePlayer != NULL)
			removeOnlineFromGuild(player, removePlayer);
		else
			removeOfflineFromGuild(player, kickee);

	} catch (...) {
		player->info("Exception in GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
		return;
	}

	player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
}

void GuildManagerImplementation::callGuildPermissions(Player* player, String proband) {
	player->info("Entering GuildManagerImplementation::callGuildPermissions(Player* player, String proband)");

	uint32 permissions;

	Player* probandPlayer;

	try {
		player->wlock();

		if ( ! (player->isGuildLeader())) {
			player->sendSystemMessage("@guild:generic_fail_no_permission");
			player->unlock();
			return;
		}

		player->setInputBoxReturnBuffer(proband);

		probandPlayer = playerManager->getPlayer(proband);

		if (probandPlayer != NULL) {

			if (probandPlayer != player) {
				probandPlayer->wlock(player);

			} else {
				player->sendSystemMessage("You cannot change your own permissions.");
				player->unlock();
				return;
			}

			if (probandPlayer->isOnline()) {
				//member is online, pulling permissions from member
				permissions = probandPlayer->getGuildPermissions();
			}

		} else {
			//Member is not online, pull permissions from the DB
			permissions = getGuildPermissionsFromDB(proband);
		}


		SuiListBox* suiListBox = new SuiListBox(player, 0x7282);

		StringBuffer prompt;

		prompt << "These are the current permissions set for " << proband << ".  "
			<< "Permissions preceded by '+' are currently allowed, and those preceded by '-' are not.  "
			<< "Select a permission and press Ok to toggle it.";

		suiListBox->setPromptTitle("@guild:permissions_title");
		suiListBox->setPromptText(prompt.toString());

		if (permissions & PlayerImplementation::GUILDMAIL)
			suiListBox->addMenuItem("@guild:permission_mail_yes");
		else
			suiListBox->addMenuItem("@guild:permission_mail_no");

		if (permissions & PlayerImplementation::GUILDSPONSOR)
			suiListBox->addMenuItem("@guild:permission_sponsor_yes");
		else
			suiListBox->addMenuItem("@guild:permission_sponsor_no");

		if (permissions & PlayerImplementation::GUILDTITLE)
			suiListBox->addMenuItem("@guild:permission_title_yes");
		else
			suiListBox->addMenuItem("@guild:permission_title_no");

		if (permissions & PlayerImplementation::GUILDKICK)
			suiListBox->addMenuItem("@guild:permission_kick_yes");
		else
			suiListBox->addMenuItem("@guild:permission_kick_no");

		if (permissions & PlayerImplementation::GUILDACCEPT)
			suiListBox->addMenuItem("@guild:permission_accept_yes");
		else
			suiListBox->addMenuItem("@guild:permission_accept_no");

		if (permissions & PlayerImplementation::GUILDWAR)
			suiListBox->addMenuItem("@guild:permission_war_yes");
		else
			suiListBox->addMenuItem("@guild:permission_war_no");

		if (permissions & PlayerImplementation::GUILDCHANGENAME)
			suiListBox->addMenuItem("@guild:permission_namechange_yes");
		else
			suiListBox->addMenuItem("@guild:permission_namechange_no");

		if (permissions & PlayerImplementation::GUILDDISBAND)
			suiListBox->addMenuItem("@guild:permission_disband_yes");
		else
			suiListBox->addMenuItem("@guild:permission_disband_no");


		suiListBox->setCancelButton(true);

		player->addSuiBox(suiListBox);
		player->sendMessage(suiListBox->generateMessage());

		if (probandPlayer != NULL && probandPlayer != player)
			probandPlayer->unlock();

		player->unlock();

	} catch (...) {
		if (probandPlayer != NULL && probandPlayer != player)
			probandPlayer->unlock();

		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::callGuildPermissions(Player* player, String proband)");
}

uint32 GuildManagerImplementation::getGuildPermissionsFromDB(String proband) {
	StringBuffer query;
	ResultSet* memberPerm;

	uint32 permissions = 0;

	String checkName = proband.toLowerCase();

	try {
		query << "SELECT guildpermission FROM characters where lcase(firstname) = '" << checkName << "';";

		memberPerm = ServerDatabase::instance()->executeQuery(query);
	} catch (Exception& e) {
		StringBuffer msg;

		msg << "Exception in GuildManager::callGuildPermissions " << e.getMessage();
		System::out << msg.toString() << endl;

		delete memberPerm;
		return permissions;
	}


	if (!memberPerm->next()) {
		delete memberPerm;

		return permissions;
	}

	permissions = memberPerm->getInt(0);

	delete memberPerm;

	return permissions;
}

void GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->info("Entering GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");

	String proband;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		proband = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");

		return;
	}


	Player* probandPlayer = playerManager->getPlayer(proband);


	try {
		if (probandPlayer != NULL) {
			probandPlayer->wlock();

			switch (index) {
			case (0):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDMAIL);
				break;
			case (1):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDSPONSOR);
				break;
			case (2):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDTITLE);
				break;
			case (3):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDKICK);
				break;
			case (4):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDACCEPT);
				break;
			case (5):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDWAR);
				break;
			case (6):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDCHANGENAME);
				break;
			case (7):
				probandPlayer->toggleGuildPermissionsBit(PlayerImplementation::GUILDDISBAND);
			break;
			default:
				probandPlayer->unlock();
				player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
				return;
			}

			probandPlayer->unlock();

		}
	} catch (...) {
		probandPlayer->unlock();
	}


	//proband is offline, touch the DB
	if (probandPlayer == NULL) {

		uint32 permissions = getGuildPermissionsFromDB(proband);

		switch (index) {
		case (0):
			if (!(permissions & PlayerImplementation::GUILDMAIL))
				permissions |= PlayerImplementation::GUILDMAIL;
			else
				permissions &= ~PlayerImplementation::GUILDMAIL;

			break;

		case (1):
			if (!(permissions & PlayerImplementation::GUILDSPONSOR))
				permissions |= PlayerImplementation::GUILDSPONSOR;
			else
				permissions &= ~PlayerImplementation::GUILDSPONSOR;

			break;

		case (2):
			if (!(permissions & PlayerImplementation::GUILDTITLE))
				permissions |= PlayerImplementation::GUILDTITLE;
			else
				permissions &= ~PlayerImplementation::GUILDTITLE;

			break;

		case (3):
			if (!(permissions & PlayerImplementation::GUILDKICK))
				permissions |= PlayerImplementation::GUILDKICK;
			else
				permissions &= ~PlayerImplementation::GUILDKICK;

			break;

		case (4):
			if (!(permissions & PlayerImplementation::GUILDACCEPT))
				permissions |= PlayerImplementation::GUILDACCEPT;
			else
				permissions &= ~PlayerImplementation::GUILDACCEPT;

			break;

		case (5):
			if (!(permissions & PlayerImplementation::GUILDWAR))
				permissions |= PlayerImplementation::GUILDWAR;
			else
				permissions &= ~PlayerImplementation::GUILDWAR;

			break;

		case (6):
			if (!(permissions & PlayerImplementation::GUILDCHANGENAME))
				permissions |= PlayerImplementation::GUILDCHANGENAME;
			else
				permissions &= ~PlayerImplementation::GUILDCHANGENAME;

			break;

		case (7):
			if (!(permissions & PlayerImplementation::GUILDDISBAND))
				permissions |= PlayerImplementation::GUILDDISBAND;
			else
				permissions &= ~PlayerImplementation::GUILDDISBAND;

			break;
		default:
			player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
			return;
		}

		updateGuildPermissionsToDB(proband, permissions);
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");

	callGuildPermissions(player, proband);

}

void GuildManagerImplementation::updateGuildPermissionsToDB(String proband, uint32 permissions) {
	String lProband = proband.toLowerCase();

	try {
		StringBuffer query;

		query << "UPDATE characters set guildpermission = " << permissions
			  << " WHERE lcase(`firstname`) = '" << lProband << "';";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
}

void GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter) {
	inviter->info("Entering GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)");

	Player* declineePlayer;

	try {
		server->lock();

		declineePlayer = playerManager->getPlayer(declinee);

		if (declineePlayer == NULL) {
			inviter->info("Clean exit from GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)");
			server->unlock();
			return;
		}

		server->unlock();
	} catch (...) {
		System::out << "Exception in GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)\n";
		inviter->info("Clean exit via Catch#1 from GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)");

		server->unlock();
		return;
	}

	checkPreviousSponsoringInDB(inviter, declineePlayer, inviteGuild);

	deletePreviousSponsoringsFromDB(declineePlayer);

	inviter->info("Clean exit from GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)");
}

void GuildManagerImplementation::checkPreviousSponsoringInDB(Player* inviter, Player* declineePlayer, uint32 inviteGuild) {
	StringBuffer inmqry;
	String toSponsor;

	ResultSet* decline;

	try {
		//Check previous sponsoring for this character and send out decline mail to that guild leader
		declineePlayer->wlock();

		toSponsor = declineePlayer->getFirstName();

		inmqry.deleteAll();
		inmqry << "SELECT guilds_sponsoring.guild_id, guilds_sponsoring.guild_name, guilds_sponsoring.sponsored_time, "
			<< "guilds_sponsoring.sponsored_by, guilds_sponsoring.sponsored, characters.firstname "

			<< "FROM guilds_sponsoring "

			<< "Inner Join guilds ON guilds_sponsoring.guild_id = guilds.guild_id "
			<< "Inner Join characters ON guilds.leader = characters.character_id "

			<< "WHERE sponsored = " << declineePlayer->getCharacterID() << ";";

		decline = ServerDatabase::instance()->executeQuery(inmqry);

		declineePlayer->unlock();

	} catch (DatabaseException& e) {
		inviter->info(e.getMessage());
		System::out << e.getMessage() << "\n";

		declineePlayer->unlock();

		delete decline;

		return;

	} catch (...) {
		System::out << "Exception in GuildManagerImplementation::checkPreviousSponsoringInDB(Player* inviter, Player* declineePlayer, uint32 inviteGuild)\n";
		inviter->info("Clean exit via Catch#2 from GuildManagerImplementation::checkPreviousSponsoringInDB(Player* inviter, Player* declineePlayer, uint32 inviteGuild)");

		declineePlayer->unlock();

		delete decline;

		return;
	}


	if (decline->next()) {
		String declineGuild = decline->getString(1);
		String declineGuildLeader = decline->getString(5);

		if ( (decline->getInt(0)) == inviteGuild ) {

			ErrorMessage* errMsg = new ErrorMessage("@base_player:swg",
					"The player has been already sponsored for membership in " + declineGuild + ".", 0);
			inviter->sendMessage(errMsg);

			ErrorMessage* errMsg2 = new ErrorMessage("@base_player:swg",
					"You have been already sponsored for membership in " + declineGuild + ".", 0);
			declineePlayer->sendMessage(errMsg2);

			delete decline;
			inviter->info("Clean exit from GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)");

			return;
		}

		StringBuffer message;
		message << toSponsor << " has declined your sponsorship for <" << declineGuild << ">.";

		sendMailGuildLeader(inviter, "Guildmanager", (decline->getInt(0)), "Guild Sponsorship declined", message.toString());

	}

	delete decline;
}

void GuildManagerImplementation::deletePreviousSponsoringsFromDB(Player* declineePlayer) {
	StringBuffer deleteQuery;

	try {
		declineePlayer->wlock();

		deleteQuery << "DELETE from guilds_sponsoring where sponsored = " << declineePlayer->getCharacterID() << ";";
		ServerDatabase::instance()->executeStatement(deleteQuery);

		declineePlayer->unlock();

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		declineePlayer->unlock();

		declineePlayer->info("DB Exception in GuildManagerImplementation::declineSponsoring(String declinee,uint32 inviteGuild, Player* inviter)");
		return;
	}
}

void GuildManagerImplementation::handleGuildInfo(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildInfo(Player* player)");

	uint32 totalMembers = totalMembersCount(player);

	Guild* playerGuild;

	StringBuffer ssTotalMembers;
	StringBuffer guildtag;
	StringBuffer guildname;
	StringBuffer guildleader;

	try {
		player->wlock();

		playerGuild = player->getGuild();

		if (playerGuild == NULL) { //Shouldnt be possible...
			player->unlock();
			return;
		}

		playerGuild->wlock();

		SuiListBox* guildInfoBox = new SuiListBox(player, 0x7276);

		guildInfoBox->setPromptTitle("@guild:info_title");
		guildInfoBox->setPromptText("@guild:menu_info");

		ssTotalMembers << totalMembers;
		String leaderName = getGuildLeaderName(playerGuild);

		guildtag << "Abbreviation: <" << playerGuild->getGuildTag() << ">";
		guildname << "Name: " << playerGuild->getGuildName() << "";
		guildleader << "Leader: " << leaderName;

		guildInfoBox->addMenuItem(guildtag.toString());
		guildInfoBox->addMenuItem(guildname.toString());
		guildInfoBox->addMenuItem(guildleader.toString());
		guildInfoBox->addMenuItem(ssTotalMembers.toString());

		player->addSuiBox(guildInfoBox);
		player->sendMessage(guildInfoBox->generateMessage());

		playerGuild->unlock();
		player->unlock();
	} catch (...) {
		playerGuild->unlock();
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildInfo(Player* player)");
}

void GuildManagerImplementation::handleGuildSponsoring(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildSponsoring(Player* player)");

	ResultSet* sponsoredList;

	StringBuffer query;
	String guildName;

	Guild* playerGuild;
	uint32 playerGuildID;

	try {
		player->wlock();

		if ( ! ( ( player->getGuildPermissions() ) & (PlayerImplementation::GUILDACCEPT) ) ) {
			player->sendSystemMessage("@guild:generic_fail_no_permission");
			player->unlock();
			return;
		}

		player->setInputBoxReturnBuffer("");

		playerGuild = player->getGuild();
		playerGuildID = player->getGuildID();
		playerGuild->clearSponsoredMap();

		guildName = playerGuild->getGuildName();

		player->unlock();
	} catch (...) {
		player->unlock();

		player->info("Exit via catch#1 from GuildManagerImplementation::handleGuildSponsoring(Player* player)");

		return;
	}


	try {
		query << "SELECT guilds_sponsoring.sponsored, characters.firstname, characters.surname "
			<< "FROM guilds_sponsoring "
			<< "Inner Join characters ON guilds_sponsoring.sponsored = characters.character_id "
			<< "where guilds_sponsoring.guild_id= " << playerGuildID << " order by characters.firstname;";

		sponsoredList= ServerDatabase::instance()->executeQuery(query);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		player->info("DB Exception in GuildManagerImplementation::handleGuildInfo(Player* player)");
		return;
	}

	SuiListBox* sponsoredBox = NULL;

	try {
		playerGuild->wlock();
		player->wlock();

		sponsoredBox = new SuiListBox(player, 0x7274);

		sponsoredBox->setPromptTitle("Sponsored for membership: " + guildName);
		sponsoredBox->setPromptText("@guild:sponsored_prompt");
		sponsoredBox->setCancelButton(true);

		while (sponsoredList->next()) {
			sponsoredBox->addMenuItem(sponsoredList->getString(1));
			playerGuild->putSponsoredMap(sponsoredList->getString(1));
		}

		player->addSuiBox(sponsoredBox);
		player->sendMessage(sponsoredBox->generateMessage());

		player->unlock();
		playerGuild->unlock();
	} catch (...) {
		player->info("Exit via catch#2 from GuildManagerImplementation::handleGuildSponsoring(Player* player)");

		player->unlock();
		playerGuild->unlock();

		return;
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildSponsoring(Player* player)");
}


void GuildManagerImplementation::handleGuildRenaming(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildRenaming(Player* player)");

	StringBuffer query;
	ResultSet* guildStamp;

	if ( !checkLastRenameTime(player) ) {
		player->sendSystemMessage("Your are allowed to change your guild's name only every 24 hours.");
		player->info("Clean exit from GuildManagerImplementation::handleGuildRenaming(Player* player)");

		return;
	}

	SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7278, 0);

	suiInpBox->setPromptTitle("@guild:namechange_abbrev_title");
	suiInpBox->setPromptText("@guild:namechange_abbrev_title");
	suiInpBox->setCancelButton(true);
	suiInpBox->setMaxInputSize(5);

	try {
		player->wlock();

		player->addSuiBox(suiInpBox);
		player->sendMessage(suiInpBox->generateMessage());

		player->unlock();
	} catch (...) {
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildRenaming(Player* player)");
}

bool GuildManagerImplementation::checkLastRenameTime(Player* player) {
	StringBuffer query;
	ResultSet* guildStamp;

	try {
		player->wlock();

		query << "SELECT last_name_change FROM guilds where guild_id =" << player->getGuildID() << ";";
		guildStamp = ServerDatabase::instance()->executeQuery(query);

		if (guildStamp->next()) {
			Time systemTime;
			uint64 lastchange;

			lastchange = Long::unsignedvalueOf(guildStamp->getString(0));

			uint64 currentTime = systemTime.getMiliTime() / 1000;

			if (currentTime < lastchange + 86400) { //1 Day (24 h)
				player->unlock();

				return false;
			}
		}

		player->unlock();

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		player->unlock();

		delete guildStamp;

		player->info("DB Exception in GuildManagerImplementation::checkLastRenameTime(Player* player)");
		return false;
	}

	delete guildStamp;

	return true;
}


void GuildManagerImplementation::handleGuildTransferLeader(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

	SuiInputBox* suiInpBox;

	try {
		player->wlock();

		Guild* playerGuild = player->getGuild();
		if (playerGuild == 0) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

			player->unlock();
			return;
		}

		if ( !player->isGuildLeader() ) {
			player->sendSystemMessage("You are not guild leader");
			player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

			player->unlock();
			return;
		}

		suiInpBox = new SuiInputBox(player, 0x7284, 0);

		suiInpBox->setPromptTitle("@guild:make_leader_t");
		suiInpBox->setPromptText("@guild:make_leader_d");
		suiInpBox->setCancelButton(true);
		suiInpBox->setMaxInputSize(25);

		player->addSuiBox(suiInpBox);
		player->sendMessage(suiInpBox->generateMessage());

		player->unlock();

	} catch (...) {
		player->unlock();
	}


	player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeader(Player* player)");
}


void GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString) {
	player->info("Entering GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

	String name;
	String proband = returnString;
	String newLeaderName = "";

	Player* otherPlayer = NULL;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		name = player->getFirstName();

		player->unlock();

	} catch (...) {
		player->unlock();
	}


	if (cancel || proband == "") {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

		return;
	}


	newLeaderName = checkForNewLeader(player, proband);
	if (newLeaderName =="")
		return;

	otherPlayer = playerManager->getPlayer(newLeaderName);

	if (otherPlayer == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

		return;
	}


	//ToDo: If housing is in: Check free lots for PA Hall Transfer

	SuiMessageBox* oSui = new SuiMessageBox(otherPlayer, 0x7285);

	oSui->setPromptTitle("@guild:make_leader_t");
	oSui->setPromptText("@guild:make_leader_p");
	oSui->setCancelButton(true);

	try {
		otherPlayer->wlock();

		otherPlayer->addSuiBox(oSui);
		otherPlayer->sendMessage(oSui->generateMessage());

		otherPlayer->setInputBoxReturnBuffer(player->getFirstName());

		otherPlayer->unlock();

	} catch (...) {
		otherPlayer->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");
}


String GuildManagerImplementation::checkForNewLeader(Player* player, String proband) {
	Zone* zone;

	String name, otherName;;
	String newLeaderName = "";

	proband = proband.toLowerCase();

	Player* otherPlayer;

	try {
		player->wlock();

		name = player->getFirstName().toLowerCase();

		zone = player->getZone();

		player->unlock();

	} catch (...) {
		player->unlock();

		return "";
	}

	try {
		if (zone != NULL) {
			zone->lock();

			for (int i = 0; i < player->inRangeObjectCount(); ++i) {
				SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

				if (obj->isPlayer()) {
					otherPlayer = (Player*) obj;
					otherName = otherPlayer->getFirstName().toLowerCase();

					if (otherName != name && otherName == proband && (player->isInRange(otherPlayer, 8))) {
						newLeaderName = otherName;
						break;
					}
				}
			}

			zone->unlock();
		}
	} catch (...) {
		zone->unlock();

		return "";
	}

	if (newLeaderName == "") {
		player->sendSystemMessage("That person is not loaded or is too far away.");
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

		return "";
	}

	//It is not possible, that otherPlayer == player due to the above name comparison
	try {
		player->wlock();
		otherPlayer->wlock(player);

		if (otherPlayer->getGuildID() != player->getGuildID()) {
			player->sendSystemMessage("Unable to find a member of the PA with that name.");
			player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, String returnString)");

			otherPlayer->unlock();
			player->unlock();

			return "";
		}

		otherPlayer->unlock();
		player->unlock();
	} catch (...) {
		otherPlayer->unlock();
		player->unlock();
	}

	return newLeaderName;
}


void GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel) {
	player->info("Entering GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

	String oldLeader;
	String name;

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

			player->unlock();
			return;
		}

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		name = player->getFirstName();

		oldLeader = player->getInputBoxReturnBuffer();

		player->unlock();

	} catch (...) {
		player->unlock();
	}


	Player* olPlayer = playerManager->getPlayer(oldLeader);

	if (olPlayer == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

		return;
	}


	if (cancel) {
		ErrorMessage* errMsg = new ErrorMessage("@guild:ml_rejected", "", 0);
		olPlayer->sendMessage(errMsg);
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

		return;
	}


	if ( !changeGuildLeader(olPlayer, player) )
		return;


	StringBuffer message;
	message << name << " is the new guild leader.";

	sendGuildMail(player, "Guild manager", "@guildmail:leaderchange_subject", message.toString(), false);

	player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");
}

bool GuildManagerImplementation::changeGuildLeader(Player* olPlayer, Player* player) {
	if (olPlayer == player)
		return false;

	uint64 playerID, olPlayerID;
	uint32 guildID;

	Guild* guild;

	try {
		player->wlock();
		olPlayer->wlock(player);

		player->setGuildPermissions(255);
		player->setGuildLeader(true);

		playerID = player->getCharacterID();

		guild = player->getGuild();
		guildID = player->getGuildID();

		olPlayer->setGuildPermissions(0);
		olPlayer->setGuildLeader(false);

		olPlayerID = olPlayer->getCharacterID();


		try {
			guild->wlock();

			guild->setGuildLeader(playerID);

			guild->unlock();
		} catch (...) {
			guild->unlock();
		}


		olPlayer->unlock();
		player->unlock();

	} catch (...) {
		olPlayer->unlock();
		player->unlock();
	}

	if ( !swapLeaderInDB(playerID, olPlayerID, guildID) )
		return false;

	return true;
}

bool GuildManagerImplementation::swapLeaderInDB(uint64 playerID, uint64 olPlayerID, uint32 guildID) {
	try {
		StringBuffer query;

		query << "UPDATE characters set guildpermission = 255 "
		<< "WHERE character_id = " << playerID << ";";

		ServerDatabase::instance()->executeStatement(query);


		query.deleteAll();
		query << "UPDATE characters set guildpermission = 0 "
		<< "WHERE character_id = " << olPlayerID << ";";

		ServerDatabase::instance()->executeStatement(query);


		query.deleteAll();
		query << "UPDATE guilds set leader = " << playerID
		<< " WHERE guild_id = " << guildID << ";";

		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
		return false;
	}

	return true;
}


uint32 GuildManagerImplementation::totalMembersCount(Player* player) {
	uint32 members = 0;

	ResultSet* guildInfo;

	StringBuffer query;


	try {
		player->wlock();

		query << "SELECT guild from characters where guild = " << player->getGuildID() << ";";

		guildInfo = ServerDatabase::instance()->executeQuery(query);

		members = guildInfo->size();

		player->unlock();


	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";

		player->info("DB Exception in GuildManagerImplementation::totalMembersCount(Player* player)");
		player->unlock();

		delete guildInfo;
		return members;
	}

	delete guildInfo;

	return members;
}
