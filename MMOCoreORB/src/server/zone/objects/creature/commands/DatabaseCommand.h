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
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/db/ServerDatabase.h"
//#include "system/io/Serializable.h"

// Copied
/*
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sessions/PlaceStructureSession.h"
#include "server/zone/objects/player/sessions/DestroyStructureSession.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/callbacks/StructurePayUncondemnMaintenanceSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/FindLostItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/DeleteAllItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructureStatusSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/NameStructureSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/StructurePayMaintenanceSuiCallback.h"
#include "server/zone/managers/stringid/StringIdManager.h"
*/

class DatabaseCommand : public QueueCommand {
public:

	DatabaseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	// Queries the database to get details of the object
	// PARAMETERS: Database, objectid
	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

			UnicodeTokenizer tokenizer(arguments);
			tokenizer.setDelimeter(" ");

			String arg0 = "";
			String arg1 = "";
			uint64 objectID;
			if (!tokenizer.hasMoreTokens())
				return INVALIDPARAMETERS;


			tokenizer.getStringToken(arg0);

			objectID = tokenizer.getLongToken();

			if ( creature == NULL)
				return GENERALERROR;



			setLogging(true);

			String strResource;
			if (! ( arg0 == "cityregions" || arg0 == "factionstructures" || arg0 == "playerstructures" || arg0 == "sceneobjects" || arg0 == "clientobjects" || arg0 == "resourcespawns"  ) )
			{
					creature->sendSystemMessage("Command format is database  < playerstructures | cityregions  | sceneobjects | clientobjects >  <objectid>");
					return INVALIDPARAMETERS;

			} else if ( arg0 == "resourcespawns") {

				if (!tokenizer.hasMoreTokens()) {
					if (!tokenizer.hasMoreTokens())
						return INVALIDPARAMETERS;
					else {
						tokenizer.getStringToken(strResource);
						if ( strResource == "mineral") {
							getMineralResources(creature);
						}
					}
				}
			}

			//info("in database command",true);
			if ( objectID == 0 && arg0 != "cityregions" )
			{
				creature->sendSystemMessage("Command format is database < playerstructures | sceneobjects | clientobjects >  <objectid>");
				setLogging(false);
				return INVALIDPARAMETERS;
			}

			Reference<SceneObject*> object = NULL;


			try {

				ObjectDatabaseManager* dManager = ObjectDatabaseManager::instance();
				ObjectDatabase* thisDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase(arg0, true);

				ObjectInputStream objectData(2000);



				uint32 serverObjectCRC;
				String className;

				//info("using DB " + arg0 + " and OID is " + String::valueOf(objectID));
				//info("going to call get data");


				if(arg0 == "cityregions"){
					//info("in cityregions",true);
					ObjectDatabaseIterator iterator(thisDatabase);
							uint64 objectID;
							ObjectInputStream* myobjectData = new ObjectInputStream(2000);

							//String zoneReference;
							String className;

							while(iterator.getNextKeyAndValue(objectID, myobjectData)){
								//CityRegion.regionName
								CityRegion* object = dynamic_cast<CityRegion*>(Core::getObjectBroker()->lookUp(objectID));
								if( object !=NULL){
									info( object->getRegionName() + "," + object->getZone()->getZoneName() +  "," + String::valueOf(object->getCityRank()),true);

								}

							}

					return 0 ;
				}
				if ( !(thisDatabase->getData(objectID,&objectData) ) ) {

					uint32 serverObjectCRC = 0;
					String className;
					//info("Going to check serializable");

					if ( Serializable::getVariable<uint32>("SceneObject.serverObjectCRC", &serverObjectCRC, &objectData)  )
					{
						// houses = BuildingObject
						Serializable::getVariable<String>("_className", &className, &objectData);

						creature->sendSystemMessage("Object found in " + arg0 + " datbase.  CLASS:   " + className);

						if ( className == "BuildingObject"  ) {
							uint16 _varCount = objectData.readShort();
							setLogging(true);
							info("there are " + String::valueOf(_varCount) + " variables");
							setLogging(false);
							StructurePermissionList structurePermissionList;
							//Serializable::getVariable<StructurePermissionList>("StructureObject.structurePermissionList", &structurePermissionList, &objectData);

							//TypeInfo<StructurePermissionList >::parseFromBinaryStream(&structurePermissionList, &objectData);
							//"StructureObject.structurePermissionList"

							setLogging(true);
							//info("permissionlist owner: " + structurePermissionList.getOwnerName());
							int totalSize = 0;

							for (int i = 0; i < _varCount; ++i) {
									String _name;
									_name.parseFromBinaryStream(&objectData);


									uint32 _varSize = objectData.readInt();
									int _currentOffset = objectData.getOffset();
									info("VAR: " + _name + "  SIZE: " + String::valueOf(_varSize));
									if (_name == "StructureObject.structurePermissionList") {

										TypeInfo<StructurePermissionList >::parseFromBinaryStream(&structurePermissionList, &objectData);

									}
									totalSize = _currentOffset + _varSize;
									objectData.setOffset(_currentOffset + _varSize);

							}
							//info("PermissionLIst owner is " + structurePermissionList.getOwnerName());
							info("total size of the buildingobject is " + String::valueOf(totalSize));

							setLogging(false);


						} else {
							uint16 _varCount = objectData.readShort();
							setLogging(true);
							info("there are " + String::valueOf(_varCount) + " variables");
							setLogging(false);

							setLogging(true);

							int totalSize = 0;

							for (int i = 0; i < _varCount; ++i) {
								String _name;
								_name.parseFromBinaryStream(&objectData);

								uint32 _varSize = objectData.readInt();
								int _currentOffset = objectData.getOffset();
								info("VAR: " + _name + "  SIZE: " + String::valueOf(_varSize));
								if ( _name == "InstallationObject.operating") {
									bool top;
									TypeInfo<bool>::parseFromBinaryStream(&top, &objectData);
									info("Operating: " + String::valueOf(top));
								} else if ( _name == "InstallationObject.lastStartTime") {
									Time ttime;
									TypeInfo<Time >::parseFromBinaryStream(&ttime, &objectData);
									info("LastStartTime = " + String::valueOf(ttime.getMiliTime()));

								} else if ( _name == "InstallationObject.lastStopTime" ) {
									Time ttime;
									TypeInfo<Time >::parseFromBinaryStream(&ttime, &objectData);
									info("LastStopTime = " + String::valueOf(ttime.getMiliTime()));
								} else if ( _name == "InstallationObject.resourceHopperTimestamp") {
									Time ttime;
									TypeInfo<Time >::parseFromBinaryStream(&ttime, &objectData);
									info("LastStopTime = " + String::valueOf(ttime.getMiliTime()));
								}
								totalSize = _currentOffset + _varSize;
								objectData.setOffset(_currentOffset + _varSize);
							}
							info("total size is " + String::valueOf(totalSize));
							setLogging(false);
						}
					} else {
						creature->sendSystemMessage("Not in DB or error in lookup");
						objectData.clear();

					}

				}
				else
					creature->sendSystemMessage("Not in DB or error in lookup");

					//delete objectDAta
					setLogging(false);

				} catch ( Exception& err ) {
					creature->sendSystemMessage("Error querying DB");
					setLogging(false);
					return GENERALERROR;
				}

				setLogging(false);

		return SUCCESS;
	}

	void getMineralResources(CreatureObject* creature){
		/*
		ObjectDatabaseManager* dManager = ObjectDatabaseManager::instance();
		ObjectDatabase* thisDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("resourcespawns", true);
		ObjectInputStream objectData(2000);



		uint32 serverObjectCRC;
		String className;

		//info("using DB " + arg0 + " and OID is " + String::valueOf(objectID));
		//info("going to call get data");
		if ( !(thisDatabase->getData(objectID,&objectData) ) ) {

			uint32 serverObjectCRC = 0;
			String className;
			//info("Going to check serializable");

			if ( Serializable::getVariable<uint32>("SceneObject.serverObjectCRC", &serverObjectCRC, &objectData)  )
			{
				// houses = BuildingObject
				Serializable::getVariable<String>("_className", &className, &objectData);

				creature->sendSystemMessage("Object found in " + arg0 + " datbase.  CLASS:   " + className);


				setLogging(true);
				//info("permissionlist owner: " + structurePermissionList.getOwnerName());
				int totalSize = 0;

				for (int i = 0; i < _varCount; ++i) {
						String _name;
						_name.parseFromBinaryStream(&objectData);


						uint32 _varSize = objectData.readInt();
						int _currentOffset = objectData.getOffset();
						info("VAR: " + _name + "  SIZE: " + String::valueOf(_varSize));

						/// do something based on class type/bariable name



						totalSize = _currentOffset + _varSize;
						objectData.setOffset(_currentOffset + _varSize);

				}
				info("PermissionLIst owner is " + structurePermissionList.getOwnerName());
				info("total size of the buildingobject is " + String::valueOf(totalSize));

				setLogging(false);

			}
			*/

	}

};

#endif //DATABASECOMMAND_H_
