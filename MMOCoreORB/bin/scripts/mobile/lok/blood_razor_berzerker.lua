blood_razor_berzerker = Creature:new {
	objectName = "@mob/creature_names:blood_razor_berzerker",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "bloodrazor",
	faction = "bloodrazor",
	level = 36,
	chanceHit = 0.43,
	damageMin = 395,
	damageMax = 500,
	baseXp = 3642,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {-1,60,25,25,-1,25,25,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_blood_razor_pirate_berzerker_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_berzerker_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_berzerker_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_berzerker_tran_m.iff"
	},

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3800000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "power_crystals", chance = 400000},
				{group = "melee_unarmed", chance = 600000},
				{group = "melee_polearm", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000},
				{group = "bloodrazor_common", chance = 2000000}
			}
		}
	},
	weapons = {"blood_razer_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(pistoleermaster,pikemanmaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_berzerker, "blood_razor_berzerker")
