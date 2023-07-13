idleDefault = {
	{id="3154429038",	name="SequenceSpace",	pid="none"},
	{id="3521391142",	name="NotSpace",	pid="3154429038"},
	{id="3390840483",	name="IfSpace",	pid="3521391142"},
	{id="2770349133",	name="CheckHasPatrol",	pid="3390840483"},
	{id="3954328391",	name="GeneratePatrol",	pid="3154429038",	args={distFromHome=100.0, numPoints=5}}}
addAiTemplate("idleDefault", idleDefault)

moveDefault = {
	{id="368441587",	name="SequenceSpace",	pid="none"},
	{id="3848206840",	name="IfSpace",	pid="368441587"},
	{id="539785228",	name="CheckDestination",	pid="3848206840"},
	{id="1331314218",	name="FindNextPosition",	pid="368441587"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="2051740559",	name="SelectorSpace",	pid="none"},
	{id="1729558672",	name="TreeSocketSpace",	pid="2051740559",	args={slot=MOVESPACE}},
	{id="869798738",	name="TreeSocketSpace",	pid="2051740559",	args={slot=IDLESPACE}}}
addAiTemplate("rootDefault", rootDefault)

