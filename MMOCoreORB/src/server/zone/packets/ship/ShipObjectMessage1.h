/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SHIPOBJECTMESSAGE1_H_
#define SHIPOBJECTMESSAGE1_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage1 : public BaseLineMessage {
public:
	ShipObjectMessage1(ShipObject* ship) : BaseLineMessage(ship->getObjectID(), 0x53484950, 1, 0x29) {
		//ship->info(true) << "ShipObjectMessage1 sent";

		insertInt(0); //start ServerObject
		insertInt(0); // EndServerObject

		ship->getComponentEfficiencyMap()->insertToMessage(this);
		ship->getComponentEnergyEfficiencyMap()->insertToMessage(this);
		ship->getComponentEnergyCostMap()->insertToMessage(this);
		ship->getComponentMassMap()->insertToMessage(this); // 5
		ship->getComponentNameMap()->insertToMessage(this);
		ship->getComponentCreatorMap()->insertToMessage(this);
		ship->getComponentMaxDamageMap()->insertToMessage(this);
		ship->getComponentMinDamageMap()->insertToMessage(this);
		ship->getShieldEffectivenessMap()->insertToMessage(this); // 10
		ship->getArmorEffectivenessMap()->insertToMessage(this);
		ship->getEnergyPerShotMap()->insertToMessage(this);
		ship->getComponentRefireRate()->insertToMessage(this);
		ship->getCurrentAmmoMap()->insertToMessage(this);
		ship->getMaxAmmoMap()->insertToMessage(this); // 15
		ship->getAmmoClassMap()->insertToMessage(this);

		insertFloat(ship->getTotalMass());
		insertFloat(ship->getShieldRechargeRate()); //shield recharge rate
		insertFloat(ship->getCapacitorMaxEnergy());
		insertFloat(ship->getCapacitorRechargeRate()); // 20
		insertFloat(ship->getEngineAccelerationRate()); //
		insertFloat(ship->getEngineDecelerationRate());//
		insertFloat(ship->getEnginePitchRate()); //
		insertFloat(ship->getEngineYawRate()); //
		insertFloat(ship->getEngineRollRate()); // 25
		insertFloat(ship->getEngineMaxPitchRate()); //
		insertFloat(ship->getEngineMaxYawRate()); //
		insertFloat(ship->getEngineMaxRollRate()); //
		insertFloat(ship->getMaxSpeed()); //
		insertFloat(ship->getReactorGenerationRate()); // 30
		insertFloat(ship->getBoosterMaxEnergy()); //
		insertFloat(ship->getBoosterRechargeRate()); //
		insertFloat(ship->getBoosterConsumptionRate());
		insertFloat(ship->getBoosterAcceleration());
		insertFloat(ship->getBoosterMaxSpeed()); // 35
		insertFloat(ship->getDroidCommandSpeed());

		insertLong(0);

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE1_H_*/
