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
    "terrain/corellia.trn", // 0
    "terrain/dantooine.trn", // 1
    "terrain/dathomir.trn", // 2
    "terrain/endor.trn", // 3
    "terrain/lok.trn", // 4
    "terrain/naboo.trn", // 5
    "terrain/rori.trn", // 6
    "terrain/talus.trn", // 7
    "terrain/tatooine.trn", // 8
    "terrain/yavin4.trn", // 9
    "terrain/space_corellia.trn", // 10
    "terrain/space_corellia_2.trn", // 11
    "terrain/space_dantooine.trn", // 12
    "terrain/space_dathomir.trn", // 13
    "terrain/space_endor.trn", // 14
    "terrain/space_env.trn", // 15
    "terrain/space_halos.trn", // 16
    "terrain/space_heavy1.trn", // 17
    "terrain/space_light1.trn", // 18
    "terrain/space_lok.trn", // 19
    "terrain/space_naboo.trn", // 20
    "terrain/space_naboo_2.trn", // 21
    "terrain/space_tatooine.trn", // 22
    "terrain/space_tatooine_2.trn", // 23
    "terrain/space_yavin4.trn", // 24

    // Test/Unused
    "terrain/09.trn", // 25
    "terrain/10.trn", // 26
    "terrain/11.trn", // 27
    "terrain/character_farm.trn", // 28
    "terrain/cinco_city_test_m5.trn", // 29
    "terrain/creature_test.trn", // 30
    "terrain/dungeon1.trn", // 31
    "terrain/endor_asommers.trn", // 32
    "terrain/floratest.trn", // 33
    "terrain/godclient_test.trn", // 34
    "terrain/otoh_gunga.trn", // 35
    "terrain/rivertest.trn", // 36
    "terrain/runtimerules.trn", // 37
    "terrain/simple.trn", // 38
    "terrain/space_09.trn", // 39
    "terrain/taanab.trn", // 40
    "terrain/test_wearables.trn", // 41
    "terrain/tutorial.trn", // 42
    "terrain/umbra.trn", // 43
    "terrain/watertabletest.trn" // 44
};

class Terrain {
public:
	inline const static char* getZoneName(int terrainid) {
		return TerrainNames[terrainid];
	}

};

#endif /*TERRAIN_H_*/
