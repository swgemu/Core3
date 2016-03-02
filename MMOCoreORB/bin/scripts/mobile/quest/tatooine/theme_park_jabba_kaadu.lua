theme_park_jabba_kaadu = Creature:new {
	objectName = "@mob/creature_names:kaadu",
	socialGroup = "mercenary",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 70,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kaadu.iff"},
	lootGroups = {
         {
			groups = {
				{group = "theme_park_loot_petrified_avian_egg", chance = 10000000}
			},
			lootChance = 10000000
		}	
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(theme_park_jabba_kaadu, "theme_park_jabba_kaadu")
