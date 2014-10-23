blood_razor_scout = Creature:new {
	objectName = "@mob/creature_names:blood_razor_scout",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 32,
	chanceHit = 0.39,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3279,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {20,45,20,20,-1,20,20,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_blood_razor_pirate_scout_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_scout_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_scout_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_scout_tran_m.iff"
		},

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3800000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_okay", chance = 400000},
				{group = "melee_unarmed", chance = 600000},
				{group = "melee_polearm", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000},
				{group = "bloodrazor_common", chance = 2000000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"blood_razer_weapons"},
	conversationTemplate = "",
	attacks = merge(pistoleermaster,pikemanmaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_scout, "blood_razor_scout")
