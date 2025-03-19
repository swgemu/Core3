--[[
Each entry in the table represents a droid command with the following fields:
	commandName:   		The unique identifier for the command.
	stringID:      		String for droid/flight computer chatter
	delayModifier: 		Multiplier applied against the droid command speed for cooldown
	component:     		Component slot to modify - 12 will apply to all weapons, not just slot 12
	energyEfficiency:	A modifier representing energy efficiency - i.e. how much power it uses.
	generalEfficiency:	A modifier representing overall efficiency - i.e. how it performs compared to its baseline.
	damage:			How much damage applied to a component when the droid command is run.
	frontReinforceRatio:	A percentage value for shield reinforcement.
	capacitorReinforcePercentage: A percentage value for capacitor to shield reinforcement.
	frontAdjustRatio:	A percentage value for shield adjustment.

REACTOR = 0,
ENGINE = 1,
SHIELD = 2,
CAPACITOR = 6,
WEAPON = 12
]]--

droidCommands = {
  -- Engine Commands
  {commandName="droidcommand_engineefficiencyone", stringID="@space/droid_commands:engine_efficiency_one", delayModifier=5, component=1, energyEfficiency=1.25, generalEfficiency=0.75, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineefficiencytwo", stringID="@space/droid_commands:engine_efficiency_two", delayModifier=5, component=1, energyEfficiency=1.5, generalEfficiency=0.5, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineefficiencythree", stringID="@space/droid_commands:engine_efficiency_three", delayModifier=5, component=1, energyEfficiency=2, generalEfficiency=0.25, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineefficiencyfour", stringID="@space/droid_commands:engine_efficiency_four", delayModifier=5, component=1, energyEfficiency=3, generalEfficiency=0.1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_enginenormalize", stringID="@space/droid_commands:engine_normalize", delayModifier=1, component=1, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineoverloadone", stringID="@space/droid_commands:engine_overload_one", delayModifier=5, component=1, energyEfficiency=0.8, generalEfficiency=1.1, damage=1, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineoverloadtwo", stringID="@space/droid_commands:engine_overload_two", delayModifier=5, component=1, energyEfficiency=0.6, generalEfficiency=1.2, damage=3, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineoverloadthree", stringID="@space/droid_commands:engine_overload_three", delayModifier=5, component=1, energyEfficiency=0.3, generalEfficiency=1.3, damage=6, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_engineoverloadfour", stringID="@space/droid_commands:engine_overload_four", delayModifier=5, component=1, energyEfficiency=0.1, generalEfficiency=1.4, damage=18, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},

  -- Reactor Commands
  {commandName="droidcommand_reactoroverloadone", stringID="@space/droid_commands:reactor_overload_one", delayModifier=5, component=0, energyEfficiency=1, generalEfficiency=1.1, damage=5, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_reactornormalize", stringID="@space/droid_commands:reactor_normalize", delayModifier=5, component=0, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_reactoroverloadtwo", stringID="@space/droid_commands:reactor_overload_two", delayModifier=5, component=0, energyEfficiency=1, generalEfficiency=1.3, damage=5, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_reactoroverloadthree", stringID="@space/droid_commands:reactor_overload_three", delayModifier=5, component=0, energyEfficiency=1, generalEfficiency=1.6, damage=10, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_reactoroverloadfour", stringID="@space/droid_commands:reactor_overload_four", delayModifier=5, component=0, energyEfficiency=1, generalEfficiency=1.9, damage=30, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},

  -- Shield Commands
  {commandName="droidcommand_shieldbacktofronttwenty", stringID="@space/droid_commands:shields_backtofront_twenty", delayModifier=1, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=1.2, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldfronttobacktwenty", stringID="@space/droid_commands:shields_fronttoback_twenty", delayModifier=1, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=0.8, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldbacktofrontfifty", stringID="@space/droid_commands:shields_backtofront_fifty", delayModifier=2, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=1.4, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldfronttobackfifty", stringID="@space/droid_commands:shields_fronttoback_fifty", delayModifier=2, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=0.6, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldbacktofronteighty", stringID="@space/droid_commands:shields_backtofront_eighty", delayModifier=3, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=1.8, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldfronttobackeighty", stringID="@space/droid_commands:shields_fronttoback_eighty", delayModifier=3, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=0.2, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldbacktofronthundred", stringID="@space/droid_commands:shields_backtofront_hundred", delayModifier=4, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldfronttobackhundred", stringID="@space/droid_commands:shields_fronttoback_hundred", delayModifier=4, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=1, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_shieldnormalize", stringID="@space/droid_commands:shields_normalize", delayModifier=1, component=2, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=1},
  {commandName="droidcommand_shieldadjustfrontone", stringID="@space/droid_commands:shield_adjust_front_one", delayModifier=1, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=1.2},
  {commandName="droidcommand_shieldadjustfronttwo", stringID="@space/droid_commands:shield_adjust_front_two", delayModifier=2, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=1.5},
  {commandName="droidcommand_shieldadjustfrontthree", stringID="@space/droid_commands:shield_adjust_front_three", delayModifier=3, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=1.75},
  {commandName="droidcommand_shieldadjustfrontfour", stringID="@space/droid_commands:shield_adjust_front_four", delayModifier=4, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=1.9},
  {commandName="droidcommand_shieldadjustrearone", stringID="@space/droid_commands:shield_adjust_rear_one", delayModifier=1, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0.8},
  {commandName="droidcommand_shieldadjustreartwo", stringID="@space/droid_commands:shield_adjust_rear_two", delayModifier=2, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0.5},
  {commandName="droidcommand_shieldadjustrearthree", stringID="@space/droid_commands:shield_adjust_rear_three", delayModifier=3, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0.25},
  {commandName="droidcommand_shieldadjustrearfour", stringID="@space/droid_commands:shield_adjust_rear_four", delayModifier=4, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0.1},
  {commandName="droidcommand_shieldemergencyfront", stringID="@space/droid_commands:shield_emergency_front", delayModifier=3.0, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=1.75, capacitorReinforcePercentage=0.75, frontAdjustRatio=0},
  {commandName="droidcommand_shieldemergencyrear", stringID="@space/droid_commands:shield_emergency_rear", delayModifier=3.0, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0.25, capacitorReinforcePercentage=0.75, frontAdjustRatio=0},
  {commandName="droidcommand_weapcaptoshieldone", stringID="@space/droid_commands:weapcap_to_shield_one", delayModifier=1, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0.25, frontAdjustRatio=0},
  {commandName="droidcommand_weapcaptoshieldtwo", stringID="@space/droid_commands:weapcap_to_shield_two", delayModifier=1, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0.5, frontAdjustRatio=0},
  {commandName="droidcommand_weapcaptoshieldthree", stringID="@space/droid_commands:weapcap_to_shield_three", delayModifier=1, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0.75, frontAdjustRatio=0},
  {commandName="droidcommand_weapcaptoshieldfour", stringID="@space/droid_commands:weapcap_to_shield_four", delayModifier=1, component=2, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=1, frontAdjustRatio=0},

  -- Weapon Commands
  {commandName="droidcommand_weaponeffeciencyone", stringID="@space/droid_commands:weapons_efficiency_one", delayModifier=5, component=12, energyEfficiency=1.25, generalEfficiency=0.75, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponeffeciencytwo", stringID="@space/droid_commands:weapons_efficiency_two", delayModifier=5, component=12, energyEfficiency=1.5, generalEfficiency=0.5, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponeffeciencythree", stringID="@space/droid_commands:weapons_efficiency_three", delayModifier=5, component=12, energyEfficiency=2, generalEfficiency=0.25, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponeffeciencyfour", stringID="@space/droid_commands:weapons_efficiency_four", delayModifier=5, component=12, energyEfficiency=3, generalEfficiency=0.1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponnormalize", stringID="@space/droid_commands:weapons_normalize", delayModifier=1, component=12, energyEfficiency=1, generalEfficiency=1, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponoverloadone", stringID="@space/droid_commands:weapons_overload_one", delayModifier=5, component=12, energyEfficiency=0.7, generalEfficiency=1.25, damage=1, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponoverloadtwo", stringID="@space/droid_commands:weapons_overload_two", delayModifier=5, component=12, energyEfficiency=0.5, generalEfficiency=1.5, damage=3, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponoverloadthree", stringID="@space/droid_commands:weapons_overload_three", delayModifier=5, component=12, energyEfficiency=2, generalEfficiency=2, damage=6, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weaponoverloadfour", stringID="@space/droid_commands:weapons_overload_four", delayModifier=5, component=12, energyEfficiency=0.1, generalEfficiency=3, damage=18, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},

  -- Capacitor Commands
  {commandName="droidcommand_weapcappowerupone", stringID="@space/droid_commands:weapcap_powerup_one", delayModifier=5, component=6, energyEfficiency=1.25, generalEfficiency=1.25, damage=2, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weapcappoweruptwo", stringID="@space/droid_commands:weapcap_powerup_two", delayModifier=5, component=6, energyEfficiency=1.5, generalEfficiency=1.5, damage=4, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weapcappowerupthree", stringID="@space/droid_commands:weapcap_powerup_three", delayModifier=5, component=6, energyEfficiency=1.75, generalEfficiency=1.75, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weapcappowerupfour", stringID="@space/droid_commands:weapcap_powerup_four", delayModifier=5, component=6, energyEfficiency=2, generalEfficiency=2, damage=8, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
  {commandName="droidcommand_weapcapequalize", stringID="@space/droid_commands:weapcap_equalize", delayModifier=1, component=6, energyEfficiency=1, generalEfficiency=1, damage=16, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},

  -- Utility Commands
  {commandName="droidcommand_mutedroid", stringID="@space/droid_commands:mute_droid", delayModifier=1, component=-1, energyEfficiency=0, generalEfficiency=0, damage=0, frontReinforceRatio=0, capacitorReinforcePercentage=0, frontAdjustRatio=0},
}
