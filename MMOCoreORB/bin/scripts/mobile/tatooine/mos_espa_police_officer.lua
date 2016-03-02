mos_espa_police_officer = Creature:new {
	objectName = "@mob/creature_names:mos_espa_police_officer",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {20,20,20,20,20,20,20,20,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_eisley_officer_aqualish_female_01.iff",
		"object/mobile/dressed_eisley_officer_aqualish_male_01.iff",
		"object/mobile/dressed_eisley_officer_bothan_female_01.iff",
		"object/mobile/dressed_eisley_officer_bothan_male_01.iff",
		"object/mobile/dressed_eisley_officer_human_female_01.iff",
		"object/mobile/dressed_eisley_officer_human_male_01.iff",
		"object/mobile/dressed_eisley_officer_quarren_male_01.iff",
		"object/mobile/dressed_eisley_officer_rodian_female_01.iff",
		"object/mobile/dressed_eisley_officer_rodian_male_01.iff",
		"object/mobile/dressed_eisley_officer_trandoshan_female_01.iff",
		"object/mobile/dressed_eisley_officer_trandoshan_male_01.iff",
		"object/mobile/dressed_eisley_officer_twilek_female_01.iff",
		"object/mobile/dressed_eisley_officer_twilek_male_01.iff",
		"object/mobile/dressed_eisley_officer_zabrak_female_01.iff",
		"object/mobile/dressed_eisley_officer_zabrak_male_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(mos_espa_police_officer, "mos_espa_police_officer")
