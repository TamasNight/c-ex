ValleBassa_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ValleBassa_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, ValleBassa_OnLoad
	.byte 0

ValleBassa_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	end

ValleBassa_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, ValleBassa_EventScript_OpenAlteringCave
	end

ValleBassa_EventScript_OpenAlteringCave::
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, FALSE
	return

ValleBassa_EventScript_Rival::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, ValleBassa_EventScript_RivalMay
	goto_if_eq VAR_RESULT, FEMALE, ValleBassa_EventScript_RivalBrendan
	end

ValleBassa_EventScript_RivalMay::
	msgbox ValleBassa_Text_MayValleBassaPokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_VALLE_BASSA_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_VALLE_BASSA_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_VALLE_BASSA_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox ValleBassa_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, ValleBassa_EventScript_StartMayBattleTreecko
	case 1, ValleBassa_EventScript_StartMayBattleTorchic
	case 2, ValleBassa_EventScript_StartMayBattleMudkip
	end

ValleBassa_EventScript_RivalBrendan::
	msgbox ValleBassa_Text_BrendanValleBassaPokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	applymovement LOCALID_VALLE_BASSA_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_VALLE_BASSA_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_VALLE_BASSA_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox ValleBassa_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, ValleBassa_EventScript_StartBrendanBattleTreecko
	case 1, ValleBassa_EventScript_StartBrendanBattleTorchic
	case 2, ValleBassa_EventScript_StartBrendanBattleMudkip
	end

ValleBassa_EventScript_StartMayBattleTreecko::
	trainerbattle_no_intro TRAINER_MAY_VALLE_BASSA_TREECKO, ValleBassa_Text_MayDefeated
	goto ValleBassa_EventScript_AfterMayBattle
	end

ValleBassa_EventScript_StartMayBattleTorchic::
	trainerbattle_no_intro TRAINER_MAY_VALLE_BASSA_TORCHIC, ValleBassa_Text_MayDefeated
	goto ValleBassa_EventScript_AfterMayBattle
	end

ValleBassa_EventScript_StartMayBattleMudkip::
	trainerbattle_no_intro TRAINER_MAY_VALLE_BASSA_MUDKIP, ValleBassa_Text_MayDefeated
	goto ValleBassa_EventScript_AfterMayBattle
	end

ValleBassa_EventScript_StartBrendanBattleTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_VALLE_BASSA_TREECKO, ValleBassa_Text_BrendanDefeated
	goto ValleBassa_EventScript_AfterBrendanBattle
	end

ValleBassa_EventScript_StartBrendanBattleTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_VALLE_BASSA_TORCHIC, ValleBassa_Text_BrendanDefeated
	goto ValleBassa_EventScript_AfterBrendanBattle
	end

ValleBassa_EventScript_StartBrendanBattleMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_VALLE_BASSA_MUDKIP, ValleBassa_Text_BrendanDefeated
	goto ValleBassa_EventScript_AfterBrendanBattle
	end

ValleBassa_EventScript_AfterMayBattle::
	msgbox ValleBassa_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto ValleBassa_EventScript_RivalExit
	end

ValleBassa_EventScript_AfterBrendanBattle::
	msgbox ValleBassa_Text_BrendanTimeToHeadBack, MSGBOX_DEFAULT
	goto ValleBassa_EventScript_RivalExit
	end

ValleBassa_EventScript_RivalExit::
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, ValleBassa_EventScript_RivalExitFacingSouth
	case DIR_NORTH, ValleBassa_EventScript_RivalExitFacingNorth
	case DIR_WEST, ValleBassa_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, ValleBassa_EventScript_RivalExitFacingEastOrWest
	end

ValleBassa_EventScript_RivalExitFacingNorth::
	applymovement LOCALID_PLAYER, ValleBassa_Movement_WatchRivalExitFacingNorth
	applymovement LOCALID_VALLE_BASSA_RIVAL, ValleBassa_Movement_RivalExitFacingNorth1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_VALLE_BASSA_RIVAL, ValleBassa_Movement_RivalExitFacingNorth2
	waitmovement 0
	goto ValleBassa_EventScript_RivalEnd
	end

ValleBassa_EventScript_RivalExitFacingEastOrWest::
	applymovement LOCALID_PLAYER, ValleBassa_Movement_WatchRivalExitFacingEastOrWest
	applymovement LOCALID_VALLE_BASSA_RIVAL, ValleBassa_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_VALLE_BASSA_RIVAL, ValleBassa_Movement_RivalExit2
	waitmovement 0
	goto ValleBassa_EventScript_RivalEnd
	end

ValleBassa_EventScript_RivalExitFacingSouth::
	applymovement LOCALID_VALLE_BASSA_RIVAL, ValleBassa_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_VALLE_BASSA_RIVAL, ValleBassa_Movement_RivalExit2
	waitmovement 0
	goto ValleBassa_EventScript_RivalEnd
	end

ValleBassa_EventScript_RivalEnd::
	removeobject LOCALID_VALLE_BASSA_RIVAL
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_VALLE_BASSA
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_LUNGAVALLE_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

ValleBassa_Movement_RivalExitFacingNorth1:
	walk_left
	walk_down
	step_end

ValleBassa_Movement_RivalExitFacingNorth2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

ValleBassa_Movement_WatchRivalExitFacingNorth:
	delay_16
	delay_4
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

ValleBassa_Movement_RivalExit1:
	walk_down
	step_end

ValleBassa_Movement_RivalExit2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

ValleBassa_Movement_WatchRivalExitFacingEastOrWest:
	delay_16
	walk_in_place_faster_down
	step_end

ValleBassa_EventScript_Boy::
	msgbox ValleBassa_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

ValleBassa_EventScript_Man::
	msgbox ValleBassa_Text_ShortcutToOldale, MSGBOX_NPC
	end

ValleBassa_EventScript_RouteSign::
	msgbox ValleBassa_Text_RouteSign, MSGBOX_SIGN
	end

ValleBassa_EventScript_Daisy::
	trainerbattle_single TRAINER_DAISY, ValleBassa_Text_DaisyIntro, ValleBassa_Text_DaisyDefeated
	msgbox ValleBassa_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, ValleBassa_Text_AmyIntro, ValleBassa_Text_AmyDefeated, ValleBassa_Text_AmyNotEnoughPokemon, ValleFredda_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, ValleFredda_EventScript_AmyRematch
	msgbox ValleBassa_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

ValleFredda_EventScript_AmyRegisterMatchCallAfterBattle::
	msgbox ValleBassa_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

ValleFredda_EventScript_AmyRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, ValleBassa_Text_AmyRematchIntro, ValleBassa_Text_AmyRematchDefeated, ValleBassa_Text_AmyRematchNotEnoughPokemon
	msgbox ValleBassa_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Liv::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, ValleBassa_Text_LivIntro, ValleBassa_Text_LivDefeated, ValleBassa_Text_LivNotEnoughPokemon, ValleFredda_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, ValleFredda_EventScript_LivRematch
	msgbox ValleBassa_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

ValleFredda_EventScript_LivRegisterMatchCallAfterBattle::
	msgbox ValleBassa_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

ValleFredda_EventScript_LivRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, ValleBassa_Text_LivRematchIntro, ValleBassa_Text_LivRematchDefeated, ValleBassa_Text_LivRematchNotEnoughPokemon
	msgbox ValleBassa_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Andrew::
	trainerbattle_single TRAINER_ANDREW, ValleBassa_Text_AndrewIntro, ValleBassa_Text_AndrewDefeated
	msgbox ValleBassa_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Miguel::
	trainerbattle_single TRAINER_MIGUEL_1, ValleBassa_Text_MiguelIntro, ValleBassa_Text_MiguelDefeated, ValleFredda_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, ValleBassa_EventScript_MiguelRematch
	msgbox ValleBassa_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

ValleFredda_EventScript_MiguelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox ValleBassa_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

ValleBassa_EventScript_MiguelRematch::
	trainerbattle_rematch TRAINER_MIGUEL_1, ValleBassa_Text_MiguelRematchIntro, ValleBassa_Text_MiguelRematchDefeated
	msgbox ValleBassa_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Marcos::
	trainerbattle_single TRAINER_MARCOS, ValleBassa_Text_MarcosIntro, ValleBassa_Text_MarcosDefeated
	msgbox ValleBassa_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Rhett::
	trainerbattle_single TRAINER_RHETT, ValleBassa_Text_RhettIntro, ValleBassa_Text_RhettDefeated
	msgbox ValleBassa_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Pete::
	trainerbattle_single TRAINER_PETE, ValleBassa_Text_PeteIntro, ValleBassa_Text_PeteDefeated
	msgbox ValleBassa_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_EventScript_Isabelle::
	trainerbattle_single TRAINER_ISABELLE, ValleBassa_Text_IsabelleIntro, ValleBassa_Text_IsabelleDefeated
	msgbox ValleBassa_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

ValleBassa_Text_MayValleBassaPokemon:
	.string "MAY: Let's see… The POKéMON found\n"
	.string "on ROUTE 103 include…$"

ValleBassa_Text_MayLetsBattle:
	.string "Oh, hi, {PLAYER}{KUN}!\p"
	.string "…Oh, I see, my dad gave you\n"
	.string "a POKéMON as a gift.\p"
	.string "Since we're here, let's have a quick\n"
	.string "battle!\p"
	.string "I'll give you a taste of what being\n"
	.string "a TRAINER is like.$"

ValleBassa_Text_MayDefeated:
	.string "Wow! That's great!\n"
	.string "{PLAYER}{KUN}, you're pretty good!$"

ValleBassa_Text_MayTimeToHeadBack:
	.string "MAY: I think I know why my dad has\n"
	.string "an eye out for you now.\p"
	.string "I mean, you just got that POKéMON,\n"
	.string "but it already likes you.\p"
	.string "You might be able to befriend any\n"
	.string "kind of POKéMON easily.\p"
	.string "Well, it's time to head back to\n"
	.string "the LAB.$"

ValleBassa_Text_BrendanValleBassaPokemon:
	.string "BRENDAN: Okay, so it's this one and\n"
	.string "that one that live on ROUTE 103…$"

ValleBassa_Text_BrendanLetsBattle:
	.string "Hey, it's {PLAYER}!\p"
	.string "…Oh, yeah, Dad gave you a POKéMON.\p"
	.string "Since we're here, how about a little\n"
	.string "battle?\p"
	.string "I'll teach you what being a TRAINER's\n"
	.string "about!$"

ValleBassa_Text_BrendanDefeated:
	.string "Huh, {PLAYER}, you're not too shabby.$"

ValleBassa_Text_BrendanTimeToHeadBack:
	.string "BRENDAN: I think I get it.\n"
	.string "I think I know why my dad has his eye\l"
	.string "out for you now.\p"
	.string "Look, your POKéMON already likes you,\n"
	.string "even though you just got it.\p"
	.string "{PLAYER}, I get the feeling that you\n"
	.string "could befriend any POKéMON with ease.\p"
	.string "We should head back to the LAB.$"

ValleBassa_Text_ShouldHaveBroughtPotion:
	.string "My POKéMON is staggeringly tired…\n"
	.string "I should have brought a POTION…$"

ValleBassa_Text_ShortcutToOldale:
	.string "If you cross the sea from here,\n"
	.string "it'll be a shortcut to OLDALE TOWN.\p"
	.string "Fufufu, that's useful, isn't it?$"

ValleBassa_Text_RouteSign:
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLDALE TOWN$"

