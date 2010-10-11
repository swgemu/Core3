prowling_gurreck = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:gurreck_prowler",
	socialGroup = "Gurreck",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 365,
	damageMax = 440,
	range = 0,
	baseXp = 4370,
	baseHAM = 9900,
	armor = 0,
	resists = {65,65,0,0,-1,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(prowling_gurreck, "prowling_gurreck")
