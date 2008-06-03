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
	
	string attributeString;
	string returnString;
	
public:
	ItemAttributes() {
		attributes = new AttributeMap(50);
	}
	
	~ItemAttributes() {
		delete attributes;
	}
	
	bool attributeExists(string& name) {
		return attributes->containsKey(name);
	}
	
	void setStringAttribute(string& name, string& value) {
		attributes->put(name, value);
	}
	
	string& getStringAttribute(string& name) {
		
		if (attributes->containsKey(name))
			return attributes->get(name);
		else {
			returnString = "";
			return returnString;
		}
	}
	
	void setIntAttribute(string& name, int value) {
		stringstream val;
		val << value;
		attributes->put(name, val.str());
	}
	
	int getIntAttribute(string& name) {
		if (attributes->containsKey(name)) {
			string value = attributes->get(name);
			return atoi(value.c_str());
		} else {
			return 0;
		}
	}
	
	void setUnsignedLongAttribute(string& name, uint64 value) {
		stringstream val;
		val << value;
		attributes->put(name, val.str());
	}
	
	uint64  getUnsignedLongAttribute(string& name) {
		if (attributes->containsKey(name)) {
			string value = attributes->get(name);
			return atoll(value.c_str());
		} else {
			return 0L;
		}
	}
	
	void setBooleanAttribute(string& name, bool value) {
		if (value)
			attributes->put(name, "true");
		else
			attributes->put(name, "false");
	}
	
	bool getBooleanAttribute(string& name) {
		if (attributes->containsKey(name)) {
			if (attributes->get(name) == "true")
				return true;
			else
				return false;
		} else {
			return false;
		}
	}
	
	void setFloatAttribute(string& name, float value) {
		stringstream val;
		val << value;
		attributes->put(name, val.str());
	}
	
	float getFloatAttribute(string& name) {
		if (attributes->containsKey(name)) {
			string value = attributes->get(name);
			return atof(value.c_str());
		} else {
			return 0.0f;
		}
	}
		
	unicode* getUnicodeAttribute(string& name) {
		if (attributes->containsKey(name)) {
			unicode* uni = new unicode(attributes->get(name));
			return uni;
		} else {
			return new unicode("");
		}
	}
	
	// String format is "name1=value1:name2=value2:name3=value3:"
	void setAttributes(string& attributestring) {
		int index1 = 0; 
		int index2;
		int index3;
		
		while ((index2 = attributestring.find(":", index1)) != string::npos) {

			string attrPair = attributestring.substr(index1, index2-index1);

			if ((index3 = attrPair.find("=", 0)) != string::npos) {
				
				string key = attrPair.substr(0, index3);
				string value = attrPair.substr(index3 + 1, attrPair.length() - index3);

				attributes->put(key, value);
			}
			
			index1 = index2 + 1;
		}
	}
	
	void getAttributeString(string& attrstring) {
		attributeString = "";

		attributes->resetIterator();
		
		while (attributes->hasNext()) {
			string key;
			string value;

			attributes->getNextKeyAndValue(key, value);
			attributeString += key + "=" + value + ":";
		}
		
		attrstring = attributeString;
		
	}
	
	// Special cases
	int getMaxCondition() {
		int index;
		string max;

		string key = "condition";
		string value = attributes->get(key);
		
		if ((index = value.find("/", 0)) != string::npos) {
			max = value.substr(index + 1, value.length() - index);
		}
		return atoi(max.c_str());
	}
	
	int getCurrentCondition() {
		string current;
		int index;

		string key = "condition";
		string value = attributes->get(key);
		
		if ((index = value.find("/", 0)) != string::npos) {
			current = value.substr(0, index);
		}
		
		return atoi(current.c_str());
	}
	
	void setCondition(int current, int max) {
		stringstream value;
		
		value << current << "/" << max;
		string key = "condition";
		
		attributes->put(key, value.str());
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
