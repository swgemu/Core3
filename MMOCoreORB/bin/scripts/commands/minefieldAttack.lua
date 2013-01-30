--minefieldAttack.lua
--Created on: Dec 21, 2012
--  Author: root

MinefieldAttackCommand = {
    name = "minefieldattack",
	combatSpam = "attack",
	poolsToDamage = RANDOM_ATTRIBUTE,
	areaAction = true,
	maxRange = -1, -- set to -1 so that range defaults to the mine
	range = -1,
	coneAction = false,
	areaRange = -1, -- default to the weapon range
	
}

AddCommand(MinefieldAttackCommand)