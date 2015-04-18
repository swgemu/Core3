/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENUMERATECHARACTERID_H_
#define ENUMERATECHARACTERID_H_

#include "engine/engine.h"
#include "server/login/account/Account.h"
#include "../objects/CharacterList.h"

class EnumerateCharacterID : public BaseMessage {
public:
	 EnumerateCharacterID(Account* account) : BaseMessage(100) {
		insertShort(0x02);
		insertInt(0x65EA4574);

		CharacterList* characters = account->getCharacterList();

	    insertInt(characters->size()); //Character List Count
	    for (int i = 0; i < characters->size(); ++i) {
	    	CharacterListEntry* entry = &characters->get(i);
			GalaxyBanEntry* galaxyBan = account->getGalaxyBan(entry->getGalaxyID());
	    	String name = entry->getFullName();
	    	if(galaxyBan != NULL)
	    		name += " \\#FF0000(GALAXY BAN)";
	    	else if(entry->isBanned())
	    		name += " \\#FF0000(BANNED)";
	    	insertUnicode(name);

	    	insertInt(entry->getRace()); //Player Race CRC
	    	insertLong(entry->getObjectID()); //Player ID

	    	insertInt(entry->getGalaxyID()); //Server ID That Character Is On
	    	insertInt(0x00000001); // server status?
	    }
	}

	static void parse(Packet* pack) {
		uint16 ackSequence = pack->parseShort();
	}

};
#endif /*ENUMERATECHARACTERID_H_*/
