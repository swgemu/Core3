beguiling_donkuwah_scout = Creature:new {
	objectName = "@mob/creature_names:beguiling_donkuwah_scout",
	socialGroup = "donkuwah_tribe",
	pvpFaction = "donkuwah_tribe",
	faction = "donkuwah_tribe",
	level = 18,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 4100,
	baseHAMmax = 5000,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "donkuwah_common", chance = 3300000}
			},
			lootChance = 7000000
		}
	},
	weapons = {"donkuwah_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster)
}

CreatureTemplates:addCreatureTemplate(beguiling_donkuwah_scout, "beguiling_donkuwah_scout")
