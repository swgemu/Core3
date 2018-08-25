phy_hudgen = Creature:new {
	objectName = "@theme_park/warren/warren_system_messages:name_phy",
	socialGroup = "",
	faction = "",
	level = 23,
	chanceHit = 1,
	damageMin = 123,
	damageMax = 254,
	baseXp = 2300,
	baseHAM = 3400,
	baseHAMmax = 4300,
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/warren_phy_hudgen.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "phyHudgenConvoTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(phy_hudgen, "phy_hudgen")