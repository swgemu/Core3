vile_donkuwah_battlelord = Creature:new {
	objectName = "@mob/creature_names:vile_donkuwah_battlelord",
	socialGroup = "donkuwah_tribe",
	faction = "donkuwah_tribe",
	level = 34,
	chanceHit = 0.42,
	damageMin = 360,
	damageMax = 430,
	baseXp = 3460,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {50,-1,25,50,50,-1,25,-1,-1},
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
				{group = "donkuwah_common", chance = 9000000},
				{group = "wearables_uncommon", chance = 1000000},
			},
			lootChance = 2300000
		}
	},
	weapons = {"donkuwah_weapons"},
	conversationTemplate = "",
	attacks = merge(fencermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(vile_donkuwah_battlelord, "vile_donkuwah_battlelord")
