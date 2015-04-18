/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINCLUSTERSTATUS_H_
#define LOGINCLUSTERSTATUS_H_

#include "engine/engine.h"

#include "../objects/GalaxyList.h"

namespace server {
namespace login {
namespace packets {

class LoginClusterStatus : public BaseMessage {
protected:
	int galaxyCount;
public:
	LoginClusterStatus(uint32 galcnt) : BaseMessage(100) {
		insertShort(0x03);
		insertInt(0x3436AEB6);

		insertInt(galcnt); //Zone Server List Count

		galaxyCount = galcnt;
	}

	LoginClusterStatus* clone() {
		LoginClusterStatus* pack = new LoginClusterStatus(galaxyCount);
		copy(pack, 0);

		pack->doSeq = doSeq;
		pack->doEncr = doEncr;
		pack->doComp = doComp;
		pack->doCRCTest = doCRCTest;

		return pack;
	}

	void addGalaxy(uint32 gid, String& address, uint16 port, uint16 pingport) {
	    insertInt(gid); //Zone Server ID
		
    	insertAscii(address); //IP Address
		
	    insertShort(port); //Zone Server Port
    	insertShort(pingport); //Ping Server Port

    	insertInt(100); //Population
    	insertInt(0x00000CB2);
    	insertInt(0x00000008);
    	insertInt(0xFFFF8F80);
    	insertInt(0x00000002); //status
    	insertByte(0);
	}

	static void parse(Packet* pack) {
		uint16 ackSequence = pack->parseShort();
	}
};

}
}
}

using namespace server::login::packets;
#endif /*LOGINCLUSTERSTATUS_H_*/
