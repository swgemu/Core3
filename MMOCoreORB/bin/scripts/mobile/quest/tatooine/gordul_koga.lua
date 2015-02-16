gordul_koga = Creature:new {
	objectName = "",
	socialGroup = "thug",
	faction = "thug",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_aqualish_male_01.iff"},
	lootGroups = {
		{
	        groups = {
			{group = "junk", chance = 4000000},
			{group = "wearables_common", chance = 2000000},			
			{group = "rifles", chance = 1000000},
			{group = "pistols", chance = 1000000},
			{group = "melee_weapons", chance = 1000000},
			{group = "carbines", chance = 1000000},
		},
			lootChance = 2600000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(gordul_koga, "gordul_koga")
