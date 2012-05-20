rorgungan_scout = Creature:new {
	objectName = "@mob/creature_names:rorgungan_scout",
	socialGroup = "rorgungan",
	pvpFaction = "rorgungan",
	faction = "rorgungan",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 514,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,15,0,0,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/gungan_s04_male.iff"},
	
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "color_crystals", chance = 200000},
				{group = "crystals_poor", chance = 200000}
			},
			lootChance = 3200000
		}					
	},
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rorgungan_scout, "rorgungan_scout")