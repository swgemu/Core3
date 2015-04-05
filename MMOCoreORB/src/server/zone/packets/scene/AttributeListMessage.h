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
