hardened_gondula_warrior = Creature:new {
	objectName = "@mob/creature_names:hardened_gondula_warrior",
	socialGroup = "Gondula Tribe",
	pvpFaction = "Gondula Tribe",
	faction = "",
	level = 53,
	chanceHit = 0.530000,
	damageMin = 410,
	damageMax = 530,
	baseXp = 5190,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {30,30,0,0,0,0,-1,0,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"ewok_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(hardened_gondula_warrior, "hardened_gondula_warrior")