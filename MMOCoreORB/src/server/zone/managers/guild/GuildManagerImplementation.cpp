/*
 * GuildManagerImplementation.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#include "GuildManager.h"

#include "server/chat/ChatManager.h"
#include "server/chat/room/ChatRoom.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/guild/GuildMemberList.h"
#include "server/zone/objects/guild/GuildMemberInfo.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

#include "server/zone/objects/guild/sui/GuildCreateNameResponseSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildCreateAbbrevResponseSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildDisbandSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildMemberListSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildMemberOptionsSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildMemberPermissionsResponseSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildMemberRemoveSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildTitleResponseSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildSponsorSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildSponsorVerifySuiCallback.h"
#include "server/zone/objects/guild/sui/GuildSponsoredListSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildSponsoredOptionsSuiCallback.h"

#include "server/zone/objects/creature/commands/sui/ListGuildsResponseSuiCallback.h"

#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/guild/GuildObjectMessage3.h"
#include "server/zone/packets/guild/GuildObjectMessage6.h"
#include "server/zone/packets/guild/GuildObjectDeltaMessage3.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

void GuildManagerImplementation::loadGuilds() {
	Locker _lock(_this);

	ObjectDatabase* guildsDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("guilds", true);

	if (guildsDatabase == NULL) {
		error("Could not load the guilds database.");
		return;
	}

	ManagedReference<ChatRoom*> guildRoom = chatManager->getGuildRoom();

	try {
		info("Loading guilds from database.", true);
		ObjectDatabaseIterator iterator(guildsDatabase);

		uint64 objectID = 0;

		while (iterator.getNextKey(objectID)) {
			ManagedReference<SceneObject*> object = server->getObject(objectID);

			if (object == NULL || !object->isGuildObject())
				continue;

			GuildObject* guild = cast<GuildObject*>( object.get());
			guildList.add(guild->getGuildKey(), guild);

			//Add sponsored player to the sponsoredPlayers VectorMap.
			for (int i = 0; i < guild->getSponsoredPlayerCount(); ++i) {
				uint64 playerID = guild->getSponsoredPlayer(i);

				if (sponsoredPlayers.contains(playerID))
					removeSponsoredPlayer(playerID);

				addSponsoredPlayer(playerID, guild);
			}

			//Recreate the guild chat rooms on load
			createGuildChannels(guild);
		}

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Loading Guild, exception: " << e.getMessage();
		error(err);
		return;
	}

	info(String::valueOf(guildList.size()) + " guilds loaded.", true);
}

void GuildManagerImplementation::sendGuildCreateNameTo(CreatureObject* player, GuildTerminal* terminal) {
	if (player->isInGuild()) {
		player->sendSystemMessage("@guild:create_fail_in_guild"); //You cannot create a guild while already in a guild.
		return;
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_NAME);
	inputBox->setCallback(new GuildCreateNameResponseSuiCallback(server));
	inputBox->setPromptTitle("@guild:create_name_title"); //Guild Name
	inputBox->setPromptText("@guild:create_name_prompt");
	inputBox->setMaxInputSize(24);
	inputBox->setUsingObject(terminal);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildName(CreatureObject* player, const String& guildName) {
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
		player->sendSystemMessage("@guild:create_fail_name_not_allowed"); //That guild name is not allowed.
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

void GuildManagerImplementation::sendGuildCreateAbbrevTo(CreatureObject* player, GuildTerminal* terminal) {
	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_ABBREV);
	inputBox->setCallback(new GuildCreateAbbrevResponseSuiCallback(server));
	inputBox->setPromptTitle("@guild:create_abbrev_title"); //Guild Abbreviation
	inputBox->setPromptText("@guild:create_abbrev_prompt");
	inputBox->setMaxInputSize(4);
	inputBox->setUsingObject(terminal);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildAbbrev(CreatureObject* player, const String& guildAbbrev) {
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
		player->sendSystemMessage("@guild:create_fail_abbrev_not_allowed"); //That guild abbreviation is not allowed.
		return false;
	}

	return true;
}

void GuildManagerImplementation::sendGuildInformationTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, 0x00);
	suiBox->setPromptTitle("@guild:info_title"); //Guild Information
	suiBox->setUsingObject(guildTerminal);

	ManagedReference<SceneObject*> guildLeader = server->getObject(guild->getGuildLeaderID());

	StringBuffer guildInfo;
	guildInfo << "Guild Name: " << guild->getGuildName() << "\n";
	guildInfo << "Abbreviation: " << guild->getGuildAbbrev() << "\n";

	if (guildLeader != NULL && guildLeader->isPlayerCreature())
		guildInfo << "Guild Leader: " << guildLeader->getDisplayedName() << "\n";
	else
		guildInfo << "Guild Leader: None\n";

	guildInfo << "Members: " << guild->getTotalMembers() << "\n";

	suiBox->setPromptText(guildInfo.toString());
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildDisbandConfirmTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	if (!guild->hasDisbandPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::GUILD_DISBAND);
	suiBox->setCallback(new GuildDisbandSuiCallback(server));
	suiBox->setPromptTitle("@guild:disband_title"); //Disband Guild
	suiBox->setPromptText("@guild:disband_prompt"); //Are you sure you wish to disband your guild?
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildMemberOptionsTo(CreatureObject* player, GuildObject* guild, uint64 memberID, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	GuildMemberList* memberList = guild->getGuildMemberList();

	if (memberList == NULL)
		return;

	if (!memberList->contains(player->getObjectID()))
		return;

	GuildMemberInfo* gmi = &memberList->get(player->getObjectID());

	if (gmi == NULL)
		return;

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_OPTIONS);
	suiBox->setCallback(new GuildMemberOptionsSuiCallback(server));
	suiBox->setPromptTitle("@guild:member_options_title"); //Guild Member Options
	suiBox->setPromptText("@guild:member_options_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	//Guild leader's don't have this option!
	if (guild->getGuildLeaderID() != player->getObjectID())
		suiBox->addMenuItem("@guild:allegiance", memberID); //Set Allegiance

	suiBox->addMenuItem("@guild:kick", memberID); //Kick
	suiBox->addMenuItem("@guild:title", memberID); //Set Title
	suiBox->addMenuItem("@guild:permissions", memberID); //Change Permissions

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildMemberListTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_LIST);
	suiBox->setCallback(new GuildMemberListSuiCallback(server));
	suiBox->setPromptTitle("@guild:members_title"); //Guild Members
	suiBox->setPromptText("@guild:members_prompt");
	suiBox->setUsingObject(guildTerminal);

	GuildMemberList* memberList = guild->getGuildMemberList();

	for (int i = 0; i < memberList->size(); ++i) {
		GuildMemberInfo* gmi = &memberList->get(i);

		if (gmi == NULL)
			continue;

		uint64 playerID = gmi->getPlayerID();
		ManagedReference<SceneObject*> obj = server->getObject(playerID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* member = cast<CreatureObject*>( obj.get());
		suiBox->addMenuItem(member->getDisplayedName(), playerID);
	}

	suiBox->setCancelButton(true, "@cancel");
	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSponsoredOptionsTo(CreatureObject* player, GuildObject* guild, uint64 playerID, GuildTerminal* guildTerminal) {
	if (guild == NULL) {
		return;
	}

	Locker _lock(guild);

	if (!guild->hasAcceptPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_SPONSORED_OPTIONS);
	suiBox->setCallback(new GuildSponsoredOptionsSuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsored_options_title"); //Sponsored For Membership
	suiBox->setPromptText("@guild:sponsored_options_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	suiBox->addMenuItem("@guild:accept", playerID); //Accept
	suiBox->addMenuItem("@guild:decline", 0); //Decline

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSponsoredListTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_SPONSORED_LIST);
	suiBox->setCallback(new GuildSponsoredListSuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsored_title"); //Sponsored for Membership
	suiBox->setPromptText("@guild:sponsored_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	for (int i = 0; i < guild->getSponsoredPlayerCount(); ++i) {
		uint64 playerID = guild->getSponsoredPlayer(i);

		ManagedReference<SceneObject*> obj = server->getObject(playerID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* sponsoredPlayer = cast<CreatureObject*>( obj.get());

		suiBox->addMenuItem(sponsoredPlayer->getDisplayedName(), playerID);
	}

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSponsorTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	if (!guild->hasSponsorPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SuiInputBox*> suiBox = new SuiInputBox(player, SuiWindowType::GUILD_SPONSOR);
	suiBox->setCallback(new GuildSponsorSuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsor_title"); //Sponsor for Membership
	suiBox->setPromptText("@guild:sponsor_prompt");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setCancelButton(true, "@cancel");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendBaselinesTo(CreatureObject* player) {
	SceneObjectCreateMessage* create = new SceneObjectCreateMessage(_this->_getObjectID(), 0x7D40E2E6);
	player->sendMessage(create);

	Locker _lock(_this);

	GuildObjectMessage3* gild3 = new GuildObjectMessage3(&guildList, _this->_getObjectID());
	player->sendMessage(gild3);

	_lock.release();

	GuildObjectMessage6* gild6 = new GuildObjectMessage6(_this->_getObjectID());
	player->sendMessage(gild6);

	SceneObjectCloseMessage* close = new SceneObjectCloseMessage(_this->_getObjectID());
	player->sendMessage(close);


	//Send GuildChat if they are in a guild!
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL)
		return;

	/*ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

	if (guildChat == NULL)
		return;

	guildChat->sendTo(player);
	guildChat->addPlayer(player);*/
}

ChatRoom* GuildManagerImplementation::createGuildChannels(GuildObject* guild) {
	ManagedReference<ChatRoom*> guildRoom = chatManager->getGuildRoom();

	ManagedReference<ChatRoom*> guildLobby = chatManager->createRoom(String::valueOf(guild->getGuildID()), guildRoom);
	guildLobby->setPrivate();
	guildRoom->addSubRoom(guildLobby);

	ManagedReference<ChatRoom*> guildChat = chatManager->createRoom("GuildChat", guildLobby);
	guildChat->setPrivate();
	guildChat->setTitle(String::valueOf(guild->getGuildID()));
	guildLobby->addSubRoom(guildChat);

	guild->setChatRoom(guildChat);

	return guildChat;
}

GuildObject* GuildManagerImplementation::createGuild(CreatureObject* player, GuildTerminal* terminal, const String& guildName, const String& guildAbbrev) {
	if (player->isInGuild()) {
		player->sendSystemMessage("@guild:create_fail_in_guild"); //You cannot create a guild while already in a guild.
		return NULL;
	}

	Locker _lock(_this);

	uint64 playerID = player->getObjectID();

	if (isCreatingGuild(playerID))
		removePendingGuild(playerID);

	ManagedReference<GuildObject*> guild = cast<GuildObject*>( ObjectManager::instance()->createObject(0xD6888614, 1, "guilds")); //object/guild/guild_object.iff
	guild->setGuildLeaderID(playerID);
	guild->setGuildID(Long::hashCode(guild->getObjectID()));
	guild->setGuildName(guildName);
	guild->setGuildAbbrev(guildAbbrev);
	guild->addMember(playerID);

	ManagedReference<ChatRoom*> guildChat = createGuildChannels(guild);

	guildChat->sendTo(player);
	guildChat->addPlayer(player);

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

	_lock.release();

	//Send the delta to everyone currently online!
	chatManager->broadcastMessage(gildd3);

	CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(player);
	creod6->updateGuildID();
	creod6->close();
	player->broadcastMessage(creod6, true);

	info("Guild " + guildName + " <" + guildAbbrev + "> created.", true);

	return guild;
}

bool GuildManagerImplementation::disbandGuild(CreatureObject* player, GuildObject* guild) {
	Locker _lock(_this);

	if (guild == NULL)
		return false;

	if (!guild->hasDisbandPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return false;
	}

	ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

	if (guildChat != NULL) {
		ManagedReference<ChatRoom*> guildLobby = guildChat->getParent();

		chatManager->destroyRoom(guildChat);

		if (guildLobby != NULL)
			chatManager->destroyRoom(guildLobby);
	}

	//Remove all sponsored members from the sponsoredPlayers vectormap
	for (int i = 0; i < guild->getSponsoredPlayerCount(); ++i) {
		uint64 playerID = guild->getSponsoredPlayer(i);
		sponsoredPlayers.drop(playerID);
	}

	//We have to remove the guild tag from everyone currently online in this guild!
	GuildMemberList* memberList = guild->getGuildMemberList();

	if (memberList == NULL)
		return false;

	_lock.release();

	//TODO: This could probably be moved to the GuildObject destructor!
	for (int i = 0; i < memberList->size(); ++i) {
		Locker _locker(_this);
		GuildMemberInfo* gmi = &memberList->get(i);

		if (gmi == NULL)
			continue;

		ManagedReference<SceneObject*> obj = server->getObject(gmi->getPlayerID());

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* member = cast<CreatureObject*>( obj.get());

		member->setGuildObject(NULL);

		_locker.release();

		if (!member->isOnline())
			continue;

		CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(member);
		creod6->updateGuildID();
		creod6->close();

		member->broadcastMessage(creod6, true);
	}

	Locker _locker(_this);

	if (guildList.contains(guild->getGuildKey())) {
		GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this->_getObjectID());
		gildd3->startUpdate(0x04);
		guildList.drop(guild->getGuildKey(), gildd3);
		gildd3->close();

		guild->destroyObjectFromDatabase(true);

		_locker.release();
		//Send the delta to everyone currently online!
		chatManager->broadcastMessage(gildd3);
	}

	info("Guild " + guild->getGuildName() + " <" + guild->getGuildAbbrev() + "> disbanded.", true);

	return true;
}

void GuildManagerImplementation::sponsorPlayer(CreatureObject* player, GuildTerminal* guildTerminal, const String& playerName) {
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL)
		return;

	if (guild->getTotalMembers() >= maximumMembers) {
		player->sendSystemMessage("@guild:sponsor_fail_full"); //No more members may be sponsored, as the guild is already full.
		return;
	}

	ManagedReference<CreatureObject*> target = playerManager->getPlayer(playerName);

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
		StringIdChatParameter params;
		params.setStringId("@guild:sponsor_already_in_guild"); //%TU is already in a guild.
		params.setTU(target);

		player->sendSystemMessage(params);
		return;
	}

	StringIdChatParameter params;
	params.setStringId("@guild:sponsor_target"); //%TU has sponsored you for membership in %TT.
	params.setTU(player->getObjectID());
	params.setTT(guild->getGuildName());
	target->sendSystemMessage(params);

	//Here we need to send a confirmation box to the target player.
	sendGuildSponsorVerifyTo(player, target);
}

void GuildManagerImplementation::sendGuildSponsorVerifyTo(CreatureObject* player, CreatureObject* target) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_SPONSOR_VERIFY);
	suiBox->setCallback(new GuildSponsorVerifySuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsor_verify_title"); //Sponsored For Guild Membership
	suiBox->setPromptText("@guild:sponsor_verify_prompt");
	suiBox->setUsingObject(player);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	target->getPlayerObject()->addSuiBox(suiBox);
	target->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::acceptSponsorshipRequest(CreatureObject* player, CreatureObject* target) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL)
		return;

	Locker _lock(target, player);

	StringIdChatParameter params;
	params.setStringId("@guild:sponsor_accept"); //%TU has accepted your sponsorship
	params.setTU(target->getObjectID());

	player->sendSystemMessage(params);

	params.clear();

	params.setStringId("@guild:sponsor_self"); //You sponsor %TU for membership in %TT.
	params.setTT(guild->getGuildName());

	player->sendSystemMessage(params);

	addSponsoredPlayer(target->getObjectID(), guild);
	guild->addSponsoredPlayer(target->getObjectID());

	//Send emails
	params.setStringId("@guildmail:sponsor_text"); //%TU has sponsored %TT for membership in the guild.
	params.setTU(player->getDisplayedName());
	params.setTT(target->getDisplayedName());

	sendGuildMail("@guildmail:sponsor_subject", params, guild);
}

void GuildManagerImplementation::acceptSponsoredPlayer(CreatureObject* player, uint64 targetID) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SceneObject*> obj = server->getObject(targetID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* target = cast<CreatureObject*>( obj.get());

	Locker _lock(target, player);

	if (target->isInGuild()) {
		player->sendSystemMessage("@guild:sponsor_already_in_guild"); //%TU is already in a guild.
		return;
	}

	StringIdChatParameter params;
	params.setStringId("@guild:accept_self"); //You accept %TU for membership in %TT.
	params.setTU(target->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	params.setStringId("@guildmail:accept_text"); //%TU has accepted %TT into the guild as a member.
	params.setTU(player->getDisplayedName());
	params.setTT(target->getDisplayedName());
	sendGuildMail("@guildmail:accept_subject", params, guild);

	params.setTT(guild->getGuildName());

	guild->addMember(targetID);
	target->setGuildObject(guild);

	if (target->isOnline()) {
		params.setStringId("@guild:accept_target"); // %TU has accepted you for membership in %TT.
		target->sendSystemMessage(params);

		CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(target);
		creod6->updateGuildID();
		creod6->close();
		target->broadcastMessage(creod6, true);

		ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

		if (guildChat != NULL) {
			guildChat->sendTo(target);
			guildChat->addPlayer(target);
		}
	}

	params.setStringId("@guildmail:accept_target_text"); //%TU has accepted you into %TT as a member.
	chatManager->sendMail(guild->getGuildName(), "@guildmail:accept_target_subject", params, target->getFirstName());
}

void GuildManagerImplementation::sendGuildKickPromptTo(CreatureObject* player, CreatureObject* target) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_MEMBER_REMOVE);
	suiBox->setCallback(new GuildMemberRemoveSuiCallback(server));
	suiBox->setPromptTitle("@guild:kick_title"); //Kick From Guild
	suiBox->setPromptText("@guild:kick_prompt"); //Are you sure you want to kick %TU out of the guild?
	suiBox->setUsingObject(target);
	suiBox->setForceCloseDisabled();
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSetTitleTo(CreatureObject* player, CreatureObject* target) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasTitlePermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SuiInputBox*> suiBox = new SuiInputBox(player, SuiWindowType::GUILD_MEMBER_TITLE);
	suiBox->setCallback(new GuildTitleResponseSuiCallback(server));
	suiBox->setPromptTitle("@guild:title_title"); //Set Title
	suiBox->setPromptText("@guild:title_prompt"); //Enter a title to set for %TU.
	suiBox->setUsingObject(target);
	suiBox->setMaxInputSize(24);
	suiBox->setCancelButton(true, "@cancel");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::kickMember(CreatureObject* player, CreatureObject* target) {
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

	StringIdChatParameter params;
	params.setStringId("@guild:kick_self"); //You remove %TU from %TT.
	params.setTU(target->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	if (target->isOnline()) {
		params.setStringId("@guild:kick_target"); //%TU has removed you from %TT.
		params.setTU(player->getDisplayedName());
		target->sendSystemMessage(params);

		CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(target);
		creod6->updateGuildID();
		creod6->close();
		target->broadcastMessage(creod6, true);

		ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

		if (guildChat != NULL) {
			guildChat->removePlayer(target);
			guildChat->sendDestroyTo(target);
		}
	}

	params.setStringId("@guildmail:kick_text"); //%TU has removed %TT from the guild.
	params.setTU(player->getDisplayedName());
	params.setTT(target->getDisplayedName());
	sendGuildMail("@guildmail:kick_subject", params, guild);
}

void GuildManagerImplementation::setMemberTitle(CreatureObject* player, CreatureObject* target, const String& title) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasTitlePermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	if (title.isEmpty() || title.length() > 25) {
		player->sendSystemMessage("@guild:title_fail_bad_length"); //Guild member titles may be at most 25 characters in length.
		return;
	}

	NameManager* nameManager = processor->getNameManager();

	if (!nameManager->validateName(title, 0)) {
		player->sendSystemMessage("@guild:title_fail_not_allowed"); //That title is not allowed.
		return;
	}

	GuildMemberInfo* gmi = guild->getMember(target->getObjectID());
	gmi->setGuildTitle(title);

	StringIdChatParameter params;
	params.setStringId("@guild:title_self"); //You set %TU's guild title to '%TT'.
	params.setTU(target->getDisplayedName());
	params.setTT(title);
	player->sendSystemMessage(params);

	if (target->isOnline()) {
		params.setStringId("@guild:title_target"); //%TU has set your guild title to '%TT'.
		params.setTU(player->getDisplayedName());
		target->sendSystemMessage(params);
	}

}

void GuildManagerImplementation::setAllegianceTo(CreatureObject* player, uint64 targetID, GuildTerminal* guildTerminal) {

}

void GuildManagerImplementation::sendMemberPermissionsTo(CreatureObject* player, uint64 targetID, GuildTerminal* guildTerminal) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->isGuildLeader(player)) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	if (!guild->hasMember(targetID))
		return;

	GuildMemberInfo* gmi = guild->getMember(targetID);

	if (gmi == NULL)
		return;

	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_PERMISSIONS);
	listBox->setCallback(new GuildMemberPermissionsResponseSuiCallback(server));
	listBox->setPromptTitle("@guild:permissions_title"); //Guild Member Permissions
	listBox->setPromptText("@guild:permissions_prompt");
	listBox->setUsingObject(guildTerminal);
	listBox->setCancelButton(true, "@cancel");

	listBox->addMenuItem(String("@guild:permission_mail_") + (gmi->hasPermission(GuildObject::PERMISSION_MAIL) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_sponsor_") + (gmi->hasPermission(GuildObject::PERMISSION_SPONSOR) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_title_") + (gmi->hasPermission(GuildObject::PERMISSION_TITLE) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_accept_") + (gmi->hasPermission(GuildObject::PERMISSION_ACCEPT) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_kick_") + (gmi->hasPermission(GuildObject::PERMISSION_KICK) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_war_") + (gmi->hasPermission(GuildObject::PERMISSION_WAR) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_namechange_") + (gmi->hasPermission(GuildObject::PERMISSION_NAME) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_disband_") + (gmi->hasPermission(GuildObject::PERMISSION_DISBAND) ? "yes" : "no"), targetID);

	player->getPlayerObject()->addSuiBox(listBox);
	player->sendMessage(listBox->generateMessage());
}

void GuildManagerImplementation::toggleGuildPermission(CreatureObject* player, uint64 targetID, int permissionIndex, GuildTerminal* guildTerminal) {
	//TODO: Change to not require a guild terminal, it only needs passing to the sui list send to be set as using object...
	if (guildTerminal == NULL)
		return;

	ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

	if (guild == NULL || !guild->isGuildLeader(player)) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	//Can't change your own permissions
	if (player->getObjectID() == targetID)
		return;

	if (!guild->hasMember(targetID))
		return;

	GuildMemberInfo* gmi = guild->getMember(targetID);

	if (gmi == NULL)
		return;

	switch (permissionIndex) {
	case 0: //mail
		gmi->togglePermission(GuildObject::PERMISSION_MAIL);
		break;
	case 1: //sponsor
		gmi->togglePermission(GuildObject::PERMISSION_SPONSOR);
		break;
	case 2: //title
		gmi->togglePermission(GuildObject::PERMISSION_TITLE);
		break;
	case 3: //accept
		gmi->togglePermission(GuildObject::PERMISSION_ACCEPT);
		break;
	case 4: //kick
		gmi->togglePermission(GuildObject::PERMISSION_KICK);
		break;
	case 5: //war
		gmi->togglePermission(GuildObject::PERMISSION_WAR);
		break;
	case 6: //namechange
		gmi->togglePermission(GuildObject::PERMISSION_NAME);
		break;
	case 7: //disband
		gmi->togglePermission(GuildObject::PERMISSION_DISBAND);
		break;
	default:
		return;
	}

	//Resend the permissions sui
	sendMemberPermissionsTo(player, targetID, guildTerminal);
}

void GuildManagerImplementation::sendGuildListTo(CreatureObject* player, const String& guildFilter) {
	if (guildFilter.isEmpty()) {
		player->sendSystemMessage("Please provide a guild filter as an argument to minimize the search results.");
		return;
	}

	Locker _lock(_this);

	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, SuiWindowType::ADMIN_GUILDLIST);
	listBox->setCallback(new ListGuildsResponseSuiCallback(server));
	listBox->setPromptTitle("Guild List");
	listBox->setCancelButton(true, "@cancel");

	ManagedReference<GuildObject*> guild = NULL;

	for (int i = 0; i < guildList.size(); ++i) {
		guild = guildList.get(guildList.getKeyAt(i));

		String guildName = guild->getGuildName();
		String guildAbbrev = guild->getGuildAbbrev();
		uint64 guildObjectID = guild->getObjectID();

		if (guildName.indexOf(guildFilter) || guildAbbrev.indexOf(guildFilter))
			listBox->addMenuItem(guildName + " <" + guildAbbrev + ">", guildObjectID);

		if (listBox->getMenuSize() == 100)
			break;
	}

	if (listBox->getMenuSize() < 1) {
		player->sendSystemMessage("No guilds were found that matched the guild filter: " + guildFilter + ".");
		return;
	}

	if (listBox->getMenuSize() == 1 && guild != NULL) {
		sendGuildInformationTo(player, guild, NULL);
		return;
	}

	StringBuffer text;
	text << "Choose a guild below to view it's information, or perform a function on it.";

	if (listBox->getMenuSize() == 100)
		text << "\n\n\\#CC3300Only the first 100 results are being displayed. Please refine your search.\\#.";

	listBox->setPromptText(text.toString());

	player->getPlayerObject()->addSuiBox(listBox);
	player->sendMessage(listBox->generateMessage());
}

void GuildManagerImplementation::leaveGuild(CreatureObject* player, GuildObject* guild) {
	if (guild == NULL)
		return;

	StringIdChatParameter params;
	params.setStringId("@guild:leave_self"); //You leave %TU.
	params.setTU(guild->getGuildName());
	player->sendSystemMessage(params);

	guild->removeMember(player->getObjectID());
	player->setGuildObject(NULL);

	CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(player);
	creod6->updateGuildID();
	creod6->close();
	player->broadcastMessage(creod6, true);

	ManagedReference<ChatRoom*> guildChat = guild->getChatRoom();

	if (guildChat != NULL) {
		guildChat->removePlayer(player);
		guildChat->sendDestroyTo(player);
	}

	params.setStringId("@guildmail:leave_text"); //%TU has removed themselves from the guild.
	params.setTU(player->getDisplayedName());

	sendGuildMail("@guildmail:leave_subject", params, guild);
}

void GuildManagerImplementation::sendGuildMail(const String& subject, StringIdChatParameter& body, GuildObject* guild) {
	if (guild == NULL)
		return;

	GuildMemberList* memberList = guild->getGuildMemberList();

	if (memberList == NULL)
		return;

	for (int i = 0; i < memberList->size(); ++i) {
		GuildMemberInfo* gmi = &memberList->get(i);

		if (gmi == NULL)
			continue;

		ManagedReference<SceneObject*> obj = server->getObject(gmi->getPlayerID());

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* recipient = cast<CreatureObject*>( obj.get());

		chatManager->sendMail(guild->getGuildName(), subject, body, recipient->getFirstName());
	}
}
