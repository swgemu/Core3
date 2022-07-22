//
// Created by g on 12/21/17.
//

#ifndef CORE3_SHIPCHASSISDATA_H
#define CORE3_SHIPCHASSISDATA_H

#include "engine/engine.h"

class DataTableRow;

class ShipChassisData {

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

		const Vector<const ComponentHardpoint*> getHardpoint(const String& name) const {
			return componentHardpoints.get(name);
		}

		void addHardpointData(String componentName, Vector<const ComponentHardpoint*>& hardpoints) {
			componentHardpoints.put(componentName, hardpoints);
		}

		const String& getName() const {
			return name;
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

	const String& getName() const {
		return name;
	}
    float getWingOpenSpeed() const {
        return wingOpenSpeed;
    }

	const ComponentSlotData* getComponentSlotData(int slotIndex) const {
		const static char* components[] = {"reactor", "engine", "shield_0", "shield_1", "armor_0", "armor_1", "capacitor", "booster", "droid_interface", "bridge", "hangar",
										   "targeting_station","weapon_0", "weapon_1", "weapon_2", "weapon_3", "weapon_4", "weapon_5","weapon_6", "weapon_7"};
		if (slotIndex < 20) {
			return componentMap.get(components[slotIndex]);
		} else {
			return componentMap.get("weapon_" + String::valueOf(slotIndex-12));
		}

	}

    const ComponentSlotData* getComponentData(const String& slot) const {
        return componentMap.get(slot);
    }
};


#endif //CORE3_SHIPCHASSISDATA_H
