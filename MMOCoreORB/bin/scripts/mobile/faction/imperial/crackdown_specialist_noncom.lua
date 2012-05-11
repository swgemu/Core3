crackdown_specialist_noncom = Creature:new {
	objectName = "@mob/creature_names:crackdown_specialist_noncom",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 1,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 40,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_medic3_human_male_01.iff",
				"object/mobile/dressed_imperial_officer_m_2.iff"
				},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 2000000},
				{group = "pistols", chance = 2000000},
				{group = "clothing_attachments", chance = 1100000},
				{group = "armor_attachments", chance = 1100000}
			},
			lootChance = 4000000
		}		
	},
	weapons = {"imperial_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(crackdown_specialist_noncom, "crackdown_specialist_noncom")