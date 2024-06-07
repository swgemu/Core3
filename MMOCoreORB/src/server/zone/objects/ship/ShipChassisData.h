//
// Created by g on 12/21/17.
//

#ifndef CORE3_SHIPCHASSISDATA_H
#define CORE3_SHIPCHASSISDATA_H

#include "engine/engine.h"
#include "ComponentSlots.h"

class DataTableRow;

class ShipChassisData : public Object {

public:
	class ComponentHardpoint : public Object {
		String templateName;
		String hardpointName;
		float range;
	public:
		ComponentHardpoint(const String& tmpl, const String& hardpoint, float collisionDistance) {
			templateName = tmpl;
			hardpointName = hardpoint;
			range = collisionDistance;
		}

		float getRange() const {
			return range;
		}

		bool isVisible() const {
			return !templateName.isEmpty();
		}

		const String& getTemplateName() const {
			return templateName;
		}

		const String& getHardpointName() const {
			return hardpointName;
		}
	};

	class ComponentSlotData : public Object {
		String name;
		String compatability;
		float hitWeight;
		bool targetable;
		VectorMap<String, Vector<const ComponentHardpoint*>> componentHardpoints;
	public:
		ComponentSlotData(const String& slotName, const String& slotCompatability, float weight, bool isTargetable) {
			name = slotName;
			compatability = slotCompatability;
			hitWeight = weight;
			targetable = isTargetable;
		}

		ComponentSlotData(const ComponentSlotData& rhs) : Object(rhs) {
			name = rhs.name;
			compatability = rhs.compatability;
			hitWeight = rhs.hitWeight;
			targetable = rhs.targetable;
			componentHardpoints = rhs.componentHardpoints;
		}

		const VectorMap<String, Vector<const ComponentHardpoint*>>& getComponentHardpoints() const {
			return componentHardpoints;
		}

		const Vector<const ComponentHardpoint*>& getHardpoint(const String& name) const {
			return componentHardpoints.get(name);
		}

		void addHardpointData(String componentName, Vector<const ComponentHardpoint*>& hardpoints) {
			componentHardpoints.put(componentName, hardpoints);
		}

		const String& getName() const {
			return name;
		}

		const String& getCompatability() const {
			return compatability;
		}

		float getHitWeight() const {
			return hitWeight;
		}

		bool isTargetable() const {
			return targetable;
		}
	};

protected:
	String name;
	float wingOpenSpeed;
	int type;

	VectorMap<String, ComponentSlotData*> componentMap;
	void loadComponentHardpoints();
public:
	ShipChassisData(DataTableRow *row, Vector<String>& columnNames);

	~ShipChassisData();

	const String& getName() const {
		return name;
	}
	float getWingOpenSpeed() const {
		return wingOpenSpeed;
	}

	const ComponentSlotData* getComponentSlotData(int slotIndex) const {
		return componentMap.get(Components::shipComponentSlotToString(slotIndex));
	}
};

#endif //CORE3_SHIPCHASSISDATA_H
