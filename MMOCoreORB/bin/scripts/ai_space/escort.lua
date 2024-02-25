idleEscort = {
	{id="3878147956",	name="SequenceSpace",	pid="none"},
	{id="4233020465",	name="NotSpace",	pid="3878147956"},
	{id="3024864836",	name="IfSpace",	pid="4233020465"},
	{id="1614536018",	name="CheckMovementState",	pid="3024864836",	args={condition=FOLLOWING}},
	{id="3826170193",	name="NotSpace",	pid="3878147956"},
	{id="1569932203",	name="IfSpace",	pid="3826170193"},
	{id="1062834130",	name="CheckHasPatrol",	pid="1569932203"},
	{id="1111847443",	name="GeneratePatrol",	pid="3878147956",	args={distFromHome=256.0, numPoints=5}}}
addAiTemplate("idleEscort", idleEscort)

moveEscort = {
	{id="3162096793",	name="SequenceSpace",	pid="none"},
	{id="3119158273",	name="IfSpace",	pid="3162096793"},
	{id="311662512",	name="CheckDestination",	pid="3119158273"},
	{id="4219492080",	name="AlwaysFailSpace",	pid="3162096793"},
	{id="145123387",	name="FindNextPosition",	pid="4219492080"}}
addAiTemplate("moveEscort", moveEscort)

rootEscort = {
	{id="763915188",	name="SelectorSpace",	pid="none"},
	{id="2765964998",	name="TreeSocketSpace",	pid="763915188",	args={slot=MOVESPACE}},
	{id="3409670866",	name="TreeSocketSpace",	pid="763915188",	args={slot=IDLESPACE}}}
addAiTemplate("rootEscort", rootEscort)

