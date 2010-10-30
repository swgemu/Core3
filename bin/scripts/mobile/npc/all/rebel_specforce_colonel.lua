rebel_specforce_colonel = Creature:new {
	objectName = "@mob/creature_names:rebel_specforce_colonel",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 27,
	chanceHit = 0.370000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2822,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,0,-1,0,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rebel_specforce_colonel, "rebel_specforce_colonel")