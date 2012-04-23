force_crystal_hunter = Creature:new {
	objectName = "@mob/creature_names:dark_force_crystal_hunter",
	socialGroup = "Remn. Of Kun",
	pvpFaction = "",
	faction = "",
	level = 115,
	chanceHit = 1,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 10921,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 2,
	resists = {80,80,80,80,80,80,80,80,-1},
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

	templates = {"object/mobile/dressed_dark_force_crystal_hunter.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_quality", chance = 900000},
				{group = "color_crystals", chance = 950000},
				{group = "melee_weapons", chance = 2500000},
				{group = "armor_attachments", chance = 2750000},
				{group = "holocron_dark", chance = 150000},
				{group = "clothing_attachments", chance = 2750000}
			},
			lootChance = 4800000
		}			
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(force_crystal_hunter, "force_crystal_hunter")