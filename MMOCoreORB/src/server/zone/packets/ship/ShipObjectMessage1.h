/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SHIPOBJECTMESSAGE1_H_
#define SHIPOBJECTMESSAGE1_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage1 : public BaseLineMessage {
protected:
	enum index : int {
		serverObjectsStart = 0,
		serverObjectsEnd = 1,
		componentEfficiencyMap = 2,
		componentEnergyEfficiencyMap = 3,
		componentEnergyCostMap = 4,
		componentMassMap = 5,
		componentNameMap = 6,
		componentCreatorMap = 7,
		componentMaxDamageMap = 8,
		componentMinDamageMap = 9,
		componentshieldEffectivenessMap = 10,
		componentarmorEffectivenessMap = 11,
		componentenergyPerShotMap = 12,
		componentRefireRate = 13,
		componentcurrentAmmoMap = 14,
		componentmaxAmmoMap = 15,
		componentammoClassMap = 16,
		chassisMaxMass = 17,
		shieldRechargeRate = 18,
		capacitorMaxEnergy = 19,
		capacitorRechargeRate = 20,
		engineAccelerationRate = 21,
		engineDecelerationRate = 22,
		enginePitchAccelerationRate = 23,
		engineYawAccelerationRate = 24,
		engineRollAccelerationRate = 25,
		enginePitchRateMaximum = 26,
		engineYawRateMaximum = 27,
		engineRollRateMaximum = 28,
		engineSpeedMaximum = 29,
		reactorGenerationRate = 30,
		boosterMaxEnergy = 31,
		boosterRechargeRate = 32,
		boosterConsumptionRate = 33,
		boosterAcceleration = 34,
		boosterMaxSpeed = 35,
		droidCommandSpeed = 36,
		droidObjectID = 37,
	};

public:
	ShipObjectMessage1(ShipObject* ship) : BaseLineMessage(ship->getObjectID(), 0x53484950, 1, 38) {
		insertInt(0); //start ServerObject
		insertInt(0); // EndServerObject

		ship->getComponentEfficiencyMap()->insertToMessage(this);
		ship->getComponentEnergyEfficiencyMap()->insertToMessage(this);
		ship->getComponentEnergyCostMap()->insertToMessage(this);
		ship->getComponentMassMap()->insertToMessage(this);
		ship->getComponentNameMap()->insertToMessage(this);
		ship->getComponentCreatorMap()->insertToMessage(this);
		ship->getComponentMaxDamageMap()->insertToMessage(this);
		ship->getComponentMinDamageMap()->insertToMessage(this);
		ship->getShieldEffectivenessMap()->insertToMessage(this);
		ship->getArmorEffectivenessMap()->insertToMessage(this);
		ship->getEnergyPerShotMap()->insertToMessage(this);
		ship->getComponentRefireRate()->insertToMessage(this);
		ship->getCurrentAmmoMap()->insertToMessage(this);
		ship->getMaxAmmoMap()->insertToMessage(this);
		ship->getAmmoClassMap()->insertToMessage(this);

		insertFloat(ship->getChassisMaxMass());
		insertFloat(ship->getShieldRechargeRate());
		insertFloat(ship->getCapacitorMaxEnergy());
		insertFloat(ship->getCapacitorRechargeRate());

		insertFloat(ship->getEngineAccelerationRate());
		insertFloat(ship->getEngineDecelerationRate());
		insertFloat(ship->getEnginePitchAccelerationRate());
		insertFloat(ship->getEngineYawAccelerationRate());
		insertFloat(ship->getEngineRollAccelerationRate());
		insertFloat(ship->getEnginePitchRate());
		insertFloat(ship->getEngineYawRate());
		insertFloat(ship->getEngineRollRate());
		insertFloat(ship->getEngineMaxSpeed());

		insertFloat(ship->getReactorGenerationRate());
		insertFloat(ship->getBoosterMaxEnergy());
		insertFloat(ship->getBoosterRechargeRate());
		insertFloat(ship->getBoosterConsumptionRate());
		insertFloat(ship->getBoosterAcceleration());
		insertFloat(ship->getBoosterMaxSpeed());

		insertFloat(ship->getDroidCommandSpeed());
		insertLong(ship->getShipDroidID());

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE1_H_*/
