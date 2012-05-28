crackdown_sand_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_sand_trooper_hard",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 160,
	chanceHit = 0.53,
	damageMin = 370,
	damageMax = 420,
	baseXp = 4302,
	baseHAM = 100000,
	baseHAMmax = 130000,
	armor = 0,
	resists = {0,0,40,100,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_stormtrooper_sand_trooper_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 4000000
		}				
	},
	weapons = {"sandtrooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_sand_trooper_hard, "crackdown_sand_trooper_hard")