/*
 * SharedBattlefieldMarkerObjectTemplate.h
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#ifndef SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_
#define SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedBattlefieldMarkerObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedBattlefieldMarkerObjectTemplate() {

	}

	~SharedBattlefieldMarkerObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SBMK') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedTangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SBMK');

		uint32 derv = iffStream->getNextFormType();

		if (derv == 'DERV') {
			loadDerv(iffStream);

			derv = iffStream->getNextFormType();
		}

		/*while (derv != 0) {
					if (derv != '
				}*/

		iffStream->openForm(derv);

		try {
			//parseFileData(iffStream);
		} catch (Exception& e) {
			String msg;
			msg += "exception caught parsing file data ->";
			msg += e.getMessage();

			Logger::console.error(msg);
		}

		iffStream->closeForm(derv);

		if (iffStream->getRemainingSubChunksNumber() > 0) {
			readObject(iffStream);
		}

		iffStream->closeForm('SBMK');
	}

};


#endif /* SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_ */
