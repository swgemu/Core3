/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef SURVEYTOOLTEMPLATE_H_
#define SURVEYTOOLTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

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

	void readObject(LuaObject* templateData) override {
		SharedTangibleObjectTemplate::readObject(templateData);

		toolType = templateData->getIntField("toolType");
		surveyType = templateData->getStringField("surveyType");
		surveyAnimation = templateData->getStringField("toolAnimation");
		sampleAnimation = templateData->getStringField("sampleAnimation");
	}

	int getToolType() const {
		return toolType;
	}

	const String& getSurveyType() const {
		return surveyType;
	}

	const String& getSurveyAnimation() const {
		return surveyAnimation;
	}

	const String& getSampleAnimation() const {
		return sampleAnimation;
	}
};

#endif /* SURVEYTOOLTEMPLATE_H_ */
