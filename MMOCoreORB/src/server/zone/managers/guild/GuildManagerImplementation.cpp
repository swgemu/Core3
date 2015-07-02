/*
 * GuildManagerImplementation.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#include "server/zone/managers/guild/GuildManager.h"

#include "server/chat/ChatManager.h"
#include "server/chat/room/ChatRoom.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"

#include "server/zone/objects/guild/RenameGuildTask.h"
#include "server/zone/objects/guild/UpdateWarStatusTask.h"

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
#include "server/zone/objects/guild/sui/GuildChangeNameResponseSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildChangeAbbrevResponseSuiCallback.h"
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
#include "server/zone/objects/guild/sui/GuildWarEnemyNameSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildAddEnemySuiCallback.h"
#include "server/zone/objects/guild/sui/GuildTransferLeadershipSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildTransferLeaderAckSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildTransferLotsSuiCallback.h"
#include "server/zone/objects/guild/sui/GuildVoteSuiCallback.h"
#include "server/zone/objects/creature/commands/sui/ListGuildsResponseSuiCallback.h"

#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "server/zone/packets/scene/SceneObjectCloseMessage.h"
#include "server/zone/packets/guild/GuildObjectMessage3.h"
#include "server/zone/packets/guild/GuildObjectMessage6.h"
#include "server/zone/packets/guild/GuildObjectDeltaMessage3.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/commands/TransferstructureCommand.h"

#include "GuildMailTask.h"

void GuildManagerImplementation::loadLuaConfig() {
	info("Loading configuration file.", true);

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/guild_manager.lua");

	guildUpdateInterval = lua->getGlobalInt("GuildUpdateInterval");
	requiredMembers = lua->getGlobalInt("RequiredMembers");
	maximumMembers = lua->getGlobalInt("MaximumMembers");

	delete lua;
	lua = NULL;
}

void GuildManagerImplementation::loadGuilds() {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

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

	scheduleGuildUpdates();
}

void GuildManagerImplementation::scheduleGuildUpdates() {
	info("Scheduling guild updates.", true);

	for (int i = 0; i < guildList.size(); ++i) {
		GuildObject* guild = guildList.getValueAt(i);

		if (guild == NULL) {
			continue;
		}

		Time* nextUpdateTime = guild->getNextUpdateTime();
		int seconds = -1 * round(nextUpdateTime->miliDifference() / 1000.f);

		if (seconds < 0)
			seconds = 0;

		guild->rescheduleUpdateEvent(seconds);
	}
}

void GuildManagerImplementation::processGuildUpdate(GuildObject* guild) {
	info("Processing guild update for: " + guild->getGuildName() + " <" + guild->getGuildAbbrev() + ">");

	Vector<uint64> toRemove;

	// Check that members still exist
	for (int i = 0; i < guild->getTotalMembers(); i++) {
		uint64 memberID = guild->getMember(i);
		ManagedReference<CreatureObject*> member = server->getObject(memberID).castTo<CreatureObject*>();

		if (member == NULL) {
			toRemove.add(memberID);

			if (memberID == guild->getGuildLeaderID()) {
				guild->setGuildLeaderID(0);
			}
		}
	}

	for (int i = 0; i < toRemove.size(); i++) {
		guild->removeMember(toRemove.get(i));
	}

	toRemove.removeAll();

	// Destroy guild if there are not enough members remaining
	if (guild->getTotalMembers() < requiredMembers) {
		guild->unlock();

		StringIdChatParameter params;
		params.setStringId("@guildmail:disband_not_enough_members_text"); // The guild has been disbanded due to lack of members.

		destroyGuild(guild, params);

		guild->lock();

		info("Guild " + guild->getGuildName() + " <" + guild->getGuildAbbrev() + "> was destroyed due to lack of members.", true);
		return;
	}

	// Cleanup sponsored players list
	for (int i = 0; i < guild->getSponsoredPlayerCount(); i++) {
		uint64 playerID = guild->getSponsoredPlayer(i);

		ManagedReference<CreatureObject*> player = server->getObject(playerID).castTo<CreatureObject*>();

		if (player == NULL) {
			toRemove.add(playerID);

			if (isSponsoredPlayer(playerID)) {
				removeSponsoredPlayer(playerID);
			}
		} else {
			if (!isSponsoredPlayer(playerID) || guild != getSponsoredGuild(playerID)) {
				toRemove.add(playerID);
			}
		}

	}

	for (int i = 0; i < toRemove.size(); i++) {
		guild->removeSponsoredPlayer(toRemove.get(i));
	}

	if (guild->isRenamePending()) {
		RenameGuildTask* task = new RenameGuildTask(server, guild);
		task->execute();
	}

	if (guild->isElectionEnabled()) {
		if (guild->getElectionState() == GuildObject::ELECTION_FIRST_WEEK) {
			guild->setElectionState(GuildObject::ELECTION_SECOND_WEEK);
		} else {
			processGuildElection(guild);
		}
	}

	if (!guild->isElectionEnabled()) {
		uint64 leaderID = guild->getGuildLeaderID();
		bool startElections = false;

		ManagedReference<SceneObject*> leader = server->getObject(leaderID);

		if (leader == NULL || !leader->isPlayerCreature()) {
			startElections = true;
		} else {
			CreatureObject* leaderCreo = leader.castTo<CreatureObject*>();

			if (leaderCreo->getPlayerObject()->getDaysSinceLastLogout() >= 30)
				startElections = true;
		}

		if (startElections) {
			guild->resetElection(false);
			guild->setElectionState(GuildObject::ELECTION_FIRST_WEEK);

			StringIdChatParameter params;
			params.setStringId("@guild:open_elections_absent_email_body"); // Your guild leader has not logged in for an extended period of time. In order to enable your guild to continue to operate efficiently, the guild leader voting system has been enabled. You may vote at the guild terminal in your PA Hall. If you are a full member of the guild, you may opt to run for the position of guild leader by registering at the guild terminal. A new guild leader will be elected in exactly two weeks. The guild member with the most votes at that time will become guild leader.
			sendGuildMail("@guild:open_elections_absent_email_subject", params, guild); // Guild Leader Elections Open!
		}
	}

	guild->rescheduleUpdateEvent(guildUpdateInterval * 60);
}

void GuildManagerImplementation::processGuildElection(GuildObject* guild) {
	VectorMap<uint64, int>* candidates = guild->getCandidates();
	uint64 oldLeaderID = guild->getGuildLeaderID();
	uint64 topCandidate = oldLeaderID; // old leader defaults as the top candidate.
	int topVotes = 0;

	ManagedReference<SceneObject*> oldLeader = server->getObject(oldLeaderID);
	CreatureObject* oldLeaderCreo = NULL;
	if (oldLeader != NULL && oldLeader->isPlayerCreature()) {
		oldLeaderCreo = oldLeader.castTo<CreatureObject*>();
	}

	//Loop through the candidate votes.
	for (int i = 0; i < candidates->size(); ++i) {
		VectorMapEntry<uint64, int> entry = candidates->elementAt(i);

		uint64 candidateID = entry.getKey();
		int votes = entry.getValue();

		// Ensure that each vote is for a valid candidate who is a current guild member.
		if (!guild->hasMember(candidateID) || !guild->isCandidate(candidateID)) {
			continue;
		}

		ManagedReference<SceneObject*> candidateObj = server->getObject(candidateID);

		if (candidateObj != NULL && candidateObj->isPlayerCreature()) {

			if (votes > topVotes || (votes == topVotes && candidateID == oldLeaderID)) {
				topCandidate = candidateID;
				topVotes = votes;
			}
		}
	}

	guild->resetElection(true);

	ManagedReference<SceneObject*> obj = server->getObject(topCandidate);
	ManagedReference<CreatureObject*> newLeader = NULL;
	if (obj != NULL && obj->isPlayerCreature()) {
		newLeader = obj.castTo<CreatureObject*>();
	}

	// If there was no old leader and no one voted, elect the player with the highest permission
	if (newLeader == NULL) {
		uint64 memberID = guild->getMemberWithHighestPermission();

		// No member had any permissions, elect the first member
		if (memberID == 0) {
			memberID = guild->getMember(0);
		}

		newLeader = server->getObject(memberID).castTo<CreatureObject*>();
	}

	// This shouldn't happen since we cleanup the member list before processing the election
	if (newLeader == NULL)
		return;

	// transfer leadership
	transferLeadership(newLeader, oldLeaderCreo, true);

	// send mail to all guild members
	String winnerName = newLeader->getFirstName();
	StringIdChatParameter emailbody;
	String subject;

	if (topCandidate == oldLeaderID) {
		emailbody.setStringId("@guild:public_election_inc_body"); // The elections for %TT have been held. The incumbent guild leader is victorious! Please congratulate %TO on retaining their office. The voting system will now be disabled. The new leader can enable it if they wish to run new elections.
		subject = "@guild:public_election_inc_subject"; // Election Results!
	} else {
		emailbody.setStringId("@guild:public_election_body"); // The leader elections for %TT have been held. The incumbent guild leader has lost the election! The new guild leader is %TO. Please congratulate the new guild leader! The voting system will now be disabled. The new leader can enable it if they wish to run new elections.
		subject = "@guild:public_election_subject"; // Election Results!
	}

	emailbody.setTT(guild->getGuildName());
	emailbody.setTO(winnerName);

	sendGuildMail(subject, emailbody, guild);

}

void GuildManagerImplementation::destroyGuild(GuildObject* guild, StringIdChatParameter& mailbody) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

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

		if (guild == getSponsoredGuild(playerID)) {
			sponsoredPlayers.drop(playerID);
		}
	}

	// Remove war references
	for (int i = 0; i < guildList.size(); ++i) {
		ManagedReference<GuildObject*> oguild = guildList.get(guildList.getKeyAt(i));

		if (oguild == NULL)
			continue;

		byte status = oguild->getWarStatus(guild->getObjectID());

		if (status != 0) {
			//setWarStatus uses its own mutex, no need to lock the guild
			oguild->setWarStatus(guild->getObjectID(), GuildObject::WAR_NONE);
		}
	}

	_lock.release();

	//We have to remove the guild tag from everyone currently online in this guild!
	GuildMemberList* memberList = guild->getGuildMemberList();

	if (memberList != NULL) {

		//TODO: This could probably be moved to the GuildObject destructor!
		for (int i = 0; i < memberList->size(); ++i) {
			Locker locker(guild);
			GuildMemberInfo* gmi = &memberList->get(i);

			if (gmi == NULL)
				continue;

			ManagedReference<SceneObject*> obj = server->getObject(gmi->getPlayerID());

			if (obj == NULL || !obj->isPlayerCreature())
				continue;

			CreatureObject* member = cast<CreatureObject*>( obj.get());

			Locker clocker(member, guild);

			member->setGuildObject(NULL);

			clocker.release();

			chatManager->sendMail(guild->getGuildName(), "@guildmail:disband_subject", mailbody, member->getFirstName());

			locker.release();

			if (!member->isOnline())
				continue;

			CreatureObjectDeltaMessage6* creod6 = new CreatureObjectDeltaMessage6(member);
			creod6->updateGuildID();
			creod6->close();

			member->broadcastMessage(creod6, true);

			PlayerObject* memberGhost = member->getPlayerObject();

			if (memberGhost != NULL) {
				memberGhost->updateInRangeBuildingPermissions();
			}
		}
	}

	Locker _locker(_this.getReferenceUnsafeStaticCast());

	if (guildList.contains(guild->getGuildKey())) {
		GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast()->_getObjectID());
		gildd3->startUpdate(0x04);
		guildList.drop(guild->getGuildKey(), gildd3);
		gildd3->close();

		guild->destroyObjectFromDatabase(true);

		_locker.release();
		//Send the delta to everyone currently online!
		chatManager->broadcastMessage(gildd3);
	}
}

void GuildManagerImplementation::sendGuildCreateNameTo(CreatureObject* player, GuildTerminal* terminal) {
	if (player->isInGuild()) {
		player->sendSystemMessage("@guild:create_fail_in_guild"); // You cannot create a guild while already in a guild.
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_CREATE_NAME);

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_NAME);
	inputBox->setCallback(new GuildCreateNameResponseSuiCallback(server));
	inputBox->setPromptTitle("@guild:create_name_title"); // Guild Name
	inputBox->setPromptText("@guild:create_name_prompt"); // Enter a name for your guild. Guild names must be between 1 and 25 characters in length.
	inputBox->setMaxInputSize(24);
	inputBox->setUsingObject(terminal);
	inputBox->setForceCloseDistance(32);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

void GuildManagerImplementation::sendGuildChangeNameTo(CreatureObject* player, GuildObject* guild, GuildTerminal* terminal) {
	if (guild == NULL)
		return;

	if (!guild->hasNamePermission(player->getObjectID()) && !player->getPlayerObject()->isPrivileged()) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	if (guild->isRenamePending()) {
		player->sendSystemMessage("A guild rename is already pending.");
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_CHANGE_NAME);

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CHANGE_NAME);
	inputBox->setCallback(new GuildChangeNameResponseSuiCallback(server, guild));
	inputBox->setPromptTitle("@guild:namechange_name_title"); // Change Guild Name
	inputBox->setPromptText("@guild:namechange_name_prompt"); // Enter the name to which you wish to change your guild. Guild names must be between 1 and 25 characters. Name changes take approximately 7 days to take effect.
	inputBox->setMaxInputSize(24);
	inputBox->setUsingObject(terminal);
	inputBox->setForceCloseDistance(32);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildName(CreatureObject* player, const String& guildName, GuildObject* guild) {
	NameManager* nameManager = processor->getNameManager();

	int validate = nameManager->validateGuildName(guildName, NameManagerType::GUILD_NAME);

	if (validate != NameManagerResult::ACCEPTED) {
		if (validate == NameManagerResult::DECLINED_GUILD_LENGTH)
			player->sendSystemMessage("@guild:create_fail_name_bad_length"); // Guild names must be 1-25 characters in length.
		else
			player->sendSystemMessage("@guild:create_fail_name_not_allowed"); // That guild name is not allowed.

		return false;
	}

	if (guildNameExists(guildName)) {
		if (guild == NULL || guildName != guild->getGuildName()) {
			player->sendSystemMessage("@guild:create_fail_name_in_use"); // That guild name is already in use.
			return false;
		}
	}

	return true;
}

bool GuildManagerImplementation::guildNameExists(const String& guildName) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < guildList.size(); ++i) {
		ManagedReference<GuildObject*> guild = guildList.get(guildList.getKeyAt(i));

		if (guild == NULL)
			continue;

		if (guild->getGuildName() == guildName)
			return true;
	}

	return false;
}

void GuildManagerImplementation::sendGuildCreateAbbrevTo(CreatureObject* player, GuildTerminal* terminal) {
	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_CREATE_ABBREV);

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CREATE_ABBREV);
	inputBox->setCallback(new GuildCreateAbbrevResponseSuiCallback(server));
	inputBox->setPromptTitle("@guild:create_abbrev_title"); // Guild Abbreviation
	inputBox->setPromptText("@guild:create_abbrev_prompt"); // Enter an abbreviation for your guild. Guild abbreviations must be 1-5 characters in length.
	inputBox->setMaxInputSize(4);
	inputBox->setUsingObject(terminal);
	inputBox->setForceCloseDistance(32);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

void GuildManagerImplementation::sendGuildChangeAbbrevTo(CreatureObject* player, GuildObject* guild, GuildTerminal* terminal) {
	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_CHANGE_ABBREV);

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::GUILD_CHANGE_ABBREV);
	inputBox->setCallback(new GuildChangeAbbrevResponseSuiCallback(server, guild));
	inputBox->setPromptTitle("@guild:namechange_abbrev_title"); // Change Guild Abbreviation
	inputBox->setPromptText("@guild:namechange_abbrev_prompt"); // Enter the abbreviation for your guild's new name. Guild abbreviations must be between 1 and 5 characters in length.
	inputBox->setMaxInputSize(4);
	inputBox->setUsingObject(terminal);
	inputBox->setForceCloseDistance(32);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool GuildManagerImplementation::validateGuildAbbrev(CreatureObject* player, const String& guildAbbrev, GuildObject* guild) {
	NameManager* nameManager = processor->getNameManager();

	int validate = nameManager->validateGuildName(guildAbbrev, NameManagerType::GUILD_ABBREV);

	if (validate != NameManagerResult::ACCEPTED) {
		if (validate == NameManagerResult::DECLINED_GUILD_LENGTH)
			player->sendSystemMessage("@guild:create_fail_abbrev_bad_length"); // Guild abbreviations must be 1-5 characters in length.
		else
			player->sendSystemMessage("@guild:create_fail_abbrev_not_allowed"); // That guild abbreviation is not allowed.

		return false;
	}

	if (guildAbbrevExists(guildAbbrev)) {
		if (guild == NULL || guildAbbrev != guild->getGuildAbbrev()) {
			player->sendSystemMessage("@guild:create_fail_abbrev_in_use"); // That guild abbreviation is already in use.
			return false;
		}
	}

	return true;
}

bool GuildManagerImplementation::guildAbbrevExists(const String& guildAbbrev) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < guildList.size(); ++i) {
		ManagedReference<GuildObject*> guild = guildList.get(guildList.getKeyAt(i));

		if (guild == NULL)
			continue;

		if (guild->getGuildAbbrev() == guildAbbrev)
			return true;
	}

	return false;
}

GuildObject* GuildManagerImplementation::createGuild(CreatureObject* player, const String& guildName, const String& guildAbbrev) {
	if (player->isInGuild()) {
		player->sendSystemMessage("@guild:create_fail_in_guild"); // You cannot create a guild while already in a guild.
		return NULL;
	}

	Locker _lock(_this.getReferenceUnsafeStaticCast());

	uint64 playerID = player->getObjectID();

	if (isCreatingGuild(playerID))
		removePendingGuild(playerID);
	// Strip out any errant escaped newlines from the guild name and tags and any errant color code starts
	String tmp = guildName.replaceAll("\n|\r|#","");
	String tabbrev = guildAbbrev.replaceAll("\n|\r|#","");

	ManagedReference<GuildObject*> guild = cast<GuildObject*>( ObjectManager::instance()->createObject(0xD6888614, 1, "guilds")); //object/guild/guild_object.iff

	Locker clocker(guild, player);

	guild->setGuildLeaderID(playerID);
	guild->setGuildID(Long::hashCode(guild->getObjectID()));
	guild->setGuildName(tmp);
	guild->setGuildAbbrev(tabbrev);
	guild->addMember(playerID);
	guild->rescheduleUpdateEvent(guildUpdateInterval * 60);

	ManagedReference<ChatRoom*> guildChat = createGuildChannels(guild);

	guildChat->sendTo(player);
	guildChat->addPlayer(player);

	//Handle setting of the guild leader.
	GuildMemberInfo* gmi = guild->getMember(playerID);
	gmi->setPermissions(GuildObject::PERMISSION_ALL);

	player->setGuildObject(guild);

	GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast()->_getObjectID());
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

	info("Guild " + tmp + " <" + tabbrev + "> created.", true);

	return guild;
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

	Locker locker(guild);

	guild->setChatRoom(guildChat);

	return guildChat;
}

void GuildManagerImplementation::setupGuildRename(CreatureObject* player, GuildObject* guild) {
	guild->setRenamePending(true);
	guild->setRenamerID(player->getObjectID());

	if (player->getPlayerObject()->isPrivileged()) {
		RenameGuildTask* task = new RenameGuildTask(server, guild);
		task->execute();
		return;
	}

	StringIdChatParameter params("@guild:namechange_self");
	params.setTU(guild->getPendingNewName());
	params.setTT(guild->getPendingNewAbbrev());
	player->sendSystemMessage(params); // You have set your guild's name and abbreviation to bechanged to '%TU' and '%TT' respectively. The change will take place in approximately 7 days, if there are no conflicts at that time.
}

void GuildManagerImplementation::renameGuild(GuildObject* guild) {
	if (!guild->isRenamePending()) {
		guild->resetRename();
		return;
	}

	uint64 renamerID = guild->getRenamerID();
	CreatureObject* renamer = server->getObject(renamerID).castTo<CreatureObject*>();

	if (renamer == NULL || !renamer->isPlayerCreature() || (!guild->hasNamePermission(renamerID) && !renamer->getPlayerObject()->isPrivileged())) {
		guild->resetRename();
		return;
	}

	String newName = guild->getPendingNewName();
	String newAbbrev = guild->getPendingNewAbbrev();

	if (!validateGuildName(renamer, newName, guild)) {
		guild->resetRename();
		return;
	}

	if (!validateGuildAbbrev(renamer, newAbbrev, guild)) {
		guild->resetRename();
		return;
	}

	Locker _lock(_this.getReferenceUnsafeStaticCast());

	if (guildList.contains(guild->getGuildKey())) {
		GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast()->_getObjectID());
		gildd3->startUpdate(0x04);
		guildList.drop(guild->getGuildKey(), gildd3);
		gildd3->close();

		_lock.release();
		//Send the delta to everyone currently online!
		chatManager->broadcastMessage(gildd3);
	}

	guild->setGuildName(newName);
	guild->setGuildAbbrev(newAbbrev);

	Locker _locker(_this.getReferenceUnsafeStaticCast());

	GuildObjectDeltaMessage3* gildd3 = new GuildObjectDeltaMessage3(_this.getReferenceUnsafeStaticCast()->_getObjectID());
	gildd3->startUpdate(0x04);
	guildList.add(guild->getGuildKey(), guild, gildd3);
	gildd3->close();

	_locker.release();

	//Send the delta to everyone currently online!
	chatManager->broadcastMessage(gildd3);

	guild->resetRename();

	// Send emails to guild
	StringIdChatParameter params;
	params.setStringId("@guildmail:namechange_text"); //%TO has renamed the guild to %TU <%TT>
	params.setTO(renamer->getFirstName());
	params.setTU(newName);
	params.setTT(newAbbrev);

	sendGuildMail("@guildmail:namechange_subject", params, guild);
}

void GuildManagerImplementation::sendGuildInformationTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_INFORMATION);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::GUILD_INFORMATION);
	suiBox->setPromptTitle("@guild:info_title"); // Guild Information
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);

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

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildDisbandConfirmTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	if (!guild->hasDisbandPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_DISBAND);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::GUILD_DISBAND);
	suiBox->setCallback(new GuildDisbandSuiCallback(server));
	suiBox->setPromptTitle("@guild:disband_title"); // Disband Guild
	suiBox->setPromptText("@guild:disband_prompt"); // Are you sure you wish to disband your guild?
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

bool GuildManagerImplementation::disbandGuild(CreatureObject* player, GuildObject* guild) {

	if (guild == NULL)
		return false;

	if (!guild->hasDisbandPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return false;
	}

	StringIdChatParameter params;
	params.setStringId("@guildmail:disband_text"); // The guild has been disbanded by %TU
	params.setTU(player->getFirstName());

	destroyGuild(guild, params);

	info("Guild " + guild->getGuildName() + " <" + guild->getGuildAbbrev() + "> disbanded.", true);

	return true;
}

void GuildManagerImplementation::sendGuildTransferTo(CreatureObject* player, GuildTerminal* guildTerminal) {

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_TRANSFER_LEADER);

	ManagedReference<SuiInputBox*> suiBox = new SuiInputBox(player, SuiWindowType::GUILD_TRANSFER_LEADER);
	suiBox->setCallback(new GuildTransferLeadershipSuiCallback(server));
	suiBox->setPromptTitle("@guild:make_leader_t"); // Transfer PA Leadership
	suiBox->setPromptText("@guild:make_leader_d"); // You are about to transfer leadership of this Player Association!  Once you take this action you will be made a normal member and your leader permissions will be revoked.
	suiBox->setCancelButton(true, "@cancel");
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendTransferAckTo(CreatureObject* player, const String& newOwnerName, SceneObject* sceoTerminal){
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>( sceoTerminal->getParentRecursively(SceneObjectType::BUILDING).get().get());
	if (building == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> owner = building->getOwnerCreatureObject();
	if (owner == NULL || !owner->isPlayerCreature()) {
		return;
	}

	ManagedReference<GuildObject*> guild = owner->getGuildObject().get();

	if (guild == NULL)
		return;

	Locker _lock(guild);

	if (!(guild->getGuildLeaderID() == player->getObjectID() && player == owner) && !player->getPlayerObject()->isPrivileged())
		return;

	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
	ManagedReference<CreatureObject*> target = playerManager->getPlayer(newOwnerName);

	if (target == NULL) {
		player->sendSystemMessage("@ui_community:friend_location_failed_noname"); // no player with that name exists
		return;
	}

	if(target->getObjectID() == guild->getGuildLeaderID()) {
		player->sendSystemMessage("@guild:already_leader"); // You are already the guild leader.
		return;
	}

	// make sure target is in the guild
	if ( !guild->hasMember(target->getObjectID())) {
		player->sendSystemMessage("@guild:ml_fail"); // unable to find a member of the PA with that name
		return;
	}

	// make sure player transferring to is nearby
	if (!target->isOnline() || !target->isInRange(sceoTerminal, 32)) {
		StringIdChatParameter params("@guild:ml_not_loaded");  // That person is not loaded or is too far away.
		player->sendSystemMessage(params);
		return;
	}

	if ( !target->getPlayerObject()->hasLotsRemaining(5) ) {
		target->sendSystemMessage("@guild:ml_no_lots_free");  // That person does not have enough free lots to own the PA hall.  PA hall ownership is a requirement be guild leader
		return;
	}

	guild->setTransferPending(true);

	_lock.release();

	Locker _clocker(target, player);

	target->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_TRANSFER_LEADER_CONFIRM);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_TRANSFER_LEADER_CONFIRM);
	suiBox->setCallback(new GuildTransferLeaderAckSuiCallback(server));
	suiBox->setPromptTitle("@guild:make_leader_t"); // Transfer PA leadership
	suiBox->setPromptText("@guild:make_leader_p");  // The leader of this PA wants to transfer leadership to you. Do you accept?
	suiBox->setUsingObject(sceoTerminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	target->getPlayerObject()->addSuiBox(suiBox);
	target->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::transferLeadership(CreatureObject* newLeader, CreatureObject* oldLeader, bool election) {
	GuildObject* guild = newLeader->getGuildObject();

	Locker glock(guild);
	guild->setGuildLeaderID(newLeader->getObjectID());
	guild->setTransferPending(false);

	// change admin privs for old and new leader
	GuildMemberInfo* gmiLeader = guild->getMember(newLeader->getObjectID());

	if (gmiLeader!= NULL){
		gmiLeader->setPermissions(GuildObject::PERMISSION_ALL);
	}

	if ( oldLeader != NULL) {
	
		GuildMemberInfo* gmiOldLeader = guild->getMember(oldLeader->getObjectID());
		
		if (gmiOldLeader != NULL){
			gmiOldLeader->setPermissions(GuildObject::PERMISSION_NONE);
		}
	}

	glock.release();

	if (election)
		return;

	if (oldLeader != NULL) {
		oldLeader->sendSystemMessage("@guild:ml_success");  // PA leadership transferred.  YOu are now a normal member of the PA.
	}

	newLeader->sendSystemMessage("@guild:ml_you_are_leader"); // You have been made leader of your PA

	// Send emails to guild
	StringIdChatParameter params;
	params.setStringId("@guildmail:leaderchange_text"); // %TU is the new guild leader.
	params.setTU(newLeader->getFirstName());

	sendGuildMail("@guildmail:leaderchange_subject", params, guild);
}

bool GuildManagerImplementation::transferGuildHall(CreatureObject* newOwner, SceneObject* sceoTerminal) {
	if (sceoTerminal == NULL || !sceoTerminal->isTerminal())
		return false;

	Terminal* terminal = cast<Terminal*>(sceoTerminal);

	if (!terminal->isGuildTerminal())
		return false;

	GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);

	if ( guildTerminal == NULL )
		return false;

	ManagedReference<BuildingObject*> buildingObject = cast<BuildingObject*>( guildTerminal->getParentRecursively(SceneObjectType::BUILDING).get().get());


	if ( buildingObject != NULL ) {

			ManagedReference<CreatureObject*> oldOwner = buildingObject->getOwnerCreatureObject();

			if ( oldOwner != NULL && oldOwner != newOwner ) {
				if (TransferstructureCommand::doTransferStructure(oldOwner, newOwner, buildingObject, true) == QueueCommand::SUCCESS) {
					newOwner->sendSystemMessage("@guild:pa_owner_now"); // You are now the owner of this PA Hall.
					return true;
				}

			} else {
				newOwner->sendSystemMessage("@player_structure:already_owner"); // You are already the owner.
			}
		}

	return false;
}

void GuildManagerImplementation::sendAcceptLotsTo(CreatureObject* newOwner, GuildTerminal* guildTerminal) {
	newOwner->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_TAKE_LOTS);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(newOwner, SuiWindowType::GUILD_TAKE_LOTS);
	suiBox->setCallback(new GuildTransferLotsSuiCallback(server));
	suiBox->setPromptTitle("@guild:accept_pa_hall_t"); // Accept PA Hall Lots
	suiBox->setPromptText("@guild:accept_pa_hall_p"); // The current owner of this PA hall has not logged in for 28 days. As guild leader, you may transfer ownership of the PA hall to yourself. You must have enough lots free to accept PA Hall ownership. Once you own the PA hall you may transfer it to another owner if you so desire.
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@cancel");

	newOwner->getPlayerObject()->addSuiBox(suiBox);
	newOwner->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildMemberListTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_MEMBER_LIST);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_LIST);
	suiBox->setCallback(new GuildMemberListSuiCallback(server));
	suiBox->setPromptTitle("@guild:members_title"); // Guild Members
	suiBox->setPromptText("@guild:members_prompt"); // These are the current members of the guild. To perform an operation on a guild member, select them in the list and press Ok.
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);

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

void GuildManagerImplementation::sendGuildMemberOptionsTo(CreatureObject* player, GuildObject* guild, uint64 memberID, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _locker(player);
	Locker _lock(guild, player);

	if (!guild->hasMember(player->getObjectID()))
		return;

	ManagedReference<SceneObject*> playObj = server->getObject(memberID);
	if (playObj == NULL || !playObj->isPlayerCreature())
		return;

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_MEMBER_OPTIONS);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_OPTIONS);
	suiBox->setCallback(new GuildMemberOptionsSuiCallback(server));
	suiBox->setPromptTitle("@guild:member_options_title"); // Member Options

	UnicodeString text = StringIdManager::instance()->getStringId("@guild:member_options_prompt"); // Select an operation from the list to perform on %TU and press Ok.
	text = text.replaceFirst("%TU", playObj->getDisplayedName());

	suiBox->setPromptText(text.toString());
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@cancel");

	suiBox->addMenuItem("@guild:title", memberID); // Set Title
	suiBox->addMenuItem("@guild:kick", memberID); // Kick
	suiBox->addMenuItem("@guild:permissions", memberID); // Change Permissions

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sendGuildSetTitleTo(CreatureObject* player, CreatureObject* target) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasTitlePermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_MEMBER_TITLE);

	ManagedReference<SuiInputBox*> suiBox = new SuiInputBox(player, SuiWindowType::GUILD_MEMBER_TITLE);
	suiBox->setCallback(new GuildTitleResponseSuiCallback(server));
	suiBox->setPromptTitle("@guild:title_title"); // Guild Member Title

	UnicodeString text = StringIdManager::instance()->getStringId("@guild:title_prompt"); // Enter a title to set for %TU.
	text = text.replaceFirst("%TU", target->getDisplayedName());

	suiBox->setPromptText(text.toString());
	suiBox->setUsingObject(target);
	suiBox->setForceCloseDistance(32);
	suiBox->setMaxInputSize(24);
	suiBox->setCancelButton(true, "@cancel");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::setMemberTitle(CreatureObject* player, CreatureObject* target, const String& title) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasTitlePermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	NameManager* nameManager = processor->getNameManager();

	int validate = nameManager->validateGuildName(title, NameManagerType::GUILD_TITLE);

	if (validate != NameManagerResult::ACCEPTED) {
		if (validate == NameManagerResult::DECLINED_GUILD_LENGTH)
			player->sendSystemMessage("@guild:title_fail_bad_length"); // Guild member titles may be at most 25 characters in length.
		else
			player->sendSystemMessage("@guild:title_fail_not_allowed"); // That title is not allowed.

		return;
	}

	Locker clocker(guild, player);

	uint64 targetID = target->getObjectID();

	if (!guild->hasMember(targetID))
			return;

	guild->setGuildMemberTitle(targetID, title);

	StringIdChatParameter params;
	params.setStringId("@guild:title_self"); // You set %TU's guild title to '%TT'.
	params.setTU(target->getDisplayedName());
	params.setTT(title);
	player->sendSystemMessage(params);

	if (target->isOnline()) {
		params.setStringId("@guild:title_target"); // %TU has set your guild title to '%TT'.
		params.setTU(player->getDisplayedName());
		target->sendSystemMessage(params);
	}

}

void GuildManagerImplementation::sendGuildKickPromptTo(CreatureObject* player, CreatureObject* target) {
	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_MEMBER_REMOVE);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_MEMBER_REMOVE);
	suiBox->setCallback(new GuildMemberRemoveSuiCallback(server));
	suiBox->setPromptTitle("@guild:kick_title"); // Kick From Guild

	UnicodeString text = StringIdManager::instance()->getStringId("@guild:kick_prompt"); // Are you sure you want to kick %TU out of the guild?
	text = text.replaceFirst("%TU", target->getDisplayedName());

	suiBox->setPromptText(text.toString());
	suiBox->setUsingObject(target);
	suiBox->setForceCloseDisabled();
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::kickMember(CreatureObject* player, CreatureObject* target) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	uint64 targetID = target->getObjectID();

	if (guild == NULL || !guild->hasKickPermission(player->getObjectID()) || guild->getGuildLeaderID() == targetID) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	Locker glocker(guild, player);

	if (!guild->hasMember(targetID)) {
		return;
	}

	guild->removeMember(targetID);

	glocker.release();

	Locker clocker(target, player);

	target->setGuildObject(NULL);

	StringIdChatParameter params;
	params.setStringId("@guild:kick_self"); // You remove %TU from %TT.
	params.setTU(target->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	if (target->isOnline()) {
		params.setStringId("@guild:kick_target"); // %TU has removed you from %TT.
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

		PlayerObject* targetGhost = target->getPlayerObject();

		if (targetGhost != NULL) {
			targetGhost->updateInRangeBuildingPermissions();
		}
	}

	String subject = "@guildmail:kick_subject";
	params.setStringId("@guildmail:kick_text"); //%TU has removed %TT from the guild.
	params.setTU(player->getDisplayedName());
	params.setTT(target->getDisplayedName());
	sendGuildMail(subject, params, guild);

	chatManager->sendMail(guild->getGuildName(), subject, params, target->getFirstName());
}

void GuildManagerImplementation::sendMemberPermissionsTo(CreatureObject* player, uint64 targetID, GuildTerminal* guildTerminal) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->isGuildLeader(player)) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	if (!guild->hasMember(targetID))
		return;

	ManagedReference<SceneObject*> target = server->getObject(targetID);
	if (target == NULL || !target->isPlayerCreature())
		return;

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_MEMBER_PERMISSIONS);

	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, SuiWindowType::GUILD_MEMBER_PERMISSIONS);
	listBox->setCallback(new GuildMemberPermissionsResponseSuiCallback(server));
	listBox->setPromptTitle("@guild:permissions_title"); // Guild Member Permissions

	UnicodeString text = StringIdManager::instance()->getStringId("@guild:permissions_prompt"); // These are the current permissions set for %TU. Permissions preceded by '+' are currently allowed, and those preceded by '-' are not. Select a permission and press Ok to toggle it.
	text = text.replaceFirst("%TU", target->getDisplayedName());

	listBox->setPromptText(text.toString());
	listBox->setUsingObject(guildTerminal);
	listBox->setForceCloseDistance(32);
	listBox->setCancelButton(true, "@cancel");

	listBox->addMenuItem(String("@guild:permission_mail_") + (guild->hasMailPermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_sponsor_") + (guild->hasSponsorPermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_title_") + (guild->hasTitlePermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_accept_") + (guild->hasAcceptPermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_kick_") + (guild->hasKickPermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_war_") + (guild->hasWarPermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_namechange_") + (guild->hasNamePermission(targetID) ? "yes" : "no"), targetID);
	listBox->addMenuItem(String("@guild:permission_disband_") + (guild->hasDisbandPermission(targetID) ? "yes" : "no"), targetID);

	player->getPlayerObject()->addSuiBox(listBox);
	player->sendMessage(listBox->generateMessage());
}

void GuildManagerImplementation::toggleGuildPermission(CreatureObject* player, uint64 targetID, int permissionIndex, GuildTerminal* guildTerminal) {

	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->isGuildLeader(player) || player->getObjectID() == targetID) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	Locker clocker(guild, player);

	if (!guild->hasMember(targetID))
		return;

	switch (permissionIndex) {
	case 0: //mail
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_MAIL);
		break;
	case 1: //sponsor
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_SPONSOR);
		break;
	case 2: //title
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_TITLE);
		break;
	case 3: //accept
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_ACCEPT);
		break;
	case 4: //kick
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_KICK);
		break;
	case 5: //war
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_WAR);
		break;
	case 6: //namechange
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_NAME);
		break;
	case 7: //disband
		guild->toggleMemberPermission(targetID, GuildObject::PERMISSION_DISBAND);
		break;
	default:
		return;
	}

	//Resend the permissions sui
	sendMemberPermissionsTo(player, targetID, guildTerminal);
}

void GuildManagerImplementation::sendGuildSponsorTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	if (!guild->hasSponsorPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_SPONSOR);

	ManagedReference<SuiInputBox*> suiBox = new SuiInputBox(player, SuiWindowType::GUILD_SPONSOR);
	suiBox->setCallback(new GuildSponsorSuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsor_title"); // Sponsor for Membership
	suiBox->setPromptText("@guild:sponsor_prompt"); // Enter the name of the person to sponsor for membership. The person must be nearby.
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@cancel");

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::sponsorPlayer(CreatureObject* player, const String& playerName) {
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL)
		return;

	if (!guild->hasSponsorPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	if ((guild->getTotalMembers() + guild->getSponsoredPlayerCount()) >= maximumMembers) {
		player->sendSystemMessage("@guild:sponsor_fail_full"); // No more members may be sponsored, as the guild is already full.
		return;
	}

	ManagedReference<CreatureObject*> target = playerManager->getPlayer(playerName);

	if (target == NULL) {
		player->sendSystemMessage("@guild:sponsor_not_found"); // The specified person to sponsor could not be found nearby.
		return;
	}

	Locker _lock(target, player);

	if (!target->isOnline() || !player->isInRange(target, 32)) {
		player->sendSystemMessage("@guild:sponsor_not_found"); // The specified person to sponsor could not be found nearby.
		return;
	}

	if (target->isInGuild()) {
		StringIdChatParameter params;
		params.setTU(target);
		params.setStringId("@guild:sponsor_already_in_guild"); // %TU is already in a guild.
		player->sendSystemMessage(params);
		return;
	}

	StringIdChatParameter params;
	params.setStringId("@guild:sponsor_self"); // You sponsor %TU for membership in %TT.
	params.setTU(target);
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	target->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_SPONSOR_VERIFY);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(target, SuiWindowType::GUILD_SPONSOR_VERIFY);
	suiBox->setCallback(new GuildSponsorVerifySuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsor_verify_title"); // Sponsored For Guild Membership

	UnicodeString text = StringIdManager::instance()->getStringId("@guild:sponsor_verify_prompt"); // %TU wishes to sponsor you for membership in %TT. Accepting this will cancel your sponsorship for any other guilds. Do you accept sponsorship?
	text = text.replaceFirst("%TU", player->getDisplayedName());
	text = text.replaceFirst("%TT", guild->getGuildName());

	suiBox->setPromptText(text.toString());
	suiBox->setUsingObject(player);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	target->getPlayerObject()->addSuiBox(suiBox);
	target->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::acceptSponsorshipRequest(CreatureObject* player, CreatureObject* target) {
	Locker _lock(player, target);

	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL)
		return;

	uint64 targetID = target->getObjectID();

	StringIdChatParameter params;
	params.setStringId("@guild:sponsor_accept"); // %TU has accepted your sponsorship
	params.setTU(targetID);
	player->sendSystemMessage(params);

	params.clear();

	params.setStringId("@guild:sponsor_target"); // %TU has sponsored you for membership in %TT.
	params.setTU(player->getObjectID());
	params.setTT(guild->getGuildName());
	target->sendSystemMessage(params);

	if (isSponsoredPlayer(targetID)) {
		ManagedReference<GuildObject*> oldGuild = getSponsoredGuild(targetID);

		if (oldGuild != NULL) {
			oldGuild->removeSponsoredPlayer(targetID);
		}

		removeSponsoredPlayer(targetID);
	}

	addSponsoredPlayer(targetID, guild);
	guild->addSponsoredPlayer(targetID);

	//Send emails
	params.setStringId("@guildmail:sponsor_text"); // %TU has sponsored %TT for membership in the guild.
	params.setTU(player->getDisplayedName());
	params.setTT(target->getDisplayedName());

	sendGuildMail("@guildmail:sponsor_subject", params, guild);
}

void GuildManagerImplementation::sendGuildSponsoredListTo(CreatureObject* player, GuildObject* guild, GuildTerminal* guildTerminal) {
	if (guild == NULL)
		return;

	Locker _lock(guild);

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_SPONSORED_LIST);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_SPONSORED_LIST);
	suiBox->setCallback(new GuildSponsoredListSuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsored_title"); // Sponsored for Membership
	suiBox->setPromptText("@guild:sponsored_prompt"); // These are the people currently sponsored for membership in the guild. If you have permission, you may select them from the list and press Ok to accept or decline their membership.
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);
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

void GuildManagerImplementation::sendGuildSponsoredOptionsTo(CreatureObject* player, GuildObject* guild, uint64 playerID, GuildTerminal* guildTerminal) {
	if (guild == NULL) {
		return;
	}

	ManagedReference<SceneObject*> target = server->getObject(playerID);

	if (target == NULL || !target->isPlayerCreature())
		return;

	Locker _lock(guild);

	if (!guild->hasAcceptPermission(player->getObjectID()) || !guild->hasSponsoredPlayer(playerID)) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_SPONSORED_OPTIONS);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_SPONSORED_OPTIONS);
	suiBox->setCallback(new GuildSponsoredOptionsSuiCallback(server));
	suiBox->setPromptTitle("@guild:sponsored_options_title"); // Sponsored For Membership

	UnicodeString text = StringIdManager::instance()->getStringId("@guild:sponsored_options_prompt"); // Sponsored for membership: %TU. You may accept them into the guild, decline their membership, or cancel to leave them unchanged for now.
	text = text.replaceFirst("%TU", target->getDisplayedName());

	suiBox->setPromptText(text.toString());
	suiBox->setUsingObject(guildTerminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@cancel");

	suiBox->addMenuItem("@guild:accept", playerID); // Accept
	suiBox->addMenuItem("@guild:decline", playerID); // Decline

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::acceptSponsoredPlayer(CreatureObject* player, uint64 targetID) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SceneObject*> obj = server->getObject(targetID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* target = cast<CreatureObject*>( obj.get());

	Locker _lock(target, player);

	if (target->isInGuild()) {
		player->sendSystemMessage("@guild:sponsor_already_in_guild"); // %TU is already in a guild.
		return;
	}

	StringIdChatParameter params;
	params.setStringId("@guild:accept_self"); // You accept %TU for membership in %TT.
	params.setTU(target->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	params.setStringId("@guildmail:accept_text"); // %TU has accepted %TT into the guild as a member.
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

		PlayerObject* targetGhost = target->getPlayerObject();

		if (targetGhost != NULL) {
			targetGhost->updateInRangeBuildingPermissions();
		}
	}

	params.setStringId("@guildmail:accept_target_text"); // %TU has accepted you into %TT as a member.
	chatManager->sendMail(guild->getGuildName(), "@guildmail:accept_target_subject", params, target->getFirstName());
}

void GuildManagerImplementation::declineSponsoredPlayer(CreatureObject* player, uint64 targetID) {
	ManagedReference<GuildObject*> guild = player->getGuildObject();

	if (guild == NULL || !guild->hasAcceptPermission(player->getObjectID())) {
		player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SceneObject*> obj = server->getObject(targetID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* target = cast<CreatureObject*>( obj.get());

	StringIdChatParameter params;
	params.setStringId("@guild:decline_self"); // You decline %TU for membership in %TT.
	params.setTU(target->getDisplayedName());
	params.setTT(guild->getGuildName());
	player->sendSystemMessage(params);

	params.setStringId("@guildmail:decline_text"); // %TU has turned down %TT for membership in the guild.
	params.setTU(player->getDisplayedName());
	params.setTT(target->getDisplayedName());
	sendGuildMail("@guildmail:decline_subject", params, guild);

	params.setTT(guild->getGuildName());

	if (target->isOnline()) {
		params.setStringId("@guild:decline_target"); // %TU has declined your membership in %TT.
		target->sendSystemMessage(params);
	}

	params.setStringId("@guildmail:decline_target_text"); // %TU has declined your sponsorship for %TT.
	chatManager->sendMail(guild->getGuildName(), "@guildmail:decline_target_subject", params, target->getFirstName());
}

void GuildManagerImplementation::sendGuildWarStatusTo(CreatureObject* player, GuildObject* guild, GuildTerminal* terminal) {
	if (guild == NULL)
		return;

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_WAR_LIST);

	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::GUILD_WAR_LIST);
	listbox->setPromptTitle("@guild:enemies_title"); // Guild Enemies
	listbox->setPromptText("@guild:enemies_prompt");
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(32);
	listbox->setCallback(new GuildAddEnemySuiCallback(server, guild));

	listbox->addMenuItem("@guild:add_enemy", 0); // Add New Enemy;

	guild->wlock();
	VectorMap<uint64, byte> waringGuilds = *guild->getWaringGuilds();
	guild->unlock();

	for (int i = 0; i < waringGuilds.size(); ++i) {
		VectorMapEntry<uint64, byte>* entry = &waringGuilds.elementAt(i);

		ManagedReference<SceneObject*> obj = server->getObject(entry->getKey());

		if (obj == NULL || !obj->isGuildObject())
			continue;

		GuildObject* waringGuild = obj.castTo<GuildObject*>();

		Locker _lock(waringGuild);

		String listing;
		listing += (char) entry->getValue();

		listbox->addMenuItem(listing + " " + waringGuild->getGuildName() + " <" + waringGuild->getGuildAbbrev() + ">", entry->getKey());
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost != NULL)
		ghost->addSuiBox(listbox);

	player->sendMessage(listbox->generateMessage());
}

void GuildManagerImplementation::promptAddNewEnemy(CreatureObject* creature, GuildObject* guild, SceneObject* terminal) {
	if (guild == NULL || !guild->hasWarPermission(creature->getObjectID())) {
		creature->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	creature->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_WAR_ENTER_NAME);

	ManagedReference<SuiInputBox*> box = new SuiInputBox(creature, SuiWindowType::GUILD_WAR_ENTER_NAME);
	box->setPromptTitle("@guild:war_enemy_name_title"); // Declare War
	box->setPromptText("@guild:war_enemy_name_prompt"); // Enter a guild name or abbreviation to declare war upon.
	box->setCancelButton(true, "@cancel");
	box->setUsingObject(terminal);
	box->setForceCloseDistance(32);
	box->setCallback(new GuildWarEnemyNameSuiCallback(server, guild));

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL)
		ghost->addSuiBox(box);

	creature->sendMessage(box->generateMessage());
}

void GuildManagerImplementation::declareWarByName(CreatureObject* creature, GuildObject* guild, const String& search) {
	if (guild == NULL || !guild->hasWarPermission(creature->getObjectID())) {
		creature->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	ManagedReference<GuildObject*> waringGuild = guildList.get(search);

	if (waringGuild == NULL) {
		waringGuild = getGuildFromAbbrev(search);
	}

	if (waringGuild == NULL) {
		creature->sendSystemMessage("@guild:war_fail_no_such_guild"); // No guild found by that name.
		return;
	}

	toggleWarStatus(creature, guild, waringGuild->getObjectID());
}

void GuildManagerImplementation::toggleWarStatus(CreatureObject* creature, GuildObject* guild, uint64 guildoid) {
	if (guild == NULL || !guild->hasWarPermission(creature->getObjectID())) {
		creature->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
		return;
	}

	ManagedReference<SceneObject*> obj = server->getObject(guildoid);

	if (obj == NULL || !obj->isGuildObject())
		return;

	GuildObject* waringGuild = obj.castTo<GuildObject*>();

	if (guild->hasDeclaredWarOn(guildoid)) {
		//This means that they have no mutual war
		guild->setWarStatus(guildoid, GuildObject::WAR_NONE);
		waringGuild->setWarStatus(guild->getObjectID(), GuildObject::WAR_NONE);

	} else if (guild->hasDeclaredWarBy(guildoid)) {
		//They have received a war declaration, and are accepting it.
		guild->setWarStatus(guildoid, GuildObject::WAR_MUTUAL);
		waringGuild->setWarStatus(guild->getObjectID(), GuildObject::WAR_MUTUAL);

		//Both guilds are now at war with each other, update everyone.
		updateWarStatusToWaringGuild(guild, waringGuild);

	} else if (guild->isAtWarWith(guildoid)) {
		//Both guilds are at war, but this guild is rescinding their declaration.
		guild->setWarStatus(guildoid, GuildObject::WAR_IN);
		waringGuild->setWarStatus(guild->getObjectID(), GuildObject::WAR_OUT);

		//Both guilds are no longer at war with each other, update everyone.
		updateWarStatusToWaringGuild(guild, waringGuild);

	} else {
		//Neither guild is at war, but this guild is declaring.
		guild->setWarStatus(guildoid, GuildObject::WAR_OUT);
		waringGuild->setWarStatus(guild->getObjectID(), GuildObject::WAR_IN);
	}
}

void GuildManagerImplementation::updateWarStatusToWaringGuild(GuildObject* guild, GuildObject* waringGuild) {
	Reference<UpdateWarStatusTask*> task = new UpdateWarStatusTask(server, guild, waringGuild);
	task->schedule(10);
}

void GuildManagerImplementation::sendBaselinesTo(CreatureObject* player) {
	SceneObjectCreateMessage* create = new SceneObjectCreateMessage(_this.getReferenceUnsafeStaticCast()->_getObjectID(), 0x7D40E2E6);
	player->sendMessage(create);

	Locker _lock(_this.getReferenceUnsafeStaticCast());

	GuildObjectMessage3* gild3 = new GuildObjectMessage3(&guildList, _this.getReferenceUnsafeStaticCast()->_getObjectID());
	player->sendMessage(gild3);

	_lock.release();

	GuildObjectMessage6* gild6 = new GuildObjectMessage6(_this.getReferenceUnsafeStaticCast()->_getObjectID());
	player->sendMessage(gild6);

	SceneObjectCloseMessage* close = new SceneObjectCloseMessage(_this.getReferenceUnsafeStaticCast()->_getObjectID());
	player->sendMessage(close);
}

void GuildManagerImplementation::sendGuildListTo(CreatureObject* player, const String& guildFilter) {
	if (guildFilter.isEmpty()) {
		player->sendSystemMessage("Please provide a guild filter as an argument to minimize the search results.");
		return;
	}

	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::ADMIN_GUILDLIST);

	Locker _lock(_this.getReferenceUnsafeStaticCast());

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

		if (guildName.toLowerCase().contains(guildFilter.toLowerCase()) || guildAbbrev.toLowerCase().contains(guildFilter.toLowerCase()))
			listBox->addMenuItem(guildName + " <" + guildAbbrev + ">", guildObjectID);

		if (listBox->getMenuSize() == 100)
			break;
	}

	if (listBox->getMenuSize() < 1) {
		player->sendSystemMessage("No guilds were found that matched the guild filter: " + guildFilter + ".");
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

void GuildManagerImplementation::sendAdminGuildInfoTo(CreatureObject* player, GuildObject* guild) {
	if (!player->getPlayerObject()->isPrivileged())
		return;

	Locker _lock(_this.getReferenceUnsafeStaticCast());

	Locker locker(guild);

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::ADMIN_GUILDINFO);

	box->setPromptTitle("Guild Info");

	StringBuffer promptText;
	promptText << "Guild Name: " << guild->getGuildName() << " <" << guild->getGuildAbbrev() << ">" << endl;
	promptText << "Guild ID: " << guild->getGuildID() << endl;

	uint64 leaderID = guild->getGuildLeaderID();
	CreatureObject* leader = player->getZoneServer()->getObject(leaderID).castTo<CreatureObject*>();

	promptText << "Guild Leader: " << (leader == NULL ? "None" : leader->getFirstName()) << endl;

	Time* updateTime = guild->getNextUpdateTime();
	promptText << "Next guild update: " << updateTime->getFormattedTime() << endl;

	bool renamePending = guild->isRenamePending();
	promptText << "Rename Pending?: " << (renamePending ? "Yes" : "No") << endl;

	if (renamePending) {
		promptText << "Pending Name: " << guild->getPendingNewName() << " <" << guild->getPendingNewAbbrev() << ">" << endl;

		uint64 renamerID = guild->getRenamerID();
		CreatureObject* renamer;
		if (renamerID == leaderID) {
			promptText << "Renamer: " << (leader == NULL ? "None" : leader->getFirstName()) << endl;
		} else {
			renamer = player->getZoneServer()->getObject(renamerID).castTo<CreatureObject*>();
			promptText << "Renamer: " << (renamer == NULL ? "None" : renamer->getFirstName()) << endl;
		}
	}

	promptText << endl << "Guild Members (" << guild->getTotalMembers() << "):" << endl;

	GuildMemberInfo* leaderInfo = guild->getMember(leaderID);
	if (leader != NULL && leaderInfo != NULL) {
		promptText << "\t" << leader->getFirstName();

		String leaderTitle = leaderInfo->getGuildTitle();
		if (leaderTitle.isEmpty()) {
			promptText << endl;
		} else {
			promptText << " (" << leaderTitle << ")" << endl;
		}

		uint8 perms = leaderInfo->getPermissions();
		addPermsToAdminGuildInfo(perms, promptText);
	}

	for (int i = 0; i < guild->getTotalMembers(); i++) {
		uint64 memberID = guild->getMember(i);

		if (memberID == leaderID) {
			continue;
		}

		CreatureObject* member = player->getZoneServer()->getObject(memberID).castTo<CreatureObject*>();
		GuildMemberInfo* memberInfo = guild->getMember(memberID);

		if (member != NULL && memberInfo != NULL) {
			promptText << "\t" << member->getFirstName();

			String title = memberInfo->getGuildTitle();
			if (title.isEmpty()) {
				promptText << endl;
			} else {
				promptText << " (" << title << ")" << endl;
			}

			uint8 perms = memberInfo->getPermissions();
			addPermsToAdminGuildInfo(perms, promptText);
		}
	}

	promptText << endl << "Sponsored Players (" << guild->getSponsoredPlayerCount() << "):" << endl;

	for (int i = 0; i < guild->getSponsoredPlayerCount(); i++) {
		uint64 sponsoredID = guild->getSponsoredPlayer(i);

		CreatureObject* sponsored = player->getZoneServer()->getObject(sponsoredID).castTo<CreatureObject*>();

		if (sponsored != NULL) {

			promptText << "\t" << sponsored->getFirstName() << endl;
		}
	}

	VectorMap<uint64, byte>* waringGuilds = guild->getWaringGuilds();
	promptText << endl << "Waring Guilds (" << waringGuilds->size() << "):" << endl;

	for (int i = 0; i < waringGuilds->size(); i++) {
		uint64 warGuildID = waringGuilds->elementAt(i).getKey();

		GuildObject* warGuild = player->getZoneServer()->getObject(warGuildID).castTo<GuildObject*>();
		byte status = guild->getWarStatus(warGuildID);
		String statusString;

		if (warGuild != NULL) {
			promptText << "\t" << (char) status << "" << warGuild->getGuildName() << " <" << warGuild->getGuildAbbrev() << ">" << endl;
		}
	}

	box->setPromptText(promptText.toString());

	player->sendMessage(box->generateMessage());

	return;
}

void GuildManagerImplementation::addPermsToAdminGuildInfo(uint8 perms, StringBuffer& text) {
	text << "\t\tPerms: ";

	if (perms == 0x00) {
		text << "None" << endl;
	} else if (perms == 0xFF) {
		text << "All" << endl;
	} else {
		if (perms & 0x01) {
			text << "Mail, ";
		}
		if (perms & 0x02) {
			text << "Sponsor, ";
		}
		if (perms & 0x04) {
			text << "Title, ";
		}
		if (perms & 0x08) {
			text << "Accept, ";
		}
		if (perms & 0x10) {
			text << "Kick, ";
		}
		if (perms & 0x20) {
			text << "War, ";
		}
		if (perms & 0x40) {
			text << "Name, ";
		}
		if (perms & 0x80) {
			text << "Disband, ";
		}
		text << endl;
	}
}

void GuildManagerImplementation::leaveGuild(CreatureObject* player, GuildObject* guild) {
	if (guild == NULL)
		return;

	Locker clocker(guild, player);

	StringIdChatParameter params;
	params.setStringId("@guild:leave_self"); // You leave %TU.
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

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != NULL) {
		ghost->updateInRangeBuildingPermissions();
	}

	params.setStringId("@guildmail:leave_text"); // %TU has removed themselves from the guild.
	params.setTU(player->getDisplayedName());

	sendGuildMail("@guildmail:leave_subject", params, guild);
}

void GuildManagerImplementation::sendGuildMail(const String& subject, StringIdChatParameter& body, GuildObject* guild) {
	if (guild == NULL)
		return;

	Reference<GuildMailTask*> task = new GuildMailTask(subject, body, guild);
	task->execute();
}

GuildObject* GuildManagerImplementation::getGuildFromAbbrev(const String& guildAbbrev) {
	Locker _lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < guildList.size(); ++i) {
		ManagedReference<GuildObject*> guild = guildList.getValueAt(i);

		if (guild == NULL)
			continue;

		Locker clocker(guild, _this.getReferenceUnsafeStaticCast());

		if (guild->getGuildAbbrev() == guildAbbrev)
			return guild;
	}

	return NULL;
}

void GuildManagerImplementation::toggleElection(GuildObject* guild, CreatureObject* player) {
	Locker locker(guild);

	StringIdChatParameter params;

	if (guild->isElectionEnabled()) {
		guild->resetElection(true);

		player->sendSystemMessage("@guild:vote_elections_closed"); // Elections for the position of guild leader are now closed.

		params.setStringId("@guild:closed_elections_email_body"); // Your guild's election for a new guild leader has been closed by the current guild leader.
		sendGuildMail("@guild:closed_elections_email_subject", params, guild); // Guild Leader Elections Closed!
	} else {
		guild->resetElection(false);
		guild->setElectionState(GuildObject::ELECTION_FIRST_WEEK);

		player->sendSystemMessage("@guild:vote_elections_open"); // Elections for the position of guild leader are now open.

		params.setStringId("@guild:open_elections_email_body"); // Your guild has started an election for a new guild leader! You may vote at the guild terminal in your PA Hall. If you are a full member of the guild, you may opt to run for the position of guild leader by registering at the guild terminal. A new guild leader will be elected in exactly two weeks. The guild member with the most votes at that time will become guild leader.
		sendGuildMail("@guild:open_elections_email_subject", params, guild); // Guild Leader Elections Open!
	}

}

void GuildManagerImplementation::resetElection(GuildObject* guild, CreatureObject* player) {
	Locker locker(guild);

	guild->resetElection(false);
}

void GuildManagerImplementation::registerForElection(GuildObject* guild, CreatureObject* player) {
	Locker locker(guild);

	uint64 playerID = player->getObjectID();

	if (guild->isCandidate(playerID)) {
		player->sendSystemMessage("@guild:vote_register_dupe"); // You are already registered for the guild leader election.
		return;
	}

	guild->addCandidate(playerID);

	player->sendSystemMessage("@guild:vote_register_congrats"); // Congratulations, you are now listed on the ballot for the position of guild leader!
}

void GuildManagerImplementation::unregisterFromElection(GuildObject* guild, CreatureObject* player) {
	Locker locker(guild);

	uint64 playerID = player->getObjectID();

	if (!guild->isCandidate(playerID)) {
		player->sendSystemMessage("@guild:vote_not_registered"); // You aren't registered to run, so you can't unregister.
		return;
	}

	guild->removeCandidate(playerID);

	player->sendSystemMessage("@guild:vote_unregistered"); // You have unregistered from the race.
}

void GuildManagerImplementation::promptCastVote(GuildObject* guild, CreatureObject* player, GuildTerminal* terminal) {
	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_VOTE);

	Locker locker(guild);

	VectorMap<uint64, int>* candidates = guild->getCandidates();

	if (candidates->isEmpty()) {
		player->sendSystemMessage("@guild:vote_no_candidates"); // No one has registered to run for guild leader.
		return;
	}

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::GUILD_VOTE);
	suiBox->setCallback(new GuildVoteSuiCallback(server));
	suiBox->setPromptTitle("@guild:leader_vote_t"); // Place Vote
	suiBox->setPromptText("@guild:leader_vote_d"); // Select your desired candidate from the list below. You may change your vote at any time.
	suiBox->setUsingObject(terminal);
	suiBox->setForceCloseDistance(32);
	suiBox->setCancelButton(true, "@cancel");
	suiBox->addMenuItem("@city/city:null", 0); // None

	for (int i = 0; i < candidates->size(); ++i) {
		VectorMapEntry<uint64, int> entry = candidates->elementAt(i);

		uint64 candidateID = entry.getKey();

		ManagedReference<SceneObject*> obj = server->getObject(candidateID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* candidateCreo = obj.castTo<CreatureObject*>();

		suiBox->addMenuItem(candidateCreo->getDisplayedName(), candidateID);
	}

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void GuildManagerImplementation::castVote(GuildObject* guild, CreatureObject* player, uint64 candidateID) {
	Locker locker(guild);

	if (!guild->isElectionEnabled())
		return;

	uint64 playerID = player->getObjectID();

	if (!guild->hasMember(playerID))
		return;

	if (candidateID != 0 && (!guild->hasMember(candidateID) || !guild->isCandidate(candidateID)))
		return;

	guild->setVote(playerID, candidateID);

	if (candidateID == 0) {
		player->sendSystemMessage("@guild:vote_abstain"); // You have chosen to abstain in this election.
	} else {
		StringIdChatParameter params;
		params.setStringId("@guild:vote_placed"); // Your vote for %TO has been recorded.
		params.setTO(candidateID);
		player->sendSystemMessage(params);
	}
}

void GuildManagerImplementation::viewElectionStandings(GuildObject* guild, CreatureObject* player, GuildTerminal* terminal) {
	player->getPlayerObject()->closeSuiWindowType(SuiWindowType::GUILD_ELECTION_STANDING);

	Locker locker(guild);

	VectorMap<uint64, int>* candidates = guild->getCandidates();

	if (candidates->size() == 0) {
		player->sendSystemMessage("@guild:vote_no_candidates"); // No one has registered to run for guild leader.
		return;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::GUILD_ELECTION_STANDING);
	listbox->setPromptText("@guild:leader_standings_d"); // A complete list of current guild leader candidates and their vote standing follows.
	listbox->setPromptTitle("@guild:leader_standings_t"); // Guild Leader Race Standings
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(32);
	listbox->setCancelButton(true, "@cancel");

	for (int i = 0; i < candidates->size(); ++i) {
		VectorMapEntry<uint64, int>* entry = &candidates->elementAt(i);

		uint64 candidateID = entry->getKey();

		ManagedReference<SceneObject*> candidate = server->getObject(candidateID);

		if (candidate == NULL || !candidate->isPlayerCreature())
			continue;

		listbox->addMenuItem(candidate->getDisplayedName() + " -- Votes: " + String::valueOf(entry->getValue()));
	}

	player->getPlayerObject()->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}
