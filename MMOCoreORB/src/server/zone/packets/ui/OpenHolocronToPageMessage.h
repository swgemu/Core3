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
   OpenHolocronToPageMessage() : BaseMessage() {
		insertShort(0x09);
		insertInt(0x7CB65021);  // CRC

		//send Once to open, once to close.
		insertShort(0); //??


   }

};

#endif /* OPENHOLOCRONTOPAGEMESSAGE_H_ */
