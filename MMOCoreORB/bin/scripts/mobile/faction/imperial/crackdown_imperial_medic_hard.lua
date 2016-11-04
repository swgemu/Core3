crackdown_imperial_medic_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_medic_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 56,
	chanceHit = 0.51,
	damageMin = 400,
	damageMax = 580,
	baseXp = 5140,
	baseHAM = 10000,
	baseHAMmax = 13500,
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
	creatureBitmask = PACK + HEALER,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_medic3_human_male_01.iff",
		"object/mobile/dressed_imperial_medic1_human_male_01.iff"
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
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(riflemannovice,carbineermaster,pikemanmid)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_medic_hard, "crackdown_imperial_medic_hard")
