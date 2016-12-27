#ifndef GETAUCTIONDETAILSRESPONSEMESSAGE_H_
#define GETAUCTIONDETAILSRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class GetAuctionDetailsResponse : public BaseMessage {
public:
	GetAuctionDetailsResponse(uint64 objectID, const UnicodeString& description) {
		insertShort(0x02);
		insertInt(0xFE0E644B); //GetAuctionDetailsResponse

		insertLong(objectID);

		insertUnicode(description);

		//Insert item attribute list
		insertInt(0); //Number of strings
			insertInt(0); //Ascii string

			System::out << "Sending an GetAuctionDetailsResponse" << endl;
	}
};
		
#endif /*GETAUCTIONDETAILSRESPONSEMESSAGE_H_*/
