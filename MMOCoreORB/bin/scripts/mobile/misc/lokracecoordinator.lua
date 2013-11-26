lok_race_coordinator = Creature:new {
	objectName = "@event_perk:name_race_droid",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {"object/mobile/3po_protocol_droid.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "lok_conversationtemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lok_race_coordinator, "lok_race_coordinator")
