idleDefault = {
	{id="3154429038",	name="SequenceSpace",	pid="none"},
	{id="1336571094",	name="Wait",	pid="3154429038",	args={duration=5.0}}}
addAiTemplate("idleDefault", idleDefault)

moveDefault = {
	{id="368441587",	name="SequenceSpace",	pid="none"},
	{id="3848206840",	name="IfSpace",	pid="368441587"},
	{id="539785228",	name="CheckDestination",	pid="3848206840",	args={condition=0.0}},
	{id="1331314218",	name="FindNextPosition",	pid="368441587"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="1234597753",	name="SequenceSpace",	pid="none"},
	{id="1729558672",	name="TreeSocketSpace",	pid="1234597753",	args={slot=MOVESPACE}},
	{id="869798738",	name="TreeSocketSpace",	pid="1234597753",	args={slot=NONESPACE}}}
addAiTemplate("rootDefault", rootDefault)

