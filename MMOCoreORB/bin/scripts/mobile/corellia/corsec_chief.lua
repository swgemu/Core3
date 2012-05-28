corsec_chief = Creature:new {
	objectName = "@mob/creature_names:corsec_chief",
	socialGroup = "corsec",
	pvpFaction = "corsec",
	faction = "corsec",
	level = 27,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2822,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {20,20,20,20,20,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_corellia_local_corsec_chief.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "corsec_weapons", chance = 1500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 4500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corsec_chief, "corsec_chief")
