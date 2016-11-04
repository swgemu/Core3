crackdown_scout_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_scout_trooper_hard",
	randomNameType = NAME_SCOUTTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 66,
	chanceHit = 0.65,
	damageMin = 420,
	damageMax = 630,
	baseXp = 6630,
	baseHAM = 12300,
	baseHAMmax = 18700,
	armor = 1,
	resists = {115,115,0,0,0,-1,0,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_scout_trooper_white_white.iff"},
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
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/stormtrooper",
	personalityStf = "@hireling/hireling_stormtrooper",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_scout_trooper_hard, "crackdown_scout_trooper_hard")
