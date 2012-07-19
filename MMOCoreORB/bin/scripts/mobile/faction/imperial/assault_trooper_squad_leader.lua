assault_trooper_squad_leader = Creature:new {
	objectName = "@mob/creature_names:fbase_stormtrooper_squad_leader",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 27,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2822,
	baseHAM = 8100,
	baseHAMmax = 9900,
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_squad_leader_white_white.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 4000000
		}	
	},
	weapons = {"st_assault_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(assault_trooper_squad_leader, "assault_trooper_squad_leader")