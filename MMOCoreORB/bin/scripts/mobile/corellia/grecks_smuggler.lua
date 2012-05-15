grecks_smuggler = Creature:new {
	objectName = "@mob/creature_names:greck_smuggler",
	socialGroup = "olag_greck",
	pvpFaction = "olag_greck",
	faction = "olag_greck",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {5,5,5,-1,-1,-1,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_crook_zabrak_female_01.iff",
		"object/mobile/dressed_crook_zabrak_male_01.iff",
		"object/mobile/dressed_robber_human_female_01.iff",
		"object/mobile/dressed_robber_human_male_01.iff",
		"object/mobile/dressed_robber_twk_female_01.iff",
		"object/mobile/dressed_robber_twk_male_01.iff"},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "loot_kits", chance = 3500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 6500000
		}	
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(grecks_smuggler, "grecks_smuggler")
