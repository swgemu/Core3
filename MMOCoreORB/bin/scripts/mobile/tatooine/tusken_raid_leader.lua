tusken_raid_leader = Creature:new {
	objectName = "@mob/creature_names:tusken_raid_leader",
	socialGroup = "tusken_raider",
	pvpFaction = "tusken_raider",
	faction = "tusken_raider",
	level = 49,
	chanceHit = 0.49,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/tusken_raider.iff"},
	lootGroups = {},
	weapons = {"tusken_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tusken_raid_leader, "tusken_raid_leader")
