/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE3_H_
#define SHIPOBJECTMESSAGE3_H_

#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class ShipObjectMessage3 : public BaseLineMessage {
protected:
	enum index : int {
		complexity = 0,
		objectName = 1,
		customObjectName = 2,
		volume = 3,
		customizationString = 4,
		visibleComponents = 5,
		optionsBitmask = 6,
		useCount = 7,
		condition = 8,
		conditionMax = 9,
		visible = 10,
		chassisSlideFactor = 11,
		chassisCurrentHealth = 12,
		chassisMaxHealth = 13,
		chassisTypeCRC = 14,
		componentMaxArmorMap = 15,
		componentCurrentArmorMap = 16,
		componentCurrentHitpointsMap = 17,
		componentMaxHitpointsMap = 18,
		componentOptionsMap = 19,
		maxFrontShield = 20,
		maxRearShield = 21
	};

public:
	ShipObjectMessage3(ShipObject* ship) : BaseLineMessage(ship, 0x53484950, 3, 22) {
		insertFloat(ship->getComplexity());
		insertStringId(ship->getObjectName());

		insertUnicode(getShipName(ship));

		insertInt(ship->getVolume());

		String app;
		ship->getCustomizationString(app);
		insertAscii(app);

		auto visibleComponents = ship->getVisibleComponents();
		visibleComponents->insertToMessage(this);

		insertInt(ship->getOptionsBitmask());
		insertInt(ship->getUseCount());
		insertInt(ship->getConditionDamage());
		insertInt(ship->getMaxCondition());
		insertByte(ship->getObjectVisible());

		insertFloat(ship->getSlip());
		insertFloat(ship->getChassisCurrentHealth());
		insertFloat(ship->getChassisMaxHealth());

		insertInt(ship->getShipNameCRC());

		ship->getMaxArmorMap()->insertToMessage(this);
		ship->getCurrentArmorMap()->insertToMessage(this);
		ship->getCurrentHitpointsMap()->insertToMessage(this);
		ship->getMaxHitpointsMap()->insertToMessage(this);
		ship->getComponentOptionsMap()->insertToMessage(this);

		insertFloat(ship->getMaxFrontShield());
		insertFloat(ship->getMaxRearShield());

		setSize();
	}

	UnicodeString getShipName(ShipObject* ship) {
		if (!ship->isShipAiAgent()) {
			return ship->getShipLaunchedName();
		}

		auto shipAgent = ship->asShipAiAgent();

		if (shipAgent != nullptr) {
			String stfShip = "@space/ship_names:" + shipAgent->getShipAgentTemplateName();
			return StringIdManager::instance()->getStringId(stfShip.hashCode());
		}

		return "";
	}
};

#endif /*SHIPOBJECTMESSAGE3_H_*/
