draya_korbinari_smuggler = Creature:new {
	objectName = "@mob/creature_names:smuggler",
	customName = "",
	socialGroup = "",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_kobola_smuggler_trandoshan_male_01.iff"},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	lootGroups = {
		{
			groups = {
				{ group = "task_loot_draya_korbinari_art_holo", chance = 10000000},			},
 			lootChance = 10000000
		},
	},
	outfit = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(draya_korbinari_smuggler, "draya_korbinari_smuggler")
