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
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,int,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,int,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		//const Archive::AutoDeltaPackedMap<int,ulong,Archive::DefaultObjectType>::`vftable'
		insertInt(0);
		insertInt(0);

		insertFloat(ship->getTotalMass()); //const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(2.f); //shield recharge rate

		insertFloat(500.f); //const Archive::AutoDeltaVariable<float>::`vftable'


		insertFloat(20.f); // const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(50.f); //const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(50.f);// const Archive::AutoDeltaVariable<float>::`vftable'

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
