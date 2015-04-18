/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SPICEDOWNERANIMATIONTASK_H_
#define SPICEDOWNERANIMATIONTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class SpiceDownerAnimationTask : public Task {

	ManagedReference<CreatureObject*> player;
	uint32 debuffCRC;

public:
	SpiceDownerAnimationTask(CreatureObject* player, uint32 debuffCRC) : Task() {
		this->player = player;
		this->debuffCRC = debuffCRC;

	}

	void run() {

		if( player == NULL )
			return;

		Locker locker(player);

		player->removePendingTask("spice_downer_animation");

		// If debuff is still active, perform animation and reschedule
		if ( player->hasBuff(debuffCRC) ) {

			player->doAnimation("heavy_cough_vomit");
			reschedule( 15000 );

		}
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*SPICEDOWNERANIMATIONTASK_H_*/
