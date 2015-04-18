/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTMESSAGE3_H_
#define INSTALLATIONOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/installation/InstallationObject.h"

#include "../tangible/TangibleObjectMessage3.h"

class InstallationObjectMessage3 : public TangibleObjectMessage3 {
public:
	InstallationObjectMessage3(InstallationObject* inso)
			: TangibleObjectMessage3(inso, 0x494E534F, 0x05) {
		/*insertFloat(1.0); // Complexity
		insertAscii("installation_n"); // STF FileName
		insertInt(0); //nothing.
		insertAscii(inso->getTemplateName()); // STF Template
		insertUnicode(inso->getCustomName()); // Object Name
		insertInt(1); // Volume

		String app;
		inso->getCustomizationString(app);
		insertAscii(app); // I think - seems to work - but no real options to update, //insertShort(0);

		insertInt(0); // ?? List  (Defenders?)
		insertInt(0); // Update Counter
		// { insertInt(0); } // ??

		insertInt(0x00000100); // 00 01 00 00; // OptionsBitMask
		//insertInt(0x00010000); // OptionsBitMask
		insertInt(0); // Timer (Incap/Prototype)

		insertInt(inso->getConditionDamage());//insertInt(0x03E80000); // max condition ??
		insertInt(inso->getMaxCondition()); //insertInt(0x00010000); //refer to hardcode below. (trying to replace)

		insertByte(0); // ??*/

		insertByte(1); // Active Flag
		insertFloat(inso->getSurplusPower()); // Energy Store
		insertFloat(inso->getBasePowerRate()); // Energy Rate

		setSize();
	}
};
#endif /*INSTALLATIONOBJECTMESSAGE3_H_*/
