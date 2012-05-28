dark_side_savage = Creature:new {
	objectName = "@mob/creature_names:dark_side_savage",
	socialGroup = "kun",
	pvpFaction = "",
	faction = "",
	level = 75,
	chanceHit = 0.7,
	damageMin = 595,
	damageMax = 900,
	baseXp = 7207,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {60,60,60,60,60,60,60,60,-1},
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

	templates = {"object/mobile/dressed_dark_side_savage.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2000000},
				{group = "crystals_poor", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "melee_weapons", chance = 1000000},
				{group = "armor_attachments", chance = 1000000},
				{group = "clothing_attachments", chance = 1000000}
			},
			lootChance = 3000000
		}	
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dark_side_savage, "dark_side_savage")