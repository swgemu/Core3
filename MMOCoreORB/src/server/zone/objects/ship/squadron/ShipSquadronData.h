#ifndef SHIPSQUADRONDATA_H_
#define SHIPSQUADRONDATA_H_

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
#include "ShipSquadronFormation.h"

class ShipSquadronDataEntry : public Object {
protected:
	Vector3 formation;
	Vector3 position;
	float speed;

public:
	ShipSquadronDataEntry() : Object() {
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

class ShipSquadronData : public Object, public Logger {
private:
	constexpr static float AUTO_RADIUS_MODIFIER = 5.f;

protected:
	Vector<ShipSquadronDataEntry> squadronData;
	float formationRadius;
	int formationType;

public:
	ShipSquadronData() : Object() {
		formationRadius = 0.f;
		formationType = 0;
	}

	ShipSquadronData(ShipObject* ship);

	~ShipSquadronData();

	int size() const {
		return squadronData.size();
	}

	int getFormationType() const {
		return formationType;
	}

	float getFormationRadius() const {
		return formationRadius;
	}

	void setFormationType(int value) {
		formationType = value;
	}

	void setFormationRadius(float value) {
		formationRadius = value;
	}

	void add(ShipObject* ship);

	void remove(int index);

	void makeLeader(ShipObject* ship);

	void setFormation(int index, float radius);

	void setFormation(int index, const Vector3& position);

	void setPosition(int index, const Vector3& position);

	void setSpeed(int index, float speed);

	Vector3 getFormation(int index) const;

	Vector3 getPosition(int index) const;

	float getSpeed(int index) const;

	float getFormationSpeed() const;
};

#endif // SHIPSQUADRONDATA_H_
