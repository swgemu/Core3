idleStatic = {
	{id="159935104",	name="Wait",	pid="none",	args={duration=-1.0}}}
addAiTemplate("idleStatic", idleStatic)

rootStatic = {
	{id="1049923712",	name="Selector",	pid="none"},
	{id="932061527",	name="TreeSocket",	pid="1049923712",	args={slot=IDLE}}}
addAiTemplate("rootStatic", rootStatic)

wanderStatic = {
	{id="3910073142",	name="Selector",	pid="none"},
	{id="446627907",	name="Sequence",	pid="3910073142"},
	{id="2664305160",	name="WriteBlackboard",	pid="446627907",	args={key="moveMode", val=WALK}},
	{id="3605604170",	name="TreeSocket",	pid="446627907",	args={slot=MOVE}},
	{id="737159031",	name="Wait",	pid="3910073142",	args={duration=10.0}}}
addAiTemplate("wanderStatic", wanderStatic)

