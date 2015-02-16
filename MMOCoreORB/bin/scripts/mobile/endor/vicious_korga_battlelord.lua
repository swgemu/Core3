vicious_korga_battlelord = Creature:new {
	objectName = "@mob/creature_names:vicious_korga_battlelord",
	socialGroup = "korga_tribe",
	faction = "korga_tribe",
	level = 48,
	chanceHit = 0.49,
	damageMin = 410,
	damageMax = 530,
	baseXp = 4734,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {25,10,0,50,50,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "ewok", chance = 9000000},
				{group = "wearables_all", chance = 1000000},
			},
			lootChance = 2300000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(vicious_korga_battlelord, "vicious_korga_battlelord")
