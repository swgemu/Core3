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

CustomizationVariables::CustomizationVariables() : VectorMap<uint8, uint8>() {
	removeAll();

	unknown = 1;
	unknown2 = false;

	female = false;
	setNullValue(0);

	keyIndex.removeAll();

	setInsertPlan(SortedVector<uint8>::NO_DUPLICATE);
}

CustomizationVariables::~CustomizationVariables() {
	removeAll();
}

CustomizationVariables::CustomizationVariables(const CustomizationVariables& cv) :VectorMap<uint8, uint8>(cv) {
	unknown = cv.unknown;
	unknown2 = cv.unknown2;

	female = cv.female;

	keyIndex = cv.keyIndex;
}

CustomizationVariables& CustomizationVariables::operator=(const String& custString) {
	parseFromClientString(custString);

	return *this;
}

void CustomizationVariables::setVariable(uint8 type, uint8 value) {
	if (!contains(type))
		keyIndex.add(type);

	drop(type);

	put(type, value);
	//System::out << "inserted type:[" << hex << type << "] value:[" << hex << value << "]\n";
}

void CustomizationVariables::setVariable(const String& type, uint8 value) {
	if (type.contains("blend_asian_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ASIAN_0, value);
	else if (type.contains("blend_brow_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_BROW_0, value);
	else if (type.contains("blend_brow_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_BROW_1, value);
	else if (type.contains("blend_cheeks_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHEEKS_0, value);
	else if (type.contains("blend_cheeks_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHEEKS_1, value);
	else if (type.contains("blend_chest_backpack"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHEST_BACKPACK, value);
	else if (type.contains("blend_chin_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHIN_0, value);
	else if (type.contains("blend_chin_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHIN_1, value);
	else if (type.contains("blend_chinsize_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHINSIZE_0, value);
	else if (type.contains("blend_chinsize_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHINSIZE_1, value);
	else if (type.contains("blend_ear_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EAR_0, value);
	else if (type.contains("blend_ear_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EAR_1, value);
	else if (type.contains("blend_ears_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EARS_0, value);
	else if (type.contains("blend_ears_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EARS_1, value);
	else if (type.contains("blend_eyedirection_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYEDIRECTION_0, value);
	else if (type.contains("blend_eyedirection_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYEDIRECTION_1, value);
	else if (type.contains("blend_eyeshape_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNWER_BLEND_EYESHAPE_0, value);
	else if (type.contains("blend_eyeshape_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNWER_BLEND_EYESHAPE_1, value);
	else if (type.contains("blend_eyesize_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYESIZE_0, value);
	else if (type.contains("blend_eyesize_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYESIZE_1, value);
	else if (type.contains("blend_eyeslant_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYESLANT_0, value);
	else if (type.contains("blend_fat"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_FAT, value);
	else if (type.contains("blend_flat_chest"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_FLAT_CHEST, value);
	else if (type.contains("blend_head_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEAD_0, value);
	else if (type.contains("blend_head_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEAD_1, value);
	else if (type.contains("blend_headsize_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEADSIZE_0, value);
	else if (type.contains("blend_headsize_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEADSIZE_1, value);
	else if (type.contains("blend_jacket"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET, value);
	else if (type.contains("blend_jacket_bandolier"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET_BANDOLIER, value);
	else if (type.contains("blend_jacket_belt"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET_BELT, value);
	else if (type.contains("blend_jacket_robe"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET_ROBE, value);
	else if (type.contains("blend_jaw_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JAW_0, value);
	else if (type.contains("blend_jaw_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JAW_1, value);
	else if (type.contains("blend_lipfullness_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULLNESS_0, value);
	else if (type.contains("blend_lipfullness_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULLNESS_1, value);
	else if (type.contains("blend_lipfulness_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULNESS_0, value);
	else if (type.contains("blend_lipfulness_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULNESS_1, value);
	else if (type.contains("blend_lipwidth_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPWIDTH_0, value);
	else if (type.contains("blend_lipwidth_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPWIDTH_1, value);
	else if (type.contains("blend_muscle"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_MUSCLE, value);
	else if (type.contains("blend_nosedepth_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEDEPTH_0, value);
	else if (type.contains("blend_nosedepth_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEDEPTH_1, value);
	else if (type.contains("blend_noselength_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSELENGTH_0, value);
	else if (type.contains("blend_noselength_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSELENGTH_1, value);
	else if (type.contains("blend_nosesize_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSESIZE_0, value);
	else if (type.contains("blend_nosesize_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSESIZE_1, value);
	else if (type.contains("blend_nosewidth_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEWIDTH_0, value);
	else if (type.contains("blend_nosewidth_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEWIDTH_1, value);
	else if (type.contains("blend_robe"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ROBE, value);
	else if (type.contains("blend_robe_bandolier"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ROBE_BANDOLIER, value);
	else if (type.contains("blend_robe_belt"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ROBE_BELT, value);
	else if (type.contains("blend_sensor_0"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_SENSOR_0, value);
	else if (type.contains("blend_sensor_1"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_SENSOR_1, value);
	else if (type.contains("blend_skinny"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_SKINNY, value);
	else if (type.contains("index_accel_max"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_ACCEL_MAX, value);
	else if (type.contains("index_accel_min"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_ACCEL_MIN, value);
	else if (type.contains("index_age"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_AGE, value);
	else if (type.contains("index_auto_level"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_AUTO_LEVEL, value);
	else if (type.contains("index_banking"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_BANKING, value);
	else if (type.contains("index_color_0"))  {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_0, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_0, value);
	} else if (type.contains("index_color_1")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_1, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_1, value);
	} else if (type.contains("index_color_107"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_107, value);
	else if (type.contains("index_color_2")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_2, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_2, value);
	} else if (type.contains("index_color_3")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_3, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_3, value);
	} else if (type.contains("index_color_4")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_4, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_4, value);
	} else if (type.contains("index_color_5"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_5, value);
	else if (type.contains("index_color_blade"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_BLADE, value);
	else if (type.contains("index_color_eye"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_EYE, value);
	else if (type.contains("index_color_eyebrow"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_EYEBROW, value);
	else if (type.contains("index_color_eyeshadow"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_EYESHADOW, value);
	else if (type.contains("index_color_facial_hair"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_FACIAL_HAIR, value);
	else if (type.contains("index_color_fur"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_FUR, value);
	else if (type.contains("index_color_hair"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_HAIR, value);
	else if (type.contains("index_color_lips"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_LIPS, value);
	else if (type.contains("index_color_pattern")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_PATTERN, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_PATTERN, value);
	} else if (type.contains("index_color_patterns"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_PATTERNS, value);
	else if (type.contains("index_color_skin")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_SKIN, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_SKIN, value);
	} else if (type.contains("index_color_tat"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_TAT, value);
	else if (type.contains("index_color_tattoo"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_TATTOO, value);
	else if (type.contains("index_color_test"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_TEST, value);
	else if (type.contains("index_damp_height"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DAMP_HEIGHT, value);
	else if (type.contains("index_damp_pitch"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DAMP_PITCH, value);
	else if (type.contains("index_damp_roll"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DAMP_ROLL, value);
	else if (type.contains("index_decel"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DECEL, value);
	else if (type.contains("index_glide"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_GLIDE, value);
	else if (type.contains("index_hover_height"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_HOVER_HEIGHT, value);
	else if (type.contains("index_patterns"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_PATTERNS, value);
	else if (type.contains("index_slope_mod"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_SLOPE_MOD, value);
	else if (type.contains("index_speed_max"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_SPEED_MAX, value);
	else if (type.contains("index_style_beard")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_BEARD, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_BEARD, value);
	} else if (type.contains("index_style_beard_2")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_BEARD_2, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_BEARD_2, value);
	} else if (type.contains("index_style_eyebrow")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_EYEBROW, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_EYEBROW, value);
	} else if (type.contains("index_style_eyebrows"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_EYEBROWS, value);
	else if (type.contains("index_style_eyeshadow"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_EYESHADOW, value);
	else if (type.contains("index_style_freckles"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_FRECKLES, value);
	else if (type.contains("index_style_hair")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_HAIR, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_HAIR, value);
	} else if (type.contains("index_style_tattoo"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_TATTOO, value);
	else if (type.contains("index_texture")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TEXTURE, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_TEXTURE, value);
	} else if (type.contains("index_texture_1")) {
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TEXTURE_1, value);
		setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_TEXTURE_1, value);
	} else if (type.contains("index_turn_rate_max"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TURN_RATE_MAX, value);
	else if (type.contains("index_turn_rate_min"))
		setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TURN_RATE_MIN, value);
	else if (type.contains("muscle_fat"))
		setVariable(CustomizationVariableTypes::SHARED_OWNER_MUSCLE_FAT, value);
	else {

		// dangers!
	}
}

void CustomizationVariables::getVariable(int idx, uint8& type, uint8& value) {
	VectorMapEntry<uint8, uint8> entry = SortedVector<VectorMapEntry<uint8, uint8> >::get(idx);

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

	if (female)
		buf.append((char)0xAB);

	if (unknown2)
		buf.append((char)0xFF);

	for (int i = 0; i < keyIndex.size(); ++i) {
		uint8 key = keyIndex.get(i);
		uint8 val = get(key);

		buf.append((char)key);

		if (val == 0x00)	{
			buf.append((char)0xFF);
			buf.append((char)0x01);
		} else if (val == 0xFF) {
			buf.append((char)0xFF);
			buf.append((char)0x02);
		} else
			buf.append((char)val);
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
		uint8 type = 0;

		int totalVars = (uint8) custString.charAt(1);
		int offset = 1;

		female = false;

		for (int i = 0; i < totalVars; ++i) {
			uint8 value;

			uint8 type = (uint8) custString.charAt(++offset);

			if (type == 0xAB) {
				female = true;

				// Not sure about the sometimes shown 0xFF
				// seems to work if we ignore it
				// on second thought, account for it in case it is valuable.
				if ((uint8) custString.charAt(offset+1) == 0xFF) {
					unknown2 = true;
					offset++;
				}

				i--;

				continue;
			}

			uint8 value1 = (uint8) custString.charAt(++offset);

			if (value1 == 0xFF) {
				value1 = custString.charAt(++offset);

				if (value1 == 0x01)
					value = 0x00; // zero
				else // value1 == 0x02
					value = 0xFF; // 255
			} else
				value = value1;

			setVariable(type, value);
		}
	} catch (Exception& e) {
		removeAll();
		//System::out << "Exception in CustomizationVariables& operator=(String& custString)\n";
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
