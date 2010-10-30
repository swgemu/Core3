tusken_raid_leader = Creature:new {
	objectName = "@mob/creature_names:tusken_raid_leader",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 49,
	chanceHit = 0.490000,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4825,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {35,25,0,60,-1,30,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"tusken_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tusken_raid_leader, "tusken_raid_leader")