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

#ifndef CLOTHINGOBJECTIMPLEMENTATION_H_
#define CLOTHINGOBJECTIMPLEMENTATION_H_

#include "ClothingObject.h"

class ClothingObjectImplementation : public ClothingObjectServant {
protected:

public:
	static const int BANDOLIER = 0x1000001;
	static const int BELT = 0x100002;
	static const int BODYSUIT = 0x100003;
	static const int CAPE = 0x100004;
	static const int CLOAK = 0x100005;
	static const int FOOTWEAR = 0x100006;
	static const int DRESS = 0x100007;
	static const int HANDWEAR = 0x100008;
	static const int EYEWEAR = 0x100009;
	static const int HEADWEAR = 0x10000A;
	static const int JACKET = 0x10000B;
	static const int PANTS = 0x10000C;
	static const int ROBE = 0x10000D;
	static const int SHIRT = 0x10000E;
	static const int VEST = 0x10000F;
	static const int WOOKIEGARB = 0x100010;
	static const int MISCCLOTHING = 0x100011;
	static const int SKIRT = 0x100012;
	static const int ITHOGARB = 0x100013;

public:
	ClothingObjectImplementation();
	~ClothingObjectImplementation();

	//Setters

	//Getters
};

#endif /* CLOTHINGOBJECTIMPLEMENTATION_H_ */
