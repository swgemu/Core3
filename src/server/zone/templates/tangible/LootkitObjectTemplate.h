/*
 * LootkitObjectTemplate.h
 *
 *  Created on: May 7, 2010
 *      Author: swgemu
 */

#ifndef LOOTKITOBJECTTEMPLATE_H_
#define LOOTKITOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class LootkitObjectTemplate: public SharedTangibleObjectTemplate {
protected:

	VectorMap<uint32, bool> components;
	VectorMap<uint32, String> attributes;
	Vector<uint32> comps;
	Vector<uint32> reward;

	bool deleteComponents;


public:
	LootkitObjectTemplate() {

	}

	~LootkitObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		deleteComponents = templateData->getByteField("deleteComponents");

		LuaObject collectibleComponents = templateData->getObjectField("collectibleComponents");
		for (int i = 1; i <= collectibleComponents.getTableSize(); ++i) {
			components.put(collectibleComponents.getStringAt(i).hashCode(), false);
			comps.add(i-1,collectibleComponents.getStringAt(i).hashCode());
		}
		collectibleComponents.pop();

		LuaObject collectibleComponentsAttributes = templateData->getObjectField("attributes");
		for (int i = 1; i <= collectibleComponentsAttributes.getTableSize(); ++i) {
			attributes.put(comps.get(i-1), collectibleComponentsAttributes.getStringAt(i));
		}
		collectibleComponentsAttributes.pop();

		LuaObject rewards = templateData->getObjectField("collectibleReward");
		for (int i = 1; i <= rewards.getTableSize(); ++i) {
			reward.add(i-1,rewards.getStringAt(i).hashCode());
		}
		rewards.pop();

	}

	VectorMap<uint32, bool> getComponents() const {
		return components;
	}

	VectorMap<uint32, String> getAttributes() const {
		return attributes;
	}

	Vector<uint32> getComps() const {
		return comps;
	}

	Vector<uint32> getReward() const {
		return reward;
	}

	bool getDeleteComponents() const {
		return deleteComponents;
	}

	void setDeleteComponents(bool deleteComponents) {
		this->deleteComponents = deleteComponents;
	}

	void setComponents(VectorMap<uint32, bool> components) {
		this->components = components;
	}

	void setAttributes(VectorMap<uint32, String> attributes) {
		this->attributes = attributes;
	}

	void setComps(Vector<uint32> comps) {
		this->comps = comps;
	}

	void setReward(Vector<uint32> reward) {
		this->reward = reward;
	}

};


#endif /* LOOTKITOBJECTTEMPLATE_H_ */
