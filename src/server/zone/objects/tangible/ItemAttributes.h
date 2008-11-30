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

#ifndef ITEMATTRIBUTES_H_
#define ITEMATTRIBUTES_H_

#include "engine/engine.h"

#include "AttributeMap.h"

class ItemAttributes {
	AttributeMap* attributes;

	String attributeString;
	String returnString;

public:
	ItemAttributes() {
		attributes = new AttributeMap(50);
	}

	~ItemAttributes() {
		delete attributes;
	}

	bool attributeExists(const String& name) {
		return attributes->containsKey(name);
	}

	void setStringAttribute(const String& name, String& value) {
		attributes->put(name, value);
	}

	String& getStringAttribute(const String& name) {
		if (attributes->containsKey(name))
			return attributes->get(name);
		else {
			returnString = "";
			return returnString;
		}
	}

	void setIntAttribute(String& name, int value) {
		attributes->put(name, String::valueOf(value));
	}

	int getIntAttribute(const String& name) {
		if (attributes->containsKey(name)) {
			String value = attributes->get(name);

			return Integer::valueOf(value);
		} else
			return 0;
	}

	void setUnsignedLongAttribute(const String& name, uint64 value) {
		attributes->put(name, String::valueOf(value));
	}

	uint64 getUnsignedLongAttribute(const String& name) {
		if (attributes->containsKey(name)) {
			String value = attributes->get(name);

			return Long::unsignedvalueOf(value);
		} else {
			return 0L;
		}
	}

	void setBooleanAttribute(const String& name, bool value) {
		if (value)
			attributes->put(name, "true");
		else
			attributes->put(name, "false");
	}

	bool getBooleanAttribute(const String& name) {
		if (attributes->containsKey(name)) {
			if (attributes->get(name) == "true")
				return true;
			else
				return false;
		} else {
			return false;
		}
	}

	void setFloatAttribute(const String& name, float value) {
		attributes->put(name, String::valueOf(value));
	}

	float getFloatAttribute(const String& name) {
		if (attributes->containsKey(name)) {
			String value = attributes->get(name);

			return Float::valueOf(value);
		} else {
			return 0.0f;
		}
	}

	UnicodeString* getUnicodeAttribute(const String& name) {
		if (attributes->containsKey(name)) {
			UnicodeString* uni = new UnicodeString(attributes->get(name));
			return uni;
		} else {
			return new UnicodeString("");
		}
	}

	// String format is "name1=value1:name2=value2:name3=value3:"
	void setAttributes(const String& attributeString) {
		int index1 = 0;
		int index2;
		int index3;

		while ((index2 = attributeString.indexOf(":", index1)) != -1) {
			String attrPair = attributeString.subString(index1, index2);

			if ((index3 = attrPair.indexOf("=", 0)) != -1) {
				String key = attrPair.subString(0, index3);

				String value = attrPair.subString(index3 + 1, attrPair.length());

				attributes->put(key, value);
			}

			index1 = index2 + 1;
		}
	}

	void getAttributeString(String& attrString) {
		StringBuffer attrs;

		attributes->resetIterator();

		while (attributes->hasNext()) {
			String key;
			String value;

			attributes->getNextKeyAndValue(key, value);
			//attributeString += key.toCharArray() + "=" + value.toCharArray() + ":";

			attrs << key << "=" << value << ":";
		}

		attributeString = attrs.toString();
		attrString = attributeString;
	}

	// Special cases
	int getMaxCondition() {
		int index;
		String max;

		String key = "condition";
		String value = attributes->get(key);

		if ((index = value.indexOf("/", 0)) != -1)
			max = value.subString(index + 1, value.length());

		return Integer::valueOf(max);
	}

	int getCurrentCondition() {
		String current;
		int index;

		String key = "condition";
		String value = attributes->get(key);

		if ((index = value.indexOf("/", 0)) != -1)
			current = value.subString(0, index);

		return Integer::valueOf(current);
	}

	void setCondition(int current, int max) {
		StringBuffer value;
		value << current << "/" << max;

		String key = "condition";

		attributes->put(key, value.toString());
	}

	//void setMaxCondition(int maxcondition);
	//void setCurrentCondition(int condition);

};

#endif /*ITEMATTRIBUTES_H_*/

/*
 * character_items database structure
 *
 * item_id 			BIGINT
 * character_id 	BIGINT
 * name 			TEXT
 * template_crc 	BIGINT
 * template_type	INT
 * template_name	TINYTEXT
 * container		BIGINT	- Needed for backpacks/houses and other containers
 * equipped			TINYINT
 * deleted			TINYINT
 * attributes		TEXT
 *
 */
