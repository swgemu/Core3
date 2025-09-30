#include "ShipDockingTask.h"

void ShipDockingTask::run() {
	auto ship = shipRef.get();
	auto target = targetRef.get();

	if (getTimeElapsed() >= DURATION_MAX || !isShipValid(ship) || !isTargetValid(target) || !isDocking(ship) || !isDocking(target)) {
		clearDockingState(ship, target);
		return;
	}

	Locker sLock(ship);
	Locker tLock(target, ship);

	switch (dockingStage) {
		case DockingStage::INITIALIZE: {
			return initializeDocking(ship, target);
		}
		case DockingStage::TRANSFORM: {
			return updateTransform(ship, target);
		}
		case DockingStage::FINALIZE:
		default: {
			return finalizeDocking(ship, target);
		}
	}
}

void ShipDockingTask::initializeDocking(ShipObject* ship, ShipObject* target) {
	sendEffectMessage(ship, "clienteffect/space_command/sys_manipulation.cef");
	sendSystemMessage(ship, "@space/cargo:dock_started");
	setDockingTransform(ship, target);

	if (!checkLineOfSight(ship, target)) {
		sendSystemMessage(ship, "@client:autopilot_obstacle");
		sendSystemMessage(ship, "@space/cargo:dock_abort");
		clearDockingState(ship, target);
		return;
	}

	auto shipTransform = ship->getShipTransform();

	if (shipTransform == nullptr) {
		return;
	}

	shipTransform->initializeTransform(ship);
	shipTransform->setNextTransform(dockTransform, SpaceTransformType::DOCK);

	dockingStage = TRANSFORM;
	reschedule(INTERVAL_INITIALIZE);
}

void ShipDockingTask::updateTransform(ShipObject* ship, ShipObject* target) {
	auto transform = ship->getShipTransform();

	if (transform == nullptr) {
		return;
	}

	interlockStatus = transform->getNextDistance() <= 0.f;

	if (dockingStage == TRANSFORM && !interlockStatus) {
		transform->updateTransform(ship);
		return reschedule(INTERVAL_TRANSFORM);
	}

	sendEffectMessage(ship, "clienteffect/space_command/shp_dock_harddock.cef");
	sendSystemMessage(ship, interlockStatus ? "@space/cargo:dock_achieved" : "@space/cargo:dock_abort");

	dockingStage = FINALIZE;
	reschedule(INTERVAL_FINALIZE);
}

void ShipDockingTask::finalizeDocking(ShipObject* ship, ShipObject* target) {
	sendEffectMessage(ship, "clienteffect/space_command/shp_dock_release.cef");
	sendSystemMessage(ship, "@space/cargo:dock_complete");

	clearDockingState(ship, target);
	notifyObservers(ship, target);
}

void ShipDockingTask::notifyObservers(ShipObject* ship, ShipObject* target) {
/*
	Reference<ShipObject*> shipRef = ship;
	Reference<ShipObject*> targetRef = target;

	Core::getTaskManager()->scheduleTask([shipRef, targetRef] () {
		if (shipRef == nullptr || targetRef == nullptr)
			return;

		Locker lock(shipRef);
		Locker clocker(targetRef, shipRef);

		targetRef->notifyObservers(ObserverEventType::SHIPDOCKED, shipRef);
	}, "notifyShipDockedLambda", 200);
*/
}

void ShipDockingTask::sendSystemMessage(ShipObject* ship, const String& message) {
	ship->sendShipMembersMessage(message);
}

void ShipDockingTask::sendEffectMessage(ShipObject* ship, const String& effect) {
	const auto& position = ship->getPosition();
	ship->broadcastMessage(new PlayClientEffectLoc(effect, "", position.getX(), position.getZ(), position.getY()), true);
}

