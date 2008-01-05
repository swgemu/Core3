#ifndef SHIPOBJECTMESSAGE1_H_
#define SHIPOBJECTMESSAGE1_H_

#include "../../packets/BaseLineMessage.h"

#include "../../objects/ship/ShipObject.h"
#include "../../objects/tangible/component/ShipComponent.h"

/*
 * This packet is in active reversing. Subject to differ from documentation until final revision
 * is worked out.
 */

class ShipObjectMessage1 : public BaseLineMessage {
public:
	ShipObjectMessage1(ShipObject* ship)
			: BaseLineMessage(ship->getObjectID(), 0x53484950, 1, 0x29) {
		
		//Blank list?
		insertInt(0);
		insertInt(0);
		
		/* I am clueless as to why these lists are inserted, especially their values...
		*  I can only infer that these are both min/max lists for something like a proportion/scale.
		*/
		insertUnkList1(ship);
		insertUnkList2(ship);
		
		insertEnergyDrainList(ship);
		insertCompMassList(ship);
		
		insertUnkList3(ship); //Again, another stupid list that has a 0 for all the values.
		
		//Blank list?
		insertInt(0);
		insertInt(0);
		
		//I have decided to leave a lot of the following lists blank. I believe they are related to 
		//ship weapons but its unacceptable to leave some of this data as hardcoded.
		//a lot of this is currently being worked out in the dummy.
		
		insertInt(0);
		insertInt(0);
		
		insertInt(0);
		insertInt(0);
	
		insertInt(0);
		insertInt(0);

		insertInt(0);
		insertInt(0);
		
		insertInt(0);
		insertInt(0);
		
		//Weapon Related list: weapon refire rate
		insertInt(0);
		insertInt(0);
		
		insertInt(0);
		insertInt(0);
		
		insertInt(0);
		insertInt(0);
		
		insertInt(0);
		insertInt(0);
		
		//A lot of data here from here on below repeat what was already declared in previous ship baselines
		
		insertFloat(ship->getTotalMass());
		insertFloat(ship->getShieldChargeRate());
		insertFloat(500.0f); //99% sure this the weapon charge rate
		insertFloat(50.0f); //?
		insertFloat(50.0f); //?
		
		//first 3 have something to do with pitch, yaw, and roll
		insertFloat(10.472f);
		insertFloat(10.472f);
		insertFloat(5.23599f); //note: 1/2 of first 2 floats
		
		insertFloat(0.837759f); //?
		insertFloat(0.837759f); //?
		insertFloat(0.907571f); //?
		
		insertFloat(ship->getMaxSpeed()); //value displayed in menus (iirc)
		insertFloat(ship->getTotalEnergy());
		
		//gahhh. more lists/data. havent seen to be filled on live..yet
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);
	}
	
	void insertUnkList1(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextUnkShip1UpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(1.0f); //no idea what this is for.
			}
			delete tsc;
		}
	}
	
	void insertUnkList2(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextUnkShip1UpdateCnt2());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(1.0f); //no idea what this is for.
			}
			delete tsc;
		}
	}
	
	void insertEnergyDrainList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextEnergyDrainUpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			float totalEnergy = 0.0f;
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getEnergyDrain());
				totalEnergy+=tsc->getEnergyDrain();
			}
			delete tsc;
			ship->setTotalEnergy(totalEnergy);
		}
	}
	
	void insertCompMassList(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextCompMassUpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			float totalMass = 0.0f;
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertFloat(tsc->getMass());
				totalMass+=tsc->getMass();
			}
			delete tsc;
			ship->setTotalMass(totalMass);
		}
	}
	
	void insertUnkList3(ShipObject* ship) {
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextUnkShip1UpdateCnt3());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertInt(0); //no idea what this is for.
			}
			delete tsc;
		}
	}
		
};

#endif /*SHIPOBJECTMESSAGE1_H_*/
