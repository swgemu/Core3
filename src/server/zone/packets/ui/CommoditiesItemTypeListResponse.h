/*
 * CommoditiesItemTypeListResponse.h
 *
 *  Created on: Nov 28, 2008
 *      Author: swgemu
 */

#ifndef COMMODITIESITEMTYPELISTRESPONSE_H_
#define COMMODITIESITEMTYPELISTRESPONSE_H_

class CommoditiesItemTypeListResponse : public BaseMessage {
public:
   CommoditiesItemTypeListResponse() : BaseMessage() {
		insertShort(0x02);
		insertInt(0xD4E937FC);  // CRC

		insertAscii("Core3.0");
		insertInt(0);
   }

};

#endif /* COMMODITIESITEMTYPELISTRESPONSE_H_ */
