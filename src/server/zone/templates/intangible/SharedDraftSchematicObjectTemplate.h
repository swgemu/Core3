/*
 * SharedDraftSchematicObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDDRAFTSCHEMATICOBJECTTEMPLATE_H_
#define SHAREDDRAFTSCHEMATICOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedDraftSchematicObjectTemplate : public SharedIntangibleObjectTemplate {
public:
	SharedDraftSchematicObjectTemplate() {

	}

	~SharedDraftSchematicObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedIntangibleObjectTemplate::readObject(templateData);
	}
};


#endif /* SHAREDDRAFTSCHEMATICOBJECTTEMPLATE_H_ */
