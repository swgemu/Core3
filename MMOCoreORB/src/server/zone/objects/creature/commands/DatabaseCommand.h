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

#ifndef DATABASECOMMAND_H_
#define DATABASECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DatabaseCommand : public QueueCommand {
public:

	DatabaseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if ( creature == NULL)
			return GENERALERROR;

		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		String arg0 = "";
		String arg1 = "";
		uint64 objectID;

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		tokenizer.getStringToken(arg0);

		try {

			if(!tokenizer.hasMoreTokens())
				return INVALIDPARAMETERS;

			objectID = tokenizer.getLongToken();

		} catch ( Exception err) {
			creature->sendSystemMessage("Error parsing objectID: " +  err.getMessage());
			return INVALIDPARAMETERS;

		}

		String strResource;
		if (! ( arg0 == "cityregions" || arg0 == "factionstructures" || arg0 == "playerstructures" || arg0 == "sceneobjects" || arg0 == "clientobjects" || arg0 == "resourcespawns"  ) ){
			creature->sendSystemMessage("Command format is database  < playerstructures | cityregions  | sceneobjects | clientobjects >  <objectid>");
			return INVALIDPARAMETERS;
		}

		try {

			ObjectDatabaseManager* dManager = ObjectDatabaseManager::instance();
			uint16 id = ObjectDatabaseManager::instance()->getDatabaseID(arg0);

			if(id == 0)
				return GENERALERROR;

			ObjectDatabase* thisDatabase = cast<ObjectDatabase*>(ObjectDatabaseManager::instance()->getDatabase(id));
			if(thisDatabase == NULL || !thisDatabase->isObjectDatabase()) {
				creature->sendSystemMessage("Error retrieving " + arg0 + " database.");
				return GENERALERROR;
			}
			ObjectInputStream objectData(2000);

			if ( !(thisDatabase->getData(objectID,&objectData) ) ) {
				uint32 serverObjectCRC;
				String className;

				if (Serializable::getVariable<uint32>(String("SceneObject.serverObjectCRC").hashCode(), &serverObjectCRC, &objectData)) {

					Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData);
					StringBuffer msg;
					msg << endl << "OID: " + String::valueOf(objectID) << endl;
					msg << "Database: " << arg0 << endl;
					msg << "ClassName: " << className << endl;
					creature->sendSystemMessage(msg.toString());
				}


			} else {
				creature->sendSystemMessage("Object " + String::valueOf(objectID) + " was not found in " + arg0 + " database.");
			}

		} catch ( Exception& err) {
			creature->sendSystemMessage("Error in database lookup: " + err.getMessage());
		}
		return SUCCESS;
	}

};
#endif //DATABASECOMMAND_H_
