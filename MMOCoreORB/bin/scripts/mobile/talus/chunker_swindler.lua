chunker_swindler = Creature:new {
	objectName = "@mob/creature_names:chunker_swindler",
	socialGroup = "chunker",
	faction = "thug",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
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
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_rodian_female_01.iff",
			"object/mobile/dressed_crook_zabrak_female_01.iff",
			"object/mobile/dressed_criminal_thug_aqualish_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 1200000},
				{group = "rifles", chance = 700000},
				{group = "melee_knife", chance = 700000},
				{group = "pistols", chance = 700000},
				{group = "carbines", chance = 700000},
				{group = "chunker_common", chance = 6000000},
			},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_light"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(chunker_swindler, "chunker_swindler")
