crackdown_imperial_noncom = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_noncom",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 1,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 40,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_medic3_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6500000},
				{group = "rifles", chance = 500000},
				{group = "loot_kit_parts", chance = 1300000},
				{group = "carbines", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000}
			},
			lootChance = 4000000
		}			
	},
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_noncom, "crackdown_imperial_noncom")