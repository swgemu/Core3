ferocious_kusak = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:ferocious_kusak",
	socialGroup = "Kusak",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	range = 0,
	baseXp = 2006,
	baseHAM = 4550,
	armor = 0,
	resists = {30,0,0,-1,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 21,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ferocious_kusak, "ferocious_kusak")
