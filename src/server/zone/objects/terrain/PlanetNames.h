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

#ifndef PLANETNAMES_H_
#define PLANETNAMES_H_

const static char* planetNames[] = {
		"corellia",
		"dantooine",
		"dathomir",
		"endor",
		"lok",
		"naboo",
		"rori",
		"talus",
		"tatooine",
		"yavin4",
		"space_corellia",
		"space_corellia_2",
		"space_dantooine",
		"space_dathomir",
		"space_endor",
		"space_env",
		"space_halos",
		"space_heavy1",
		"space_light1",
		"space_lok",
		"space_naboo",
		"space_naboo_2",
		"space_tatooine",
		"space_tatooine_2",
		"space_yavin4",

		// Test/Unused
		"09",
		"10",
		"11",
		"character_farm",
		"cinco_city_test_m5",
		"creature_test",
		"dungeon1",
		"endor_asommers",
		"floratest",
		"godclient_test",
		"otoh_gunga",
		"rivertest",
		"runtimerules",
		"simple",
		"space_09",
		"taanab",
		"test_wearables",
		"tutorial",
		"umbra",
		"watertabletest"
};

static int planetCrcs[] = {
		0x63556843, //corellia
		0x2748F9D7, //dantooine
		0x63E75AED, //dathomir
		0xA94ECA19, //endor
		0x578E8F4F, //lok
		0xAFD7B558, //naboo
		0x51D50A39, //rori
		0xB616FA38, //talus
		0x57279121, //tatooine
		0xC2A64B83, //yavin4
		0x574A0227, //space_corellia
		0xB19B288F, //space_corellia_2
		0xFF14869B, //space_dantooine
		0x57F83089, //space_dathomir
		0xFF172887, //space_endor
		0xF4CBEBED, //space_env
		0x386BD461, //space_halos
		0xB941C1ED, //space_heavy1
		0x7EFAF029, //space_light1
		0x5413BF2D, //space_lok
		0xF98E57C6, //space_naboo
		0x6745DC80, //space_naboo_2
		0x6338FB45, //space_tatooine
		0xD419829A, //space_tatooine_2
		0xF9553336, //space_yavin4

		// Test/Unused
		0x3941AB28, //09
		0xC9919AFB, //10
		0xCD50874C, //11
		0xE065F039, //character_farm
		0xB0E66F33, //cinco_city_test_m5
		0x2C6A8285, //creature_test
		0x171946CE, //dungeon1
		0x859E7A53, //endor_asommers
		0xE699FC49, //floratest
		0x26358B6C, //godclient_test
		0xD09ED2D6, //otoh_gunga
		0x7F3A707F, //rivertest
		0x5BF2EFDC, //runtimerules
		0xCCE51202, //simple
		0xCCDC4B8E, //space_09
		0x5D65571B, //taanab
		0x59E1A56, //test_wearables - WRONG
		0xB9E17522, //tutorial
		0x24E58F4, //umbra - WRONG
		0x8337AF3D, //watertabletest
};

class Planet {
public:
	inline const static char* getPlanetName(int id) {
		return planetNames[id];
	}

	inline const static char* getPlanetNameByCrc(int crc) {
		int id = 0;
		for(int i = 0; i < 10; ++i) {
			if (crc == planetCrcs[i])
				return getPlanetName(i);
		}
		return "";
	}

	static int getPlanetID(const String& name) {
		for (int i = 0; i < 10; ++i) {
			if (name == planetNames[i])
				return i;
		}

		return -1;
	}

	static int getPlanetCRC(const String& name) {
		for (int i = 0; i < 10; ++i) {
			if (name == planetNames[i]) {
				return planetCrcs[i];
			}
		}

		return -1;
	}

};

#endif /*PLANETNAMES_H_*/
