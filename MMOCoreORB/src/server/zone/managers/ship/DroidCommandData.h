
#ifndef DROIDCOMMANDDATA_H_
#define DROIDCOMMANDDATA_H_

namespace server {
namespace zone {
namespace managers {
namespace ship {

class DroidCommandData : public Object {

protected:
	String commandName;
	String stringID;
	float delayModifier;
	int componentType;
	float energyEfficiency;
	float generalEfficiency;
	float damage;
	float frontReinforceRatio;
	float capacitorReinforcePercentage;
	float frontShieldRatio;

public:
	DroidCommandData(String command, String notifyString, float delay, int component, float energyModifier, float generalModifier, float incurDamage, float frontReinforcePercent, float capacitorReinforcePercent, float frontRatio) : Object() {
		commandName = command;
		stringID = notifyString;
		delayModifier = delay;
		componentType = component;
		energyEfficiency = energyModifier;
		generalEfficiency = generalModifier;
		damage = incurDamage;
		frontReinforceRatio = frontReinforcePercent;
		capacitorReinforcePercentage = capacitorReinforcePercent;
		frontShieldRatio = frontRatio;
	}

	~DroidCommandData() {
	}

	const String& getCommandName() const {
		return commandName;
	}

	const String& getStringID() const {
		return stringID;
	}

	float getDelayModifier() const {
		return delayModifier;
	}

	int getComponentType() const {
		return componentType;
	}

	float getEnergyEfficiency() const {
		return energyEfficiency;
	}

	float getGeneralEfficiency() const {
		return generalEfficiency;
	}

	float getDamage() const {
		return damage;
	}

	float getFrontReinforceRatio() const {
		return frontReinforceRatio;
	}

	float getCapacitorReinforcePercentage() const {
		return capacitorReinforcePercentage;
	}

	float getFrontShieldRatio() const {
		return frontShieldRatio;
	}
};

}
}
}
}

#endif /* DROIDCOMMANDDATA_H_ */
