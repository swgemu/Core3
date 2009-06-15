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

#ifndef SPECIES_H_
#define SPECIES_H_

#include "engine/engine.h"

static const char* SpeciesNames[] = {
    "human",
    "trandoshan",
    "twilek",
    "bothan",
    "zabrak",
    "rodian",
    "moncal",
    "wookiee",
    "sullustan",
    "ithorian",
};

static uint32 attributeLimits[10][19] = {
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

class Species : public DistributedObject {
protected:
	String species;
	String gender;
	String templatePath;
	uint32 speciesCRC;
	uint32* attributeLimits;

public:
	Species(const String& speciesname, const String& sex, uint32* attributelimits) : DistributedObject() {
		species = speciesname;
		gender = sex;

		//Make the template path.
		templatePath = "object/creature/player/shared_" + species + "_" + gender + ".iff";
		speciesCRC = templatePath.hashCode();

		attributeLimits = attributelimits;
	}

	~Species() {
	}

	/**
	 * Used to get the SpeciesID from a racefile during character creation, this number can then
	 * be used to get the static Species from the SpeciesList.
	 * \param racefile A string file path sent by the client during character creation.
	 * \return int An index corresponding to the SpeciesList.
	 */
	static int getSpeciesID(const String& racefile) {
		int idx1 = racefile.lastIndexOf("/");
		int idx2 = racefile.lastIndexOf("_");
		int idx3 = racefile.lastIndexOf(".");

		if (idx1 == -1 || idx2 == -1 || idx3 == -1)
			return 0;

		String species = racefile.subString(idx1 + 1, idx2);
		String gender = racefile.subString(idx2 + 1, idx3);

		for (int i = 0; i < 10; ++i) {
			if (SpeciesNames[i] == species) {
				if (gender.indexOf("female"))
					return (i + 10); //The female species come after the male species.

				return i;
			}
		}

		return 0;
	}

	//Getters
	inline String& getSpeciesName() {
		return species;
	}

	inline String& getGender() {
		return gender;
	}

	inline String& getTemplatePath() {
		return templatePath;
	}

	inline uint32 getSpeciesCRC() {
		return speciesCRC;
	}

	inline uint32 getAttributeLimit(uint8 attribute) {
		return attributeLimits[attribute];
	}

	inline uint32 getAttributeTotals() {
		return attributeLimits[9];
	}
};

//Since these are static, we have to make one for both male and female.
static Species* SpeciesList[20] = {
	//Males
	new Species("human", "male", attributeLimits[0]),
	new Species("trandoshan", "male", attributeLimits[1]),
	new Species("twilek", "male", attributeLimits[2]),
	new Species("bothan", "male", attributeLimits[3]),
	new Species("zabrak", "male", attributeLimits[4]),
	new Species("rodian", "male", attributeLimits[5]),
	new Species("rodian", "male", attributeLimits[6]),
	new Species("wookiee", "male", attributeLimits[7]),
	new Species("sullustan", "male", attributeLimits[8]),
	new Species("ithorian", "male", attributeLimits[9]),

	//Females
	new Species("human", "female", attributeLimits[0]),
	new Species("trandoshan", "female", attributeLimits[1]),
	new Species("twilek", "female", attributeLimits[2]),
	new Species("bothan", "female", attributeLimits[3]),
	new Species("zabrak", "female", attributeLimits[4]),
	new Species("rodian", "female", attributeLimits[5]),
	new Species("rodian", "female", attributeLimits[6]),
	new Species("wookiee", "female", attributeLimits[7]),
	new Species("sullustan", "female", attributeLimits[8]),
	new Species("ithorian", "female", attributeLimits[9])
};

#endif /*SPECIES_H_*/
