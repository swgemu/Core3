/*
 * LaunchBrowserMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef LAUNCHBROWSERMESSAGE_H_
#define LAUNCHBROWSERMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class LaunchBrowserMessage : public BaseMessage {
public:
   LaunchBrowserMessage(const String& url) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x8DE7E213);  // CRC

		insertAscii(url); //url. minus the http.
   }

};

#endif /* LAUNCHBROWSERMESSAGE_H_ */
