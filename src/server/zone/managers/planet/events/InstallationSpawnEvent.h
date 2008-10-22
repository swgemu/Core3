/*
Copyright (C) 2007 <SWGEmu>

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

#ifndef INSTALLATIONSPAWNEVENT_H_
#define INSTALLATIONSPAWNEVENT_H_

#include "../PlanetManagerImplementation.h"
#include "../../../objects/installation/InstallationObjectImplementation.h"

#include "../../../../chat/ChatManagerImplementation.h"

//class InstallationObject;
//class Zone;
//class Player;

class InstallationSpawnEvent : public Event {

	InstallationObject* inso;
	Player * player;
	Zone* z;

public:
	InstallationSpawnEvent(Player * play, InstallationObject * inInso, Zone* zn) : Event() {

		inso = inInso;
		player = play;
		z = zn;

		setKeeping(false);
	}

	bool activate() {

		try {
			inso->wlock();
			// need to lock inso
			inso->insertToZone(z);

			/*
			try {
				stringstream query;
*/
/*
 *
zoneid  	tinyint(4)  	 	  	No  	 	 	  Browse distinct values   	  Change   	  Drop   	  Primary   	  Unique   	  Index   	 Fulltext
	objectid 	bigint(20) 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	parentid 	bigint(20) 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	owner_id 	mediumint(8) 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	name 	varchar(200) 	latin1_swedish_ci 		No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	template 	varchar(255) 	latin1_swedish_ci 		No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	crc 	bigint(20) 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	file 	varchar(200) 	latin1_swedish_ci 		No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	oX 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	oY 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	oZ 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	oW 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	X 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	Z 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	Y 	float 			No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	attributes 	text 	latin1_swedish_ci 		No 			Browse distinct values 	Change 	Drop 	Primary 	Unique 	Index 	Fulltext
	noBuildArea
 */
/*
				query << "INSERT into `character_structures` (zone_id, objectid, parent_id, owner_id, name, template, "
				<< " crc, file, oX, oY, oZ, oW, X, Z, Y, attributes, noBuildArea) "
				<< "VALUES (" << player->getZoneID() << ", " << inso->getObjectID() << ", 0, ", " << player->getCharacterID() << ", '\\" << inso->getName()
				<< "','" << inso->getName << "',"
				<< inso->getTemplateName() << "',"
				<< inso->getObjectCRC() << ", '"
				<< inso->getFileName() << "', "
				<< inso->getooX(), ", "
				<< inso->getooY(), ", "
				<< inso->getooZ(), ", "
				<< inso->getooW(), ", "
				<< inso->getoX(), ", "
				<< inso->getoZ(), ", "
				<< inso->getoY(), ", "

				player->getCharacterID() << itemType << ","
				<< player->getObjectID() << ",'" << playername << "'," << price << "," << auctionout << ",0,"
				<< expire << "," << bazaarid << "," << planet << ",0,'');";

				ServerDatabase::instance()->executeStatement(query2);

				stringstream query3;
				query3 << "UPDATE `character_items` SET character_id = 0 where item_id = " << objectid << ";";

				ServerDatabase::instance()->executeStatement(query3);

			} catch (DatabaseException& e) {
				stringstream err;
				err << "Can't add bazaar_item " << objectid;
				error(err);
				return;
			}*/


			inso->unlock();
		} catch (...) {
			inso->unlock();
		}

		try {
			player->wlock();

			string mailSender = "Structure Builder";
			string charNameSender = player->getFirstName();

			unicode subjectSender("Construction Complete");
			unicode bodySender("Construction of your " + inso->getName().c_str() + " is now complete.  You have xx lots remaining.");

			player->sendMail(mailSender, subjectSender, bodySender, charNameSender);

			// Create Waypoint to Structure
			WaypointObject* waypoint =
					new WaypointObject(player, player->getNewItemID());
			waypoint->setName(inso->getName().c_str());
			waypoint->setPosition(inso->getPositionX(), 0.0f, inso->getPositionY());
			waypoint->changeStatus(true);

			player->addWaypoint(waypoint);

			player->unlock();
		} catch (...) {
			player->unlock();
		}

		return true;
	}

};

#endif /*INSTALLATIONSPAWNEVENT_H_*/
