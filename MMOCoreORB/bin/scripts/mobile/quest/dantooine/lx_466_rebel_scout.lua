lx_466_rebel_scout = Creature:new {
	objectName = "",
	customName = "(a Stranded Rebel Scout)",	
	socialGroup = "rebel",
	faction = "rebel",
	mobType = MOB_NPC,
	level = 50,
	chanceHit = 1,
	damageMin = 330,
	damageMax = 5000,
	baseXp = 4533,
	baseHAM = 12000,
	baseHAMmax = 15000,
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
	creatureBitmask = PACK + STALKER + KILLER,
	optionsBitmask = AIENABLED,	
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
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_weapons_light",
	secondaryWeapon = "unarmed",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(pistoleermaster,marksmanmaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(lx_466_rebel_scout, "lx_466_rebel_scout")
