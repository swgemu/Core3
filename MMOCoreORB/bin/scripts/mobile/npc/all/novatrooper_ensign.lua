novatrooper_ensign = Creature:new {
	objectName = "@mob/creature_names:Novatrooper Ensign",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 87,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8315,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {40,35,80,30,0,0,30,45,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_captain_black_gold.iff"},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(novatrooper_ensign, "novatrooper_ensign")