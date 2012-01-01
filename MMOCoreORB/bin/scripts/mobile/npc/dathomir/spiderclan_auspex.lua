spiderclan_auspex = Creature:new {
	objectName = "@mob/creature_names:Spiderclan_auspex",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 107,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 10174,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 1,
	resists = {95,100,100,95,100,100,90,75,-1},
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

	templates = {"object/mobile/dressed_dathomir_spider_nightsister_spellweaver.iff"},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(spiderclan_auspex, "spiderclan_auspex")