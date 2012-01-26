corsec_special_ops_major = Creature:new {
	objectName = "@mob/creature_names:corsec_major_aggro",
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
	armor = 2,
	resists = {65,65,30,40,80,30,40,35,-1},
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

	templates = {"object/mobile/dressed_corsec_captain_human_female_01.iff"},
	lootgroups = {},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corsec_special_ops_major, "corsec_special_ops_major")