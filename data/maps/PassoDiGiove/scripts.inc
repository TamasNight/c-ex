PassoDiGiove_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PassoDiGiove_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, PassoDiGiove_OnTransition
	.byte 0

PassoDiGiove_OnFrame:
	map_script_2 VAR_BOARD_BRINEY_BOAT_STATE, 1, PassoDiGiove_EventScript_StartSailToDewford
	.2byte 0

PassoDiGiove_EventScript_StartSailToDewford::
	lockall
	goto PassoDiGiove_EventScript_SailToDewford
	end

PassoDiGiove_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call PassoDiGiove_EventScript_TrySetRivalPos
	call PassoDiGiove_EventScript_ShowOrHideWhiteHerbFlorist
	end

PassoDiGiove_EventScript_ShowOrHideWhiteHerbFlorist::
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, PassoDiGiove_EventScript_HideWhiteHerbFlorist
	goto_if_unset FLAG_BADGE03_GET, PassoDiGiove_EventScript_HideWhiteHerbFlorist
	clearflag FLAG_HIDE_PASSO_DI_GIOVE_WHITE_HERB_FLORIST
	return

PassoDiGiove_EventScript_HideWhiteHerbFlorist::
	setflag FLAG_HIDE_PASSO_DI_GIOVE_WHITE_HERB_FLORIST
	return

PassoDiGiove_EventScript_TrySetRivalPos::
	goto_if_ge VAR_BOARD_BRINEY_BOAT_STATE, 1, PassoDiGiove_EventScript_DontSetRivalPos
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, PassoDiGiove_EventScript_DontSetRivalPos
	goto_if_unset FLAG_REGISTER_RIVAL_POKENAV, PassoDiGiove_EventScript_DontSetRivalPos
	setobjectxyperm LOCALID_PASSO_DI_GIOVE_RIVAL, 17, 52
	return

PassoDiGiove_EventScript_DontSetRivalPos::
	return

PassoDiGiove_EventScript_Rival::
	lockall
	setvar VAR_0x8008, 1
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto PassoDiGiove_EventScript_RivalEncounter

PassoDiGiove_EventScript_RivalTrigger::
	lockall
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_PASSO_DI_GIOVE_STATE, 2
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 10
	addobject LOCALID_PASSO_DI_GIOVE_RIVAL
	clearflag FLAG_HIDE_PASSO_DI_GIOVE_RIVAL
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_PlayerBackUp
	waitmovement 0
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, PassoDiGiove_Movement_RivalExitBrineysCottage
	waitmovement 0
	delay 20
	setvar VAR_0x8008, 0
	call RustboroCity_EventScript_PlayRivalMusic
	playse SE_PIN
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	goto PassoDiGiove_EventScript_RivalEncounter

@ Unused, shares script with Rustboro encounter instead
PassoDiGiove_EventScript_PlayRivalMusic::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PassoDiGiove_EventScript_PlayMayMusic
	goto_if_eq VAR_RESULT, FEMALE, PassoDiGiove_EventScript_PlayBrendanMusic
	return

PassoDiGiove_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

PassoDiGiove_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

PassoDiGiove_EventScript_RivalEncounter::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PassoDiGiove_EventScript_MayEncounter
	goto_if_eq VAR_RESULT, FEMALE, PassoDiGiove_EventScript_BrendanEncounter
	end

PassoDiGiove_EventScript_MayEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE, PassoDiGiove_EventScript_MayDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, PassoDiGiove_EventScript_MayAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox PassoDiGiove_Text_MayWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox PassoDiGiove_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_PlayerFaceRival
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, PassoDiGiove_Movement_RivalWalkSlowLeft
	msgbox PassoDiGiove_Text_MayHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, PassoDiGiove_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_PASSO_DI_GIOVE_RIVAL
	msgbox PassoDiGiove_Text_MayMinesDecentLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PassoDiGiove_EventScript_BattleMay
	msgbox PassoDiGiove_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	call PassoDiGiove_EventScript_RestoreMusic
	releaseall
	end

PassoDiGiove_Movement_RivalWalkSlowLeft:
	walk_slow_left
	step_end

PassoDiGiove_Movement_RivalApproachPlayer:
	walk_down
	face_right
	step_end

PassoDiGiove_Movement_PlayerFaceRival:
	delay_4
	walk_in_place_faster_left
	step_end

PassoDiGiove_EventScript_MayAskToBattle::
	msgbox PassoDiGiove_Text_MayLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PassoDiGiove_EventScript_BattleMay
	msgbox PassoDiGiove_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	releaseall
	end

PassoDiGiove_EventScript_BattleMay::
	msgbox PassoDiGiove_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, PassoDiGiove_EventScript_BattleMayTreecko
	case 1, PassoDiGiove_EventScript_BattleMayTorchic
	case 2, PassoDiGiove_EventScript_BattleMayMudkip
	end

PassoDiGiove_EventScript_MayDefeated::
	msgbox PassoDiGiove_Text_MayPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, PassoDiGiove_EventScript_RestoreMusic
	releaseall
	end

PassoDiGiove_EventScript_RestoreMusic::
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

PassoDiGiove_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, PassoDiGiove_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE
	goto PassoDiGiove_EventScript_MayDefeated
	end

PassoDiGiove_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, PassoDiGiove_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE
	goto PassoDiGiove_EventScript_MayDefeated
	end

PassoDiGiove_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, PassoDiGiove_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE
	goto PassoDiGiove_EventScript_MayDefeated
	end

PassoDiGiove_EventScript_BrendanEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE, PassoDiGiove_EventScript_BrendanDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, PassoDiGiove_EventScript_BrendanAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox PassoDiGiove_Text_BrendanWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox PassoDiGiove_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_PlayerFaceRival
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, PassoDiGiove_Movement_RivalWalkSlowLeft
	msgbox PassoDiGiove_Text_BrendanHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_PASSO_DI_GIOVE_RIVAL, PassoDiGiove_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_PASSO_DI_GIOVE_RIVAL
	msgbox PassoDiGiove_Text_BrendanDoingGreatLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PassoDiGiove_EventScript_BattleBrendan
	msgbox PassoDiGiove_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	call PassoDiGiove_EventScript_RestoreMusic
	releaseall
	end

PassoDiGiove_EventScript_BrendanAskToBattle::
	msgbox PassoDiGiove_Text_BrendanLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PassoDiGiove_EventScript_BattleBrendan
	msgbox PassoDiGiove_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	releaseall
	end

PassoDiGiove_EventScript_BattleBrendan::
	msgbox PassoDiGiove_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, PassoDiGiove_EventScript_BattleBrendanTreecko
	case 1, PassoDiGiove_EventScript_BattleBrendanTorchic
	case 2, PassoDiGiove_EventScript_BattleBrendanMudkip
	end

PassoDiGiove_EventScript_BrendanDefeated::
	msgbox PassoDiGiove_Text_BrendanPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, PassoDiGiove_EventScript_RestoreMusic
	releaseall
	end

PassoDiGiove_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, PassoDiGiove_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE
	goto PassoDiGiove_EventScript_BrendanDefeated
	end

PassoDiGiove_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, PassoDiGiove_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE
	goto PassoDiGiove_EventScript_BrendanDefeated
	end

PassoDiGiove_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, PassoDiGiove_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_PASSO_DI_GIOVE
	goto PassoDiGiove_EventScript_BrendanDefeated
	end

PassoDiGiove_Movement_PlayerBackUp:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

PassoDiGiove_Movement_RivalExitBrineysCottage:
	walk_down
	step_end

PassoDiGiove_EventScript_ExpertF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHESTO_BERRY_PASSO_DI_GIOVE, PassoDiGiove_EventScript_ReceivedBerry
	msgbox PassoDiGiove_Text_PlantBerriesInSoilTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_CHESTO_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHESTO_BERRY_PASSO_DI_GIOVE
	msgbox PassoDiGiove_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_ReceivedBerry::
	msgbox PassoDiGiove_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_WhiteHerbFlorist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WHITE_HERB, PassoDiGiove_EventScript_ReceivedWhiteHerb
	msgbox PassoDiGiove_Text_DontNeedThisTakeIt, MSGBOX_DEFAULT
	giveitem ITEM_WHITE_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WHITE_HERB
	release
	end

PassoDiGiove_EventScript_ReceivedWhiteHerb::
	msgbox PassoDiGiove_Text_FlowerShopSellingSaplings, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_Girl1::
	msgbox PassoDiGiove_Text_BrineyLivesInSeasideCottage, MSGBOX_NPC
	end

PassoDiGiove_EventScript_BugCatcher::
	msgbox PassoDiGiove_Text_WhatsItLikeAtBottomOfSea, MSGBOX_SIGN
	end

PassoDiGiove_EventScript_BrineysCottageSign::
	msgbox PassoDiGiove_Text_MrBrineysCottage, MSGBOX_SIGN
	end

PassoDiGiove_EventScript_RouteSignPetalburg::
	msgbox PassoDiGiove_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

PassoDiGiove_EventScript_RouteSignRustboro::
	msgbox PassoDiGiove_Text_RouteSignRustboro, MSGBOX_SIGN
	end

PassoDiGiove_EventScript_FlowerShopSign::
	msgbox PassoDiGiove_Text_PrettyPetalFlowShop, MSGBOX_SIGN
	end

PassoDiGiove_EventScript_TrainerTipsDoubleBattles::
	msgbox PassoDiGiove_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
	end

PassoDiGiove_EventScript_Boy1::
	msgbox PassoDiGiove_Text_ThrowBallAtWeakenedPokemon, MSGBOX_NPC
	end

PassoDiGiove_EventScript_Woman::
	msgbox PassoDiGiove_Text_OnlyThrowBallAtWildPokemon, MSGBOX_NPC
	end

PassoDiGiove_EventScript_Boy2::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_BULLET_SEED, PassoDiGiove_EventScript_ReceivedBulletSeed
	msgbox PassoDiGiove_Text_LikeFillingMouthWithSeedsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_BULLET_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_BULLET_SEED
	release
	end

PassoDiGiove_EventScript_ReceivedBulletSeed::
	msgbox PassoDiGiove_Text_TMsAreOneTimeUse, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_Girl2::
	msgbox PassoDiGiove_Text_ImNotATrainer, MSGBOX_NPC
	end

PassoDiGiove_EventScript_SailToDewford::
	setobjectsubpriority LOCALID_PASSO_DI_GIOVE_BRINEY, MAP_PASSO_DI_GIOVE, 0
	setobjectsubpriority LOCALID_PLAYER, MAP_PASSO_DI_GIOVE, 0
	applymovement LOCALID_PASSO_DI_GIOVE_BRINEY, PassoDiGiove_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_PASSO_DI_GIOVE_BRINEY
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_PASSO_DI_GIOVE
	call Common_EventScript_PlayBrineysBoatMusic
	goto_if_set FLAG_ENABLE_NORMAN_MATCH_CALL, PassoDiGiove_EventScript_SailToDewfordNoCall
	goto_if_unset FLAG_ENABLE_NORMAN_MATCH_CALL, PassoDiGiove_EventScript_SailToDewfordDadCalls
	end

PassoDiGiove_EventScript_SailToDewfordNoCall::
	applymovement LOCALID_PASSO_DI_GIOVE_BOAT, PassoDiGiove_Movement_SailToDewford
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_SailToDewford
	waitmovement 0
	goto PassoDiGiove_EventScript_ArriveInDewford

PassoDiGiove_EventScript_SailToDewfordDadCalls::
	applymovement LOCALID_PASSO_DI_GIOVE_BOAT, PassoDiGiove_Movement_SailToDewfordBeforeDadCalls
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_SailToDewfordBeforeDadCalls
	waitmovement 0
	pokenavcall PassoDiGiove_Text_DadPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox PassoDiGiove_Text_RegisteredDadInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_NORMAN_MATCH_CALL
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_SailToDewfordAfterDadCalls
	applymovement LOCALID_PASSO_DI_GIOVE_BOAT, PassoDiGiove_Movement_SailToDewfordAfterDadCalls, MAP_PASSO_DI_GIOVE
	waitmovement LOCALID_PASSO_DI_GIOVE_BOAT, MAP_PASSO_DI_GIOVE
	waitmovement 0
	goto PassoDiGiove_EventScript_ArriveInDewford

PassoDiGiove_EventScript_ArriveInDewford::
	delay 50
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_PlayerExitBoat
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat LOCALID_PLAYER, MAP_DEWFORD_TOWN
	applymovement LOCALID_PLAYER, PassoDiGiove_Movement_PlayerMoveForBriney
	waitmovement 0
	setobjectxyperm LOCALID_DEWFORD_BRINEY, 12, 8
	addobject LOCALID_DEWFORD_BRINEY
	setobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN, 0
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	applymovement LOCALID_DEWFORD_BRINEY, PassoDiGiove_Movement_BrineyExitBoat
	waitmovement 0
	addobject LOCALID_DEWFORD_BOAT
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	call Common_EventScript_StopBrineysBoatMusic
	setflag FLAG_HIDE_PASSO_DI_GIOVE_MR_BRINEY_BOAT
	hideobjectat LOCALID_PASSO_DI_GIOVE_BOAT, MAP_PASSO_DI_GIOVE
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectsubpriority LOCALID_PLAYER, MAP_PASSO_DI_GIOVE
	resetobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN
	copyobjectxytoperm LOCALID_DEWFORD_BRINEY
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 0
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, PassoDiGiove_EventScript_DeliverLetterReminder
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, PassoDiGiove_EventScript_LandedInDewford
	end

PassoDiGiove_EventScript_DeliverLetterReminder::
	msgbox PassoDiGiove_Text_LandedInDewfordDeliverLetter, MSGBOX_DEFAULT
	releaseall
	end

PassoDiGiove_EventScript_LandedInDewford::
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
	releaseall
	end

PassoDiGiove_Movement_SailToDewfordBeforeDadCalls:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

PassoDiGiove_Movement_SailToDewfordAfterDadCalls:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

PassoDiGiove_Movement_SailToDewford:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

PassoDiGiove_Movement_PlayerBoardBoat:
	walk_left
	walk_down
	walk_down
	step_end

PassoDiGiove_Movement_PlayerExitBoat:
	walk_down
	step_end

PassoDiGiove_Movement_PlayerMoveForBriney:
	walk_down
	walk_left
	walk_in_place_faster_right
	step_end

PassoDiGiove_Movement_BrineyBoardBoat:
	walk_down
	walk_down
	step_end

PassoDiGiove_Movement_BrineyExitBoat:
	walk_down
	walk_in_place_faster_left
	step_end

PassoDiGiove_EventScript_Ivan::
	trainerbattle_single TRAINER_IVAN, PassoDiGiove_Text_IvanIntro, PassoDiGiove_Text_IvanDefeat
	msgbox PassoDiGiove_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
	end

PassoDiGiove_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY, PassoDiGiove_Text_BillyIntro, PassoDiGiove_Text_BillyDefeat
	msgbox PassoDiGiove_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end

PassoDiGiove_EventScript_Haley::
	trainerbattle_single TRAINER_HALEY_1, PassoDiGiove_Text_HaleyIntro, PassoDiGiove_Text_HaleyDefeat, PassoDiGiove_EventScript_TryRegisterHaleyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PassoDiGiove_EventScript_RematchHaley
	setvar VAR_0x8004, TRAINER_HALEY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PassoDiGiove_EventScript_TryRegisterHaley
	msgbox PassoDiGiove_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_TryRegisterHaleyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PassoDiGiove_EventScript_RegisterHaleyAfterBattle
	release
	end

PassoDiGiove_EventScript_RegisterHaleyAfterBattle::
	msgbox PassoDiGiove_Text_HaleyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

PassoDiGiove_EventScript_TryRegisterHaley::
	goto_if_set FLAG_HAS_MATCH_CALL, PassoDiGiove_EventScript_RegisterHaley
	msgbox PassoDiGiove_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_RegisterHaley::
	msgbox PassoDiGiove_Text_HaleyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

PassoDiGiove_EventScript_RematchHaley::
	trainerbattle_rematch TRAINER_HALEY_1, PassoDiGiove_Text_HaleyRematchIntro, PassoDiGiove_Text_HaleyRematchDefeat
	msgbox PassoDiGiove_Text_HaleyPostRematch, MSGBOX_AUTOCLOSE
	end

PassoDiGiove_EventScript_Winston::
	trainerbattle_single TRAINER_WINSTON_1, PassoDiGiove_Text_WinstonIntro, PassoDiGiove_Text_WinstonDefeat, PassoDiGiove_EventScript_TryRegisterWinstonAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PassoDiGiove_EventScript_RematchWinston
	setvar VAR_0x8004, TRAINER_WINSTON_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PassoDiGiove_EventScript_TryRegisterWinston
	msgbox PassoDiGiove_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_TryRegisterWinstonAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PassoDiGiove_EventScript_RegisterWinstonAfterBattle
	release
	end

PassoDiGiove_EventScript_RegisterWinstonAfterBattle::
	msgbox PassoDiGiove_Text_WinstonRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

PassoDiGiove_EventScript_TryRegisterWinston::
	goto_if_set FLAG_HAS_MATCH_CALL, PassoDiGiove_EventScript_RegisterWinston
	msgbox PassoDiGiove_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_RegisterWinston::
	msgbox PassoDiGiove_Text_WinstonRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

PassoDiGiove_EventScript_RematchWinston::
	trainerbattle_rematch TRAINER_WINSTON_1, PassoDiGiove_Text_WinstonRematchIntro, PassoDiGiove_Text_WinstonRematchDefeat
	msgbox PassoDiGiove_Text_WinstonPostRematch, MSGBOX_AUTOCLOSE
	end

PassoDiGiove_EventScript_Cindy::
	trainerbattle_single TRAINER_CINDY_1, PassoDiGiove_Text_CindyIntro, PassoDiGiove_Text_CindyDefeat, PassoDiGiove_EventScript_TryRegisterCindyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PassoDiGiove_EventScript_RematchCindy
	setvar VAR_0x8004, TRAINER_CINDY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PassoDiGiove_EventScript_TryRegisterCindy
	msgbox PassoDiGiove_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_TryRegisterCindyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PassoDiGiove_EventScript_RegisterCindyAfterBattle
	release
	end

PassoDiGiove_EventScript_RegisterCindyAfterBattle::
	msgbox PassoDiGiove_Text_CindyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

PassoDiGiove_EventScript_TryRegisterCindy::
	goto_if_set FLAG_HAS_MATCH_CALL, PassoDiGiove_EventScript_RegisterCindy
	msgbox PassoDiGiove_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_RegisterCindy::
	msgbox PassoDiGiove_Text_CindyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

PassoDiGiove_EventScript_RematchCindy::
	trainerbattle_rematch TRAINER_CINDY_1, PassoDiGiove_Text_CindyRematchIntro, PassoDiGiove_Text_CindyRematchDefeat
	msgbox PassoDiGiove_Text_CindyPostRematch, MSGBOX_AUTOCLOSE
	end

PassoDiGiove_EventScript_Gina::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, PassoDiGiove_Text_GinaIntro, PassoDiGiove_Text_GinaDefeat, PassoDiGiove_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox PassoDiGiove_Text_GinaPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_Mia::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, PassoDiGiove_Text_MiaIntro, PassoDiGiove_Text_MiaDefeat, PassoDiGiove_Text_MiaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox PassoDiGiove_Text_MiaPostBattle, MSGBOX_DEFAULT
	release
	end

PassoDiGiove_EventScript_Darian::
	trainerbattle_single TRAINER_DARIAN, PassoDiGiove_Text_DarianIntro, PassoDiGiove_Text_DarianDefeat
	msgbox PassoDiGiove_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
	end

PassoDiGiove_Text_BrineyLivesInSeasideCottage:
	.string "That seaside cottage is where\n"
	.string "MR. BRINEY lives.\p"
	.string "He was once a mighty sailor who never\n"
	.string "feared the sea, however stormy.$"

PassoDiGiove_Text_WhatsItLikeAtBottomOfSea:
	.string "The sea, huh?\p"
	.string "I wonder what it's like at the bottom\n"
	.string "of the sea?$"

PassoDiGiove_Text_ThrowBallAtWeakenedPokemon:
	.string "If you're going to throw a POKé BALL,\n"
	.string "weaken the wild POKéMON first.\p"
	.string "It will be easier to catch if it's been\n"
	.string "poisoned, burned, or lulled to sleep.$"

PassoDiGiove_Text_OnlyThrowBallAtWildPokemon:
	.string "You're a thief if you try to steal\n"
	.string "someone else's POKéMON.\p"
	.string "You should throw POKé BALLS only at\n"
	.string "wild POKéMON.$"

PassoDiGiove_Text_ImNotATrainer:
	.string "Oh, no, I'm not a TRAINER.\p"
	.string "But that's right, if TRAINERS lock eyes,\n"
	.string "it's a challenge to battle.\p"
	.string "If you don't want to battle, stay out\n"
	.string "of their sight.$"

PassoDiGiove_Text_LikeFillingMouthWithSeedsTakeThis:
	.string "I like filling my mouth with seeds,\n"
	.string "then spitting them out fast!\p"
	.string "You can have this, so you try it out!\p"
	.string "Use it on a POKéMON, and it will learn\n"
	.string "a move for firing seeds rapidly.$"

PassoDiGiove_Text_TMsAreOneTimeUse:
	.string "A word of advice!\p"
	.string "A TM, TECHNICAL MACHINE, is good only\n"
	.string "for one-time use.\p"
	.string "Once you use it, it's gone.\n"
	.string "Think twice before using it!$"

PassoDiGiove_Text_DontNeedThisTakeIt:
	.string "This FLOWER SHOP started selling\n"
	.string "saplings recently.\p"
	.string "It made me so happy, I went overboard\n"
	.string "shopping.\p"
	.string "I don't need this WHITE HERB anymore.\n"
	.string "Would you take it, please?$"

PassoDiGiove_Text_FlowerShopSellingSaplings:
	.string "This FLOWER SHOP started selling\n"
	.string "saplings recently.\p"
	.string "It made me so happy, I went overboard\n"
	.string "shopping. Where should I put them?$"

PassoDiGiove_Text_MrBrineysCottage:
	.string "MR. BRINEY'S COTTAGE$"

PassoDiGiove_Text_RouteSignPetalburg:
	.string "ROUTE 1O4\n"
	.string "{RIGHT_ARROW} PETALBURG CITY$"

PassoDiGiove_Text_RouteSignRustboro:
	.string "ROUTE 1O4\n"
	.string "{UP_ARROW} RUSTBORO CITY$"

PassoDiGiove_Text_PrettyPetalFlowShop:
	.string "PRETTY PETAL FLOWER SHOP$"

PassoDiGiove_Text_TrainerTipsDoubleBattles:
	.string "TRAINER TIPS\p"
	.string "In the HOENN region there are pairs\n"
	.string "of TRAINERS who challenge others\l"
	.string "for 2-on-2 POKéMON battles called\l"
	.string "DOUBLE BATTLES.\p"
	.string "In a DOUBLE BATTLE, the TRAINER must\n"
	.string "send out two POKéMON, the one at the\l"
	.string "left of the list and the top one.\l"
	.string "Watch how POKéMON are lined up.$"

PassoDiGiove_Text_MayWeShouldRegister:
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\p"
	.string "DEVON upgraded your POKéNAV with\n"
	.string "the MATCH CALL system, huh?\p"
	.string "We should register each other so we\n"
	.string "can get in contact anytime.$"

PassoDiGiove_Text_RegisteredMay:
	.string "{PLAYER} registered MAY\n"
	.string "in the POKéNAV.$"

PassoDiGiove_Text_MayHowsYourPokedex:
	.string "MAY: Oh, by the way, {PLAYER}{KUN},\n"
	.string "how's your POKéDEX coming along?$"

PassoDiGiove_Text_MayMinesDecentLetsBattle:
	.string "Mine's looking pretty decent.\n"
	.string "So…\l"
	.string "How about a little battle?$"

PassoDiGiove_Text_MayHaventRaisedPokemon:
	.string "MAY: Oh, what's the matter?\p"
	.string "Haven't you caught or raised your\n"
	.string "POKéMON very much?\p"
	.string "That's not very good for a TRAINER!$"

PassoDiGiove_Text_MayLetsBattle:
	.string "MAY: So, what do you think?\n"
	.string "How about a little battle here?$"

PassoDiGiove_Text_MayIntro:
	.string "MAY: You just became a TRAINER,\n"
	.string "{PLAYER}{KUN}. I'm not going to lose!$"

PassoDiGiove_Text_MayDefeat:
	.string "Yikes!\n"
	.string "You're better than I expected!$"

PassoDiGiove_Text_MayPostBattle:
	.string "MAY: I can tell you've gotten pretty\n"
	.string "good with the way you handle POKéMON.\p"
	.string "But instead of only making them\n"
	.string "battle, you should be like MR. BRINEY.\p"
	.string "It's important to become friends with\n"
	.string "POKéMON, too.$"

PassoDiGiove_Text_BrendanWeShouldRegister:
	.string "BRENDAN: Oh, hey, {PLAYER}!\p"
	.string "Cool, you had DEVON install the MATCH\n"
	.string "CALL system on your POKéNAV!\p"
	.string "Let's register each other in our\n"
	.string "POKéNAVS so we can keep in touch.$"

PassoDiGiove_Text_RegisteredBrendan:
	.string "{PLAYER} registered BRENDAN\n"
	.string "in the POKéNAV.$"

PassoDiGiove_Text_BrendanHowsYourPokedex:
	.string "BRENDAN: {PLAYER}, how's your POKéDEX?\n"
	.string "Have you filled in any pages yet?$"

PassoDiGiove_Text_BrendanDoingGreatLetsBattle:
	.string "Me, I'm doing great!\p"
	.string "Want to check out how good I am with\n"
	.string "a battle?$"

PassoDiGiove_Text_BrendanNoConfidence:
	.string "BRENDAN: What's the matter? Don't have\n"
	.string "any confidence in your POKéMON?$"

PassoDiGiove_Text_BrendanLetsBattle:
	.string "BRENDAN: What's up?\n"
	.string "Want to have a battle with me?$"

PassoDiGiove_Text_BrendanIntro:
	.string "BRENDAN: I know you just became\n"
	.string "a TRAINER, but I won't go easy!$"

PassoDiGiove_Text_BrendanDefeat:
	.string "Hmm…\n"
	.string "You're pretty good.$"

PassoDiGiove_Text_BrendanPostBattle:
	.string "BRENDAN: You've gotten pretty decent\n"
	.string "at handling POKéMON.\p"
	.string "But, you know, you shouldn't just be\n"
	.string "making POKéMON battle.\p"
	.string "Like MR. BRINEY, it's important to\n"
	.string "become friends with your POKéMON.$"
