stoos_imperial_ensign = Creature:new {
  objectName = "",
  socialGroup = "imperial",
  faction = "imperial",
  mobType = MOB_NPC,
  level = 30,
  chanceHit = 0.390000,
  damageMin = 290,
  damageMax = 300,
  baseXp = 2914,
  baseHAM = 8400,
  baseHAMmax = 10200,
  armor = 0,
  resists = {0,45,0,-1,40,-1,40,-1,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0.,
  ferocity = 0,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = {"imperial_officer"},
  lootGroups = {},
  primaryWeapon = "imperial_weapons_medium",
	secondaryWeapon = "unarmed",
  conversationTemplate = "stoos_olko_mission_target_convotemplate",
  
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { },

}

CreatureTemplates:addCreatureTemplate(stoos_imperial_ensign, "stoos_imperial_ensign")
