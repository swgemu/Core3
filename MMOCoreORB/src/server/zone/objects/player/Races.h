/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RACES_H_
#define RACES_H_

#include "system/lang.h"

const static char* Species[] = {
    "human", // human male
    "trandoshan", // trandoshan male
    "twilek", // twilek male
    "bothan", // bothan male
    "zabrak", // zabrak male
    "rodian", // rodian male
    "moncal", // moncal male
    "wookiee", // wookiee male
    "sullustan", // sullustan male
    "ithorian", // ithorian male
    "human", // human female
    "trandoshan", // trandoshan female
    "twilek", // twilek female
    "bothan", // bothan female
    "zabrak", // zabrak female
    "rodian", // rodian female
    "moncal", // moncal female
    "wookiee", // wookiee female
    "sullustan", // sullustan female
    "ithorian"  // DA E7   -   ithorian female
};

const static int TemplateSpecies[] = {
		0,
		2,
		6,
		5,
		7,
		1,
		3,
		4,
		0x31,
		0x21,
		0,
		2,
		6,
		5,
		7,
		1,
		3,
		4,
		0x31,
		0x21
};

const static char* Gender[] = {
    "male", // human male
    "male", // trandoshan male
    "male", // twilek male
    "male", // bothan male
    "male", // zabrak male
    "male", // rodian male
    "male", // moncal male
    "male", // wookiee male
    "male", // sullustan male
    "male", // ithorian male
    "female", // human female
    "female", // trandoshan female
    "female", // twilek female
    "female", // bothan female
    "female", // zabrak female
    "female", // rodian female
    "female", // moncal female
    "female", // wookiee female
    "female", // sullustan female
    "female"  // DA E7   -   ithorian female
};

const static char* RaceStrs[] = {
    "object/creature/player/shared_human_male.iff", // human male
    "object/creature/player/shared_trandoshan_male.iff", // trandoshan male
    "object/creature/player/shared_twilek_male.iff", // twilek male
    "object/creature/player/shared_bothan_male.iff", // bothan male
    "object/creature/player/shared_zabrak_male.iff", // zabrak male
    "object/creature/player/shared_rodian_male.iff", // rodian male
    "object/creature/player/shared_moncal_male.iff", // moncal male
    "object/creature/player/shared_wookiee_male.iff", // wookiee male
    "object/creature/player/shared_sullustan_male.iff", // sullustan male
    "object/creature/player/shared_ithorian_male.iff", // ithorian male
    "object/creature/player/shared_human_female.iff", // human female
    "object/creature/player/shared_trandoshan_female.iff", // trandoshan female
    "object/creature/player/shared_twilek_female.iff", // twilek female
    "object/creature/player/shared_bothan_female.iff", // bothan female
    "object/creature/player/shared_zabrak_female.iff", // zabrak female
    "object/creature/player/shared_rodian_female.iff", // rodian female
    "object/creature/player/shared_moncal_female.iff", // moncal female
    "object/creature/player/shared_wookiee_female.iff", // wookiee female
    "object/creature/player/shared_sullustan_female.iff", // sullustan female
    "object/creature/player/shared_ithorian_female.iff"  // DA E7   -   ithorian female
};

const static char* CCRaceStrs[] = {
    "object/creature/player/human_male.iff", // human male
    "object/creature/player/trandoshan_male.iff", // trandoshan male
    "object/creature/player/twilek_male.iff", // twilek male
    "object/creature/player/bothan_male.iff", // bothan male
    "object/creature/player/zabrak_male.iff", // zabrak male
    "object/creature/player/rodian_male.iff", // rodian male
    "object/creature/player/moncal_male.iff", // moncal male
    "object/creature/player/wookiee_male.iff", // wookiee male
    "object/creature/player/sullustan_male.iff", // sullustan male
    "object/creature/player/ithorian_male.iff", // ithorian male
    "object/creature/player/human_female.iff", // human female
    "object/creature/player/trandoshan_female.iff", // trandoshan female
    "object/creature/player/twilek_female.iff", // twilek female
    "object/creature/player/bothan_female.iff", // bothan female
    "object/creature/player/zabrak_female.iff", // zabrak female
    "object/creature/player/rodian_female.iff", // rodian female
    "object/creature/player/moncal_female.iff", // moncal female
    "object/creature/player/wookiee_female.iff", // wookiee female
    "object/creature/player/sullustan_female.iff", // sullustan female
    "object/creature/player/ithorian_female.iff"  // DA E7   -   ithorian female
};

static uint32 SharedRace[] = {
    0xAF1DC1A1,
    0x50C45B8F,
    0xF280E27B,
    0x5BF77F33,
    0xE204A556,
    0x0BF9CD9C,
    0xB9C855A8,
    0x0564791D,
    0x0B9399A4,
    0x38BAC7C4,
    0xFFFFBBE9,
    0x183C24C6,
    0x849752DC,
    0x1D52730E,
    0xA9E35FFD,
    0xC264245B,
    0x982FBFDE,
    0x0DAB65E2,
    0x1573341A,
    0xB3E08013
};

static unsigned int attributeLimits[10][19] = {
		{400, 1100,	400, 1100,  400, 1100, 400, 1100, 400, 1100, 400, 1100,	400, 1100, 400,	1100, 400, 1100, 5400},
		{550, 1250,	600,  800,	700,  800, 300,	1000, 300,  450, 300,  400,	300, 1000, 300,	 500, 300,	600, 5550},
		{300, 1000,	300,  500,	550,  650, 550,	1250, 600,	750, 300,  400,	400, 1100, 300,	 500, 300,	500, 5400},
		{300, 1000,	300,  500,	300,  400, 600,	1300, 600,	750, 400,  500,	400, 1100, 400,	 600, 300,	500, 5400},
		{500, 1200,	300,  500,	300,  400, 600,	1300, 300,	450, 300,  400,	300, 1000, 300,	 500, 700,	900, 5400},
		{300, 1000,	300,  500,	300,  400, 300,	1200, 300,	650, 450,  850,	300, 1000, 300,	 500, 350,	550, 5400},
		{300, 1000,	300,  500,	300,  400, 300,	1000, 300,	450, 450,  550,	600, 1300, 600,	 800, 450,	650, 5400},
		{650, 1350,	650,  850,	450,  550, 500,	1200, 400,	550, 400,  500,	400, 1100, 450,	 650, 400,	600, 6100},
		{300, 1200,	300,  500,	300,  400, 600,	1400, 300,	750, 300,  500,	400, 1200, 400,	 600, 300,	600, 5400},
		{300, 1400,	300,  600,	300,  500, 600,	1100, 300,	750, 300,  500,	400, 1300, 400,	 600, 300,	500, 5400}
};

class Races {
public:
	inline const static char* getRace(int raceid) {
		if (raceid < 0 || raceid > 19)
			return "";

		return RaceStrs[raceid];
	}

	inline static int getSpeciesID(int raceid) {
		if (raceid < 0 || raceid > 19)
			return 0;

		return TemplateSpecies[raceid];
	}

	inline const static char* getSpecies(int raceid) {
		if (raceid < 0 || raceid > 19)
			return "";

		return Species[raceid];
	}

	inline const static char* getGender(int raceid) {
		if (raceid < 0 || raceid > 19)
			return "";

		return Gender[raceid];
	}

	inline static uint32 getRaceCRC(int raceid) {
		if (raceid < 0 || raceid > 19)
			return 0;

		return SharedRace[raceid];
	}

	inline static const char* getCompleteRace(uint32 sharedRaceCRC) {
		int race = -1;
		for (int i = 0; i < 20; ++i) {
			if (SharedRace[i] == sharedRaceCRC) {
				race = i;
				break;
			}
		}

		if (race == -1)
			return "";
		else
			return CCRaceStrs[race];
	}

	inline static int getRaceID(const String& name) {
    	for (int i = 0; i < 20; i++) {
        	if (strcmp(name.toCharArray(), CCRaceStrs[i]) == 0)
            	return i;
    	}

    	return 0;
	}

	inline static unsigned int * getAttribLimits(int raceid) {
		return attributeLimits[raceid % 10];
	}

};

#endif /*RACES_H_*/
