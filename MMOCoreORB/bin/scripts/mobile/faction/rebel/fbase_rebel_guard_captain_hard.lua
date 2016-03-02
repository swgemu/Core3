fbase_rebel_guard_captain_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_guard_captain_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 90,
	chanceHit = 0.9,
	damageMin = 595,
	damageMax = 900,
	baseXp = 9000,
	baseHAM = 19000,
	baseHAMmax = 26000,
	armor = 1,
	resists = {30,30,30,130,30,130,-1,-1,-1},
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_specforce_captain_human_male_01.iff",
		"object/mobile/dressed_rebel_specforce_captain_human_female_01.iff",
		"object/mobile/dressed_rebel_specforce_captain_moncal_female_01.iff",
		"object/mobile/dressed_rebel_specforce_captain_rodian_female_01.iff",
		"object/mobile/dressed_rebel_specforce_captain_zabrak_male_01.iff",
		"object/mobile/dressed_rebel_specforce_captain_trandoshan_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1100000},
				{group = "armor_all", chance = 1100000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "rebel_officer_common", chance = 400000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,pistoleermaster,teraskasimid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_guard_captain_hard, "fbase_rebel_guard_captain_hard")
