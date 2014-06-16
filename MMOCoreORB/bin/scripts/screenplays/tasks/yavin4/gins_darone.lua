gins_darone_missions =
  {
    {
      missionType = "confiscate",
      primarySpawns =
      {
        { npcTemplate = "gins_stranded_rebel_officer", planetName = "yavin4", npcName = "Stranded Rebel Officer" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/gins_darone_q1_needed.iff", itemName = "" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
        { rewardType = "faction", faction = "imperial", amount = 15 }
      }
    },
    {
      missionType = "confiscate",
      primarySpawns =
      {
        { npcTemplate = "gins_rebel_specforce_sergeant", planetName = "yavin4", npcName = "" }
      },
      secondarySpawns =
      {
        { npcTemplate = "senior_specforce_pathfinder", planetName = "yavin4", npcName = "" },
        { npcTemplate = "senior_specforce_pathfinder", planetName = "yavin4", npcName = "" },
        { npcTemplate = "senior_specforce_urban_guerrilla", planetName = "yavin4", npcName = "" },
        { npcTemplate = "senior_specforce_urban_guerrilla", planetName = "yavin4", npcName = "" }
      },
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/gins_darone_q2_needed.iff", itemName = "" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
        { rewardType = "faction", faction = "imperial", amount = 15 }
      }
    },
    {
      missionType = "assassinate",
      primarySpawns =
      {
        { npcTemplate = "gins_scientist", planetName = "yavin4", npcName = "Rebel Scientist" }
      },
      secondarySpawns = {},
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
        { rewardType = "faction", faction = "imperial", amount = 15 }
      }
    },
  }

npcMapGinsDarone =
  {
    {
      spawnData = { planetName = "yavin4", npcTemplate = "gins_darone", x = -22.0, z = 32.0, y = 58.0, direction = 111, cellID = 3465358, position = STAND },
      worldPosition = { x = -3094, y = -2985 },
      npcNumber = 1,
      stfFile = "@static_npc/yavin/yavin_massassi_gins_darone",
      missions = gins_darone_missions
    },

  }

GinsDarone = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapGinsDarone,
  className = "GinsDarone",
  screenPlayState = "gins_darone_quest",
  distance = 500,
  faction = FACTIONIMPERIAL
}

registerScreenPlay("GinsDarone", true)

gins_darone_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = GinsDarone
}
gins_darone_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = GinsDarone
}