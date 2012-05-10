izaryx = Creature:new {
	objectName = "",
	customName = "Izaryx",
	socialGroup = "mtn_clan",
	pvpFaction = "mtn_clan",
	faction = "mtn_clan",
	level = 100,
	chanceHit = 1,
	damageMin = 0,
	damageMax = 0,
	baseXp = 0,
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_izaryx.iff"},
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(izaryx, "izaryx")