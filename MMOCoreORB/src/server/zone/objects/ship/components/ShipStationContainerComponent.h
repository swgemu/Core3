/*
 * ShipStationContainerComponent.h
 *
 * Container component for POB ship stations (pilot chair, operations chair, turret ladder).
 * Overrides transferObject to prevent premature broadcastObject during zone transfers
 * (e.g., hyperspace) where notifyClient is false. The base ContainerComponent always
 * broadcasts for slotted transfers (containmentType >= 4) when objZone is null,
 * regardless of notifyClient — this causes client crashes during hyperspace because
 * the player's create message is sent before the proper load sequence completes.
 */

#ifndef SHIPSTATIONCONTAINERCOMPONENT_H_
#define SHIPSTATIONCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class ShipStationContainerComponent : public ContainerComponent, public Logger {
public:
	ShipStationContainerComponent() {
		setLoggingName("ShipStationContainerComponent");
	}

	bool transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient = false, bool allowOverflow = false, bool notifyRoot = true) const override;
};

#endif /* SHIPSTATIONCONTAINERCOMPONENT_H_ */
