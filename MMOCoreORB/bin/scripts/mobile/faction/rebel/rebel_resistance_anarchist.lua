rebel_resistance_anarchist = Creature:new {
	objectName = "@mob/creature_names:rebel_resistance_anarchist",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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

	templates = {
		"object/mobile/selonian_female.iff",
		"object/mobile/selonian_male.iff",
		"object/mobile/bothan_female.iff",
		"object/mobile/bothan_male.iff",
		"object/mobile/aqualish_female.iff",
		"object/mobile/aqualish_male.iff"},
	lootGroups = {
		{
	        groups = {
			{group = "junk", chance = 6000000},
			{group = "rifles", chance = 1000000},
			{group = "pistols", chance = 1000000},
			{group = "melee_weapons", chance = 1000000},
			{group = "carbines", chance = 1000000},
		},
			lootChance = 2700000
		}	
	},
	weapons = {"rebel_weapons_light"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(rebel_resistance_anarchist, "rebel_resistance_anarchist")
