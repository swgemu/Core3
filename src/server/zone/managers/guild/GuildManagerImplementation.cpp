/*
 * GuildManagerImplementation.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#include "GuildManager.h"
#include "server/chat/ChatManager.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/guild/GuildMemberList.h"
#include "server/zone/objects/guild/GuildMemberInfo.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/guild/GuildObjectMessage3.h"
#include "server/zone/packets/guild/GuildObjectMessage6.h"
#include "server/zone/packets/guild/GuildObjectDeltaMessage3.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

void GuildManagerImplementation::loadGuilds() {
	Locker _lock(_this);

	ObjectDatabase* guildsDatabase = ObjectDatabaseManager::instance()->loadDatabase("guilds", true);

	if (guildsDatabase == NULL) {
		error("Could not load the guilds database.");
		return;
	}

	try {
		info("Loading guilds from database.", true);
		ObjectDatabaseIterator iterator(guildsDatabase);

		uint64 objectID = 0;

		while (iterator.getNextKey(objectID)) {
			ManagedReference<SceneObject*> object = server->getObject(objectID);

			if (object == NULL || !object->isGuildObject())
				continue;

			GuildObject* guild = (GuildObject*) object.get();
			guildList.add(guild->getGuildKey(), guild);

			//Add sponsored player to the sponsoredPlayers VectorMap.
			for (int i = 0; i < guild->getSponsoredPlayerCount(); ++i) {
				uint64 playerID = guild->getSponsoredPlayer(i);

				if (sponsoredPlayers.contains(playerID))
					removeSponsoredPlayer(playerID);

				addSponsoredPlayer(playerID, guild);
			}
		}

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Loading Guild, exception: " << e.getMessage();
		error(err);
		return;
	} catch (...) {
		throw Exception("problem in GuildManagerImplementation::loadGuilds()");
	}

	info(guildList.size() + " guilds loaded.", true);
}

void GuildManagerImplementation::sendGuildCreateNameTo(PlayerCreature* player, GuildTerminal* terminal) {
	if (player->isInGuild()) {
		player->sendSystemMessage("@guild:create_fail_in_guild"); //You cannot create a guild while already in a guild.
		return;
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_NAME);
	inputBox->setPromptTitle("@guild:create_name_title"); //Guild Name
	inputBox->setPromptText("@guild:create_name_prompt");
	inputBox->setMaxInputSize(24);
	inputBox->setUsingObject(terminal);

	player->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildName(PlayerCreature* player, const String& guildName) {
	if (guildName.length() < 1 || guildName.length() > 25) {
		player->sendSystemMessage("@guild:create_fail_name_bad_length"); //Guild names must be 1-25 characters in length.
		return false;
	}

	NameManager* nameManager = processor->getNameManager();

	if (!nameManager->validateName(guildName, 0)) {
		player->sendSystemMessage("@guild:create_fail_name_in_use"); //That guild name is already in use.
		return false;
	}

	if (guildNameExists(guildName)) {
		player->sendSystemMessage("@guild:create_fail_name_now_allowed"); //That guild name is not allowed.
		return false;
	}

	return true;
}

bool GuildManagerImplementation::guildNameExists(const String& guildName) {
	Locker _lock(_this);

	for (int i = 0; i < guildList.size(); ++i) {
		ManagedReference<GuildObject*> guild = guildList.get(guildList.getKeyAt(i));

		if (guild == NULL)
			continue;

		if (guild->getGuildName() == guildName)
			return true;
	}

	return false;
}

bool GuildManagerImplementation::guildAbbrevExists(const String& guildAbbrev) {
	Locker _lock(_this);

	for (int i = 0; i < guildList.size(); ++i) {
		ManagedReference<GuildObject*> guild = guildList.get(guildList.getKeyAt(i));

		if (guild == NULL)
			continue;

		if (guild->getGuildAbbrev() == guildAbbrev)
			return true;
	}

	return false;
}

void GuildManagerImplementation::sendGuildCreateAbbrevTo(PlayerCreature* player, GuildTerminal* terminal) {
	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_ABBREV);
	inputBox->setPromptTitle("@guild:create_abbrev_title"); //Guild Abbreviation
	inputBox->setPromptText("@guild:create_abbrev_prompt");
	inputBox->setMaxInputSize(4);
	inputBox->setUsingObject(terminal);

	player->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildAbbrev(PlayerCreature* player, const String& guildAbbrev) {
	if (guildAbbrev.length() < 1 || guildAbbrev.length() > 5) {
		player->sendSystemMessage("@guild:create_fail_abbrev_bad_length"); //Guild abbreviations must be 1-5 characters in length.
		return false;
	}

	NameManager* nameManager = processor->getNameManager();

	if (!nameManager->validateName(guildAbbrev, 0)) {
		player->sendSystemMessage("@guild:create_fail_abbrev_in_use"); //That guild abbreviation is already in use.
		return false;
	}

	if (guildAbbrevExists(guildAbbrev)) {
		player->sendSystemMessage("@guild:create_fail_abbrev_now_allowed"); //That guild abbreviation is not allowed.
		return false;
	}

	return true;
}

void GuildManagerImplementation::sendGuildInformationTo(PlayerCreature* player, GuildTerminal* guildTerminal) {
	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL)
		return;

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, 0x00);
	suiBox->setPromptTitle("@guild:info_title"); //Guild Information
	suiBox->setUsingObject(guildTerminal);

	ManagedReference<SceneObject*> guildLeader = server->getObject(guild->getGuildLeaderID());

	StringBuffer guildInfo;
	guildInfo << "Guild Name: " << guild->getGuildName() << "\n";
	guildInfo << "Abbreviation: " << guild->getGuildAbbrev() << "\n";

	if (guildLeader != NULL && guildLeader->isPlayerCreature())
		guildInfo << "Guild Leader: " << guildLeader->getObjectName()->getDisplayedName() << "\n";
	else
		guildInfo << "Guild Leader: None\n";

	guildInfo << "Members: " << guild->getTotalMembers() << "\n";

	suiBox->setPromptText(guildInfo.toString());
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildDisbandConfirmTo(PlayerCreature* player, GuildTerminal* guildTerminal) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::GUILD_DISBAND);
	suiBox->setPromptTitle("@guild:disband_title"); //Disband Guild
	suiBox->setPromptText("@guild:disband_prompt"); //Are you sure you wish to disband your guild?
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	player->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildMemberOptionsTo(PlayerCreature* player, GuildTerminal* guildTerminal, uint64 memberID) {
	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL)
		return;

	GuildMemberList* memberList = guild->getGuildMemberList();

	if (memberList == NULL)
		return;

	GuildMemberInfo* gmi = &memberList->get(player->getObjectID());

	if (gmi == NULL)
		return;

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_OPTIONS);
	suiBox->setPromptTitle("@guild:members_options_title"); //Guild Member Options
	suiBox->setPromptText("@guild:members_options_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	//Guild leader's don't have this option!
	if (guild->getGuildLeaderID() != player->getObjectID())
		suiBox->addMenuItem("@guild:allegiance", memberID); //Set Allegiance

	suiBox->addMenuItem("@guild:kick", memberID); //Kick
	suiBox->addMenuItem("@guild:title", memberID); //Set Title
	suiBox->addMenuItem("@guild:permissions", memberID); //Change Permissions

	player->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildMemberListTo(PlayerCreature* player, GuildTerminal* guildTerminal) {
	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL)
		return;

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_LIST);
	suiBox->setPromptTitle("@guild:members_title"); //Guild Members
	suiBox->setPromptText("@guild:members_prompt");
	suiBox->setUsingObject(guildTerminal);

	Locker _lock(guild);

	GuildMemberList* memberList = guild->getGuildMemberList();

	for (int i = 0; i < memberList->size(); ++i) {
		GuildMemberInfo* gmi = &memberList->get(i);

		if (gmi == NULL)
			continue;

		uint64 playerID = gmi->getPlayerID();
		ManagedReference<SceneObject*> obj = server->getObject(playerID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		PlayerCreature* member = (PlayerCreature*) obj.get();
		suiBox->addMenuItem(member->getObjectName()->getDisplayedName(), playerID);
	}

	suiBox->setCancelButton(true, "@cancel");
	player->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSponsoredOptionsTo(PlayerCreature* player, uint64 playerID, GuildTerminal* guildTerminal) {
	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_SPONSORED_OPTIONS);
	suiBox->setPromptTitle("@guild:sponsored_options_title"); //Sponsored For Membership
	suiBox->setPromptText("@guild:sponsored_options_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	suiBox->addMenuItem("@guild:accept", playerID); //Accept
	suiBox->addMenuItem("@guild:decline", 0); //Decline

	player->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSponsoredListTo(PlayerCreature* player, GuildTerminal* guildTerminal) {
	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_SPONSORED_LIST);
	suiBox->setPromptTitle("@guild:sponsored_title"); //Sponsored for Membership
	suiBox->setPromptText("@guild:sponsored_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	for (int i = 0; i < guild->getSponsoredPlayerCount(); ++i) {
		uint64 playerID = guild->getSponsoredPlayer(i);

		ManagedReference<SceneObject*> obj = server->getObject(playerID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		PlayerCreature* sponsoredPlayer = (PlayerCreature*) obj.get();

		suiBox->addMenuItem(sponsoredPlayer->getObjectName()->getDisplayedName(), playerID);
	}

	player->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSponsorTo(PlayerCreature* player, GuildTerminal* guildTerminal) {
	ManagedReference<SuiInputBox*> suiBox = new SuiInputBox(player, SuiWindowType::GUILD_SPONSOR);
	suiBox->setPromptTitle("@guild:sponsor_title"); //Sponsor for Membership
	suiBox->setPromptText("@guild:sponsor_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	player->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendBaselinesTo(PlayerCreature* player) {
	SceneObjectCreateMessage* create = new SceneObjectCreateMessage(_this->_getObjectID(), 0x7D40E2E6);
	player->sendMessage(create);

	Locker _lock(_this);

	GuildObjectMessage3* gild3 = new GuildObjectMessage3(&guildList, _this->_getObjectID());
	player->sendMessage(gild3);

	GuildObjectMessage6* gild6 = new GuildObjectMessage6(_this->_getObjectID());
	player->sendMessage(gild6);

	SceneObjectCloseMessage* close = new SceneObjectCloseMessage(_this->_getObjectID());
	player->sendMessage(close);
}

GuildObject* GuildManagerImplementation::createGuild(PlayerCreature* player, GuildTerminal* terminal, const String& guildName, const String& guildAbbrev) {
	Locker _lock(_this);

	uint64 playerID = player->getObjectID();

	if (isCreatingGuild(playerID))
		removePendingGuild(playerID);

	ManagedReference<GuildObject*> guild = (GuildObject*) ObjectManager::instance()->createObject(0xD6888614, 0, "guilds"); //object/guild/guild_object.iff
	guild->setGuildLeaderID(playerID);
	guild->setGuildID(Long::hashCode(guild->getObjectID()));
	guild->setGuildName(guildName);
	guild->setGuildAbbrev(guildAbbrev);
	guild->addMember(playerID);

	//Handle setting of the guild leader.
	GuildMemberInfo* gmi = guild->getMember(playerID);
	gmi->setDeclaredAllegiance(playerID);
	gmi->setPermissions(GuildObject::PERMISSION_ALL);

	player->setGuildObject(guild);
	terminal->setGuildObject(guild);

	GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this->_getObjectID());
	gildd3->startUpdate(0x04);
	guildList.add(guild->getGuildKey(), guild, gildd3);
	gildd3->close();

	//Send the delta to everyone currently online!
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	chatManager->broadcastMessage(gildd3);

	CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(player);
	creod6->updateGuildID();
	creod6->close();
	player->broadcastMessage(creod6, true);

	info("Guild " + guildName + " <" + guildAbbrev + "> created.", true);

	return guild;
}

bool GuildManagerImplementation::disbandGuild(PlayerCreature* player, GuildTerminal* guildTerminal) {
	Locker _lock(_this);

	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	guildTerminal->setGuildObject(NULL);

	if (guild == NULL)
		return false;

	//Remove all sponsored members from the sponsoredPlayers vectormap
	for (int i = 0; i < guild->getSponsoredPlayerCount(); ++i) {
		uint64 playerID = guild->getSponsoredPlayer(i);
		sponsoredPlayers.drop(playerID);
	}

	//We have to remove the guild tag from everyone currently online in this guild!
	GuildMemberList* memberList = guild->getGuildMemberList();

	if (memberList == NULL)
		return false;

	//TODO: This could probably be moved to the GuildObject destructor!
	for (int i = 0; i < memberList->size(); ++i) {
		GuildMemberInfo* gmi = &memberList->get(i);

		if (gmi == NULL)
			continue;

		ManagedReference<SceneObject*> obj = server->getObject(gmi->getPlayerID());

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		PlayerCreature* member = (PlayerCreature*) obj.get();

		member->setGuildObject(NULL);

		if (!member->isOnline())
			continue;

		CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(member);
		creod6->updateGuildID();
		creod6->close();
		member->broadcastMessage(creod6, true);
	}

	GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this->_getObjectID());
	gildd3->startUpdate(0x04);
	guildList.drop(guild->getGuildKey(), gildd3);
	gildd3->close();

	//Send the delta to everyone currently online!
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	chatManager->broadcastMessage(gildd3);

	info("Guild " + guild->getGuildName() + " <" + guild->getGuildAbbrev() + "> disbanded.", true);

	return true;
}

void GuildManagerImplementation::sponsorPlayer(PlayerCreature* player, GuildTerminal* guildTerminal, const String& playerName) {
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL)
		return;

	if (guild->getTotalMembers() >= maximumMembers) {
		player->sendSystemMessage("@guild:sponsor_fail_full"); //No more members may be sponsored, as the guild is already full.
		return;
	}

	ManagedReference<PlayerCreature*> target = playerManager->getPlayer(playerName);

	if (target == NULL) {
		player->sendSystemMessage("@guild:sponsor_not_found"); //The specified person to sponsor could not be found nearby.
		return;
	}

	Locker _lock(target, player);

	if (!target->isOnline() || !player->isInRange(target, 32)) {
		player->sendSystemMessage("@guild:sponsor_not_found"); //The specified person to sponsor could not be found nearby.
		return;
	}

	if (target->isInGuild()) {
		ParameterizedStringId params;
		params.setStringId("@guild:sponsor_already_in_guild"); //%TU is already in a guild.
		params.setTU(target);

		player->sendSystemMessage(params);
		return;
	}

	//Here we need to send a confirmation box to the target player.
	sendGuildSponsorVerifyTo(player, target);
}

void GuildManagerImplementation::sendGuildSponsorVerifyTo(PlayerCreature* player, PlayerCreature* target) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_SPONSOR_VERIFY);
	suiBox->setPromptTitle("@guild:sponsor_verify_title"); //Sponsored For Guild Membership
	suiBox->setPromptText("@guild:sponsor_verify_prompt");
	suiBox->setUsingObject(player);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	target->addSuiBox(suiBox);
	target->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::acceptSponsorshipRequest(PlayerCreature* player, PlayerCreature* target) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL)
		return;

	Locker _lock(target, player);

	ParameterizedStringId params;
	params.setStringId("@guild:sponsor_self"); //You sponsor %TU for membership in %TT.
	params.setTU(target->getObjectID());
	params.setTT(guild->getGuildName());

	player->sendSystemMessage(params);

	params.clear();

	params.setStringId("@guild:sponsor_accept"); //%TU has accepted your sponsorship
	params.setTU(target->getObjectID());

	target->sendSystemMessage(params);

	addSponsoredPlayer(target->getObjectID(), guild);
	guild->addSponsoredPlayer(target->getObjectID());
}

void GuildManagerImplementation::acceptSponsoredPlayer(PlayerCreature* player, uint64 targetID) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SceneObject*> obj = server->getObject(targetID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	PlayerCreature* target = (PlayerCreature*) obj.get();

	Locker _lock(target, player);

	if (target->isInGuild()) {
		player->sendSystemMessage("@guild:sponsor_already_in_guild"); //%TU is already in a guild.
		return;
	}

	guild->addMember(targetID);
	target->setGuildObject(guild);

	ParameterizedStringId params;
	params.setStringId("@guild:accept_self"); //You accept %TU for membership in %TT.
	params.setTU(target->getObjectName()->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	if (target->isOnline()) {
		params.setStringId("@guild:accept_target"); // %TU has accepted you for membership in %TT.
		params.setTU(player->getObjectID());
		target->sendSystemMessage(params);

		CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(target);
		creod6->updateGuildID();
		creod6->close();
		target->broadcastMessage(creod6, true);
	}

	//TODO: Guild emails
	//@guildmail:accept_text %TU has accepted %TT into the guild as a member.
	//@guildmail:accept_target_text %TU has accepted you into %TT as a member.
}

void GuildManagerImplementation::sendGuildKickPromptTo(PlayerCreature* player, PlayerCreature* target) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_MEMBER_REMOVE);
	suiBox->setPromptTitle("@guild:kick_title"); //Kick From Guild
	suiBox->setPromptText("@guild:kick_prompt"); //Are you sure you want to kick %TU out of the guild?
	suiBox->setUsingObject(target);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	target->addSuiBox(suiBox);
	target->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSetTitleTo(PlayerCreature* player, PlayerCreature* target) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_MEMBER_TITLE);
	suiBox->setPromptTitle("@guild:title_title"); //Set Title
	suiBox->setPromptText("@guild:title_prompt"); //Enter a title to set for %TU.
	suiBox->setUsingObject(target);
	suiBox->setCancelButton(true, "@cancel");

	target->addSuiBox(suiBox);
	target->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::kickMember(PlayerCreature* player, PlayerCreature* target) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasKickPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	uint64 targetID = target->getObjectID();

	if (!guild->hasMember(targetID)) {
		//Isn't in this guild...
		return;
	}

	guild->removeMember(targetID);

	Locker clocker(target, player);

	target->setGuildObject(NULL);

	ParameterizedStringId params;
	params.setStringId("@guild:kick_self"); //You remove %TU from %TT.
	params.setTU(target->getObjectName()->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	if (target->isOnline()) {
		params.setStringId("@guild:kick_target"); //%TU has removed you from %TT.
		params.setTU(player->getObjectName()->getDisplayedName());
		target->sendSystemMessage(params);

		CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(target);
		creod6->updateGuildID();
		creod6->close();
		target->broadcastMessage(creod6, true);
	}

	//TODO: Send out guild mails
}

void GuildManagerImplementation::setMemberTitle(PlayerCreature* player, uint64 targetID, GuildTerminal* guildTerminal) {

}

void GuildManagerImplementation::setAllegianceTo(PlayerCreature* player, uint64 targetID, GuildTerminal* guildTerminal) {

}

void GuildManagerImplementation::sendMemberPermissionsTo(PlayerCreature* player, PlayerCreature* target) {

}
