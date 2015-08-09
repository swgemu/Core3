/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VEHICLEDECAYTASK_H_
#define VEHICLEDECAYTASK_H_

#include "server/zone/objects/creature/VehicleObject.h"

class VehicleDecayTask : public Task {
	ManagedReference<TangibleObject*> vehicleObj;
	bool initialDecay;

public:
	VehicleDecayTask(TangibleObject* veh) : Task() {
		vehicleObj = veh;
		initialDecay = true;
	}

	void run() {
		ManagedReference<TangibleObject*> vehicle = vehicleObj.get();

		if (vehicle == NULL)
			return;

		vehicle->removePendingTask("decay");

		int decayCycle = 600; // 10 minute decay cycle
		int decayRate = getDecayRate(vehicle);

		Locker locker(vehicle);

		if (initialDecay) {
			vehicle->inflictDamage(vehicle, 0, floor(decayRate / 2), true);
			initialDecay = false;
		} else {
			vehicle->inflictDamage(vehicle, 0, decayRate, true);
		}

		vehicle->addPendingTask("decay", this, decayCycle * 1000);
	}

	int getDecayRate(TangibleObject* vehicle) {
		uint32 crc = vehicle->getServerObjectCRC();

		switch(crc) {
		case 0xD789E1F8: // object/mobile/vehicle/speederbike_swoop.iff
			return 50;
		case 0x32F87A54: // object/mobile/vehicle/jetpack.iff
			return 35;
		case 0x728ED9D3: // object/mobile/vehicle/speederbike.iff
			return 25;
		case 0x78AA4B83: // object/mobile/vehicle/speederbike_flash.iff
		case 0x3E125EC4: // object/mobile/vehicle/landspeeder_xp38.iff
		case 0x128F9F19: // object/mobile/vehicle/landspeeder_x34.iff
		case 0x7B767B17: // object/mobile/vehicle/landspeeder_x31.iff
		case 0xA819F8D9: // object/mobile/vehicle/landspeeder_av21.iff
		default:
			return 15;
		}
	}

};

#endif /*VEHICLEDECAYTASK_H_*/
