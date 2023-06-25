ruwan_warrant_officer = Creature:new {
  objectName = "@mob/creature_names:imperial_warrant_officer_ii",
  socialGroup = "imperial",
  faction = "imperial",
	mobType = MOB_NPC,
  level = 18,
  chanceHit = 0.32,
  damageMin = 170,
  damageMax = 180,
  baseXp = 1426,
  baseHAM = 4100,
  baseHAMmax = 5000,
  armor = 0,
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
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = { "imperial_officer" },
  lootGroups = {},
  primaryWeapon = "imperial_weapons_medium",
	secondaryWeapon = "unarmed",
  conversationTemplate = "ruwan_tokai_mission_target_convotemplate",
  
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,carbineermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(ruwan_warrant_officer, "ruwan_warrant_officer")
