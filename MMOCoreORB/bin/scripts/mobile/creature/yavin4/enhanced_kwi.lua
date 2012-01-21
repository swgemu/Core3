enhanced_kwi = Creature:new {
	objectName = "@mob/creature_names:geonosian_enhanced_kwi",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 106,
	chanceHit = 1.75,
	damageMin = 690,
	damageMax = 1090,
	baseXp = 10081,
	baseHAM = 30000,
	baseHAMmax = 30000,
	armor = 2,
	resists = {40,40,5,40,5,5,5,5,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0,
	ferocity = 16,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 3000000,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {
		{group = "enhanced_kwi", chance = 10000000}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kwi, "enhanced_kwi")