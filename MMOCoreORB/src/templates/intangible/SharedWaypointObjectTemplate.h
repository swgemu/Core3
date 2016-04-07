/*
 * SharedWaypointObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDWAYPOINTOBJECTTEMPLATE_H_
#define SHAREDWAYPOINTOBJECTTEMPLATE_H_

#include "templates/SharedIntangibleObjectTemplate.h"

class SharedWaypointObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedWaypointObjectTemplate() {

	}

	~SharedWaypointObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SWAY') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedIntangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SWAY');

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

		iffStream->closeForm('SWAY');
	}

};


#endif /* SHAREDWAYPOINTOBJECTTEMPLATE_H_ */
