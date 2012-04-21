nightsister_ranger = Creature:new {
	objectName = "@mob/creature_names:nightsister_ranger",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 81,
	chanceHit = 0.75,
	damageMin = 555,
	damageMax = 820,
	baseXp = 7761,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {30,30,30,100,100,100,100,100,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_nightsister_ranger.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_good", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "nightsister_common", chance = 6500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "melee_polearm", chance = 750000},
				{group = "melee_unarmed", chance = 750000}
			},
			lootChance = 5300000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nightsister_ranger, "nightsister_ranger")