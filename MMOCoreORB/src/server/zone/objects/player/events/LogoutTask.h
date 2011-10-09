/*
 Copyright (C) 2007 <SWGEmu>

 This File is part of Core3.

 This program is free software; you can redistribute
 it and/or modify it under the terms of the GNU Lesser
 General Public License as published by the Free Software
 Foundation; either version 3 of the License,
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

/**
 * LogoutTask.h
 *
 *  Created: Sat Oct  8 09:18:00 EDT 2011
 *   Author: lordkator
 *
 *  Description: Task created by LogoutServerCommand to implement the /logout process
 */

#ifndef LOGOUTTASK_H_
#define LOGOUTTASK_H_

#include "server/zone/packets/player/LogoutMessage.h"

class LogoutTask: public Task {
	ManagedReference<CreatureObject*> creature;
	int timeLeft;

public:
	LogoutTask(CreatureObject* cr) {
		creature = cr;
		timeLeft = 30; // 30 seconds with messages in 5 second intervals

		// TODO: Do we need to do player->setLoggingOut() here or just before the actual logout?
		// TODO: Doesn't seem to be a way to clearLoggingOut so seems to be a very final act on the object!

		StringIdChatParameter stringId("logout", "time_left");
		stringId.setDI(30);

		creature->sendSystemMessage(stringId); // You have %DI seconds left until you may log out safely.
	}

	void cancelLogout() {
		creature->removePendingTask("logout");

		if(isScheduled())
			cancel();

		StringIdChatParameter abortMsg("logout", "aborted");
		creature->sendSystemMessage(abortMsg); // Your attempt to log out safely has been aborted.
	}

	void run() {
		Locker creatureLocker(creature);

		PlayerObject* player = creature->getPlayerObject();

		try {
			// TODO: Research do things like bleeding, poison etc stop a /logout ??
			if (creature->isBleeding() || creature->isPoisoned() || creature->isDiseased()) {
				cancelLogout();
				return;
			}

			timeLeft -= 5;

			// Done waiting yet?
			if (timeLeft <= 0) {
				// Not 100% certain if this is right place to call this but seems like it should get called...
				player->setLoggingOut();

				StringIdChatParameter safeMsg("logout", "safe_to_log_out");
				creature->sendSystemMessage(safeMsg); // You may now log out safely.

				creature->removePendingTask("logout");

				// Send the client the Logout Packet
				creature->sendMessage(new LogoutMessage());

				player->info(creature->getFirstName() + " Loggedout");

				return;
			}

			// Let them know how much time they have left before they log out...
			StringIdChatParameter timeLeftMsg("logout", "time_left");
			timeLeftMsg.setDI(timeLeft);

			creature->sendSystemMessage(timeLeftMsg); // You have %DI seconds left until you may log out safely.

			// run() again in 5 seconds
			reschedule(5000);
		} catch (Exception& e) {
			creature->error("unreported exception caught in LogoutTask::run()");
		}
	}
};

#endif /* LOGOUTTASK_H_ */
