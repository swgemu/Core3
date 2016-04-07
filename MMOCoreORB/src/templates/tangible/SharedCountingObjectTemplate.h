/*
 * SharedCountingObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDCOUNTINGOBJECTTEMPLATE_H_
#define SHAREDCOUNTINGOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class SharedCountingObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedCountingObjectTemplate() {

	}

	~SharedCountingObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SCOU') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedTangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SCOU');

		uint32 derv = iffStream->getNextFormType();

		if (derv == 'DERV') {
			loadDerv(iffStream);

			derv = iffStream->getNextFormType();
		}


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

		iffStream->closeForm('SCOU');
	}
};


#endif /* SHAREDCOUNTINGOBJECTTEMPLATE_H_ */
