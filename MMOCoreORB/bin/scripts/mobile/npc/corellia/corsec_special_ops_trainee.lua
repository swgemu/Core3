corsec_special_ops_trainee = Creature:new {
	objectName = "@mob/creature_names:CorSec_Special_Ops_Trainee",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 71,
	chanceHit = 0.7,
	damageMin = 495,
	damageMax = 700,
	baseXp = 6839,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {35,35,30,0,80,30,0,35,-1},
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_trainee, "corsec_special_ops_trainee")