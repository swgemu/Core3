event_dark_jedi_master = Creature:new {
	objectName = "@mob/creature_names:dark_jedi_master",
	customName = "a Dark Jedi Master (event)",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 291,
	chanceHit = 272.5,
	damageMin = 1800,
	damageMax = 3310,
	baseXp = 0,
	baseHAM = 321000,
	baseHAMmax = 392000,
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
	weapons = {"dark_jedi_weapons_gen4"},
	conversationTemplate = "",
	attacks = merge(lightsabermaster,forcepowermaster)
}

CreatureTemplates:addCreatureTemplate(event_dark_jedi_master, "event_dark_jedi_master")
