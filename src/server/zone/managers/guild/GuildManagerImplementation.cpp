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
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

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
	inputBox->setMaxInputSize(25);
	inputBox->setUsingObject(terminal);

	player->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildName(PlayerCreature* player, const String& guildName) {

	//@guild:create_fail_name_in_use That guild name is already in use.
	//@guild:create_fail_name_now_allowed That guild name is not allowed.
	//@guild:create_fail_name_bad_length Guild names must be 1-25 characters in length.
	return true;
}

void GuildManagerImplementation::sendGuildCreateAbbrevTo(PlayerCreature* player, GuildTerminal* terminal) {
	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_ABBREV);
	inputBox->setPromptTitle("@guild:create_abbrev_title"); //Guild Abbreviation
	inputBox->setPromptText("@guild:create_abbrev_prompt");
	inputBox->setMaxInputSize(5);
	inputBox->setUsingObject(terminal);

	player->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildAbbrev(PlayerCreature* player, const String& guildAbbrev) {
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
	guildInfo << "Guild Name: " << guild->getCustomObjectName().toString() << "\n";
	guildInfo << "Abbreviation: " << guild->getGuildAbbrev() << "\n";

	if (guildLeader != NULL && guildLeader->isPlayerCreature())
		guildInfo << "Guild Leader: " << guildLeader->getObjectName()->getDisplayedName() << "\n";
	else
		guildInfo << "Guild Leader: None\n";

	guildInfo << "Members: " << guild->getTotalMembers() << "\n";

	suiBox->setPromptText(guildInfo.toString());
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendBaselinesTo(PlayerCreature* player) {
	SceneObjectCreateMessage* create = new SceneObjectCreateMessage(0xDEADBABE, 0x7D40E2E6);
	player->sendMessage(create);

	Locker _lock(_this);

	GuildObjectMessage3* gild3 = new GuildObjectMessage3(&guildList);
	player->sendMessage(gild3);

	GuildObjectMessage6* gild6 = new GuildObjectMessage6();
	player->sendMessage(gild6);

	SceneObjectCloseMessage* close = new SceneObjectCloseMessage(0xDEADBABE);
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

	player->setGuildObject(guild);

	GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3();
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

void GuildManagerImplementation::acceptMember(PlayerCreature* player, uint64 targetID) {

}

void GuildManagerImplementation::kickMember(PlayerCreature* player, uint64 targetID) {

}

void GuildManagerImplementation::setGuildMemberTitle(PlayerCreature* player, uint64 targetID) {

}

void GuildManagerImplementation::setAllegianceTo(PlayerCreature* player, uint64 targetID) {

}
