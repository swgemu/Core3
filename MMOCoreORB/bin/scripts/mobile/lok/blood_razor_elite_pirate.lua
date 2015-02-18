blood_razor_elite_pirate = Creature:new {
	objectName = "@mob/creature_names:blood_razor_pirate_elite",
	socialGroup = "bloodrazor",
	faction = "bloodrazor",
	level = 33,
	chanceHit = 0.39,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3370,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {20,60,20,20,-1,20,20,-1,-1},
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
		"object/mobile/dressed_blood_razor_pirate_elite_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_elite_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_elite_nikto_m.iff"
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
	reactionStf = "@npc_reaction/slang",
	attacks = merge(pistoleermaster,pikemanmaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_elite_pirate, "blood_razor_elite_pirate")
