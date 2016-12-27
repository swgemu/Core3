/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINENUMCLUSTER_H_
#define LOGINENUMCLUSTER_H_

#include "engine/service/proto/BaseMessage.h"

namespace server {
namespace login {
namespace packets {

class LoginEnumCluster : public BaseMessage {
protected:
	int galaxyCount;
public:
	LoginEnumCluster(uint32 galcnt) : BaseMessage(100) {
		insertShort(0x02);
		insertInt(0xC11C63B9);
		
		insertInt(galcnt); //Galaxy count

		galaxyCount = galcnt;
	}

	LoginEnumCluster* clone() {
		LoginEnumCluster* pack = new LoginEnumCluster(galaxyCount);
		copy(pack, 0);

		pack->doSeq = doSeq;
		pack->doEncr = doEncr;
		pack->doComp = doComp;
		pack->doCRCTest = doCRCTest;

		return pack;
	}

	void addGalaxy(uint32 gid, String& name) {
	    insertInt(gid); //Zone Server ID

    	insertAscii(name); //IP Address

    	insertInt(0xFFFF8F80);
	}

	void finish() {
		insertInt(0x00000008);
	}

	static void parse(Packet* pack) {
		uint16 ackSequence = pack->parseShort();
	}
	
};

}
}
}

using namespace server::login::packets;

#endif /*LOGINENUMCLUSTER_H_*/
