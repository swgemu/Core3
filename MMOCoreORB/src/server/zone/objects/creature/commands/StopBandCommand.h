/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPBANDCOMMAND_H_
#define STOPBANDCOMMAND_H_

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

		// TODO: outro

		for (int i = 0; i < group->getGroupSize(); ++i) {
			Reference<CreatureObject*> groupMember = group->getGroupMember(i);

			if (groupMember == nullptr || !groupMember->isPlayingMusic())
				continue;

			Locker clocker(groupMember, creature);

			ManagedReference<EntertainingSession*> bandMemberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

			if (bandMemberSession == nullptr || !bandMemberSession->isPlayingMusic())
				continue;

			if (groupMember == creature) {
				groupMember->sendSystemMessage("@performance:music_stop_band_self"); // You stop the band.
			} else {
				StringIdChatParameter stringID;

				stringID.setTU(creature->getCustomObjectName());
				stringID.setStringId("performance", "music_stop_band_members"); // %TU stops your band.
				groupMember->sendSystemMessage(stringID);
			}

			bandMemberSession->stopPlayingMusic();
		}

		return SUCCESS;
	}

};

#endif //STOPBANDCOMMAND_H_
