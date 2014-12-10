/*
 * GuildObjectImplementation.cpp
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/ZoneServer.h"
#include "server/ServerCore.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/guild/GuildMemberInfo.h"
#include "server/zone/objects/guild/RenameGuildTask.h"
#include "server/zone/objects/guild/GuildUpdateEvent.h"

void GuildObjectImplementation::rescheduleUpdateEvent(uint32 seconds) {
	Locker locker(_this.get());

	if (guildUpdateEvent == NULL) {
		guildUpdateEvent = new GuildUpdateEvent(_this.get(), ServerCore::getZoneServer());
	} else if (guildUpdateEvent->isScheduled()) {
		guildUpdateEvent->cancel();
	}

	guildUpdateEvent->schedule(seconds * 1000);

	Core::getTaskManager()->getNextExecutionTime(guildUpdateEvent, nextUpdateTime);
}

void GuildObjectImplementation::rescheduleRename() {
	Locker locker(_this.get());

	if (renamePending) {
		CreatureObject* renamer = server->getZoneServer()->getObject(renamerID).castTo<CreatureObject*>();

		if (renamer == NULL) {
			setRenamePending(false);
		} else {
			RenameGuildTask* renameGuildTask = new RenameGuildTask(renamer, server->getZoneServer(), _this.get());

			if (renameTime.isPast()) {
				renameGuildTask->execute();
			} else {
				renameGuildTask->schedule(renameTime);
			}
		}
	}
}

void GuildObjectImplementation::updateRenameTime(uint64 miliseconds) {
	Locker locker(_this.get());

	renameTime.updateToCurrentTime();
	renameTime.addMiliTime(miliseconds);
}

void GuildObjectImplementation::sendBaselinesTo(SceneObject* player) {
}

void GuildObjectImplementation::broadcastMessage(BaseMessage* msg) {
}

void GuildObjectImplementation::broadcastMessage(CreatureObject* player, BaseMessage* msg, bool sendSelf) {
}

void GuildObjectImplementation::addMember(uint64 playerID) {
	Locker locker(_this.get());

	GuildMemberInfo gmi(playerID);
	guildMembers.put(playerID, gmi);
}

void GuildObjectImplementation::removeMember(uint64 playerID) {
	Locker locker(_this.get());

	guildMembers.drop(playerID);
}

bool GuildObjectImplementation::hasMember(uint64 playerID) {
	Locker locker(_this.get());

	return guildMembers.contains(playerID);
}

bool GuildObjectImplementation::isInWaringGuild(CreatureObject* creature) {
	ManagedReference<GuildObject*> attackerGuild = creature->getGuildObject();

	if (attackerGuild != NULL) {

		try {
			if (isAtWarWith(attackerGuild->getObjectID())) {
				return true;
			}
		} catch (...) {
			error("unreported exception caught in bool GuildObjectImplementation::isInWaringGuild(CreatureObject* creature)");
		}

	}

	return false;
}

bool GuildObjectImplementation::isAtWarWith(unsigned long long guildoid) {
	waringGuildsMutex.rlock();

	bool res = waringGuilds.get(guildoid) == WAR_MUTUAL;

	waringGuildsMutex.runlock();

	return res;
}

uint64 GuildObjectImplementation::getMember(int index) {
	return guildMembers.get(index).getPlayerID();
}

GuildMemberInfo* GuildObjectImplementation::getMember(uint64 playerID) {
	Locker locker(_this.get());

	return &guildMembers.get(playerID);
}

bool GuildObjectImplementation::hasMailPermission(uint64 playerID) {
	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo gmi = guildMembers.get(playerID);

	return gmi.hasPermission(GuildObject::PERMISSION_MAIL);
}

bool GuildObjectImplementation::hasSponsorPermission(uint64 playerID) {
	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_SPONSOR);
}

bool GuildObjectImplementation::hasAcceptPermission(uint64 playerID) {
	Locker locker(_this.get());

	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_ACCEPT);
}

bool GuildObjectImplementation::hasKickPermission(uint64 playerID) {
	Locker locker(_this.get());

	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_KICK);
}

bool GuildObjectImplementation::hasDisbandPermission(uint64 playerID) {
	Locker locker(_this.get());

	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_DISBAND);
}

bool GuildObjectImplementation::hasNamePermission(uint64 playerID) {
	Locker locker(_this.get());

	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_NAME);
}

bool GuildObjectImplementation::hasTitlePermission(uint64 playerID) {
	Locker locker(_this.get());

	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_TITLE);
}

bool GuildObjectImplementation::hasWarPermission(uint64 playerID) {
	Locker locker(_this.get());

	if (!guildMembers.contains(playerID))
		return false;

	GuildMemberInfo* gmi = &guildMembers.get(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_WAR);
}
