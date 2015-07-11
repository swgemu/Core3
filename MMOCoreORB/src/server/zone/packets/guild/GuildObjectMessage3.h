/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDOBJECTMESSAGE3_H_
#define GUILDOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"
#include "server/zone/objects/scene/variables/DeltaSet.h"

class GuildObjectMessage3 : public BaseLineMessage {
public:
	GuildObjectMessage3(DeltaSet<String, ManagedReference<GuildObject*> >* guildList, uint64 oid)
			: BaseLineMessage(oid, 0x47494C44, 3, 0x05) {

		insertFloat(1);
		insertAscii("String_id_table");
		insertInt(0);
		insertAscii("");
		insertUnicode("");
		insertInt(0);

		guildList->insertToMessage(this);

		setSize();
	}
};
#endif /*GUILDOBJECTMESSAGE3_H_*/
