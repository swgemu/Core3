corsec_inspector_sergeant = Creature:new {
	objectName = "@mob/creature_names:corsec_inspector_sergeant",
	socialGroup = "corsec",
	faction = "corsec",
	level = 19,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 4500,
	baseHAMmax = 5500,
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_corsec_detective_human_male_01.iff",
		"object/mobile/dressed_corsec_detective_human_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "corsec_weapons", chance = 2500000},
				{group = "wearables_common", chance = 2000000},
				{group = "tailor_components", chance = 1500000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"corsec_police_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(corsec_inspector_sergeant, "corsec_inspector_sergeant")
