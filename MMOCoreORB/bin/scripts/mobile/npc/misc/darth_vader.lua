darth_vader = Creature:new {
	objectName = "@mob/creature_names:darth_vader",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 300,
	chanceHit = 30,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 28549,
	baseHAM = 385000,
	baseHAMmax = 471000,
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
	pvpBitmask = ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/darth_vader.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(darth_vader, "darth_vader")