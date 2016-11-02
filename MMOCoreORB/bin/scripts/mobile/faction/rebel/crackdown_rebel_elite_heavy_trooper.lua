crackdown_rebel_elite_heavy_trooper = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_elite_heavy_trooper_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 1,--All combat stats can be dealt with later once GCW 'Crackdown' content is implemented
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 45,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_ris_01.iff",
		"object/mobile/dressed_rebel_ris_02.iff",
		"object/mobile/dressed_rebel_ris_03.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 300000},
				{group = "junk", chance = 6000000},
				{group = "holocron_dark", chance = 150000},
				{group = "holocron_light", chance = 150000},
				{group = "weapons_all", chance = 1050000},
				{group = "armor_all", chance = 1050000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,teraskasimaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_elite_heavy_trooper, "crackdown_rebel_elite_heavy_trooper")
