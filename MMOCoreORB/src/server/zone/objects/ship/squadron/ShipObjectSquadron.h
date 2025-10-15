#ifndef SHIPOBJECTSQUADRON_H_
#define SHIPOBJECTSQUADRON_H_

namespace server {
	namespace zone {
		namespace objects {
			namespace ship {
				class ShipObject;
			}
		}
	}
}

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/ship/transform/SpaceTransform.h"
#include "server/zone/objects/ship/transform/SpaceTransformType.h"
#include "ShipSquadronFormation.h"

class SquadronDataEntry : public Object {
protected:
	Vector3 formation;
	Vector3 position;
	float speed;

public:
	SquadronDataEntry() : Object() {
		speed = 0.f;
	}

	const Vector3& getFormation() const {
		return formation;
	}

	const Vector3& getPosition() const {
		return position;
	}

	float getSpeed() const {
		return speed;
	}

	void setFormation(const Vector3& value) {
		formation = value;
	}

	void setPosition(const Vector3& value) {
		position = value;
	}

	void setSpeed(float value) {
		speed = value;
	}
};

class ShipObjectSquadron : public Object {
protected:
	Vector<Reference<ShipObject*>> squadron;
	Vector<SquadronDataEntry> squadronData;

	float formationRadius;
	int formationType;

public:
	ShipObjectSquadron() : Object() {
		formationRadius = 0.f;
		formationType = 0;
	}

	ShipObjectSquadron(ShipObject* ship);

	~ShipObjectSquadron();

	ShipObject* get(int index) const {
		return squadron.size() > index ? squadron.get(index) : nullptr;
	}

	int find(ShipObject* ship) const {
		return squadron.find(ship);
	}

	int size() const {
		return squadron.size();
	}

	int getFormationType() const {
		return formationType;
	}

	float getFormationRadius() const {
		return formationRadius;
	}

	void add(ShipObject* ship);

	void remove(ShipObject* ship);

	void setFormation(ShipObject* ship);

	void setFormationType(int type, float radius = -1.f);

	void setFormation(int index, const Vector3& position);

	void setPosition(int index, const Vector3& position);

	void setSpeed(int index, float speed);

	Vector3 getFormation(int index) const;

	Vector3 getPosition(int index) const;

	float getSpeed(int index) const;

	float getFormationSpeed() const;
};

#endif // SHIPOBJECTSQUADRON_H_
