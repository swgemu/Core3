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

const static char* MoodStr[][2]= {
	{"none", "neutral"},
	{"absentminded", "neutral"},
	{"amazed", "neutral"},
	{"amused", "happy"},
	{"angry", "angry"},
	{"approving", "neutral"},
	{"bitter", "neutral"},
	{"bloodthirsty", "neutral"},
	{"brave", "neutral"},
	{"callous", "neutral"},
	{"careful", "neutral"},
	{"careless", "neutral"},
	{"casual", "neutral"},
	{"clinical", "neutral"},
	{"cocky", "neutral"},
	{"cold", "neutral"},
	{"compassionate", "neutral"},
	{"condescending", "neutral"},
	{"confident", "neutral"},
	{"confused", "neutral"},
	{"content", "happy"},
	{"courtly", "neutral"},
	{"coy", "neutral"},
	{"crude", "neutral"},
	{"cruel", "neutral"},
	{"curious", "neutral"},
	{"cynical", "neutral"},
	{"defensive", "neutral"},
	{"depressed", "unhappy"},
	{"devious", "neutral"},
	{"dimwitted", "neutral"},
	{"disappointed", "unhappy"},
	{"discreet", "neutral"},
	{"disgruntled", "disgruntled"},
	{"disgusted", "neutral"},
	{"dismayed", "unhappy"},
	{"disoriented", "neutral"},
	{"distracted", "neutral"},
	{"doubtful", "neutral"},
	{"dramatic", "neutral"},
	{"dreamy", "neutral"},
	{"drunk", "neutral"},
	{"earnest", "neutral"},
	{"ecstatic", "happy"},
	{"embarrassed", "neutral"},
	{"emphatic", "neutral"},
	{"encouraging", "neutral"},
	{"enthusiastic", "neutral"},
	{"evil", "neutral"},
	{"exasperated", "disgruntled"},
	{"exuberant", "happy"},
	{"fanatical", "neutral"},
	{ "forgive", "neutral"},
	{"frustrated", "neutral"},
	{"guilty", "neutral"},
	{"happy", "happy"},
	{"honest", "neutral"},
	{"hopeful", "neutral"},
	{"hopeless", "neutral"},
	{"humble", "neutral"},
	{"hysterical", "neutral"},
	{"imploring", "neutral"},
	{"indifferent", "neutral"},
	{"indignant", "angry"},
	{"interested", "neutral"},
	{"jealous", "neutral"},
	{"joyful", "happy"},
	{"lofty", "neutral"},
	{"loud", "neutral"},
	{"loving", "neutral"},
	{"lustful", "neutral"},
    {"mean", "neutral"},
    {"mischievous", "neutral"},
    {"nervous", "neutral"},
    {"neutral", "neutral"},
    {"offended", "neutral"},
    {"optimistic", "neutral"},
    {"pedantic", "neutral"},
    {"pessimistic", "neutral"},
    {"petulant", "neutral"},
    {"philosophical", "neutral"},
    {"pitying", "neutral"},
    {"playful", "happy"},
    {"polite", "neutral"},
    {"pompous", "neutral"},
    {"proud", "neutral"},
    {"provocative", "neutral"},
    {"puzzled", "neutral"},
    {"regretful", "unhappy"},
    {"relieved", "neutral"},
    {"reluctant", "neutral"},
    {"resigned", "neutral"},
    {"respectful", "neutral"},
    {"romantic", "neutral"},
    {"rude", "neutral"},
    {"sad", "unhappy"},
    {"sarcastic", "neutral"},
    {"scared", "neutral"},
    {"scolding", "neutral"},
    {"scornful", "neutral"},
    {"serious", "neutral"},
    {"shameless", "neutral"},
    {"shocked", "neutral"},
    {"shy", "neutral"},
    {"sincere", "neutral"},
    {"sleepy", "neutral"},
    {"sly", "neutral"},
    {"smug", "neutral"},
    {"snobby", "neutral"},
    {"sorry", "neutral"},
    {"spiteful", "neutral"},
    {"stubborn", "neutral"},
    {"sullen", "neutral"},
    {"suspicious", "neutral"},
    {"taunting", "neutral"},
    {"terrified", "neutral"},
    {"thankful", "neutral"},
    {"thoughtful", "neutral"},
    {"tolerant", "neutral"},
    {"uncertain", "neutral"},
    {"unhappy", "unhappy"},
    {"unwilling", "neutral"},
    {"warm", "neutral"},
    {"whiny", "neutral"},
    {"wicked", "neutral"},
    {"wistful", "neutral"},
    {"worried", "worried"},
    {"tired", "neutral"},
    {"exhausted", "neutral"},
    {"friendly", "happy"},
    {"timid", "neutral"},
    {"lazy", "neutral"},
    {"surprised", "worried"},
    {"innocent", "happy"},
    {"wise", "neutral"},
    {"youthful", "neutral"},
    {"adventurous", "neutral"},
    {"annoyed", "angry"},
    {"perturbed", "unhappy"},
    {"sedate", "neutral"},
    {"calm", "neutral"},
    {"suffering", "unhappy"},
    {"hungry", "neutral"},
    {"thirsty", "neutral"},
    {"alert", "neutral"},
    {"shifty", "neutral"},
    {"relaxed", "neutral"},
    {"crotchety", "angry"},
    {"surly", "angry"},
    {"painful", "unhappy"},
    {"wounded", "unhappy"},
    {"bubbly", "happy"},
    {"heroic", "neutral"},
    {"quiet", "neutral"},
    {"remorseful", "unhappy"},
    {"grumpy", "angry"},
    {"logical", "neutral"},
    {"emotional", "neutral"},
    {"troubled", "unhappy"},
    {"panicked", "worried"},
    {"nice", "happy"},
    {"cheerful", "happy"},
    {"emotionless", "neutral"},
    {"gloomy", "unhappy"},
    {"ambivalent", "neutral"},
    {"envious", "neutral"},
    {"vengeful", "angry"},
    {"fearful", "worried"},
    {"enraged", "angry"},
    {"sheepish", "happy"},
    {"belligerent", "angry"},
    {"obnoxious", "neutral"},
    {"fastidious", "neutral"},
    {"squeamish", "unhappy"},
    {"dainty", "neutral"},
    {"dignified", "neutral"},
    {"haughty", "neutral"},
    {"obscure", "neutral"},
    {"goofy", "happy"},
    {"silly", "happy"},
    {"disdainful", "neutral"},
    {"contemptuous", "neutral"},
    {"diplomatic", "neutral"},
    {"wary", "neutral"},
    {"malevolent", "angry"},
    {"hurried", "neutral"},
    {"patient", "neutral"},
    {"firm", "neutral"},
    {"meditating", "meditating"},
	{"entertained", "entertained"}

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
		return RaceStrs[raceid];
	}

	inline static int getSpeciesID(int raceid) {
		return TemplateSpecies[raceid];
	}

	inline const static char* getMood(int moodid) {
		return MoodStr[moodid][0];
	}

	inline const static char* getSpecies(int raceid) {
		return Species[raceid];
	}

	inline const static char* getGender(int raceid) {
		return Gender[raceid];
	}

	inline static uint32 getRaceCRC(int raceid) {
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

	inline static int getMoodID(const String& name) {
    	for (int i = 0; i < 190; i++) {
        	if (strcmp(name.toCharArray(), MoodStr[i][0]) == 0)
            	return i;
    	}

    	return 0;
	}

	inline const static char* getMoodStr(const String& name) {
		for (int i = 0; i < 190; i++) {
			if (strcmp(name.toCharArray(), MoodStr[i][0]) == 0)
				return MoodStr[i][1];
		}

		return MoodStr[0][1];
	}

	inline static unsigned int * getAttribLimits(int raceid) {
		return attributeLimits[raceid % 10];
	}

};

#endif /*RACES_H_*/
