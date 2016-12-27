/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERSYSGROUPCOMMAND_H_
#define SERVERSYSGROUPCOMMAND_H_

class ServerSysGroupCommand : public QueueCommand {
public:

	ServerSysGroupCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isPlayerCreature()) {
			ManagedReference<CreatureObject*> player = creature;
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group == NULL) {
				player->sendSystemMessage("@error_message:not_grouped");
				return GENERALERROR;
			}

			if (group->getLeader() == player) {
				for (int i = 0; i < group->getGroupSize(); i++) {
					CreatureObject* member = group->getGroupMember(i);
					if (member->isPlayerCreature()) {
						member->sendSystemMessage("Squad Leader " + player->getFirstName() + ": " + arguments.toString());
					}
				}
			} else {
				player->sendSystemMessage("@error_message:not_group_leader");
			}
		}

		return SUCCESS;
	}

};

#endif //SERVERSYSGROUPCOMMAND_H_
