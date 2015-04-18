/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDOBJECTMESSAGE6_H_
#define GUILDOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

class GuildObjectMessage6 : public BaseLineMessage {
public:
	GuildObjectMessage6(uint64 oid)
			: BaseLineMessage(oid, 0x47494C44, 6, 0x01) {
		
		insertInt(0x3B);
		
		setSize();
	}
};


#endif /*GUILDOBJECTMESSAGE6_H_*/
