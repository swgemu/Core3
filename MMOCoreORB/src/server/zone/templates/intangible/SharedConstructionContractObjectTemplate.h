/*
 * SharedConstructionContractObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDCONSTRUCTIONCONTRACTOBJECTTEMPLATE_H_
#define SHAREDCONSTRUCTIONCONTRACTOBJECTTEMPLATE_H_

#include "templates/SharedIntangibleObjectTemplate.h"

class SharedConstructionContractObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedConstructionContractObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SCNC') {
			//Logger::console.error("expecting SCNC got " + String::hexvalueOf((int)nextType));

			SharedIntangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SCNC');

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

		iffStream->closeForm('SCNC');
	}

	~SharedConstructionContractObjectTemplate() {

	}


};


#endif /* SHAREDCONSTRUCTIONCONTRACTOBJECTTEMPLATE_H_ */
