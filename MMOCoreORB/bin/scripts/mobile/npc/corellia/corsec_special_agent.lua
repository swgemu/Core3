corsec_special_agent = Creature:new {
	objectName = "@mob/creature_names:corsec_agent_aggro",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 105,
	chanceHit = 1.75,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 9987,
	baseHAM = 29000,
	baseHAMmax = 36000,
	armor = 2,
	resists = {45,45,30,5,80,30,5,35,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_corsec_captain_human_female_01.iff"},
	lootGroups = {},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corsec_special_agent, "corsec_special_agent")