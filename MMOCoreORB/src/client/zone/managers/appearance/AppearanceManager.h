/*
 * AppearanceManager.h
 *
 *  Created on: April 9, 2016
 *      Author: gslomin
 */

#ifndef APPEARANCEMANAGER_H_
#define APPEARANCEMANAGER_H_

#include "engine/engine.h"
#include "client/zone/objects/appearance/ClientAppearance.h"

class AppearanceManager : public Mutex, public Logger, public Singleton<AppearanceManager>, public Object {
	
	static ObjectFactory<ClientAppearance* (AppearanceTemplate*), uint32> appearanceFactory;
	void registerObjectTypes();
public:
	AppearanceManager();
	virtual ~AppearanceManager();

	ClientAppearance* getAppearance(AppearanceTemplate *tmpl) const;
};


#endif /* APPEARANCEMANAGER_H_ */
