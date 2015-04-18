/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
