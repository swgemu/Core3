/*
 * SendJtlRecruitment.h
 *
 *  Created on: 2024-10-23
 *	Author: Hakry
 */

#ifndef SENDJTLRECRUITMENT_H_
#define SENDJTLRECRUITMENT_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/ChatManager.h"

class SendJtlRecruitment : public Task {
	ManagedWeakReference<CreatureObject*> weakPlayer;

public:
	SendJtlRecruitment(CreatureObject* player){
		weakPlayer = player;

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		auto player = weakPlayer.get();

		if (player == nullptr) {
			return;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto chatManager = zoneServer->getChatManager();

		if (chatManager == nullptr) {
			return;
		}

		const auto playerName = player->getFirstName();

		// Neutral Mail
		ManagedReference<WaypointObject*> neutralWaypoint = zoneServer->createObject(0xc456e788, 0).castTo<WaypointObject*>();

		if (neutralWaypoint != nullptr) {
			Locker waypointLocker(neutralWaypoint);

			neutralWaypoint->setPlanetCRC(STRING_HASHCODE("tatooine"));
			neutralWaypoint->setPosition(-1174, 0, -3647);

			neutralWaypoint->setCustomObjectName("@space/space_interaction:neutral_wp_name", false);

			StringIdChatParameter emailBody("space/space_interaction", "email_body_2");

			chatManager->sendMail("@space/space_interaction:email_sender_2", "@space/space_interaction:email_subject_2", emailBody, playerName, neutralWaypoint);
		}

		// Rebel Mail
		ManagedReference<WaypointObject*> rebelWaypoint = zoneServer->createObject(0xc456e788, 0).castTo<WaypointObject*>();

		if (rebelWaypoint != nullptr) {
			Locker waypointLocker(rebelWaypoint);

			rebelWaypoint->setPlanetCRC(STRING_HASHCODE("corellia"));
			rebelWaypoint->setPosition(-5072, 0, -2343);

			rebelWaypoint->setCustomObjectName("@space/space_interaction:rebel_wp_name", false);

			StringIdChatParameter emailBody("space/space_interaction", "email_body_3");

			chatManager->sendMail("@space/space_interaction:email_sender_3", "@space/space_interaction:email_subject_3", emailBody, playerName, rebelWaypoint);
		}

		// Imperial Mail
		WaypointChatParameterVector impWaypoints;

		// Landau
		WaypointChatParameter impWaypoint1;
		impWaypoint1.set("@space/space_interaction:imperial_wp_name", -5516, 6.0, 4403, STRING_HASHCODE("naboo"));

		impWaypoints.add(impWaypoint1);

		// Gunham
		WaypointChatParameter impWaypoint2;
		impWaypoint2.set("@space/space_interaction:imperial_wp_name", -1125, 12.1959, -3622.83, STRING_HASHCODE("tatooine"));

		impWaypoints.add(impWaypoint2);

		// Zhanks
		WaypointChatParameter impWaypoint3;
		impWaypoint3.set("@space/space_interaction:imperial_wp_name", -3269.3, 87.0, 3109.6, STRING_HASHCODE("corellia"));

		impWaypoints.add(impWaypoint3);

		UnicodeString subject("@space/space_interaction:email_subject_1");
		UnicodeString emailBody("@space/space_interaction:email_body_1");
		StringIdChatParameterVector sellerBodyVector;

		chatManager->sendMail("@space/space_interaction:email_sender_1", subject, emailBody, playerName, &sellerBodyVector, &impWaypoints);
	}
};

#endif // SENDJTLRECRUITMENT_H_
