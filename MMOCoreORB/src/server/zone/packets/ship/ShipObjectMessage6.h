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

		insertShort(ship->getUniqueID()); //2 m_shipId Archive::AutoDeltaVariableCallback<ushort,ShipObject::Callbacks::DefaultCallback<ShipObject::Messages::ShipIdChanged,ushort>,ShipObject>::`vftable
		static Logger logger;
		logger.info("ShipID: " + String::valueOf(ship->getUniqueID()), true);
		insertFloat(ship->getShipAccelerationRate()); // 3 const Archive::AutoDeltaVariable<float>::`vftable' // acceleration rate
		insertFloat(ship->getShipDecelerationRate()); // 4 min speed // Archive::AutoDeltaVariable<float> // decelleration rate

		insertFloat(ship->getCurrentPitchRate()); //5 Pitch Acceleration Max
		insertFloat(ship->getCurrentYawRate()); // 6 Yaw Acceleration Max
		insertFloat(ship->getCurrentRollRate()); //7 Roll Acceleration Max

		insertFloat(ship->getMaxPitchRate()); //8 Pitch Acceleration
		insertFloat(ship->getMaxYawRate()); //9 Yaw Acceleration
		insertFloat(ship->getMaxRollRate()); //10 Roll Acceleration
		insertFloat(ship->getMaxSpeed()); //11 max speed

                // look at target
		insertLong(0); //12 const
                
		insertInt(0); //13 m_pilotLookAtTargetSlot

		ship->getTargetableBitfield()->insertToMessage(this);

		//logger.info("Component at 0 is: " + ship->getShipComponentMap()->getKeyAt(0), true);

        ship->getShipComponentMap()->insertToMessage(this); //15

		insertAscii(""); //16 m_wingName Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'
		insertAscii(""); //17 m_typeName Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'
		insertAscii(""); //18 m_difficulty Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'
		insertAscii(""); //19 m_faction Archive::AutoDeltaVariable<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char>>>::`vftable'

		insertFloat(ship->getFrontShield()); //20 front shield current
		insertFloat(ship->getRearShield()); //21 back shield current

		insertInt(0); //m_guildId const Archive::AutoDeltaVariable<int>::`vftable'

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
