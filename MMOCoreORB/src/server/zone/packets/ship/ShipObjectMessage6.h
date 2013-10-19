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
