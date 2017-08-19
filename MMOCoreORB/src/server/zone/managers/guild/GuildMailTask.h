/*
 * GuildMailTask.h
 *
 *  Created on: Jan 21, 2015
 *      Author: TheAnswer
 */

#ifndef GUILDMAILTASK_H_
#define GUILDMAILTASK_H_

class GuildMailTask : public Task {
	ManagedReference<GuildObject*> guild;
	StringIdChatParameter body;
	String subject;

public:
	GuildMailTask(const String& subject, StringIdChatParameter& body,
		GuildObject* guild) : guild(guild), body(body), subject(subject) {

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		Vector<uint64> members;

		Locker locker(guild);

		GuildMemberList* memberList = guild->getGuildMemberList();

		if (memberList == NULL)
			return;

		for (int i = 0; i < memberList->size(); ++i) {
			GuildMemberInfo* gmi = &memberList->get(i);

			if (gmi == NULL)
				continue;

			members.add(gmi->getPlayerID());
		}

		auto guildName = guild->getGuildName();

		locker.release();

		for (const auto& memberID : members) {
			auto firstName = guild->getZoneServer()->getPlayerManager()->getPlayerName(memberID);

			guild->getZoneServer()->getChatManager()->sendMail(guildName, subject, body, firstName);
		}
	}
};


#endif /* GUILDMAILTASK_H_ */
