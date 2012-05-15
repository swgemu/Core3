forsaken_force_drifter = Creature:new {
	objectName = "@mob/creature_names:forsaken_force_drifter",
	socialGroup = "force",
	pvpFaction = "",
	faction = "",
	level = 80,
	chanceHit = 0.8,
	damageMin = 625,
	damageMax = 960,
	baseXp = 7668,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {35,35,35,35,35,35,35,35,-1},
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

	templates = {"object/mobile/dressed_forsaken_force_drifter.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_quality", chance = 900000},
				{group = "color_crystals", chance = 950000},
				{group = "melee_weapons", chance = 2500000},
				{group = "armor_attachments", chance = 2750000},
				{group = "holocron_light", chance = 150000},
				{group = "clothing_attachments", chance = 2750000}
			},
			lootChance = 4800000	
		}	
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(forsaken_force_drifter, "forsaken_force_drifter")