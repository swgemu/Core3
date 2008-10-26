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

#ifndef WEARABLEIMPLEMENTATION_H_
#define WEARABLEIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"

#include "Wearable.h"

class WearableImplementation : public WearableServant {
public:

	// Areas covered
	static const int CHEST = 0x0001;
	static const int HAND = 0x0002;
	static const int BRACERL = 0x0004;
	static const int BICEPL = 0x0008;
	static const int BRACERR = 0x0010;
	static const int BICEPR = 0x0020;
	static const int LEG = 0x0040;
	static const int FOOT = 0x0080;
	static const int HEAD = 0x0100;
	static const int BELT = 0x0200;  // special case as a belt can go over most clothing
	static const int SHIRT = 0x0400;  // special case as a shirt can go under most clothing.
	static const int BACKPACK = 0x0800;

	WearableImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp = false)
			: WearableServant(objid, CLOTHING) {
		objectCRC = tempCRC;

		name = n;

		templateTypeName = "wearables_name";
		templateName = tempn;

		equipped = eqp;
	}

	WearableImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp = false)
		: WearableServant(oid, CLOTHING) {
		objectCRC = tempCRC;

		name = n;

		templateTypeName = "wearables_name";
		templateName = tempn;

		if ((equipped = eqp))
			setContainer(creature, 0x04);
		else
			setContainer((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);
	}

	WearableImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp = false)
			: WearableServant(creature->getNewItemID(), CLOTHING) {
		objectCRC = tempCRC;

		name = n;

		templateTypeName = "wearables_name";
		templateName = tempn;

		if ((equipped = eqp))
			setContainer(creature, 0x04);
		else
			setContainer((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);
	}

};

#endif /*WEARABLEIMPLEMENTATION_H_*/
