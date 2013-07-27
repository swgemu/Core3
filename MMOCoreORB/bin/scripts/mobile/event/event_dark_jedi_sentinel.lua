event_dark_jedi_sentinel = Creature:new {
	objectName = "@mob/creature_names:dark_jedi_sentinel",
	customName = "a Dark Jedi Sentinel (event)",
	socialGroup = "self",
	pvpFaction = "self",
	faction = "",
	level = 300,
	chanceHit = 300,
	damageMin = 2645,
	damageMax = 5000,
	baseXp = 0,
	baseHAM = 1106000,
	baseHAMmax = 1352000,
	armor = 3,
	resists = {95,95,95,95,95,95,95,95,-1},
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
	creatureBitmask = PACK + HERD + KILLER + STALKER,
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

CreatureTemplates:addCreatureTemplate(event_dark_jedi_sentinel, "event_dark_jedi_sentinel")
