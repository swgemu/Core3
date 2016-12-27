/*
 * GuildObjectDeltaMessage3.h
 *
 *  Created on: Oct 29, 2010
 *      Author: crush
 */

#ifndef GUILDOBJECTDELTAMESSAGE3_H_
#define GUILDOBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/guild/GuildObject.h"

class GuildObjectDeltaMessage3 : public DeltaMessage {
public:
	GuildObjectDeltaMessage3(uint64 oid)
			: DeltaMessage(oid, 0x47494C44, 3) {
	}


	void addGuild(GuildObject* guild) {
		startUpdate(0x04);
		startList(1, 0);
		insertByte(0x01);

		if (guild == NULL) {
			insertAscii("");
			return;
		}

		StringBuffer guildString;
		guildString << guild->getGuildID() << ":" << guild->getGuildAbbrev();
		insertAscii(guildString.toString());
	}

	void removeGuild(GuildObject* guild) {
		startUpdate(0x04);
		startList(1, 0);
		insertByte(0x00);

		if (guild == NULL) {
			insertAscii("");
			return;
		}

		StringBuffer guildString;
		guildString << guild->getGuildID() << ":" << guild->getGuildAbbrev();
		insertAscii(guildString.toString());
	}

	void removeAllGuilds() {
		startUpdate(0x04);
		insertInt(0);
		insertInt(0);
		insertByte(0x03);
	}
};

#endif /* GUILDOBJECTDELTAMESSAGE3_H_ */
