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

#ifndef TERRAIN_H_
#define TERRAIN_H_

const static char* TerrainNames[] = {
    "terrain/corellia.trn",
    "terrain/dantooine.trn",
    "terrain/dathomir.trn",
    "terrain/endor.trn",
    "terrain/lok.trn",
    "terrain/naboo.trn",
    "terrain/rori.trn",
    "terrain/talus.trn",
    "terrain/tatooine.trn",
    "terrain/yavin4.trn",
    "terrain/space_corellia.trn",
    "terrain/space_corellia_2.trn",
    "terrain/space_dantooine.trn",
    "terrain/space_dathomir.trn",
    "terrain/space_endor.trn",
    "terrain/space_env.trn",
    "terrain/space_halos.trn",
    "terrain/space_heavy1.trn",
    "terrain/space_light1.trn",
    "terrain/space_lok.trn",
    "terrain/space_naboo.trn",
    "terrain/space_naboo_2.trn",
    "terrain/space_tatooine.trn",
    "terrain/space_tatooine_2.trn",
    "terrain/space_yavin4.trn",

    // Test/Unused
    "terrain/09.trn",
    "terrain/10.trn",
    "terrain/11.trn",
    "terrain/character_farm.trn",
    "terrain/cinco_city_test_m5.trn",
    "terrain/creature_test.trn",
    "terrain/dungeon1.trn",
    "terrain/endor_asommers.trn",
    "terrain/floratest.trn",
    "terrain/godclient_test.trn",
    "terrain/otoh_gunga.trn",
    "terrain/rivertest.trn",
    "terrain/runtimerules.trn",
    "terrain/simple.trn",
    "terrain/space_09.trn",
    "terrain/taanab.trn",
    "terrain/test_wearables.trn",
    "terrain/tutorial.trn",
    "terrain/umbra.trn",
    "terrain/watertabletest.trn"
};

class Terrain {
public:
	inline const static char* getTerrainName(int terrainid) {
		return TerrainNames[terrainid];
	}
	
};

#endif /*TERRAIN_H_*/
