#include "server/zone/objects/ship/ShipObject.h"
#include "ShipSquadronData.h"

ShipSquadronData::ShipSquadronData(ShipObject* ship) : Object() {
	formationRadius = ShipSquadronFormation::NONE;
	formationType = ShipSquadronFormation::NONE;
}

ShipSquadronData::~ShipSquadronData() {
	squadronData.removeAll();
}

void ShipSquadronData::add(ShipObject* ship) {
	if (ship == nullptr) {
		return;
	}

	squadronData.add(ShipSquadronDataEntry());
}

void ShipSquadronData::remove(int index) {
	if (squadronData.size() > index) {
		squadronData.remove(index);
	}
}

void ShipSquadronData::setFormation(int index, float radius) {
	float distance = radius * AUTO_RADIUS_MODIFIER;

	if (formationRadius > 0.f) {
		distance = Math::max(formationRadius / (float)squadronData.size(), distance);
	}

#ifdef DEBUG_SQUADRONS
	info(true) << "ShipSquadronData:" << __FUNCTION__ << "() -- Index: " << index << " radius: " << radius << " distance: " << distance << " formationRadius: " << formationRadius;
#endif // DEBUG_SQUADRONS

	auto formation = ShipSquadronFormation::getPosition(formationType, index, distance, squadronData.size());
	setFormation(index, formation);
}

void ShipSquadronData::setFormation(int index, const Vector3& position) {
	if (squadronData.size() > index) {
		squadronData.get(index).setFormation(position);
	}
}

void ShipSquadronData::setPosition(int index, const Vector3& position) {
	if (squadronData.size() > index) {
		squadronData.get(index).setPosition(position);
	}
}

void ShipSquadronData::setSpeed(int index, float speed) {
	if (squadronData.size() > index) {
		squadronData.get(index).setSpeed(speed);
	}
}

Vector3 ShipSquadronData::getFormation(int index) const {
	return squadronData.size() > index ? squadronData.get(index).getFormation() : Vector3::ZERO;
}

Vector3 ShipSquadronData::getPosition(int index) const {
	return squadronData.size() > index ? squadronData.get(index).getPosition() : Vector3::ZERO;
}

float ShipSquadronData::getSpeed(int index) const {
	return squadronData.size() > index ? squadronData.get(index).getSpeed() : 0.f;
}

float ShipSquadronData::getFormationSpeed() const {
	float speed = FLT_MAX;

	for (int i = 1; i < squadronData.size(); ++i) {
		speed = Math::min(squadronData.get(i).getSpeed(), speed);
	}

	return Math::clamp(0.f, speed, 512.f);
}
