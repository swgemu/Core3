/*
 * OpenHolocronToPageMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef OPENHOLOCRONTOPAGEMESSAGE_H_
#define OPENHOLOCRONTOPAGEMESSAGE_H_

class OpenHolocronToPageMessage : public BaseMessage {
public:
   OpenHolocronToPageMessage(const String& page) : BaseMessage() {
		insertShort(0x09);
		insertInt(0x7CB65021);  // CRC

		insertAscii(page);
		insertShort(0x00);
   }
};

#endif /* OPENHOLOCRONTOPAGEMESSAGE_H_ */
