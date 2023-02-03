/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTMESSAGE3_H_
#define INSTALLATIONOBJECTMESSAGE3_H_

#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"

class InstallationObjectMessage3 : public TangibleObjectMessage3 {
public:
	InstallationObjectMessage3(InstallationObject* inso) : TangibleObjectMessage3(inso, 0x494E534F, 0x05) {
		insertByte(inso->isActive()); // Active Flag
		insertFloat(inso->getSurplusPower()); // Energy Store
		insertFloat(inso->getBasePowerRate()); // Energy Rate

		setSize();
	}
};
#endif /*INSTALLATIONOBJECTMESSAGE3_H_*/
