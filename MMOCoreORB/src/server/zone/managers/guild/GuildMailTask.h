/*
 * GuildMailTask.h
 *
 *  Created on: Jan 21, 2015
 *      Author: TheAnswer
 */

#ifndef GUILDMAILTASK_H_
#define GUILDMAILTASK_H_
#include "server/zone/managers/player/PlayerManager.h"

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

        PlayerManager* playerManager = guild->getZoneServer()->getPlayerManager();
        
        const String& guildName = guild->getGuildName();
        
		for (int i = 0; i < memberList->size(); ++i) {
			GuildMemberInfo* gmi = &memberList->get(i);

			if (gmi == NULL)
				continue;

            String name = playerManager->getPlayerName(gmi->getPlayerID());
            if (name.isEmpty())
                continue;

			guild->getZoneServer()->getChatManager()->sendMail(guildName, subject, body, name);
		}
	}
};


#endif /* GUILDMAILTASK_H_ */
