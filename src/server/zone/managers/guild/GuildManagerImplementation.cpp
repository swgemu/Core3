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

	stringstream query;
	query << "SELECT * FROM guilds";

	guildList = ServerDatabase::instance()->executeQuery(query);

	while (guildList->next()) {
		uint32 gid = guildList->getInt(0);

		string tag = guildList->getString(1);
		string name = guildList->getString(2);

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

bool GuildManagerImplementation::createGuild(Player* player, string& tag, string& name) {
	player->wlock();
	player->info("ENTERING GuildManagerImplementation::createGuild(Player* player, string& tag, string& name)");

	uint64 charID = player->getCharacterID();

	player->info("Entering GuildManagerImplementation::createGuild(Player* player, string& tag, string& name)");

	if (player->getGuildID() != 0) {
		player->sendSystemMessage("You cannot create a guild while already in a guild.");

		player->unlock();
		player->info("Clean exit from GuildManagerImplementation::createGuild(Player* player, string& tag, string& name)");
		return false;
	}

	uint32 gid;

	player->unlock();

	try {
		string tagString = tag;
		MySqlDatabase::escapeString(tagString);

		string nameString = name;
		MySqlDatabase::escapeString(nameString);

		stringstream query;
		Time systemTime;
	    query << "INSERT INTO `guilds` "
	          << "(`guild_tag`,`guild_name`, members, created, leader,last_name_change)"
		      << "VALUES ('" << tagString << "','" << nameString << "'"
		      << ",0," << systemTime.getMiliTime() / 1000 << "," << charID << ","
		      << systemTime.getMiliTime() / 1000 << ");";

		ResultSet* resins = ServerDatabase::instance()->executeQuery(query);
		gid = resins->getLastAffectedRow();
		query.str("");

		stringstream query2;
	    query2 << "UPDATE characters set guild = " << gid << ", guildpermission=255 "
				<< " WHERE character_id = " << charID << ";";

		ServerDatabase::instance()->executeStatement(query2);
		query2.str("");

		//Delete all sponsoring for this character
		declineSponsoring(player->getFirstName(), gid, player);

		delete resins;


	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		player->info("DB Exception in GuildManagerImplementation::createGuild(Player* player, string& tag, string& name)");

		//player->unlock();
		return false;
	}

	PlayerMap* players = playerManager->getPlayerMap();
	Guild* guild = NULL;

	try {
		server->lock();
	
		Guild* guild = new Guild(gid, name, tag);
	
		guild->setGuildManager((GuildManager*) _this);
		guild->setGuildLeader(player->getCharacterID());
		guilds->add(guild);
	
		player->setGuildPermissions(255);
		player->setGuildLeader(true);
		
		server->unlock();
	} catch (...) {
		server->unlock();
	}

	players->resetIterator();

	while (players->hasNext()) {
		Player* player = players->getNextValue();

		player->wlock();
		guild->sendGuildListTo(player);
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::createGuild(Player* player, string& tag, string& name)");

	//Garbage collection
	guild = NULL;
	player = NULL;
	players = NULL;

	return true;
}

Guild* GuildManagerImplementation::getGuild(string& tag, bool doLock) {
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

	stringstream query;

	try {
		query << "DELETE FROM guilds WHERE guild_id = '" << gid <<"';";
		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		query.str("");
		return false;
	}

	try {
		query.str("");
		query << "DELETE FROM guilds_sponsoring WHERE guild_id = '" << gid <<"';";
		ServerDatabase::instance()->executeStatement(query);

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		query.str("");
		return false;
	}

	query.str("");

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

	server->lock();
	
	PlayerMap* players = playerManager->getPlayerMap();
	
	server->unlock();

	players->resetIterator();

	while (players->hasNext()) {
		Player* player = players->getNextValue();

		player->wlock();

		if (player->getGuildID() == gid) {
			Guild* playerGuild = player->getGuild();

			if (playerGuild == NULL) {
				player->unlock();
				return;
			}

			ChatRoom* room = playerGuild->getGuildChat();

			player->setGuild(defGuild);
			player->updateGuild(defGuild);
			player->setGuildLeader(false);
			player->setGuildPermissions(0);

			if (room != NULL)
				room->removePlayer(player, false);

			room = NULL;
			playerGuild = NULL;
		}
		
		player->unlock();
		player = NULL;
	}

	try {
		stringstream query;
		query << "UPDATE characters set guild = 0, guildpermission = 0 where guild = " << gid << ";";
		
		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	player->info("ENTERING GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, string returnString)");

	try {
		player->wlock();

		if (!player->hasSuiBox(boxID)) {
			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, string returnString)");
			return;
		}

		player->setInputBoxReturnBuffer(returnString);

		SuiBox* sui = player->getSuiBox(boxID);
		player->removeSuiBox(boxID);
		sui->finalize();

		if (cancel == 1 || returnString == "") {
			player->setInputBoxReturnBuffer("");
			player->info("Clean exit from GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, string returnString)");
			player->unlock();
			return;
		}

		player->unlock();

	} catch (Exception& e) {
		stringstream msg;
		player->info("Exception in GuildManagerImplementation::handleGuildTag " + e.getMessage());
		player->unlock();
	} catch (...) {
		player->info("Unreported exception caught in GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, string returnString)");
		player->unlock();
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildTag(uint32 boxID, Player* player, string returnString)");

	handleGuildCreationName(player);

	//Garbage collection
	player = NULL;
}


void GuildManagerImplementation::handleGuildCreationName(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildCreationName(Player* player)");
	SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7271, 0);

	suiInpBox->setPromptTitle("@guild:create_name_title");
	suiInpBox->setPromptText("@guild:create_name_prompt");
	suiInpBox->setCancelButton(true);

	player->wlock();

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildCreationName(Player* player)");

	//Garbage collection
	player = NULL;
	suiInpBox = NULL;
}

void GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	player->info("ENTERING GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");

	string tag;
	string tempName = returnString;
	String::toLower(tempName);

	server->lock();
	GuildManager* myGuildmanager = server->getGuildManager();
	server->unlock();

	if (myGuildmanager == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
		return;
	}

	player->wlock();

	if (!player->hasSuiBox(boxID)) {
		player->unlock();
		player->info("DEBUG INFO:Player has no SuiBox ?! Exit GuildManager::handleGuildName(uint32 boxID, Player* player, string returnString)");
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	try {
		tag = player->getInputBoxReturnBuffer();
		player->setInputBoxReturnBuffer("");

		if (tempName == "") {
			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
			return;
		}

		if (tag.size() > 5) {
			ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_abbrev_bad_length", "", 0);
			player->sendMessage(errMsg);
			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
			errMsg = NULL;
			return;
		}

		if (tempName.size() > 25) {
			ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_name_bad_length", "", 0);
			player->sendMessage(errMsg);
			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
			errMsg = NULL;
			return;
		}

		server->lock();

		for (int i = 0; i < guilds->size(); ++i) {
			Guild* myGuild = guilds->get(i);

			if (myGuild != NULL) {
				string guildname = myGuild->getGuildName();
				String::toLower(guildname);

				if (tempName == guildname) {
					server->unlock();

					ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_name_in_use", "", 0);
					player->sendMessage(errMsg);

					player->unlock();
					player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
					errMsg = NULL;
					return;
				}


				string tagName = myGuild->getGuildTag();
				string tagTemp = tag;
				String::toLower(tagName);
				String::toLower(tagTemp);

				if (tagTemp == tagName) {
					server->unlock();

					ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_abbrev_in_use","", 0);
					player->sendMessage(errMsg);

					player->unlock();
					player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
					errMsg = NULL;
					return;
				}
			}
			myGuild = NULL;
		}

		server->unlock();

		//Check guild tag and guild name for invalid characters and profanity
		string name = tag + returnString;
		string species = player->getSpeciesName();

		if ( playerManager != NULL) {
			playerManager->wlock();

			BaseMessage* msg = playerManager->checkPlayerName(name, species);

			playerManager->unlock();

			if (msg != NULL) {
				player->sendMessage(msg);

				player->unlock();
				player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");

				return;
			}
			msg = NULL;
		}

		if (cancel == 1 || tempName == "") {
			player->unlock();
			player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
			return;
		}

		player->unlock();

		if (!myGuildmanager->createGuild(player, tag, returnString) ) {
			player->wlock();

			ErrorMessage* errMsg = new ErrorMessage("Error:", "There was an error creating the guild, please contact support.", 0);
			player->sendMessage(errMsg);

			player->unlock();

			player->info("Clean exit from GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
			errMsg = NULL;
			return;
		}

		player->wlock();

		stringstream msg;
		msg << "The guild: <" <<  tag << "> " << returnString << " has been created and you are the leader.";
		player->sendSystemMessage(msg.str());

		player->setGuildLeader(true);

		Guild* myGuild = myGuildmanager->getGuild(tag,true);

		if (myGuild != NULL ) {
			player->setGuild(myGuild);
			player->updateGuild(myGuild);
		}

	} catch (Exception& e) {
		stringstream msg;
		msg << "Exception in GuildManager::handleGuildName " << e.getMessage();
		cout << msg;
		player->info("DB Exception in GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
		player->unlock();

	} catch (...) {
		player->info("Unreported exception caught in GuildManagerImplementation::handleGuildName(uint32 boxID, Player* player, string returnString)");
		player->unlock();
	}

	player->unlock();

	player->info("Clean exit from GuildManager::handleGuildName(uint32 boxID, Player* player, string returnString)");

	player->loadGuildChat();

	//Garbage collection
	myGuildmanager = NULL;
	player = NULL;
}

void GuildManagerImplementation::handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	player->info("ENTERING GuildManager::handleGuildSponsor(uint32 boxID, Player* player, string returnString)");

	player->wlock();

	if (!player->hasSuiBox(boxID)) {
		player->unlock();
		player->info("DEBUG INFO:This Player has no SuiBox ?! Exit GuildManager::handleGuildSponsor(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	player->unlock();


	if (cancel) {
		player->setInputBoxReturnBuffer("");

		player->info("DEBUG INFO:Clean Exit due to cancel button in GuildManager::handleGuildName(uint32 boxID, Player* player, string returnString)");
		return;
	}

	string tag, errmsg, proband;
	string name = player->getFirstName();
	string toSponsor = "";

	uint32 othersGuild;
	Player* otherPlayer;

	if (server == NULL) {
		player->info("DEBUG INFO:Clean exit - Zone (server) is NULL in GuildManager::handleGuildSponsor(uint32 boxID, Player* player, string returnString)");
		return;
	}

	proband = returnString;
	String::toLower(proband);

	Zone* zone = player->getZone();
	if (zone == NULL)
		return;

	//server->lock();
	zone->lock();

	for (int i = 0; i < player->inRangeObjectCount(); ++i) {
		SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

		if (obj->isPlayer()) {
			otherPlayer = (Player*) obj;

			string otherName = otherPlayer->getFirstName();
			String::toLower(otherName);

			if (otherName != name && otherName == proband && (player->isInRange(otherPlayer, 8))) {
				player->sendSystemMessage("You sponsor " + otherName + " for membership in <" + (player->getGuild()->getGuildTag()) + ">.");
				toSponsor = otherName;
				othersGuild = otherPlayer->getGuildID();
				break;
			}
		}
		obj = NULL;
	}

	zone->unlock();
	//server->unlock();

	if ( toSponsor == "") {
		ErrorMessage* errMsg = new ErrorMessage("@base_player:swg", "@guild:sponsor_not_found", 0);
		player->sendMessage(errMsg);
		player->info("Clean exit from GuildManager::handleGuildSponsor(uint32 boxID, Player* player, string returnString)");
		errMsg = NULL;
		return;
	}


	if ( othersGuild != 0) {
		ErrorMessage* errMsg = new ErrorMessage("Guild:", toSponsor + " is already in a guild.", 0);
		player->sendMessage(errMsg);
		player->info("Clean exit from GuildManager::handleGuildSponsor(uint32 boxID, Player* player, string returnString)");
		errMsg = NULL;
		return;
	}

	otherPlayer->lock();
	otherPlayer->setInputBoxReturnBuffer(name);
	otherPlayer->unlock();

	VerifyBoxSponsorTargetforGuildMembership(otherPlayer, name, player->getGuildName());

	//Garbage collection
	otherPlayer = NULL;
	player = NULL;
	zone = NULL;
}

void GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel) {
	otherPlayer->wlock();

	otherPlayer->info("Entering GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");

	if (!otherPlayer->hasSuiBox(boxID)) {
		otherPlayer->unlock();
		otherPlayer->info("DEBUG INFO:This Player has no SuiBox ?! Exit GuildManager::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
		return;
	}

	SuiBox* sui = otherPlayer->getSuiBox(boxID);
	otherPlayer->removeSuiBox(boxID);
	sui->finalize();

	string inviterName = otherPlayer->getInputBoxReturnBuffer();
	otherPlayer->setInputBoxReturnBuffer("");

	if (inviterName == "") {
		otherPlayer->unlock();
		otherPlayer->info("Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
		return;
	}

	server->lock();
	Player* inviter = playerManager->getPlayer(inviterName);
	server->unlock();

	if (inviter == NULL) {
		otherPlayer->unlock();
		otherPlayer->info("Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
		return;
	}


	if (cancel) {
		SuiMessageBox* sui = new SuiMessageBox(otherPlayer, 0x1234); //Make it an unknown Box so its handled by default (clean up)

		sui->setPromptTitle("Sponsor For Membership");
		sui->setPromptText((otherPlayer->getFirstName()) + " has declined your sponsorship.");

		inviter->wlock();

		inviter->addSuiBox(sui);
		inviter->sendMessage(sui->generateMessage());

		inviter->unlock();
		otherPlayer->unlock();

		otherPlayer->info("Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");
		return;
	}


	inviter->wlock();

	uint32 inviteGuild = inviter->getGuildID();
	string toSponsor = otherPlayer->getFirstName();
	string guildTag = inviter->getGuild()->getGuildTag();
	uint64 inviterID = inviter->getCharacterID();
	uint64 otherPlayerID = otherPlayer->getCharacterID();

	inviter->unlock();
	otherPlayer->unlock();

	//delete all previous sponsoring
	declineSponsoring(inviterName, inviteGuild, otherPlayer);

	otherPlayer->sendSystemMessage("Sponsoring accepted for membership in <" + guildTag + ">.");

	try {
		//Insert this sponsorship to DB
		stringstream inmqry;
		inmqry.str("");
		inmqry << "INSERT into guilds_sponsoring set guild_id = " << inviteGuild
			<< ",guild_name ='" << inviter->getGuild()->getGuildTag() << "', sponsored_time = 0, "
			<< "sponsored_by = " << inviterID << ", sponsored = " << otherPlayerID << ";";

		ServerDatabase::instance()->executeStatement(inmqry);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}

	stringstream message;
	message.str("");

	message << inviterName << " has sponsored " << toSponsor  << " for membership in the guild.";

	sendGuildMail(inviter, "Guild manager", "Guild Sponsorship", message.str(), false);

	otherPlayer->info("Clean exit from GuildManagerImplementation::handleVerifyBoxSponsorTargetforGuildMembership(uint32 boxID, Player* otherPlayer, uint32 cancel)");

	//Garbage collection
	otherPlayer = NULL;
	inviter = NULL;
}


void GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, string inviter, string guildname) {
	otherPlayer->wlock();

	otherPlayer->info("Entering GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, string inviter, string guildname)");

	if (otherPlayer->hasSuiBoxType(0x7273)) {
		otherPlayer->unlock();
		otherPlayer->info("Clean exit from GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, string inviter, string guildname)");
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

	otherPlayer->info("Clean exit from GuildManagerImplementation::VerifyBoxSponsorTargetforGuildMembership(Player* otherPlayer, string inviter, string guildname)");

	//Garbage collection
	otherPlayer = NULL;
	sui = NULL;
}

void GuildManagerImplementation::sendGuildMail(Player* player, string sender, string subject, string body, bool excludeSender) {
	player->wlock();
	player->info("Entering GuildManagerImplementation::sendGuildMail(Player* player, string sender, string subject, string body, bool excludeSender)");

	stringstream inmqry;
	inmqry.str("");

	ChatManager * cm = player->getZone()->getChatManager();
	if (cm == NULL) {
		player->unlock();
		player->info("Clean exit from GuildManagerImplementation::sendGuildMail(Player* player, string sender, string subject, string body, bool excludeSender)");
		return;
	}


	uint32 guildid = player->getGuildID();
	string playerName = player->getFirstName();
	String::toLower(playerName);

	inmqry << "SELECT characters.guild, characters.firstname, guilds.guild_tag "
		<< "FROM guilds Inner Join characters ON guilds.guild_id = characters.guild "
		<< "WHERE guilds.guild_id = "
		<< guildid << ";";

	ResultSet* inform;

	player->unlock();


	try {

		inform = ServerDatabase::instance()->executeQuery(inmqry);

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		player->info("DB Exception in GuildManagerImplementation::sendGuildMail(Player* player, string sender, string subject, string body, bool excludeSender)");
		delete inform;
		return;
	}


	while (inform->next()) {
		string receiver = inform->getString(1);
		String::toLower(receiver);

		unicode uSubject(subject.c_str());
		unicode uBody(body.c_str());

		if (! ( (playerName == receiver) && excludeSender) ) {
			cm->sendMail(sender, uSubject, uBody, receiver);
		}
	}

	delete inform;

	player->info("Clean exit from GuildManagerImplementation::sendGuildMail(Player* player, string sender, string subject, string body, bool excludeSender)");

	//Garbage collection
	player = NULL;
	cm = NULL;
	inmqry.str("");

}

void GuildManagerImplementation::sendMailGuildLeader(Player* player, string sender, uint32 guildid, string subject, string body) {
	player->info("Entering GuildManagerImplementation::sendMailGuildLeader(Player* player, string sender, uint32 guildid, string subject, string body)");
	stringstream inmqry;
	inmqry.str("");

	inmqry << "SELECT guilds.guild_id, characters.firstname "
			<< "FROM characters Inner Join guilds ON guilds.leader = characters.character_id "
			<< "WHERE guilds.guild_id = "
			<< guildid << ";";

	ResultSet* inform;

	player->wlock();
	ChatManager * cm = player->getZone()->getChatManager();
	player->unlock();

	if (cm == NULL) {
		player->info("Clean exit from GuildManagerImplementation::sendMailGuildLeader(Player* player, string sender, uint32 guildid, string subject, string body)");
		return;
	}

	try {
		inform = ServerDatabase::instance()->executeQuery(inmqry);

		if (inform->next()) {
			string receiver = inform->getString(1);

			unicode uSubject(subject.c_str());
			unicode uBody(body.c_str());

			cm->sendMail(sender, uSubject, uBody, receiver);
		}

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		player->info("DB Exception in GuildManagerImplementation::sendMailGuildLeader(Player* player, string sender, uint32 guildid, string subject, string body)");
		delete inform;
		return;
	}

	delete inform;

	player->info("Clean exit from GuildManagerImplementation::sendMailGuildLeader(Player* player, string sender, uint32 guildid, string subject, string body)");

	//Garbage collection
	player = NULL;
	cm = NULL;
	inmqry.str("");
}

void GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->wlock();
	player->info("Entering GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

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

	player->setInputBoxReturnBuffer( (playerGuild->getSponsoredMap(index)) );

	SuiListBox* sponsoredAcceptBox = new SuiListBox(player, 0x7275);

	sponsoredAcceptBox->setPromptTitle("@guild:sponsor_title");
	sponsoredAcceptBox->setPromptText("@guild:sponsor_verify_title : " + (playerGuild->getSponsoredMap(index)) );
	sponsoredAcceptBox->addMenuItem("@guild:accept");
	sponsoredAcceptBox->addMenuItem("@guild:decline");
	sponsoredAcceptBox->setCancelButton(true);

	player->addSuiBox(sponsoredAcceptBox);
	player->sendMessage(sponsoredAcceptBox->generateMessage());

	player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	player->unlock();

	//Garbage collection
	player = NULL;
	sponsoredAcceptBox = NULL;
	playerGuild = NULL;
}

void GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	string probandName = player->getInputBoxReturnBuffer();
	string name = player->getFirstName();

	player->setInputBoxReturnBuffer("");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	if (cancel || index == -1) {
		player->unlock();
		player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		return;
	}

	ChatManager* cm = player->getZone()->getChatManager();
	if (cm == NULL) {
		player->unlock();
		player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		return;
	}

	server->lock();
	Player* proband = playerManager->getPlayer(probandName);
	server->unlock();

	if (proband == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	Guild* playerGuild = player->getGuild();
	string guildName = playerGuild->getGuildName();
	ChatRoom* guildchat = playerGuild->getGuildChat();

	player->unlock();

	stringstream body;
	stringstream body2;
	stringstream body3;
	stringstream subject;

	if (index == 0) { //sponsored toon accepted into the guild

		body3 << name << " has accepted " << probandName << " into the guild as a member.";
		sendGuildMail(player, "Guild manager", "@guildmail:accept_subject", body3.str(), false);


		body << name << " has accepted you into " << guildName << " as a member.";
		unicode uBody(body.str());
		subject << "Accepted to guild";
		unicode uSubject(subject.str());
		cm->sendMail("Guild manager", uSubject, uBody, probandName);


		proband->wlock();

		uint64 probandID = proband->getCharacterID();

		proband->setGuild(playerGuild);
		proband->updateGuild(playerGuild);

		proband->unlock();


		guildchat->sendTo(proband);
		guildchat->addPlayer(proband, true);

		//Update CHAR to new guild
		stringstream query;
		query << "UPDATE characters SET " << "guild ="
			  << proband->getGuildID()
			  << ", guildpermission = 0 WHERE character_id= " << probandID << ";";

		ServerDatabase::instance()->executeStatement(query.str());

		//Delete sponsoring from table
		query.str("");
		query << "DELETE from guilds_sponsoring where sponsored = " << probandID << ";";
		ServerDatabase::instance()->executeStatement(query.str());

		body.str("");
		body << name << " has accepted you for membership in " << guildName << ".";
		proband->sendSystemMessage(body.str());

		body2 << "You accept " << probandName << " for membership in " << guildName << ".";
		player->sendSystemMessage(body2.str());

	} else {

		proband->wlock();
		uint64 probandID = proband->getCharacterID();
		proband->unlock();

		ostringstream query;
		query << "DELETE from guilds_sponsoring where sponsored = " << probandID << ";";
		ServerDatabase::instance()->executeStatement(query.str());

		//Mail for sponsored target
		body << name << " has declined your sponsorship for " << guildName << ".";
		unicode uBody(body.str());

		subject << "@guildmail:decline_target_subject";
		unicode uSubject(subject.str());

		cm->sendMail("Guild manager", uSubject, uBody, probandName);

		//Mail for guild
		body2.str("");
		body2 << name << " has turned down " << probandName << " for membership in the guild.";

		sendGuildMail(player, "Guild manager", "@guildmail:decline_subject", body2.str(), false);
	}

	body.str("");
	body2.str("");
	body3.str("");
	subject.str("");

	player->info("Clean exit from GuildManagerImplementation::handleSponsoredGuildMembersAcceptBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	//Garbage Collection
	cm = NULL;
	proband = NULL;
	player = NULL;
	playerGuild = NULL;
	guildchat = NULL;
}

void GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

	if (player != removePlayer)
		removePlayer->wlock();

	if (player->getGuildID() == 0) {
		player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");
		player->unlock();
		if (player != removePlayer)
			removePlayer->unlock();

		return;
	}

	int playerGuildID = player->getGuildID();
	int removeGuildID = removePlayer->getGuildID();

	if (playerGuildID != removeGuildID) {
		player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");
		player->unlock();
		if (player != removePlayer)
			removePlayer->unlock();

		return;
	}


	Guild* playerGuild = player->getGuild();
	ChatRoom* room = playerGuild->getGuildChat();

	uint defGuild=0;
	string subject;
	stringstream body;
	body.str("");

	string guildname = playerGuild->getGuildName();
	string name = player->getFirstName();
	uint64 myCharid = player->getCharacterID();

	string removeName = removePlayer->getFirstName();
	uint64 removeCharid = removePlayer->getCharacterID();

	if (removeCharid == playerGuild->getGuildLeader()) {
		ErrorMessage* errMsg = new ErrorMessage("Guild:", "The guild leader cannot be removed from the guild.", 0);
		player->sendMessage(errMsg);

		player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

		player->unlock();
		if (player != removePlayer)
			removePlayer->unlock();

		errMsg = NULL;
		return;
	}

	player->unlock();
	if (player != removePlayer)
		removePlayer->unlock();

	if (room != NULL)
		room->removePlayer(removePlayer, true);

	if (player == removePlayer) {
		player->sendSystemMessage("You remove yourself from the guild.");

		body << name << " has removed themselves from the guild.";
		subject = "@guildmail:leave_subject";
		sendGuildMail(removePlayer, "Guild manager", subject, body.str(), true);

		stringstream sSubject;
		sSubject << "@guildmail:kick_subject";
		unicode uSubject(sSubject.str());

		body.str("");
		body << "You remove yourself from " << guildname << ".";
		unicode uBody(body.str());

		removePlayer->wlock();
		ChatManager * cm = removePlayer->getZone()->getChatManager();
		removePlayer->unlock();

		if (cm != NULL)
			cm->sendMail("Guild manager", uSubject, uBody, removeName);

		body.str("");
		sSubject.str("");
		cm = NULL;

	} else {

		body.str("");
		body << "You remove " << removeName << " from " << guildname << ".";
		player->sendSystemMessage(body.str());

		body.str("");
		body << name << " has removed you from " << guildname << ".";
		removePlayer->sendSystemMessage(body.str());

		body.str("");
		body << name << " has removed " << removeName << " from the guild.";
		subject = "@guildmail:kick_subject";

		sendGuildMail(player, "Guild manager", subject, body.str(), false);

		stringstream sSubject;

		sSubject << "@guildmail:kick_subject";
		unicode uSubject(sSubject.str());

		body.str("");
		body << name << " has removed you from " << guildname << ".";
		unicode uBody(body.str());

		removePlayer->wlock();
		ChatManager * cm = removePlayer->getZone()->getChatManager();
		removePlayer->unlock();

		if (cm != NULL)
			cm->sendMail("Guild manager", uSubject, uBody, removeName);

		body.str("");
		sSubject.str("");
		cm = NULL;
	}

	removePlayer->setGuild(defGuild);
	removePlayer->updateGuild(defGuild);
	removePlayer->setGuildLeader(false);
	removePlayer->setGuildPermissions(0);

	stringstream update;
	update << "UPDATE `characters` SET `guild` = 0, guildpermission=0 WHERE character_id = " << removeCharid << ";";
	ServerDatabase::instance()->executeStatement(update);

	player->info("Clean exit from GuildManagerImplementation::removeFromGuild(Player* player, Player* removePlayer)");

	//Garbage collection
	player = NULL;
	playerGuild = NULL;
	removePlayer = NULL;
	room = NULL;
}

void GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	string name = player->getFirstName();

	player->unlock();

	if (cancel) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		return;
	}

	if (returnString != "disband guild") {
		player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		return;
	}

	stringstream subject;
	stringstream body;

	subject << "@guildmail:disband_subject";
	body << "The guild has been disbanded by " << name;

	sendGuildMail(player, "Guild manager", subject.str(), body.str(), false);

	removeGuild(player->getGuildID());

	player->info("Clean exit from GuildManagerImplementation::handleGuildDisbandBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	//Garbage collection
	player = NULL;
	body.str("");
	subject.str("");
}

void GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	//ToDO: After "Guild alpha" on TC is due: Change to allowed only once a week

	player->wlock();
	player->info("Entering GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->setInputBoxReturnBuffer(returnString);

	player->removeSuiBox(boxID);
	sui->finalize();

	if (cancel == 1 || returnString == "") {
		player->setInputBoxReturnBuffer("");
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, string returnString)");

		player->unlock();
		return;
	}

	//Create inputbox for renaming the guild
	SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7279, 0);

	suiInpBox->setPromptTitle("@guild:namechange_name_title");
	suiInpBox->setPromptText("@guild:namechange_name_prompt");
	suiInpBox->setCancelButton(true);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());


	player->info("Clean exit from GuildManagerImplementation::handleGuildNameChange(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	player->unlock();

	//Garbage collection
	player = NULL;
	suiInpBox = NULL;
}

void GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	string tag;
	string tempName = returnString;
	String::toLower(tempName);

	server->lock();

	GuildManager* myGuildmanager = server->getGuildManager();
	GuildMap* myGuildMap;

	if (myGuildmanager != NULL)
		myGuildMap = myGuildmanager->getGuildMap();
	else {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		server->unlock();
		return;
	}

	server->unlock();

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	if (cancel) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		return;
	}


	tag = player->getInputBoxReturnBuffer();
	player->setInputBoxReturnBuffer("");

	if (tag.size() > 5) {
		player->sendSystemMessage("@guild:namechange_fail_abbrev_bad_length");
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		return;
	}

	if (tempName.size() > 25) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->sendSystemMessage("@guild:namechange_fail_name_bad_length");
		player->unlock();
		return;
	}

	if (tempName == "") {
		player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
		player->unlock();
		return;
	}

	lock();

	for (int i = 0; i < myGuildMap->size(); ++i) {
		Guild* theGuild = myGuildMap->get(i);

		if (theGuild != NULL) {
			string guildname = theGuild->getGuildName();
			String::toLower(guildname);

			string guildtag = theGuild->getGuildTag();
			String::toLower(guildtag);

			if (tempName == guildname) {
				ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_name_in_use","", 0);
				player->sendMessage(errMsg);

				player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");

				unlock();
				player->unlock();
				errMsg = NULL;
				return;
			}
			if (guildtag == tag) {
				ErrorMessage* errMsg = new ErrorMessage("@guild:create_fail_name_in_use","", 0);
				player->sendMessage(errMsg);

				player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");

				unlock();
				player->unlock();
				errMsg = NULL;
				return;
			}
			theGuild = NULL;
		}
	}

	unlock();

	//Check guild tag and guild name for invalid characters and profanity
	string name = tag + returnString;
	string species = player->getSpeciesName();

	if ( playerManager != NULL) {
		playerManager->wlock();

		BaseMessage* msg = playerManager->checkPlayerName(name, species);

		playerManager->unlock();

		if (msg != NULL) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");
			player->sendMessage(msg);
			player->unlock();
			return;
		}
		msg->finalize();
	}

	stringstream msg;
	msg << "You have set your guild's name and abbreviation to be changed to '<" << tag << ">' and '" << returnString << "' "
		<< "respectively.  The change will take place in approximately 7 days, if there are no conflicts at that time.";

	player->sendSystemMessage(msg.str());


	Guild* myGuild = player->getGuild();
	uint32 guildid = player->getGuildID();

	player->unlock();

	string tagString = tag;
	MySqlDatabase::escapeString(tagString);

	string nameString = returnString;
	MySqlDatabase::escapeString(nameString);

	stringstream update;
	Time systemTime;

	update << "UPDATE guilds SET `guild_tag` = '" << tagString
			<< "', guild_name = '" << nameString << "', last_name_change ='" << systemTime.getMiliTime() / 1000 << "' "
			<< "WHERE guild_id = " << guildid << ";";

	ServerDatabase::instance()->executeStatement(update);


	server->lock();
	myGuild->setGuildTag(tag);
	myGuild->setGuildName(returnString);

	guilds->remove(guildid);
	guilds->add(myGuild);

	PlayerMap* players = playerManager->getPlayerMap();

	server->unlock();

	players->resetIterator();

	while (players->hasNext()) {
		Player* oPlayer = players->getNextValue();
		oPlayer->wlock();

		if (oPlayer->getGuildID() == guildid) {
			myGuild->sendGuildListTo(oPlayer);
			oPlayer->updateGuild(myGuild);
		}
		oPlayer->unlock();
	}

	stringstream message;
	message << "Farmer John has renamed the guild to '" << returnString << "' <" << tag << ">.";
	sendGuildMail(player, "Guild manager", "@guildmail:namechange_subject", message.str(), false);


	player->info("Clean exit from GuildManagerImplementation::handleGuildNameChangeName(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	//Garbage collection
	myGuildmanager = NULL;
	player = NULL;
	msg.str("");
	myGuild = NULL;
	players = NULL;;
}

void GuildManagerImplementation::handleGuildInformationMembers(Player* player) {
	player->info("Entering GuildManagerImplementation::handleGuildInformationMembers(Player* player)");

	SuiListBox* suiListBox = new SuiListBox(player, 0x7280);

	suiListBox->setPromptTitle("@guild:members_title");
	suiListBox->setPromptText("@guild:members_prompt");
	suiListBox->setCancelButton(true);

	stringstream query;
	ResultSet* guildInfo;

	player->wlock();

	Guild* playerGuild = player->getGuild();
	uint32 playerGuildID = player->getGuildID();

	playerGuild->clearSponsoredMap();

	player->unlock();

	try {
		query << "SELECT firstname, surname "
			<< "FROM characters "
			<< "WHERE guild = " << playerGuildID << " order by firstname;";

		guildInfo = ServerDatabase::instance()->executeQuery(query);

		stringstream entry;

		server->lock();

		while (guildInfo->next()) {
			entry.str("");
			entry << guildInfo->getString(0) << " " << guildInfo->getString(1);
			suiListBox->addMenuItem(entry.str());
			playerGuild->putSponsoredMap(guildInfo->getString(0));
		}

		server->unlock();

	} catch (...) {
		player->info("Error in: void GuildManagerImplementation::handleGuildInformationMembers(Player* player)");
		server->unlock();

		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembers(Player* player)");
		return;
	}

	player->wlock();
	player->addSuiBox(suiListBox);
	player->sendMessage(suiListBox->generateMessage());
	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembers(Player* player)");

	//Garbage collection
	query.str("");
	player = NULL;
	suiListBox = NULL;
	playerGuild = NULL;
	delete guildInfo;
}

void GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();


	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	Guild* playerGuild = player->getGuild();

	string firstname = player->getFirstName();
	string oFirstname = playerGuild->getSponsoredMap(index);
	String::toLower(firstname);
	String::toLower(oFirstname);

	if (firstname == oFirstname) {
		player->sendSystemMessage("You cannot perform actions on yourself.");
		player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	player->setInputBoxReturnBuffer( (playerGuild->getSponsoredMap(index)) );


	SuiListBox* suiListBox = new SuiListBox(player, 0x7281);
	stringstream prompt;
	prompt << "Select an operation from the list you want to perform on " << playerGuild->getSponsoredMap(index) << " and press Ok.";

	suiListBox->setPromptTitle("@guild:member_options_title");
	suiListBox->setPromptText(prompt.str());
	suiListBox->addMenuItem("@guild:title");
	suiListBox->addMenuItem("@guild:kick");
	suiListBox->addMenuItem("@guild:permissions");
	suiListBox->setCancelButton(true);

	player->addSuiBox(suiListBox);
	player->sendMessage(suiListBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildInformationMembersBox(uint32 boxID, Player* player, uint32 cancel, int index)");

	//Garbage collection
	player = NULL;
	playerGuild = NULL;
	suiListBox = NULL;
}

void GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->wlock();
	player->info("Entering GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	string proband = player->getInputBoxReturnBuffer();
	player->setInputBoxReturnBuffer("");

	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	player->unlock();

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
		player->unlock();
		player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");
		return;
	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildMemberOptions(uint32 boxID, Player* player, uint32 cancel, int index)");

	//Garbage collection
	player = NULL;
}

void GuildManagerImplementation::handleRemoveFromGuild(Player* player, string kickee) {
	player->wlock();
	player->info("Entering GuildManagerImplementation::handleRemoveFromGuild(Player* player, string kickee)");


	string pName = player->getFirstName();
	String::toLower(pName);

	string kName = kickee;
	String::toLower(kName);

	if (kName != pName) {
		if ( ! ( ( player->getGuildPermissions() ) & (PlayerImplementation::GUILDKICK) ) ) {
			player->sendSystemMessage("@guild:generic_fail_no_permission");
			player->unlock();
			return;
		}
	}


	Guild* playerGuild = player->getGuild();
	player->setInputBoxReturnBuffer(kickee);


	stringstream prompt;
	SuiMessageBox* suiMessageBox = new SuiMessageBox(player, 0x7283);
	prompt << "Are you sure you want kick " << kickee << " out of the guild?";

	suiMessageBox->setPromptTitle("@guild:kick_title");
	suiMessageBox->setPromptText(prompt.str());
	suiMessageBox->setCancelButton(true);

	player->addSuiBox(suiMessageBox);
	player->sendMessage(suiMessageBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleRemoveFromGuild(Player* player, string kickee)");

	//Garbage collection
	player = NULL;
	playerGuild = NULL;
	suiMessageBox = NULL;
}

void GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel) {
	player->wlock();
	player->info("Entering GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");

	string kickee = player->getInputBoxReturnBuffer();
	player->setInputBoxReturnBuffer("");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	if (cancel || kickee == "") {
		player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
		player->unlock();
		return;
	}

	stringstream kickQuery;
	Guild* playerGuild = player->getGuild();

	if (playerGuild == NULL) {
		player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
		player->unlock();
		return;
	}

	player->unlock();

	//If kickee-player is online, remove from guild
	server->lock();
	Player* kickeePlayer = playerManager->getPlayer(kickee);
	server->unlock();

	if ( kickeePlayer != NULL) {
		kickeePlayer->wlock();

		if (kickeePlayer->isOnline()) {
			kickeePlayer->unlock();
			removeFromGuild(player, kickeePlayer);
		} else
			kickeePlayer->unlock();
	}

	kickeePlayer->wlock();

	if (kickeePlayer->getGuildID() == 0) {
		try {
			kickQuery << "Update characters set guild = 0, guildpermission = 0 where firstname = '" << kickee << "';";
			ServerDatabase::instance()->executeStatement(kickQuery);

		} catch (...) {
			cout << "DB Update Error in: GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)" << endl;

			player->info("DB Update Error in: GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");
			kickeePlayer->unlock();
			return;
		}
	}

	kickeePlayer->unlock();

	player->info("Clean exit from GuildManagerImplementation::execRemoveFromGuild(uint32 boxID, Player* player, uint32 cancel)");

	//Garbage collection
	playerGuild = NULL;
	player = NULL;
	kickeePlayer = NULL;
}

void GuildManagerImplementation::callGuildPermissions(Player* player, string proband) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::callGuildPermissions(Player* player, string proband)");

	if ( ! (player->isGuildLeader())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission");
		player->unlock();
		return;
	}

	stringstream query;
	uint32 permissions;
	ResultSet* memberPerm;

	player->setInputBoxReturnBuffer(proband);

	Player* probandPlayer = playerManager->getPlayer(proband);

	if (probandPlayer == NULL) {
		player->info("Clean exit from GuildManagerImplementation::callGuildPermissions(Player* player, string proband)");
		player->unlock();
		return;
	}

	probandPlayer->wlock();

	if (probandPlayer->isOnline()) {
		//member is online, pulling permissions from member
		permissions = probandPlayer->getGuildPermissions();

	} else {
		//Member is not online, pull permissions from the DB
		try {
			query << "SELECT guildpermission FROM characters where firstname = '" << proband
				<< "' and guild = " << player->getGuildID() << ";";

			memberPerm = ServerDatabase::instance()->executeQuery(query);


		} catch (Exception& e) {
			stringstream msg;
			delete memberPerm;

			msg << "Exception in GuildManager::callGuildPermissions " << e.getMessage();
			cout << msg.str() << endl;

			player->info("Clean exit from GuildManagerImplementation::callGuildPermissions(Player* player, string proband)");

			probandPlayer->unlock();
			player->unlock();
			return;
		}

		if (! memberPerm->next()) {
			probandPlayer->unlock();
			player->unlock();

			player->info("Clean exit from GuildManagerImplementation::callGuildPermissions(Player* player, string proband)");

			delete memberPerm;
			return;
		}

		permissions = memberPerm->getInt(0);
		delete memberPerm;
	}

	SuiListBox* suiListBox = new SuiListBox(player, 0x7282);

	stringstream prompt;
	prompt << "These are the current permissions set for " << proband << ".  "
		<< "Permissions preceded by '+' are currently allowed, and those preceded by '-' are not.  "
		<< "Select a permission and press Ok to toggle it.";

	suiListBox->setPromptTitle("@guild:permissions_title");
	suiListBox->setPromptText(prompt.str());

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

	probandPlayer->unlock();
	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::callGuildPermissions(Player* player, string proband)");

	//Garbage collection
	player = NULL;
	probandPlayer = NULL;
	suiListBox = NULL;
}

void GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	string proband = player->getInputBoxReturnBuffer();
	player->setInputBoxReturnBuffer("");

	if (cancel || index == -1) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
		player->unlock();
		return;
	}

	player->unlock();

	server->lock();
	Player* probandPlayer = playerManager->getPlayer(proband);
	server->unlock();

	if (probandPlayer != NULL) {
		probandPlayer->wlock();

		if (!probandPlayer->isOnline()) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
			probandPlayer->unlock();
			return;
		}

		if (probandPlayer->isGuildLeader()) {
			player->sendSystemMessage("You cannot change the permissions of the guild leader.");
			player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
			probandPlayer->unlock();
			return;
		}

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

	} else {

		//Player is offline, touch the DB
		ResultSet* memberPerm;
		stringstream query;
		query.str("");

		try{
			query << "SELECT guildpermission FROM characters where firstname = '" << proband
				<< "' and guild = " << player->getGuildID() << ";";

			memberPerm = ServerDatabase::instance()->executeQuery(query);


		} catch (Exception& e) {
			stringstream msg;
			msg << "DB Exception in GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index): " << e.getMessage();
			cout << msg;
			delete memberPerm;
			player->info("DB Exception in GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
			return;
		}

		if (! memberPerm->next()) {
			player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");
			return;
		}

		uint32 permissions = memberPerm->getInt(0);
		delete memberPerm;
		query.str("");


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

		query.str("");
	    query << "UPDATE characters set guildpermission = " << permissions
				<< " WHERE character_id = " << probandPlayer->getCharacterID() << ";";

		ServerDatabase::instance()->executeStatement(query);
	    query.str("");

	}

	player->info("Clean exit from GuildManagerImplementation::handleGuildPermissionSelection(uint32 boxID, Player* player, uint32 cancel, int index)");

	callGuildPermissions(player, proband);

	//Garbage collection
	player = NULL;
	probandPlayer = NULL;
}

void GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter) {
	server->lock();

	inviter->info("Entering GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter)");

	Player* declineePlayer = playerManager->getPlayer(declinee);

	if (declineePlayer == NULL) {
		inviter->info("Clean exit from GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter)");
		server->unlock();
		return;
	}

	server->unlock();

	stringstream inmqry;
	ResultSet* decline;


	try {
		//Check previous sponsoring for this character and send out decline mail to that guild leader
		declineePlayer->wlock();

		string toSponsor = declineePlayer->getFirstName();

		inmqry.str("");
		inmqry << "SELECT guilds_sponsoring.guild_id, guilds_sponsoring.guild_name, guilds_sponsoring.sponsored_time, "
			<< "guilds_sponsoring.sponsored_by, guilds_sponsoring.sponsored, characters.firstname "

			<< "FROM guilds_sponsoring "

			<< "Inner Join guilds ON guilds_sponsoring.guild_id = guilds.guild_id "
			<< "Inner Join characters ON guilds.leader = characters.character_id "

			<< "WHERE sponsored = " << declineePlayer->getCharacterID() << ";";

		decline = ServerDatabase::instance()->executeQuery(inmqry);

		declineePlayer->unlock();

		if (decline->next()) {
			string declineGuild = decline->getString(1);
			string declineGuildLeader = decline->getString(5);

			if ( (decline->getInt(0)) == inviteGuild ) {
				ErrorMessage* errMsg = new ErrorMessage("@base_player:swg",
						"The player has been already sponsored for membership in " + declineGuild + ".", 0);
				inviter->sendMessage(errMsg);

				ErrorMessage* errMsg2 = new ErrorMessage("@base_player:swg",
						"You have been already sponsored for membership in " + declineGuild + ".", 0);
				declineePlayer->sendMessage(errMsg2);

				delete decline;
				inviter->info("Clean exit from GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter)");
				return;
			}

			stringstream message;
			message << toSponsor << " has declined your sponsorship for <" << declineGuild << ">.";
			sendMailGuildLeader(inviter, "Guildmanager", (decline->getInt(0)), "Guild Sponsorship declined", message.str());

		}
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		declineePlayer->unlock();

		inviter->info("DB Exception in GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter)");
		delete decline;
		return;
	}

	delete decline;

	stringstream deleteQuery;
	try {

		declineePlayer->wlock();
		deleteQuery << "DELETE from guilds_sponsoring where sponsored = " << declineePlayer->getCharacterID() << ";";
		ServerDatabase::instance()->executeStatement(deleteQuery);
		declineePlayer->unlock();

	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
		declineePlayer->unlock();
		inviter->info("DB Exception in GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter)");
		return;
	}


	deleteQuery.str("");
	inmqry.str("");

	inviter->info("Clean exit from GuildManagerImplementation::declineSponsoring(string declinee,uint32 inviteGuild, Player* inviter)");

	//Garbage collection
	inviter = NULL;
	declineePlayer = NULL;
}


void GuildManagerImplementation::handleGuildInfo(Player* player) {
	ResultSet* guildInfo;
	stringstream query;
	query.str("");

	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildInfo(Player* player)");

	SuiListBox* guildInfoBox = new SuiListBox(player, 0x7276);

	guildInfoBox->setPromptTitle("@guild:info_title");
	guildInfoBox->setPromptText("@guild:menu_info");

	try {
		query << "SELECT guilds.guild_tag, guilds.guild_name, "
			<< "(SELECT concat(characters.firstname,' ',characters.surname) "
			<< "FROM characters Inner Join guilds ON guilds.leader = characters.character_id) as leader "
			<< "FROM guilds Inner Join characters ON guilds.guild_id = characters.guild "
			<< "WHERE guilds.guild_id = " << player->getGuildID() << ";";

		guildInfo = ServerDatabase::instance()->executeQuery(query);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";

		player->info("DB Exception in GuildManagerImplementation::handleGuildInfo(Player* player)");
		player->unlock();
		return;
	}

	if (guildInfo->next()) {
		int members = guildInfo->size();

		stringstream totalMembers;
		stringstream guildtag;
		stringstream guildname;
		stringstream guildleader;

		totalMembers << members;
		guildtag << "Abbreviation: <" << guildInfo->getString(0) << ">";
		guildname << "Name: " << guildInfo->getString(1) << "";
		guildleader << "Leader: " << guildInfo->getString(2);


		guildInfoBox->addMenuItem(guildtag.str());
		guildInfoBox->addMenuItem(guildname.str());
		guildInfoBox->addMenuItem(guildleader.str());
		guildInfoBox->addMenuItem(totalMembers.str());

	}

	player->addSuiBox(guildInfoBox);
	player->sendMessage(guildInfoBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildInfo(Player* player)");

	//Garbage collection
	query.str("");
	
	player = NULL;
	guildInfoBox = NULL;
	
	delete guildInfo;
}

void GuildManagerImplementation::handleGuildSponsoring(Player* player) {
	ResultSet* sponsoredList;
	stringstream query;
	query.str("");

	player->wlock();

	if ( ! ( ( player->getGuildPermissions() ) & (PlayerImplementation::GUILDACCEPT) ) ) {
		player->sendSystemMessage("@guild:generic_fail_no_permission");
		player->unlock();
		return;
	}

	player->info("Entering GuildManagerImplementation::handleGuildSponsoring(Player* player)");

	player->setInputBoxReturnBuffer("");

	SuiListBox* sponsoredBox = new SuiListBox(player, 0x7274);

	sponsoredBox->setPromptTitle("Sponsored for membership: " + player->getGuildName());
	sponsoredBox->setPromptText("@guild:sponsored_prompt");
	sponsoredBox->setCancelButton(true);

	string sponsoredName;

	Guild* playerGuild = player->getGuild();
	playerGuild->clearSponsoredMap();

	try {
		query << "SELECT guilds_sponsoring.sponsored, characters.firstname, characters.surname "
			<< "FROM guilds_sponsoring "
			<< "Inner Join characters ON guilds_sponsoring.sponsored = characters.character_id "
			<< "where guilds_sponsoring.guild_id= " << player->getGuildID() << " order by characters.firstname;";

		sponsoredList= ServerDatabase::instance()->executeQuery(query);

		while (sponsoredList->next()) {
			sponsoredName = sponsoredList->getString(1);
			sponsoredBox->addMenuItem(sponsoredName);
			playerGuild->putSponsoredMap(sponsoredName);
		}

	} catch (...) {
		cout << "Error in: void RadialManager::handleGuildSponsored(Player* player)" << endl;
		player->info("Error in: GuildManagerImplementation::handleGuildSponsoring(Player* player)");
		player->unlock();
		return;
	}

	player->addSuiBox(sponsoredBox);
	player->sendMessage(sponsoredBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildSponsoring(Player* player)");

	//Garbage collection
	query.str("");
	player = NULL;
	delete sponsoredList;
	sponsoredBox = NULL;
	playerGuild = NULL;
}


void GuildManagerImplementation::handleGuildRenaming(Player* player) {
	ResultSet* guildStamp;

	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildRenaming(Player* player)");

	stringstream query;
	query << "SELECT last_name_change FROM guilds where guild_id =" << player->getGuildID() << ";";
	guildStamp = ServerDatabase::instance()->executeQuery(query);

	if (guildStamp->next()) {
		Time systemTime;
		stringstream helper;
		uint64 lastchange;

		helper << guildStamp->getString(0);
		helper >> lastchange;
		helper.str("");

		uint64 currentTime = systemTime.getMiliTime() / 1000;

		if (currentTime < lastchange+864000) { //1 Day (24 h)
			player->sendSystemMessage("Your are allowed to change your guild's name only every 24 hours.");
			player->info("Clean exit from GuildManagerImplementation::handleGuildRenaming(Player* player)");

			player->unlock();
			return;
		}
	}

	SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7278, 0);

	suiInpBox->setPromptTitle("@guild:namechange_abbrev_title");
	suiInpBox->setPromptText("@guild:namechange_abbrev_title");
	suiInpBox->setCancelButton(true);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildRenaming(Player* player)");

	//Garbage collection
	delete guildStamp;
	player = NULL;
	suiInpBox = NULL;
	query.str("");
}

void GuildManagerImplementation::handleGuildTransferLeader(Player* player) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

	Guild* playerGuild = player->getGuild();
	if (playerGuild == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

		player->unlock();
		return;
	}

	server->lock();
	if ( !player->isGuildLeader() ) {
		server->unlock();

		player->sendSystemMessage("You are not guild leader");
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

		player->unlock();
		return;
	}
	server->unlock();



	SuiInputBox* suiInpBox = new SuiInputBox(player, 0x7284, 0);

	suiInpBox->setPromptTitle("@guild:make_leader_t");
	suiInpBox->setPromptText("@guild:make_leader_d");
	suiInpBox->setCancelButton(true);

	player->addSuiBox(suiInpBox);
	player->sendMessage(suiInpBox->generateMessage());

	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeader(Player* player)");

	//Garbage collection
	player = NULL;
	playerGuild = NULL;
	suiInpBox = NULL;
}

void GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	if (cancel) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

		player->unlock();
		return;
	}

	string proband = returnString;

	if (proband == "") {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

		player->unlock();
		return;
	}

	string name = player->getFirstName();

	server->lock();

	string newLeaderName = "";
	Player* otherPlayer;

	for (int i = 0; i < player->inRangeObjectCount(); ++i) {
		SceneObject* obj = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

		if (obj->isPlayer()) {
			otherPlayer = (Player*) obj;

			string otherName = otherPlayer->getFirstName();
			String::toLower(otherName);

			if (otherName != name && otherName == proband && (player->isInRange(otherPlayer, 8))) {
				newLeaderName = otherName;
				break;
			}
		}
	}


	server->unlock();

	if (newLeaderName == "") {
		player->sendSystemMessage("That person is not loaded or is too far away.");
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

		player->unlock();
		return;
	}

	otherPlayer->wlock();

	if (otherPlayer->getGuildID() != player->getGuildID()) {
		player->sendSystemMessage("Unable to find a member of the PA with that name.");
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

		player->unlock();
		otherPlayer->unlock();
		return;
	}

	//ToDo: If housing is in: Check free lots for PA Hall Transfer

	SuiMessageBox* oSui = new SuiMessageBox(otherPlayer, 0x7285);
	oSui->setPromptTitle("@guild:make_leader_t");
	oSui->setPromptText("@guild:make_leader_p");

	oSui->setCancelButton(true);

	otherPlayer->addSuiBox(oSui);
	otherPlayer->sendMessage(oSui->generateMessage());

	otherPlayer->setInputBoxReturnBuffer(player->getFirstName());

	otherPlayer->unlock();
	player->unlock();

	player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderBox(uint32 boxID, Player* player, uint32 cancel, string returnString)");

	//Garbage collection
	otherPlayer = NULL;
	oSui = NULL;
	player = NULL;
}

void GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel) {
	player->wlock();

	player->info("Entering GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

	if (!player->hasSuiBox(boxID)) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");
		player->unlock();
		return;
	}

	SuiBox* sui = player->getSuiBox(boxID);
	player->removeSuiBox(boxID);
	sui->finalize();

	string oldLeader = player->getInputBoxReturnBuffer();

	server->lock();
	Player* olPlayer = playerManager->getPlayer(oldLeader);

	if (olPlayer == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

		player->unlock();
		return;
	}

	Guild* guild = player->getGuild();
	server->unlock();

	if (guild == NULL) {
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

		player->unlock();
		return;
	}


	if (cancel) {
		ErrorMessage* errMsg = new ErrorMessage("@guild:ml_rejected", "", 0);
		olPlayer->sendMessage(errMsg);
		player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

		player->unlock();
		errMsg = NULL;
		return;
	}


	olPlayer->wlock();

	player->setGuildPermissions(255);
	player->setGuildLeader(true);

	guild->setGuildLeader(player->getCharacterID());

	olPlayer->setGuildPermissions(0);
	olPlayer->setGuildLeader(false);

	stringstream query;
    query << "UPDATE characters set guildpermission = 255 "
			<< "WHERE character_id = " << player->getCharacterID() << ";";

	ServerDatabase::instance()->executeStatement(query);


	query.str("");
    query << "UPDATE characters set guildpermission = 0 "
			<< "WHERE character_id = " << olPlayer->getCharacterID() << ";";

	ServerDatabase::instance()->executeStatement(query);


	query.str("");
	query << "UPDATE guilds set leader = " << player->getCharacterID()
			<< " WHERE guild_id = " << player->getGuildID() << ";";

	ServerDatabase::instance()->executeStatement(query);

	stringstream message;
	message << player->getFirstName() << " is the new guild leader.";

	player->unlock();
	olPlayer->unlock();

	sendGuildMail(player, "Guild manager", "@guildmail:leaderchange_subject", message.str(), false);

	player->info("Clean exit from GuildManagerImplementation::handleGuildTransferLeaderVerifyBox(uint32 boxID, Player* player, uint32 cancel)");

	//Garbage collection
	player = NULL;
	olPlayer = NULL;
	guild = NULL;
}
