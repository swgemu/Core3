/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDRESPONSEMESSAGE_H_
#define GUILDRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class GuildResponseMessage : public BaseMessage {
public:
    GuildResponseMessage(CreatureObject* creo) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x32263F20);  // CRC
        
		insertLong(creo->getObjectID()); //Object Id to set guild for

		ManagedReference<GuildObject*> guild = creo->getGuildObject().get();
		
		if (guild == NULL)
			insertAscii("");
		else
			insertAscii(guild->getGuildName());
		
		insertShort(0);

		setCompression(true);
	}
	
};

#endif /*GUILDRESPONSEMESSAGE_H_*/
