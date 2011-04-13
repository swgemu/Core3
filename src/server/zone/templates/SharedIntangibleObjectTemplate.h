/*
 * SharedIntangibleObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDINTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDINTANGIBLEOBJECTTEMPLATE_H_


#include "SharedObjectTemplate.h"


class SharedIntangibleObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedIntangibleObjectTemplate() {

	}

	~SharedIntangibleObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedObjectTemplate::readObject(templateData);
	}

};


#endif /* SHAREDINTANGIBLEOBJECTTEMPLATE_H_ */
