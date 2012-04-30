force_trained_archaist = Creature:new {
	objectName = "@mob/creature_names:force_trained_archaist",
	socialGroup = "Force Regen.",
	pvpFaction = "",
	faction = "",
	level = 90,
	chanceHit = 0.9,
	damageMin = 640,
	damageMax = 990,
	baseXp = 8593,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 2,
	resists = {45,45,0,0,0,0,0,0,-1},
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

	templates = {"object/mobile/dressed_force_trained_archaist.iff"},
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
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(force_trained_archaist, "force_trained_archaist")