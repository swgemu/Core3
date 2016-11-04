crackdown_stormtrooper_sniper_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_stormtrooper_sniper_hard",
	randomNameType = NAME_STORMTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 75,
	chanceHit = 0.76,
	damageMin = 550,
	damageMax = 760,
	baseXp = 7845,
	baseHAM = 14800,
	baseHAMmax = 22300,
	armor = 1,
	resists = {0,0,140,0,0,0,0,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {
		"object/mobile/dressed_stormtrooper_sniper_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7550000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "stormtrooper_common", chance = 100000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"st_sniper_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	personalityStf = "@hireling/hireling_stormtrooper",
	attacks = merge(riflemanmaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_stormtrooper_sniper_hard, "crackdown_stormtrooper_sniper_hard")
