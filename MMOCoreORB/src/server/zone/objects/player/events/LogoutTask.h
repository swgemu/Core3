/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

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
