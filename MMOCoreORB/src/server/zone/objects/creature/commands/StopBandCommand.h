/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPBANDCOMMAND_H_
#define STOPBANDCOMMAND_H_

#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"

class StopBandCommand : public QueueCommand {
public:

	StopBandCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == nullptr)
			return GENERALERROR;

		for (int i = 0; i < group->getGroupSize(); ++i) {
			Reference<CreatureObject*> groupMember = group->getGroupMember(i);

			if (groupMember == nullptr || !groupMember->isPlayingMusic())
				continue;

			Locker clocker(groupMember, creature);

			if (groupMember->isDroidObject()) {
				DroidObject* droid = cast<DroidObject*>(groupMember.get());

				if (droid == nullptr)
					continue;

				auto module = droid->getModule("playback_module");

				if (module == nullptr)
					continue;

				DroidPlaybackModuleDataComponent* playbackModule = cast<DroidPlaybackModuleDataComponent*>(module.get());

				if (playbackModule == nullptr)
					continue;

				playbackModule->deactivate();

				continue;
			}

			bool isLeader = false;

			if (groupMember == creature)
				isLeader = true;

			ManagedReference<EntertainingSession*> bandMemberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

			if (bandMemberSession == nullptr || !bandMemberSession->isPlayingMusic())
				continue;

			bandMemberSession->stopMusic(false, true, isLeader);
		}

		return SUCCESS;
	}

};

#endif //STOPBANDCOMMAND_H_
