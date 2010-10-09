bark_mite_burrower_collector = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:bark_mite_burrower_collector",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 36,
	chanceHit = 0.400000,
	damageMin = 335,
	damageMax = 380,
	range = 0,
	baseXp = 3551,
	baseHAM = 9600,
	armor = 0,
	resists = {0,40,-1,70,-1,65,70,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scale",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.200000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_collector, "bark_mite_burrower_collector")
