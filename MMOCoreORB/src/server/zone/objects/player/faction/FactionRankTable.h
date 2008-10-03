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


#ifndef FACTIONRANKTABLE_H_
#define FACTIONRANKTABLE_H_
/*
Imperial/Rebel (Cost:0/200) 1,000 (Delegate Costs 650 to send 100)

Private (Cost:10)  1,000 (Delegate Costs 650 to send 100)

Lance Corporal (Cost:400) 8,000 (Delegate Costs 500 to send 100)

Corporal (Cost:800) 16,000 (Delegate Costs 400 to send 100)

Staff Corporal (Cost:1,200) 24,000 (Delegate Costs 400 to send 100)
"this rank is needed to use factional base turret terminals"

Sergeant (Cost:1,600) 32,000 (Delegate Costs 286 to send 100)

Staff Sergeant (Cost:2,000) 40,000 (Delegate Costs 250 to send 100)

Master Sergeant (Cost:2,500) 50,000 (Delegate Costs 230 to send 100)

Warrant Officer II (Cost:3,000) 60,000 (Delegate Costs 200 to send 100)
"this rank allows you to see ally base vulnerable timers, also immune to ally faction searchs, due to officer rank"

Warrant Officer I (Cost:3,500) 70,000 (Delegate Costs 180 to send 100)

Second Lieutenant (Cost:4,000) 80,000 (Delegate Costs 167 to send 100)

Lieutenant (Cost:5,000) 100,000 (Delegate Costs 154 to send 100)

Captain (Cost:5,000) 100,000 (Delegate Costs 143 to send 100)

Major (Cost:5,500) 110,000 (Delegate Costs 134 to send 100)

Lieutenant Colonel (Cost:5,500) 110,000 (Delegate Costs 125 to send 100)

Colonel (Cost:6,000) 120,000 (Delegate Costs 118 to send 100)
 */

static const string rankNames[16] = { "", "private",
		"lance_corporal", "corporal", "staff_corporal", "sergeant",
		"staff_sergeant", "master_sergeant", "warrant_officer_2",
		"warrant_officer_1", "second_lieutenant", "lieutenant", "captain",
		"major", "lieutenant_colonel", "colonel" };

static const uint16 points[16] = { 0, 10, 400, 800, 1200, 1600,
		2000, 2500, 3000, 3500, 4000, 5000, 5000, 5500, 5500, 6000 };

static const float ratio[16] = { 6.5, 6.5, 5, 4, 4, 2.86, 2.5, 2.3,
		2, 1.8, 1.67, 1.54, 1.43, 1.34, 1.25, 1.18 };

static const uint32 cap[16] = { 1000, 1000, 8000, 16000, 24000,
		32000, 40000, 50000, 60000, 70000, 80000, 100000, 100000, 110000,
		110000, 120000 };

class FactionRankTable {

public:
	inline static bool rankExists(uint8 rank) {
		return rank < 16;
	}

	inline static const string getRankName(uint8 rank) {
		if (!rankExists(rank))
			return "";

		return rankNames[rank];
	}

	inline static const uint16 getRequiredPoints(uint8 rank) {
		if (!rankExists(rank))
			return 0;

		return points[rank];
	}

	inline static const float getDelegateRatio(uint8 rank) {
		if (!rankExists(rank))
			return 0;

		return ratio[rank];
	}

	inline static const uint32 getFPCap(uint8 rank) {
		if (!rankExists(rank))
			return 0;

		return cap[rank];
	}
};

#endif /* FACTIONRANKTABLE_H_ */
