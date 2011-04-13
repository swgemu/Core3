proficient_jinda_worker = Creature:new {
	objectName = "@mob/creature_names:proficient_jinda_worker",
	socialGroup = "Jinda Tribe",
	pvpFaction = "Jinda Tribe",
	faction = "",
	level = 28,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2822,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {35,35,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(proficient_jinda_worker, "proficient_jinda_worker")