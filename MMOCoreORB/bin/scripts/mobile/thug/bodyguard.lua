bodyguard = Creature:new {
	objectName = "@mob/creature_names:bodyguard",
	socialGroup = "thug",
	pvpFaction = "thug",
	faction = "thug",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
					"object/mobile/dressed_tatooine_desert_demon_bodyguard.iff",
					"object/mobile/dressed_mugger.iff",
					"object/mobile/dressed_hoodlum_zabrak_female_01.iff",
					"object/mobile/dressed_robber_twk_male_01.iff",
					"object/mobile/dressed_criminal_thug_human_female_01.iff",
					"object/mobile/dressed_robber_twk_female_01.iff",
					"object/mobile/dressed_crook_zabrak_male_01.iff",
					"object/mobile/dressed_hooligan_rodian_female_01.iff"
				},
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bodyguard, "bodyguard")