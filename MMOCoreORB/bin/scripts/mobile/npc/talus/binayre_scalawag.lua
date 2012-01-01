binayre_scalawag = Creature:new {
	objectName = "@mob/creature_names:binayre_scalawag",
	socialGroup = "Binayre",
	pvpFaction = "Binayre",
	faction = "",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 430,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_binayre_scalawag_twk_female_01.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(binayre_scalawag, "binayre_scalawag")