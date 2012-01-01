disciple_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:disciple_of_Lord_Nyax",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,15,0,0,-1,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(disciple_of_lord_nyax, "disciple_of_lord_nyax")