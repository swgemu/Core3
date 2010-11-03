/*
 * ObjectVersionUpdateManager.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: oru
 */

#include "ObjectVersionUpdateManager.h"


ObjectVersionUpdateManager::ObjectVersionUpdateManager() {
	luaInstance = new Lua();
	luaInstance->init();
}


