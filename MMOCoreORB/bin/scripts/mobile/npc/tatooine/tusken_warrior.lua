tusken_warrior = Creature:new {
	objectName = "@mob/creature_names:tusken_warrior",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 38,
	chanceHit = 0.43,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {45,30,0,30,-1,30,-1,-1,-1},
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
	lootgroups = {},
	weapons = {"tusken_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tusken_warrior, "tusken_warrior")