/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef CHATPERSISTENTMESSAGETOCLIENT_H_
#define CHATPERSISTENTMESSAGETOCLIENT_H_

#include "engine/engine.h"
#include "server/chat/ChatParameter.h"
#include "server/chat/StringIdChatParameterVector.h"
#include "server/chat/WaypointChatParameterVector.h"
#include "server/chat/PersistentMessage.h"
#include "server/chat/StringIdChatParameter.h"

class ChatPersistentMessageToClient : public BaseMessage {
	void insertParameters(PersistentMessage* mail) {
		int offset = getOffset();
		insertInt(0); //size

		StringIdChatParameterVector* stringIdParameters = mail->getStringIdParameters();

		for (int i = 0; i < stringIdParameters->size(); ++i) {
			StringIdChatParameter* parameter = &stringIdParameters->get(i);

			if (parameter == NULL)
				continue;

			parameter->insertToMessage(this);
		}

		WaypointChatParameterVector* waypointParameters = mail->getWaypointParameters();

		for (int i = 0; i < waypointParameters->size(); ++i) {
			WaypointChatParameter* parameter = &waypointParameters->get(i);

			if (parameter == NULL)
				continue;

			parameter->insertToMessage(this);
		}

		int size = (getOffset() - offset - 4) / 2;

		insertInt(offset, size);
	}
public:
	ChatPersistentMessageToClient(const String& sender, uint32 mailid, uint8 type, const UnicodeString& subject
			, const UnicodeString& body, uint32 timestamp = 0, char status = 'N') : BaseMessage() {
		insertShort(0x02);
		insertInt(0x08485E17);  // CRC

		insertAscii(sender.toCharArray());
		insertAscii("SWG");
		insertAscii(""); //galaxy
		insertInt(mailid);

		insertByte(type);
		
		if (type == 0x00)
			insertUnicode(body);
		else
			insertInt(0);
		
		insertUnicode(subject);
		
		insertInt(0); //empty chat parameter size ACTUALLY!
		
		insertByte(status); // status 'N' 'U' or 'R'
		
		if (timestamp == 0) {
			Time systemTime;
			timestamp = systemTime.getMiliTime() / 1000;
		}
		insertInt(timestamp);
		
		insertInt(0x00);

		setCompression(true);
	}


	ChatPersistentMessageToClient(const String& sender, uint32 mailid, uint8 type, const UnicodeString& subject
			, StringIdChatParameter& body, uint32 timestamp = 0, char status = 'N') : BaseMessage() {
		insertShort(0x02);
		insertInt(0x08485E17);  // CRC

		insertAscii(sender.toCharArray());
		insertAscii("SWG");
		insertAscii(""); //galaxy
		insertInt(mailid);

		insertByte(type);

		insertInt(0);

		insertUnicode(subject);

		if (type == 0x00)
			body.insertToMessage(this);
		else
			insertInt(0);

		insertByte(status); // status 'N' 'U' or 'R'

		if (timestamp == 0) {
			Time systemTime;
			timestamp = systemTime.getMiliTime() / 1000;
		}
		insertInt(timestamp);

		insertInt(0x00);

		setCompression(true);
	}

	ChatPersistentMessageToClient(PersistentMessage* mail, bool sendBody) {
		insertShort(0x02);
		insertInt(0x08485E17); //ChatPersistentMessageToClient

		insertAscii(mail->getSenderName());
		insertAscii(""); //Game NOTE: SOE doesn't send this, why should we?
		insertAscii(""); //Galaxy Name
		insertInt(mail->getMailID());

		insertByte((uint8) !sendBody);

		if (sendBody)
			insertUnicode(mail->getBody());
		else
			insertInt(0);

		insertUnicode(mail->getSubject());

		if (sendBody)
			insertParameters(mail);
		else
			insertInt(0); //Send no parameters, since we aren't sending a body.

		insertByte(mail->getStatus());
		insertInt(mail->getTimeStamp());
		//insertInt(0); //Pretty sure we don't need to append this.

		//System::out << toStringData() << endl;

		setCompression(true);
	}
};

#endif /*CHATPERSISTENTMESSAGETOCLIENT_H_*/
