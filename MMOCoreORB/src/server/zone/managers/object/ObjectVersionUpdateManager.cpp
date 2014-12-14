/*
 * ObjectVersionUpdateManager.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: oru
 */

#include "ObjectVersionUpdateManager.h"
#include "ObjectManager.h"
#include "server/zone/objects/player/Races.h"
#include "server/db/ServerDatabase.h"
#include "system/util/SortedVector.h"
#include "server/zone/objects/structure/StructurePermissionList.h"

#define INITIAL_DATABASE_VERSION 0

ObjectVersionUpdateManager::ObjectVersionUpdateManager() : Logger("ObjectVersionUpdateManager") {
	luaInstance = new Lua();
	luaInstance->init();
}


int ObjectVersionUpdateManager::run() {
	int version = ObjectDatabaseManager::instance()->getCurrentVersion();

	if (version == INITIAL_DATABASE_VERSION ){
		updateResidences();
		ObjectDatabaseManager::instance()->updateCurrentVersion(INITIAL_DATABASE_VERSION + 1);
		return 0;
	} else if ( version ==  INITIAL_DATABASE_VERSION + 1) {
		updateCityTreasury();
		ObjectDatabaseManager::instance()->updateCurrentVersion(INITIAL_DATABASE_VERSION + 2);
		return 0;
	} else if (version == INITIAL_DATABASE_VERSION + 2) {
		updateWeaponsDots();
		ObjectDatabaseManager::instance()->updateCurrentVersion(INITIAL_DATABASE_VERSION + 3);
		return 0;
	} else if (version == INITIAL_DATABASE_VERSION + 3) {
		updateStructurePermissionLists();
		ObjectDatabaseManager::instance()->updateCurrentVersion(INITIAL_DATABASE_VERSION + 4);
		return 0;
	} else if (version == INITIAL_DATABASE_VERSION + 4) {
		updateCityTreasuryToDouble();
		ObjectDatabaseManager::instance()->updateCurrentVersion(INITIAL_DATABASE_VERSION + 5);
		return 0;
	}  else {

		info("database on latest version : " + String::valueOf(version), true);
		//verifyResidenceVariables();
		return 1;
	}
/*

	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true);

	ObjectData baseIterator iterator(database);

	ObjectInputStream objectData(2000);
	uint64 objectID = 0;

	info("starting database update", true);

	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {
			bool municipalZone = false;

			try {
				if (!Serializable::getVariable<bool>("ActiveArea.municipalZone", &municipalZone, &objectData)) {
					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}

			//info("updating object", true);

			if (municipalZone) {
				database->deleteData(objectID);

				info("deleting municipal zone 0x" + String::hexvalueOf((int64)objectID), true);
			}

			objectData.clear();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	ObjectDatabaseManager::instance()->updateCurrentVersion(version);

	info("finished database update", true);

	return 0;
	*/
}



ObjectOutputStream* ObjectVersionUpdateManager::addVariable(String variableName, ObjectInputStream* object, Stream* newVariableData){
	object->reset();

	uint16 oldVariableCount = object->readShort();
	//info("first variable count is " + String::valueOf(oldVariableCount),true);
	ObjectOutputStream* newData = new ObjectOutputStream(object->size());
	object->copy(newData, 0);

	newData->writeShort(0, oldVariableCount + 1);
	newData->setOffset(newData->size());


	uint32 _nameHashCode = variableName.hashCode();
	TypeInfo<uint32>::toBinaryStream(&_nameHashCode, newData);
	newData->writeInt(newVariableData->size());
	newData->writeStream(newVariableData);

	return newData;


}

int ObjectVersionUpdateManager::getVariableDataOffset(const uint32& variableHashCode, ObjectInputStream* stream) {
	uint16 dataSize = stream->readShort();
	int offset;

	for (int i = 0; i < dataSize; ++i) {
		uint32 namehashCode = stream->readInt();

		uint32 varSize = stream->readInt();

		offset = stream->getOffset();

		if (namehashCode != variableHashCode)
			stream->shiftOffset(varSize);
		else {
			stream->reset();
			return offset;
		}
	}

	offset = -1;

	stream->reset();

	return offset;
}

ObjectOutputStream* ObjectVersionUpdateManager::changeVariableData(const uint32& variableHashCode, ObjectInputStream* object, Stream* newVariableData) {
	int offset = getVariableDataOffset(variableHashCode, object);

	if (offset == -1)
		return NULL;

	ObjectOutputStream* newData = new ObjectOutputStream(object->size());
	object->copy(newData);

	object->reset();
	newData->reset();
	object->shiftOffset(offset - 4);
	uint32 dataSize = object->readInt();

	newData->shiftOffset(offset); //we go data length

	if (dataSize > 0)
		newData->removeRange(offset, offset + dataSize);

	newData->writeInt(offset - 4, newVariableData->size());
	newData->insertStream(newVariableData, newVariableData->size(), offset);

	object->reset();
	//newData->reset();

	return newData;
}

void ObjectVersionUpdateManager::updateWeaponsDots() {
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true);

	ObjectDatabaseIterator iterator(database);
	ObjectInputStream objectData(2000);
	uint64 objectID = 0;

	info("update database weapon dots", true);

	int count = 0;
	uint32 classNameHashCode = String("_className").hashCode();
	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {
			String className;
			int oldType = 0;

			try {
				if (!Serializable::getVariable<String>(classNameHashCode, &className, &objectData) ||
						!Serializable::getVariable<int>(String("WeaponObject.dotType").hashCode(), &oldType, &objectData)) {

					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}

			if (className == "WeaponObject") {
				Vector<int> dots;

				ObjectOutputStream newDotsValue;
				TypeInfo<Vector<int> >::toBinaryStream(&dots, &newDotsValue);

				//	info("we found a Player " + String::valueOf(objectID) + " with residence " + String::valueOf(residence),true);
				ObjectOutputStream* newData = changeVariableData(String("WeaponObject.dotType").hashCode(), &objectData, &newDotsValue);
				newData->reset();

				ObjectInputStream* inputStream = new ObjectInputStream(newData->getBuffer(), newData->size());
				delete newData;

				ObjectOutputStream* newNextData = changeVariableData(String("WeaponObject.dotAttribute").hashCode(), inputStream, &newDotsValue);
				newNextData->reset();

				delete inputStream;
				inputStream = new ObjectInputStream(newNextData->getBuffer(), newNextData->size());
				delete newNextData;

				newData = changeVariableData(String("WeaponObject.dotStrength").hashCode(), inputStream, &newDotsValue);
				newData->reset();

				delete inputStream;
				inputStream = new ObjectInputStream(newData->getBuffer(), newData->size());
				delete newData;

				newNextData = changeVariableData(String("WeaponObject.dotDuration").hashCode(), inputStream, &newDotsValue);
				newNextData->reset();

				delete inputStream;
				inputStream = new ObjectInputStream(newNextData->getBuffer(), newNextData->size());
				delete newNextData;

				newData = changeVariableData(String("WeaponObject.dotPotency").hashCode(), inputStream, &newDotsValue);
				newData->reset();

				delete inputStream;
				inputStream = new ObjectInputStream(newData->getBuffer(), newData->size());
				delete newData;

				newNextData = changeVariableData(String("WeaponObject.dotUses").hashCode(), inputStream, &newDotsValue);
				newNextData->reset();

				delete inputStream;

				database->putData(objectID, newNextData, NULL);
			}

			objectData.clear();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	info("done updating databse weapon dots\n", true);
}


void ObjectVersionUpdateManager::updateStructurePermissionLists() {
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("playerstructures", true);

	ObjectDatabaseIterator iterator(database);

	ObjectInputStream objectData(2000);
	uint64 objectID = 0;
	int count = 0;

	info("Setting owner on structure permission lists",true);

	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {

			String className;

			try {
				if (!Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)) {
					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}

			if (className == "BuildingObject" || className == "InstallationObject" || className == "GarageInstallation" || className == "ShuttleInstallation") {
				uint64 ownerID = 0;
				String ownerName;
				count ++;
				printf("\r\tUpdating structure owners [%d] / [?]\t", count);

				if( Serializable::getVariable<uint64>(String("StructureObject.ownerObjectID").hashCode(), &ownerID, &objectData)) {
					StructurePermissionList permissionList;

					if ( Serializable::getVariable<StructurePermissionList>(String("StructureObject.structurePermissionList").hashCode(), &permissionList, &objectData)){
						ObjectOutputStream newOutputStream;
						permissionList.setOwner(ownerID);
						permissionList.toBinaryStream(&newOutputStream);

						ObjectOutputStream* test = changeVariableData(String("StructureObject.structurePermissionList").hashCode(), &objectData, &newOutputStream);
						test->reset();
						database->putData(objectID, test, NULL);
					} else {
						info("ERROR unable to get structurePermissionList for structure " + String::valueOf(objectID),true);
					}

				} else {
					info("ERROR unable to get ownerObjectID for structure " + String::valueOf(objectID),true);
				}
			}
			objectData.clear();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
	info("Done updating owner on structure permission lists\n",true);

}

void ObjectVersionUpdateManager::updateResidences(){
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true);

	ObjectDatabaseIterator iterator(database);

	ObjectInputStream objectData(2000);
	uint64 objectID = 0;
	info("---------------Setting residences---------------------",true);
	info("Setting residence values for all active player residences ", true);

	int count = 0;
	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {

			String className;
			uint64 residence = 0;

			try {
				if (!Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData) ||
						!Serializable::getVariable<uint64>(String("PlayerObject.declaredResidence").hashCode(), &residence, &objectData)) {

					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}

			if (className == "PlayerObject") {
			//	info("we found a Player " + String::valueOf(objectID) + " with residence " + String::valueOf(residence),true);
				SortedVector<unsigned long long> structureList;
				uint64 residence = 0;
				count++;
				printf("\r\tUpdating player residence [%d] / [?]\t", count);
				if( Serializable::getVariable< SortedVector<unsigned long long> >(String("PlayerObject.ownedStructures").hashCode(), &structureList, &objectData) &&
						Serializable::getVariable<uint64>(String("PlayerObject.declaredResidence").hashCode(), &residence, &objectData)){

					for(int i = 0; i < structureList.size(); i++){
						bool isRes = (structureList.get(i) == residence);
						//info("Owned structure " + String::valueOf(structureList.get(i)) + " residence =  " + String::valueOf(isRes),true);
						setResidence(structureList.get(i),isRes);
					}
				} else {
					info("ERROR unable to get ownedStructures for player " + String::valueOf(objectID),true);
				}

			}

			objectData.clear();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
	info("\n",true);

}

void ObjectVersionUpdateManager::setResidence(uint64 buildingID, bool isResidence){
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("playerstructures", true);
	ObjectInputStream objectData(2000);

	bool res  = isResidence;
	String className;

	ObjectOutputStream newResidenceValue;
	TypeInfo<bool>::toBinaryStream(&res, &newResidenceValue );

	if(!database->getData(buildingID,&objectData)){


		if ( Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)){

			if(className == "BuildingObject"){
				if ( !Serializable::getVariable<bool>(String("BuildingObject.isOwnerResidence").hashCode(), &isResidence, &objectData)){
					//info("setResidence() adding the variable",true);
					ObjectOutputStream* newVariableData = addVariable("BuildingObject.isOwnerResidence", &objectData, &newResidenceValue);
					database->putData(buildingID, newVariableData, NULL);

				} else {
					//info("setResidence() has variable and value = " + String::valueOf(isResidence) +  " ... changing it",true);
					ObjectOutputStream* test = changeVariableData(String("BuildingObject.isOwnerResidence").hashCode(), &objectData, &newResidenceValue);
					test->reset();
					database->putData(buildingID, test, NULL);
				}

			}
		} else {

			info("ERROR couldn't get object " + String::valueOf(buildingID),true);

		}


	}
}

void ObjectVersionUpdateManager::updateCityTreasury(){

	info("---------------MOdifying City Treasury---------------------",true);
	info("Converting treasury to float for all cities ", true);
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("cityregions", true);
	ObjectInputStream objectData(2000);

	String className;
	ObjectDatabaseIterator iterator(database);

	uint64 objectID = 0;
	int count = 0;
	try {
		while (iterator.getNextKeyAndValue(objectID, &objectData)) {

			String className;
			try {

				if (!Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)) {

					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}
			int funds;
			float floatFunds = 5;

			if (className == "CityRegion") {
				count++;
				printf("\r\tUpdating city treasury [%d] / [?]\t", count);
				if ( Serializable::getVariable<int>(String("CityRegion.cityTreasury").hashCode(), &funds, &objectData)){

					floatFunds = funds;
					ObjectOutputStream newFunds;
					TypeInfo<float>::toBinaryStream(&floatFunds, &newFunds );
					ObjectOutputStream* test = changeVariableData(String("CityRegion.cityTreasury").hashCode(), &objectData, &newFunds);
					test->reset();
					database->putData(objectID, test, NULL);


				} else {
					info("Error... city " + String::valueOf(objectID) + " doesn't have cityTreasury variable",true);
				}
			}

			objectData.clear();


		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

}

void ObjectVersionUpdateManager::updateCityTreasuryToDouble(){

	info("---------------MOdifying City Treasury---------------------",true);
	info("Converting treasury to double for all cities ", true);
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("cityregions", true);
	ObjectInputStream objectData(2000);

	String className;
	ObjectDatabaseIterator iterator(database);

	uint64 objectID = 0;
	int count = 0;
	try {
		while (iterator.getNextKeyAndValue(objectID, &objectData)) {

			String className;
			try {

				if (!Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)) {

					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}
			float funds;
			double floatFunds = 5;

			if (className == "CityRegion") {
				count++;
				printf("\r\tUpdating city treasury [%d] / [?]\t", count);
				if ( Serializable::getVariable<float>(String("CityRegion.cityTreasury").hashCode(), &funds, &objectData)){

					floatFunds = funds;
					ObjectOutputStream newFunds;
					TypeInfo<double>::toBinaryStream(&floatFunds, &newFunds );
					ObjectOutputStream* test = changeVariableData(String("CityRegion.cityTreasury").hashCode(), &objectData, &newFunds);
					test->reset();
					database->putData(objectID, test, NULL);


				} else {
					info("Error... city " + String::valueOf(objectID) + " doesn't have cityTreasury variable",true);
				}
			}

			objectData.clear();


		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

}
