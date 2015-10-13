idlePet = {
	{id="idle",		name="Selector",			pid="none"},
	{id="idle0",	name="Sequence",			pid="idle"},
	{id="idle1",	name="Sequence",			pid="idle"},
	{id="idle2",	name="Wait",				pid="idle"},
	{id="idle3",	name="CheckFollowState",	pid="idle0",	args={condition=PATROLLING}},
	{id="idle4",	name="WriteBlackboard",		pid="idle0",	args={key="moveMode", val=WALK}},
	{id="idle5",	name="TreeSocket",			pid="idle0",	args={slot=MOVE}},
	{id="idle6",	name="Wait",				pid="idle0",	args={duration=5}}, -- TODO: This needs to be behind an at destination check
	{id="idle7",	name="Not",					pid="idle1"},
	{id="idle8",	name="WriteBlackboard",		pid="idle1",	args={key="moveMode", val=RUN}},
	{id="idle9",	name="TreeSocket",			pid="idle1",	args={slot=MOVE}},
	{id="idle10",	name="CheckFollowState",	pid="idle7",	args={condition=OBLIVIOUS}}
}
addAiTemplate("idlePet", idlePet)

targetPet = {
	{id="gettar0",	name="Selector",				pid="none"},
	{id="gettar1",	name="Sequence",				pid="gettar0"},
	{id="gettar2",	name="ExitCombat",				pid="gettar0",	args={clearDefenders=true}},
	{id="gettar3",	name="Selector",				pid="gettar1"},
	{id="gettar4",	name="Selector",				pid="gettar1"},
	{id="gettar5",	name="SetDefenderFromFollow",	pid="gettar1"},
	{id="gettar6",	name="Sequence",				pid="gettar3"},
	{id="gettar7",	name="Sequence",				pid="gettar3"},
	{id="gettar8",	name="Sequence",				pid="gettar3"},
	{id="gettar10",	name="CheckTargetIsValid",		pid="gettar4"},
	{id="gettar11",	name="AlwaysFail",				pid="gettar4"},
	{id="gettar12",	name="CheckPetCommand",			pid="gettar6",	args={condition=PET_GUARD}},
	{id="gettar13",	name="CheckFollowIsCommand",	pid="gettar6"},
	{id="gettar14",	name="AlwaysSucceed",			pid="gettar6"},
	{id="gettar15",	name="Selector",				pid="gettar7"},
	{id="gettar16",	name="Not",						pid="gettar7"},
	{id="gettar17",	name="AlwaysSucceed",			pid="gettar7"},
	{id="gettar18",	name="CheckPetCommand",			pid="gettar8",	args={condition=PET_PATROL}},
	{id="gettar19",	name="AlwaysSucceed",			pid="gettar8"},
	{id="gettar23",	name="Sequence",				pid="gettar11"},
	{id="gettar24",	name="GetFollowFromTarget",		pid="gettar14"},
	{id="gettar25",	name="CheckPetCommand",			pid="gettar15",	args={condition=PET_ATTACK}},
	{id="gettar26",	name="CheckPetCommand",			pid="gettar15",	args={condition=PET_SPECIAL_ATTACK1}},
	{id="gettar27",	name="CheckPetCommand",			pid="gettar15",	args={condition=PET_SPECIAL_ATTACK2}},
	{id="gettar28",	name="CheckFollowIsCommand",	pid="gettar16"},
	{id="gettar29",	name="GetFollowFromCommand",	pid="gettar17"},
	{id="gettar30",	name="Selector",				pid="gettar19"},
	{id="gettar31",	name="DropFollowFromDefenders",	pid="gettar23"},
	{id="gettar32",	name="RestoreFollow",			pid="gettar23"},
	{id="gettar33",	name="GetFollowFromThreatMap",	pid="gettar30"},
	{id="gettar34",	name="GetFollowFromDefenders",	pid="gettar30"}
}
addAiTemplate("targetPet", targetPet)

movePet = {
	{id="move0",	name="Selector",			pid="none"},
	{id="move1",	name="Not",					pid="move0"},
	{id="move3",	name="AlwaysFail",			pid="move0"},
	{id="move4",	name="FindNextPosition",	pid="move0"},
	{id="move5",	name="Sequence",			pid="move1"},
	{id="move8",	name="Sequence",			pid="move3"},
	{id="move9",	name="CheckPosture",		pid="move5",	args={condition=UPRIGHT}},
	{id="move10",	name="CheckDestination",	pid="move5",	args={condition=0}},
	{id="move11",	name="CheckSpeed",			pid="move8",	args={condition=0}},
	{id="move12",	name="CompleteMove",		pid="move8"}
}
addAiTemplate("movePet", movePet)
