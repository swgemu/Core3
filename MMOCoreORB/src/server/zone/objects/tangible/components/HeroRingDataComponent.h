
#ifndef HERORINGDATACOMPONENT_H_
#define HERORINGDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"

class HeroRingDataComponent : public DataObjectComponent {
protected:
	int charges;
public:
	HeroRingDataComponent() {
		charges = 50;
		addSerializableVariables();
	}

	virtual ~HeroRingDataComponent() {

	}

	void setCharges(int num) {
		charges = num;
	}

	int getCharges() {
		return charges;
	}

	bool isHeroRingData() {
		return true;
	}

private:
	void addSerializableVariables() {
		addSerializableVariable("charges", &charges);
	}
};


#endif /* HERORINGDATACOMPONENT_H_ */
