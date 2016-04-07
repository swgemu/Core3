/*
 * SharedGroupObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDGROUPOBJECTTEMPLATE_H_
#define SHAREDGROUPOBJECTTEMPLATE_H_


#include "templates/SharedUniverseObjectTemplate.h"

class SharedGroupObjectTemplate : public SharedUniverseObjectTemplate {

public:
	SharedGroupObjectTemplate() {

	}

	~SharedGroupObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SGRP') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedUniverseObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SGRP');

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

		iffStream->closeForm('SGRP');
	}


};


#endif /* SHAREDGROUPOBJECTTEMPLATE_H_ */
