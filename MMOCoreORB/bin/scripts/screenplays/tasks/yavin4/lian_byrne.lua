lian_byrne_missions =
  {
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "lian_imperial_courier", planetName = "yavin4", npcName = "Imperial Courier" }
      },
      secondarySpawns =
      {
        { npcTemplate = "rebel_trooper", planetName = "yavin4", npcName = "" },
        { npcTemplate = "rebel_trooper", planetName = "yavin4", npcName = "" }
      },
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/lian_byrne_q1_needed.iff", itemName = "Forensics report" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
        { rewardType = "faction", faction = "imperial", amount = 10 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "lian_imperial_operative", planetName = "yavin4", npcName = "Imperial Operative" }
      },
      secondarySpawns = {
        { npcTemplate = "lian_thief", planetName = "yavin4", npcName = "Scavenger" },
        { npcTemplate = "lian_thief", planetName = "yavin4", npcName = "Scavenger" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 75 },
        { rewardType = "faction", faction = "imperial", amount = 10 }
      }
    },
    {
      missionType = "confiscate",
      primarySpawns =
      {
        { npcTemplate = "lian_spynet_operative", planetName = "yavin4", npcName = "Rebel Spy" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/lian_byrne_q3_needed.iff", itemName = "" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 100 },
        { rewardType = "faction", faction = "imperial", amount = 15 }
      }
    },
    {
      missionType = "assassinate",
      primarySpawns =
      {
        { npcTemplate = "lian_rebel_specforce_urban_guerrilla", planetName = "yavin4", npcName = "" },
        { npcTemplate = "lian_rebel_specforce_urban_guerrilla", planetName = "yavin4", npcName = "" }
      },
      secondarySpawns = {},
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 200 },
        { rewardType = "faction", faction = "imperial", amount = 15 }
      }
    },
  }

npcMapLianByrne =
  {
    {
      spawnData = { planetName = "yavin4", npcTemplate = "lian_byrne", x = -8.6, z = 58.0, y = -52.4, direction = 115, cellID = 3465362, position = STAND },
      worldPosition = { x = -2985, y = -2965 },
      npcNumber = 1,
      stfFile = "@static_npc/yavin/yavin_massassi_lian_byrne",
      missions = lian_byrne_missions
    },

  }

LianByrne = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapLianByrne,
  className = "LianByrne",
  screenPlayState = "lian_byrne_quest",
  distance = 500,
  faction = FACTIONIMPERIAL
}

registerScreenPlay("LianByrne", true)

lian_byrne_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = LianByrne
}
lian_byrne_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = LianByrne
}