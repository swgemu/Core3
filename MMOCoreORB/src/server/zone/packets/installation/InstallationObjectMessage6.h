/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTMESSAGE6_H_
#define INSTALLATIONOBJECTMESSAGE6_H_

#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"

class InstallationObjectMessage6 : public TangibleObjectMessage6 {
public:
	InstallationObjectMessage6(InstallationObject * inso)
			: TangibleObjectMessage6(inso, 0x494E534F, 0x05) {
printf("InstallationObjectMessage6\n");
		setSize();
	}
};
#endif /*INSTALLATIONOBJECTMESSAGE6_H_*/
