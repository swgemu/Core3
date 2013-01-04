rebel_commodore = Creature:new {
	objectName = "@mob/creature_names:corvette_rebel_commodore",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 181,
	chanceHit = 130,
	damageMin = 1045,
	damageMax = 1800,
	baseXp = 17178,
	baseHAM = 126000,
	baseHAMmax = 154000,
	armor = 2,
	resists = {65,75,40,40,30,30,80,65,-1},
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

	templates = {"object/mobile/dressed_rebel_commando_zabrak_female_01.iff"},
	lootGroups = {
		{
	        groups = {
				{group = "color_crystals", chance = 500000},
				{group = "junk", chance = 4500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
                {group = "melee_weapons", chance = 1000000},
                {group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 6000000
		}	
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(rebel_commodore, "rebel_commodore")