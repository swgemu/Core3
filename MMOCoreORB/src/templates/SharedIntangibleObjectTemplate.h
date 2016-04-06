/*
 * SharedIntangibleObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDINTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDINTANGIBLEOBJECTTEMPLATE_H_


#include "templates/SharedObjectTemplate.h"


class SharedIntangibleObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedIntangibleObjectTemplate() {

	}

	~SharedIntangibleObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SITN') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SITN');

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

		iffStream->closeForm('SITN');
	}

	void readObject(LuaObject* templateData) {
		SharedObjectTemplate::readObject(templateData);
	}

};


#endif /* SHAREDINTANGIBLEOBJECTTEMPLATE_H_ */
