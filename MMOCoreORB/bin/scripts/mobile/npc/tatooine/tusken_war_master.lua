tusken_war_master = Creature:new {
	objectName = "@mob/creature_names:tusken_war_master",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 53,
	chanceHit = 0.53,
	damageMin = 410,
	damageMax = 530,
	baseXp = 5190,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {20,20,0,50,-1,30,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(tusken_war_master, "tusken_war_master")