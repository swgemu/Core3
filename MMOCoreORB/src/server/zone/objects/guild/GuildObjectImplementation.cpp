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
#include "server/zone/objects/guild/GuildUpdateEvent.h"

#define EVENT_RANDOM_MAX_DELTA 3600 * 2 /*2 hours*/

void GuildObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	transferPending = false;
}

void GuildObjectImplementation::rescheduleUpdateEvent(uint32 seconds) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (guildUpdateEvent == NULL) {
		guildUpdateEvent = new GuildUpdateEvent(_this.getReferenceUnsafeStaticCast(), ServerCore::getZoneServer());
	} else if (guildUpdateEvent->isScheduled()) {
		guildUpdateEvent->cancel();
	}

	seconds += System::random(EVENT_RANDOM_MAX_DELTA);

	guildUpdateEvent->schedule(seconds * 1000);

	Core::getTaskManager()->getNextExecutionTime(guildUpdateEvent, nextUpdateTime);
}

void GuildObjectImplementation::sendBaselinesTo(SceneObject* player) {
}

void GuildObjectImplementation::broadcastMessage(BaseMessage* msg) {
}

void GuildObjectImplementation::broadcastMessage(CreatureObject* player, BaseMessage* msg, bool sendSelf) {
}

void GuildObjectImplementation::addMember(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	GuildMemberInfo gmi(playerID);
	guildMembers.put(playerID, gmi);
}

void GuildObjectImplementation::removeMember(uint64 playerID) {
	guildMembers.drop(playerID);

	if (candidates.contains(playerID)) {
		removeCandidate(playerID);
	}

	if (votes.contains(playerID)) {
		setVote(playerID, 0);
		votes.drop(playerID);
	}

	if (playerID == guildLeaderID) {
		guildLeaderID = 0;
	}
}

bool GuildObjectImplementation::hasMember(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	return guildMembers.contains(playerID);
}

uint64 GuildObjectImplementation::getMember(int index) {
	return guildMembers.get(index).getPlayerID();
}

GuildMemberInfo* GuildObjectImplementation::getMember(uint64 playerID) {
	return &guildMembers.get(playerID);
}

void GuildObjectImplementation::setGuildMemberTitle(uint64 playerID, const String& title) {
	GuildMemberInfo* gmi = getMember(playerID);
	if (gmi == NULL)
		return;

	gmi->setGuildTitle(title);
}

String GuildObjectImplementation::getGuildMemberTitle(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	GuildMemberInfo* gmi = getMember(playerID);
	if (gmi == NULL)
		return "";

	return gmi->getGuildTitle();
}

bool GuildObjectImplementation::isInWaringGuild(CreatureObject* creature) {
	ManagedReference<GuildObject*> attackerGuild = creature->getGuildObject().get();

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

bool GuildObjectImplementation::hasMailPermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_MAIL);
}

bool GuildObjectImplementation::hasSponsorPermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_SPONSOR);
}

bool GuildObjectImplementation::hasAcceptPermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_ACCEPT);
}

bool GuildObjectImplementation::hasKickPermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_KICK);
}

bool GuildObjectImplementation::hasDisbandPermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_DISBAND);
}

bool GuildObjectImplementation::hasNamePermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_NAME);
}

bool GuildObjectImplementation::hasTitlePermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_TITLE);
}

bool GuildObjectImplementation::hasWarPermission(uint64 playerID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (!hasMember(playerID))
		return false;

	GuildMemberInfo* gmi = getMember(playerID);

	return gmi->hasPermission(GuildObject::PERMISSION_WAR);
}

void GuildObjectImplementation::toggleMemberPermission(uint64 playerID, uint8 permission) {
	GuildMemberInfo* gmi = getMember(playerID);
	if (gmi == NULL)
		return;

	gmi->togglePermission(permission);
}

void GuildObjectImplementation::removeCandidate(uint64 candidateoid) {
	candidates.drop(candidateoid);

	// Remove votes for the candidate
	for (int i = votes.size() - 1; i >= 0; --i) {
		if (votes.get(i) == candidateoid) {
			votes.drop(votes.elementAt(i).getKey());
		}
	}
}

uint64 GuildObjectImplementation::getMemberWithHighestPermission() {
	uint64 highestMember = 0;
	uint8 highestPerm = 0;

	for (int i = 0; i < guildMembers.size(); i++) {
		GuildMemberInfo* gmi = &guildMembers.get(i);

		if (gmi == NULL)
			continue;

		uint8 perm = gmi->getPermissions();

		if (perm > highestPerm) {
			highestPerm = perm;
			highestMember = gmi->getPlayerID();
		}
	}

	return highestMember;
}
