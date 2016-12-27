#ifndef RECYCLETOOLTEMPLATE_H_
#define RECYCLETOOLTEMPLATE_H_

#include "templates/tangible/ContainerTemplate.h"

class RecycleToolTemplate : public ContainerTemplate {
private:

	short toolType;
	Vector<String> resourceTypes;

public:
	RecycleToolTemplate() : toolType(0) {

	}

	~RecycleToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		ContainerTemplate::readObject(templateData);

		toolType = templateData->getByteField("toolType");

		LuaObject resources = templateData->getObjectField("resourceTypes");
		for (int i = 1; i <= resources.getTableSize(); ++i) {
			resourceTypes.add(resources.getStringAt(i));
		}
		resources.pop();
	}

	short getToolType() {
		return toolType;
	}

	Vector<String> getResourceTypes() {
		return resourceTypes;
	}

	bool isRecycleToolTemplate() {
		return true;
	}
};

#endif /* RECYCLETOOLTEMPLATE_H_ */
