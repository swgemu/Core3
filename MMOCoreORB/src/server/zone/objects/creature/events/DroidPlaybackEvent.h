/*
Copyright (C) 2013 <SWGEmu>

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

#ifndef DROIDPLAYBACKEVENT_H_
#define DROIDPLAYBACKEVENT_H_

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class DroidPlaybackEvent : public Task {

	ManagedReference<DroidPlaybackModuleDataComponent*> module;
	ManagedReference<CreatureObject*> player;
	int action;
	String song;
	int instrument;
public:
	const static uint8 SET_TRACK = 0;
	const static uint8 CHANGE_SONG = 1;
	const static uint8 STOP_PLAYING = 2;

	DroidPlaybackEvent(DroidPlaybackModuleDataComponent* module,CreatureObject* player, String song, int instrument, int action) : Task() {
		this->module = module;
		this->action = action;
		this->song = song;
		this->player = player;
		this->instrument = instrument;
	}

	void run() {
		if (module == NULL)
			return;

		DroidObject* droid = module->getDroidObject();
		if (droid == NULL)
			return;

		Locker locker(droid);

		if( droid->getLocalZone() == NULL ){  // Not outdoors

			ManagedWeakReference<SceneObject*> parent = droid->getParent();
			if( parent == NULL || !parent.get()->isCellObject() ){ // Not indoors either
				module->deactivate();
				droid->removePendingTask("droid_playback_event");
				return;
			}
		}

		// Check droid states
		if( droid->isDead() || droid->isIncapacitated() ){
			module->deactivate();
			droid->removePendingTask("droid_playback_event");
			return;
		}


		// Droid must have power
		if( !droid->hasPower() ){
			module->deactivate();
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			droid->removePendingTask("droid_playback_event");
			return;
		}
		Locker plock(player);
		Locker crossLock(droid,player);
		if (action == SET_TRACK)
			module->setTrack(player,song,instrument);
		if (action == CHANGE_SONG)
			module->songChanged(player);
		if (action == STOP_PLAYING)
			module->songStopped(player);

	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*DROIDPLAYBACKEVENT_H_*/
