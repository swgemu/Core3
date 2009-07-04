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
#ifndef DAMAGEDONE_H_
#define DAMAGEDONE_H_

#include "engine/engine.h"

class DamageDone : public Serializable {
	protected:
	VectorMap<String, int> xpDamage;
	VectorMap<String, int> xpLevel;

	int totalDamage;

	public:
	DamageDone() : Serializable() {
		xpDamage.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);
		xpLevel.setInsertPlan(SortedVector<int>::ALLOW_OVERWRITE);

		xpDamage.removeAll();
		xpLevel.removeAll();

		totalDamage = 0;

		addSerializableVariable("xpDamage", &xpDamage);
		addSerializableVariable("xpLevel", &xpLevel);
		addSerializableVariable("totalDamage", &totalDamage);
	}

	~DamageDone() {
		xpDamage.removeAll();
		xpLevel.removeAll();
	}

	void addDamage( String xptype, int damage, int level ) {
		totalDamage += damage;

		if (xpDamage.contains(xptype)) {
			damage += xpDamage.get(xptype);
			xpDamage.drop(xptype);
		}

		xpDamage.put(xptype, damage);

		if (!xpLevel.contains(xptype))
			xpLevel.put(xptype, level);
	}

	int getSize() {
		return xpDamage.size();
	}

	String getXpType(int idx) {
		VectorMapEntry<String, int> entry = xpDamage.SortedVector<VectorMapEntry<String, int> >::get(idx);
		return entry.getKey();
	}

	int getDamage(int idx) {
		return xpDamage.get(idx);
	}

	int getDamage(String xptype) {
		return xpDamage.get(xptype);
	}

	int getLevel(int idx) {
		return xpLevel.get(idx);
	}

	int getLevel(String xptype) {
		return xpLevel.get(xptype);
	}

	int getTotalDamage() {
		return totalDamage;
	}
};

#endif /*DAMAGEDONE_H_*/
