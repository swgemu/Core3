#ifndef SHIPCOMPONENTOBJECTTEMPLATE_H_
#define SHIPCOMPONENTOBJECTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class ShipComponentTemplate: public SharedTangibleObjectTemplate {
protected:
	VectorMap<String, float> attributeMap;
	VectorMap<String, float> modifierMap;

	StringParam componentDataName;

public:
	ShipComponentTemplate() {
		attributeMap.setNoDuplicateInsertPlan();
		attributeMap.setNullValue(0.f);

		modifierMap.setNoDuplicateInsertPlan();
		modifierMap.setNullValue(0.f);
	}

	~ShipComponentTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		componentDataName = templateData->getStringField("componentDataName");

		auto attributes = templateData->getObjectField("attributes");

		if (attributes.isValidTable()) {
			for (int i = 1; i <= attributes.getTableSize(); ++i) {
				auto entry = attributes.getObjectAt(i);

				if (entry.isValidTable() && entry.getTableSize() == 2) {
					String key = entry.getStringAt(1);
					float value = entry.getFloatAt(2);

					attributeMap.put(key, value);
				}

				entry.pop();
			}
		}

		attributes.pop();

		auto modifiers = templateData->getObjectField("modifiers");

		if (modifiers.isValidTable()) {
			for (int i = 1; i <= modifiers.getTableSize(); ++i) {
				auto entry = modifiers.getObjectAt(i);

				if (entry.isValidTable() && entry.getTableSize() == 2) {
					String key = entry.getStringAt(1);
					float value = entry.getFloatAt(2);

					modifierMap.put(key, value);
				}

				entry.pop();
			}
		}

		modifiers.pop();
	}

	const VectorMap<String, float>& getAttributeMap() const {
		return attributeMap;
	}

	const VectorMap<String, float>& getModifierMap() const {
		return modifierMap;
	}

	const String& getComponentDataName() const {
		return componentDataName.get();
	}
};

#endif /* SHIPCOMPONENTOBJECTTEMPLATE_H_ */
