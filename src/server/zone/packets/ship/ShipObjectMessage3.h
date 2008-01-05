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
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getCurArmor());
			}
			delete tsc;
		}
	}
	
	void insertMaxArmorList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextMaxArmorUpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getMaxArmor());
			}
			delete tsc;
		}
	}
	
	void insertCurHitpointsList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextCurHitpointsUpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getCurHitpoints());
			}
			delete tsc;
		}
	}
	
	void insertMaxHitpointsList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextMaxHitpointsUpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getMaxHitpoints());
			}
			delete tsc;
		}
	}
	
	//this list sets unk values for active components to 0x02 (int)
	void insertUnkList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextUnkShip3UpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertInt(0x02);
			}
			delete tsc;
		}
	}
		
};

#endif /*SHIPOBJECTMESSAGE3_H_*/
