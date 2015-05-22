blood_razor_officer = Creature:new {
	objectName = "@mob/creature_names:blood_razor_officer",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "bloodrazor",
	faction = "bloodrazor",
	level = 40,
	chanceHit = 0.43,
	damageMin = 335,
	damageMax = 380,
	baseXp = 4006,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {25,60,25,25,-1,25,25,-1,-1},
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
		"object/mobile/dressed_blood_razor_pirate_officer_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_officer_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_officer_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_officer_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_officer_wee_m.iff"
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
				{group = "bloodrazor_common", chance = 1500000},
				{group = "wearables_uncommon", chance = 500000},
			}
		}
	},
	weapons = {"blood_razer_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(pistoleermaster,pikemanmaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_officer, "blood_razor_officer")
