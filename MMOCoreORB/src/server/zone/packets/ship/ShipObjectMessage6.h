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

#include "../../packets/BaseLineMessage.h"

#include "../../objects/ship/ShipObject.h"
#include "../../objects/tangible/component/ShipComponent.h"

/*
 * This packet is in active reversing. Subject to differ from documentation until final revision
 * is worked out.
 */

class ShipObjectMessage6 : public BaseLineMessage {
public:
	ShipObjectMessage6(ShipObject* ship)
			: BaseLineMessage(ship->getObjectID(), 0x53484950, 6, 0x18) {
				
		insertInt(0x8B);
		
		insertInt(0);
		insertInt(0);
		insertShort(0);
		
		insertFloat(0);
		insertFloat(1.0f); //min speed
		insertFloat(50.0f);
		insertFloat(50.0f);
		
		//first 3 have something to do with pitch, yaw, and roll
		insertFloat(10.472f);
		insertFloat(10.472f);
		insertFloat(5.23599f); //note: 1/2 of first 2 floats
		insertFloat(0.753982f);
		insertFloat(ship->getMaxSpeed()); //this value * 10 = max speed
		
		insertLong(ship->getObjectID());
		
		insertInt(0); //LENGTH FOR SOMETHING, swg will allocate this number of bytes
		
		//(list?)
		insertInt(0);
		insertInt(0);
		
		insertCrcList(ship);
		
		//pretty sure these shorts are 2 int's for lists.
		insertShort(0);
		insertShort(0);
		insertShort(0);
		insertShort(0);
		
		insertFloat(ship->getFrontshieldCur());
		insertFloat(ship->getBackshieldCur());
		
		insertInt(0); //?
	}
	
	void insertCrcList(ShipObject* ship) {
		/*
		List struct:
		INT: List Size
		INT: Update Count
		{
    		BYTE: ??
    		INT: Component Index
    		INT: Component CRC
		}
		*/
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextCrcUpdateCnt());
		
		/*for (int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if (tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertInt(tsc->getComponentCrc());
			}
			delete tsc;
		}*/
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
