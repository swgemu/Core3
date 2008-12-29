/*
 * NewbieTutorialEnableHudElement.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef NEWBIETUTORIALENABLEHUDELEMENT_H_
#define NEWBIETUTORIALENABLEHUDELEMENT_H_

class NewbieTutorialEnableHudElement : public BaseMessage {
public:
	NewbieTutorialEnableHudElement(const String& element) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xCA375124);  // CRC

		insertAscii(element); //enable all.
		insertInt(1); //??
		insertByte(0); //??


   }

};

#endif /* NEWBIETUTORIALENABLEHUDELEMENT_H_ */
