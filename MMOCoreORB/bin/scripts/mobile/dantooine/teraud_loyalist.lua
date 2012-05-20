teraud_loyalist = Creature:new {
	objectName = "@mob/creature_names:warren_teraud_loyalist",
	socialGroup = "warren_teraud",
	pvpFaction = "warren_teraud",
	faction = "warren_teraud",
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3460,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {25,25,0,-1,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/warren_teraud_loyalist_s01.iff",
		"object/mobile/warren_teraud_loyalist_s02.iff",
		"object/mobile/warren_teraud_loyalist_s03.iff",
		"object/mobile/warren_teraud_loyalist_s04.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 1000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000}
			},
			lootChance = 3500000
		}			
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(teraud_loyalist, "teraud_loyalist")
