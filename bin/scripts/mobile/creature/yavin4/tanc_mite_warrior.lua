tanc_mite_warrior = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:tanc_mite_warrior",
	socialGroup = "Tancmite",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	range = 25,
	baseXp = 1102,
	baseHAM = 3200,
	armor = 0,
	resists = {0,15,-1,0,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tanc_mite_warrior, "tanc_mite_warrior")
