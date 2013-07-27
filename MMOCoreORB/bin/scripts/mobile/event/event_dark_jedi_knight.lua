event_dark_jedi_knight = Creature:new {
	objectName = "@mob/creature_names:dark_jedi_knight",
	customName = "a Dark Jedi Knight (event)",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 265,
	chanceHit = 235,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 0,
	baseHAM = 261000,
	baseHAMmax = 320000,
	armor = 3,
	resists = {90,90,90,90,90,90,90,90,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_dark_jedi_human_male_01.iff",
		"object/mobile/dressed_dark_jedi_human_female_01.iff"},
	lootGroups = {},
	weapons = {"dark_jedi_weapons_gen3"},
	conversationTemplate = "",
	attacks = merge(lightsabermaster)
}

CreatureTemplates:addCreatureTemplate(event_dark_jedi_knight, "event_dark_jedi_knight")
