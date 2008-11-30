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

#ifndef CUSTOMIZATIONVARIABLES_H_
#define CUSTOMIZATIONVARIABLES_H_

#include "system/lang.h"

class CustomizationVariableTypes {
public:
	static const uint8 PRIVATE_INDEX_COLOR_2 = 0x01;
	static const uint8 PRIVATE_INDEX_COLOR_1 = 0x02;
	static const uint8 SHARED_OWNER_BLEND_SKINNY = 0x03;
	static const uint8 SHARED_OWNER_BLEND_MUSCLE = 0x04;
	static const uint8 SHARED_OWNER_BLEND_FAT = 0x05;
	static const uint8 SHARED_OWNER_BLEND_NOSEDEPTH_1 = 0x06;
	static const uint8 SHARED_OWNER_BLEND_EYESIZE_0 = 0x07;
	static const uint8 SHARED_OWNER_BLEND_NOSEDEPTH_0 = 0x08;
	static const uint8 SHARED_OWNER_BLEND_NOSELENGTH_1 = 0x09;
	static const uint8 SHARED_OWNER_BLEND_EYESIZE_1 = 0x0A;
	static const uint8 SHARED_OWNER_BLEND_CHEEKS_0 = 0x0B;
	static const uint8 SHARED_OWNER_BLEND_EYEDIRECTION_0 = 0x0C;
	static const uint8 SHARED_OWNER_BLEND_NOSELENGTH_0 = 0x0D;
	static const uint8 SHARED_OWNER_BLEND_EYEDIRECTION_1 = 0x0E;
	static const uint8 SHARED_OWNER_BLEND_NOSEWIDTH_0 = 0x0F;
	static const uint8 SHARED_OWNER_BLEND_NOSEWIDTH_1 = 0x10;
	static const uint8 SHARED_OWNER_BLEND_CHEEKS_1 = 0x11;
	static const uint8 SHARED_OWNER_BLEND_JAW_1 = 0x12;
	static const uint8 SHARED_OWNER_BLEND_JAW_0 = 0x13;
	static const uint8 SHARED_OWNER_INDEX_COLOR_SKIN = 0x14;
	static const uint8 SHARED_OWNER_BLEND_LIPWIDTH_0 = 0x15;
	static const uint8 SHARED_OWNER_BLEND_LIPWIDTH_1 = 0x16;
	static const uint8 SHARED_OWNER_BLEND_LIPFULLNESS_0 = 0x17;
	static const uint8 SHARED_OWNER_BLEND_LIPFULLNESS_1 = 0x18;
	static const uint8 SHARED_OWNER_BLEND_EARS_0 = 0x19;
	static const uint8 SHARED_OWNER_BLEND_EARS_1 = 0x1A;
	static const uint8 SHARED_OWNER_BLEND_CHINSIZE_1 = 0x1B;
	static const uint8 SHARED_OWNER_BLEND_CHINSIZE_0 = 0x1C;
	static const uint8 PRIVATE_INDEX_COLOR_3 = 0x1D;
	static const uint8 PRIVATE_INDEX_STYLE_EYEBROW = 0x1E;
	static const uint8 PRIVATE_INDEX_COLOR_FACIAL_HAIR = 0x1F;
	static const uint8 SHARED_OWNWER_BLEND_EYESHAPE_1 = 0x20;
	static const uint8 SHARED_OWNWER_BLEND_EYESHAPE_0 = 0x21;
	static const uint8 PRIVATE_INDEX_COLOR_0 = 0x22;
	static const uint8 PRIVATE_INDEX_STYLE_BEARD = 0x23;
	static const uint8 PRIVATE_INDEX_AGE = 0x24;
	static const uint8 PRIVATE_INDEX_STYLE_FRECKLES = 0x25;
	static const uint8 PRIVATE_INDEX_TEXTURE_1 = 0x26;
	static const uint8 SHARED_OWNER_BLEND_SENSOR_0 = 0x27;
	static const uint8 SHARED_OWNER_BLEND_SENSOR_1 = 0x28;
	static const uint8 SHARED_OWNER_BLEND_ASIAN_0 = 0x29;
	static const uint8 PRIVATE_INDEX_COLOR_SKIN = 0x2A;
	static const uint8 SHARED_OWNER_BLEND_FLAT_CHEST = 0x2B;
	static const uint8 PRIVATE_INDEX_COLOR_EYESHADOW = 0x2C;
	static const uint8 PRIVATE_INDEX_STYLE_EYESHADOW = 0x2D;
	static const uint8 PRIVATE_INDEX_COLOR_LIPS = 0x2E;
	static const uint8 SHARED_OWNER_INDEX_TEXTURE_1 = 0x2F;
	static const uint8 SHARED_OWNER_INDEX_COLOR_PATTERN = 0x30;
	static const uint8 PRIVATE_INDEX_COLOR_4 = 0x31;
	static const uint8 PRIVATE_INDEX_COLOR_HAIR = 0x32;
	static const uint8 SHARED_OWNER_BLEND_NOSESIZE_1 = 0x33;
	static const uint8 SHARED_OWNER_BLEND_NOSESIZE_0 = 0x34;
	static const uint8 PRIVATE_INDEX_STYLE_TATTOO = 0x35;
	static const uint8 PRIVATE_INDEX_COLOR_TATTOO = 0x36;
	static const uint8 PRIVATE_INDEX_COLOR_TAT = 0x37;
	static const uint8 SHARED_OWNER_INDEX_COLOR_0 = 0x38;
	static const uint8 SHARED_OWNER_BLEND_HEADSIZE_0 = 0x39;
	static const uint8 SHARED_OWNER_BLEND_HEADSIZE_1 = 0x3A;
	static const uint8 PRIVATE_INDEX_COLOR_PATTERN = 0x3B;
	static const uint8 PRIVATE_INDEX_COLOR_EYE = 0x3C;
	static const uint8 SHARED_OWNER_MUSCLE_FAT = 0x3D;
	static const uint8 SHARED_OWNER_BLEND_EAR_0 = 0x3E;
	static const uint8 SHARED_OWNER_BLEND_EAR_1 = 0x3F;
	static const uint8 PRIVATE_INDEX_COLOR_EYEBROW = 0x40;
	static const uint8 PRIVATE_INDEX_COLOR_5 = 0x41;
	static const uint8 SHARED_OWNER_BLEND_BROW_1 = 0x42;
	static const uint8 SHARED_OWNER_BLEND_BROW_0 = 0x43;
	static const uint8 PRIVATE_INDEX_STYLE_EYEBROWS = 0x44;
	static const uint8 PRIVATE_INDEX_COLOR_TEST = 0x45;
	static const uint8 PRIVATE_INDEX_COLOR_107 = 0x46;
	static const uint8 SHARED_OWNER_INDEX_COLOR_4 = 0x47;
	static const uint8 SHARED_OWNER_INDEX_COLOR_3 = 0x48;
	static const uint8 SHARED_OWNER_INDEX_COLOR_1 = 0x49;
	static const uint8 PRIVATE_INDEX_COLOR_BLADE = 0x4A;
	static const uint8 PRIVATE_INDEX_COLOR_FUR = 0x4B;
	static const uint8 SHARED_OWNER_BLEND_ROBE_BELT = 0x4C;
	static const uint8 SHARED_OWNER_BLEND_EYESLANT_0 = 0x4D;
	static const uint8 SHARED_OWNER_BLEND_CHIN_1 = 0x4E;
	static const uint8 SHARED_OWNER_INDEX_COLOR_2 = 0x4F;
	static const uint8 SHARED_OWNER_BLEND_CHIN_0 = 0x50;
	static const uint8 SHARED_OWNER_BLEND_ROBE_BANDOLIER = 0x51;
	static const uint8 SHARED_OWNER_BLEND_JACKET_BELT = 0x52;
	static const uint8 SHARED_OWNER_BLEND_CHEST_BACKPACK = 0x53;
	static const uint8 SHARED_OWNER_BLEND_JACKET_BANDOLIER = 0x54;
	static const uint8 PRIVATE_INDEX_GLIDE = 0x55;
	static const uint8 PRIVATE_INDEX_TURN_RATE_MAX = 0x56;
	static const uint8 PRIVATE_INDEX_SPEED_MAX = 0x57;
	static const uint8 PRIVATE_INDEX_BANKING = 0x58;
	static const uint8 PRIVATE_INDEX_HOVER_HEIGHT = 0x59;
	static const uint8 PRIVATE_INDEX_ACCEL_MAX = 0x5A;
	static const uint8 PRIVATE_INDEX_ACCEL_MIN = 0x5B;
	static const uint8 PRIVATE_INDEX_DECEL = 0x5C;
	static const uint8 PRIVATE_INDEX_DAMP_HEIGHT = 0x5D;
	static const uint8 PRIVATE_INDEX_TURN_RATE_MIN = 0x5E;
	static const uint8 PRIVATE_INDEX_SLOPE_MOD = 0x5F;
	static const uint8 PRIVATE_INDEX_DAMP_ROLL = 0x60;
	static const uint8 PRIVATE_INDEX_AUTO_LEVEL = 0x61;
	static const uint8 PRIVATE_INDEX_DAMP_PITCH = 0x62;
	static const uint8 PRIVATE_INDEX_COLOR_PATTERNS = 0x63;
	static const uint8 PRIVATE_INDEX_STYLE_HAIR = 0x64;
	static const uint8 PRIVATE_INDEX_PATTERNS = 0x65;
	static const uint8 PRIVATE_INDEX_TEXTURE = 0x66;
	static const uint8 PRIVATE_INDEX_STYLE_BEARD_2 = 0x67;
	static const uint8 SHARED_OWNER_BLEND_LIPFULNESS_0 = 0x68;
	static const uint8 SHARED_OWNER_BLEND_LIPFULNESS_1 = 0x69;
	static const uint8 SHARED_OWNER_INDEX_STYLE_EYEBROW = 0x6A;
	static const uint8 SHARED_OWNER_INDEX_TEXTURE = 0x6B;
	static const uint8 SHARED_OWNER_INDEX_STYLE_HAIR = 0x6C;
	static const uint8 SHARED_OWNER_BLEND_ROBE = 0x6D;
	static const uint8 SHARED_OWNER_INDEX_STYLE_BEARD = 0x6E;
	static const uint8 SHARED_OWNER_BLEND_JACKET = 0x6F;
	static const uint8 SHARED_OWNER_INDEX_STYLE_BEARD_2 = 0x70;
	static const uint8 SHARED_OWNER_BLEND_JACKET_ROBE = 0x71;
	static const uint8 SHARED_OWNER_BLEND_HEAD_0 = 0x72;
	static const uint8 SHARED_OWNER_BLEND_HEAD_1 = 0x73;
};

class CustomizationVariables : private VectorMap<uint8, uint8> {
	uint8 unknown;
	bool unknown2;

	bool female;

	Vector<uint8> keyIndex;

public:
	CustomizationVariables() : VectorMap<uint8, uint8>() {
		removeAll();

		unknown = 1;
		unknown2 = false;

		female = false;
		setNullValue(0);

		keyIndex.removeAll();

		setInsertPlan(SortedVector<uint8>::NO_DUPLICATE);
	}

	~CustomizationVariables() {
		removeAll();
	}

	CustomizationVariables& operator=(const String& custString) {
		removeAll();

		if (custString.length() < 2)
			return *this;

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

				if (value1 == 0xFF) 				{
					value1 = custString.charAt(++offset);

					if (value1 == 0x01)
						value = 0x00; // zero
					else // value1 == 0x02
						value = 0xFF; // 255
				} else
					value = value1;

                setVariable(type, value);
			}
		} catch (...) {
			removeAll();
			//System::out << "Exception in CustomizationVariables& operator=(String& custString)\n";
		}

		return *this;
	}

	void setVariable(uint8 type, uint8 value) {
	    if (!contains(type))
            keyIndex.add(type);

		drop(type);

		put(type, value);
		//System::out << "inserted type:[" << hex << type << "] value:[" << hex << value << "]\n";
	}

	void setVariable(String type, uint8 value) {
		if (type == "blend_asian_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ASIAN_0, value);
		else if (type == "blend_brow_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_BROW_0, value);
		else if (type == "blend_brow_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_BROW_1, value);
		else if (type == "blend_cheeks_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHEEKS_0, value);
		else if (type == "blend_cheeks_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHEEKS_1, value);
		else if (type == "blend_chest_backpack")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHEST_BACKPACK, value);
		else if (type == "blend_chin_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHIN_0, value);
		else if (type == "blend_chin_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHIN_1, value);
		else if (type == "blend_chinsize_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHINSIZE_0, value);
		else if (type == "blend_chinsize_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_CHINSIZE_1, value);
		else if (type == "blend_ear_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EAR_0, value);
		else if (type == "blend_ear_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EAR_1, value);
		else if (type == "blend_ears_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EARS_0, value);
		else if (type == "blend_ears_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EARS_1, value);
		else if (type == "blend_eyedirection_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYEDIRECTION_0, value);
		else if (type == "blend_eyedirection_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYEDIRECTION_1, value);
		else if (type == "blend_eyeshape_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNWER_BLEND_EYESHAPE_0, value);
		else if (type == "blend_eyeshape_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNWER_BLEND_EYESHAPE_1, value);
		else if (type == "blend_eyesize_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYESIZE_0, value);
		else if (type == "blend_eyesize_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYESIZE_1, value);
		else if (type == "blend_eyeslant_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_EYESLANT_0, value);
		else if (type == "blend_fat")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_FAT, value);
		else if (type == "blend_flat_chest")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_FLAT_CHEST, value);
		else if (type == "blend_head_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEAD_0, value);
		else if (type == "blend_head_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEAD_1, value);
		else if (type == "blend_headsize_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEADSIZE_0, value);
		else if (type == "blend_headsize_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_HEADSIZE_1, value);
		else if (type == "blend_jacket")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET, value);
		else if (type == "blend_jacket_bandolier")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET_BANDOLIER, value);
		else if (type == "blend_jacket_belt")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET_BELT, value);
		else if (type == "blend_jacket_robe")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JACKET_ROBE, value);
		else if (type == "blend_jaw_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JAW_0, value);
		else if (type == "blend_jaw_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_JAW_1, value);
		else if (type == "blend_lipfullness_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULLNESS_0, value);
		else if (type == "blend_lipfullness_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULLNESS_1, value);
		else if (type == "blend_lipfulness_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULNESS_0, value);
		else if (type == "blend_lipfulness_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPFULNESS_1, value);
		else if (type == "blend_lipwidth_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPWIDTH_0, value);
		else if (type == "blend_lipwidth_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_LIPWIDTH_1, value);
		else if (type == "blend_muscle")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_MUSCLE, value);
		else if (type == "blend_nosedepth_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEDEPTH_0, value);
		else if (type == "blend_nosedepth_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEDEPTH_1, value);
		else if (type == "blend_noselength_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSELENGTH_0, value);
		else if (type == "blend_noselength_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSELENGTH_1, value);
		else if (type == "blend_nosesize_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSESIZE_0, value);
		else if (type == "blend_nosesize_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSESIZE_1, value);
		else if (type == "blend_nosewidth_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEWIDTH_0, value);
		else if (type == "blend_nosewidth_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_NOSEWIDTH_1, value);
		else if (type == "blend_robe")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ROBE, value);
		else if (type == "blend_robe_bandolier")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ROBE_BANDOLIER, value);
		else if (type == "blend_robe_belt")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_ROBE_BELT, value);
		else if (type == "blend_sensor_0")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_SENSOR_0, value);
		else if (type == "blend_sensor_1")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_SENSOR_1, value);
		else if (type == "blend_skinny")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_BLEND_SKINNY, value);
		else if (type == "index_accel_max")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_ACCEL_MAX, value);
		else if (type == "index_accel_min")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_ACCEL_MIN, value);
		else if (type == "index_age")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_AGE, value);
		else if (type == "index_auto_level")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_AUTO_LEVEL, value);
		else if (type == "index_banking")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_BANKING, value);
		else if (type == "index_color_0")  {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_0, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_0, value);
		} else if (type == "index_color_1") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_1, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_1, value);
		} else if (type == "index_color_107")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_107, value);
		else if (type == "index_color_2") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_2, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_2, value);
		} else if (type == "index_color_3") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_3, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_3, value);
		} else if (type == "index_color_4") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_4, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_4, value);
		} else if (type == "index_color_5")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_5, value);
		else if (type == "index_color_blade")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_BLADE, value);
		else if (type == "index_color_eye")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_EYE, value);
		else if (type == "index_color_eyebrow")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_EYEBROW, value);
		else if (type == "index_color_eyeshadow")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_EYESHADOW, value);
		else if (type == "index_color_facial_hair")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_FACIAL_HAIR, value);
		else if (type == "index_color_fur")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_FUR, value);
		else if (type == "index_color_hair")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_HAIR, value);
		else if (type == "index_color_lips")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_LIPS, value);
		else if (type == "index_color_pattern") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_PATTERN, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_PATTERN, value);
		} else if (type == "index_color_patterns")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_PATTERNS, value);
		else if (type == "index_color_skin") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_SKIN, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_COLOR_SKIN, value);
		} else if (type == "index_color_tat")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_TAT, value);
		else if (type == "index_color_tattoo")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_TATTOO, value);
		else if (type == "index_color_test")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_COLOR_TEST, value);
		else if (type == "index_damp_height")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DAMP_HEIGHT, value);
		else if (type == "index_damp_pitch")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DAMP_PITCH, value);
		else if (type == "index_damp_roll")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DAMP_ROLL, value);
		else if (type == "index_decel")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_DECEL, value);
		else if (type == "index_glide")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_GLIDE, value);
		else if (type == "index_hover_height")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_HOVER_HEIGHT, value);
		else if (type == "index_patterns")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_PATTERNS, value);
		else if (type == "index_slope_mod")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_SLOPE_MOD, value);
		else if (type == "index_speed_max")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_SPEED_MAX, value);
		else if (type == "index_style_beard") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_BEARD, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_BEARD, value);
		} else if (type == "index_style_beard_2") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_BEARD_2, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_BEARD_2, value);
		} else if (type == "index_style_eyebrow") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_EYEBROW, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_EYEBROW, value);
		} else if (type == "index_style_eyebrows")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_EYEBROWS, value);
		else if (type == "index_style_eyeshadow")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_EYESHADOW, value);
		else if (type == "index_style_freckles")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_FRECKLES, value);
		else if (type == "index_style_hair") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_HAIR, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_STYLE_HAIR, value);
		} else if (type == "index_style_tattoo")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_STYLE_TATTOO, value);
		else if (type == "index_texture") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TEXTURE, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_TEXTURE, value);
		} else if (type == "index_texture_1") {
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TEXTURE_1, value);
			setVariable(CustomizationVariableTypes::SHARED_OWNER_INDEX_TEXTURE_1, value);
		} else if (type == "index_turn_rate_max")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TURN_RATE_MAX, value);
		else if (type == "index_turn_rate_min")
			setVariable(CustomizationVariableTypes::PRIVATE_INDEX_TURN_RATE_MIN, value);
		else if (type == "muscle_fat")
			setVariable(CustomizationVariableTypes::SHARED_OWNER_MUSCLE_FAT, value);
		else {

			// dangers!
		}
	}

	uint8 getVariable(uint8 type) {
		return get(type);
	}

	uint8 getVariable(int idx) {
		return get(idx);
	}

	void getVariable(int idx, uint8& type, uint8& value) {
		VectorMapEntry<uint8, uint8>* entry = SortedVector<VectorMapEntry<uint8, uint8>*>::get(idx);

		type = entry->getKey();
		value = entry->getValue();
	}

	int getSize() {
		return size();
	}

	void toString(String& ascii) {
		if (isEmpty())
			return;

		StringBuffer buf;

		buf.append(unknown);
		buf.append(size());

		if (female)
			buf.append(0xAB);

		if (unknown2)
			buf.append(0xFF);

		for (int i = 0; i < keyIndex.size(); ++i) {
		   	uint8 key = keyIndex.get(i);
			uint8 val = get(key);

			buf.append(key);

			if (val == 0x00)	{
				buf.append(0xFF);
				buf.append(0x01);
			} else if (val == 0xFF) {
				buf.append(0xFF);
				buf.append(0x02);
			} else
				buf.append(val);
		}

		buf.append(0xFF);
		buf.append(0x03);
	}

};

#endif /*CUSTOMIZATIONVARIABLES_H_*/
