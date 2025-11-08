ValleFredda_MapScripts::
	.byte 0

ValleFredda_EventScript_PlayerPositioningLeft::
    lockall
	applymovement LOCALID_PLAYER, ValleFredda_Movement_PlayerPositioningLeft
	goto ValleFredda_EventScript_Saverio

ValleFredda_EventScript_PlayerPositioningLeft2::
    lockall
	applymovement LOCALID_PLAYER, ValleFredda_Movement_PlayerPositioningLeft2
	goto ValleFredda_EventScript_Saverio

ValleFredda_EventScript_PlayerPositioningRight::
    lockall
	applymovement LOCALID_PLAYER, ValleFredda_Movement_PlayerPositioningRight
	goto ValleFredda_EventScript_Saverio

ValleFredda_EventScript_PlayerPositioningCenter::
    lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown2
	goto ValleFredda_EventScript_Saverio

ValleFredda_EventScript_Saverio::
    waitmovement 0
	msgbox ValleFredda_Text_SaverioIntro, MSGBOX_DEFAULT
	msgbox ValleFredda_Text_PlayerIntro, MSGBOX_DEFAULT
	msgbox ValleFredda_Text_SaverioBeforeGiveBond, MSGBOX_DEFAULT
	closemessage
	delay 16
	giveitem ITEM_BOND, 5
	msgbox ValleFredda_Text_SaverioExplainsBond, MSGBOX_DEFAULT
	closemessage
    delay 16
	msgbox ValleFredda_Text_FirstLesson, MSGBOX_DEFAULT
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_SAVERIO_1, ValleFredda_Text_SaverioDefeated
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ValleFredda_EventScript_SaverioLessonEnd
	msgbox ValleFredda_Text_SaverioPostBattlePlayerLost, MSGBOX_DEFAULT
	goto ValleFredda_EventScript_SaverioLessonEnd

ValleFredda_EventScript_SaverioLessonEnd::
    msgbox ValleFredda_Text_SaverioHealingParty, MSGBOX_DEFAULT
    closemessage
    call Common_EventScript_OutOfCenterPartyHeal
    msgbox ValleFredda_Text_SaverioNextQuest, MSGBOX_DEFAULT
    closemessage
    delay 16
    applymovement LOCALID_SAVERIO_VALLE_FREDDA, Common_Movement_WalkDown2
    waitmovement 0
    applymovement LOCALID_RAPIDASH_VALLE_FREDDA, Common_Movement_WalkDown6
    applymovement LOCALID_SAVERIO_VALLE_FREDDA, Common_Movement_WalkDown6
    waitmovement 0
    setvar VAR_KNIGHT_WAY_STATE, 3
    subquestmenu QUEST_MENU_COMPLETE_QUEST QUEST_KNIGHT_WAY 1
    subquestmenu QUEST_MENU_COMPLETE_QUEST QUEST_KNIGHT_WAY 2
    updatequestmsg QUEST_KNIGHT_WAY
    removeobject LOCALID_SAVERIO_VALLE_FREDDA
    removeobject LOCALID_RAPIDASH_VALLE_FREDDA
	end

ValleFredda_EventScript_RouteSign::
	msgbox ValleFredda_Text_RouteSign, MSGBOX_SIGN
	end

ValleFredda_EventScript_Boy::
	msgbox ValleFredda_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

ValleFredda_EventScript_Guido::
	trainerbattle_single TRAINER_GUIDO_1, ValleFredda_Text_GuidoIntro, ValleFredda_Text_GuidoDefeated
	msgbox ValleFredda_Text_GuidoPostBattle, MSGBOX_NPC
	release
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

ValleFredda_Text_CatchWholeBunchOfPokemon:
	.string "I'm going to catch a whole bunch of\n"
	.string "POKéMON!$"

ValleFredda_Text_RouteSign:
	.string "Valle Fredda\n"
	.string "{DOWN_ARROW} Locanda del Santo\l"
	.string "{DOWN_ARROW} Valle di Pretoria$"

ValleFredda_Text_SaverioIntro:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: Before we go further, you’ll\n"
	.string "need to learn how to defend yourself.\p"
	.string "The wilds of Iria can be dangerous, even\n"
	.string "for those who think they are ready.$"

ValleFredda_Text_PlayerIntro:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: I'll be ready, teach me!$"

ValleFredda_Text_SaverioBeforeGiveBond:
	.string "{COLOR}{BLUE}Saverio{COLOR}{02}: First, you need to know how to\n"
	.string "find new companions. Here, take these.$"

ValleFredda_Text_SaverioExplainsBond:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: They’re called {COLOR}{RED}Legami{COLOR}{02}, magical\n"
	.string "items empowered by runes of loyalty.\l"
	.string "Use them to bind Pokémon to you, making\l"
	.string "them your allies.$"

ValleFredda_Text_FirstLesson:
	.string "{COLOR}{BLUE}Saverio{COLOR}{02}: Now let's move on to the most\n"
	.string "important matters: during the journey,\l"
	.string "we may encounter bandits and other\l"
	.string "threats, so you must be prepared and\l"
	.string "capable of fighting.\p"
    .string "Let's start right away with the first\n"
	.string "lesson: each Pokémon has a {COLOR}{GREEN}class\l"
	.string "ability{COLOR}{02}. Learn how to make the most of\l"
	.string "it to dominate the battlefield.$"

ValleFredda_Text_SaverioHealingParty:
	.string "{COLOR}{BLUE}Saverio{COLOR}{02}: Great battle, you still have a\n"
    .string "lot to learn but you're on the right\l"
    .string "track. Now let me heal your Pokémon.$"


ValleFredda_Text_SaverioNextQuest:
	.string "{COLOR}{BLUE}Saverio{COLOR}{02}: Our next destination will be\n"
    .string "the tavern at the bottom of the valley.\l"
    .string "I'll wait for you there. I want you to\l"
    .string "learn to be independent right away.\p"
	.string "Practice with {COLOR}{RED}Legami{COLOR}{02} on your way to the\n"
    .string "tavern. If you catch some good\l"
    .string "Pokémon, I'll reward you.$"


ValleFredda_Movement_PlayerPositioningLeft:
    walk_right
    walk_right
    walk_down
    walk_down
    step_end

ValleFredda_Movement_PlayerPositioningLeft2:
    walk_right
    walk_down
    walk_down
    step_end

ValleFredda_Movement_PlayerPositioningRight:
    walk_left
    walk_down
    walk_down
    step_end






