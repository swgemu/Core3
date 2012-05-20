geonosian_worker = Creature:new {
	objectName = "@mob/creature_names:geonosian_worker",
	socialGroup = "geonosian",
	pvpFaction = "geonosian",
	faction = "",
	level = 44,
	chanceHit = 0.46,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4279,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {25,25,-1,65,0,25,-1,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_geonosian_commoner_01.iff",
		"object/mobile/dressed_geonosian_commoner_02.iff"},
	lootGroups = {
	},
	weapons = {"geonosian_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(geonosian_worker, "geonosian_worker")