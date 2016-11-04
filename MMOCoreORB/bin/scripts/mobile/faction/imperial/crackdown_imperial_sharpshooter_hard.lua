crackdown_imperial_sharpshooter_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_sharpshooter",
	randomNameType = NAME_STORMTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 57,
	chanceHit = 0.52,
	damageMin = 460,
	damageMax = 570,
	baseXp = 5440,
	baseHAM = 10500,
	baseHAMmax = 14300,
	armor = 1,
	resists = {5,5,5,5,5,5,5,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_sniper_m.iff",
			"object/mobile/dressed_imperial_gunner_m.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",	
	attacks = merge(riflemanmaster,carbineermaster,pistoleermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_sharpshooter_hard, "crackdown_imperial_sharpshooter_hard")