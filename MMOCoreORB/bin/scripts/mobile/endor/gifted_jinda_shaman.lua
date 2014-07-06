gifted_jinda_shaman = Creature:new {
	objectName = "@mob/creature_names:gifted_jinda_shaman",
	socialGroup = "jinda_tribe",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {30,30,0,-1,0,0,-1,0,-1},
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
	creatureBitmask = PACK + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/jinda_male.iff",
			"object/mobile/jinda_male_01.iff",
			"object/mobile/jinda_female.iff",
			"object/mobile/jinda_female_01.iff"},
	lootGroups = {
		{
	        groups = {
				{group = "ewok", chance = 9100000},
				{group = "armor_attachments", chance = 450000},
				{group = "clothing_attachments", chance = 450000}
			},
			lootChance = 2200000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(gifted_jinda_shaman, "gifted_jinda_shaman")
