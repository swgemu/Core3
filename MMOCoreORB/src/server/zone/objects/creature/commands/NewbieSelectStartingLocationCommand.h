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

#ifndef NEWBIESELECTSTARTINGLOCATIONCOMMAND_H_
#define NEWBIESELECTSTARTINGLOCATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NewbieSelectStartingLocationCommand : public QueueCommand {
public:

	NewbieSelectStartingLocationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		Zone* zone = creature->getZone();

		if (zone == NULL || zone->getZoneID() != 42)
			return GENERALERROR;

		ManagedReference<SceneObject*> cell = creature->getParent();

		if (cell == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> tutorial = cell->getParent();

		String city = arguments.toString();
		//"0=Corellia, 1=Dantooine, 2=Dathomir, 3=Endor, 4=Lok,\n"
		//"5=Naboo, 6=Rori, 7=Talus, 8=Tatooine, 9=Yavin 4, 10=Bad player prison (Space)");
		/*
				 (1,'bestine',8,-1290.000000,0.000000,-3590.000000,'Bestine, Tatooine',3,180),
				 (2,'mos_espa',8,-2902.000000,0.000000,2130.000000,'Mos Espa, Tatooine',3,180),
				 (3,'mos_eisley',8,3528.000000,0.000000,-4804.000000,'Mos Eisley, Tatooine',3,180),
				 (4,'mos_entha',8,1291.000000,0.000000,3138.000000,'Mos Entha, Tatooine',3,180),
				 (5,'coronet',0,-137.000000,0.000000,-4723.000000,'Coronet, Corellia',3,180),
				 (6,'tyrena',0,-5045.000000,0.000000,-2294.000000,'Tyrena, Corellia',3,180),
				 (7,'kor_vella',0,-3138.000000,0.000000,2808.000000,'Kor Vella, Corellia',3,180),
				 (8,'doaba_guerfel',0,3336.000000,0.000000,5525.000000,'Doaba Guerfel, Corellia',3,180),
				 (9,'dearic',7,335.000000,0.000000,-2931.000000,'Dearic, Talus',3,180),
				 (10,'nashal',7,4371.000000,0.000000,5165.000000,'Nashal, Talus',3,180),
				 (11,'narmle',6,-5310.000000,0.000000,-2221.000000,'Narmle, Rori',3,180),
				 (12,'restuss',6,5362.000000,0.000000,5663.000000,'Restuss, Rori',3,180),
				 (13,'theed',6,-4856.000000,0.000000,4162.000000,'Theed, Naboo',3,180),
				 (14,'moenia',5,4800.000000,0.000000,-4700.000000,'Moenia, Naboo',3,180),
				 (15,'keren',5,1441.000000,0.000000,2771.000000,'Keren, Naboo',3,180),
				 (16,'kaadara',5,5209.000000,0.000000,6677.000000,'Kaadara, Naboo',3,180),
				 (17,'tutorial',41,0.000000,0.000000,0.000000,'Tutorial',3,180);
		 */

		if (city == "mos_eisley") {
			creature->switchZone(8, 3528, 0, -4804);

		} else if (city == "mos_espa") {
			creature->switchZone(8, -2902, 0, 2130);

		} else if (city == "mos_entha") {
			creature->switchZone(8, 1291, 0, 3138);

		} else if (city == "coronet") {
			creature->switchZone(0, -137, 0, -4723);

		} else if (city == "tyrena") {
			creature->switchZone(0, -5045, 0, -2294);

		} else if (city == "kor_vella") {
			creature->switchZone(0, -3138, 0, 2808);

		} else if (city == "doaba_guerfel") {
			creature->switchZone(0, 3336, 0, 5525);

		} else if (city == "dearic") {
			creature->switchZone(7, 335, 0, -2931);

		} else if (city == "nashal") {
			creature->switchZone(7, 4371, 0, 5165);

		} else if (city == "narmle") {
			creature->switchZone(6, -5310, 0, -221);

		} else if (city == "restuss") {
			creature->switchZone(6, 5362, 0, 5663);

		} else if (city == "theed") {
			creature->switchZone(5, -4856, 0, 4162);

		} else if (city == "keren") {
			creature->switchZone(5, 1441, 0, 2771);

		} else if (city == "moenia") {
			creature->switchZone(5, 4800, 0, -4700);

		} else if (city == "kaadara") {
			creature->switchZone(5, 5209, 0, 6667);

		} else { //city == bestine, default
			creature->switchZone(8, -1290, 0, -3590);
		}

		tutorial->destroyObjectFromDatabase(true);
		creature->updateToDatabase();
		//tutorial->info("remaining references " + String::valueOf(tutorial->getReferenceCount()), true);

		return SUCCESS;
	}

};

#endif //NEWBIESELECTSTARTINGLOCATIONCOMMAND_H_

