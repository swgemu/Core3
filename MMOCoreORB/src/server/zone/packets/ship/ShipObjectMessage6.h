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

#ifndef SHIPOBJECTMESSAGE6_H_
#define SHIPOBJECTMESSAGE6_H_

#include "../../packets/tangible/TangibleObjectMessage6.h"
#include "../../objects/ship/ShipObject.h"

class ShipObjectMessage6 : public TangibleObjectMessage6 {
public:
	ShipObjectMessage6(ShipObject* ship)
			: TangibleObjectMessage6(ship, 0x53484950, 0x18) {

		insertShort(ship->getUniqueID());

		insertFloat(50.f);
		insertFloat(50.f); //min speed

		insertFloat(0.174532935 * 4);
		insertFloat(0.174532935 * 4);
		insertFloat(0.174532935 * 4);

		insertFloat(1.260066867 * 4);
		insertFloat(1.260066867 * 4);
		insertFloat(1.260066867 * 4);

		insertFloat(50.f); // max speed
		//insertLong(ship->getObjectID()); //This is zeroed out on NGE packet caps?
		insertLong(0);

		insertInt(0); //length
		insertInt(0); // list?

		insertInt(0);

		//components
		insertInt(7);
		insertInt(7);

		insertByte(0);
		insertInt(0);
		insertInt(0x9abdbfdc); // 0xDC, 0xBF, 0xBD, 0x9A,

		insertByte(0);
		insertInt(1);
		insertInt(0x35a0c705); // 0x05, 0xC7, 0xA0, 0x35,

		insertByte(0);
		insertInt(2);
		insertInt(0xe73217be); // 0xBE, 0x17, 0x32, 0xE7

		insertByte(0);
		insertInt(4);
		insertInt(0x9e60cbe1); // 0x9E, 0x60, 0xCB, 0xE1,

		insertByte(0);
		insertInt(5);
		insertInt(0x9e60cbe1); // 0x9E, 0x60, 0xCB, 0xE1,

		insertByte(0);
		insertInt(6);
		insertInt(0x20ced6ee); // 0xEE, 0xD6, 0xCE, 0x20,

		insertByte(0);
		insertInt(0x0f);
		insertInt(0x2c823c3d); //0x3D, 0x3C, 0x82, 0x2C,



		insertInt(0);
		insertInt(0);

/*

		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);

		insertInt(0); //List
		insertInt(0);

		insertInt(0);
		insertInt(0);*/

		insertFloat(300.f);
		insertFloat(300.f);

		insertInt(0);

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
