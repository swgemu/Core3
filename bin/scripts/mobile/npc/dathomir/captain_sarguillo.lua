captain_sarguillo = Creature:new {
	objectName = "Captain Sarguillo",
	socialGroup = "Force Sensitive villager",
	pvpFaction = "Force Sensitive villager",
	faction = "",
	level = 69,
	chanceHit = 0.600000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 6655,
	baseHAM = 11000,
	baseHAMmax = 13500,
	armor = 0,
	resists = {60,60,60,60,60,60,60,60,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(captain_sarguillo, "captain_sarguillo")