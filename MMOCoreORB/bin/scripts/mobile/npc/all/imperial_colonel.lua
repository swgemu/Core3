imperial_colonel = Creature:new {
	objectName = "@mob/creature_names:imperial_colonel",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2443,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {15,15,0,0,0,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_colonel_m.iff"},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_colonel, "imperial_colonel")