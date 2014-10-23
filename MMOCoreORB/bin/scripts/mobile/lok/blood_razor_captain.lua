blood_razor_captain = Creature:new {
	objectName = "@mob/creature_names:blood_razor_captain",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {40,70,30,30,-1,30,30,-1,-1},
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
		"object/mobile/dressed_blood_razor_pirate_captain_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_captain_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_captain_wee_m.iff"
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
				{group = "wearables_all", chance = 500000},
			},
			lootChance = 3500000
		}
	},
	weapons = {"blood_razer_weapons"},
	conversationTemplate = "",
	attacks = merge(pistoleermaster,pikemanmaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_captain, "blood_razor_captain")
