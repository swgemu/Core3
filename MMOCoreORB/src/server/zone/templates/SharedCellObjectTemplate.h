/*
 * SharedCellObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDCELLOBJECTTEMPLATE_H_
#define SHAREDCELLOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"


class SharedCellObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedCellObjectTemplate() {

	}

	~SharedCellObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'CCLT') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('CCLT');

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

		iffStream->closeForm('CCLT');
	}


};


#endif /* SHAREDCELLOBJECTTEMPLATE_H_ */
