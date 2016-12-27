#ifndef SUIUPDATEPAGEMESSAGE_H_
#define SUIUPDATEPAGEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/player/sui/SuiPageData.h"

class SuiUpdatePageMessage : public BaseMessage {

public:
	SuiUpdatePageMessage(SuiPageData* sui) {
		insertShort(0x02);
		insertInt(0x5F3342F6);

		sui->toBinaryStream(this);

		setCompression(true);
	}
};

#endif
