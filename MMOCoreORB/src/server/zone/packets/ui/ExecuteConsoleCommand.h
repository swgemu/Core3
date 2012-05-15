/*
 * ExecuteConsoleCommand.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef EXECUTECONSOLECOMMAND_H_
#define EXECUTECONSOLECOMMAND_H_

class ExecuteConsoleCommand : public BaseMessage {
public:
   ExecuteConsoleCommand(const String& com) : BaseMessage() {
		insertShort(0x01);
		insertInt(0xB1CFCE1C);  // CRC

		insertAscii(com); //Command to execute. With slash. Multiple commands seperated by ;

   }

};

#endif /* EXECUTECONSOLECOMMAND_H_ */
