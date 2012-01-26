corsec_special_ops_inspector = Creature:new {
	objectName = "@mob/creature_names:corsec_inspector_sergeant_aggro",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 150,
	chanceHit = 8.5,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14219,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {55,55,30,0,80,30,0,35,-1},
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_inspector, "corsec_special_ops_inspector")