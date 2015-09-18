fbase_rebel_army_captain_extreme = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_army_captain_extreme",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 124,
	chanceHit = 3.4,
	damageMin = 765,
	damageMax = 1240,
	baseXp = 12400,
	baseHAM = 48000,
	baseHAMmax = 66000,
	armor = 2,
	resists = {10,10,10,10,10,10,10,-1,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_army_captain_bothan_male.iff",
		"object/mobile/dressed_rebel_army_captain_human_male_01.iff",
		"object/mobile/dressed_rebel_army_captain_moncal_male_01.iff",
		"object/mobile/dressed_rebel_army_captain_trandoshan_female.iff",
		"object/mobile/dressed_rebel_army_captain_twk_male.iff",
		"object/mobile/dressed_rebel_army_captain_zabrak_female.iff"},
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
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,carbineermaster,teraskasimaster)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_army_captain_extreme, "fbase_rebel_army_captain_extreme")
