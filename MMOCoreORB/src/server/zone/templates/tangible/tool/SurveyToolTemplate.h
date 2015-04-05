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
	String surveyAnimation;
	String sampleAnimation;

public:
	SurveyToolTemplate() : toolType(0) {

	}

	~SurveyToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		toolType = templateData->getIntField("toolType");
		surveyType = templateData->getStringField("surveyType");
		surveyAnimation = templateData->getStringField("toolAnimation");
		sampleAnimation = templateData->getStringField("sampleAnimation");
	}

	int getToolType() {
		return toolType;
	}

	String getSurveyType() {
		return surveyType;
	}

	String getSurveyAnimation() {
		return surveyAnimation;
	}

	String getSampleAnimation() {
		return sampleAnimation;
	}
};

#endif /* SURVEYTOOLTEMPLATE_H_ */
