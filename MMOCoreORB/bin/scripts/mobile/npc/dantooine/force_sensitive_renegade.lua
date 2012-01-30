force_sensitive_renegade = Creature:new {
	objectName = "@mob/creature_names:force_sensitive_renegade",
	socialGroup = "Force Regen.",
	pvpFaction = "",
	faction = "",
	level = 80,
	chanceHit = 0.8,
	damageMin = 585,
	damageMax = 880,
	baseXp = 7668,
	baseHAM = 12000,
	baseHAMmax = 15000,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_force_sensitive_renegade.iff"},
	lootGroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(force_sensitive_renegade, "force_sensitive_renegade")