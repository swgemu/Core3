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

#ifndef FACTIONRANK_H_
#define FACTIONRANK_H_

#include "engine/engine.h"

class FactionRank : public DistributedObject {
protected:
	String rankTitle;
	uint32 pointsCost;
	uint32 pointsMax;
	float conversionRatio;

public:
	FactionRank(const String& title, uint32 cost, uint32 max, float ratio) : DistributedObject() {
		rankTitle = title;
		pointsCost = cost;
		pointsMax = max;
		conversionRatio = ratio;
	}

	//Getters
	inline String& getRankTitle() {
		return rankTitle;
	}

	inline uint32 getPointsCost() {
		return pointsCost;
	}

	inline uint32 getPointsMax() {
		return pointsMax;
	}

	inline float getConversionRatio() {
		return conversionRatio;
	}
};

static FactionRank* FactionRankList[16] = {
	new FactionRank("", 0, 1000, 6.5f),
	new FactionRank("private", 200, 1000, 6.5f),
	new FactionRank("lance_corporal", 400, 8000, 5.0f),
	new FactionRank("corporal", 800, 16000, 4.0f),
	new FactionRank("staff_corporal", 1200, 24000, 4.0f),
	new FactionRank("sergeant", 1600, 32000, 2.86f),
	new FactionRank("staff_sergeant", 2000, 40000, 2.5f),
	new FactionRank("master_sergeant", 2500, 50000, 2.3f),
	new FactionRank("warrant_officer_2", 3000, 60000, 2.0f),
	new FactionRank("warrant_officer_1", 3500, 70000, 1.8f),
	new FactionRank("second_lieutenant", 4000, 80000, 1.67f),
	new FactionRank("lieutenant", 5000, 100000, 1.54f),
	new FactionRank("captain", 5000, 100000, 1.43f),
	new FactionRank("major", 5500, 110000, 1.34f),
	new FactionRank("lieutenant_colonel", 5500, 110000, 1.25f),
	new FactionRank("colonel", 6000, 120000, 1.18f)
};

#endif /* FACTIONRANK_H_ */
