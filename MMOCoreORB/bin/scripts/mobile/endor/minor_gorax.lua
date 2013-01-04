minor_gorax = Creature:new {
	objectName = "@mob/creature_names:minor_gorax",
	socialGroup = "gorax",
	pvpFaction = "",
	faction = "",
	level = 131,
	chanceHit = 40,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 12424,
	baseHAM = 89000,
	baseHAMmax = 109000,
	armor = 3,
	resists = {65,65,50,50,50,50,50,50,-1},
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
	diet = CARNIVORE,

	templates = {"object/mobile/gorax.iff"},
	lootGroups = {
	    {
	        groups = {
				{group = "minor_gorax", chance = 5000000},
				{group = "armor_attachments", chance = 2500000},
				{group = "clothing_attachments", chance = 2500000}
			},
			lootChance = 3000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(minor_gorax, "minor_gorax")