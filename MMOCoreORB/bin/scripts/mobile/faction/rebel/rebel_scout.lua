rebel_scout = Creature:new {
	objectName = "@mob/creature_names:rebel_scout",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 4000,
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
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_scout_bothan_male_01.iff",
		"object/mobile/dressed_rebel_scout_human_female_01.iff",
		"object/mobile/dressed_rebel_scout_human_female_02.iff",
		"object/mobile/dressed_rebel_scout_human_male_01.iff",
		"object/mobile/dressed_rebel_scout_rodian_male_01.iff",
		"object/mobile/dressed_rebel_scout_zabrak_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_light"},
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(rebel_scout, "rebel_scout")
