nightsister_spell_weaver = Creature:new {
	objectName = "@mob/creature_names:nightsister_spell_weaver",
	socialGroup = "nightsister",
	pvpFaction = "nightsister",
	faction = "nightsister",
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_nightsister_spellweaver.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_quality", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "nightsister_common", chance = 6500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "pistols", chance = 750000},
				{group = "rifles", chance = 750000}
			},
			lootChance = 5700000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_spell_weaver, "nightsister_spell_weaver")