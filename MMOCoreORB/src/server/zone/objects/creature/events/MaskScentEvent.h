/*
 * MaskScentEvent.h
 *
 *  Created on: Oct 17, 2008
 *      Author: swgdev
 */

#ifndef MASKSCENTEVENT_H_
#define MASKSCENTEVENT_H_

#include "../../../objects/creature/CreatureObject.h"

class MaskScentEvent : public Event {
	CreatureObject* creature;
		uint32 camoCrc;
public:
	MaskScentEvent(CreatureObject* cr, uint32 crc, int time) : Event(time * 1000){
		creature = cr;
		camoCrc = crc;
	}

	bool activate() {
		try {
			creature->wlock();

			creature->deactivateCamo(false);

			creature->unlock();
		} catch (...) {
			creature->error("Unreported exception caught on MaskScentEvent\n");

			creature->unlock();
		}

		return true;
	}

	uint32 getNameCRC() {
		return camoCrc;
	}

};

#endif
