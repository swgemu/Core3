/*
 * BountyHunterDroidMenuComponent.h
 *
 *  Created on: 01/19/2012
 *      Author: loshult
 */

#ifndef BOUNTYHUNTERDROIDMENUCOMPONENT_H_
#define BOUNTYHUNTERDROIDMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/mission/MissionObject.h"

class BountyHunterDroidMenuComponent : public TangibleObjectMenuComponent {
public:

	/**
	 * Fills the radial options, needs to be overriden
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

	/**
	 * Handles the radial selection sent by the client, must be overriden by inherited objects
	 * @pre { this object is locked, player is locked }
	 * @post { this object is locked, player is locked }
	 * @param player PlayerCreature that selected the option
	 * @param selectedID selected menu id
	 * @returns 0 if successfull
	 */
	virtual int handleObjectMenuSelect(SceneObject* droidObject, CreatureObject* player, byte selectedID) const;

private:
	/**
	 * Checks if the player has the skill to use the track feature.
	 * @param player the player to check.
	 * @return true if the player got the required skill.
	 */
	bool playerCanUseTrack(CreatureObject* player) const;

	/**
	 * Checks if the player has the skill to use a bounty hunter droid.
	 * @param player the player to check.
	 * @return true if the player got the required skill.
	 */
	bool playerCanUseDroids(CreatureObject* player) const;

	/**
	 * Checks if the object is a probe droid.
	 * @param droidObject the object to check.
	 * @return true if it is a probe droid.
	 */
	bool isProbeDroid(SceneObject* droidObject) const;

	/**
	 * Checks if the object is a seeker droid.
	 * @param droidObject the object to check.
	 * @return true if it is a seeker droid.
	 */
	bool isSeekerDroid(SceneObject* droidObject) const;

	/**
	 * Checks if the scene object is in the inventory of the player.
	 * @param droidObject the object to check.
	 * @param player the player creature to check in.
	 * @return true if the object is found in the inventory of the player.
	 */
	bool droidIsInPlayerInventory(SceneObject* droidObject, CreatureObject* player) const;

	/**
	 * Checks if the object is in a zone.
	 * @param droidObject the object to check.
	 * @return true if it is in the Zone.
	 */
	bool droidIsInZone(SceneObject* droidObject) const;

	/**
	 * Checks if the player owns the droid.
	 * @param droidObject the droid.
	 * @param player the player.
	 * @return true if the player owns the droid.
	 */
	bool playerOwnsTheDroid(SceneObject* droidObject, CreatureObject* player) const;

	/**
	 * Perform the droid action selected in the radial menu.
	 * @param action the action to perform.
	 * @param droidObject the droid.
	 * @param player the player that performs the action on the droid.
	 */
	void performDroidAction(int action, SceneObject* droidObject, CreatureObject* player) const;

	/**
	 * Returns a bounty hunter mission object if the player has one.
	 * @param player the player.
	 * @return bounty hunter mission object if the player has one otherwise NULL.
	 */
	MissionObject* getBountyHunterMission(CreatureObject* player) const;
};

#endif /* BOUNTYHUNTERDROIDMENUCOMPONENT_H_ */
