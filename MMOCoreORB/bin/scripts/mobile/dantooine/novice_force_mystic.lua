novice_force_mystic = Creature:new {
	objectName = "@mob/creature_names:novice_force_mystic",
	socialGroup = "force",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.6,
	damageMin = 475,
	damageMax = 660,
	baseXp = 5830,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {30,30,15,15,5,15,15,15,-1},
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

	templates = {},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "crystals_poor", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "melee_weapons", chance = 1000000},
				{group = "armor_attachments", chance = 1000000},
				{group = "clothing_attachments", chance = 1000000}
			},
			lootChance = 3000000
		}	
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(novice_force_mystic, "novice_force_mystic")
