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

#ifndef BADGESIMPLEMENTATION_H_
#define BADGESIMPLEMENTATION_H_

#include "Badges.h"
#include "Badge.h"

class BadgesImplementation : public BadgesServant {
	uint32 badgeBitmask[5];
	uint8 badgeTypeCounts[6];
	uint8 badgeTotal;

public:

	BadgesImplementation() {
		for (int i = 0; i < 5; ++i)
			badgeBitmask[i] = 0;

		for (int i = 0; i < 6; ++i)
			badgeTypeCounts[i] = 0;

		badgeTotal = 0;
	}

	~BadgesImplementation() {
	}

public:
	void setBadge(int badgeindex) {
		int bitmaskNumber = badgeindex >> 5;

		uint32 bit = badgeindex % 32;
		uint32 value = 1 << bit;

		if (!(badgeBitmask[bitmaskNumber] & value)) {
			badgeBitmask[bitmaskNumber] |= value;
			badgeTypeCounts[Badge::getType(badgeindex)]++;
			badgeTotal++;
		}
	}

	void unsetBadge(int badgeindex) {
		int bitmaskNumber = badgeindex >> 5;

		uint32 bit = badgeindex % 32;
		uint32 value = 1 << bit;

		if (badgeBitmask[bitmaskNumber] & value) {
			badgeBitmask[bitmaskNumber] -= value;
			badgeTypeCounts[Badge::getType(badgeindex)]--;
			badgeTotal--;
		}
	}



	bool hasBadge(int badgeindex) {
		int bitmaskNumber = badgeindex >> 5;

		uint32 bit = badgeindex % 32;
		uint32 value = 1 << bit;

		return badgeBitmask[bitmaskNumber] & value;
	}

	void setBitmask(int index, uint32 bitmask) {
		badgeBitmask[index] = bitmask;
	}

	uint32 getBitmask(int index) {
		return badgeBitmask[index];
	}

	void setTypeCount(uint8 index, uint8 value) {
		badgeTypeCounts[index] = value;
	}

	uint8 getTypeCount(uint8 type) {
		return badgeTypeCounts[type];
	}

	uint8 getNumBadges() {
		return badgeTotal;
	}

	void setNumBadges(uint8 value) {
		badgeTotal = value;
	}



};

#endif /*BADGESIMPLEMENTATION_H_*/
