#ifndef RECYCLETOOLTEMPLATE_H_
#define RECYCLETOOLTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"
#include "../ContainerTemplate.h"

class RecycleToolTemplate : public ContainerTemplate {
private:

	short toolType;
	Vector<String> resourceTypes;

public:
	RecycleToolTemplate() {

	}

	~RecycleToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		ContainerTemplate::readObject(templateData);

		toolType = templateData->getByteField("toolType");

		String resources = templateData->getStringField("resourceTypes");

		StringTokenizer resourceTokens(resources);
		resourceTokens.setDelimeter(",");

		while (resourceTokens.hasMoreTokens()) {
			String token;
			resourceTokens.getStringToken(token);
			resourceTypes.add(token);
		}
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
