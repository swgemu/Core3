/*
 * SharedMissionDataObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDMISSIONDATAOBJECTTEMPLATE_H_
#define SHAREDMISSIONDATAOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedMissionDataObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedMissionDataObjectTemplate() {

	}

	~SharedMissionDataObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SMSD') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedIntangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SMSD');

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

		iffStream->closeForm('SMSD');
	}


};


#endif /* SHAREDMISSIONDATAOBJECTTEMPLATE_H_ */
