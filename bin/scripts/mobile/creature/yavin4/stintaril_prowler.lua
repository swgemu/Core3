stintaril_prowler = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:stintaril_prowler",
	socialGroup = "Stinaril",
	pvpFaction = "",
	faction = "",
	level = 83,
	chanceHit = 0.850000,
	damageMin = 595,
	damageMax = 900,
	range = 25,
	baseXp = 7945,
	baseHAM = 13500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 9,
	hideType = "hide_bristley",
	hideAmount = 7,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stintaril_prowler, "stintaril_prowler")
