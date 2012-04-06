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

#include "CustomizationVariables.h"

#include "engine/db/BinaryData.h"

#include "server/zone/managers/customization/CustomizationIdManager.h"

CustomizationVariables::CustomizationVariables() : VectorMap<uint8, int16>() {
	removeAll();

	unknown = 1;
	setNullValue(0);

	keyIndex.removeAll();

	setInsertPlan(SortedVector<uint8>::NO_DUPLICATE);
}

CustomizationVariables::~CustomizationVariables() {
	removeAll();
}

CustomizationVariables::CustomizationVariables(const CustomizationVariables& cv) :VectorMap<uint8, int16>(cv) {
	unknown = cv.unknown;

	keyIndex = cv.keyIndex;
}

CustomizationVariables& CustomizationVariables::operator=(const String& custString) {
	parseFromClientString(custString);

	return *this;
}

void CustomizationVariables::setVariable(uint8 type, int16 value) {
	if (!contains(type))
		keyIndex.add(type);

	drop(type);

	put(type, value);
	//System::out << "inserted type:[" << hex << type << "] value:[" << hex << value << "]\n";
}

void CustomizationVariables::setVariable(const String& type, int16 value) {
	uint16 id = CustomizationIdManager::instance()->getCustomizationId(type);

	setVariable(id, value);
}

void CustomizationVariables::getVariable(int idx, uint8& type, int16& value) {
	VectorMapEntry<uint8, int16> entry = SortedVector<VectorMapEntry<uint8, int16> >::get(idx);

	type = entry.getKey();
	value = entry.getValue();
}

void CustomizationVariables::getData(String& ascii) {
	ascii = "";

	if (isEmpty())
		return;

	StringBuffer buf;

	buf.append((char)unknown);
	buf.append((char)size());

	for (int i = 0; i < keyIndex.size(); ++i) {
		uint8 key = keyIndex.get(i);
		int16 val = get(key);

		if (val >= 0) {
			buf.append((char)key);

			if (val == 0x00)	{
				buf.append((char)0xFF);
				buf.append((char)0x01);
			} else if (val == 0xFF) {
				buf.append((char)0xFF);
				buf.append((char)0x02);
			} else
				buf.append((char)val);
		} else {
			buf.append((char)(key | 0x80));

			buf.append((char)val);
			buf.append((char)0xFF);
			buf.append((char)0x02);
		}
	}

	buf.append((char)0xFF);
	buf.append((char)0x03);

	ascii = buf.toString();

	return;
}

void CustomizationVariables::parseFromClientString(const String& custString) {
	removeAll();
	keyIndex.removeAll();

	if (custString.length() < 2)
		return;

	try {
		unknown = (uint8) custString.charAt(0);
		//uint8 type = 0;

		int totalVars = (uint8) custString.charAt(1);
		int offset = 1;

		if (totalVars == 0xFF)
			return;

		for (int i = 0; i < totalVars; ++i) {
			uint8 value;

			uint8 type = (uint8) custString.charAt(++offset);

			bool isSigned = false;

			if (type & 0x80) { //signed type
				type &= 0x7F;

				isSigned = true;
			}

			uint8 value1 = (uint8) custString.charAt(++offset);

			if (isSigned) {
				if (value1 != 0xFF) {
					uint8 footer1 = custString.charAt(++offset);
					uint8 footer2 = custString.charAt(++offset);

					if (footer2 == 2) { //negative
						setVariable(type, 0xFF00 | value1);
					} else { // positive
						setVariable(type, value1);
					}
				} else {
					setVariable(type, 0);
				}
			} else {
				if (value1 == 0xFF) {
					value1 = custString.charAt(++offset);

					if (value1 == 0x01)
						value = 0x00; // zero
					else // value1 == 0x02
						value = 0xFF; // 255
				} else {
					value = value1;
				}

				setVariable(type, value);
			}
		}
	} catch (Exception& e) {
		removeAll();
		printf("Exception in CustomizationVariables& operator=(String& custString)\n");

		const char* array = custString.toCharArray();

		StringBuffer str;
		str << "parsing CustomizationString [" << custString.length() << "] " << uppercase << hex;

		for (int i = 0; i < custString.length(); ++i) {
			unsigned int byte = ((unsigned int) array[i]) & 0xFF;

			if ((byte & 0xF0) == 0)
				str << "0" << hex << byte  << " ";
			else
				str << hex << byte  << " ";
		}

		printf("%s\n", str.toString().toCharArray());
	}

}


bool CustomizationVariables::toString(String& ascii) {
	String binData;
	getData(binData);

	BinaryData cust(binData);

	cust.encode(ascii);

	return true;
}

bool CustomizationVariables::parseFromString(const String& str, int version) {
	String data = str;
	BinaryData cust(data);

	String custStr;
	cust.decode(custStr);

	*this = custStr;

	return true;
}

bool CustomizationVariables::toBinaryStream(ObjectOutputStream* stream) {
	String str;
	getData(str);

	str.toBinaryStream(stream);

	return true;
}

bool CustomizationVariables::parseFromBinaryStream(ObjectInputStream* stream) {
	String str;
	str.parseFromBinaryStream(stream);

	*this = str;

	return true;
}
