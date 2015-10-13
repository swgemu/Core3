-- this is for scripters to set manual one-time patrol points
wanderStatic = {
	{id="wander",	name="Selector",		pid="none"},
	{id="wander0",	name="Sequence",		pid="wander"},
	{id="walkset",	name="WriteBlackboard",	pid="wander0",	args={key="moveMode", val=WALK}},
	{id="walkmove",	name="TreeSocket",		pid="wander0",	args={slot=MOVE}},
	{id="wait0",	name="Wait",			pid="wander",	args={duration=10}}
}
addAiTemplate("wanderStatic", wanderStatic)

escortWalk = {
	{id="wander",	name="Selector",		pid="none"},
	{id="wander0",	name="Sequence",		pid="wander"},
	{id="walkset",	name="WriteBlackboard",	pid="wander0",	args={key="moveMode", val=WALK}},
	{id="walkmove",	name="TreeSocket",		pid="wander0",	args={slot=MOVE}},
	{id="wait0",	name="Wait",			pid="wander"}
}
addAiTemplate("escortWalk", escortWalk)

escortRun = {
	{id="wander",	name="Selector",		pid="none"},
	{id="wander0",	name="Sequence",		pid="wander"},
	{id="runset",	name="WriteBlackboard",	pid="wander0",	args={key="moveMode", val=RUN}},
	{id="runmove",	name="TreeSocket",		pid="wander0",	args={slot=MOVE}},
	{id="wait0",	name="Wait",			pid="wander"}
}
addAiTemplate("escortRun", escortRun)

-- this is for mobs that stand still always
idleStationary = {
	{id="wait",	name="Wait",	pid="none"}
}
addAiTemplate("idleStationary", idleStationary)

rootNoAttack = {
	{id="root",	name="Selector",	pid="none"},
	{id="idle",	name="TreeSocket",	pid="root",	args={slot=IDLE}}
}
addAiTemplate("rootNoAttack", rootNoAttack)
