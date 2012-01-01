corsec_special_ops_major = Creature:new {
	objectName = "@mob/creature_names:CorSec_Special_Ops_Major",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 181,
	chanceHit = 13,
	damageMin = 1045,
	damageMax = 1800,
	baseXp = 17178,
	baseHAM = 126000,
	baseHAMmax = 154000,
	armor = 0,
	resists = {65,65,30,0,80,30,0,35,-1},
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

	templates = {},
	lootgroups = {},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corsec_special_ops_major, "corsec_special_ops_major")