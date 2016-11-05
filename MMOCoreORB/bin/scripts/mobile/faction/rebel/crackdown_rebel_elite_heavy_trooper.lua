crackdown_rebel_elite_heavy_trooper = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_elite_heavy_trooper",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 91,
	chanceHit = 0.96,
	damageMin = 540,
	damageMax = 950,
	baseXp = 9045,
	baseHAM = 34000,
	baseHAMmax = 35000,
	armor = 2,
	resists = {140,120,115,150,150,150,150,125,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
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
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermaster,marksmanmaster,riflemanmid,carbineermid,teraskasimid,pistoleermid)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_elite_heavy_trooper, "crackdown_rebel_elite_heavy_trooper")