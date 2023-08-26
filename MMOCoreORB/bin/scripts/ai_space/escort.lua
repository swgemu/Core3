idleEscort = {
	{id="1518537252",	name="SequenceSpace",	pid="none"},
	{id="3893125218",	name="NotSpace",	pid="1518537252"},
	{id="2796352310",	name="IfSpace",	pid="3893125218"},
	{id="3211654910",	name="CheckMovementState",	pid="2796352310",	args={condition=FOLLOWING}},
	{id="325001551",	name="NotSpace",	pid="1518537252"},
	{id="2647026017",	name="IfSpace",	pid="325001551"},
	{id="3340069447",	name="CheckHasPatrol",	pid="2647026017"},
	{id="1857803864",	name="GeneratePatrol",	pid="1518537252",	args={distFromHome=0.0, numPoints=0}}}
addAiTemplate("idleEscort", idleEscort)

moveEscort = {
	{id="884857570",	name="SequenceSpace",	pid="none"},
	{id="3779780954",	name="IfSpace",	pid="884857570"},
	{id="1318511574",	name="CheckDestination",	pid="3779780954"},
	{id="3906717712",	name="AlwaysFailSpace",	pid="884857570"},
	{id="1120284701",	name="FindNextPosition",	pid="3906717712"}}
addAiTemplate("moveEscort", moveEscort)

rootEscort = {
	{id="3361030279",	name="SelectorSpace",	pid="none"},
	{id="2451338969",	name="TreeSocketSpace",	pid="3361030279",	args={slot=MOVESPACE}},
	{id="2213142081",	name="TreeSocketSpace",	pid="3361030279",	args={slot=IDLESPACE}}}
addAiTemplate("rootEscort", rootEscort)

