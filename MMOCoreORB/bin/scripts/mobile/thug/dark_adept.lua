dark_adept = Creature:new {
	objectName = "@mob/creature_names:dark_adept",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 140,
	chanceHit = 47.5,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 13178,
	baseHAM = 50000,
	baseHAMmax = 61000,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "holocron_dark", chance = 400000},
				{group = "holocron_light", chance = 400000},
				{group = "crystals_premium", chance = 400000},
				{group = "color_crystals", chance = 1000000},
				{group = "rifles", chance = 1500000},
				{group = "pistols", chance = 1500000},
				{group = "melee_weapons", chance = 1500000},
				{group = "armor_attachments", chance = 900000},
				{group = "clothing_attachments", chance = 900000},
				{group = "carbines", chance = 1500000}				
			},
			lootChance = 5500000
		}
	},
	weapons = {"dark_jedi_weapons_gen2"},
	conversationTemplate = "",
	attacks = merge(lightsabermaster)
}

CreatureTemplates:addCreatureTemplate(dark_adept, "dark_adept")