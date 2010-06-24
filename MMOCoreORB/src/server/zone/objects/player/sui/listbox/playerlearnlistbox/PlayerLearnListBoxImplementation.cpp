/*
 * PlayerLearnListBoxImplementation.cpp
 *
 *  Created on: 6/22/2010
 *      Author: thoop
 *
 *      Extended just to add some needed storage variables onto the SuiListBox
 */

#include "PlayerLearnListBox.h"
#include "server/zone/objects/creature/professions/SkillBox.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/group/GroupObject.h"

void PlayerLearnListBoxImplementation::init() {
	setPromptTitle("@sui:teach");
	setPromptText("What would you like to teach?");
	setCancelButton(true, "");
}
