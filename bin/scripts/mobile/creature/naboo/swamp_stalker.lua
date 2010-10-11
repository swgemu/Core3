swamp_stalker = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:swamp_stalker",
	socialGroup = "Swamp Tusk Cat",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	range = 0,
	baseXp = 3279,
	baseHAM = 9300,
	armor = 0,
	resists = {35,0,0,70,0,0,60,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.200000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swamp_stalker, "swamp_stalker")
