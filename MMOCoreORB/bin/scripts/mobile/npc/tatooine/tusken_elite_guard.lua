tusken_elite_guard = Creature:new {
	objectName = "@mob/creature_names:tusken_elite_guard",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 44,
	chanceHit = 0.46,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4370,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(tusken_elite_guard, "tusken_elite_guard")