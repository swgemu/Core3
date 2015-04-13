donkuwah_cub = Creature:new {
	objectName = "@mob/creature_names:donkuwah_cub",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "donkuwah_tribe",
	faction = "donkuwah_tribe",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dulok_male.iff",
		"object/mobile/dulok_female.iff"},
	lootGroups = {
		{
			groups = {
				{group = "donkuwah_common", chance = 10000000}
			},
			lootChance = 2300000
		}
	},
	weapons = {"donkuwah_weapons"},
	conversationTemplate = "",
	attacks = brawlermid
}

CreatureTemplates:addCreatureTemplate(donkuwah_cub, "donkuwah_cub")
