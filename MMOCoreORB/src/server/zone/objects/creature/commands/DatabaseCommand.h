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

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

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
		if (! ( arg0 == "cityregions" || arg0 == "factionstructures" || arg0 == "playerstructures" || arg0 == "sceneobjects" || arg0 == "clientobjects" || arg0 == "resourcespawns" ||
				arg0 == "characters" || arg0 == "deleted_characters") ){
			creature->sendSystemMessage("Command format is database  < playerstructures | cityregions  | sceneobjects | clientobjects >  <objectid>");
			return INVALIDPARAMETERS;
		}

		try {

			if(arg0 == "characters" || arg0 == "deleted_characters" ) {

				doSQLQuery(creature, arg0, objectID);

			} else {
				doObjectDBQuery(creature, arg0, objectID);


			}


		} catch ( Exception& err) {
			creature->sendSystemMessage("Error in database lookup: " + err.getMessage());
			info("ERROR: " + err.getMessage(),true);
		}
		return SUCCESS;
	}


private:

	void doObjectDBQuery(CreatureObject* creature, String db, uint64 objectID) const {
		StringBuffer msg;
		//info("doing object query for " + db + " with object " + String::valueOf(objectID),true);

		try {
			ObjectDatabaseManager* dManager = ObjectDatabaseManager::instance();
			uint16 id = ObjectDatabaseManager::instance()->getDatabaseID(db);

			if ( id == 0 ){
				creature->sendSystemMessage("invalid db");
				return;
			}
			ObjectDatabase* thisDatabase = cast<ObjectDatabase*>(ObjectDatabaseManager::instance()->getDatabase(id));

			if(thisDatabase == NULL || !thisDatabase->isObjectDatabase()) {
				creature->sendSystemMessage("Error retrieving " + db + " database.");
				return;
			}

			ObjectInputStream objectData(2000);

			if ( !(thisDatabase->getData(objectID,&objectData) ) ) {
				uint32 serverObjectCRC;
				String className;

				if (Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)) {

					msg << endl << "OID: " + String::valueOf(objectID) << endl;
					msg << "Database: " << db << endl;
					msg << "ClassName: " << className << endl;
					creature->sendSystemMessage(msg.toString());
				} else {

					msg << "ERROR desrializing from db" << endl;
				}

			} else {
				creature->sendSystemMessage("Object " + String::valueOf(objectID) + " was not found in " + db + " database.");
			}
		} catch ( DatabaseException& err) {
			msg << endl << err.getMessage();
		} catch ( Exception& err){
			msg << endl << err.getMessage();
		}

		creature->sendSystemMessage(msg.toString());
	}

	void doSQLQuery(CreatureObject* creature, String db, uint64 objectID) const {
		StringBuffer selectStatement;
		StringBuffer msg;

		try {

			selectStatement << "SELECT * FROM " << db << " WHERE character_oid = " << objectID;
			Reference<ResultSet*> queryResults = ServerDatabase::instance()->executeQuery(selectStatement);

			if(queryResults == NULL || queryResults.get()->getRowsAffected() == 0){

				msg << endl << "No results for " << selectStatement.toString();

			} else if ( queryResults->getRowsAffected() > 1) {

				msg << endl << "Duplicate character id.";

			} else {

			  while (queryResults->next()) {
				  msg << endl << "Found in the database";
				  uint64 newOID = queryResults->getUnsignedLong(0);
				  msg << "oid " << String::valueOf(newOID) << endl;
				  msg << "account id: " << String::valueOf(queryResults->getUnsignedInt(1)) << endl;
				  msg << "galaxy id " << String::valueOf(queryResults->getUnsignedInt(2)) << endl;

				  if(db == "characters")
			 		 msg << "Name: " << queryResults->getString(3) << " " << queryResults->getString(4) << endl;


				  if(db == "deleted_characters")
			 		 msg << "db_deleted: " <<  String::valueOf(queryResults->getInt(9)) << endl;
			  }

		  }
		} catch ( DatabaseException& err ) {
			msg << endl << err.getMessage();
		} catch ( Exception& err) {
			msg << endl << err.getMessage();
		}

		creature->sendSystemMessage(msg.toString());
	}


};
#endif //DATABASECOMMAND_H_
