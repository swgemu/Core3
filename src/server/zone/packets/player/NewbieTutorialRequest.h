/*
 * NewbieTutorialRequest.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef NEWBIETUTORIALREQUEST_H_
#define NEWBIETUTORIALREQUEST_H_

class NewbieTutorialRequest : public BaseMessage {
public:
   NewbieTutorialRequest(const String& test) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x90DD61AF);  // CRC

		insertAscii(test); //try openContainer openStatMigration etc.
   }

};

#endif /* NEWBIETUTORIALREQUEST_H_ */
