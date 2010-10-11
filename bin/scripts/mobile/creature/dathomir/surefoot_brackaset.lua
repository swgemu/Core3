surefoot_brackaset = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:surefoot_brackaset",
	socialGroup = "Brackaset",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.440000,
	damageMin = 340,
	damageMax = 390,
	range = 0,
	baseXp = 4461,
	baseHAM = 11100,
	armor = 0,
	resists = {60,55,60,0,0,-1,-1,80,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 91,
	boneType = "bone_mammal",
	boneAmount = 81,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(surefoot_brackaset, "surefoot_brackaset")
