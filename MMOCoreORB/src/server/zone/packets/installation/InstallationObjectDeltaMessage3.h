/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTDELTAMESSAGE3_H_
#define INSTALLATIONOBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/objects/installation/InstallationObject.h"

class InstallationObjectDeltaMessage3 : public TangibleObjectDeltaMessage3 {
	InstallationObject* inso;

public:
	InstallationObjectDeltaMessage3(InstallationObject* ins)
			: TangibleObjectDeltaMessage3(ins, 0x494E534F) {
		inso = ins;
	}

	void updateOperating(bool value) {
		/*if (value)
			addIntUpdate(0x06, 0x00000101); // 01 01 00 00
		else
			addIntUpdate(0x06, 0x00000100); // 00 01 00 00*/
		addByteUpdate(0x0B, value);
	}
};


#endif /* INSTALLATIONOBJECTDELTAMESSAGE3_H_ */
