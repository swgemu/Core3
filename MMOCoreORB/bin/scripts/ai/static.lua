idleStatic = {
	{id="868845731",	name="Selector",	pid="none"},
	{id="160531963",	name="Sequence",	pid="868845731"},
	{id="3886503512",	name="If",	pid="160531963"},
	{id="630408355",	name="CheckMovementState",	pid="3886503512",	args={condition=LEASHING}},
	{id="3416313250",	name="WriteBlackboard",	pid="160531963",	args={key="moveMode", val=RUN}},
	{id="159935104",	name="Wait",	pid="868845731",	args={duration=-1.0}}}
addAiTemplate("idleStatic", idleStatic)

rootStatic = {
	{id="1049923712",	name="Selector",	pid="none"},
	{id="932061527",	name="TreeSocket",	pid="1049923712",	args={slot=IDLE}}}
addAiTemplate("rootStatic", rootStatic)

wanderStatic = {
	{id="2998071590",	name="Sequence",	pid="none"},
	{id="1736612732",	name="Sequence",	pid="2998071590"},
	{id="4240569526",	name="If",	pid="1736612732"},
	{id="2201117244",	name="CheckMovementState",	pid="4240569526",	args={condition=LEASHING}},
	{id="1848176669",	name="WriteBlackboard",	pid="1736612732",	args={key="moveMode", val=RUN}},
	{id="4224953071",	name="TreeSocket",	pid="1736612732",	args={slot=MOVE}},
	{id="3910073142",	name="Selector",	pid="2998071590"},
	{id="446627907",	name="Sequence",	pid="3910073142"},
	{id="2664305160",	name="WriteBlackboard",	pid="446627907",	args={key="moveMode", val=WALK}},
	{id="3605604170",	name="TreeSocket",	pid="446627907",	args={slot=MOVE}},
	{id="1411814469",	name="Not",	pid="3910073142"},
	{id="3866536807",	name="If",	pid="1411814469"},
	{id="4198924774",	name="CheckIsHome",	pid="3866536807"},
	{id="737159031",	name="Wait",	pid="3910073142",	args={duration=10.0}}}
addAiTemplate("wanderStatic", wanderStatic)

