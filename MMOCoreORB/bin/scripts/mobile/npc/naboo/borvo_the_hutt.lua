borvo_the_hutt = Creature:new {
	objectName = "@mob/creature_names:borvo_the_hutt",
	socialGroup = "Borvo",
	pvpFaction = "Borvo",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9336,
	baseHAM = 24000,
	baseHAMmax = 30000,
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/borvo.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "color_crystals", chance = 500000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kits", chance = 1500000},
				{group = "rilfes", chance = 1750000},
				{group = "carbines", chance = 1750000}
			},
			lootChance = 4800000
		}				
	},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(borvo_the_hutt, "borvo_the_hutt")