/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ATTRIBUTELISTMESSAGE_H_
#define ATTRIBUTELISTMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

//class SceneObject;

namespace server {
 namespace zone {
  namespace packets {
   namespace scene {



class AttributeListMessage : public BaseMessage {
	int listcount;
	int countLocation;

public:
	AttributeListMessage(SceneObject* object) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xF3F12F2A); // opcode

		insertLong(object->getObjectID());
		insertInt(0); // list count

		setCompression(true);

		listcount = 0;
		countLocation = 18;
	}

	AttributeListMessage(uint64 objectID, int listCount) : BaseMessage(), listcount(listCount),
			countLocation(18) {
		insertShort(0x04);
		insertInt(0xF3F12F2A); // opcode

		insertLong(objectID);
		insertInt(listCount); // list count
		setCompression(true);
	}

	AttributeListMessage(uint64 objectID) : BaseMessage() {
		insertShort(0x04);
		insertInt(0xF3F12F2A);
		insertLong(objectID);
		insertInt(0); // list count
		listcount = 0;
		countLocation = 18;
		setCompression(true);
	}

	// For bazaar/vendor items
	AttributeListMessage(uint64 objectid, UnicodeString& description) : BaseMessage() {
		insertShort(2);
		insertInt(0xFE0E644B);

		insertLong(objectid);

		insertUnicode(description);

		insertInt(0); // list count
		listcount = 0;
		countLocation = 22 + description.length() * 2;
		setCompression(true);
	}

	void insertAttribute(const String& attribute, UnicodeString& value) {
		insertAscii(attribute);
		insertUnicode(value);

		updateListCount();
	}

	void insertAttribute(const String& attribute, String& value) {
		UnicodeString Value = UnicodeString(value);
		insertAscii(attribute);
		insertUnicode(Value);

		updateListCount();
	}

	void insertAttribute(const String& attribute, const String& value) {
		UnicodeString Value = UnicodeString(value);
		insertAscii(attribute);
		insertUnicode(Value);

		updateListCount();
	}

	void insertAttribute(const String& attribute, StringBuffer& value) {
		UnicodeString Value = UnicodeString(value.toString());

		insertAscii(attribute);
		insertUnicode(Value);

		updateListCount();
	}

	void insertAttribute(const String& attribute, float value) {
		StringBuffer t;
		t << value;

		UnicodeString Value = UnicodeString(t.toString());

		insertAscii(attribute);
		insertUnicode(Value);

		updateListCount();
	}

	void insertAttribute(const String& attribute, int value) {
		StringBuffer t;
		t << value;

		UnicodeString Value = UnicodeString(t.toString());

		insertAscii(attribute.toCharArray());
		insertUnicode(Value);

		updateListCount();
	}

	void insertAttribute(const String& attribute, int value, bool asInt) {
		insertAscii(attribute);
		insertInt(value);

		updateListCount();
	}

	void updateListCount() {
		insertInt(countLocation, ++listcount);
	}


};

   }
  }
 }
}

using namespace server::zone::packets::scene;


#endif /*ATTRIBUTELISTMESSAGE_H_*/
