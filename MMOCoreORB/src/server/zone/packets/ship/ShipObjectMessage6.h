/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE6_H_
#define SHIPOBJECTMESSAGE6_H_

#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage6 : public TangibleObjectMessage6 {
public:
	ShipObjectMessage6(ShipObject* ship)
			: TangibleObjectMessage6(ship, 0x53484950, 0x18) {

		insertShort(ship->getUniqueID()); //3 const Archive::AutoDeltaVariableCallback<ushort,ShipObject::Callbacks::DefaultCallback<ShipObject::Messages::ShipIdChanged,ushort>,ShipObject>::`vftable


		insertFloat(50.f); // 4 const Archive::AutoDeltaVariable<float>::`vftable'
		insertFloat(50.f); // 5 min speed // Archive::AutoDeltaVariable<float>

		insertFloat(10.472f); //6 Yaw Acceleration Max
		insertFloat(10.472f); // 7 Pitch Acceleration Max
		insertFloat(5.23599f); //8 Roll Acceleration Max

		insertFloat(0.1675516); //9 Yaw Acceleration
		insertFloat(0.1675516); //10 Pitch Acceleration
		insertFloat(0.907571f); //11 Roll Acceleration


		insertFloat(50.f); //12 max speed

		insertLong(0); //13 const Archive::AutoDeltaVariableCallback<CachedNetworkId,ShipObject::Callbacks::DefaultCallback<ShipObject::Messages::LookAtTargetChanged,CachedNetworkId>,ShipObject>::`vftable'

		insertInt(0); //14 const Archive::AutoDeltaVariableCallback<int,ShipObject::Callbacks::DefaultCallback<ShipObject::Messages::LookAtTargetSlotChanged,int>,ShipObject>::`vftable'

		insertInt(0); //15  const Archive::AutoDeltaVariableCallback<BitArray,ShipObject::Callbacks::DefaultCallback<ShipObject::Messages::TargetableSlotBitfieldChanged,BitArray>,ShipObject>::`vftable'
		insertInt(0);

		//components 16
		insertInt(7); // const Archive::AutoDeltaMap<int,ulong,ShipObject>::`vftable'
		insertInt(7);

		insertByte(0);
		insertInt(0);
		insertInt(0x9abdbfdc); // 0xDC, 0xBF, 0xBD, 0x9A, //rct_prototype

		insertByte(0);
		insertInt(1);
		insertInt(0x35a0c705); // 0x05, 0xC7, 0xA0, 0x35, //eng_prototype

		insertByte(0);
		insertInt(2);
		insertInt(0xe73217be); // 0xBE, 0x17, 0x32, 0xE7 //shd_prototype

		insertByte(0);
		insertInt(4);
		insertInt(0xe1cb609e); // 0x9E, 0x60, 0xCB, 0xE1, //arm_prototype

		insertByte(0);
		insertInt(5);
		insertInt(0xe1cb609e); // 0x9E, 0x60, 0xCB, 0xE1, //arm_prototype

		insertByte(0);
		insertInt(6);
		insertInt(0x20ced6ee); // 0xEE, 0xD6, 0xCE, 0x20, //cap_prototype

		insertByte(0);
		insertInt(0x0f);
		insertInt(0x2c823c3d); //0x3D, 0x3C, 0x82, 0x2C, //wpn_prototype

		insertAscii(""); //17 const Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'
		insertAscii(""); //18 const Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'
		insertAscii(""); //19 const Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'
		insertAscii(""); //20 const Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'

		insertFloat(301.f); //21 front shield current
		insertFloat(302.f); //22 back shield current

		insertInt(0); //23 const Archive::AutoDeltaVariable<int>::`vftable'

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
