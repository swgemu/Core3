crackdown_command_security_guard = Creature:new {
	objectName = "@mob/creature_names:crackdown_command_security_guard",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 1,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 40,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(crackdown_command_security_guard, "crackdown_command_security_guard")