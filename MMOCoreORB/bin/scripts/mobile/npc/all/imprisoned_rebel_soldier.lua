imprisoned_rebel_soldier = Creature:new {
	objectName = "@mob/creature_names:imprisoned_rebel",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_scout_human_male_01.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imprisoned_rebel_soldier, "imprisoned_rebel_soldier")