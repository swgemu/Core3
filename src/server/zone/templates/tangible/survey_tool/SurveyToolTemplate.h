/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef SURVEYTOOLTEMPLATE_H_
#define SURVEYTOOLTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"

class SurveyToolTemplate : public SharedTangibleObjectTemplate {
private:

	int toolType;
	String surveyType;

public:
	SurveyToolTemplate() {

	}

	~SurveyToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		toolType = templateData->getIntField("toolType");
		surveyType = templateData->getStringField("surveyType");
	}

	int getToolType() {
		return toolType;
	}

	String getSurveyType() {
		return surveyType;
	}
};

#endif /* SURVEYTOOLTEMPLATE_H_ */
