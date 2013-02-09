stormtrooper_bombardier = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_bombardier",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 25,
	chanceHit = 0.36,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2637,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {15,15,40,15,15,15,15,-1,-1},
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

	templates = {"object/mobile/dressed_stormtrooper_bombardier_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4600000},
				{group = "rifles", chance = 1200000},
				{group = "pistols", chance = 1200000},
				{group = "melee_weapons", chance = 1200000},
				{group = "carbines", chance = 1200000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000}
			},
			lootChance = 2800000
		}						
	},
	weapons = {"st_bombardier_weapons"},
	conversationTemplate = "",
	attacks = merge(commandomaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(stormtrooper_bombardier, "stormtrooper_bombardier")
