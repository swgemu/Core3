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

		if (group == NULL) {
			creature->sendSystemMessage("You must be the leader of a band to use that command.");
			return GENERALERROR;
		}

		Reference<CreatureObject*> leader = group->getLeader();

		if (leader == NULL || creature != leader) {
			creature->sendSystemMessage("You must be the band leader to stop the band's song.");
			return GENERALERROR;
		}

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (session == NULL)
			return GENERALERROR;

		if (!session->isPlayingMusic())
			return GENERALERROR;

		creature->unlock();

		try {
			Locker locker(group);

			for (int i = 0; i < group->getGroupSize(); ++i) {
				Reference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == NULL || !groupMember->isPlayingMusic())
					continue;

				Locker clocker(groupMember, group);

				ManagedReference<EntertainingSession*> bandMemberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

				if (bandMemberSession == NULL || !bandMemberSession->isPlayingMusic())
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

			group->setBandSong("");

		} catch (Exception& e) {
			creature->wlock();

			throw;
		}

		creature->wlock();

		return SUCCESS;
	}

};

#endif //STOPBANDCOMMAND_H_
