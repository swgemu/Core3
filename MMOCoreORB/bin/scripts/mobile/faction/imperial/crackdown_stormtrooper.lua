crackdown_stormtrooper = Creature:new {
	objectName = "@mob/creature_names:crackdown_stormtrooper",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 1,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 45,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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

	templates = {"object/mobile/dressed_stormtrooper_commando1_m.iff",
				"object/mobile/dressed_stormtrooper_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6500000},
				{group = "rifles", chance = 500000},
				{group = "loot_kit_parts", chance = 1300000},
				{group = "carbines", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000}
			},
			lootChance = 4000000
		}					
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_stormtrooper, "crackdown_stormtrooper")