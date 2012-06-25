stormtrooper_sniper = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_sniper",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_sniper_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 300000},
				{group = "pistols", chance = 300000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 4000000
		}					
	},
	weapons = {"st_sniper_weapons"},
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(stormtrooper_sniper, "stormtrooper_sniper")