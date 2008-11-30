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

#ifndef SHIPOBJECTMESSAGE3_H_
#define SHIPOBJECTMESSAGE3_H_

#include "../../packets/BaseLineMessage.h"

#include "../../objects/ship/ShipObject.h"
#include "../../objects/tangible/component/ShipComponent.h"

/*
 * This packet is in active reversing. Subject to differ from documentation until final revision
 * is worked out.
 */

class ShipObjectMessage3 : public BaseLineMessage {
public:
	ShipObjectMessage3(ShipObject* ship)
			: BaseLineMessage(ship->getObjectID(), 0x53484950, 3, 0x16) {
				
		insertFloat(1.0f);
		
		insertAscii("space_ship"); //stf file to look up the name
		insertInt(0); //spacer
		insertAscii(ship->getStfName()); //ex. player_prototype_hutt_light
		insertUnicode(ship->getOwnerName());
		
		insertInt(0x01);
		insertShort(0);
		insertInt(0);
		insertInt(0);
		insertInt(0x01);
		insertInt(0);
		insertInt(0);
		
		insertInt(0x64);
		/* original:
		insertInt(0); //0x01, 0x33, 0x33, 0xF3, 
		insertByte(0x3F);
		*/
		
		insertByte(0x01);
		insertFloat(1.9f);
		
		insertFloat(ship->getChassisCur());
		insertFloat(ship->getChassisMax());
		
		//something to do w/ engine? tried the other int and it caused a sound warning in visual studio debug
		insertInt(0x16B73FE9); //0xE9, 0x3F, 0xB7, 0x16,
		
		//Lists Begin
		
		insertCurArmorList(ship);
		insertMaxArmorList(ship);
		insertCurHitpointsList(ship);
		insertMaxHitpointsList(ship);
		insertUnkList(ship);
		
		insertFloat(ship->getFrontshieldMax());
		insertFloat(ship->getBackshieldMax());
		
	}
	
	void insertCurArmorList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextCurArmorUpdateCnt());
		
		/*for (int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if (tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getCurArmor());
			}
			delete tsc;
		}*/
	}
	
	void insertMaxArmorList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextMaxArmorUpdateCnt());
		
		/*for (int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if (tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getMaxArmor());
			}
			delete tsc;
		}*/
	}
	
	void insertCurHitpointsList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextCurHitpointsUpdateCnt());
		
		/*for (int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if (tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getCurHitpoints());
			}
			delete tsc;
		}*/
	}
	
	void insertMaxHitpointsList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextMaxHitpointsUpdateCnt());
		
		/*for (int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if (tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getMaxHitpoints());
			}
			delete tsc;
		}*/
	}
	
	//this list sets unk values for active components to 0x02 (int)
	void insertUnkList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextUnkShip3UpdateCnt());
		
		/*for (int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if (tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertInt(0x02);
			}
			delete tsc;
		}*/
	}
		
};

#endif /*SHIPOBJECTMESSAGE3_H_*/
