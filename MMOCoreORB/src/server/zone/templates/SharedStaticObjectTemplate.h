/*
 * SharedStaticObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDSTATICOBJECTTEMPLATE_H_
#define SHAREDSTATICOBJECTTEMPLATE_H_


#include "SharedObjectTemplate.h"
#include "tangible/SharedBuildingObjectTemplate.h"


class SharedStaticObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedStaticObjectTemplate() {

	}

	~SharedStaticObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedObjectTemplate::readObject(templateData);
	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'STAT') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('STAT');

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

		iffStream->closeForm('STAT');
	}

};


#endif /* SHAREDSTATICOBJECTTEMPLATE_H_ */
