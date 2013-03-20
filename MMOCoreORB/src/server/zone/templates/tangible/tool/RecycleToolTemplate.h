#ifndef RECYCLETOOLTEMPLATE_H_
#define RECYCLETOOLTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"
#include "../ContainerTemplate.h"

class RecycleToolTemplate : public ContainerTemplate {
private:

	short toolType;

public:
	RecycleToolTemplate() {

	}

	~RecycleToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		ContainerTemplate::readObject(templateData);

		toolType = templateData->getByteField("toolType");
	}

	short getToolType() {
		return toolType;
	}

	bool isRecycleToolTemplate() {
		return true;
	}
};

#endif /* RECYCLETOOLTEMPLATE_H_ */
