/*
 * ObjectVersionUpdateManager.h
 *
 *  Created on: Oct 28, 2010
 *      Author: oru
 */

#ifndef OBJECTVERSIONUPDATEMANAGER_H_
#define OBJECTVERSIONUPDATEMANAGER_H_

#include "engine/engine.h"
#include "engine/log/Logger.h"
#include "engine/util/Singleton.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
class Stream;
}  // namespace io
}  // namespace sys

class ObjectVersionUpdateManager : public Singleton<ObjectVersionUpdateManager>, public Logger, public Object {

public:
	ObjectVersionUpdateManager();

	void initialize();

	void checkCurrentRevision();
	void runScripts();

	int updateToVersion2();
	int updateToVersion3();

	ObjectOutputStream* addVariable(String variableName, ObjectInputStream* object, Stream* newVariableData);
	int getVariableDataOffset(const uint32& variableHashCode, ObjectInputStream* stream);
	ObjectOutputStream* changeVariableData(const uint32& variableHashCode, ObjectInputStream* object, Stream* newVariableData);

	void updateTangibleObjectsVersion6();
	void updateResidences();
	void setResidence(uint64 buildingID, bool isResidence);
	void verifyResidenceVariables();
	void updateWeaponsDots();
	void updateStructurePermissionLists();

	void updateCityTreasury();
	void updateCityTreasuryToDouble();
	int run();

};

#endif /* OBJECTVERSIONUPDATEMANAGER_H_ */
