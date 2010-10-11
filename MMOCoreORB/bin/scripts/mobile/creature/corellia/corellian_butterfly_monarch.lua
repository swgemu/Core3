corellian_butterfly_monarch = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "corellian butterfly monarch",
	socialGroup = "Cor. Butterfly",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 200,
	damageMax = 210,
	range = 0,
	baseXp = 1803,
	baseHAM = 5000,
	armor = 0,
	resists = {-1,25,-1,0,0,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 27,
	hideType = "hide_scale",
	hideAmount = 27,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_monarch, "corellian_butterfly_monarch")
