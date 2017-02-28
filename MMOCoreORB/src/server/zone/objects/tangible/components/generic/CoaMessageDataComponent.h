
#ifndef COAMESSAGEDATACOMPONENT_H_
#define COAMESSAGEDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"

class CoaMessageDataComponent : public DataObjectComponent {
protected:
	SerializableString faction;
	int number;
public:
	CoaMessageDataComponent() {
		number = 1;
		addSerializableVariables();
	}

	virtual ~CoaMessageDataComponent() {

	}

	void setFaction(String side) {
		faction = side;
	}

	void setNumber(int num) {
		number = num;
	}

	String getFaction() {
		return faction;
	}

	int getNumber() {
		return number;
	}

	bool isCoaMessageData() {
		return true;
	}

private:
	void addSerializableVariables() {
		addSerializableVariable("faction", &faction);
		addSerializableVariable("number", &number);
	}
};


#endif /* COAMESSAGEDATACOMPONENT_H_ */
