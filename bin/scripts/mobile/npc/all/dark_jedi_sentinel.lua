dark_jedi_sentinel = Creature:new {
	objectName = "@mob/creature_names:dark_jedi_sentinel",
	socialGroup = "self",
	pvpFaction = "self",
	faction = "",
	level = 1,
	chanceHit = 30.000000,
	damageMin = 2645,
	damageMax = 5000,
	baseXp = 45,
	baseHAM = 1106000,
	baseHAMmax = 1352000,
	armor = 0,
	resists = {95,95,95,95,95,95,95,95,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"dark_jedi_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(dark_jedi_sentinel, "dark_jedi_sentinel")