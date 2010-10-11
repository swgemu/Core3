stintaril_fleshripper = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:stintaril_fleshstripper",
	socialGroup = "Stinaril",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 150,
	damageMax = 160,
	range = 0,
	baseXp = 960,
	baseHAM = 3900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stintaril_fleshripper, "stintaril_fleshripper")
