mat_rags_greater_desert_womp_rat = Creature:new {
	objectName = "@mob/creature_names:greater_desert_womprat",
	socialGroup = "rat",
	faction = "",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,10,35,30,10,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_desert_womp_rat.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "task_loot_womp_rat_hide", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mat_rags_greater_desert_womp_rat, "mat_rags_greater_desert_womp_rat")
