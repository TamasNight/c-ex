Common_EventScript_FindItem::
    applymovement VAR_LAST_TALKED, Common_Movement_FaceUp
	waitmovement 0
	callnative GetItemBallIdAndAmountFromTemplate
	finditem VAR_RESULT VAR_0x8009
	delay 10
	removeobject VAR_LAST_TALKED
	end
