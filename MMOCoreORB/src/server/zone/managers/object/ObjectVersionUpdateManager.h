/*
 * ObjectVersionUpdateManager.h
 *
 *  Created on: Oct 28, 2010
 *      Author: oru
 */

#ifndef OBJECTVERSIONUPDATEMANAGER_H_
#define OBJECTVERSIONUPDATEMANAGER_H_

#include "engine/engine.h"

class ObjectVersionUpdateManager : public Singleton<ObjectVersionUpdateManager>, public Logger, public Object {
	Lua* luaInstance;
public:
	ObjectVersionUpdateManager();

	void initialize();

	void checkCurrentRevision();
	void runScripts();

	int updateToVersion2();
	int updateToVersion3();

	int run();
};


#endif /* OBJECTVERSIONUPDATEMANAGER_H_ */
