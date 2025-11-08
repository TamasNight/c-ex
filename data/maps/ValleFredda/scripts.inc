ValleFredda_MapScripts::
	.byte 0

ValleFredda_EventScript_LittleBoy::
	msgbox ValleFredda_Text_ImNotVeryTall, MSGBOX_NPC
	end

ValleFredda_EventScript_RouteSignOldale::
	msgbox ValleFredda_Text_RouteSignOldale, MSGBOX_SIGN
	end

ValleFredda_EventScript_RouteSignPetalburg::
	msgbox ValleFredda_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

ValleFredda_EventScript_Boy::
	msgbox ValleFredda_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

ValleFredda_EventScript_Calvin::
	trainerbattle_single TRAINER_CALVIN_1, ValleFredda_Text_CalvinIntro, ValleFredda_Text_CalvinDefeated, ValleFredda_EventScript_CalvinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, ValleFredda_EventScript_CalvinRematch
	setvar VAR_0x8004, TRAINER_CALVIN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, ValleFredda_EventScript_CalvinTryRegister
	msgbox ValleFredda_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

ValleFredda_EventScript_CalvinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, ValleFredda_EventScript_CalvinRegisterMatchCall
	release
	end

ValleFredda_EventScript_CalvinRegisterMatchCall::
	msgbox ValleFredda_Text_CalvinRegisterShort, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

ValleFredda_EventScript_CalvinTryRegister::
	goto_if_set FLAG_HAS_MATCH_CALL, ValleFredda_EventScript_CalvinRegister
	msgbox ValleFredda_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

ValleFredda_EventScript_CalvinRegister::
	msgbox ValleFredda_Text_CalvinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

ValleFredda_EventScript_CalvinRematch::
	trainerbattle_rematch TRAINER_CALVIN_1, ValleFredda_Text_CalvinRematchIntro, ValleFredda_Text_CalvinRematchDefeated
	msgbox ValleFredda_Text_CalvinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

ValleFredda_EventScript_Rick::
	trainerbattle_single TRAINER_RICK, ValleFredda_Text_RickIntro, ValleFredda_Text_RickDefeated
	msgbox ValleFredda_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

ValleFredda_EventScript_Tiana::
	trainerbattle_single TRAINER_TIANA, ValleFredda_Text_TianaIntro, ValleFredda_Text_TianaDefeated
	msgbox ValleFredda_Text_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

ValleFredda_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN, ValleFredda_Text_AllenIntro, ValleFredda_Text_AllenDefeated
	msgbox ValleFredda_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

ValleFredda_Text_WatchMeCatchPokemon:
	.string "WALLY: {PLAYER}…\n"
	.string "POKéMON hide in tall grass like this,\l"
	.string "don't they?\p"
	.string "Please watch me and see if I can\n"
	.string "catch one properly.\p"
	.string "…Whoa!$"

ValleFredda_Text_WallyIDidIt:
	.string "WALLY: I did it… It's my…\n"
	.string "My POKéMON!$"

ValleFredda_Text_LetsGoBack:
	.string "{PLAYER}, thank you!\n"
	.string "Let's go back to the GYM!$"

ValleFredda_Text_ImNotVeryTall:
	.string "I'm…not very tall, so I sink right\n"
	.string "into tall grass.\p"
	.string "The grass goes up my nose and…\n"
	.string "Fwafwafwafwafwa…\p"
	.string "Fwatchoo!$"

ValleFredda_Text_CatchWholeBunchOfPokemon:
	.string "I'm going to catch a whole bunch of\n"
	.string "POKéMON!$"

ValleFredda_Text_RouteSignOldale:
	.string "ROUTE 102\n"
	.string "{RIGHT_ARROW} OLDALE TOWN$"

ValleFredda_Text_RouteSignPetalburg:
	.string "ROUTE 102\n"
	.string "{LEFT_ARROW} PETALBURG CITY$"
