tough_thug_male_rodian = Creature:new {
	objectName = "@mob/creature_names:thug",
	socialGroup = "Thug",
	pvpFaction = "Thug",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 2900,
	baseHAMmax = 3500,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_cobral_thug_rodian_male_01.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tough_thug_male_rodian, "tough_thug_male_rodian")