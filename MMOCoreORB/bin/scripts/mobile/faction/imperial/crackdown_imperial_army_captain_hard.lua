crackdown_imperial_army_captain_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_army_captain_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 61,
	chanceHit = 0.64,
	damageMin = 450,
	damageMax = 610,
	baseXp = 6206,
	baseHAM = 12400,
	baseHAMmax = 16600,
	armor = 1,
	resists = {10,10,10,10,10,10,10,-1,-1},
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_captain_white_white.iff",
		"object/mobile/dressed_imperial_captain_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7200000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "imperial_officer_common", chance = 450000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(riflemanmaster,carbineermaster,pikemanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_army_captain_hard, "crackdown_imperial_army_captain_hard")