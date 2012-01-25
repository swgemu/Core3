governor_grayed_wintozzen = Creature:new {
	objectName = "",
	customName = "Governor Grayed Wintozzen",
	socialGroup = "Townsperson",
	pvpFaction = "Townsperson",
	faction = "",
	level = 5,
	chanceHit = 0.250000,
	damageMin = 45,
	damageMax = 55,
	baseXp = 150,
	baseHAM = 250,
	baseHAMmax = 300,
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

	templates = {"object/mobile/dressed_imperial_moff_m.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "imperial_retreat_governor_grayed_wintozzen_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(governor_grayed_wintozzen, "governor_grayed_wintozzen")