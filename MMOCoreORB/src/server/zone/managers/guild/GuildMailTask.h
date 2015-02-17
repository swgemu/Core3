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
	}

	void run() {
		Locker locker(guild);

		GuildMemberList* memberList = guild->getGuildMemberList();

		if (memberList == NULL)
			return;

		for (int i = 0; i < memberList->size(); ++i) {
			GuildMemberInfo* gmi = &memberList->get(i);

			if (gmi == NULL)
				continue;

			ManagedReference<SceneObject*> obj = guild->getZoneServer()->getObject(gmi->getPlayerID());

			if (obj == NULL || !obj->isPlayerCreature())
				continue;

			CreatureObject* recipient = cast<CreatureObject*>( obj.get());

			guild->getZoneServer()->getChatManager()->sendMail(guild->getGuildName(), subject, body, recipient->getFirstName());
		}
	}
};


#endif /* GUILDMAILTASK_H_ */
