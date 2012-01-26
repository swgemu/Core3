dageerin = Creature:new {
	objectName = "@mob/creature_names:fs_villager_sad1",
	socialGroup = "Force Sensitive villager",
	pvpFaction = "Force Sensitive villager",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_force_sensitive_renegade.iff"},
	lootgroups = {},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dageerin, "dageerin")