tusken_chief = Creature:new {
	objectName = "@mob/creature_names:tusken_chief",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 43,
	chanceHit = 0.46,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4279,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {45,0,0,60,-1,40,-1,-1,-1},
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

CreatureTemplates:addCreatureTemplate(tusken_chief, "tusken_chief")