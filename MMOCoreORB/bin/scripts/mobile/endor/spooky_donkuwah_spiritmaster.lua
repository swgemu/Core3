spooky_donkuwah_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:spooky_donkuwah_spiritmaster",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "donkuwah_tribe",
	faction = "donkuwah_tribe",
	level = 26,
	chanceHit = 0.36,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {25,15,0,50,50,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(spooky_donkuwah_spiritmaster, "spooky_donkuwah_spiritmaster")
