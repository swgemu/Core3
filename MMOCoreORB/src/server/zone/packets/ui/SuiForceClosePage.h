/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SUIFORCECLOSEPAGE_H_
#define SUIFORCECLOSEPAGE_H_

#include "engine/service/proto/BaseMessage.h"

class SuiForceClosePage : public BaseMessage {
public:
   SuiForceClosePage(uint32 pageID) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x990B5DE0);  // CRC
		
		insertInt(pageID);
   }

};

#endif /*SUIFORCECLOSEPAGE_H_*/
