spiderclan_protector = Creature:new {
	objectName = "@mob/creature_names:spider_nightsister_protector",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 131,
	chanceHit = 4.75,
	damageMin = 770,
	damageMax = 1250,
	baseXp = 12424,
	baseHAM = 50000,
	baseHAMmax = 61000,
	armor = 2,
	resists = {45,95,100,65,100,100,55,100,-1},
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

	templates = {"object/mobile/dressed_dathomir_spider_nightsister_protector.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_select", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "melee_weapons", chance = 2500000},
				{group = "armor_attachments", chance = 550000},
				{group = "clothing_attachments", chance = 550000},
				{group = "pistols", chance = 2750000},
				{group = "rifles", chance = 2750000}
			},
			lootChance = 4800000
		}			
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(spiderclan_protector, "spiderclan_protector")