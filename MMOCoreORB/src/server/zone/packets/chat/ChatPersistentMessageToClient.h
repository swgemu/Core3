/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHATPERSISTENTMESSAGETOCLIENT_H_
#define CHATPERSISTENTMESSAGETOCLIENT_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/chat/StringIdChatParameterVector.h"
#include "server/chat/WaypointChatParameterVector.h"
#include "server/chat/PersistentMessage.h"

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

	ChatPersistentMessageToClient(PersistentMessage* mail, const String& serverName, bool sendBody) {
		insertShort(0x02);
		insertInt(0x08485E17); //ChatPersistentMessageToClient

		insertAscii(mail->getSenderName());
		insertAscii("SWG"); // Game Name
		insertAscii(serverName.toCharArray()); //Galaxy Name
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
