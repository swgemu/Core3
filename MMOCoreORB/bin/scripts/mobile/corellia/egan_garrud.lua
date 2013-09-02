egan_garrud = Creature:new {
	objectName = "@mob/creature_names:corsec_captain",
	customName = "Captain Egan Garrud",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_corsec_captain_human_male_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "tailor_components", chance = 1500000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "garmTargetConvo",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(egan_garrud, "egan_garrud")
