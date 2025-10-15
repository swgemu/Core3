#include "ShipObjectSquadron.h"
#include "server/zone/objects/ship/ShipObject.h"

ShipObjectSquadron::ShipObjectSquadron(ShipObject* ship) : Object() {
	formationRadius = ShipSquadronFormation::NONE;
	formationType = ShipSquadronFormation::NONE;
	add(ship);
}

ShipObjectSquadron::~ShipObjectSquadron() {
	squadron.removeAll();
	squadronData.removeAll();
}

void ShipObjectSquadron::add(ShipObject* ship) {
	if (ship == nullptr || squadron.contains(ship)) {
		return;
	}

	squadron.add(ship);
	squadronData.add(SquadronDataEntry());
	setFormation(ship);
}

void ShipObjectSquadron::remove(ShipObject* ship) {
	int index = squadron.find(ship);

	if (index != -1) {
		squadron.remove(index);
		squadronData.remove(index);
	}
}

void ShipObjectSquadron::setFormation(ShipObject* ship) {
	int index = squadron.find(ship);

	if (index != -1) {
		float distance = ship->getBoundingRadius() * 2.f;

		if (formationRadius > 0.f) {
			distance = Math::max(formationRadius / (float)squadron.size(), distance);
		}

		auto formation = ShipSquadronFormation::getPosition(formationType, index, distance, squadron.size());
		setFormation(index, formation);
	}
}

void ShipObjectSquadron::setFormationType(int type, float radius) {
	if (type <= ShipSquadronFormation::NONE || type >= ShipSquadronFormation::SIZE) {
		type = System::random(type >= ShipSquadronFormation::SIZE - 1);
	}

	if (formationRadius == radius && formationType == type) {
		return;
	}

	formationRadius = radius;
	formationType = type;

	for (int i = 0; i < squadron.size(); ++i) {
		setFormation(squadron.get(i));
	}
}

void ShipObjectSquadron::setFormation(int index, const Vector3& position) {
	if (squadronData.size() > index) {
		squadronData.get(index).setFormation(position);
	}
}

void ShipObjectSquadron::setPosition(int index, const Vector3& position) {
	if (squadronData.size() > index) {
		squadronData.get(index).setPosition(position);
	}
}

void ShipObjectSquadron::setSpeed(int index, float speed) {
	if (squadronData.size() > index) {
		squadronData.get(index).setSpeed(speed);
	}
}

Vector3 ShipObjectSquadron::getFormation(int index) const {
	return squadronData.size() > index ? squadronData.get(index).getFormation() : Vector3::ZERO;
}

Vector3 ShipObjectSquadron::getPosition(int index) const {
	return squadronData.size() > index ? squadronData.get(index).getPosition() : Vector3::ZERO;
}

float ShipObjectSquadron::getSpeed(int index) const {
	return squadronData.size() > index ? squadronData.get(index).getSpeed() : 0.f;
}

float ShipObjectSquadron::getFormationSpeed() const {
	float speed = FLT_MAX;

	for (int i = 1; i < squadronData.size(); ++i) {
		speed = Math::min(squadronData.get(i).getSpeed(), speed);
	}

	return Math::clamp(0.f, speed, 512.f);
}
