corsec_trooper = Creature:new {
	objectName = "@mob/creature_names:corsec_trooper",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "corsec",
	faction = "corsec",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
		"object/mobile/dressed_corsec_officer_human_male_01.iff",
		"object/mobile/dressed_corsec_officer_human_female_01.iff",
		"object/mobile/dressed_corsec_pilot_human_male_01.iff",
		"object/mobile/dressed_corsec_pilot_human_female_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "tailor_components", chance = 1500000}
			},
			lootChance = 2000000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(corsec_trooper, "corsec_trooper")
