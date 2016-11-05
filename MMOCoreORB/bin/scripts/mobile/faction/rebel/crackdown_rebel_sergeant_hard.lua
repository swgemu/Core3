crackdown_rebel_sergeant_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_sergeant_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 56,
	chanceHit = 0.51,
	damageMin = 470,
	damageMax = 580,
	baseXp = 5600,
	baseHAM = 10000,
	baseHAMmax = 13500,
	armor = 1,
	resists = {105,5,5,5,5,5,5,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_sergeant_fat_zabrak_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_human_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_moncal_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_rodian_female_01.iff",
		"object/mobile/dressed_rebel_sergeant_rodian_male_01.iff",
		"object/mobile/dressed_rebel_sergeant_twilek_female_old_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermid,marksmanmaster,riflemannovice,carbineermaster,pistoleermid)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_sergeant_hard, "crackdown_rebel_sergeant_hard")
