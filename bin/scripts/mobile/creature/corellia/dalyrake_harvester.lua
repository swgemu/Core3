dalyrake_harvester = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:dalyrake_harvester",
	socialGroup = "Dalyrake",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	range = 0,
	baseXp = 831,
	baseHAM = 2700,
	armor = 0,
	resists = {10,10,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 25,
	hideType = "hide_scale",
	hideAmount = 45,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dalyrake_harvester, "dalyrake_harvester")
