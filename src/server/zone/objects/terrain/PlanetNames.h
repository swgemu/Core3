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

const static char* PlanetNames[] = {
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

class Planet {
	
public:
	inline const static char* getPlanetName(int id) {
		return PlanetNames[id];
	}
	
	const static int getPlanetID(const string& name) {
		for (int i = 0; i < 10; ++i) {
			if (name == PlanetNames[i])
				return i;
		}
	}
	
};

#endif /*PLANETNAMES_H_*/
