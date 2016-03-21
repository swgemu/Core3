/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SHIPOBJECTMESSAGE1_H_
#define SHIPOBJECTMESSAGE1_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage1 : public BaseLineMessage {
public:
	ShipObjectMessage1(ShipObject* ship)
	: BaseLineMessage(ship->getObjectID(), 0x53484950, 1, 0x29) {

		// const Archive::AutoDeltaVariableCallback<int,ClientObject::Callbacks::DefaultCallback<ClientObject::Messages::BankBalance,int>,ClientObject>::`vftable'
		insertInt(0);

		//const Archive::AutoDeltaVariableCallback<int,ClientObject::Callbacks::DefaultCallback<ClientObject::Messages::CashBalance,int>,ClientObject>::`vftable
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable
		insertInt(0);
		insertInt(0);
		//insertDummyList(0x3f800000);

		// const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable
		insertInt(0);
		insertInt(0);
		//insertDummyList(0x44fa0000);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);
		//insertDummyList(0x44bb0000);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);
		//insertDummyList(0);

		// const Archive::AutoDeltaPackedMap<int,_STL::basic_string<ushort,_STL::char_traits<ushort>,_STL::allocator<ushort>>,Archive::DefaultObjectType>::`vftable
		//map<int, unicode>
		insertInt(0);
		insertInt(0);
		//insertDummyList(0x44fa0000);

		//const Archive::AutoDeltaPackedMap<int,NetworkId,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		// const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0); // component general efficiency

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0); // component energy efficiency
		insertInt(0); // component energy requirements

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0); // component mass
		insertInt(0); // component names

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);  // component creators?
		insertInt(0); // max weapon damage

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0); // min weapon damage
		insertInt(0); // shield effectiveness

		//const Archive::AutoDeltaPackedMap<int,int,Archive::DefaultObjectType>::`vftable'
		insertInt(0); // armor effectiveness
		
		insertInt(0); // energy drain per shot

		//const Archive::AutoDeltaPackedMap<int,int,Archive::DefaultObjectType>::`vftable'
		insertInt(0); // weapon refire rate
		insertInt(0); // weapon ammo current

		//const Archive::AutoDeltaPackedMap<int,ulong,Archive::DefaultObjectType>::`vftable'
		insertInt(0); // weapon ammo maximum
		insertInt(0); // weapon ammo type

		insertFloat(ship->getTotalMass()); // Total component mass 	//const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(2.f); //shield recharge rate

		insertFloat(500.f); // Capacitor energy maximum	//const Archive::AutoDeltaVariable<float>::`vftable'


		insertFloat(20.f); // Capacitor energy charge rate // const Archive::AutoDeltaVariable<float>::`vftable'
		
		
		insertFloat(50.f); // Engine Acceleration rate	//const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(50.f); // Engine Deceleration rate	//const Archive::AutoDeltaVariable<float>::`vftable'

		insertFloat(10.472f); //Max Yaw Acceleration
		insertFloat(10.472f); //Max Pitch Acceleration
		insertFloat(5.23599f); //Max Roll Acceleration

		insertFloat(0.837759f); //Current Yaw Acceleration
		insertFloat(0.837759f); //Current Pitch Acceleration
		insertFloat(0.907571f); //Current Roll Acceleration

		insertFloat(50.f); //Max Speed?
		insertFloat(8000.f); // Reactor generation rate

		// hmm

		insertFloat(0); //const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(0); //const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(0); //const Archive::AutoDeltaVariable<float>::`vftable'

		insertFloat(0); //const Archive::AutoDeltaVariable<float>::`vftable
		insertFloat(0); //const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(0); // const Archive::AutoDeltaVariable<float>::`vftable'



		insertLong(0); // const Archive::AutoDeltaVariableCallback<NetworkId,ShipObject::Callbacks::DefaultCallback<ShipObject::Messages::DroidPcdChanged,NetworkId>,ShipObject>::`vftable'

		setSize();
	}

	void insertDummyList(int val) {
		insertInt(7);
		insertInt(7);

		insertByte(0);
		insertInt(0);
		insertInt(val); // 0xDC, 0xBF, 0xBD, 0x9A,

		insertByte(0);
		insertInt(1);
		insertInt(val); // 0x05, 0xC7, 0xA0, 0x35,

		insertByte(0);
		insertInt(2);
		insertInt(val); // 0xBE, 0x17, 0x32, 0xE7

		insertByte(0);
		insertInt(4);
		insertInt(val); // 0x9E, 0x60, 0xCB, 0xE1,

		insertByte(0);
		insertInt(5);
		insertInt(val); // 0x9E, 0x60, 0xCB, 0xE1,

		insertByte(0);
		insertInt(6);
		insertInt(val); // 0xEE, 0xD6, 0xCE, 0x20,

		insertByte(0);
		insertInt(0x0f);
		insertInt(val); //0x3D, 0x3C, 0x82, 0x2C,
	}
};

#endif /*SHIPOBJECTMESSAGE1_H_*/
