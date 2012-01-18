nightsister_spell_weaver = Creature:new {
	objectName = "@mob/creature_names:nightsister_spell_weaver",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 107,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 10174,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 2,
	resists = {25,100,25,100,100,100,100,100,-1},
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
	lootChance = 5700000,

	templates = {"object/mobile/dressed_dathomir_spider_nightsister_spellweaver.iff"},
	lootgroups = {
		{group = "nightsister_crystals_3", chance = 1000000},
		{group = "nightsister_common", chance = 7500000},
		{group = "pistols", chance = 750000},
		{group = "rifles", chance = 750000}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_spell_weaver, "nightsister_spell_weaver")