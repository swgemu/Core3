triggo_binz = Creature:new {
	objectName = "@mob/creature_names:thug",
	socialGroup = "thug",
	pvpFaction = "thug",
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
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_organized_twilek_male_01.iff"},
	lootGroups = {
		{
	        groups = {
			{group = "junk", chance = 6000000},
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

CreatureTemplates:addCreatureTemplate(triggo_binz, "triggo_binz")
