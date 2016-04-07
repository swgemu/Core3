/*
 * SharedGuildObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDGUILDOBJECTTEMPLATE_H_
#define SHAREDGUILDOBJECTTEMPLATE_H_

#include "templates/SharedUniverseObjectTemplate.h"

class SharedGuildObjectTemplate : public SharedUniverseObjectTemplate {

public:
	SharedGuildObjectTemplate() {

	}

	~SharedGuildObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SGLD') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedUniverseObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SGLD');

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

		iffStream->closeForm('SGLD');
	}


};

#endif /* SHAREDGUILDOBJECTTEMPLATE_H_ */
