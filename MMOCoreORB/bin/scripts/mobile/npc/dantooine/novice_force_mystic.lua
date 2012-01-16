novice_force_mystic = Creature:new {
	objectName = "@mob/creature_names:novice_force_mystic",
	socialGroup = "Force Reneg.",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.6,
	damageMin = 475,
	damageMax = 660,
	baseXp = 5830,
	baseHAM = 1100,
	baseHAMmax = 1300,
	armor = 1,
	resists = {30,30,15,15,5,15,15,15,-1},
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

	templates = {},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(novice_force_mystic, "novice_force_mystic")