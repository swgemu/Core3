bh_untrained_wielder_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:untrained_wielder_of_the_dark_side",
	socialGroup = "kun",
	pvpFaction = "",
	faction = "",
	level = 65,
	chanceHit = 0.6,
	damageMin = 545,
	damageMax = 800,
	baseXp = 6288,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {40,40,25,25,25,25,25,25,-1},
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

	templates = {"object/mobile/dressed_untrained_wielder_of_the_darkside.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "crystals_poor", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "holocron_dark", chance = 500000},
				{group = "holocron_light", chance = 500000},
				{group = "melee_weapons", chance = 1000000},
				{group = "armor_attachments", chance = 1000000},
				{group = "clothing_attachments", chance = 1000000},
				{group = "wearables_common", chance = 500000},
				{group = "wearables_uncommon", chance = 500000}
			},
			lootChance = 3000000
		},
		{
			groups = {
				{group = "crystals_poor", chance = 1500000},
				{group = "crystals_quality", chance = 500000},
				{group = "crystals_okay", chance = 500000},
				{group = "color_crystals", chance = 2500000},
				{group = "melee_weapons", chance = 2000000},
				{group = "armor_attachments", chance = 1500000},
				{group = "clothing_attachments", chance = 1500000}
			},
			lootChance = 6000000
		}			
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(pikemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(bh_untrained_wielder_of_the_dark_side, "bh_untrained_wielder_of_the_dark_side")
