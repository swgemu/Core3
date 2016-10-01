/*
 * AppearanceManager.cpp
 *
 *  Created on: April 9, 2016
 *      Author: gslomin
 */

#include "AppearanceManager.h"
#include "client/zone/objects/appearance/ClientDetailAppearance.h"
#include "client/zone/objects/appearance/ClientMeshAppearance.h"
#include "client/zone/objects/appearance/ClientComponentAppearance.h"

ObjectFactory<ClientAppearance* (const AppearanceTemplate*), uint32> AppearanceManager::appearanceFactory;

AppearanceManager::AppearanceManager() : Mutex("AppearanceManager"), Logger("AppearanceManager") {
	registerObjectTypes();
}

AppearanceManager::~AppearanceManager() {

}

void AppearanceManager::registerObjectTypes() {
	info("registering appearance types");
	appearanceFactory.registerObject<ClientAppearance>('APPR');
	appearanceFactory.registerObject<ClientDetailAppearance>('DTAL');
	appearanceFactory.registerObject<ClientComponentAppearance>('CMPA');
	appearanceFactory.registerObject<ClientMeshAppearance>('MESH');
}


ClientAppearance* AppearanceManager::getAppearance(const AppearanceTemplate *tmpl) const {
	if (tmpl == NULL)
		return NULL;
	
	ClientAppearance *appearance = appearanceFactory.createObject(tmpl->getType(), tmpl);
	
	return appearance;
}
