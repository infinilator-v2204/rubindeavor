#include "generic.h"
#include "event.h"
#include "dialog.h"
#include "battlesystem.h"
#include "overworld.h"
#include "sprites.h"
#include "audio.h"
#include "action.h"
#include "party.h"
#include "profile.h"



void Event_Trigger(int id) {
	OverworldObject* player = &overworld.objects[0];
	OverworldObject* caller = &overworld.objects[eventSystem.callerObjectId];
	
	eventSystem.ptr = 0;
	eventSystem.runningSize = 0;
	eventSystem.queueSize = 0;
	eventSystem.sync = false;
	eventSystem.playerPositionSync = false;
	eventSystem.cameraPlayerFollow = false;
	switch (id) {
		case 1: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(0);
			Event_Queue_CompareIntToConst(&partyMembers[0].armorId, 16);
			Event_Queue_JumpIfEqual(0);
			Event_Queue_SetSync(true);
			Event_Queue_SaveToVarFloat(0, &overworld.objects[0].x);
			Event_Queue_SaveToVarFloat(1, &overworld.objects[0].y);
			Event_Queue_Object_WalkToRelative(0, 64, 0, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Camera_MoveToRelative(64, 16, 1);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_WalkToPointer(1, 64, 24, 1, OBJECT_DIRECTION_UP, &eventSystem.vars[0].f, &eventSystem.vars[1].f);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			Event_Queue_Exit();
			
			Event_Queue_Label(0);
			Event_Queue_Dialog_Run(2);
			Event_Queue_Regroup(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 2: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (!profile.flags[FLAG_NOAH_JOINED] && profile.flags[FLAG_CANTGOALONE_ATTEMPTS] <= 3) {
				Event_Queue_Dialog_Run(2069);
				profile.flags[FLAG_CANTGOALONE_ATTEMPTS]++;
			}
			else {
				if (!profile.flags[FLAG_NOAH_JOINED]) {
					Event_Queue_Dialog_Run(2114);
					Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
					Event_Queue_JumpIfEqual(1);
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
					Event_Queue_Exit();
					Event_Queue_Label(1);
				}
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(4, OBJECT_DIRECTION_RIGHT);
				if (!profile.flags[FLAG_NOAH_JOINED])
					Event_Queue_Dialog_Run(100);
				else
					Event_Queue_Dialog_Run(101);
				Event_Queue_EngageBattle(4, 11);
				Event_Queue_Object_Destroy(11);
				Event_Queue_Object_Destroy(12);
				Event_Queue_RemoveCurrentTrigger();
				Event_Queue_SetFlag(FLAG_PLOT, 5);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 3: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 5952, 3888, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 5944, 3920, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Camera_MoveTo(6000, 3872, 2);
			Event_Queue_SetSync(false);
			
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(15, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(16, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(40);
			Event_Queue_Dialog_Run(110);
			Event_Queue_Dialog_Run(111);
			Event_Queue_Dialog_Run(112);
			Event_Queue_Dialog_Run(113);
			Event_Queue_Object_Destroy(16);
			Event_Queue_Party_Join(2);
			if (!profile.flags[FLAG_NOAH_JOINED]) {
				Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[16].x, &overworld.objects[16].y);
				Event_Queue_Object_WalkTo(1, 5968, 3856, 2, OBJECT_DIRECTION_RIGHT);
			}
			else {
				Event_Queue_Object_TeleportToPointer(2, 0, 0, &overworld.objects[16].x, &overworld.objects[16].y);
				Event_Queue_Object_WalkTo(2, 5968, 3856, 2, OBJECT_DIRECTION_RIGHT);
			}
			
			Event_Queue_WaitFrames(10);
			Event_Queue_Dialog_Run(114);
			Event_Queue_Dialog_Run(115);
			Event_Queue_Dialog_Run(116);
			Event_Queue_Dialog_Run(129);
			Event_Queue_Object_ChangeSpriteId(13, SPR_misc_sally_serious);
			Event_Queue_Dialog_Run(117);
			Event_Queue_EngageBattle(5, 13);
			Event_Queue_Object_ChangeSpriteFrame(13, 1);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(118);
			Event_Queue_Dialog_Run(119);
			Event_Queue_Dialog_Run(120);
			Event_Queue_SetSync(true);
			Event_Queue_Object_ChangeSpriteId(13, SPR_owchar_sally);
			Event_Queue_Object_WalkTo(13, 5568, 3968, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(15, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(15, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(121);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(14, 5568, 3968, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(15, 5888, 3968, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeDirection(15, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(130);
			Event_Queue_Object_WalkTo(15, 5568, 3968, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_Destroy(13);
			Event_Queue_Object_Destroy(14);
			Event_Queue_Object_Destroy(15);
			
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			if (!profile.flags[FLAG_NOAH_JOINED])
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
			else
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(122);
			Event_Queue_Dialog_Run(123);
			Event_Queue_Dialog_Run(124);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_Dialog_Run(125);
			Event_Queue_Label(33);
				Event_Queue_Dialog_Run(126);
				Event_Queue_Profile_InventoryPartyOrderAdd(2);
				Event_Queue_SetFlag(FLAG_EMMET_JOINED, 1);
				Event_Queue_Dialog_Run(3002);
				Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
				Event_Queue_CompareCharToConst(&profile.partyOrder[1], 1);
				Event_Queue_JumpIfNotEqual(2);
				Event_Queue_Dialog_Run(131);
				Event_Queue_Dialog_Run(132);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
				Event_Queue_Dialog_Run(133);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Jump(33);
			Event_Queue_Label(2);
			Event_Queue_Dialog_Run(127);
			
			Event_Queue_Dialog_Run(128);
			Event_Queue_Object_WalkTo(1, 5568, 3968, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Party_Leave(2);
			Event_Queue_SetFlag(FLAG_ALONE, 1);
			
			Event_Queue_Label(0);
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 6);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 4: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_CreateObject(70, 1, SPR_owchar_npc_8, 8608, 3600, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToPointer(70, 48, 0, 2, OBJECT_DIRECTION_LEFT, &overworld.player.x, &overworld.player.y);
			Event_Queue_Dialog_Run(172);
			Event_Queue_Dialog_Run(173);
			Event_Queue_Dialog_Run(174);
			Event_Queue_Dialog_Run(175);
			Event_Queue_Dialog_Run(176);
			Event_Queue_Dialog_Run(177);
			Event_Queue_Dialog_Run(178);
			Event_Queue_Dialog_Run(179);
			Event_Queue_Object_WalkToRelative(70, 96, 0, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkToRelative(70, 112, -112, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Dialog_Run(201);
			if (!profile.flags[FLAG_NOAH_JOINED] && profile.flags[FLAG_EMMET_JOINED]) {
				Event_Queue_Dialog_Run(202);
				Event_Queue_Dialog_Run(203);
			}
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 11);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 5: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(140);
			Event_Queue_CreateObject(70, 1, SPR_owchar_lulu, 7840, 3632, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(70, 7664, 3480, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 7632, 3480, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 7584, 3528, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Dialog_Run(141);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(7536, 3520, 1);
			Event_Queue_Object_WalkTo(0, 7536, 3528, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 7512, 3528, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 7488, 3528, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(142);
			Event_Queue_Dialog_Run(143);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(144);
			Event_Queue_Dialog_Run(145);
			Event_Queue_Dialog_Run(146);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(147);
			Event_Queue_Dialog_Run(148);
			Event_Queue_Object_EnableFighterSprite(70, 16, 15, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(149);
			Event_Queue_Object_EnableFighterSprite(70, 16, 15, FIGHTER_STATE_ATTACK1);
			Event_Queue_WaitFrames(10);
			Event_Queue_Dialog_Run(150);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(151);
			
			Event_Queue_EngageBattle(9, 70);
			Event_Queue_Object_EnableFighterSprite(70, 16, 15, FIGHTER_STATE_HURT);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(152);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Dialog_Run(153);
			
			Event_Queue_Object_WalkTo(70, 7632, 3480, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(70, 7664, 3480, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(70, 7840, 3632, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 10);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 6: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_WaitFrames(55);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(110);
			Event_Queue_Object_WalkToRelative(10, -16, 0, 0.25, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(48);
			Event_Queue_Object_WalkToRelative(10, -48, 0, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_EngageBattle(26, 10);
			Event_Queue_Object_Destroy(10);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 9);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 7: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(103);
			Event_Queue_CreateObject(70, 1, SPR_owchar_leafcrew, 3456, 1312, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 3328, 1440, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(104);
			Event_Queue_Dialog_Run(105);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(106);
			Event_Queue_CreateObject(71, 1, SPR_owchar_leafcrew, 3552, 1456, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(71, 3360, 1456, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(107);
			Event_Queue_Object_WalkTo(71, 3552, 1456, 3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_Destroy(71);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(108);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_EngageBattle(23, 11);
			Event_Queue_Object_Destroy(11);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 13);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 8: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_WaitFrames(60);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 3056, 496, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 3024, 496, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 3088, 496, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(3056, 464, 1);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(180);
			Event_Queue_Dialog_Run(181);
			Event_Queue_Dialog_Run(182);
			Event_Queue_Dialog_Run(183);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(204);
				Event_Queue_Dialog_Run(205);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(206);
				Event_Queue_Dialog_Run(207);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(208);
				Event_Queue_WaitFrames(50);
				Event_Queue_PlayMusic(MUS_scary);
				Event_Queue_Dialog_Run(209);
				Event_Queue_WaitFrames(50);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			}
			else {
				if (profile.flags[FLAG_EMMET_JOINED]) Event_Queue_Dialog_Run(184);
				Event_Queue_Dialog_Run(185);
				Event_Queue_PlayMusic(MUS_scary);
				Event_Queue_Dialog_Run(186);
				Event_Queue_Dialog_Run(187);
				if (profile.flags[FLAG_EMMET_JOINED]) Event_Queue_Dialog_Run(188);
				Event_Queue_Dialog_Run(189);
				Event_Queue_Dialog_Run(190);
				Event_Queue_Dialog_Run(191);
				Event_Queue_Dialog_Run(192);
				Event_Queue_Dialog_Run(193);
			}
			Event_Queue_Dialog_Run(194);
			Event_Queue_WaitFrames(60);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(8, 11);
			
			Event_Queue_Dialog_Run(195);
			Event_Queue_Dialog_Run(196);
			Event_Queue_Dialog_Run(197);
			Event_Queue_Object_WalkTo(11, 3064, 428, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_Destroy(11);
			Event_Queue_WaitFrames(120);
			if (!profile.flags[FLAG_ALONE]) {
				if (profile.flags[FLAG_NOAH_JOINED]) Event_Queue_Dialog_Run(198);
				if (profile.flags[FLAG_EMMET_JOINED]) Event_Queue_Dialog_Run(199);
				Event_Queue_Dialog_Run(200);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_CreateTrigger(5, 3040, 576, 3072, 592, 44);
			Event_Queue_SetFlag(FLAG_PLOT, 14);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 9: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_MoveTo(552, 1288, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 552, 1288, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(1, 528, 1336, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(2, 576, 1336, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(210);
			Event_Queue_Object_ToggleGhost(11, true);
			Event_Queue_Object_WalkToPointer(11, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(11, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_Destroy(11);
			Event_Queue_CreateNPC(11, 70000, 552, 1268, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(251);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3071);
			
			if (!profile.flags[FLAG_ALONE] && profile.flags[FLAG_EMMET_JOINED]) {
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(211);
				Event_Queue_Dialog_Run(212);
				Event_Queue_Dialog_Run(213);
				Event_Queue_Dialog_Run(214);
				Event_Queue_Dialog_Run(215);
				Event_Queue_Dialog_Run(216);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(217);
				Event_Queue_Dialog_Run(218);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Dialog_Run(219);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_Dialog_Run(3062);
			Event_Queue_SetFlag(FLAG_BADGES_UNLOCKED, 1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 15);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 10: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_MoveTo(10000, 8288, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 10152, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 10168, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 10184, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 9992, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 10008, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 10024, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 9960, 8312, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 9992, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 10024, 8280, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			
			Event_Queue_WaitFrames(90);
			
			Event_Queue_Object_WalkTo(11, 10344, 8168, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(11, 10056, 8328, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_CreateObject(70, 1, SPR_owchar_jackie, 10304, 8248, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 10056, 8248, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 10056, 8288, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_TeleportTo(10, 10232, 8152);
			Event_Queue_Object_WalkTo(10, 10056, 8248, 3, OBJECT_DIRECTION_LEFT);
			
			Event_Queue_WaitFrames(60);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_electra);
			Event_Queue_SetSync(false);
			
			Event_Queue_WaitFrames(120);
			
			Event_Queue_EngageBattle(20, 70);
			
			Event_Queue_Object_Destroy(70);
			Event_Queue_CreateNPC(10, 4, 10232, 8128, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateNPC(11, 5, 10512, 8144, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 53);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 11: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_WaitFrames(1);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(110);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkToRelative(10, 64, 0, 6, OBJECT_DIRECTION_RIGHT);
			Event_Queue_EngageBattle(32, 10);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Object_Destroy(11);
			Event_Queue_Object_Destroy(12);
			Event_Queue_Object_Destroy(13);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 71);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 12: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Player_SetPositionSync(true);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 7400, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(1, 7432, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Camera_MoveTo(7400, 7592, 1);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(60);
				
				Event_Queue_Dialog_Run(490);
				Event_Queue_Dialog_Run(920);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(921);
				Event_Queue_Dialog_Run(922);
				Event_Queue_PlayMusic(MUS_scary2);
				Event_Queue_Dialog_Run(501);
				Event_Queue_Dialog_Run(923);
				Event_Queue_Dialog_Run(924);
				Event_Queue_Dialog_Run(925);
				Event_Queue_Dialog_Run(926);
				Event_Queue_Dialog_Run(927);
				Event_Queue_Dialog_Run(928);
				Event_Queue_Dialog_Run(929);
				
				Event_Queue_Object_WalkTo(10, 7400, 7544, 0.5, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(930);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(90);
				if (profile.flags[FLAG_SALLY_JOINED])
					Event_Queue_Dialog_Run(523);
				else
					Event_Queue_Dialog_Run(949);
				
				Event_Queue_StopMusic();
				Event_Queue_EngageBattle(28, 10);
				Event_Queue_Object_TeleportTo(10, 7400, 7576);
				Event_Queue_Object_EnableFighterSprite(10, 29, 29, FIGHTER_STATE_HURT);
				
				Event_Queue_WaitFrames(120);
				Event_Queue_Dialog_Run(931);
				Event_Queue_Dialog_Run(932);
				Event_Queue_Object_DisableFighterSprite(10);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_Object_WalkTo(0, 7360, 7576, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(933);
				Event_Queue_Dialog_Run(934);
				Event_Queue_Dialog_Run(935);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(936);
				Event_Queue_Dialog_Run(937);
				Event_Queue_Dialog_Run(938);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(939);
				Event_Queue_Dialog_Run(940);
				Event_Queue_Dialog_Run(941);
				Event_Queue_Dialog_Run(942);
				Event_Queue_Dialog_Run(943);
				Event_Queue_Dialog_Run(944);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(945);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(10, 7400, 7520, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(10);
				Event_Queue_WaitFrames(30);
				if (profile.flags[FLAG_SALLY_JOINED]) {
					Event_Queue_Object_WalkTo(1, 7400, 7576, 1, OBJECT_DIRECTION_LEFT);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Dialog_Run(946);
					Event_Queue_Dialog_Run(947);
					Event_Queue_Dialog_Run(948);
				}
			}
			else {
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 7360, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(1, 7388, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(2, 7412, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(3, 7440, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Camera_MoveTo(7400, 7592, 1);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(60);
				
				Event_Queue_Dialog_Run(490);
				Event_Queue_Dialog_Run(491);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(492);
				Event_Queue_Dialog_Run(493);
				Event_Queue_Object_WalkTo(3, 7440, 7632, 0.5, OBJECT_DIRECTION_UP);
				Event_Queue_PlayMusic(MUS_scary);
				Event_Queue_Dialog_Run(494);
				Event_Queue_Dialog_Run(495);
				Event_Queue_Dialog_Run(496);
				Event_Queue_Dialog_Run(497);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(498);
				Event_Queue_Dialog_Run(499);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(3, SPR_misc_sally_serious);
				Event_Queue_Object_ChangeSpriteFrame(3, 0);
				Event_Queue_Dialog_Run(500);
				Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_sally);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(501);
				
				Event_Queue_Object_WalkTo(10, 7400, 7544, 0.5, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(502);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(90);
				Event_Queue_Dialog_Run(523);
				Event_Queue_StopMusic();
				Event_Queue_EngageBattle(28, 10);
				Event_Queue_Object_TeleportTo(3, 7440, 7648);
				Event_Queue_Object_TeleportTo(10, 7400, 7576);
				Event_Queue_Object_EnableFighterSprite(10, 29, 29, FIGHTER_STATE_HURT);
				
				Event_Queue_WaitFrames(120);
				Event_Queue_Object_ChangeSpriteId(3, SPR_misc_sally_serious);
				Event_Queue_Object_ChangeSpriteFrame(3, 1);
				Event_Queue_Dialog_Run(503);
				Event_Queue_Object_DisableFighterSprite(10);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(504);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_ATTACK2);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(505);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_DisableFighterSprite(3);
				
				/*Event_Queue_WaitFrames(90);
				Event_Queue_Object_TeleportToPointer(10, -1, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_TeleportToPointer(10, 2, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_TeleportToPointer(10, -2, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_TeleportToPointer(10, 2, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_TeleportToPointer(10, -1, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				Event_Queue_WaitFrames(30);*/
				
				Event_Queue_Object_WalkTo(0, 7360, 7576, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_sally);
				Event_Queue_Dialog_Run(507);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(508);
				Event_Queue_Dialog_Run(509);
				Event_Queue_Dialog_Run(510);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(511);
				Event_Queue_Dialog_Run(512);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(513);
				Event_Queue_WaitFrames(80);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(80);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(514);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(515);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(516);
				Event_Queue_Dialog_Run(517);
				Event_Queue_Dialog_Run(518);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(519);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(520);
				Event_Queue_Object_WalkTo(0, 7360, 7648, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_WalkTo(10, 7400, 7520, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(10);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 72);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 13: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_PlaySound(SND_hit1);
			Event_Queue_Object_ToggleWalkAnimation(0, false);
			Event_Queue_Object_ToggleWalkAnimation(1, false);
			Event_Queue_Object_ToggleWalkAnimation(2, false);
			Event_Queue_Object_ToggleWalkAnimation(3, false);
			Event_Queue_Object_WalkTo(0, 3040, 1840, 6, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 3008, 1840, 6, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(2, 3072, 1840, 6, OBJECT_DIRECTION_DOWN);
			Event_Queue_Camera_MoveTo(3040, 1832, 6);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(3);
			Event_Queue_CreateObject(70, 1, SPR_owchar_lulu, 3040, 1920, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(70, 3040, 1872, 3, OBJECT_DIRECTION_UP);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_Dialog_Run(220);
			Event_Queue_PlayMusic(MUS_lu);
			Event_Queue_Dialog_Run(221);
			Event_Queue_Dialog_Run(222);
			Event_Queue_Object_EnableFighterSprite(70, 16, 16, FIGHTER_STATE_IDLE);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_EnableFighterSprite(70, 16, 16, FIGHTER_STATE_ATTACK3);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(223);
			Event_Queue_Dialog_Run(224);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Dialog_Run(225);
			Event_Queue_Dialog_Run(226);
			if (profile.flags[FLAG_EMMET_JOINED]) Event_Queue_Dialog_Run(227);
			Event_Queue_Object_EnableFighterSprite(70, 16, 16, FIGHTER_STATE_BLOCK);
			if (profile.flags[FLAG_EMMET_JOINED]) Event_Queue_Dialog_Run(228);
			Event_Queue_Dialog_Run(229);
			
			Event_Queue_EngageBattle(10, 70);
			Event_Queue_Object_EnableFighterSprite(70, 16, 16, FIGHTER_STATE_HURT);
			Event_Queue_Object_ToggleWalkAnimation(0, true);
			Event_Queue_Object_ToggleWalkAnimation(1, true);
			Event_Queue_Object_ToggleWalkAnimation(2, true);
			Event_Queue_Object_ToggleWalkAnimation(3, true);
			
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(230);
			if (profile.flags[FLAG_NOAH_JOINED]) Event_Queue_Dialog_Run(231);
			Event_Queue_Dialog_Run(232);
			Event_Queue_Object_EnableFighterSprite(70, 16, 16, FIGHTER_STATE_HURT);
			Event_Queue_Dialog_Run(233);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(240);
				Event_Queue_Dialog_Run(221);
			}
			else {
				Event_Queue_Dialog_Run(234);
				Event_Queue_Dialog_Run(235);
				if (profile.flags[FLAG_EMMET_JOINED]) Event_Queue_Dialog_Run(236);
			}
			Event_Queue_Dialog_Run(237);
			Event_Queue_Object_EnableFighterSprite(70, 16, 16, FIGHTER_STATE_ATTACK1);
			Event_Queue_Dialog_Run(238);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(239);
			Event_Queue_Object_WalkTo(70, 3040, 1920, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_Destroy(70);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			if (profile.flags[FLAG_ALONE])
				Event_Queue_SetFlag(FLAG_PLOT, 17);
			else
				Event_Queue_SetFlag(FLAG_PLOT, 16);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 14: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_WaitFrames(15);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(0, 80, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkToRelative(1, 48, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkToRelative(2, 16, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(250);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(251);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(252);
			Event_Queue_Dialog_Run(253);
			Event_Queue_Dialog_Run(254);
			Event_Queue_Dialog_Run(255);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 51);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 15: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(350);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(10, 13656, 7920, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(11, 13688, 7960, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_WalkTo(11, 13656, 7960, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(351);
			Event_Queue_Dialog_Run(352);
			Event_Queue_Dialog_Run(353);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(354);
				Event_Queue_Object_EnableFighterSprite(10, 17, 17, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(11, 17, 17, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(355);
			}
			Event_Queue_EngageBattle(11, 10);
			
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(364);
				Event_Queue_Dialog_Run(365);
				Event_Queue_Dialog_Run(366);
			}
			else {
				Event_Queue_Object_DisableFighterSprite(10);
				Event_Queue_Object_DisableFighterSprite(11);
				Event_Queue_Dialog_Run(356);
				Event_Queue_Dialog_Run(357);
				Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(358);
				Event_Queue_Dialog_Run(359);
				Event_Queue_Dialog_Run(360);
				Event_Queue_Dialog_Run(361);
				Event_Queue_Dialog_Run(362);
			}
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(10, 256, 0, 1, -1);
			Event_Queue_Object_WalkToRelative(11, 256, 0, 1, -1);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Object_Destroy(11);
			Event_Queue_Object_DisableFighterSprite(2);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(363);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 52);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 16: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(10168, 8328, 1);
			Event_Queue_Object_WalkTo(0, 10144, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 10168, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 10192, 8328, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(260);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 53);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 17: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_MoveTo(17024, 8448, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 17024, 8456, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 17056, 8456, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(2, 17088, 8456, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(300);
			Event_Queue_Dialog_Run(301);
			Event_Queue_Dialog_Run(302);
			Event_Queue_CreateObject(70, 1, SPR_owchar_perry, 16832, 8456, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(70, 16976, 8456, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(303);
			Event_Queue_Dialog_Run(304);
			Event_Queue_Dialog_Run(305);
			Event_Queue_Dialog_Run(306);
			Event_Queue_Dialog_Run(307);
			Event_Queue_Camera_TogglePlayerFollow(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_QueueWalkTo(70, 16488, 8456, 3, -1);
			Event_Queue_Object_QueueWalkTo(70, 16488, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(70, 16048, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(70, 16048, 7760, 3, -1);
			Event_Queue_Object_QueueWalkTo(70, 16392, 7760, 3, -1);
			Event_Queue_Object_QueueWalkTo(70, 16392, 7688, 3, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_Object_QueueWalkTo(0, 16488, 8456, 3, -1);
			Event_Queue_Object_QueueWalkTo(0, 16488, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(0, 16048, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(0, 16048, 7760, 3, -1);
			Event_Queue_Object_QueueWalkTo(0, 16424, 7760, 3, OBJECT_DIRECTION_UP);
			
			Event_Queue_Object_QueueWalkTo(1, 16488, 8456, 3, -1);
			Event_Queue_Object_QueueWalkTo(1, 16488, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(1, 16048, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(1, 16048, 7760, 3, -1);
			Event_Queue_Object_QueueWalkTo(1, 16392, 7760, 3, OBJECT_DIRECTION_UP);
			
			Event_Queue_Object_QueueWalkTo(2, 16488, 8456, 3, -1);
			Event_Queue_Object_QueueWalkTo(2, 16488, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(2, 16048, 7912, 3, -1);
			Event_Queue_Object_QueueWalkTo(2, 16048, 7760, 3, -1);
			Event_Queue_Object_QueueWalkTo(2, 16360, 7760, 3, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(5);
			Event_Queue_Object_WalkTo(0, 16392, 7688, 2, OBJECT_DIRECTION_UP);
			Event_Queue_GotoArea(9, 9608, 8432, -1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			
			Event_Queue_Camera_TogglePlayerFollow(false);
			Event_Queue_Dialog_Run(308);
			Event_Queue_Dialog_Run(309);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveToRelative(0, -96, 2);
			Event_Queue_Object_QueueWalkTo(70, 9608, 8256, 2, -1);
			Event_Queue_Object_QueueWalkTo(70, 9752, 8256, 2, -1);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 55);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 18: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_WalkTo(1, 9608, 8392, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(323);
				Event_Queue_Dialog_Run(324);
				Event_Queue_Dialog_Run(329);
				Event_Queue_Object_WalkTo(1, 9608, 8256, 2, -1);
				Event_Queue_Object_WalkTo(1, 9752, 8256, 2, -1);
			}
			else {
				Event_Queue_Object_WalkTo(3, 9608, 8392, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(323);
				Event_Queue_Dialog_Run(324);
				Event_Queue_Dialog_Run(325);
				Event_Queue_Object_WalkTo(3, 9608, 8256, 2, -1);
				Event_Queue_Object_WalkTo(3, 9752, 8256, 2, -1);
			}
			Event_Queue_Party_Leave(6);
			Event_Queue_Profile_InventoryPartyOrderRemove(6);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 58);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 19: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(8992, 8448, 1);
				Event_Queue_Object_WalkTo(0, 8918, 8488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteId(0, -1);
				Event_Queue_Object_ChangeSpriteFrame(11, 3);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(660);
				Event_Queue_FadeOut(0.01);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeSpriteFrame(11, 0);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_perry);
				Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
				Event_Queue_Object_TeleportTo(10, 9000, 8416);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_FadeIn(0.0625);
				Event_Queue_PlayMusic(MUS_casual);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(661);
				Event_Queue_Dialog_Run(662);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(316);
				Event_Queue_Dialog_Run(338);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_SetFlag(FLAG_PERRY_PIZZASLICES, 2);
			}
			else {
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(8992, 8448, 1);
				Event_Queue_Object_WalkTo(0, 8918, 8488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_WalkTo(1, 8966, 8488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_WalkTo(2, 9014, 8488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(30);
				Event_Queue_SetSync(true);
				Event_Queue_Object_ChangeSpriteId(0, -1);
				Event_Queue_Object_ChangeSpriteId(1, -1);
				Event_Queue_Object_ChangeSpriteId(2, -1);
				Event_Queue_Object_ChangeSpriteFrame(11, 3);
				Event_Queue_Object_ChangeSpriteFrame(12, 4);
				Event_Queue_Object_ChangeSpriteFrame(13, 5);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(660);
				Event_Queue_FadeOut(0.01);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeSpriteFrame(11, 0);
				Event_Queue_Object_ChangeSpriteFrame(12, 1);
				Event_Queue_Object_ChangeSpriteFrame(13, 2);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
				Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_perry);
				Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
				Event_Queue_Object_TeleportTo(10, 9000, 8416);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_FadeIn(0.0625);
				Event_Queue_PlayMusic(MUS_casual);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(330);
				Event_Queue_Dialog_Run(331);
				Event_Queue_Dialog_Run(332);
				Event_Queue_Dialog_Run(333);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(334);
				Event_Queue_Dialog_Run(336);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(335);
				Event_Queue_Dialog_Run(338);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Dialog_Run(337);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 59);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 20: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 16392, 7736, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 16424, 7752, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 16424, 7768, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(340);
				Event_Queue_Dialog_Run(341);
			}
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(10, 16320, 7752, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkTo(11, 16288, 7736, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(12, 16288, 7768, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(370);
			Event_Queue_Dialog_Run(371);
			Event_Queue_Object_EnableFighterSprite(10, 32, 34, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(372);
			Event_Queue_Dialog_Run(373);
			if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(374);
			Event_Queue_Dialog_Run(375);
			Event_Queue_Dialog_Run(376);
			Event_Queue_Dialog_Run(377);
			Event_Queue_Dialog_Run(378);
			Event_Queue_Dialog_Run(379);
			Event_Queue_EngageBattle(36, 10);
			
			Event_Queue_Object_EnableFighterSprite(10, 32, 34, FIGHTER_STATE_HURT);
			Event_Queue_Object_EnableFighterSprite(11, 31, 33, FIGHTER_STATE_HURT);
			Event_Queue_Object_EnableFighterSprite(12, 31, 33, FIGHTER_STATE_HURT);
			Event_Queue_Dialog_Run(380);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_Object_DisableFighterSprite(12);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(10, 16080, 7752, 1, -1);
			Event_Queue_WaitFrames(75);
			Event_Queue_Object_WalkTo(11, 16080, 7736, 1, -1);
			Event_Queue_Object_WalkTo(12, 16080, 7768, 1, -1);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Object_Destroy(11);
			Event_Queue_Object_Destroy(12);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 60);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 21: {
			overworld.map.triggers[1].eventId = 0;
			overworld.map.triggers[2].eventId = 0;
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(680);
				Event_Queue_FadeOutMusic(2000);
				if (player->y >= 6832) {
					Event_Queue_Object_WalkTo(13, 14256, 6904, 2, -1);
					Event_Queue_Object_WalkToPointer(13, -32, 0, 2, OBJECT_DIRECTION_RIGHT, &player->x, &player->y);
				}
				else {
					Event_Queue_Object_WalkToPointer(13, -32, 0, 2, OBJECT_DIRECTION_RIGHT, &player->x, &player->y);
				}
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_PlayMusic(MUS_bother);
				Event_Queue_Dialog_Run(681);
				Event_Queue_Dialog_Run(682);
				Event_Queue_Dialog_Run(683);
				Event_Queue_Dialog_Run(684);
				Event_Queue_Object_ChangeSpriteId(13, SPR_misc_sally_serious);
				Event_Queue_Object_ChangeSpriteFrame(13, 1);
				Event_Queue_Dialog_Run(685);
				Event_Queue_Object_ChangeSpriteId(13, SPR_owchar_sally);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE_PLOT] > 2) ? 687 : 686);
				
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE_PLOT] > 2) ? 694 : 688);
				Event_Queue_Dialog_Run(689);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE_PLOT] > 2) ? 691 : 690);
				Event_Queue_Dialog_Run(692);
				Event_Queue_Dialog_Run(693);
				
				Event_Queue_Label(0);
				Event_Queue_Object_Destroy(13);
				Event_Queue_Party_Join(3);
				Event_Queue_Profile_InventoryPartyOrderAdd(3);
				Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[13].x, &overworld.objects[13].y);
				Event_Queue_FadeOutMusic(1000);
				if (profile.flags[FLAG_ALONE_PLOT] > 2) {
					Event_Queue_CreateTrigger(1, 16372, 7680, 16412, 7726, 55);
				}
			}
			else {
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(390);
				Event_Queue_SetSync(true);
				Event_Queue_FadeOutMusic(2000);
				if (player->y >= 6832) {
					Event_Queue_Object_QueueWalkTo(0, 14256, 6768, 2, -1);
					Event_Queue_Object_QueueWalkTo(0, 14400, 6720, 2, OBJECT_DIRECTION_UP);
					
					Event_Queue_Object_QueueWalkTo(1, 14256, 6768, 2, -1);
					Event_Queue_Object_QueueWalkTo(1, 14432, 6720, 2, OBJECT_DIRECTION_UP);
					
					Event_Queue_Object_QueueWalkTo(2, 14256, 6768, 2, -1);
					Event_Queue_Object_QueueWalkTo(2, 14368, 6720, 2, OBJECT_DIRECTION_UP);
					
					Event_Queue_Object_QueueWalkTo(3, 14256, 6768, 2, -1);
					Event_Queue_Object_QueueWalkTo(3, 14336, 6720, 2, OBJECT_DIRECTION_UP);
				}
				else {
					Event_Queue_Object_WalkTo(0, 14400, 6720, 2, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(1, 14432, 6720, 2, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(2, 14368, 6720, 2, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(3, 14336, 6720, 2, OBJECT_DIRECTION_UP);
				}
				Event_Queue_SetSync(false);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
				Event_Queue_PlayMusic(MUS_bother);
				Event_Queue_Dialog_Run(391);
				Event_Queue_Dialog_Run(392);
				Event_Queue_Object_ChangeSpriteId(13, SPR_misc_sally_serious);
				Event_Queue_Object_ChangeSpriteFrame(13, 1);
				Event_Queue_Dialog_Run(393);
				Event_Queue_Dialog_Run(394);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeSpriteFrame(13, 0);
				Event_Queue_Dialog_Run(395);
				Event_Queue_Dialog_Run(396);
				Event_Queue_Dialog_Run(397);
				Event_Queue_Dialog_Run(398);
				Event_Queue_Object_ChangeSpriteFrame(13, 1);
				Event_Queue_Dialog_Run(399);
				Event_Queue_Dialog_Run(400);
				Event_Queue_Dialog_Run(401);
				Event_Queue_Dialog_Run(402);
				Event_Queue_Object_ChangeSpriteFrame(13, 0);
				Event_Queue_Dialog_Run(403);
				Event_Queue_Dialog_Run(404);
				Event_Queue_Object_ChangeSpriteFrame(13, 1);
				Event_Queue_Dialog_Run(405);
				Event_Queue_Dialog_Run(406);
				Event_Queue_Dialog_Run(407);
				Event_Queue_Dialog_Run(408);
				Event_Queue_Dialog_Run(409);
				Event_Queue_Object_ChangeSpriteFrame(13, 0);
				Event_Queue_Dialog_Run(410);
				Event_Queue_Object_ChangeSpriteId(13, SPR_owchar_sally);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(45);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(411);
				Event_Queue_Dialog_Run(412);
				Event_Queue_Dialog_Run(413);
				Event_Queue_Object_WalkTo(13, 14380, 6704, 4, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(13, 4, 5, FIGHTER_STATE_ATTACK1);
				Event_Queue_SetSync(true);
				Event_Queue_Dialog_Run(414);
				Event_Queue_Object_ToggleWalkAnimation(2, false);
				Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_HURT);
				Event_Queue_PlaySound(SND_hit3);
				Event_Queue_Object_WalkToRelative(2, -32, 32, 4, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetSync(false);
				Event_Queue_Object_ToggleWalkAnimation(2, true);
				Event_Queue_Object_DisableFighterSprite(13);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(415);
				Event_Queue_Dialog_Run(416);
				Event_Queue_Dialog_Run(417);
				Event_Queue_Object_DisableFighterSprite(2);
				Event_Queue_Object_Destroy(13);
				Event_Queue_Party_Join(3);
				Event_Queue_Profile_InventoryPartyOrderAdd(3);
				Event_Queue_Object_TeleportToPointer(3, 0, 0, &overworld.objects[13].x, &overworld.objects[13].y);
				Event_Queue_FadeOutMusic(1000);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_Dialog_Run(3003);
			Event_Queue_PlayMusic(MUS_town);
			Event_Queue_SetFlag(FLAG_SALLY_JOINED, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 22: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_CreateObject(70, 1, SPR_misc_glasses, 680, 2678, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ToggleGhost(0, true);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_wakeup);
			Event_Queue_Object_ChangeSpriteFrame(0, 0);
			Event_Queue_Object_TeleportTo(0, 640, 2672);
			Event_Queue_Camera_TeleportTo(656, 2696);
			Event_Queue_WaitFrames(90);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(0, 2);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(0, 3);
			Event_Queue_WaitFrames(89);
			Event_Queue_CreateObject(71, 1, SPR_misc_rubybed, 640, 2672, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(71, 3);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_zero2);
			Event_Queue_Object_TeleportTo(0, 660, 2696);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 680, 2704, 0.5, OBJECT_DIRECTION_LEFT);
			Event_Queue_Camera_MoveTo(680, 2696, 0.5);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 2);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 1);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_Destroy(71);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_zero);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(30);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(31);
			
			Event_Queue_Object_ToggleGhost(0, false);
			Event_Queue_Regroup(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 23: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_WaitFrames(15);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 3280, 5440, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Camera_MoveTo(3280, 5432, 1);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(52);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(70, 1, SPR_owchar_river, 3488, 5440, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 3328, 5440, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(15);
			Event_Queue_Dialog_Run(40);
			Event_Queue_Dialog_Run(41);
			Event_Queue_PlayMusic(MUS_bother);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(42);
			Event_Queue_Dialog_Run(43);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(44);
			Event_Queue_Dialog_Run(45);
			Event_Queue_Dialog_Run(46);
			Event_Queue_Dialog_Run(47);
			Event_Queue_Dialog_Run(48);
			Event_Queue_EngageBattle(49, 70);
			
			Event_Queue_Dialog_Run(52);
			Event_Queue_Dialog_Run(53);
			Event_Queue_Dialog_Run(54);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_Object_WalkTo(70, 3488, 5440, 1, -1);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_PlayMusic(MUS_field);
			Event_Queue_Dialog_Run(55);
			Event_Queue_Dialog_Run(56);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(57);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 3);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 24: {
			if (profile.flags[FLAG_PURCHASED_BUS_TICKET]) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				if (profile.flags[FLAG_ALONE])
					Event_Queue_Dialog_Run(2119);
				else
					Event_Queue_Dialog_Run(2026);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 25: {
			if (profile.flags[FLAG_ALONE]) {
				profile.flags[FLAG_RUBY_ALONE_STATBOOST] = 1;
				Party_Refresh(0);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(8456, 4872, 2);
			Event_Queue_Object_WalkTo(0, 8456, 4888, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_WalkTo(1, 8424, 4888, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_WalkTo(2, 8488, 4888, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_WalkTo(0, 8456, 4864, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_TeleportTo(0, 8456, 4368);
			Event_Queue_Object_WalkTo(1, 8456, 4864, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_TeleportTo(1, 8456, 4368);
			Event_Queue_Object_WalkTo(2, 8456, 4864, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_TeleportTo(2, 8456, 4368);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_ChangeSpriteFrameSpeed(20, 0.0625);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteFrameSpeed(20, 0.125);
			Event_Queue_Object_WalkToRelative(20, 16, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkToRelative(20, 48, 0, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkToRelative(20, 96, 0, 3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(20, 160, 0, 4, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
			Event_Queue_SetSync(false);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_WaitFrames(30);
				Event_Queue_PlaySound(SND_reset);
				Event_Queue_WaitFrames(90);
				Event_Queue_Dialog_Run(2122);
			}
			Event_Queue_WaitFrames(30);
			
			Event_Queue_SetSync(true);
			Event_Queue_GotoArea(6, 13328, 7896, SPR_tileset_day);
			Event_Queue_WaitFrames(24);
			Event_Queue_CreateObject(70, 1, SPR_misc_sapphirebus, 13328, 7888, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ToggleGhost(70, true);
			Event_Queue_SetSync(false);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(13328, 7912, 1);
			Event_Queue_Object_WalkToRelative(0, 16, 16, 0.5, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToRelative(1, 0, 16, 0.5, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToRelative(2, -16, 16, 0.5, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			
			Event_Queue_WaitFrames(15);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(0, 64, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkToRelative(1, 40, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkToRelative(2, 16, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeSpriteFrameSpeed(70, 0.0625);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteFrameSpeed(70, 0.125);
			Event_Queue_Object_WalkToRelative(70, 16, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkToRelative(70, 48, 0, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkToRelative(70, 96, 0, 3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(70, 160, 0, 4, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(50);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(256);
				Event_Queue_WaitFrames(66);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Dialog_Run(257);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			}
			else {
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(250);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(251);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(252);
				Event_Queue_Dialog_Run(253);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Dialog_Run(254);
				Event_Queue_Dialog_Run(255);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 51);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 26: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(60);
			if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(326);
			Event_Queue_Dialog_Run(327);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PERRY_BASEMENT_DIALOG, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 27: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_MoveTo(7432, 7240, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 7432, 7240, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(3, 7448, 7288, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(1, 7416, 7288, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(2, 7384, 7288, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ToggleGhost(11, true);
			Event_Queue_Object_WalkToPointer(11, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(11, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_Destroy(11);
			Event_Queue_CreateNPC(11, 70000, 7432, 7216, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(252);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3072);
			
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(530);
				Event_Queue_Dialog_Run(531);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(532);
				Event_Queue_Dialog_Run(533);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			}
			
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(521);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(10, 7536, 7256, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(10, 7480, 7256, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(10, 7448, 7240, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(524);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Dialog_Run(526);
				Event_Queue_Dialog_Run(527);
			}
			else {
				Event_Queue_Profile_ItemAdd(17);
				Event_Queue_Dialog_Run(4004);
				Event_Queue_SetFlag(FLAG_MANSION_DIA_GIFT, 1);
			}
			if (profile.flags[FLAG_ALONE] && profile.flags[FLAG_ALONE_PLOT] >= 11) {
				Event_Queue_Dialog_Run(950);
				Event_Queue_Object_WalkToRelative(10, -8, 0, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(10, SPR_misc_dia_hug);
				Event_Queue_WaitFrames(98);
				Event_Queue_Dialog_Run(951);
				Event_Queue_Dialog_Run(952);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				
				Event_Queue_Dialog_Run(954);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_dia);
				Event_Queue_Object_JumpToRelative(10, 8, 0, OBJECT_DIRECTION_LEFT, 0, 4);
				Event_Queue_Dialog_Run(955);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_beamsword);
				Event_Queue_Object_ChangeSpriteFrame(0, 0);
				Event_Queue_Dialog_Run(956);
				Event_Queue_Dialog_Run(957);
				Event_Queue_Object_WalkToRelative(10, -4, 0, 0.125, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(958);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_StopMusic();
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_ChangeSpriteFrame(0, 2);
				Event_Queue_PlaySound(SND_hit1);
				Event_Queue_Object_EnableFighterSprite(10, 29, 29, FIGHTER_STATE_HURT);
				Event_Queue_WaitFrames(6);
				Event_Queue_PlaySound(SND_hit3);
				Event_Queue_WaitFrames(44);
				Event_Queue_Dialog_Run(501);
				Event_Queue_WaitFrames(64);
				Event_Queue_PlaySound(SND_hit2);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_ATTACK1);
				Event_Queue_Object_DisableFighterSprite(10);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_collapse_dia);
				Event_Queue_Object_ChangeSpriteFrame(10, 0);
				Event_Queue_Object_JumpToRelative(10, 8, 0, OBJECT_DIRECTION_DOWN, 0, 4);
				Event_Queue_WaitFrames(41);
				Event_Queue_PlaySound(SND_poison);
				Event_Queue_Object_ChangeSpriteFrame(10, 1);
				Event_Queue_WaitFrames(30);
				Event_Queue_CreateObject(70, 1, SPR_misc_collapseblood, 7452, 7239, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_ChangeSpriteFrame(70, 1);
				Event_Queue_WaitFrames(120);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_WaitFrames(12);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_ChangeSpriteFrame(0, 0);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetFlag(FLAG_ALONE_PLOT, 20);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_dia);
				Event_Queue_Object_JumpToRelative(10, 8, 0, OBJECT_DIRECTION_LEFT, 0, 4);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(953);
				Event_Queue_Object_WalkTo(10, 7528, 7264, 2, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_Label(0);
			}
			else {
				Event_Queue_Dialog_Run(525);
				Event_Queue_Object_WalkToRelative(10, -8, 0, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(10, SPR_misc_dia_hug);
				Event_Queue_WaitFrames(83);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_dia);
				Event_Queue_Object_JumpToRelative(10, 8, 0, OBJECT_DIRECTION_LEFT, 0, 4);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_WalkTo(10, 7528, 7264, 2, OBJECT_DIRECTION_DOWN);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 73);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 28: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Dialog_Run(540);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(15576, 3704, 1);
			Event_Queue_Object_WalkTo(0, 15576, 3688, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(1, 15544, 3664, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(2, 15608, 3664, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_WalkTo(3, 15576, 3640, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(10);
			Event_Queue_PlayMusic(MUS_lu);
			if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(541);
			Event_Queue_Dialog_Run(profile.flags[FLAG_FUN] % 3 == 2 ? 568 : 542);
			if (profile.flags[FLAG_ALONE_PLOT] >= 11) {
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(564);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(565);
			}
			else {
				Event_Queue_Dialog_Run(543);
				Event_Queue_Dialog_Run(544);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(545);
				if (!profile.flags[FLAG_ALONE]) {
					Event_Queue_Dialog_Run(546);
					Event_Queue_Object_EnableFighterSprite(10, 16, 16, FIGHTER_STATE_ATTACK1);
					Event_Queue_Dialog_Run(547);
				}
			}
			Event_Queue_EngageBattle(21, 10);
			Event_Queue_Object_EnableFighterSprite(10, 16, 16, FIGHTER_STATE_HURT);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_Dialog_Run(548);
			Event_Queue_CreateObject(70, 1, SPR_owchar_josh, 15392, 3856, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(15576, 3752, 1);
			Event_Queue_Object_WalkTo(70, 15544, 3856, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(15576, 3736, 0.5);
			Event_Queue_Object_WalkTo(70, 15576, 3808, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(549);
			Event_Queue_Dialog_Run(550);
			Event_Queue_Object_EnableFighterSprite(70, 32, 34, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(551);
			Event_Queue_Dialog_Run(552);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_WalkTo(70, 15576, 3784, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(553);
			Event_Queue_Object_EnableFighterSprite(10, 16, 15, FIGHTER_STATE_HURT);
			Event_Queue_Dialog_Run(554);
			Event_Queue_Object_EnableFighterSprite(70, 32, 34, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(555);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_EnableFighterSprite(11, 31, 33, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(556);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(12, 31, 33, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(557);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkTo(10, 15576, 3760, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_Object_DisableFighterSprite(12);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_DisableFighterSprite(70);
			if (profile.flags[FLAG_ALONE])
				Event_Queue_Dialog_Run(566);
			else
				Event_Queue_Dialog_Run(558);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(10, 15528, 3816, 3, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_ALONE])
				Event_Queue_Dialog_Run(567);
			else
				Event_Queue_Dialog_Run(559);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Object_WalkTo(10, 15208, 3918, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_Destroy(10);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(560);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(15576, 3680, 1);
			Event_Queue_Object_WalkToRelative(70, 0, 112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToRelative(11, 0, 112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToRelative(12, 0, 112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_Destroy(11);
			Event_Queue_Object_Destroy(12);
			Event_Queue_WaitFrames(20);
			if (profile.flags[FLAG_ALONE_PLOT] < 11) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(561);
				Event_Queue_Dialog_Run(562);
				Event_Queue_Dialog_Run(563);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_PlayMusic(MUS_town);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 74);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			
			Overworld_CreateTrigger(1, 20192, 7104, 20256, 7200, 29);
		} break;
		
		case 29: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Object_ToggleWalkAnimation(0, false);
			Event_Queue_Object_ToggleWalkAnimation(1, false);
			Event_Queue_Object_ToggleWalkAnimation(2, false);
			Event_Queue_Object_ToggleWalkAnimation(3, false);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_HURT);
			Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_HURT);
			Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_HURT);
			Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_HURT);
			Event_Queue_SetSync(true);
			Event_Queue_CreateObject(70, 1, SPR_owchar_lulu_omega, 20200, 7152, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_ATTACK3);
			Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
			Event_Queue_WaitFrames(1);
			Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
			Event_Queue_Object_WalkTo(0, 20096, 7152, 8, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 20064, 7120, 8, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 20064, 7184, 8, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(3, 20032, 7152, 8, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ToggleWalkAnimation(0, true);
			Event_Queue_Object_ToggleWalkAnimation(1, true);
			Event_Queue_Object_ToggleWalkAnimation(2, true);
			Event_Queue_Object_ToggleWalkAnimation(3, true);
			Event_Queue_WaitFrames(120);
			Event_Queue_Camera_MoveTo(20144, 7144, 1);
			Event_Queue_PlayMusic(MUS_lastresort_intro);
			Event_Queue_Dialog_Run(570);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_IDLE);
			Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_IDLE);
			Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_IDLE);
			Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_IDLE);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(571);
			Event_Queue_Dialog_Run(572);
			Event_Queue_Dialog_Run(573);
			Event_Queue_Dialog_Run(574);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_BLOCK);
			Event_Queue_Dialog_Run(575);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_omega_rage);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(576);
			
			Event_Queue_SetFlag(FLAG_OMEGALULU_GAMEOVER, 1);
			Event_Queue_EngageBattle(191, 70);
			
			Event_Queue_PlayMusic(MUS_bother);
			Event_Queue_Dialog_Run(584);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 30: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_Overworld_ShakeScreen(8);
			Event_Queue_Object_Destroy(30);
			Event_Queue_WaitFrames(90);
			Event_Queue_CreateNPC(30, 28, 6584, 3928, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateNPC(31, 28, 6616, 3928, OBJECT_DIRECTION_DOWN);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_BRICKWALL_REMOVED, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 31: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(19944, 10232, 1);
			Event_Queue_Object_WalkTo(0, 19968, 10256, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 19944, 10272, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 19920, 10272, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 19896, 10272, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(590);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_WalkToRelative(0, 0, -8, 0.25, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteId(11, SPR_misc_neveah_prepare);
				Event_Queue_Dialog_Run(603);
				Event_Queue_Object_ChangeSpriteId(10, SPR_misc_kelly_prepare);
				Event_Queue_Dialog_Run(604);
			}
			else {
				Event_Queue_Dialog_Run(591);
				Event_Queue_Dialog_Run(592);
				Event_Queue_Dialog_Run(593);
				Event_Queue_Dialog_Run(594);
				Event_Queue_Dialog_Run(595);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteId(10, SPR_misc_kelly_prepare);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(596);
				Event_Queue_Dialog_Run(597);
				Event_Queue_Object_WalkTo(3, 19912, 10240, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_ATTACK1);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(598);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteId(11, SPR_misc_neveah_prepare);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(599);
				Event_Queue_Dialog_Run(600);
			}
			
			Event_Queue_EngageBattle(56, 10);
			Event_Queue_Object_DisableFighterSprite(3);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_kelly);
			Event_Queue_Object_ChangeSpriteId(11, SPR_owchar_neveah);
			Event_Queue_Object_EnableFighterSprite(10, 46, 51, FIGHTER_STATE_HURT);
			Event_Queue_Object_EnableFighterSprite(11, 47, 52, FIGHTER_STATE_HURT);
			
			Event_Queue_Dialog_Run(601);
			Event_Queue_Dialog_Run(602);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(11, 19968, 10216, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportTo(11, 19968, 9216);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(19936, 10160, 2);
			Event_Queue_Object_WalkTo(10, 19968, 10216, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportTo(10, 19968, 9216);
			Event_Queue_SetSync(true);
			Event_Queue_Object_TeleportTo(11, 19928, 10144);
			Event_Queue_Object_WalkTo(11, 19928, 10072, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportTo(10, 19928, 10144);
			Event_Queue_Object_WalkTo(10, 19928, 10072, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_Destroy(11);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_Destroy(10);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(70);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 102);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 32: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(20104, 10112, 1);
			Event_Queue_Object_WalkTo(0, 20120, 10152, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 20088, 10152, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 20104, 10168, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 20104, 10112, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(610);
			Event_Queue_Dialog_Run(611);
			Event_Queue_Object_WalkToRelative(3, 0, 16, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(10);
			Event_Queue_Dialog_Run(612);
			Event_Queue_SetSync(true);
			Event_Queue_Dialog_Run(613);
			Event_Queue_Object_WalkTo(3, 20104, 10072, 3, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_TeleportTo(3, 19968, 9216);
			Event_Queue_WaitFrames(7);
			Event_Queue_SetSync(false);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 20104, 10072, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_WalkTo(1, 20104, 10072, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_WalkTo(2, 20104, 10072, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(20);
			Event_Queue_GotoArea(83, 20088, 9896, -1);
			Event_Queue_SetSync(false);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_TeleportTo(1, 20064, 9896);
			Event_Queue_Object_TeleportTo(2, 20104, 9916);
			Event_Queue_Object_TeleportTo(3, 20104, 9864);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(614);
			Event_Queue_Dialog_Run(615);
			Event_Queue_Dialog_Run(617);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(618);
			Event_Queue_Dialog_Run(616);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(619);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 103);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 33: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(20128, 10144, 1);
			Event_Queue_Object_WalkTo(0, 20120, 10168, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 20120, 10152, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 20120, 10136, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(3, 20152, 10152, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(620);
			Event_Queue_Object_WalkToRelative(3, -16, 0, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(25);
			Event_Queue_Object_WalkTo(3, 20192, 10152, 3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_TeleportTo(3, 19968, 9216);
			Event_Queue_SetSync(true);
			Event_Queue_WaitFrames(3);
			Event_Queue_Object_WalkTo(0, 20192, 10152, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_WalkTo(1, 20192, 10152, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_WalkTo(2, 20192, 10152, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(20);
			Event_Queue_GotoArea(84, 20328, 10152, -1);
			Event_Queue_SetSync(false);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_TeleportTo(1, 20312, 10132);
			Event_Queue_Object_TeleportTo(2, 20312, 10172);
			Event_Queue_Object_TeleportTo(3, 20376, 10152);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(621);
			Event_Queue_Dialog_Run(622);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 104);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 34: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 20008, 9848, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 20040, 9848, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 20056, 9872, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(3, 20000, 9880, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(630);
			Event_Queue_Dialog_Run(631);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(632);
			Event_Queue_Object_WalkTo(3, 19992, 9880, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(633);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(634);
			Event_Queue_Object_WalkToPointer(11, -40, 0, 0.5, OBJECT_DIRECTION_RIGHT, &overworld.objects[3].x, &overworld.objects[3].y);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(35);
			Event_Queue_Object_WalkToRelative(11, 4, 0, 0.0625, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(1);
			Event_Queue_Object_EnableFighterSprite(11, 47, 52, FIGHTER_STATE_ATTACK1);
			Event_Queue_WaitFrames(8);
			Event_Queue_PlaySound(SND_hit1);
			Event_Queue_Object_EnableFighterSprite(11, 47, 52, FIGHTER_STATE_ATTACK2);
			Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_HURT);
			Event_Queue_Object_ToggleWalkAnimation(3, false);
			Event_Queue_Object_WalkToRelative(3, 28, 0, 4, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ToggleWalkAnimation(3, true);
			Event_Queue_WaitFrames(14);
			Event_Queue_Dialog_Run(635);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(11, 19976, 9900, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(11, 20104, 9900, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(11, 20104, 9920, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(4);
			Event_Queue_Object_WalkTo(10, 19944, 9900, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(10, 20104, 9900, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(10, 20104, 9920, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(62);
			Event_Queue_Object_Destroy(11);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_Destroy(10);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(56);
			Event_Queue_Object_DisableFighterSprite(3);
			Event_Queue_WaitFrames(36);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(636);
			Event_Queue_Dialog_Run(637);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 106);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 35: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(20016, 11040, 1);
			Event_Queue_Object_WalkTo(0, 20016, 11104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 19984, 11136, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 20048, 11136, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 20016, 11168, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(730);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(20);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(20016, 11088, 1);
				Event_Queue_Object_WalkTo(10, 20016, 11048, 0.5, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_PlayMusic(MUS_blue);
				Event_Queue_Dialog_Run(1040);
				Event_Queue_Dialog_Run(1041);
				Event_Queue_Dialog_Run(1042);
				
				Event_Queue_Object_JumpTo(10, 20016, 11060, OBJECT_DIRECTION_DOWN, 32, 20);
				Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
				Event_Queue_WaitFrames(1);
				Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
				Event_Queue_PlaySound(SND_thunder);
				Event_Queue_Overworld_ShakeScreen(30);
				Event_Queue_Dialog_Run(1043);
			}
			else {
				Event_Queue_Dialog_Run(731);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(20);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(20016, 11088, 1);
				Event_Queue_Object_WalkTo(10, 20016, 11048, 0.5, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(732);
				Event_Queue_Dialog_Run(733);
				Event_Queue_Dialog_Run(734);
				Event_Queue_Dialog_Run(735);
				Event_Queue_Dialog_Run(736);
				Event_Queue_Dialog_Run(737);
				Event_Queue_Dialog_Run(738);
				Event_Queue_Dialog_Run(739);
				Event_Queue_Dialog_Run(740);
				Event_Queue_Object_WalkTo(3, 20016, 11136, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(3, 20072, 11048, 2, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(741);
				Event_Queue_Dialog_Run(742);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(743);
				Event_Queue_Object_WalkTo(10, 20056, 11048, 6, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_EnableFighterSprite(10, 35, 37, FIGHTER_STATE_ATTACK1);
				Event_Queue_PlaySound(SND_hit3);
				Event_Queue_Overworld_ShakeScreen(10);
				Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_collapse_sally);
				Event_Queue_Object_ChangeSpriteFrame(3, 0);
				Event_Queue_Object_JumpTo(3, 20016, 11156, OBJECT_DIRECTION_DOWN, 14, 17);
				Event_Queue_PlaySound(SND_poison);
				Event_Queue_Object_ChangeSpriteFrame(3, 1);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(30);
				Event_Queue_PlayMusic(MUS_blue);
				Event_Queue_Dialog_Run(744);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_DisableFighterSprite(10);
				Event_Queue_Object_WalkTo(10, 20016, 11048, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(745);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(746);
				Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
				Event_Queue_WaitFrames(1);
				Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
				Event_Queue_PlaySound(SND_thunder);
				Event_Queue_Overworld_ShakeScreen(30);
				Event_Queue_Dialog_Run(747);
				Event_Queue_Dialog_Run(748);
				Event_Queue_Dialog_Run(749);
				Event_Queue_Object_JumpTo(10, 20016, 11060, OBJECT_DIRECTION_DOWN, 32, 20);
				Event_Queue_Dialog_Run(750);
			}
			
			Event_Queue_EngageBattle(41, 10);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_sally);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			}
			Event_Queue_Object_TeleportTo(10, 20016, 11056);
			Event_Queue_Dialog_Run(751);
			Event_Queue_Dialog_Run(752);
			Event_Queue_Dialog_Run(753);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(754);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(755);
			Event_Queue_Regroup(1);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(756);
			}
			
			Event_Queue_RemoveCurrentTrigger();
			if (profile.flags[FLAG_PLOT] < 112) Event_Queue_SetFlag(FLAG_PLOT, 112);
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 112);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 36: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Dialog_Run(770);
			Event_Queue_Dialog_Run(771);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(772);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(30);
			Event_Queue_Camera_MoveTo(23088, 4448, 1);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_BLOCK);
			Event_Queue_WaitFrames(18);
			Event_Queue_Object_ToggleGhost(70, true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(22984, 4720, 3);
			Event_Queue_WaitFrames(72);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_RUN);
			Event_Queue_Object_JumpTo(70, 23024, 4720, OBJECT_DIRECTION_LEFT, 8, 24);
			Event_Queue_SetSync(false);
			
			Event_Queue_Object_ToggleGhost(70, false);
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(true);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_ATTACK3);
			Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
			Event_Queue_WaitFrames(1);
			Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
			Event_Queue_Object_JumpTo(0, 22952, 4720, OBJECT_DIRECTION_RIGHT, 8, 8);
			Event_Queue_Object_JumpTo(1, 22936, 4696, OBJECT_DIRECTION_RIGHT, 8, 8);
			Event_Queue_Object_JumpTo(2, 22920, 4720, OBJECT_DIRECTION_RIGHT, 8, 8);
			Event_Queue_Object_JumpTo(3, 22904, 4696, OBJECT_DIRECTION_RIGHT, 8, 8);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_PlayMusic(MUS_lu);
			Event_Queue_Dialog_Run(773);
			Event_Queue_Dialog_Run(774);
			Event_Queue_Dialog_Run(775);
			Event_Queue_Dialog_Run(776);
			Event_Queue_Dialog_Run(777);
			Event_Queue_Dialog_Run(778);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(70, 70);
			Event_Queue_Object_Destroy(70);
			Event_Queue_CreateNPC(70, 88, 23024, 4720, OBJECT_DIRECTION_DOWN);
			
			/*Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_HURT);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Object_WalkTo(70, 23112, 4744, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(70, 23160, 4952, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_Destroy(70);*/
			
			Event_Queue_Regroup(1);
			Event_Queue_PlayMusic(MUS_city);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 113);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 37: {
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_RemoveCurrentTrigger();
				Event_Queue_SetFlag(FLAG_PLOT, 116);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				break;
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(17816, 11112, 1);
			Event_Queue_Object_WalkTo(0, 17848, 11144, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 17848, 11096, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 17736, 11112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(3, 17784, 11128, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_WalkTo(2, 17752, 11144, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(780);
			Event_Queue_Dialog_Run(781);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(782);
			Event_Queue_Dialog_Run(783);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 17808, 11112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 17776, 11112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(2, 17712, 11112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(3, 17744, 11112, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(784);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_Dialog_Run(785);
			Event_Queue_Dialog_Run(786);
			Event_Queue_Dialog_Run(787);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 116);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 38: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_SetFlag(FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR, 0);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkToPointer(70, 32, 0, 1, OBJECT_DIRECTION_LEFT, &overworld.player.x, &overworld.player.y);
			Event_Queue_WaitFrames(12);
			Event_Queue_Dialog_Run(2101);
			Event_Queue_Dialog_Run(2102);
			Event_Queue_Dialog_Run(2103);
			Event_Queue_Dialog_Run(2104);
			Event_Queue_Dialog_Run(2105);
			Event_Queue_Dialog_Run(2106);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(2107);
			Event_Queue_Dialog_Run(2108);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			}
			else {
				Event_Queue_Dialog_Run(2109);
				Event_Queue_Dialog_Run(2110);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Dialog_Run(2111);
			}
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_Party_Leave(1);
			Event_Queue_Party_Leave(2);
			Event_Queue_Party_Leave(3);
			
			Event_Queue_GotoArea(92, 18456, 12168, -1);
			Event_Queue_Camera_TeleportTo(18456, 12120);
			Event_Queue_Object_WalkTo(0, 18432, 12144, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(31);
			Event_Queue_Object_WalkTo(70, 18456, 12096, 2, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(20);
			Event_Queue_Dialog_Run(2112);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_WaitFrames(10);
			Event_Queue_PlaySound(SND_elevator);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(60);
			Event_Queue_PlaySound(SND_chess_mate);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_WalkTo(70, 18456, 12176, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_PLOT, 117);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 39: {
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 118);
			Event_Queue_Object_WalkTo(70, 18136, 11632, 3, OBJECT_DIRECTION_UP);
			Event_Queue_Object_Destroy(70);
		} break;
		
		case 40: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(80);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(2440, 10848, 1);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_WalkTo(0, 2440, 10904, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(110);
			Event_Queue_Dialog_Run(3128);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(3129);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(3130);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_WaitFrames(70);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(55, -1);
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_WaitFrames(120);
			Event_Queue_GotoArea(231, 1416, 12136, -1);
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_Overworld_FadeOut(300, 0, 0, 0);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_PLOT, 121);
			Event_Queue_SetFlag(FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			overworld.map.doors[69].enabled = true;
		} break;
		
		case 41: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(10, 36, 38, FIGHTER_STATE_RUN);
			Event_Queue_Object_EnableFighterSprite(11, 36, 38, FIGHTER_STATE_RUN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpTo(10, 7976, 13592, OBJECT_DIRECTION_LEFT, 30, 22);
			Event_Queue_Object_JumpTo(11, 8040, 13592, OBJECT_DIRECTION_RIGHT, 30, 22);
			Event_Queue_SetSync(false);
			Event_Queue_Object_EnableFighterSprite(10, 36, 38, FIGHTER_STATE_IDLE);
			Event_Queue_Object_EnableFighterSprite(11, 36, 38, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(820);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(40);
			Event_Queue_Camera_MoveTo(8008, 13584, 2);
			Event_Queue_Dialog_Run(821);
			Event_Queue_Dialog_Run(822);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(823);
			
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_CreateObject(70, 1, SPR_owchar_volcano, 8008, 13560, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(70);
			Event_Queue_Dialog_Run(824);
			Event_Queue_Object_WalkTo(70, 8008, 13568, 0.125, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(825);
			Event_Queue_Dialog_Run(826);
			Event_Queue_WaitFrames(80);
			Event_Queue_Overworld_ShakeScreen(24);
			Event_Queue_SetSync(true);
			Event_Queue_Dialog_Run(827);
			Event_Queue_Object_JumpToRelative(10, 0, 0, -1, 12, 10);
			Event_Queue_Object_JumpToRelative(11, 0, 0, -1, 12, 10);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(828);
			Event_Queue_Object_EnableFighterSprite(10, 36, 38, FIGHTER_STATE_RUN);
			Event_Queue_Object_EnableFighterSprite(11, 36, 38, FIGHTER_STATE_RUN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpTo(10, 7944, 13464, OBJECT_DIRECTION_DOWN, 30, 22);
			Event_Queue_Object_JumpTo(11, 8072, 13464, OBJECT_DIRECTION_DOWN, 30, 22);
			Event_Queue_SetSync(false);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_WaitFrames(30);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(8008, 13568, 0.5);
			Event_Queue_Object_WalkTo(0, 8008, 13608, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 7976, 13632, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 8040, 13632, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 8008, 13656, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(829);
			Event_Queue_Dialog_Run(830);
			Event_Queue_Dialog_Run(831);
			Event_Queue_Dialog_Run(832);
			Event_Queue_Dialog_Run(833);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(842);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(837);
				Event_Queue_Dialog_Run(843);
			}
			else {
				Event_Queue_Dialog_Run(834);
				Event_Queue_Dialog_Run(835);
				Event_Queue_Dialog_Run(836);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(837);
				Event_Queue_Dialog_Run(838);
			}
			Event_Queue_Dialog_Run(839);
			Event_Queue_Object_WalkTo(70, 8008, 13552, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_Object_Destroy(70);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_WaitFrames(32);
				Event_Queue_Dialog_Run(840);
				Event_Queue_Dialog_Run(841);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 132);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 42: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_WaitFrames(20);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(6344, 12856, 0.5);
			Event_Queue_Object_WalkTo(10, 6344, 12808, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_WalkTo(0, 6344, 12888, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_WalkTo(1, 6344, 12968, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(1, 6312, 12912, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_WalkTo(2, 6344, 12968, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(2, 6376, 12912, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_WalkTo(3, 6344, 12936, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(850);
			Event_Queue_Dialog_Run(851);
			Event_Queue_Dialog_Run(852);
			Event_Queue_Dialog_Run(853);
			Event_Queue_Dialog_Run(854);
			Event_Queue_Dialog_Run(855);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(856);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(897);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(898);
			}
			else {
				Event_Queue_Dialog_Run(857);
				Event_Queue_Dialog_Run(858);
				Event_Queue_Dialog_Run(859);
				Event_Queue_Dialog_Run(860);
				Event_Queue_Dialog_Run(861);
				Event_Queue_Overworld_ShakeScreen(24);
				Event_Queue_Dialog_Run(862);
				Event_Queue_Dialog_Run(863);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(864);
			}
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(3);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(2);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_PlaySound(SND_mana);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_ATTACK3);
			Event_Queue_WaitFrames(5);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_ATTACK1);
			Event_Queue_WaitFrames(8);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_SPECIAL1);
			Event_Queue_WaitFrames(8);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_ATTACK1);
			Event_Queue_WaitFrames(8);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_SPECIAL1);
			Event_Queue_WaitFrames(8);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_ATTACK1);
			Event_Queue_WaitFrames(5);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_EnableFighterSprite(10, 55, 61, FIGHTER_STATE_BLOCK);
			Event_Queue_WaitFrames(12);
			Event_Queue_PlaySound(SND_swing);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_JumpToRelative(10, 0, 0, OBJECT_DIRECTION_DOWN, 24, 24);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(865);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(64, 10);
			
			Event_Queue_WaitFrames(120);
			Event_Queue_Dialog_Run(866);
			Event_Queue_Dialog_Run(867);
			if (profile.flags[FLAG_ALONE])
				Event_Queue_WaitFrames(30);
			else
				Event_Queue_Dialog_Run(868);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(869);
			Event_Queue_Object_WalkTo(10, 6344, 12840, 0.5, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(870);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 133);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 43: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			if (overworld.player.y <= 12480) {
				Event_Queue_Camera_MoveTo(8008, 12456, 1);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 8008, 12456, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(2, 7976, 12408, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(1, 8008, 12408, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(3, 8040, 12408, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
			}
			else {
				Event_Queue_Camera_MoveTo(8008, 12504, 1);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 8008, 12504, 1, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(2, 7976, 12552, 1, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(1, 8008, 12552, 1, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(3, 8040, 12552, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
			}
			Event_Queue_Object_ToggleGhost(12, true);
			Event_Queue_Object_WalkToPointer(12, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(12, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_Destroy(12);
			Event_Queue_CreateNPC(12, 70000, 8008, 12476, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(253);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3073);
			
			if (overworld.player.y <= 12480) {
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(8008, 12504, 1);
				Event_Queue_Object_WalkTo(0, 7992, 12488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(0, 8008, 12504, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(2, 7992, 12488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(2, 7976, 12552, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(1, 8040, 12488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(1, 8008, 12552, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(15);
				Event_Queue_Object_WalkTo(3, 8040, 12488, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(3, 8040, 12552, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 134);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 44: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2115);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 45: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(9352, 9184, 1);
			Event_Queue_Object_WalkTo(0, 9352, 9192, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(68);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_JumpToRelative(10, 0, 0, OBJECT_DIRECTION_DOWN, 12, 12);
			Event_Queue_WaitFrames(24);
			Event_Queue_Dialog_Run(663);
			Event_Queue_Object_WalkTo(10, 9456, 9160, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(10);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(9408, 9168, 0.5);
			Event_Queue_Object_WalkTo(0, 9368, 9176, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(664);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(665);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(666);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(667);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_collapse_perry);
			Event_Queue_Object_ChangeSpriteFrame(10, 0);
			Event_Queue_Dialog_Run(668);
			Event_Queue_Object_WalkTo(0, 9384, 9176, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(20);
			Event_Queue_Dialog_Run(669);
			Event_Queue_WaitFrames(45);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(10, 57, 67, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(677);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Dialog_Run(678);
			Event_Queue_Dialog_Run(679);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(1);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(69, 10);
			
			Event_Queue_Object_Destroy(10);
			Event_Queue_CreateNPC(10, 58, 9450, 9160, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(11, 1, SPR_misc_collapseblood, 9450, 9159, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(11, 2);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetFlag(FLAG_ALONE_PLOT, 10);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
			Event_Queue_WaitFrames(60);
			Event_Queue_Player_SetPositionSync(false);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(695);
			Event_Queue_Dialog_Run(696);
			Event_Queue_Dialog_Run(697);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_perry);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(698);
			Event_Queue_Dialog_Run(699);
			Event_Queue_Object_WalkTo(10, 9400, 9176, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(727);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(728);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(10, 9320, 9208, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(729);
			Event_Queue_Object_WalkTo(10, 9244, 9208, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(10, 9244, 9000, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_Destroy(10);
			Event_Queue_PlayMusic(MUS_cave);
			Event_Queue_SetFlag(FLAG_ALONE_PERRY_SPARED, 1);
			
			Event_Queue_Label(0);
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 46: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_Object_EnableFighterSprite(1, 4, 5, FIGHTER_STATE_HURT);
			Event_Queue_PlaySound(SND_hit1);
			Event_Queue_Object_WalkToRelative(0, 48, 0, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(14);
			Event_Queue_Party_Leave(3);
			Event_Queue_Object_DisableFighterSprite(1);
			Event_Queue_CreateObject(70, 1, SPR_owchar_sally, 9336, 9720, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(73, 1, SPR_misc_web, 9336, 9720, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_EnableFighterSprite(70, 4, 5, FIGHTER_STATE_HURT);
			Event_Queue_PlaySound(SND_hit3);
			Event_Queue_StopMusic();
			Event_Queue_Dialog_Run(700);
			Event_Queue_Dialog_Run(680);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_WalkTo(0, 9336, 9840, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(0, 9336, 9784, 1, OBJECT_DIRECTION_UP);
			Event_Queue_PlayMusic(MUS_scary);
			Event_Queue_Dialog_Run(701);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(702);
			
			Event_Queue_CreateNPC(71, 10035, 9336, 9720, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateTrigger(2, 9312, 9824, 9344, 9872, 47);
			Event_Queue_CreateTrigger(3, 9392, 9824, 9408, 9872, 48);
			Event_Queue_CreateTrigger(4, 9248, 9824, 9264, 9872, 48);
			Event_Queue_CreateTrigger(5, 9520, 9824, 9536, 9872, 49);
			Event_Queue_CreateTrigger(6, 9120, 9824, 9136, 9872, 49);
			
			Event_Queue_Regroup(2);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_SALLY_SPIDERTRAP, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 47: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_ALONE_PLOT] >= 10) {
				Event_Queue_Dialog_Run(703);
				Event_Queue_RemoveCurrentTrigger();
			}
			else {
				Event_Queue_Dialog_Run(708);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 48: {
			overworld.map.triggers[3].eventId = 0;
			overworld.map.triggers[4].eventId = 0;
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(704);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 49: {
			for (int i = 0; i < 6; i++) {
				Profile_UnequipAction(3, 0);
				Profile_UnequipPassive(3, 0);
			}
			Profile_UnequipArmor(3);
			overworld.map.triggers[0].eventId = 0;
			overworld.map.triggers[5].eventId = 0;
			overworld.map.triggers[6].eventId = 0;
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_PlaySound(SND_hit3);
			Event_Queue_WaitFrames(33);
			Event_Queue_PlaySound(SND_hit3);
			Event_Queue_WaitFrames(12);
			Event_Queue_PlaySound(SND_hit3);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_Destroy(71);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Object_Destroy(11);
			Event_Queue_Object_Destroy(12);
			Event_Queue_Object_Destroy(13);
			Event_Queue_WaitFrames(90);
			Event_Queue_Profile_InventoryPartyOrderRemove(3);
			Event_Queue_SetFlag(FLAG_SALLY_JOINED, 0);
			Event_Queue_SetFlag(FLAG_PLOT, 71);
			Event_Queue_SetFlag(FLAG_ALONE_PLOT, 11);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 50: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TeleportTo(17560, 12920);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_WaitFrames(120);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(17560, 13208, 2);
			Event_Queue_Object_WalkTo(0, 17560, 13216, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 17560, 13240, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 17560, 13264, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 17560, 13288, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(17560, 12968, 2);
			Event_Queue_Object_WalkTo(0, 17560, 13000, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 17528, 13032, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 17592, 13032, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 17560, 13064, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_WaitFrames(60);
			if (profile.flags[FLAG_ALONE])
				Event_Queue_Dialog_Run(1050);
			else
				Event_Queue_Dialog_Run(871);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_JumpTo(11, 17560, 12952, OBJECT_DIRECTION_DOWN, 8, 16);
			Event_Queue_WaitFrames(90);
			Event_Queue_PlayMusic(MUS_blue);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(872);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] >= 134) {
				Event_Queue_Dialog_Run(873);
				Event_Queue_Object_WalkTo(11, 17560, 12968, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(901);
				Event_Queue_Dialog_Run(902);
				Event_Queue_Dialog_Run(903);
				Event_Queue_Dialog_Run(904);
				Event_Queue_Dialog_Run(905);
				Event_Queue_Object_WalkToRelative(12, 0, 8, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(906);
				Event_Queue_Object_WalkToRelative(13, 0, 8, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(907);
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(908);
				Event_Queue_Dialog_Run(909);
				
				Event_Queue_EngageBattle(63, 11);
				Event_Queue_Object_TeleportTo(12, 17528, 12968);
				Event_Queue_Object_TeleportTo(13, 17592, 12968);
				
				Event_Queue_Dialog_Run(885);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(910);
				Event_Queue_Dialog_Run(911);
				Event_Queue_Dialog_Run(912);
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(913);
				Event_Queue_Dialog_Run(914);
			}
			else if (profile.flags[FLAG_ALONE] && profile.flags[FLAG_ALONE_PLOT] >= 20) {
				Event_Queue_Dialog_Run(1051);
				Event_Queue_Object_WalkTo(11, 17560, 12968, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1052);
				Event_Queue_Dialog_Run(1053);
				Event_Queue_Object_WalkToRelative(12, 0, 8, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1054);
				Event_Queue_Dialog_Run(1055);
				Event_Queue_Object_WalkToRelative(13, 0, 8, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(909);
				
				Event_Queue_EngageBattle(63, 11);
				Event_Queue_Object_TeleportTo(0, 17560, 13016);
				Event_Queue_Object_TeleportTo(12, 17528, 12968);
				Event_Queue_Object_TeleportTo(13, 17592, 12968);
				
				Event_Queue_Dialog_Run(885);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run);
				Event_Queue_Object_ChangeSpriteFrame(0, 7);
				Event_Queue_Dialog_Run(1056);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_CreateObject(70, 1, SPR_misc_rubydart, 17560, 12999, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(70, 17560, 12982, 5, -1);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_StopMusic();
				Event_Queue_Object_ChangeSpriteId(11, SPR_owchar_collapse_luna);
				Event_Queue_Object_ChangeSpriteFrame(11, 0);
				Event_Queue_Object_TeleportTo(11, 17558, 12968);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_TeleportTo(11, 17562, 12968);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_TeleportTo(11, 17559, 12968);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_TeleportTo(11, 17561, 12968);
				Event_Queue_WaitFrames(9);
				Event_Queue_Object_TeleportTo(11, 17559, 12968);
				Event_Queue_WaitFrames(9);
				Event_Queue_Object_TeleportTo(11, 17560, 12968);
				Event_Queue_WaitFrames(20);
				Event_Queue_PlaySound(SND_goner);
				Event_Queue_Object_Destroy(70);
				Event_Queue_CreateSpark(2, 17560, 12968, 0);
				Event_Queue_WaitFrames(4);
				Event_Queue_CreateSpark(2, 17560, 12968, 0);
				Event_Queue_WaitFrames(4);
				Event_Queue_CreateSpark(2, 17560, 12968, 0);
				Event_Queue_WaitFrames(4);
				Event_Queue_CreateSpark(2, 17560, 12968, 0);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(67);
				Event_Queue_Dialog_Run(1057);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(1060);
				Event_Queue_Dialog_Run(1071);
				Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_TeleportTo(11, 17559, 12968);
				Event_Queue_WaitFrames(9);
				Event_Queue_Object_TeleportTo(11, 17561, 12968);
				Event_Queue_WaitFrames(9);
				Event_Queue_Object_TeleportTo(11, 17559, 12968);
				Event_Queue_WaitFrames(9);
				Event_Queue_Object_TeleportTo(11, 17560, 12968);
				Event_Queue_WaitFrames(26);
				Event_Queue_Object_ChangeSpriteId(11, SPR_misc_luna_pain);
				Event_Queue_Dialog_Run(1058);
				Event_Queue_WaitFrames(52);
				Event_Queue_PlaySound(SND_poison);
				Event_Queue_Object_ChangeSpriteId(11, SPR_owchar_collapse_luna);
				Event_Queue_Object_ChangeSpriteFrame(11, 1);
				Event_Queue_Object_ChangeSpriteId(13, SPR_misc_nate_worried);
				Event_Queue_WaitFrames(64);
				Event_Queue_PlayMusic(MUS_oh);
				Event_Queue_Dialog_Run(1059);
				Event_Queue_Object_ChangeSpriteId(13, SPR_owchar_nate);
				Event_Queue_Object_WalkTo(13, 17568, 12992, 2, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(58);
				Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1061);
				Event_Queue_Dialog_Run(1062);
				Event_Queue_Dialog_Run(1063);
				Event_Queue_Dialog_Run(1064);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(1065);
				Event_Queue_Dialog_Run(1066);
				Event_Queue_Object_WalkToRelative(12, 0, 8, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Dialog_Run(1067);
				Event_Queue_Dialog_Run(1068);
				Event_Queue_Object_ChangeSpriteId(13, SPR_misc_nate_worried);
				Event_Queue_Dialog_Run(1069);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
				Event_Queue_Dialog_Run(1070);
				Event_Queue_FadeOutMusic(2000);
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_WaitFrames(150);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_SetFlag(FLAG_ALONE_PLOT, 30);
				Event_Queue_SetFlag(FLAG_LUNA_OPTIONALFIGHT, 1);
				Event_Queue_GotoArea(98, 24840, 11352, -1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				break;
			}
			else {
				Event_Queue_Dialog_Run(873);
				Event_Queue_Dialog_Run(874);
				Event_Queue_Dialog_Run(875);
				Event_Queue_Object_WalkTo(11, 17560, 12968, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(876);
				Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(877);
				Event_Queue_Dialog_Run(878);
				Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(879);
				Event_Queue_Dialog_Run(880);
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(881);
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(882);
				Event_Queue_Dialog_Run(883);
				Event_Queue_Dialog_Run(884);
				
				Event_Queue_EngageBattle(63, 11);
				
				Event_Queue_Dialog_Run(885);
				Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE]) ? 896 : 886);
				Event_Queue_Dialog_Run(887);
				Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE]) ? 2238 : 888);
				Event_Queue_Dialog_Run(889);
				Event_Queue_Dialog_Run(890);
				Event_Queue_Dialog_Run(891);
				Event_Queue_Dialog_Run(892);
				Event_Queue_Dialog_Run(893);
				Event_Queue_Dialog_Run(894);
				Event_Queue_Dialog_Run(895);
			}
			Event_Queue_Object_WalkTo(11, 17560, 12952, 0.25, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_JumpTo(11, 17560, 12944, OBJECT_DIRECTION_DOWN, 8, 16);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_WaitFrames(80);
			
			Event_Queue_PlayMusic(MUS_ozone);
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_LUNA_OPTIONALFIGHT, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 51: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(710);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(19288, 10584, 1);
			Event_Queue_Object_WalkTo(0, 19292, 10608, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 19280, 10632, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 19300, 10632, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 19320, 10632, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(724);
				Event_Queue_Dialog_Run(712);
				Event_Queue_Dialog_Run(713);
				Event_Queue_WaitFrames(28);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(716);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(725);
				Event_Queue_Dialog_Run(718);
				Event_Queue_SetSync(true);
				Event_Queue_Object_ToggleGhost(10, true);
				Event_Queue_Object_WalkToRelative(10, 16, 0, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(10, 19272, 10568, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(11, 19304, 10568, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(726);
			}
			else {
				Event_Queue_Dialog_Run(711);
				Event_Queue_Dialog_Run(712);
				Event_Queue_Dialog_Run(713);
				Event_Queue_Dialog_Run(714);
				Event_Queue_Dialog_Run(715);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(716);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(717);
				Event_Queue_Dialog_Run(718);
				Event_Queue_SetSync(true);
				Event_Queue_Object_ToggleGhost(10, true);
				Event_Queue_Object_WalkToRelative(10, 16, 0, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(10, 19272, 10568, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(11, 19304, 10568, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(719);
			}
			Event_Queue_WaitFrames(24);
			
			Event_Queue_EngageBattle(57, 11);
			
			Event_Queue_Dialog_Run(720);
			if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(721);
			Event_Queue_Dialog_Run(722);
			Event_Queue_Object_WalkTo(10, 19292, 10584, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Profile_KeyItemAdd(167);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_Object_WalkTo(10, 19272, 10568, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(723);
			Event_Queue_SetSync(true);
			Event_Queue_Regroup(1);
			Event_Queue_Object_WalkTo(10, 19240, 10560, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(11, 19304, 10560, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ToggleGhost(10, false);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 109);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 52: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(760);
				Event_Queue_Dialog_Run(761);
				Event_Queue_Dialog_Run(762);
				Event_Queue_Dialog_Run(763);
			}
			else {
				Event_Queue_SetFlag(FLAG_PLOT, 113);
			}
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_RCCLUB_CLEAR, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 53: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Camera_TeleportTo(17568, 11712);
			Event_Queue_Object_TeleportTo(0, 17568, 11712);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(2167);
			Event_Queue_Dialog_Run(2168);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(2169);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(2170);
			Event_Queue_Dialog_Run(2171);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Camera_TeleportTo(overworld.camera.x, overworld.camera.y);
			Event_Queue_Object_TeleportTo(0, overworld.player.x, overworld.player.y);
			Event_Queue_Object_ChangeDirection(0, overworld.player.direction);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_SetFlag(FLAG_AZURETOPHOTEL_COMPUTER_STATUS, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 54: {
			int inventoryId = -1;
			for (int i = 15; i >= 0; i--) {
				if (profile.itemInventory[i] == 23) {
					inventoryId = i;
					break;
				}
			}
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2185);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
			Event_Queue_EngageBattle(71, 10);
			Event_Queue_Dialog_Run(2187);
			Event_Queue_SetFlag(FLAG_BRIAN_OPTIONALFIGHT, 1);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
			if (inventoryId < 0) {
				Event_Queue_Dialog_Run(2190);
				Event_Queue_EngageBattle(71, 10);
				Event_Queue_Dialog_Run(2191);
				Event_Queue_Jump(0);
			}
			else {
				Event_Queue_Profile_ItemRemove(inventoryId);
				Event_Queue_Dialog_Run(2188);
				Event_Queue_Dialog_Run(2186);
				Event_Queue_SetFlag(FLAG_BRIAN_OPTIONALFIGHT, 2);
			}
			
			Event_Queue_Label(0);
			Event_Queue_Object_WalkToRelative(10, 0, 176, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_Destroy(10);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 55: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2260);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 56: {
			if (profile.flags[FLAG_ALONE] && profile.flags[FLAG_SALLY_JOINED]) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(14608, 4768, 2);
				Event_Queue_Object_WalkTo(0, 14592, 4768, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(1, 14624, 4768, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(980);
				Event_Queue_Dialog_Run(192);
				Event_Queue_Dialog_Run(981);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(1, SPR_misc_sally_phone);
				Event_Queue_Object_ChangeSpriteFrame(1, 0);
				Event_Queue_WaitFrames(30);
				Event_Queue_PlaySound(SND_menu5);
				Event_Queue_WaitFrames(18);
				Event_Queue_PlaySound(SND_menu5);
				Event_Queue_WaitFrames(20);
				Event_Queue_PlaySound(SND_menu4);
				Event_Queue_WaitFrames(15);
				Event_Queue_PlaySound(SND_menu4);
				Event_Queue_WaitFrames(25);
				Event_Queue_PlaySound(SND_menu6);
				Event_Queue_WaitFrames(62);
				Event_Queue_Object_ChangeSpriteFrame(1, 1);
				Event_Queue_Dialog_Run(982);
				Event_Queue_WaitFrames(47);
				Event_Queue_Dialog_Run(983);
				Event_Queue_WaitFrames(47);
				Event_Queue_Dialog_Run(984);
				Event_Queue_WaitFrames(12);
				Event_Queue_Object_ChangeSpriteFrame(1, 0);
				Event_Queue_WaitFrames(12);
				Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_sally);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(985);
				
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_Camera_TeleportTo(13336, 7912);
				Event_Queue_Object_TeleportTo(0, 13312, 7952);
				Event_Queue_Object_TeleportTo(1, 13360, 7952);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_CreateObject(70, 1, SPR_misc_sapphirebus, 13328, 7888, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ToggleGhost(70, true);
				Event_Queue_WaitFrames(30);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_WaitFrames(24);
				Event_Queue_CreateObject(71, 1, SPR_owchar_noah, 13328, 7896, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(72, 1, SPR_owchar_emmet, 13328, 7896, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkToRelative(71, 12, 16, 0.5, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkToRelative(72, -12, 16, 0.5, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_ChangeSpriteFrameSpeed(70, 0.0625);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteFrameSpeed(70, 0.125);
				Event_Queue_Object_WalkToRelative(70, 16, 0, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkToRelative(70, 48, 0, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkToRelative(70, 96, 0, 3, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetSync(true);
				Event_Queue_Dialog_Run(986);
				Event_Queue_Object_WalkToRelative(70, 160, 0, 4, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Dialog_Run(987);
				Event_Queue_Dialog_Run(988);
				Event_Queue_Dialog_Run(989);
				Event_Queue_Object_WalkToRelative(1, 0, -4, 0.25, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(990);
				
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_Object_Destroy(71);
				Event_Queue_Object_Destroy(72);
				Event_Queue_Party_Leave(3);
				Event_Queue_Profile_InventoryPartyOrderRemove(3);
				Event_Queue_Party_Join(1);
				Event_Queue_Party_Join(2);
				Event_Queue_Party_Join(3);
				Event_Queue_Profile_InventoryPartyOrderAdd(1);
				Event_Queue_Profile_InventoryPartyOrderAdd(2);
				Event_Queue_Profile_InventoryPartyOrderAdd(3);
				Event_Queue_Object_TeleportTo(0, 13304, 7912);
				Event_Queue_Object_TeleportToPointer(1, 0, 0, &player->x, &player->y);
				Event_Queue_Object_TeleportToPointer(2, 0, 0, &player->x, &player->y);
				Event_Queue_Object_TeleportToPointer(3, 0, 0, &player->x, &player->y);
				Event_Queue_Object_WalkToRelative(0, 128, 0, 2, OBJECT_DIRECTION_DOWN);
				Event_Queue_Regroup(8);
				Event_Queue_Dialog_Run(3001);
				Event_Queue_Dialog_Run(3002);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_RemoveCurrentTrigger();
				Event_Queue_SetFlag(FLAG_NOAH_JOINED, 1);
				Event_Queue_SetFlag(FLAG_EMMET_JOINED, 1);
				Event_Queue_SetFlag(FLAG_ALONE, 0);
				Event_Queue_SetFlag(FLAG_PLOT, 75);
				
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(342);
				Event_Queue_RemoveCurrentTrigger();
				Event_Queue_SetFlag(FLAG_PLOT, 75);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 57: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(1000);
			Event_Queue_Dialog_Run(1001);
			Event_Queue_Dialog_Run(1002);
			Event_Queue_Dialog_Run(1003);
			Event_Queue_Dialog_Run(1004);
			Event_Queue_Dialog_Run(1005);
			Event_Queue_Dialog_Run(1006);
			Event_Queue_Dialog_Run(1007);
			Event_Queue_Dialog_Run(1008);
			Event_Queue_Dialog_Run(1009);
			Event_Queue_Dialog_Run(1010);
			Event_Queue_Dialog_Run(1011);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 100);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 58: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Object_ToggleWalkAnimation(0, false);
			Event_Queue_Object_ToggleWalkAnimation(1, false);
			Event_Queue_Object_ToggleWalkAnimation(2, false);
			Event_Queue_Object_ToggleWalkAnimation(3, false);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_HURT);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_HURT);
				Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_HURT);
				Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_HURT);
			}
			Event_Queue_SetSync(true);
			Event_Queue_CreateObject(70, 1, SPR_owchar_lulu_omega, 12384, 11792, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_ATTACK3);
			Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
			Event_Queue_Object_WalkTo(0, 12448, 11792, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 12472, 11760, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 12472, 11824, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(3, 12496, 11792, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(1);
			Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ToggleWalkAnimation(0, true);
			Event_Queue_Object_ToggleWalkAnimation(1, true);
			Event_Queue_Object_ToggleWalkAnimation(2, true);
			Event_Queue_Object_ToggleWalkAnimation(3, true);
			Event_Queue_WaitFrames(120);
			Event_Queue_Camera_MoveTo(12416, 11784, 1);
			Event_Queue_PlayMusic(MUS_lu);
			Event_Queue_Dialog_Run(1080);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_IDLE);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_IDLE);
			}
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(profile.flags[FLAG_ALONE] ? 1087 : 1081);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_omega_rage);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(1082);
			
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_SetFlag(FLAG_OMEGALULU_GAMEOVER, 1);
				Event_Queue_EngageBattle(192, 70);
				
				Event_Queue_PlayMusic(MUS_bother);
				Event_Queue_Dialog_Run(584);
			}
			else {
				Event_Queue_EngageBattle(22, 70);
				Event_Queue_Object_ChangeSpriteId(70, -1);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_HURT);
				Event_Queue_WaitFrames(140);
				Event_Queue_Object_DisableFighterSprite(0);
				if (!profile.flags[FLAG_ALONE]) {
					Event_Queue_Object_DisableFighterSprite(1);
					Event_Queue_Object_DisableFighterSprite(2);
					Event_Queue_Object_DisableFighterSprite(3);
				}
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_omega_rage);
				Event_Queue_Object_ChangeSpriteFrame(70, 1);
				Event_Queue_Dialog_Run(1083);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(1084);
				Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_ATTACK1);
				Event_Queue_Dialog_Run(1085);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_RUN);
				Event_Queue_FadeOutMusic(2000);
				Event_Queue_Object_JumpTo(70, 11848, 11656, OBJECT_DIRECTION_LEFT, 64, 60);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(1086);
				Event_Queue_SetFlag(FLAG_PLOT, 135);
				Event_Queue_GotoArea(103, overworld.player.x, overworld.player.y, SPR_tileset_day);
			}
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 59: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(26176, 1000, 2);
			Event_Queue_WaitFrames(12);
			Event_Queue_Object_WalkTo(3, 26176, 1096, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(12);
			Event_Queue_Dialog_Run(1120);
			Event_Queue_Camera_MoveTo(26176, 1056, 2);
			if (player->x < 26176)
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			else
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1121);
			
			Event_Queue_Regroup(2);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 151);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 60: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(20656, 15184, 1);
			Event_Queue_Object_WalkTo(0, 20656, 15216, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 20632, 15216, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 20680, 15216, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 20656, 15184, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1125);
			Event_Queue_Dialog_Run(1126);
			Event_Queue_Dialog_Run(1127);
			Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
			Event_Queue_Dialog_Run(1128);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(20656, 15088, 1);
			Event_Queue_Object_WalkTo(3, 20704, 15060, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(64);
			Event_Queue_PlaySound(SND_menu2);
			Event_Queue_WaitFrames(40);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(20656, 15184, 1);
			Event_Queue_Object_WalkTo(3, 20656, 15184, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1129);
			Event_Queue_Dialog_Run(1130);
			Event_Queue_Dialog_Run(1131);
			Event_Queue_Dialog_Run(1132);
			Event_Queue_AddCash(484);
			Event_Queue_Dialog_Run(1133);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
			Event_Queue_Dialog_Run(1134);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_GotoArea(187, 20698, 15520, -1);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_TeleportTo(1, 20698, 15552);
			Event_Queue_Object_TeleportTo(2, 20758, 15520);
			Event_Queue_Object_TeleportTo(3, 20758, 15552);
			Event_Queue_CreateObject(70, 1, SPR_misc_perrypizza, 20712, 15504, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(71, 1, SPR_misc_perrypizza, 20712, 15536, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(72, 1, SPR_misc_perrypizza, 20744, 15504, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(73, 1, SPR_misc_perrypizza, 20744, 15536, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_WaitFrames(70);
			Event_Queue_Dialog_Run(1140);
			Event_Queue_Dialog_Run(1141);
			Event_Queue_Dialog_Run(1142);
			Event_Queue_Dialog_Run(1143);
			Event_Queue_Dialog_Run(1144);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1145);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1146);
			Event_Queue_Dialog_Run(1147);
			Event_Queue_Object_ToggleGhost(1, true);
			Event_Queue_Object_WalkTo(1, 20696, 15560, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ToggleGhost(1, false);
			Event_Queue_Object_WalkTo(1, 20672, 15560, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(16);
			Event_Queue_Dialog_Run(1148);
			Event_Queue_Dialog_Run(1149);
			Event_Queue_Dialog_Run(1150);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1151);
			Event_Queue_Dialog_Run(1152);
			Event_Queue_Dialog_Run(1153);
			Event_Queue_Dialog_Run(1154);
			Event_Queue_Dialog_Run(1155);
			Event_Queue_Dialog_Run(192);
			Event_Queue_Dialog_Run(1156);
			Event_Queue_Dialog_Run(1157);
			Event_Queue_Dialog_Run(1158);
			Event_Queue_Object_WalkTo(1, 20672, 15520, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1159);
			Event_Queue_Dialog_Run(324);
			Event_Queue_SetFlag(FLAG_NOAH_CASH_LENT, profile.cash / 4);
			Event_Queue_AddCash(-profile.cash / 4);
			Event_Queue_Dialog_Run(1160);
			Event_Queue_Dialog_Run(1178);
			Event_Queue_Object_WalkTo(1, 20368, 15552, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1163);
			Event_Queue_Dialog_Run(1164);
			Event_Queue_Dialog_Run(1165);
			Event_Queue_Dialog_Run(1166);
			Event_Queue_Dialog_Run(1167);
			Event_Queue_Dialog_Run(1168);
			Event_Queue_Dialog_Run(1169);
			Event_Queue_Dialog_Run(1170);
			Event_Queue_Dialog_Run(1171);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_FullyHealParty();
			Event_Queue_Party_Leave(1);
			Event_Queue_Profile_InventoryPartyOrderRemove(1);
			Event_Queue_Profile_UnequipAll(1);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_Destroy(71);
			Event_Queue_Object_Destroy(72);
			Event_Queue_Object_Destroy(73);
			Event_Queue_Object_TeleportTo(0, 20680, 15496);
			Event_Queue_Object_TeleportTo(1, 20680, 15496);
			Event_Queue_Object_TeleportTo(2, 20680, 15496);
			Event_Queue_Object_WalkTo(0, 20664, 15560, 3, OBJECT_DIRECTION_UP);
			Event_Queue_Regroup(8);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_Dialog_Run(1172);
			Event_Queue_Dialog_Run(1173);
			Event_Queue_Dialog_Run(1174);
			Event_Queue_Dialog_Run(1175);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1176);
			Event_Queue_Dialog_Run(1177);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_SetFlag(FLAG_PLOT, 152);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 61: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(26176, 1092, 2);
			Event_Queue_Object_WalkTo(0, 26176, 1096, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_WalkTo(1, 26176, 1078, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_WalkTo(2, 26176, 1060, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(70, 26216, 1096, 4, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1180);
			Event_Queue_Dialog_Run(1181);
			Event_Queue_Dialog_Run(1182);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(1183);
			Event_Queue_Dialog_Run(1184);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_WalkTo(70, 26632, 1096, 4, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(12);
			Event_Queue_Object_WalkToRelative(1, 24, 0, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1185);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1186);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1187);
			Event_Queue_Dialog_Run(1188);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1189);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(1190);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(1191);
			Event_Queue_Dialog_Run(1192);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1193);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1194);
			Event_Queue_Dialog_Run(1195);
			Event_Queue_Dialog_Run(1196);
			
			Event_Queue_Regroup(2);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 153);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 62: {
			bool triggerDeath = true;
			for (int i = 0; i < 5; i++) {
				if (profile.party[i] < 0) break;
				partyMembers[profile.party[i]].hpDamage += 25;
				if (partyMembers[profile.party[i]].hpDamage < partyMembers[profile.party[i]].hpMax - 1) {
					triggerDeath = false;
				}
			}
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_PlaySound(SND_hit3);
			Event_Queue_PlaySound(SND_saw);
			Event_Queue_PlaySound(SND_electric);
			for (int i = 0; i < 20; i++) {
				Event_Queue_Object_TeleportTo(0, player->x + Random_IRange(-2, 2), player->y + Random_IRange(-2, 2));
				Event_Queue_Object_TeleportTo(1, overworld.objects[1].x + Random_IRange(-2, 2), overworld.objects[1].y + Random_IRange(-2, 2));
				Event_Queue_Object_TeleportTo(2, overworld.objects[2].x + Random_IRange(-2, 2), overworld.objects[2].y + Random_IRange(-2, 2));
				Event_Queue_Object_TeleportTo(3, overworld.objects[3].x + Random_IRange(-2, 2), overworld.objects[3].y + Random_IRange(-2, 2));
				Event_Queue_WaitFrames(1);
			}
			Event_Queue_Object_TeleportTo(0, player->x, player->y);
			Event_Queue_Object_TeleportTo(1, overworld.objects[1].x, overworld.objects[1].y);
			Event_Queue_Object_TeleportTo(2, overworld.objects[2].x, overworld.objects[2].y);
			Event_Queue_Object_TeleportTo(3, overworld.objects[3].x, overworld.objects[3].y);
			if (triggerDeath) {
				for (int i = 0; i < 5; i++) {
					if (profile.party[i] < 0) break;
					
					int spriteId = -1;
					switch (profile.party[i]) {
						case 0:
							spriteId = SPR_owchar_collapse_ruby;
							break;
						case 1:
							spriteId = SPR_owchar_collapse_noah;
							break;
						case 2:
							spriteId = SPR_owchar_collapse_emmet;
							break;
						case 3:
							spriteId = SPR_owchar_collapse_sally;
							break;
						
						case 6:
							spriteId = SPR_owchar_collapse_perry;
							break;
					}
					if (spriteId >= 0) {
						Event_Queue_Object_ChangeSpriteId(i, spriteId);
						Event_Queue_Object_ChangeSpriteFrame(i, 0);
					}
				}
				Event_Queue_WaitFrames(60);
				Event_Queue_PlaySound(SND_poison);
				for (int i = 0; i < 5; i++) {
					if (profile.party[i] < 0) break;
					
					Event_Queue_Object_ChangeSpriteFrame(i, 1);
				}
				Event_Queue_WaitFrames(75);
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_GotoArea(189, 19608, 15984, -1);
			}
			else if (profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_HITS] == 0 && profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_SOLUTION_FOUND] < 2) {
				Event_Queue_WaitFrames(10);
				Event_Queue_Dialog_Run(2329);
				Event_Queue_Dialog_Run(2330);
				Event_Queue_Dialog_Run(2331);
				if (profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_SOLUTION_FOUND]) {
					Event_Queue_Dialog_Run(2333);
				}
				else {
					Event_Queue_Dialog_Run(2332);
				}
			}
			
			Event_Queue_SetFlag(FLAG_WHITELIGHT_ELECTROFLOOR_HITS, profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_HITS] + 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 63: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_HITS] > 0) {
				Event_Queue_Dialog_Run(2334);
				Event_Queue_Camera_MoveTo(19496, 15576, 2);
				Event_Queue_Dialog_Run(2335);
				
				Event_Queue_Regroup(2);
			}
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_WHITELIGHT_ELECTROFLOOR_SOLUTION_FOUND, 2);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 64: {
			int spotX = 19008;
			int spotY = 15328;
			int spotDirection = OBJECT_DIRECTION_DOWN;
			for (int i = 0; i < 70; i++) {
				if (overworld.objects[160 + i].vars[7].i == 1) {
					spotX = overworld.objects[160 + i].x;
					spotY = overworld.objects[160 + i].y;
					spotDirection = overworld.objects[160 + i].vars[6].i;
					break;
				}
			}
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_PlaySound(SND_no);
			Event_Queue_StopMusic();
			if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] >= 5) {
				Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_DOWN);
				if (overworld.objects[71].x < 18864) {
					Event_Queue_Object_JumpTo(71, 18784, 15824, OBJECT_DIRECTION_DOWN, 24, 26);
				}
				else {
					Event_Queue_Object_JumpTo(71, 18944, 15824, OBJECT_DIRECTION_DOWN, 24, 26);
				}
				Event_Queue_Object_Destroy(71);
			}
			Event_Queue_WaitFrames(10);
			Event_Queue_Camera_MoveTo(spotX, spotY, 4);
			Event_Queue_WaitFrames(10);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_TeleportTo(10, spotX, spotY);
			if (spotDirection == OBJECT_DIRECTION_RIGHT) {
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_JumpToRelative(10, 8, 0, OBJECT_DIRECTION_RIGHT, 8, 12);
			}
			else if (spotDirection == OBJECT_DIRECTION_LEFT) {
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_JumpToRelative(10, -8, 0, OBJECT_DIRECTION_LEFT, 8, 12);
			}
			else if (spotDirection == OBJECT_DIRECTION_DOWN) {
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpToRelative(10, 0, 16, OBJECT_DIRECTION_DOWN, 8, 12);
			}
			else {
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Object_JumpToRelative(10, 0, -10, OBJECT_DIRECTION_UP, 8, 12);
			}
			Event_Queue_Dialog_Run(2342);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_Camera_TeleportTo(18864, 15676);
			Event_Queue_Object_TeleportTo(0, 18864, 15760);
			Event_Queue_Object_TeleportTo(1, 18864, 15760);
			Event_Queue_Object_TeleportTo(2, 18864, 15760);
			Event_Queue_Object_TeleportTo(3, 18864, 15760);
			Event_Queue_Object_TeleportTo(10, 18864, 15656);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToRelative(0, 0, -80, 3, OBJECT_DIRECTION_UP);
			for (int i = 0; i < 70; i++) {
				Event_Queue_Object_TeleportTo(160 + i, overworld.objects[160 + i].x, overworld.objects[160 + i].y - 1000);
			}
			Event_Queue_Regroup(3);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_PlayMusic(MUS_whitelight);
			
			if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] == 4) {
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(2, 18784, 15824, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(26);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(28);
				Event_Queue_Dialog_Run(2351);
				Event_Queue_WaitFrames(92);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Party_Leave(3);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2352);
				Event_Queue_Dialog_Run(2353);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			}
			
			Event_Queue_SetBoolPtr(&overworld.map.doors[174].enabled, true);
			Event_Queue_SetBoolPtr(&overworld.map.doors[175].enabled, true);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 65: {
			Profile_EquipAction(1, 1);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1230);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(18032, 15664, 1);
			Event_Queue_Object_WalkTo(2, 17976, 15640, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(0, 18008, 15656, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 17960, 15696, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1231);
			Event_Queue_Dialog_Run(1162);
			Event_Queue_Object_JumpToRelative(10, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
			Event_Queue_Dialog_Run(1232);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(18096, 15640, 1);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(10, 18184, 15568, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(10, 18184, 15608, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(10, 18096, 15616, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(34);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(6);
			Event_Queue_Object_WalkTo(0, 18096, 15648, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 18064, 15648, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(27);
			Event_Queue_Object_WalkTo(2, 18128, 15648, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1233);
			Event_Queue_Dialog_Run(1234);
			Event_Queue_Dialog_Run(1235);
			Event_Queue_Dialog_Run(1236);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1237);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1238);
			Event_Queue_Dialog_Run(1239);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1240);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1241);
			Event_Queue_Dialog_Run(1242);
			Event_Queue_Dialog_Run(1243);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1244);
			Event_Queue_Object_JumpToRelative(11, 0, 0, OBJECT_DIRECTION_DOWN, 16, 8);
			Event_Queue_Dialog_Run(1245);
			Event_Queue_Dialog_Run(1246);
			Event_Queue_Object_WalkTo(11, 18080, 15568, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1247);
			Event_Queue_Dialog_Run(1248);
			Event_Queue_Dialog_Run(1249);
			Event_Queue_Dialog_Run(1250);
			Event_Queue_Dialog_Run(1251);
			Event_Queue_Object_EnableFighterSprite(10, 74, 83, FIGHTER_STATE_IDLE);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1252);
			Event_Queue_Dialog_Run(1253);
			Event_Queue_Object_DisableFighterSprite(10);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1254);
			Event_Queue_Object_JumpToRelative(1, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(1255);
			Event_Queue_Dialog_Run(1256);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1257);
			Event_Queue_Object_JumpToRelative(2, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(1258);
			Event_Queue_Dialog_Run(1259);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_WaitFrames(80);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(1260);
			Event_Queue_Object_ChangeSpriteId(2, SPR_misc_sally_serious);
			Event_Queue_Object_ChangeSpriteFrame(2, 1);
			Event_Queue_Dialog_Run(1261);
			Event_Queue_Dialog_Run(1262);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1263);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1264);
			
			Event_Queue_Object_WalkTo(70, 18082, 15680, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_sally);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Party_Leave(2);
			Event_Queue_Party_Leave(3);
			Event_Queue_Profile_InventoryPartyOrderRemove(2);
			Event_Queue_Profile_InventoryPartyOrderRemove(3);
			Event_Queue_Profile_InventoryPartyOrderAdd(1);
			Event_Queue_Profile_InventoryPartyOrderAdd(2);
			Event_Queue_Profile_InventoryPartyOrderAdd(3);
			Event_Queue_Party_Join(1);
			Event_Queue_Party_Join(2);
			Event_Queue_Party_Join(3);
			Event_Queue_Object_TeleportToPointer(3, 0, 0, &overworld.objects[2].x, &overworld.objects[2].y);
			Event_Queue_Object_TeleportToPointer(2, 0, 0, &overworld.objects[1].x, &overworld.objects[1].y);
			Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[70].x, &overworld.objects[70].y);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(1265);
			Event_Queue_Dialog_Run(1266);
			Event_Queue_Object_WalkTo(0, 18096, 15656, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1267);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1268);
			Event_Queue_Dialog_Run(1269);
			Event_Queue_Dialog_Run(1270);
			
			Event_Queue_Regroup(1);
			Event_Queue_Dialog_Run(3001);
			Event_Queue_Dialog_Run(1271);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 160);
			Event_Queue_SetFlag(FLAG_WHITELIGHT_PLOT, 3);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			
			Overworld_CreateTrigger(1, 18040, 15600, 18152, 15640, 66);
			Overworld_CreateTrigger(2, 18040, 15672, 18152, 15712, 66);
			Overworld_CreateTrigger(3, 18040, 15600, 18080, 15712, 66);
			Overworld_CreateTrigger(4, 18112, 15600, 18152, 15712, 66);
		} break;
		
		case 66: {
			overworld.map.triggers[1].eventId = 0;
			overworld.map.triggers[2].eventId = 0;
			overworld.map.triggers[3].eventId = 0;
			overworld.map.triggers[4].eventId = 0;
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1272);
			Event_Queue_Dialog_Run(1273);
			Event_Queue_Dialog_Run(1274);
			Event_Queue_Dialog_Run(1275);
			
			Event_Queue_EngageBattle(80, 10);
			Event_Queue_Camera_TeleportTo(18096, 15640);
			Event_Queue_Object_TeleportTo(11, 18064, 15568);
			Event_Queue_Object_TeleportTo(12, 18000, 15600);
			Event_Queue_Object_TeleportToPointer(1, 0, 32, &overworld.objects[0].x, &overworld.objects[0].y);
			Event_Queue_Object_TeleportToPointer(2, -24, 16, &overworld.objects[0].x, &overworld.objects[0].y);
			Event_Queue_Object_TeleportToPointer(3, 24, 16, &overworld.objects[0].x, &overworld.objects[0].y);
			
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(1276);
			Event_Queue_Dialog_Run(1277);
			Event_Queue_Dialog_Run(1278);
			Event_Queue_Dialog_Run(1279);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_WaitFrames(40);
			Event_Queue_Dialog_Run(1280);
			Event_Queue_WaitFrames(80);
			Event_Queue_Dialog_Run(1281);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(1282);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1283);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1284);
			Event_Queue_Dialog_Run(1285);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(10, 18184, 15608, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(10, 18184, 15568, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(10, 18096, 15568, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Regroup(1);
			Event_Queue_SetSync(false);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 67: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(18096, 16064, 2);
			Event_Queue_Object_WalkTo(0, 18096, 16056, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 18128, 16080, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 18064, 16080, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(3, 18096, 16104, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1290);
			Event_Queue_Dialog_Run(1291);
			Event_Queue_Dialog_Run(1292);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1293);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1294);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(0, 18096, 16076, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(0, 18120, 16080.125, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_hug);
			Event_Queue_WaitFrames(150);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_JumpToRelative(0, -8, -0.125, OBJECT_DIRECTION_RIGHT, 0, 4);
			Event_Queue_WaitFrames(70);
			Event_Queue_Dialog_Run(1295);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(1296);
			Event_Queue_Dialog_Run(1297);
			Event_Queue_Dialog_Run(1298);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(1299);
			Event_Queue_AddCash(profile.flags[FLAG_NOAH_CASH_LENT] + 400);
			Event_Queue_Dialog_Run(1300);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_WHITELIGHT_PLOT, 4);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 68: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TeleportTo(15616, 16144);
			
			Event_Queue_Object_TeleportTo(0, 15532, 16192);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_sit);
			Event_Queue_Object_ChangeSpriteFrame(0, 2);
			
			Event_Queue_Object_TeleportTo(1, 15532, 16160);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(1, SPR_misc_noah_sit);
			Event_Queue_Object_ChangeSpriteFrame(1, 2);
			
			Event_Queue_Object_TeleportTo(2, 15532, 16128);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(2, SPR_misc_emmet_sit);
			Event_Queue_Object_ChangeSpriteFrame(2, 2);
			
			Event_Queue_Object_TeleportTo(3, 15532, 16096);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(3, SPR_misc_sally_sit);
			Event_Queue_Object_ChangeSpriteFrame(3, 2);
			
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_WaitFrames(180);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_suppressed);
			Event_Queue_Object_ChangeSpriteFrame(0, 0);
			Event_Queue_Object_JumpToRelative(0, 12, 0, OBJECT_DIRECTION_RIGHT, 0, 3);
			Event_Queue_WaitFrames(90);
			Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_JumpToRelative(1, 12, 0, OBJECT_DIRECTION_DOWN, 0, 3);
			Event_Queue_WaitFrames(120);
			Event_Queue_PlayMusic(MUS_shutdownpre);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeSpriteFrame(0, 2);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_collapse_ruby);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_Overworld_FadeIn(120, 0, 0, 0);
			Event_Queue_SetFlag(FLAG_SALLY_NEO, 1);
			Event_Queue_SetIntPtr(&partyMembers[3].headId, 79);
			Event_Queue_SetIntPtr(&partyMembers[3].defaultArmorId, 74);
			Event_Queue_Party_Leave(3);
			Event_Queue_Profile_InventoryPartyOrderRemove(3);
			Event_Queue_Profile_UnequipAll(3);
			Event_Queue_Object_TeleportTo(0, 15792, 16136);
			Event_Queue_Object_WalkTo(0, 15712, 16136, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Regroup(2);
			Event_Queue_WaitFrames(360);
			Event_Queue_StopMusic();
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_PlayMusic(MUS_ominous);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 2);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 69: {
			Profile_AddAction(138, 1);
			Profile_AddAction(139, 1);
			Profile_AddAction(140, 1);
			Profile_AddAction(142, 1);
			Profile_EquipAction(3, 138);
			Profile_EquipAction(3, 139);
			Profile_EquipAction(3, 140);
			Profile_EquipAction(3, 142);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(25952, 3536, 1);
			Event_Queue_Object_WalkTo(0, 25920, 3552, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 25904, 3568, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 25888, 3584, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_sally_neo);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_JumpTo(70, 26008, 3560, OBJECT_DIRECTION_DOWN, 8, 12);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 25928, 3584, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_StopMusic();
			Event_Queue_PlaySound(SND_snowqueenwannabeapproaches);
			Event_Queue_WaitFrames(162);
			
			Event_Queue_Party_Leave(0);
			Event_Queue_Party_Leave(1);
			Event_Queue_EngageBattle(84, 70);
			Event_Queue_Party_Join(0);
			Event_Queue_Party_Join(1);
			Event_Queue_Party_Leave(2);
			Event_Queue_Party_Join(2);
			
			Event_Queue_PlayMusic(MUS_bother);
			Event_Queue_WaitFrames(60);
			Event_Queue_CreateObject(71, 1, SPR_owchar_diego, 26144, 3600, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(71, 26016, 3600, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteId(71, SPR_misc_diego_greet);
			Event_Queue_Object_ChangeSpriteFrame(71, 0);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 1);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 2);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 3);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 4);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 5);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 4);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 3);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 2);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 1);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteFrame(71, 0);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeSpriteId(71, SPR_owchar_diego);
			Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkTo(70, 25996, 3600.01, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_JumpToRelative(70, 12, 0, OBJECT_DIRECTION_RIGHT, 0, 4);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_sally_neo_hug);
			Event_Queue_WaitFrames(80);
			Event_Queue_Object_ChangeSpriteId(71, SPR_owchar_collapse_diego);
			Event_Queue_Object_ChangeSpriteFrame(71, 0);
			Event_Queue_Object_TeleportToPointer(71, 1, 0, &overworld.objects[71].x, &overworld.objects[71].y);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_TeleportToPointer(71, -2, 0, &overworld.objects[71].x, &overworld.objects[71].y);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_TeleportToPointer(71, 2, 0, &overworld.objects[71].x, &overworld.objects[71].y);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_TeleportToPointer(71, -2, 0, &overworld.objects[71].x, &overworld.objects[71].y);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_TeleportToPointer(71, 1, 0, &overworld.objects[71].x, &overworld.objects[71].y);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_sally_neo);
			Event_Queue_Object_JumpToRelative(70, -12, 0, OBJECT_DIRECTION_RIGHT, 0, 4);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(71, SPR_owchar_diego);
			Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkTo(71, 26248, 3624, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_Destroy(71);
			Event_Queue_Party_Join(3);
			Event_Queue_Profile_InventoryPartyOrderAdd(3);
			Event_Queue_Object_TeleportToPointer(3, 0, 0, &overworld.objects[70].x, &overworld.objects[70].y);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Regroup(2);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 3);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 70: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_WaitFrames(70);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(29912, 10568, 1);
			Event_Queue_Object_WalkTo(0, 29912, 10580, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 29888, 10608, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 29936, 10608, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 29912, 10632, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(40);
			Event_Queue_Dialog_Run(2397);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(2398);
			Event_Queue_Object_WalkTo(3, 29936, 10580, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(2399);
			Event_Queue_Object_ChangeSpriteId(11, SPR_owchar_npc_35);
			Event_Queue_Object_ChangeSpriteFrameSpeed(11, 0);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_WalkTo(11, 29944, 10532, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(11, 29944, 10552, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(11, 29920, 10552, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeSpriteFrame(11, 5);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpToRelative(11, 21, 0, OBJECT_DIRECTION_LEFT, 0, 21);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeSpriteFrame(11, 2);
			Event_Queue_SetSync(false);
			Event_Queue_Object_WalkTo(11, 29912, 10552, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_StopMusic();
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_SetIntPtr(&overworld.overlayId, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(12, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(13, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(14, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(15, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(16, 0);
			Event_Queue_Object_ChangeSpriteFrame(16, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(17, 0);
			Event_Queue_Object_ChangeSpriteFrame(17, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(18, 0);
			Event_Queue_Object_SetColor(18, 0, 0, 0);
			Event_Queue_WaitFrames(7);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(44);
			Event_Queue_Object_ChangeSpriteId(12, SPR_owchar_npc_36);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(13, SPR_owchar_npc_37);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(14, SPR_owchar_npc_38);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2400);
			Event_Queue_Dialog_Run(2401);
			Event_Queue_Dialog_Run(2402);
			Event_Queue_Dialog_Run(2403);
			Event_Queue_Dialog_Run(2404);
			Event_Queue_Dialog_Run(2405);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_JumpToRelative(12, 0, 0, OBJECT_DIRECTION_RIGHT, 16, 12);
			Event_Queue_Dialog_Run(2406);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_UP);
			Event_Queue_Object_JumpToRelative(14, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(2407);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_JumpToRelative(13, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
			Event_Queue_Dialog_Run(2408);
			Event_Queue_Dialog_Run(2409);
			Event_Queue_Dialog_Run(2410);
			Event_Queue_Dialog_Run(2411);
			Event_Queue_Dialog_Run(2412);
			Event_Queue_Dialog_Run(2413);
			Event_Queue_Dialog_Run(2414);
			Event_Queue_Dialog_Run(2415);
			Event_Queue_Dialog_Run(2416);
			Event_Queue_Dialog_Run(2417);
			Event_Queue_Object_JumpTo(11, 29912, 10532, OBJECT_DIRECTION_UP, 72, 30);
			Event_Queue_SetSync(true);
			Event_Queue_Dialog_Run(2418);
			Event_Queue_WaitFrames(7);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_SetIntPtr(&overworld.overlayId, 14);
			Event_Queue_WaitFrames(21);
			
			Event_Queue_PlayMusic(MUS_discodoomsday);
			Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0.125);
			Event_Queue_Object_ChangeSpriteId(11, SPR_misc_npc_35_dj);
			Event_Queue_Object_ChangeSpriteFrameSpeed(11, 0.1);
			Event_Queue_Object_ChangeSpriteId(12, SPR_misc_npc_36_floss);
			Event_Queue_Object_ChangeSpriteFrameSpeed(12, 0.25);
			Event_Queue_Object_ChangeSpriteFrameSpeed(13, 0.5);
			Event_Queue_Object_ChangeSpriteId(14, SPR_misc_npc_38_dance);
			Event_Queue_Object_ChangeSpriteFrameSpeed(14, 0.25);
			Event_Queue_Object_ChangeSpriteFrameSpeed(15, 0.125);
			Event_Queue_Object_ChangeSpriteFrameSpeed(16, 0.144);
			Event_Queue_Object_ChangeSpriteFrameSpeed(17, 0.144);
			Event_Queue_Object_ChangeSpriteFrameSpeed(18, 0.25);
			Event_Queue_Object_SetColor(18, 255, 255, 255);
			
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(394);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 20);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 71: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(28584, 10616, 1);
			Event_Queue_Object_WalkTo(0, 28584, 10616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 28616, 10640, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 28584, 10664, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 28552, 10640, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(40);
			Event_Queue_Dialog_Run(2419);
			Event_Queue_Dialog_Run(2420);
			Event_Queue_Dialog_Run(2421);
			Event_Queue_Dialog_Run(2422);
			Event_Queue_Dialog_Run(2423);
			Event_Queue_Dialog_Run(2424);
			Event_Queue_Dialog_Run(2425);
			Event_Queue_Dialog_Run(2426);
			Event_Queue_Dialog_Run(2427);
			Event_Queue_Dialog_Run(2428);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(1, 28904, 10616, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveToRelative(80, 0, 2);
			Event_Queue_SetSync(false);
			Event_Queue_PlaySound(SND_swing);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_WalkTo(10, 28824, 10608, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(10, 28792, 10608, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(10, 28776, 10608, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(6);
			Event_Queue_Object_WalkTo(1, 28616, 10640, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			
			Event_Queue_Dialog_Run(2429);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2430);
			Event_Queue_Dialog_Run(2431);
			Event_Queue_Dialog_Run(2432);
			Event_Queue_Dialog_Run(2433);
			Event_Queue_Dialog_Run(2434);
			Event_Queue_Dialog_Run(2435);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(8);
			Event_Queue_WaitFrames(34);
			Event_Queue_Camera_MoveTo(28832, 10304, 2);
			Event_Queue_CreateObject(70, 1, SPR_owchar_reti, 28832, 10304, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(70, 28832, 10328, 0.5, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2436);
			Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_BLOCK);
			Event_Queue_WaitFrames(6);
			Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_ATTACK3);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(8);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
			Event_Queue_WaitFrames(10);
			Event_Queue_Dialog_Run(2437);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(70, 28712, 10336, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(28584, 10616, 2);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Dialog_Run(2438);
			Event_Queue_Dialog_Run(2439);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(2440);
			
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_Camera_MoveTo(28584, 10936, 2);
			Event_Queue_PlayMusic(MUS_countdown);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 21);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_PAUSED);
			Event_Queue_ChangeMenu(10004);
		} break;
		
		case 72: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_StopMusic();
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TeleportTo(28584, 10616);
			if (overworld.menu.cursors[0] == 0) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_CreateObject(70, 1, SPR_owchar_reti, 28312, 10632, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_Object_WalkTo(70, 28504, 10632, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2446);
				Event_Queue_Dialog_Run(2447);
				Event_Queue_Dialog_Run(2448);
				Event_Queue_Dialog_Run(2449);
				Event_Queue_Dialog_Run(2450);
				Event_Queue_Dialog_Run(2451);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(16);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_BLOCK);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_ATTACK3);
				Event_Queue_PlaySound(SND_crusherhit);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Overworld_ShakeScreen(8);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(10);
				Event_Queue_Dialog_Run(2452);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(2453);
				
				Event_Queue_EngageBattle(85, 70);
				
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2454);
				Event_Queue_Dialog_Run(2455);
				Event_Queue_Dialog_Run(2456);
				Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
				Event_Queue_Dialog_Run(2457);
				Event_Queue_Object_ToggleWalkAnimation(70, false);
				Event_Queue_Object_WalkToRelative(70, -16, 0, 1, -1);
				Event_Queue_Object_ToggleWalkAnimation(70, true);
				Event_Queue_WaitFrames(95);
				Event_Queue_Object_WalkTo(70, 28312, 10632, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(70);
				
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(2458);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (overworld.menu.cursors[0] == 1) {
				Event_Queue_Object_WalkTo(0, 28776, 10648, 3, OBJECT_DIRECTION_UP);
				Event_Queue_CreateWall(71, 28832, 10600, 1600, 16);
				Event_Queue_Object_WalkTo(0, 28776, 10616, 3, OBJECT_DIRECTION_UP);
				Event_Queue_Regroup(3);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_WaitFrames(20);
				Event_Queue_Dialog_Run(2441);
				
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(10, 28296, 10608, 4, -1);
				Event_Queue_Camera_MoveTo(28296, 10608, 4);
				Event_Queue_SetSync(false);
				Event_Queue_PlaySound(SND_hit3);
				
				Event_Queue_CreateObject(70, 1, SPR_owchar_reti, 28296, 10344, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(70, 28296, 10552, 2, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(120);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(70, 28296, 10336, 2, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(30);
				Event_Queue_Regroup(2);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(2442);
				Event_Queue_Dialog_Run(2443);
				Event_Queue_Dialog_Run(2444);
				Event_Queue_CreateObject(72, 103, 28776, 10616, 0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_TeleportTo(70, 28784, 10336);
				Event_Queue_PlayMusic(MUS_retichase);
				
				Event_Queue_Regroup(1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (overworld.menu.cursors[0] == 2) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_CreateObject(70, 1, SPR_owchar_reti, 28312, 10632, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_Object_WalkTo(70, 28504, 10632, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2446);
				Event_Queue_Dialog_Run(2459);
				Event_Queue_Dialog_Run(2460);
				Event_Queue_Dialog_Run(2461);
				Event_Queue_Dialog_Run(2462);
				Event_Queue_Dialog_Run(2463);
				Event_Queue_Dialog_Run(2464);
				Event_Queue_CompareIntToConst(&profile.cash, 10000);
				Event_Queue_JumpIfLess(2);
				
				Event_Queue_Dialog_Run(2465);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				
				Event_Queue_Label(2);
				Event_Queue_Dialog_Run(2468);
				Event_Queue_Dialog_Run(2469);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_AddCash(-10000);
				Event_Queue_Dialog_Run(2466);
				Event_Queue_Dialog_Run(2467);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_WalkTo(70, 28312, 10632, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(2458);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (overworld.menu.cursors[0] == 3) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_CreateObject(70, 1, SPR_owchar_reti, 28312, 10632, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_Object_WalkTo(70, 28504, 10632, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2446);
				Event_Queue_Dialog_Run(2470);
				Event_Queue_Dialog_Run(2471);
				Event_Queue_Dialog_Run(2472);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(2);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 2);
				Event_Queue_JumpIfEqual(3);
				Event_Queue_Jump(4);
				
				Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2473);
				Event_Queue_Dialog_Run(2474);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(2);
				Event_Queue_Dialog_Run(2475);
				Event_Queue_Dialog_Run(2476);
				Event_Queue_Dialog_Run(2477);
				Event_Queue_Dialog_Run(2478);
				Event_Queue_Dialog_Run(2479);
				Event_Queue_Dialog_Run(2480);
				Event_Queue_Dialog_Run(2481);
				Event_Queue_Dialog_Run(2482);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(16);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_BLOCK);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_ATTACK3);
				Event_Queue_PlaySound(SND_crusherhit);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Overworld_ShakeScreen(8);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(10);
				Event_Queue_Dialog_Run(2483);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(3);
				Event_Queue_Dialog_Run(2484);
				Event_Queue_Dialog_Run(2485);
				Event_Queue_Dialog_Run(2486);
				Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
				Event_Queue_Dialog_Run(2487);
				Event_Queue_Dialog_Run(2488);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(4);
				Event_Queue_Dialog_Run(2489);
				Event_Queue_Dialog_Run(2490);
				Event_Queue_Dialog_Run(2491);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(16);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_BLOCK);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_ATTACK3);
				Event_Queue_PlaySound(SND_crusherhit);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Overworld_ShakeScreen(8);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_EnableFighterSprite(70, 80, 89, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(10);
				Event_Queue_Dialog_Run(2492);
				Event_Queue_Dialog_Run(2493);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Dialog_Run(2494);
				Event_Queue_Object_WalkTo(70, 28312, 10632, 2, OBJECT_DIRECTION_UP);
				
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(2458);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_reti_mask);
				Event_Queue_Object_WalkTo(70, 28504, 10632, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2495);
				Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
				Event_Queue_Dialog_Run(2496);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(2497);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2498);
				Event_Queue_Jump(0);
			}
			else {
				Event_Queue_WaitFrames(90);
				Event_Queue_PlayMusic(MUS_countdown);
				
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_PAUSED);
				Event_Queue_ChangeMenu(10004);
			}
			Event_Queue_Exit();
			
			Event_Queue_Label(0);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(70, 28584, 10632, 4, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(70, 28584, 10592, 4, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(8);
			Event_Queue_PlaySound(SND_hit1);
			Event_Queue_Object_JumpToRelative(0, 48, 0, OBJECT_DIRECTION_LEFT, 8, 12);
			Event_Queue_Object_JumpToRelative(1, 48, 0, OBJECT_DIRECTION_LEFT, 8, 12);
			Event_Queue_Object_JumpToRelative(2, 48, 0, OBJECT_DIRECTION_LEFT, 8, 12);
			Event_Queue_Object_JumpToRelative(3, 72, 0, OBJECT_DIRECTION_LEFT, 8, 12);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(55);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(15);
			Event_Queue_WaitFrames(17);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_WaitFrames(12);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_WaitFrames(15);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_WaitFrames(82);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Overworld_ShakeScreen(140);
			
			Event_Queue_WaitFrames(140);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_SetSync(true);
			Event_Queue_Object_TeleportTo(0, 28584, 10600);
			Event_Queue_Object_TeleportTo(1, 28584, 10600);
			Event_Queue_Object_TeleportTo(2, 28584, 10600);
			Event_Queue_Object_TeleportTo(3, 28584, 10600);
			Event_Queue_Object_WalkTo(0, 28664, 10616, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(0, 28584, 10616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 28616, 10640, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 28584, 10664, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 28552, 10640, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Object_TeleportTo(10, 28776, 10608);
			Event_Queue_Camera_TeleportTo(28584, 10936);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_PlayMusic(MUS_countdown);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_PAUSED);
			Event_Queue_ChangeMenu(10004);
		} break;
		
		case 73: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_StopMusic();
			Event_Queue_Object_Destroy(71);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(28832, 10304, 2);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkTo(70, 28832, 10336, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2445);
			Event_Queue_Camera_MoveTo(player->x, player->y - 4, 3);
			
			Event_Queue_Regroup(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 74: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_StopMusic();
			Event_Queue_Object_Destroy(71);
			Event_Queue_PlaySound(SND_chess_wrong);
			Event_Queue_WaitFrames(15);
			Event_Queue_Camera_MoveTo(overworld.objects[70].x, overworld.objects[70].y - 4, 8);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(70, 28584, 10632, 4, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(70, 28584, 10592, 4, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(28584, overworld.objects[70].y - 4, 4);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(55);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(15);
			Event_Queue_WaitFrames(17);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_WaitFrames(12);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_WaitFrames(15);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_WaitFrames(82);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_crusherhit);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Overworld_ShakeScreen(140);
			
			Event_Queue_WaitFrames(140);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_SetSync(true);
			Event_Queue_Object_TeleportTo(0, 28584, 10600);
			Event_Queue_Object_TeleportTo(1, 28584, 10600);
			Event_Queue_Object_TeleportTo(2, 28584, 10600);
			Event_Queue_Object_TeleportTo(3, 28584, 10600);
			Event_Queue_Object_WalkTo(0, 28664, 10616, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(0, 28584, 10616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 28616, 10640, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 28584, 10664, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 28552, 10640, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Object_TeleportTo(10, 28776, 10608);
			Event_Queue_Camera_TeleportTo(28584, 10936);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_PlayMusic(MUS_countdown);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_PAUSED);
			Event_Queue_ChangeMenu(10004);
		} break;
		
		case 75: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(29912, 10568, 2);
			Event_Queue_Object_WalkTo(0, 29912, 10580, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 29888, 10608, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 29936, 10608, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 29912, 10632, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteId(11, SPR_owchar_npc_35);
			Event_Queue_Object_ChangeSpriteFrameSpeed(11, 0);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_StopMusic();
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_SetIntPtr(&overworld.overlayId, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(12, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(13, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(14, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(15, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(16, 0);
			Event_Queue_Object_ChangeSpriteFrame(16, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(17, 0);
			Event_Queue_Object_ChangeSpriteFrame(17, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(18, 0);
			Event_Queue_Object_SetColor(18, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteId(12, SPR_owchar_npc_36);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(13, SPR_owchar_npc_37);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(14, SPR_owchar_npc_38);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2499);
			Event_Queue_Dialog_Run(2500);
			Event_Queue_Dialog_Run(2501);
			Event_Queue_Dialog_Run(2502);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_JumpToRelative(12, 0, 0, OBJECT_DIRECTION_RIGHT, 16, 12);
			Event_Queue_Dialog_Run(2503);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_UP);
			Event_Queue_Object_JumpToRelative(14, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(2504);
			Event_Queue_Dialog_Run(2505);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2506);
			Event_Queue_Dialog_Run(2507);
			Event_Queue_Dialog_Run(2508);
			
			Event_Queue_Object_WalkTo(11, 29944, 10532, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(11, 29944, 10552, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(11, 29912, 10552, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2509);
			Event_Queue_Dialog_Run(2390);
			Event_Queue_Dialog_Run(2510);
			
			Event_Queue_Object_JumpTo(11, 29912, 10532, OBJECT_DIRECTION_UP, 72, 30);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_SetIntPtr(&overworld.overlayId, 14);
			Event_Queue_WaitFrames(21);
			
			Event_Queue_PlayMusic(MUS_discodoomsday);
			Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0.125);
			Event_Queue_Object_ChangeSpriteId(11, SPR_misc_npc_35_dj);
			Event_Queue_Object_ChangeSpriteFrameSpeed(11, 0.1);
			Event_Queue_Object_ChangeSpriteId(12, SPR_misc_npc_36_floss);
			Event_Queue_Object_ChangeSpriteFrameSpeed(12, 0.25);
			Event_Queue_Object_ChangeSpriteFrameSpeed(13, 0.5);
			Event_Queue_Object_ChangeSpriteId(14, SPR_misc_npc_38_dance);
			Event_Queue_Object_ChangeSpriteFrameSpeed(14, 0.25);
			Event_Queue_Object_ChangeSpriteFrameSpeed(15, 0.125);
			Event_Queue_Object_ChangeSpriteFrameSpeed(16, 0.144);
			Event_Queue_Object_ChangeSpriteFrameSpeed(17, 0.144);
			Event_Queue_Object_ChangeSpriteFrameSpeed(18, 0.25);
			Event_Queue_Object_SetColor(18, 255, 255, 255);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 22);
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 2);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 76: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(29104, 12912, 1);
			Event_Queue_Object_WalkTo(0, 29104, 12840, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 29080, 12824, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(2, 29128, 12824, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(3, 29104, 12808, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_JumpToRelative(12, 0, 0, OBJECT_DIRECTION_RIGHT, 16, 12);
			Event_Queue_Dialog_Run(2511);
			Event_Queue_Dialog_Run(2512);
			Event_Queue_StopMusic();
			Event_Queue_PlaySound(SND_ampbroadcast);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(29104, 12720, 2);
			Event_Queue_CreateObject(70, 1, SPR_misc_ampbroadcast, 29104, 12704, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(70, 5);
			Event_Queue_PlaySound(SND_beep_square);
			Event_Queue_WaitFrames(45);
			Event_Queue_Object_ChangeSpriteFrame(70, 6);
			Event_Queue_WaitFrames(70);
			Event_Queue_PlayMusic(MUS_amper);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(2513);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_Dialog_Run(2514);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(2515);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_Dialog_Run(2516);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Dialog_Run(2517);
			Event_Queue_Dialog_Run(2518);
			Event_Queue_StopMusic();
			Event_Queue_Object_ChangeSpriteFrame(70, 5);
			Event_Queue_WaitFrames(6);
			Event_Queue_Object_ChangeSpriteFrame(70, 3);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(60);
			Event_Queue_Camera_MoveTo(29104, 12912, 2);
			
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2519);
			Event_Queue_Dialog_Run(2520);
			Event_Queue_Object_JumpToRelative(14, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(2521);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(2522);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2523);
			Event_Queue_Dialog_Run(2524);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2525);
			Event_Queue_Dialog_Run(2526);
			Event_Queue_Dialog_Run(2527);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(29104, 12848, 6);
			Event_Queue_Object_JumpTo(14, 29104, 12792, OBJECT_DIRECTION_DOWN, 56, 12);
			Event_Queue_SetSync(false);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_Overworld_ShakeScreen(8);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpTo(0, 29104, 12856, OBJECT_DIRECTION_DOWN, 8, 6);
			Event_Queue_Object_JumpTo(1, 29080, 12840, OBJECT_DIRECTION_DOWN, 8, 6);
			Event_Queue_Object_JumpTo(2, 29128, 12840, OBJECT_DIRECTION_DOWN, 8, 6);
			Event_Queue_Object_JumpTo(3, 29104, 12824, OBJECT_DIRECTION_DOWN, 8, 6);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(2528);
			Event_Queue_Dialog_Run(2529);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(12, 29080, 12888, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(13, 29128, 12888, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(2530);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(2531);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2532);
			Event_Queue_Dialog_Run(2533);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2534);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_UP);
			
			Event_Queue_EngageBattle(75, 12);
			Event_Queue_Object_TeleportTo(14, 29104, 12920);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_UP);
			Event_Queue_PlayMusic(MUS_casualneo);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(2535);
			Event_Queue_Dialog_Run(2536);
			Event_Queue_Dialog_Run(2537);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(2538);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2539);
			Event_Queue_Dialog_Run(2540);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(12, 0, 192, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToRelative(14, 0, 192, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(72);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2542);
			Event_Queue_Object_WalkTo(13, 29104, 12888, 1, OBJECT_DIRECTION_UP);
			Event_Queue_CompareIntToConst(&partyMembers[0].armorId, 28);
			Event_Queue_JumpIfNotEqual(0);
			
			Event_Queue_Dialog_Run(2541);
			Event_Queue_WaitFrames(40);
			
			Event_Queue_Label(0);
			Event_Queue_Dialog_Run(2543);
			Event_Queue_Dialog_Run(316);
			Event_Queue_Dialog_Run(2544);
			Event_Queue_Dialog_Run(2393);
			Event_Queue_Dialog_Run(2545);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 51);
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 5);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 77: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.camera.x >= 29344 || overworld.camera.x <= 28896 || overworld.camera.y >= 14160) {
				Event_Queue_Object_TeleportTo(61, 29096, 13952);
			}
			else {
				Event_Queue_Object_WalkTo(61, 29152, 13952, 2, -1);
				Event_Queue_Object_WalkTo(61, 29096, 13952, 2, OBJECT_DIRECTION_DOWN);
			}
			Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DEFEATED, 2);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 78: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Dialog_Run(2595);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_SetSync(true);
			
			Event_Queue_Object_WalkTo(11, 28944, 15616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(11, 28944, 15702, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_QueueWalkTo(11, 29128, 15750, 2, OBJECT_DIRECTION_UP);
			
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_WalkTo(0, 28944, 15616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(0, 28944, 15702, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_QueueWalkTo(0, 29112, 15750, 2, OBJECT_DIRECTION_UP);
			
			Event_Queue_WaitFrames(14);
			Event_Queue_Object_WalkTo(1, 28944, 15616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(1, 28944, 15702, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_QueueWalkTo(1, 29096, 15750, 2, OBJECT_DIRECTION_UP);
			
			Event_Queue_WaitFrames(14);
			Event_Queue_Object_WalkTo(2, 28944, 15616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(2, 28944, 15702, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_QueueWalkTo(2, 29080, 15750, 2, OBJECT_DIRECTION_UP);
			
			Event_Queue_WaitFrames(14);
			Event_Queue_Object_WalkTo(3, 28944, 15616, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(3, 28944, 15702, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_QueueWalkTo(3, 29064, 15750, 2, OBJECT_DIRECTION_UP);
			
			Event_Queue_SetSync(false);
			Event_Queue_Camera_TogglePlayerFollow(false);
			
			Event_Queue_Camera_MoveTo(29152, 15712, 2);
			Event_Queue_WaitFrames(20);
			Event_Queue_Dialog_Run(2596);
			Event_Queue_Dialog_Run(2597);
			Event_Queue_WaitFrames(120);
			Event_Queue_Dialog_Run(2598);
			Event_Queue_Camera_MoveTo(29152, 15584, 1);
			Event_Queue_CreateObject(70, 1, SPR_owchar_flora, 29008, 15544, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(70, 29008, 15560, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(70, 29152, 15592, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(2599);
			Event_Queue_Dialog_Run(2600);
			Event_Queue_Dialog_Run(2601);
			Event_Queue_WaitFrames(90);
			Event_Queue_SetSync(true);
			Event_Queue_Dialog_Run(2602);
			Event_Queue_WaitFrames(125);
			Event_Queue_CreateObject(71, 1, SPR_owchar_npc_29, 29296, 15544, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(71, 29296, 15568, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(71, 29200, 15584, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(2603);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(71, 29200, 15592, 0.5, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2604);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_WaitFrames(90);
			Event_Queue_Dialog_Run(2605);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_Dialog_Run(2606);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_Destroy(71);
			for (int i = 20; i <= 36; i++) {
				Event_Queue_Object_Destroy(i);
			}
			Event_Queue_Camera_TeleportTo(29320, 15556);
			Event_Queue_Object_TeleportTo(11, 29272, 15584);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_TeleportTo(0, 29240, 15560);
			Event_Queue_Object_WalkTo(0, 29320, 15560, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_TeleportTo(1, 29320, 15576);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_TeleportTo(2, 29320, 15592);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_TeleportTo(3, 29320, 15608);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_Dialog_Run(2607);
			Event_Queue_Dialog_Run(2608);
			Event_Queue_Dialog_Run(2609);
			Event_Queue_Dialog_Run(2610);
			Event_Queue_Dialog_Run(2611);
			Event_Queue_Dialog_Run(2612);
			Event_Queue_Dialog_Run(2613);
			Event_Queue_Dialog_Run(2614);
			Event_Queue_Object_WalkTo(11, 29296, 15536, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_Destroy(11);
			
			Event_Queue_Regroup(1);
			Event_Queue_Dialog_Run(2395);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 70);
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 7);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 79: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_CreateTrigger(1, 31792, 12672, 31872, 12752, 80);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 80: {
			overworld.map.doors[147].enabled = true;
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(2615);
			}
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_CreateObject(70, 1, SPR_owchar_flora, 31696, overworld.player.y, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Camera_MoveTo(31784, 12688, 1);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(2670);
				Event_Queue_Dialog_Run(2671);
				Event_Queue_Dialog_Run(2672);
				Event_Queue_Dialog_Run(2673);
				Event_Queue_Dialog_Run(2674);
				Event_Queue_Dialog_Run(2675);
				Event_Queue_Dialog_Run(2676);
				Event_Queue_Dialog_Run(2677);
				Event_Queue_Dialog_Run(2678);
				Event_Queue_Dialog_Run(2627);
				
				Event_Queue_EngageBattle(51, 70);
				Event_Queue_Object_EnableFighterSprite(70, 44, 46, FIGHTER_STATE_HURT);
				
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(2679);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_WalkTo(70, 31840, overworld.player.y, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2396);
				Event_Queue_Dialog_Run(2680);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(31984, 12688, 1);
				Event_Queue_Object_WalkTo(70, 32064, overworld.player.y, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Object_WalkTo(70, 32064, 12688, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2681);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Object_Destroy(10);
				
				Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 8);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 81);
			}
			else {
				Event_Queue_Dialog_Run(2616);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2617);
				Event_Queue_Dialog_Run(2618);
				Event_Queue_Object_EnableFighterSprite(70, 44, 46, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(2619);
				
				Event_Queue_Dialog_Run(2620);
				Event_Queue_Dialog_Run(2621);
				Event_Queue_Dialog_Run(2622);
				Event_Queue_Dialog_Run(2623);
				Event_Queue_Dialog_Run(2624);
				Event_Queue_Dialog_Run(2625);
				Event_Queue_Dialog_Run(2626);
				Event_Queue_Dialog_Run(2627);
				
				Event_Queue_EngageBattle(51, 70);
				Event_Queue_Object_EnableFighterSprite(70, 44, 46, FIGHTER_STATE_HURT);
				
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(2628);
				Event_Queue_Dialog_Run(2629);
				Event_Queue_Dialog_Run(2630);
				Event_Queue_Dialog_Run(2631);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(31984, 12688, 1);
				Event_Queue_Object_WalkTo(70, 32064, overworld.player.y, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Object_WalkTo(70, 32064, 12688, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2632);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Object_Destroy(10);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 80);
			}
			
			
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 81: {
			overworld.map.doors[148].enabled = true;
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 32504, 11784, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 32520, 11800, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 32544, 11800, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(3, 32568, 11800, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Camera_MoveTo(32536, 11768, 2);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(20);
			Event_Queue_Dialog_Run(2633);
			Event_Queue_Dialog_Run(2634);
			Event_Queue_Dialog_Run(2635);
			Event_Queue_Dialog_Run(2636);
			Event_Queue_Dialog_Run(2637);
			Event_Queue_Dialog_Run(2638);
			Event_Queue_Object_WalkTo(10, 32616, 11768, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(10, 32672, 11704, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_WalkTo(10, 32552, 11744, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2396);
			Event_Queue_Dialog_Run(2639);
			Event_Queue_Dialog_Run(2640);
			Event_Queue_Dialog_Run(2641);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(2642);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(2643);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 81);
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 8);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 82: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 31320, 13080, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 31288, 13096, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 31264, 13096, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(3, 31240, 13096, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Camera_MoveTo(31320, 13064, 2);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(90);
			Event_Queue_Dialog_Run(1301);
			Event_Queue_CreateObject(70, 1, SPR_owchar_amp, 30968, 13168, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Camera_MoveTo(31088, 13152, 2);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(70, 31208, 13080, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Camera_MoveTo(31272, 13064, 2);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1302);
			Event_Queue_Dialog_Run(1303);
			Event_Queue_Dialog_Run(1304);
			Event_Queue_Dialog_Run(1305);
			Event_Queue_Dialog_Run(1306);
			Event_Queue_Dialog_Run(1307);
			Event_Queue_Dialog_Run(1308);
			Event_Queue_Dialog_Run(1309);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 90);
			Event_Queue_GotoArea(164, 30544, 13056, -1);
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_Object_WalkTo(0, 30544, 13136, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 30512, 13104, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(2, 30576, 13104, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(3, 30544, 13072, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Camera_TeleportTo(30544, 13168);
			Event_Queue_CreateObject(70, 1, SPR_owchar_amp, 30544, 13216, OBJECT_DIRECTION_UP);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(1310);
			
			Event_Queue_EngageBattle(48, 70);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(1311);
			Event_Queue_PlayMusic(MUS_perspective);
			Event_Queue_Dialog_Run(1312);
			Event_Queue_Dialog_Run(1313);
			Event_Queue_Dialog_Run(1314);
			Event_Queue_Dialog_Run(1315);
			Event_Queue_Dialog_Run(1316);
			Event_Queue_Dialog_Run(1317);
			Event_Queue_Dialog_Run(1318);
			Event_Queue_Dialog_Run(1319);
			Event_Queue_Dialog_Run(1320);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_WalkTo(70, 30544, 13472, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 91);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 83: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 31320, 13080, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(0, 31320, 13064, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 31352, 13096, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 31320, 13096, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 31288, 13096, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(31312, 13052, 1);
			Event_Queue_SetSync(false);
			
			Event_Queue_Object_ToggleGhost(10, true);
			Event_Queue_Object_WalkToPointer(10, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(10, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_Destroy(10);
			Event_Queue_CreateNPC(10, 70000, 31320, 13044, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(254);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3074);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 250);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 84: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 27520, 3560, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(1, 27488, 3560, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(2, 27552, 3560, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(3, 27608, 3592, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Camera_MoveTo(27520, 3584, 1);
			Event_Queue_SetSync(false);
			
			Event_Queue_Dialog_Run(1321);
			Event_Queue_Dialog_Run(1322);
			Event_Queue_Dialog_Run(1323);
			Event_Queue_Dialog_Run(1324);
			Event_Queue_Dialog_Run(1325);
			Event_Queue_Dialog_Run(1326);
			Event_Queue_Dialog_Run(1327);
			Event_Queue_Dialog_Run(1328);
			Event_Queue_Dialog_Run(1329);
			Event_Queue_Dialog_Run(1330);
			Event_Queue_Dialog_Run(1331);
			Event_Queue_Dialog_Run(1332);
			Event_Queue_Dialog_Run(1333);
			Event_Queue_Dialog_Run(1334);
			Event_Queue_Object_JumpToRelative(70, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(1335);
			Event_Queue_Dialog_Run(1336);
			Event_Queue_Dialog_Run(1337);
			Event_Queue_Dialog_Run(1338);
			Event_Queue_Dialog_Run(1339);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(1340);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1341);
			Event_Queue_PlaySound(SND_swing);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_JumpToRelative(70, 0, 0, -1, 256, 120);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportTo(70, 27520, 3472);
			Event_Queue_Object_JumpToRelative(70, 0, 0, -1, 1, 2);
			Event_Queue_Camera_MoveTo(27520, 3472, 16);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_kara_jump);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_PlaySound(SND_flower2);
			Event_Queue_PlaySound(SND_encountermg);
			Event_Queue_SetSync(false);
			Event_Queue_Overworld_FadeIn(60, 255, 255, 255);
			Event_Queue_Overworld_FadeOut(60, 255, 255, 255);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1342);
			Event_Queue_Camera_MoveTo(27520, 3536, 16);
			Event_Queue_Object_JumpTo(70, 27520, 3536, OBJECT_DIRECTION_DOWN, 32, 6);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_kara);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_EnableFighterSprite(70, 67, 76, FIGHTER_STATE_BLOCK);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_Overworld_ShakeScreen(8);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpToRelative(0, 0, 32, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Object_JumpToRelative(1, 0, 32, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Object_JumpToRelative(2, 0, 32, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(90);
			
			Event_Queue_StopMusic();
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Dialog_Run(1343);
			Event_Queue_Profile_KeyItemAdd(176);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_PlayMusic(MUS_megacity);
			Event_Queue_Dialog_Run(1344);
			Event_Queue_Dialog_Run(1345);
			Event_Queue_Object_WalkTo(70, 27520, 3520, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1346);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(80);
			
			Event_Queue_Dialog_Run(1347);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1348);
			Event_Queue_Dialog_Run(1349);
			Event_Queue_Dialog_Run(1350);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 251);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 85: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Camera_MoveTo(2576, 7712, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 2544, 7712, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 2528, 7688, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 2544, 7736, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(3, 2496, 7728, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			
			Event_Queue_FadeOutMusic(2000);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_WaitFrames(80);
				Event_Queue_Dialog_Run(1351);
				Event_Queue_Dialog_Run(1610);
				Event_Queue_Dialog_Run(1611);
				Event_Queue_Dialog_Run(1612);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_PlayMusic(MUS_luxpre);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_cloak2);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(54);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(5);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(54);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_master);
				Event_Queue_PlaySound(SND_dodge);
				Event_Queue_Overworld_ShakeScreen(4);
				Event_Queue_CreateObject(71, 1, SPR_misc_lulu_cloakthrow, 2632, 7724, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(71, 2912, 7664, OBJECT_DIRECTION_DOWN, 96, 120);
				Event_Queue_WaitFrames(34);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(8);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_BLOCK);
				Event_Queue_Camera_TeleportTo(2624, 7712);
				Event_Queue_SetFloatPtr(&overworld.camera.zoom, 12);
				Event_Queue_WaitFrames(1);
				Event_Queue_Object_Destroy(71);
				Event_Queue_PlaySound(SND_firemassattack);
				Event_Queue_Overworld_ShakeScreen(14);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(14);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(13);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(13);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(12);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(12);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(11);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(11);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(10);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(9);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(8);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(7);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(6);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(5);
				Event_Queue_WaitFrames(60);
				Event_Queue_Camera_TeleportTo(2576, 7708);
				Event_Queue_SetFloatPtr(&overworld.camera.zoom, 2);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(1613);
				Event_Queue_Dialog_Run(1614);
				Event_Queue_Dialog_Run(1615);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
				Event_Queue_Dialog_Run(1616);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(1617);
				
				Event_Queue_StopMusic();
				Event_Queue_EngageBattle(87, 70);
				Event_Queue_PlayMusic(MUS_lux);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_master_broken);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(1618);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_beamsword);
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_PlaySound(SND_saw);
				Event_Queue_PlaySound(SND_beamsword);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_ChangeSpriteFrame(0, 2);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(1619);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_RUN);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_StopMusic();
				Event_Queue_Object_JumpTo(0, 2600, 7728, OBJECT_DIRECTION_RIGHT, 0, 6);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_ATTACK2);
				Event_Queue_PlaySound(SND_beamsword);
				Event_Queue_PlaySound(SND_hit3);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_HURT);
				Event_Queue_Object_JumpTo(70, 2648, 7728, OBJECT_DIRECTION_LEFT, 0, 6);
				Event_Queue_WaitFrames(41);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(44);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_master_broken);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(102);
				Event_Queue_CreateObject(71, 1, SPR_misc_collapseblood, 2648, 7723, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(83);
				Event_Queue_Dialog_Run(1620);
				Event_Queue_Dialog_Run(1621);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(1622);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_ATTACK1);
				Event_Queue_WaitFrames(12);
				Event_Queue_PlaySound(SND_firemassattack);
				Event_Queue_Overworld_FadeIn(1, 255, 127, 0);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Object_Destroy(71);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Overworld_FadeOut(1, 255, 127, 0);
				Event_Queue_Object_JumpTo(0, 2568, 7728, OBJECT_DIRECTION_RIGHT, 0, 8);
				Event_Queue_WaitFrames(93);
				Event_Queue_Dialog_Run(1623);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			}
			else {
				Event_Queue_WaitFrames(120);
				Event_Queue_Dialog_Run(1351);
				Event_Queue_Dialog_Run(1352);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(1353);
				Event_Queue_Dialog_Run(1354);
				Event_Queue_Object_JumpToRelative(70, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
				Event_Queue_Dialog_Run(1355);
				Event_Queue_Dialog_Run(1356);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(1357);
				Event_Queue_Dialog_Run(1358);
				Event_Queue_Dialog_Run(1359);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1360);
				Event_Queue_Dialog_Run(1361);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_cloak_happy);
				Event_Queue_Dialog_Run(1362);
				Event_Queue_WaitFrames(20);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_PlayMusic(MUS_luxpre);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_cloak2);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(54);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(5);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(54);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_master);
				Event_Queue_PlaySound(SND_dodge);
				Event_Queue_Overworld_ShakeScreen(4);
				Event_Queue_CreateObject(71, 1, SPR_misc_lulu_cloakthrow, 2632, 7724, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(71, 2912, 7664, OBJECT_DIRECTION_DOWN, 96, 120);
				Event_Queue_WaitFrames(34);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(8);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_BLOCK);
				Event_Queue_Camera_TeleportTo(2624, 7712);
				Event_Queue_SetFloatPtr(&overworld.camera.zoom, 12);
				Event_Queue_WaitFrames(1);
				Event_Queue_PlaySound(SND_firemassattack);
				Event_Queue_Overworld_ShakeScreen(14);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(14);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(13);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(13);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(12);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(12);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(11);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(11);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(10);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(9);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(8);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(7);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(6);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_ShakeScreen(5);
				Event_Queue_WaitFrames(60);
				Event_Queue_Camera_TeleportTo(2576, 7708);
				Event_Queue_SetFloatPtr(&overworld.camera.zoom, 2);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				
				Event_Queue_Dialog_Run(1363);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(1364);
				Event_Queue_Dialog_Run(1365);
				Event_Queue_Dialog_Run(1366);
				Event_Queue_Dialog_Run(1367);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1368);
				Event_Queue_Dialog_Run(1369);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(1370);
				if (profile.cash >= 10000000) {
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
					Event_Queue_Dialog_Run(1371);
					Event_Queue_Dialog_Run(1372);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_Dialog_Run(1373);
				}
				else if (profile.cash == 9999999) {
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
					Event_Queue_Dialog_Run(1371);
					Event_Queue_Dialog_Run(1377);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_Dialog_Run(1374);
				}
				else {
					Event_Queue_Dialog_Run(1374);
				}
				Event_Queue_Dialog_Run(1375);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(1376);
				Event_Queue_WaitFrames(120);
				
				Event_Queue_StopMusic();
				Event_Queue_EngageBattle(87, 70);
				Event_Queue_PlayMusic(MUS_lux);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_HURT);
				Event_Queue_SetVarInt(0, Random_IRange(0, 135));
				Event_Queue_SetVarInt(1, Random_IRange(0, 135));
				Event_Queue_SetVarInt(2, Random_IRange(0, 135));
				Event_Queue_SetVarInt(3, Random_IRange(0, 135));
				Event_Queue_SetVarInt(4, Random_IRange(0, 135));
				Event_Queue_SetVarInt(5, Random_IRange(0, 135));
				Event_Queue_SetVarInt(6, Random_IRange(0, 135));
				Event_Queue_SetVarInt(7, Random_IRange(0, 135));
				
				Event_Queue_WaitFrames(105);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_master_rage);
				Event_Queue_Object_ChangeSpriteFrame(70, 0);
				Event_Queue_Dialog_Run(1378);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(1379);
				Event_Queue_WaitFrames(48);
				Event_Queue_Object_ChangeSpriteFrame(70, 1);
				Event_Queue_Overworld_ShakeScreen(16);
				Event_Queue_Dialog_Run(1380);
				Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_RIGHT, 16, 12);
				Event_Queue_Dialog_Run(1381);
				Event_Queue_WaitFrames(46);
				Event_Queue_Overworld_ShakeScreen(16);
				Event_Queue_Dialog_Run(1382);
				Event_Queue_StopMusic();
				Event_Queue_PlaySound(SND_poison);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_master_broken);
				Event_Queue_Object_ChangeSpriteFrame(70, 0);
				Event_Queue_Object_TeleportToRelative(70, -2, 0);
				Event_Queue_WaitFrames(2);
				Event_Queue_Object_TeleportToRelative(70, 3, 0);
				Event_Queue_WaitFrames(2);
				Event_Queue_Object_TeleportToRelative(70, -2, 0);
				Event_Queue_WaitFrames(2);
				Event_Queue_Object_TeleportToRelative(70, 1, 0);
				Event_Queue_WaitFrames(105);
				Event_Queue_Dialog_Run(1383);
				Event_Queue_Dialog_Run(1384);
				Event_Queue_Dialog_Run(1385);
				if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 8) {
					Event_Queue_Dialog_Run(1386);
				}
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(1387);
				Event_Queue_Dialog_Run(1388);
				Event_Queue_Object_EnableFighterSprite(70, 81, 91, FIGHTER_STATE_RUN);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_Object_JumpTo(70, 2536, 7688.125, OBJECT_DIRECTION_LEFT, 0, 14);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_master_hug);
				Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_HURT);
				Event_Queue_SetSync(true);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
				Event_Queue_Object_JumpTo(0, 2544, 7720, OBJECT_DIRECTION_UP, 8, 12);
				Event_Queue_Object_JumpTo(2, 2544, 7744, OBJECT_DIRECTION_UP, 8, 12);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(65);
				Event_Queue_Dialog_Run(1389);
				Event_Queue_Dialog_Run(1390);
				Event_Queue_WaitFrames(35);
				Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_master_flushed);
				Event_Queue_Object_JumpTo(70, 2544, 7688, OBJECT_DIRECTION_LEFT, 0, 14);
				Event_Queue_WaitFrames(70);
				Event_Queue_Object_DisableFighterSprite(1);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1391);
				Event_Queue_Dialog_Run(1392);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_master);
				Event_Queue_Object_WalkTo(70, 2440, 7704, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(70, 2248, 7640, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Dialog_Run(1393);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(1394);
				Event_Queue_Dialog_Run(1395);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(1396);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1397);
				Event_Queue_Dialog_Run(1398);
				Event_Queue_Dialog_Run(1399);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(1400);
				Event_Queue_Dialog_Run(1401);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 252);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 86: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(30440, 5888, 1);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_WalkTo(70, 30440, 5880, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(70);
				Event_Queue_Object_WalkTo(70, 30440, 5912, 2, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_EngageBattle(88, 70);
				Event_Queue_Object_Destroy(70);
			}
			else {
				Event_Queue_Dialog_Run(1410);
				Event_Queue_Dialog_Run(1411);
				Event_Queue_Object_WalkTo(70, 30440, 5880, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1412);
				Event_Queue_Dialog_Run(1413);
				Event_Queue_Dialog_Run(1414);
				Event_Queue_Object_WalkTo(70, 30440, 5912, 2, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_EngageBattle(88, 70);
				Event_Queue_Object_Destroy(70);
				
				Event_Queue_Dialog_Run(1415);
				Event_Queue_Dialog_Run(1416);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 255);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 87: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_WaitFrames(50);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(13400, 15208, 0.5);
			Event_Queue_Object_WalkTo(0, 13352, 15224, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 13320, 15192, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(2, 13320, 15256, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(3, 13288, 15224, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_TeleportToRelative(70, -1, 0);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_TeleportToRelative(70, 2, 0);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_TeleportToRelative(70, -2, 0);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_TeleportToRelative(70, 2, 0);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_TeleportToRelative(70, -2, 0);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_TeleportToRelative(70, 2, 0);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_TeleportToRelative(70, -2, 0);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_TeleportToRelative(70, 2, 0);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_TeleportToRelative(70, -2, 0);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_TeleportToRelative(70, 2, 0);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_TeleportToRelative(70, -1, 0);
			Event_Queue_Object_JumpToRelative(70, 0, -320, -1, 0, 40);
			Event_Queue_Object_TeleportToRelative(70, -16, -16);
			Event_Queue_Object_JumpToRelative(70, 0, 320, -1, 0, 20);
			Event_Queue_PlaySound(SND_thunder);
			Event_Queue_Overworld_ShakeScreen(57);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_ATTACK1);
			Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_ATTACK1);
			Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_ATTACK1);
			Event_Queue_Object_EnableFighterSprite(3, 79, 88, FIGHTER_STATE_ATTACK1);
			Event_Queue_WaitFrames(180);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(100, 70);
			Event_Queue_SetIntPtr(&overworld.overlayId, 0);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Object_DisableFighterSprite(0);
			Event_Queue_Object_DisableFighterSprite(1);
			Event_Queue_Object_DisableFighterSprite(2);
			Event_Queue_Object_DisableFighterSprite(3);
			Event_Queue_WaitFrames(114);
			
			Event_Queue_Regroup(0.5);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 300);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 88: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Camera_MoveTo(4776, 15256, 0.5);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(53);
			Event_Queue_Dialog_Run(3159);
			Event_Queue_Object_WalkTo(70, 4880, 15122, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(70, 4848, 15024, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(70, 5096, 14976, 2, OBJECT_DIRECTION_RIGHT);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_CreateTrigger(11, 4560, 14880, 4656, 14896, 89);
			Event_Queue_SetFlag(FLAG_PLOT, 301);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 89: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3172);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 90: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3160);
			Event_Queue_Object_WalkTo(70, 5144, 14976, 2, -1);
			Event_Queue_Object_WalkTo(70, 5216, 15144, 2, -1);
			Event_Queue_Object_JumpTo(70, 5144, 15360, OBJECT_DIRECTION_LEFT, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 91: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3162);
			Event_Queue_Object_WalkTo(70, 4984, 15360, 2, -1);
			Event_Queue_Object_JumpTo(70, 4568, 15448, OBJECT_DIRECTION_UP, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 92: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3163);
			Event_Queue_Object_WalkTo(70, 4376, 15408, 2, -1);
			Event_Queue_Object_JumpTo(70, 4288, 15592, OBJECT_DIRECTION_DOWN, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 93: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3164);
			Event_Queue_Object_WalkTo(70, 4464, 15728, 2, -1);
			Event_Queue_Object_JumpTo(70, 4768, 15904, OBJECT_DIRECTION_RIGHT, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 94: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3165);
			Event_Queue_Object_WalkTo(70, 4816, 15904, 2, -1);
			Event_Queue_Object_WalkTo(70, 4968, 15760, 2, -1);
			Event_Queue_Object_JumpTo(70, 5256, 15712, OBJECT_DIRECTION_RIGHT, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 95: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3166);
			Event_Queue_Object_WalkTo(70, 5272, 15792, 2, -1);
			Event_Queue_Object_WalkTo(70, 5128, 15808, 2, -1);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 96: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3167);
			Event_Queue_Object_WalkTo(70, 5112, 15888, 2, -1);
			Event_Queue_Object_WalkTo(70, 5256, 15904, 2, -1);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 97: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3168);
			Event_Queue_Object_WalkTo(70, 5408, 15904, 2, -1);
			Event_Queue_Object_JumpTo(70, 5472, 15440, OBJECT_DIRECTION_UP, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 98: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3169);
			Event_Queue_Object_WalkTo(70, 5472, 15312, 2, -1);
			Event_Queue_Object_JumpTo(70, 6288, 15648, OBJECT_DIRECTION_UP, 16, 4);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 99: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Camera_MoveTo(6288, 15644, 0.5);
			Event_Queue_WaitFrames(6);
			for (int i = 0; i < 64; i++) {
				Event_Queue_SetTempFlag(TEMPFLAG_POSTFINALDIALOG_BRIGHTNESS, 3 + i * 4);
				Event_Queue_WaitFrames(1);
			}
			Event_Queue_WaitFrames(58);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(3170);
			Event_Queue_WaitFrames(76);
			Event_Queue_Dialog_Run(3171);
			Event_Queue_Object_WalkTo(70, 6288, 15618, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_SetColor(70, 191, 191, 191);
			Event_Queue_WaitFrames(28);
			Event_Queue_Object_SetColor(70, 127, 127, 127);
			Event_Queue_WaitFrames(28);
			Event_Queue_Object_SetColor(70, 63, 63, 63);
			Event_Queue_WaitFrames(28);
			Event_Queue_Object_Destroy(70);
			for (int i = 0; i < 32; i++) {
				Event_Queue_SetTempFlag(TEMPFLAG_POSTFINALDIALOG_BRIGHTNESS, 248 - i * 8);
				Event_Queue_WaitFrames(1);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 100: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_MoveTo(6704, 16056, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 6704, 16056, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_WalkTo(1, 6664, 16104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 6744, 16104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 6704, 16104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(58);
			Event_Queue_Object_ToggleGhost(10, true);
			Event_Queue_Object_WalkToPointer(10, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_WaitFrames(37);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(10, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_StopMusic();
			Event_Queue_StopAllSounds();
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Overworld_FadeIn(1, 255, 127, 0);
			Event_Queue_Object_Destroy(10);
			Event_Queue_WaitFrames(6);
			Event_Queue_Overworld_FadeOut(1, 255, 127, 0);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_WaitFrames(68);
			Event_Queue_Dialog_Run(1420);
			Event_Queue_Dialog_Run(1421);
			Event_Queue_Dialog_Run(1422);
			Event_Queue_PlaySound(SND_swing);
			Event_Queue_CreateSpark(3, 6704, 16016, 0);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(24);
			Event_Queue_CreateSpark(4, 6704, 16016, 0);
			Event_Queue_PlaySound(SND_explode);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(6704, 16088, 3);
			Event_Queue_Object_JumpTo(0, 6704, 16104, OBJECT_DIRECTION_UP, 16, 8);
			Event_Queue_Object_JumpTo(1, 6664, 16136, OBJECT_DIRECTION_UP, 16, 8);
			Event_Queue_Object_JumpTo(2, 6744, 16136, OBJECT_DIRECTION_UP, 16, 8);
			Event_Queue_Object_JumpTo(3, 6704, 16168, OBJECT_DIRECTION_UP, 16, 8);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(65);
			Event_Queue_Dialog_Run(1423);
			Event_Queue_Dialog_Run(1424);
			Event_Queue_Dialog_Run(1425);
			Event_Queue_Dialog_Run(1426);
			Event_Queue_CreateObject(70, 1, SPR_misc_lulu_god_entry, 6704, 15920, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrameSpeed(70, 0.125);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpTo(70, 6704, 16064, OBJECT_DIRECTION_UP, 32, 390);
			Event_Queue_WaitFrames(92);
			Event_Queue_PlaySound(SND_ruentry);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(4);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_god_entryland);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Object_ChangeSpriteFrameSpeed(70, 0);
			Event_Queue_WaitFrames(58);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_god);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(16);
			Event_Queue_PlayMusic(MUS_lastresort_intro);
			Event_Queue_Dialog_Run(1427);
			Event_Queue_Dialog_Run(1428);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_god_entryland);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Dialog_Run(1429);
			Event_Queue_Dialog_Run(1430);
			Event_Queue_Dialog_Run(1431);
			Event_Queue_Dialog_Run(1432);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_WaitFrames(16);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_god);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(26);
			Event_Queue_Dialog_Run(1433);
			Event_Queue_Dialog_Run(1434);
			Event_Queue_Dialog_Run(1435);
			Event_Queue_Object_JumpToRelative(2, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(1436);
			Event_Queue_Dialog_Run(1437);
			Event_Queue_Dialog_Run(1438);
			Event_Queue_Dialog_Run(1439);
			Event_Queue_Dialog_Run(1440);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(101, 70);
			
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_collapse_ruby);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_collapse_noah);
			Event_Queue_Object_ChangeSpriteFrame(1, 1);
			Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_collapse_emmet);
			Event_Queue_Object_ChangeSpriteFrame(2, 1);
			Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_collapse_sally_neo);
			Event_Queue_Object_ChangeSpriteFrame(3, 1);
			Event_Queue_WaitFrames(120);
			Event_Queue_PlayMusic(MUS_oh);
			Event_Queue_Dialog_Run(1441);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1442);
			Event_Queue_Dialog_Run(1443);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(1444);
			Event_Queue_Dialog_Run(237);
			Event_Queue_Dialog_Run(1445);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_god_rage);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(1446);
			Event_Queue_StopMusic();
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_EnableFighterSprite(70, 82, 94, FIGHTER_STATE_ATTACK1);
			Event_Queue_Dialog_Run(1447);
			Event_Queue_WaitFrames(82);
			Event_Queue_Dialog_Run(149);
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_PlaySound(SND_swing);
			Event_Queue_Object_EnableFighterSprite(70, 82, 94, FIGHTER_STATE_ATTACK3);
			Event_Queue_WaitFrames(231);
			Event_Queue_Overworld_FadeOut(1, 0, 0, 0);
			Event_Queue_WaitFrames(131);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_god);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(104);
			Event_Queue_Dialog_Run(1448);
			Event_Queue_Dialog_Run(1449);
			Event_Queue_Dialog_Run(1450);
			Event_Queue_PlaySound(SND_poison);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_god_cry);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Object_TeleportToRelative(70, -2, 0);
			Event_Queue_WaitFrames(2);
			Event_Queue_Object_TeleportToRelative(70, 3, 0);
			Event_Queue_WaitFrames(2);
			Event_Queue_Object_TeleportToRelative(70, -2, 0);
			Event_Queue_WaitFrames(2);
			Event_Queue_Object_TeleportToRelative(70, 1, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(1451);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_Dialog_Run(1452);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_sally_neo);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(50);
			Event_Queue_ChangeEvent(101);
		} break;
		
		case 101: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 6704, 16088, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 6664, 16108, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 6744, 16112, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 6704, 16116, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1453);
			Event_Queue_Dialog_Run(1454);
			Event_Queue_Dialog_Run(1455);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(1456);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_Dialog_Run(1457);
			Event_Queue_Dialog_Run(1458);
			Event_Queue_Dialog_Run(1459);
			Event_Queue_Object_WalkTo(0, 6688, 16064, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1460);
			Event_Queue_Dialog_Run(1461);
			Event_Queue_Object_JumpToRelative(2, 0, 0, OBJECT_DIRECTION_UP, 16, 12);
			Event_Queue_Dialog_Run(1462);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_EnableFighterSprite(3, 79, 88, FIGHTER_STATE_ATTACK1);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_JumpToRelative(2, 16, 0, OBJECT_DIRECTION_LEFT, 0, 6);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(1463);
			Event_Queue_Object_DisableFighterSprite(3);
			Event_Queue_Object_WalkToRelative(2, -16, 0, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1464);
			Event_Queue_Dialog_Run(1465);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_Dialog_Run(1466);
			Event_Queue_Dialog_Run(1467);
			Event_Queue_Dialog_Run(1468);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_JumpToRelative(0, 6, 0.125, OBJECT_DIRECTION_RIGHT, 0, 6);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_hug);
			Event_Queue_WaitFrames(140);
			Event_Queue_Object_ChangeSpriteFrame(70, 3);
			Event_Queue_Dialog_Run(1469);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(1470);
			Event_Queue_Object_WalkTo(1, 6720, 16080, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(1, 6720, 16064, 0.5, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1471);
			Event_Queue_Object_JumpToRelative(1, -6, 0.125, OBJECT_DIRECTION_LEFT, 0, 6);
			Event_Queue_Object_ChangeSpriteId(1, SPR_misc_noah_hug);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_WaitFrames(126);
			Event_Queue_Dialog_Run(1472);
			Event_Queue_WaitFrames(36);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpToRelative(0, -6, -0.125, OBJECT_DIRECTION_RIGHT, 0, 6);
			Event_Queue_Object_JumpToRelative(1, 6, -0.125, OBJECT_DIRECTION_LEFT, 0, 6);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_god);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 6704, 16088, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 6664, 16108, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1474);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
			Event_Queue_Object_WalkTo(0, 6704, 16088, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1473);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_lulu_god);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(70);
			
			Event_Queue_Label(0);
			Event_Queue_Dialog_Run(1475);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(71);
			Event_Queue_PlaySound(SND_chess_check);
			Event_Queue_CreateNPC(10, 60000, 6704, 16024, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(95);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(6704, 16056, 0.5);
			Event_Queue_Object_WalkTo(70, 6736, 16064, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(70, 6736, 15992, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_QueueWalkTo(70, 6704, 15992, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1476);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(1477);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1478);
			Event_Queue_Object_WalkTo(70, 6704, 15936, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Camera_MoveTo(6704, 16056, 1);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 6704, 16056, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_WalkTo(1, 6664, 16104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 6744, 16104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(3, 6704, 16104, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(58);
			Event_Queue_Object_ToggleGhost(10, true);
			Event_Queue_Object_WalkToPointer(10, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_WaitFrames(37);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(10, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_Destroy(10);
			Event_Queue_CreateNPC(10, 70000, 6704, 16028, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(250);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3070);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 500);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_ChangeEvent(102);
		} break;
		
		case 102: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(3061);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(1);
			Event_Queue_Dialog_Run(3064);
			
			Event_Queue_Label(1);
			Event_Queue_FadeOutMusic(1500);
			Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_Party_Leave(1);
			Event_Queue_Profile_InventoryPartyOrderRemove(1);
			Event_Queue_Party_Leave(2);
			Event_Queue_Profile_InventoryPartyOrderRemove(2);
			Event_Queue_Party_Leave(3);
			Event_Queue_Profile_InventoryPartyOrderRemove(3);
			
			Event_Queue_PlaySound(SND_encountermg_slow);
			Event_Queue_WaitFrames(240);
			Event_Queue_GotoArea(240, 280, 10376, -1);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 103: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(280, 9776, 0.5);
			Event_Queue_Object_WalkTo(0, 280, 9824, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(35);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_RUBY_GODMODE]) {
				Event_Queue_Dialog_Run(3233);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(66);
				Event_Queue_Dialog_Run(3234);
			}
			else {
				Event_Queue_Dialog_Run(3173);
				Event_Queue_Dialog_Run(3174);
				Event_Queue_Dialog_Run(3175);
				Event_Queue_Dialog_Run(3176);
				Event_Queue_Dialog_Run(3177);
				Event_Queue_WaitFrames(66);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(3178);
			}
			Event_Queue_Object_ToggleGhost(70, true);
			Event_Queue_Object_WalkTo(70, 280, 9744, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_SetColor(70, 191, 191, 191);
			Event_Queue_Object_WalkTo(70, 280, 9736, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_Object_SetColor(70, 127, 127, 127);
			Event_Queue_Object_WalkTo(70, 280, 9728, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_Object_SetColor(70, 63, 63, 63);
			Event_Queue_Object_WalkTo(70, 280, 9720, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(95);
			Event_Queue_Object_ToggleGhost(0, true);
			Event_Queue_Object_WalkTo(0, 280, 9744, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ToggleGhost(0, false);
			Event_Queue_FadeOutMusic(1500);
			Event_Queue_Overworld_FadeIn(120, 0, 0, 0);
			Event_Queue_WaitFrames(60);
			Event_Queue_GotoArea(251, 280, 11896, -1);
			Event_Queue_Overworld_FadeOut(60, 0, 0, 0);
			
			Event_Queue_Regroup(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 104: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_Overworld_FadeIn(60, 0, 0, 0);
			Event_Queue_WaitFrames(30);
			if (profile.flags[FLAG_RUBY_GODMODE]) {
				Event_Queue_Dialog_Run(3235);
			}
			else {
				Event_Queue_Dialog_Run(3179);
			}
			Event_Queue_WaitFrames(60);
			Event_Queue_GotoArea(252, 1120, 10576, -1);
			Event_Queue_Overworld_FadeOut(1, 0, 0, 0);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 105: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_StopMusic();
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_SetSync(true);
			//Event_Queue_Object_WalkTo(0, 2552, 11640, 0.125, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkToRelative(0, 0, -40, 0.125, OBJECT_DIRECTION_UP);
			Event_Queue_Overworld_FadeIn(240, 255, 255, 255);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			
			if (profile.flags[FLAG_NOAH_JOINED]) {
				Event_Queue_Party_Join(1);
				Event_Queue_Profile_InventoryPartyOrderAdd(1);
			}
			if (profile.flags[FLAG_EMMET_JOINED]) {
				Event_Queue_Party_Join(2);
				Event_Queue_Profile_InventoryPartyOrderAdd(2);
			}
			if (profile.flags[FLAG_SALLY_JOINED]) {
				Event_Queue_Party_Join(3);
				Event_Queue_Profile_InventoryPartyOrderAdd(3);
			}
			
			Event_Queue_GotoArea(202, 6704, 16064, -1);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Overworld_FadeOut(120, 255, 255, 255);
				
				Event_Queue_Regroup(1);
			}
			else {
				Event_Queue_Object_TeleportTo(1, 6664, 16104);
				Event_Queue_Object_TeleportTo(2, 6744, 16104);
				Event_Queue_Object_TeleportTo(3, 6704, 16104);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
				Event_Queue_Overworld_FadeOut(120, 255, 255, 255);
				Event_Queue_WaitFrames(47);
				Event_Queue_Dialog_Run(1480);
				Event_Queue_Dialog_Run(1481);
				
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(1482);
			}
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 106: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(2552, 11596, 0.5);
			Event_Queue_Object_WalkTo(0, 2552, 11704, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(120);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(102, 10);
			Event_Queue_Object_Destroy(10);
			Event_Queue_WaitFrames(60);
			
			Event_Queue_Regroup(0.5);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 107: {
			if (profile.flags[FLAG_METRO_LOCATION] == 0) {
				overworld.map.doors[201].x2 = 9328; overworld.map.doors[201].y2 = 5424; overworld.map.doors[201].area2 = 0;
			}
			else if (profile.flags[FLAG_METRO_LOCATION] == 1) {
				overworld.map.doors[201].x2 = 14448; overworld.map.doors[201].y2 = 7616; overworld.map.doors[201].area2 = 6;
			}
			else if (profile.flags[FLAG_METRO_LOCATION] == 2) {
				overworld.map.doors[201].x2 = 26912; overworld.map.doors[201].y2 = 6960; overworld.map.doors[201].area2 = 80;
			}
			else {
				overworld.map.doors[201].x2 = 21888; overworld.map.doors[201].y2 = 3712; overworld.map.doors[201].area2 = 150;
			}
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 108: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(1486);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_SetFlag(FLAG_PLOT, 501);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 109: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(8608, 5312, 1);
			Event_Queue_Object_WalkTo(0, 8568, 5304, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 8648, 5304, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 8608, 5272, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkTo(3, 8608, 5336, 1, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(35);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(37);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(35);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1490);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1491);
			Event_Queue_Dialog_Run(1492);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1493);
			Event_Queue_Object_JumpToRelative(3, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
			Event_Queue_Dialog_Run(1494);
			Event_Queue_Dialog_Run(1495);
			
			Event_Queue_Regroup(2);
			Event_Queue_SetFlag(FLAG_PLOT, 502);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 110: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_PlaySound(SND_swing);
			Event_Queue_Object_JumpTo(70, 12384, 11792, OBJECT_DIRECTION_RIGHT, 96, 35);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_PlaySound(SND_firemassattack);
			Event_Queue_Object_ToggleWalkAnimation(0, false);
			Event_Queue_Object_ToggleWalkAnimation(1, false);
			Event_Queue_Object_ToggleWalkAnimation(2, false);
			Event_Queue_Object_ToggleWalkAnimation(3, false);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_HURT);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_HURT);
				Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_HURT);
				Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_HURT);
			}
			Event_Queue_SetSync(true);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_ATTACK3);
			Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
			Event_Queue_Object_WalkTo(0, 12448, 11792, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 12472, 11760, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 12472, 11824, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(3, 12496, 11792, 8, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(1);
			Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ToggleWalkAnimation(0, true);
			Event_Queue_Object_ToggleWalkAnimation(1, true);
			Event_Queue_Object_ToggleWalkAnimation(2, true);
			Event_Queue_Object_ToggleWalkAnimation(3, true);
			Event_Queue_WaitFrames(120);
			Event_Queue_Camera_MoveTo(12416, 11784, 1);
			Event_Queue_PlayMusic(MUS_lu);
			Event_Queue_Dialog_Run(1080);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_IDLE);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_IDLE);
			}
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(profile.flags[FLAG_ALONE] ? 1087 : 1081);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_omega_rage);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(1082);
			
			Event_Queue_EngageBattle(22, 70);
			Event_Queue_Object_ChangeSpriteId(70, -1);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_HURT);
			Event_Queue_WaitFrames(140);
			Event_Queue_Object_DisableFighterSprite(0);
			if (!profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_DisableFighterSprite(1);
				Event_Queue_Object_DisableFighterSprite(2);
				Event_Queue_Object_DisableFighterSprite(3);
			}
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_lulu_omega_rage);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(1083);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(1084);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(70, 16, 26, FIGHTER_STATE_RUN);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Object_JumpTo(70, 11848, 11656, OBJECT_DIRECTION_LEFT, 64, 60);
			Event_Queue_Object_Destroy(70);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_PLOT, 135);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 111: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(21992, 3464, 2);
			Event_Queue_Object_WalkTo(0, 21964, 3464, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(1510);
			
			Event_Queue_Regroup(2);
			Event_Queue_SetFlag(FLAG_PLOT, 151);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 112: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(25888, 3568, 1);
			Event_Queue_Object_WalkTo(0, 25888, 3576, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(18);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Object_WalkTo(70, 25928, 3576, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1520);
			Event_Queue_Dialog_Run(192);
			Event_Queue_Dialog_Run(1524);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TeleportTo(29240, 3320);
			Event_Queue_Object_TeleportTo(0, 29208, 3344);
			Event_Queue_Object_TeleportTo(70, 29288, 3344);
			Event_Queue_StopMusic();
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(1521);
			Event_Queue_Dialog_Run(1522);
			Event_Queue_Dialog_Run(1523);
			Event_Queue_PlayMusic(MUS_lastresort_pitchdown);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1525);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(1526);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1527);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(1528);
			Event_Queue_WaitFrames(86);
			Event_Queue_Object_WalkTo(70, 29272, 3344, 0.5, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1529);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_panda_beamsword);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Dialog_Run(1530);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(1531);
			Event_Queue_Dialog_Run(1532);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_panda);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1533);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_panda_beamsword);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Dialog_Run(1534);
			Event_Queue_StopMusic();
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_WaitFrames(30);
			Event_Queue_PlaySound(SND_saw);
			Event_Queue_PlaySound(SND_beamsword);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_ChangeSpriteFrame(70, 3);
			Event_Queue_WaitFrames(55);
			Event_Queue_Object_EnableFighterSprite(70, 83, 96, FIGHTER_STATE_ATTACK1);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1535);
			
			Event_Queue_EngageBattle(103, 70);
			
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_collapse_panda);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_WaitFrames(73);
			Event_Queue_Dialog_Run(1555);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(1556);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportToRelative(70, -0.5, 0);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportToRelative(70, 1, 0);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportToRelative(70, -1, 0);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportToRelative(70, 1, 0);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportToRelative(70, -1, 0);
			Event_Queue_WaitFrames(10);
			Event_Queue_Object_TeleportToRelative(70, 0.5, 0);
			Event_Queue_Dialog_Run(1557);
			Event_Queue_PlaySound(SND_poison);
			Event_Queue_CreateNPC(40, 132, 29272, 3344, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(30);
			Event_Queue_CreateObject(41, 1, SPR_misc_collapseblood, 29272, 3343, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeSpriteFrame(41, 1);
			Event_Queue_WaitFrames(150);
			
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(1558);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 3);
			Event_Queue_SetFlag(FLAG_ALONE_PLOT, 40);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 113: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_WalkTo(70, overworld.player.x, 9688, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1570);
			Event_Queue_Dialog_Run(1571);
			Event_Queue_Dialog_Run(1572);
			Event_Queue_Dialog_Run(1573);
			Event_Queue_Dialog_Run(1574);
			Event_Queue_Dialog_Run(192);
			Event_Queue_Dialog_Run(1575);
			Event_Queue_Dialog_Run(2395);
			Event_Queue_Dialog_Run(1576);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(0, 40, -4, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 30072, 9688, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(70, 30072, 9728, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(15);
			
			Event_Queue_Regroup(2);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 7);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 114: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Camera_MoveTo(31496, 13164, 2);
			Event_Queue_WaitFrames(40);
			Event_Queue_Dialog_Run(1580);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_amp);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 31032, 13168, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_JumpTo(70, 31544, 13160, OBJECT_DIRECTION_DOWN, 8, 12);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(8);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1581);
			Event_Queue_Object_EnableFighterSprite(70, 40, 42, FIGHTER_STATE_RUN);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(31096, 13164, 12);
			Event_Queue_Object_JumpTo(70, 31096, 13168, OBJECT_DIRECTION_LEFT, 64, 60);
			Event_Queue_SetSync(false);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_amp_kneel);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_PlaySound(SND_thunder);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_PlayMusic(MUS_scary2);
			Event_Queue_WaitFrames(31);
			Event_Queue_Dialog_Run(1582);
			Event_Queue_Dialog_Run(192);
			Event_Queue_Dialog_Run(1583);
			Event_Queue_Dialog_Run(1584);
			Event_Queue_Dialog_Run(1585);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(48, 70);
			Event_Queue_Object_EnableFighterSprite(70, 40, 42, FIGHTER_STATE_HURT);
			
			Event_Queue_WaitFrames(115);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(1586);
			if (profile.flags[FLAG_ALONE_PLOT] >= 40) {
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_beamsword);
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_PlaySound(SND_saw);
				Event_Queue_PlaySound(SND_beamsword);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_ChangeSpriteFrame(0, 2);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_IDLE);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(1587);
				Event_Queue_Dialog_Run(1588);
				Event_Queue_Dialog_Run(1589);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_ATTACK1);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteFrame(70, 2);
				Event_Queue_Dialog_Run(1590);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
				Event_Queue_Dialog_Run(1591);
				Event_Queue_Dialog_Run(1592);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(1593);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				
				Event_Queue_WaitFrames(96);
				Event_Queue_Dialog_Run(1596);
				Event_Queue_Dialog_Run(1597);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_beamsword);
				Event_Queue_Object_ChangeSpriteFrame(0, 2);
				Event_Queue_WaitFrames(12);
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_ChangeSpriteFrame(0, 0);
				Event_Queue_WaitFrames(12);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_WaitFrames(12);
				Event_Queue_PlayMusic(MUS_blue);
				Event_Queue_Dialog_Run(1598);
				Event_Queue_Object_ChangeSpriteFrame(70, 1);
				Event_Queue_Dialog_Run(1599);
				Event_Queue_AddCash(100000);
				Event_Queue_Dialog_Run(1606);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_amp);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(1604);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 31320, 13080, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_QueueWalkTo(0, 31320, 13064, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Camera_MoveTo(31320, 13060, 2);
				Event_Queue_WaitFrames(68);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(30);
				
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1605);
				Event_Queue_Object_WalkTo(70, 31544, 13224, 6, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(70, 31544, 13156, OBJECT_DIRECTION_LEFT, 32, 20);
				Event_Queue_Object_Destroy(70);
				Event_Queue_CreateNPC(11, 128, 31544, 13156, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(11, SPR_misc_amp_sit);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(1594);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_RUN);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_SetSync(true);
				Event_Queue_Object_JumpTo(0, 31072, 13168, OBJECT_DIRECTION_RIGHT, 0, 8);
				Event_Queue_Dialog_Run(1595);
				Event_Queue_SetSync(false);
				Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
				Event_Queue_PlaySound(SND_hit3);
				Event_Queue_SetFlag(FLAG_ALONE_PLOT, 50);
				Event_Queue_WaitFrames(150);
				Event_Queue_PlaySound(SND_poison);
				Event_Queue_WaitFrames(174);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_IDLE);
				Event_Queue_Object_Destroy(70);
				Event_Queue_CreateNPC(11, 128, 31096, 13168, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(12, 1, SPR_misc_collapseblood, 31096, 13167, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				Event_Queue_WaitFrames(63);
				Event_Queue_Object_ChangeSpriteFrame(12, 1);
				Event_Queue_WaitFrames(140);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_beamsword);
				Event_Queue_Object_ChangeSpriteFrame(0, 2);
				Event_Queue_WaitFrames(12);
				Event_Queue_Object_ChangeSpriteFrame(0, 1);
				Event_Queue_WaitFrames(6);
				Event_Queue_Object_ChangeSpriteFrame(0, 0);
				Event_Queue_WaitFrames(12);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_WaitFrames(12);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 31320, 13080, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_QueueWalkTo(0, 31320, 13064, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Camera_MoveTo(31320, 13060, 2);
				Event_Queue_SetSync(false);
				
				Event_Queue_Label(0);
			}
			else {
				Event_Queue_PlayMusic(MUS_blue);
				Event_Queue_Dialog_Run(1600);
				Event_Queue_Dialog_Run(1601);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
				Event_Queue_Dialog_Run(1602);
				Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_amp);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(1603);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				
				Event_Queue_Object_WalkTo(70, 31544, 13224, 6, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(70, 31544, 13156, OBJECT_DIRECTION_LEFT, 32, 20);
				Event_Queue_Object_Destroy(70);
				Event_Queue_CreateNPC(11, 128, 31544, 13156, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(11, SPR_misc_amp_sit);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 31320, 13080, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_QueueWalkTo(0, 31320, 13064, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Camera_MoveTo(31320, 13060, 2);
				Event_Queue_SetSync(false);
			}
			
			Event_Queue_Object_ToggleGhost(10, true);
			Event_Queue_Object_WalkToPointer(10, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
			Event_Queue_Object_WalkToPointer(10, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_Destroy(10);
			Event_Queue_CreateNPC(10, 70000, 31320, 13044, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(254);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3074);
			
			Event_Queue_Regroup(1);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 250);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 115: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_WalkTo(70, overworld.player.x, 9688, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1570);
			Event_Queue_Dialog_Run(1571);
			Event_Queue_Dialog_Run(1572);
			Event_Queue_Dialog_Run(1573);
			Event_Queue_Dialog_Run(1574);
			Event_Queue_Dialog_Run(192);
			Event_Queue_Dialog_Run(1575);
			Event_Queue_Dialog_Run(2395);
			Event_Queue_Dialog_Run(1576);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(0, 40, -4, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 30072, 9688, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_QueueWalkTo(70, 30072, 9728, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(15);
			
			Event_Queue_Regroup(2);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 7);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 116: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_FadeOutMusic(4000);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(30296, 15020, 1);
			Event_Queue_Object_WalkTo(0, 30264, 15024, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			
			Event_Queue_WaitFrames(110);
			Event_Queue_Object_JumpToRelative(10, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
			Event_Queue_Dialog_Run(1630);
			Event_Queue_PlaySound(SND_birchswing2);
			Event_Queue_Object_JumpTo(10, 30328, 15000, OBJECT_DIRECTION_LEFT, 48, 20);
			Event_Queue_Dialog_Run(1631);
			Event_Queue_Object_WalkTo(11, 30328, 15048, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(1632);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1633);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_JumpToRelative(11, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1634);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1635);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1636);
			Event_Queue_WaitFrames(150);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(105);
			Event_Queue_Dialog_Run(1637);
			Event_Queue_Dialog_Run(1638);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(1639);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(1640);
			Event_Queue_Object_EnableFighterSprite(11, 85, 98, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(1641);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1642);
			Event_Queue_Object_DisableFighterSprite(11);
			Event_Queue_Dialog_Run(1643);
			Event_Queue_Object_EnableFighterSprite(11, 85, 98, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(1644);
			Event_Queue_Dialog_Run(1645);
			Event_Queue_Dialog_Run(1646);
			Event_Queue_Dialog_Run(1647);
			Event_Queue_Dialog_Run(1648);
			Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(1649);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_EnableFighterSprite(10, 84, 97, FIGHTER_STATE_IDLE);
			Event_Queue_Dialog_Run(1650);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(104, 10);
			Event_Queue_Object_DisableFighterSprite(0);
			Event_Queue_SetFlag(FLAG_ALONE_PLOT, 100);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Object_Destroy(11);
			Event_Queue_CreateNPC(10, 133, 30328, 15000, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateNPC(11, 134, 30328, 15048, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(12, 1, SPR_misc_collapseblood, 30328, 14999, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(12, 1);
			Event_Queue_CreateObject(13, 1, SPR_misc_collapseblood, 30328, 15047, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(13, 1);
			Event_Queue_WaitFrames(90);
			
			Event_Queue_Regroup(0.5);
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 117: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(6704, 16104, 0.5);
			Event_Queue_Object_WalkTo(0, 6704, 16152, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(60);
			
			Event_Queue_Dialog_Run(1670);
			Event_Queue_Object_WalkTo(0, 6704, 16136, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_PlayMusic(MUS_lastresort_intro);
			Event_Queue_Dialog_Run(1671);
			Event_Queue_Dialog_Run(1672);
			Event_Queue_Dialog_Run(1673);
			Event_Queue_Dialog_Run(1674);
			Event_Queue_Dialog_Run(1675);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(101, 70);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_god);
			Event_Queue_Object_Destroy(70);
			Event_Queue_CreateObject(70, 1, SPR_misc_collapseblood, 6704, 16072, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(60);
			
			Event_Queue_Camera_MoveTo(6704, 16056, 1);
			Event_Queue_Object_WalkTo(0, 6704, 16056, 1, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(58);
			Event_Queue_Object_ToggleGhost(10, true);
			Event_Queue_Object_WalkToPointer(10, 0, -320, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_WaitFrames(37);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_WalkToPointer(10, 0, -36, 2, OBJECT_DIRECTION_UP, &overworld.player.x, &overworld.player.y);
			Event_Queue_PlaySound(SND_introwakeup);
			Event_Queue_WaitFrames(30);
			Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_Destroy(10);
			Event_Queue_CreateNPC(10, 70000, 6704, 16028, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 255, 255, 255);
			Event_Queue_WaitFrames(60);
			Event_Queue_Profile_KeyItemAdd(250);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3070);
			
			Event_Queue_RemoveCurrentTrigger();
			Event_Queue_SetFlag(FLAG_PLOT, 500);
			Event_Queue_SetFlag(FLAG_ALONE_PLOT, 110);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_ChangeEvent(102);
		} break;
		
		case 118: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(4000);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(13384, 15224, 1);
			Event_Queue_Object_WalkTo(0, 13432, 15224, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(30);
			
			Event_Queue_Dialog_Run(1700);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(28);
			Event_Queue_Object_JumpToRelative(12, 0, 0, OBJECT_DIRECTION_RIGHT, 16, 12);
			Event_Queue_Dialog_Run(1701);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(63);
			Event_Queue_Object_JumpToRelative(13, 0, 0, OBJECT_DIRECTION_RIGHT, 16, 12);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(1702);
			Event_Queue_Object_JumpToRelative(11, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
			Event_Queue_Dialog_Run(1703);
			Event_Queue_Object_JumpToRelative(10, 0, 0, OBJECT_DIRECTION_LEFT, 16, 12);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(12, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1704);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(36);
			Event_Queue_Dialog_Run(1705);
			
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 13384, 15256, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_WalkToRelative(10, 0, 24, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			
			Event_Queue_Dialog_Run(1706);
			Event_Queue_Dialog_Run(1707);
			Event_Queue_Dialog_Run(1708);
			Event_Queue_Dialog_Run(1709);
			Event_Queue_Dialog_Run(1710);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1711);
			Event_Queue_Object_JumpToRelative(13, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
			Event_Queue_Dialog_Run(1712);
			Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1713);
			Event_Queue_Dialog_Run(1714);
			Event_Queue_Dialog_Run(1715);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(105, 10);
			Event_Queue_ShowEnding(1);
		} break;
		
		case 119: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_CreateObject(70, 1, SPR_owchar_gregory, 2152, 744, OBJECT_DIRECTION_DOWN);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Overworld_ShakeScreen(4);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Camera_MoveTo(2152, 776, 16);
			Event_Queue_PlaySound(SND_surprise);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(2684);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(2152, 1048, 5);
			Event_Queue_Object_WalkTo(0, 2168, 1096, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 2168, 1128, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 2136, 1088, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(70, 2152, 1016, 3, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_Dialog_Run(2685);
			Event_Queue_Dialog_Run(2686);
			Event_Queue_Dialog_Run(2687);
			Event_Queue_Dialog_Run(2688);
			Event_Queue_Dialog_Run(2689);
			Event_Queue_Dialog_Run(2690);
			Event_Queue_Dialog_Run(2691);
			Event_Queue_Dialog_Run(2692);
			Event_Queue_Dialog_Run(2693);
			Event_Queue_Dialog_Run(2694);
			Event_Queue_Dialog_Run(2695);
			Event_Queue_Dialog_Run(2696);
			Event_Queue_PlayMusic(MUS_scary);
			Event_Queue_Dialog_Run(2697);
			Event_Queue_Dialog_Run(2698);
			Event_Queue_Dialog_Run(2699);
			Event_Queue_Dialog_Run(2700);
			Event_Queue_Dialog_Run(2701);
			Event_Queue_Dialog_Run(2702);
			Event_Queue_Object_WalkToRelative(0, 0, -16, 0.25, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2703);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2704);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2705);
			
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(83, 70);
			
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_gregory_defeated);
			Event_Queue_CreateObject(71, 1, SPR_misc_gregoryscythe, 2140, 1010, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(72, 1, SPR_misc_gregorygun, 2160, 1014, OBJECT_DIRECTION_DOWN);
			Event_Queue_PlayMusic(MUS_outside);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_WalkTo(0, 2152, 1040, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(2706);
			Event_Queue_Object_Destroy(71);
			Event_Queue_Object_Destroy(72);
			Event_Queue_Dialog_Run(2707);
			Event_Queue_Object_WalkTo(0, 2152, 1064, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2708);
			Event_Queue_Dialog_Run(2709);
			Event_Queue_Dialog_Run(2710);
			Event_Queue_Dialog_Run(2711);
			Event_Queue_Object_WalkTo(0, 2152, 1040, 1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
			Event_Queue_WaitFrames(12);
			Event_Queue_PlaySound(SND_hit1);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Object_JumpToRelative(70, 0, -8, OBJECT_DIRECTION_DOWN, 8, 12);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
			Event_Queue_Dialog_Run(2712);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_GotoArea(5, 600, 1296, -1);
			Event_Queue_StopMusic();
			
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 504, 1296, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 504, 1352, 2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 536, 1312, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_SetSync(false);
			Event_Queue_Camera_TeleportTo(528, 1296);
			Event_Queue_WaitFrames(60);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_Dialog_Run(2713);
			Event_Queue_WaitFrames(27);
			Event_Queue_Object_WalkTo(0, 496, 1296, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(49);
			Event_Queue_Object_ChangeSpriteId(10, SPR_misc_lisao_sleepawake);
			Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeSpriteId(10, SPR_misc_lisao_sit);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_TeleportTo(10, 468, 1290);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(2714);
			Event_Queue_Dialog_Run(2715);
			Event_Queue_Dialog_Run(2716);
			Event_Queue_Dialog_Run(2717);
			Event_Queue_Dialog_Run(2718);
			Event_Queue_Dialog_Run(2719);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(12);
			Event_Queue_PlaySound(SND_menu2);
			Event_Queue_CreateObject(11, 1, SPR_misc_gregoryscythe, 492, 1234, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(12, 1, SPR_misc_gregorygun, 510, 1262, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(30);
			Event_Queue_Object_WalkTo(0, 520, 1296, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2720);
			Event_Queue_Dialog_Run(2721);
			Event_Queue_Dialog_Run(2722);
			Event_Queue_Dialog_Run(2723);
			Event_Queue_Dialog_Run(2724);
			Event_Queue_Dialog_Run(2725);
			Event_Queue_Dialog_Run(2726);
			Event_Queue_Dialog_Run(2727);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_lisao);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_JumpTo(10, 488, 1296, OBJECT_DIRECTION_RIGHT, 8, 16);
			Event_Queue_Dialog_Run(2728);
			Event_Queue_Dialog_Run(2729);
			Event_Queue_Object_ChangeSpriteId(10, SPR_misc_lisao_happy);
			Event_Queue_Dialog_Run(2730);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_lisao);
			Event_Queue_Object_WalkTo(10, 520, 1312, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(15);
			Event_Queue_Object_JumpTo(10, 528, 1312.125, OBJECT_DIRECTION_RIGHT, 0, 8);
			Event_Queue_Object_ChangeSpriteId(10, SPR_misc_lisao_hug);
			Event_Queue_Object_ChangeSpriteFrame(10, 0);
			Event_Queue_WaitFrames(35);
			Event_Queue_Object_ChangeSpriteFrame(10, 1);
			Event_Queue_WaitFrames(25);
			Event_Queue_Object_ChangeSpriteFrame(10, 0);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_lisao);
			Event_Queue_Object_JumpTo(10, 520, 1312, OBJECT_DIRECTION_RIGHT, 0, 8);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2731);
			Event_Queue_Object_WalkTo(10, 488, 1296, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(2732);
			Event_Queue_Dialog_Run(2733);
			Event_Queue_Object_ChangeSpriteId(10, SPR_misc_lisao_happy);
			Event_Queue_Dialog_Run(2734);
			Event_Queue_Dialog_Run(2735);
			Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_lisao);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2736);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			if (Profile_KeyItemExists(177)) {
				Event_Queue_Dialog_Run(2737);
				Event_Queue_Profile_KeyItemRemove(177);
				Event_Queue_Dialog_Run(2738);
				Event_Queue_Dialog_Run(2739);
			}
			
			Event_Queue_Regroup(1);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
			Event_Queue_PlayMusic(MUS_casual);
			Event_Queue_SetFlag(FLAG_GREGORY_OPTIONALFIGHT, 1);
			Event_Queue_SetFlag(FLAG_FOREST_FORK_PROGRESS, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 120: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_CreateObject(9, 106, SPR_misc_gregoryguide, player->x, player->y + 136, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetFloatPtr(&overworld.objects[9].vars[0].f, 0);
			Event_Queue_SetFloatPtr(&overworld.objects[9].vars[1].f, 80);
			Event_Queue_SetIntPtr(&overworld.objects[9].vars[2].i, 0);
			Event_Queue_Label(1);
			Event_Queue_WaitFrames(1);
			Event_Queue_CompareIntToConst(&overworld.objects[9].type, 0);
			Event_Queue_JumpIfGreater(1);
			
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 121: {
			SDL_Delay(335);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(4800, 2320, 225);
			Event_Queue_Dialog_Run(10);
			Event_Queue_PlaySound(SND_boost);
			Event_Queue_PlaySound(SND_shards);
			Event_Queue_PlaySound(SND_menu1);
			Event_Queue_WaitFrames(27);
			Event_Queue_StopMusic();
			Event_Queue_EngageBattle(106, 0);
			Event_Queue_SetSync(false);
			Event_Queue_SetIntPtr(0, 0);
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		
		
		
		
		
		case 1000000: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(0);
			Event_Queue_Object_WalkToRelative(10, 0, 64, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkToRelative(10, -64, 0, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1);
			Event_Queue_Object_WalkToRelative(10, 64, -64, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000001: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3);
			
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_Dialog_Run(4);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
				Event_Queue_CompareIntToConst(&partyMembers[0].armorId, 18);
				Event_Queue_JumpIfEqual(2);
				
				Event_Queue_Dialog_Run(5);
				Event_Queue_EngageBattle(10, -1);
				Event_Queue_Jump(0);
			
			Event_Queue_Label(2);
				Event_Queue_Dialog_Run(6);
			
			Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000002: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(102);
			if (profile.flags[FLAG_PLOT] == 11) {
				if (!profile.flags[FLAG_NOAH_JOINED] && profile.flags[FLAG_EMMET_JOINED]) {
					Event_Queue_Dialog_Run(93);
				}
				else {
					Event_Queue_Dialog_Run(90);
					Event_Queue_Dialog_Run(91);
					Event_Queue_Dialog_Run(92);
					Event_Queue_EngageBattle(7, 22);
					Event_Queue_Object_Destroy(22);
					Event_Queue_Object_Destroy(23);
					Event_Queue_Object_Destroy(24);
					Event_Queue_SetFlag(FLAG_PLOT, 12);
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000003: {
			if (overworld.areaId == 80) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2327);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
					Event_Queue_GotoArea(150, 22648, 3656, SPR_tileset_day);
					Event_Queue_Jump(1);
				
				Event_Queue_Label(1);
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (overworld.areaId == 6) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2004);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
					Event_Queue_GotoArea(80, 22504, 8984, SPR_tileset_day);
					Event_Queue_Jump(1);
				
				Event_Queue_Label(1);
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2000);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
					Event_Queue_GotoArea(6, 13320, 7672, SPR_tileset_day);
					Event_Queue_Jump(1);
				
				Event_Queue_Label(1);
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000004: {
			if (overworld.player.y - 8 <= caller->y) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2072);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_PLOT] <= 53 && !profile.flags[FLAG_ALONE]) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Dialog_Run(261);
				Event_Queue_Dialog_Run(262);
				Event_Queue_Dialog_Run(263);
				Event_Queue_SetVarInt(0, 0);
				Event_Queue_CompareIntToConst(&profile.cash, 9);
				Event_Queue_JumpIfLess(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(2);
					Event_Queue_AddCash(-9);
					Event_Queue_SetVarInt(0, 1);
					Event_Queue_Dialog_Run(264);
					Event_Queue_Profile_ItemAdd(10);
					Event_Queue_Profile_ItemAdd(10);
					Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
					Event_Queue_Dialog_Run(265);
					Event_Queue_Dialog_Run(266);
					Event_Queue_Dialog_Run(267);
					Event_Queue_Profile_ItemAdd(9);
					Event_Queue_Profile_ItemAdd(9);
					Event_Queue_Jump(0);
				
				Event_Queue_Label(2);
					Event_Queue_Dialog_Run(268);
					Event_Queue_Dialog_Run(269);
					Event_Queue_Dialog_Run(267);
					Event_Queue_Profile_ItemAdd(9);
					Event_Queue_Profile_ItemAdd(9);
				
				Event_Queue_Label(0);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(10000, 8288, 1);
				Event_Queue_Object_WalkTo(0, 10152, 8328, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(1, 10168, 8328, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(2, 10184, 8328, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Object_ToggleGhost(0, true);
				Event_Queue_Object_ToggleGhost(1, true);
				Event_Queue_Object_ToggleGhost(2, true);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 9968, 8328, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(1, 10032, 8328, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(2, 10032, 8328, 1, OBJECT_DIRECTION_UP);
				
				Event_Queue_Object_QueueWalkTo(0, 9964, 8302, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_QueueWalkTo(1, 10004, 8286, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_QueueWalkTo(2, 10032, 8272, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_QueueWalkTo(2, 9976, 8272, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(10);
				Event_Queue_CreateObject(71, 1, SPR_misc_bar_glass, 9976, 8290, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(72, 1, SPR_misc_bar_glass, 9978, 8280, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(73, 1, SPR_misc_bar_glass, 9992, 8284, OBJECT_DIRECTION_DOWN);
				Event_Queue_CompareIntToConst(&eventSystem.vars[0].i, 1);
				Event_Queue_JumpIfEqual(10);
					Event_Queue_Object_ChangeSpriteFrame(71, 2);
					Event_Queue_Object_ChangeSpriteFrame(72, 2);
					Event_Queue_Object_ChangeSpriteFrame(73, 2);
					Event_Queue_Jump(10);
				
				Event_Queue_Label(10);
				Event_Queue_WaitFrames(90);
				Event_Queue_Dialog_Run(270);
				Event_Queue_Dialog_Run(271);
				Event_Queue_Dialog_Run(272);
				Event_Queue_Dialog_Run(273);
				Event_Queue_Dialog_Run(274);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(275);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_TeleportTo(73, 9995, 8288);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_TeleportTo(73, 9999, 8294);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_TeleportTo(73, 10001, 8298);
				
				Event_Queue_CompareIntToConst(&eventSystem.vars[0].i, 1);
				Event_Queue_JumpIfEqual(11);
					Event_Queue_Object_ChangeSpriteFrame(73, 3);
					Event_Queue_Jump(12);
				Event_Queue_Label(11);
					Event_Queue_Object_ChangeSpriteFrame(73, 1);
				Event_Queue_Label(12);
				Event_Queue_PlaySound(SND_burn);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(276);
				
				Event_Queue_Object_WalkTo(11, 10344, 8168, 3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(11, 10056, 8328, 3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(277);
				Event_Queue_CreateObject(70, 1, SPR_owchar_jackie, 10304, 8248, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(70, 10056, 8248, 3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(70, 10056, 8288, 3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_TeleportTo(10, 10232, 8152);
				Event_Queue_Object_WalkTo(10, 10056, 8248, 3, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(278);
				Event_Queue_Object_ChangeSpriteId(2, SPR_misc_emmet_facepalm);
				Event_Queue_Dialog_Run(279);
				Event_Queue_Dialog_Run(280);
				Event_Queue_Dialog_Run(281);
				Event_Queue_Dialog_Run(282);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(283);
				Event_Queue_Dialog_Run(284);
				Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
				Event_Queue_Dialog_Run(285);
				
				Event_Queue_Object_DisableFighterSprite(70);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_electra);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(10, 24, 24, FIGHTER_STATE_IDLE);
				Event_Queue_Object_EnableFighterSprite(11, 25, 25, FIGHTER_STATE_IDLE);
				Event_Queue_PlaySound(SND_mana);
				Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(286);
				Event_Queue_EngageBattle(20, 70);
				
				Event_Queue_Object_TeleportTo(0, 10008, 8312);
				Event_Queue_Object_TeleportTo(2, 9988, 8260);
				
				Event_Queue_Object_Destroy(71);
				Event_Queue_Object_Destroy(72);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_DisableFighterSprite(10);
				Event_Queue_Object_DisableFighterSprite(11);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(287);
				Event_Queue_Dialog_Run(288);
				Event_Queue_Dialog_Run(289);
				Event_Queue_Dialog_Run(290);
				Event_Queue_Object_WalkTo(70, 10034, 8312, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_SPECIAL1);
				Event_Queue_Dialog_Run(293);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
				Event_Queue_Dialog_Run(294);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(295);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Dialog_Run(296);
				Event_Queue_Dialog_Run(291);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(292);
				Event_Queue_Object_DisableFighterSprite(70);
				
				Event_Queue_Object_Destroy(71);
				Event_Queue_Object_Destroy(73);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(70, 10056, 8096, 2, -1);
				Event_Queue_Object_WalkTo(10, 10304, 8248, 2, -1);
				Event_Queue_Object_WalkTo(11, 10304, 8328, 2, -1);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				Event_Queue_CreateNPC(10, 4, 10232, 8128, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateNPC(11, 5, 10512, 8144, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(297);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(0, 10048, 8328, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(1, 10032, 8288, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(2, 10032, 8272, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_Object_ToggleGhost(0, false);
				Event_Queue_Object_ToggleGhost(1, false);
				Event_Queue_Object_ToggleGhost(2, false);
				
				Event_Queue_Regroup(1);
				Event_Queue_SetFlag(FLAG_PLOT, 54);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2001);
				Event_Queue_OpenShopMenu(6);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000005: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2003);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000006: {
			if (profile.flags[FLAG_SILVERBLOCK_PUSHED] == 1) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(171);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Camera_MoveTo(7568, 3520, 1);
				Event_Queue_Dialog_Run(170);
				Event_Queue_Object_WalkTo(0, 7552, 3532, 1, OBJECT_DIRECTION_RIGHT);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(17, 7624, 3536, 0.25, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(0, 7608, 3532, 0.25, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_LEFT);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(10);
				
				Event_Queue_Dialog_Run(140);
				Event_Queue_Object_WalkTo(18, 7664, 3480, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(18, 7632, 3480, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(18, 7584, 3528, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(0, 7536, 3528, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(1, 7512, 3528, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(2, 7488, 3528, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Camera_MoveTo(7536, 3520, 1);
				Event_Queue_SetSync(false);
				Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_RIGHT);
				Event_Queue_StopMusic();
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(141);
				Event_Queue_WaitFrames(30);
				Event_Queue_PlayMusic(MUS_lu);
				Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(142);
				Event_Queue_Dialog_Run(143);
				Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(144);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(145);
				Event_Queue_Dialog_Run(146);
				Event_Queue_Object_EnableFighterSprite(18, 16, 15, FIGHTER_STATE_IDLE);
				Event_Queue_Dialog_Run(147);
				Event_Queue_Object_EnableFighterSprite(18, 16, 15, FIGHTER_STATE_ATTACK1);
				Event_Queue_WaitFrames(10);
				Event_Queue_Dialog_Run(148);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(149);
				
				Event_Queue_EngageBattle(9, 18);
				Event_Queue_Object_EnableFighterSprite(18, 16, 15, FIGHTER_STATE_HURT);
				
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(150);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_DisableFighterSprite(18);
				if (profile.flags[FLAG_ALONE])
					Event_Queue_Dialog_Run(152);
				else
					Event_Queue_Dialog_Run(151);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(18, 7632, 3480, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_QueueWalkTo(18, 7664, 3480, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_QueueWalkTo(18, 7840, 3632, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_WalkTo(17, 7632, 3480, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_QueueWalkTo(17, 7664, 3480, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_QueueWalkTo(17, 7840, 3632, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(18);
				Event_Queue_Object_Destroy(17);
				Event_Queue_PlayMusic(MUS_field);
				
				Event_Queue_Regroup(2);
				Event_Queue_SetFlag(FLAG_SILVERBLOCK_PUSHED, 1);
				Event_Queue_SetFlag(FLAG_PLOT, 10);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000007: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(160);
			Event_Queue_Dialog_Run(161);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(162);
			Event_Queue_Dialog_Run(163);
			Event_Queue_Dialog_Run(164);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Party_Join(1);
			Event_Queue_Profile_InventoryPartyOrderAdd(1);
			Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[10].x, &overworld.objects[10].y);
			Event_Queue_Dialog_Run(3001);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			
			Event_Queue_Regroup(1);
			if (profile.flags[FLAG_EMMET_JOINED]) {
				Event_Queue_Party_Leave(2);
				Event_Queue_Profile_InventoryPartyOrderRemove(2);
				Event_Queue_Party_Join(2);
				Event_Queue_Profile_InventoryPartyOrderAdd(2);
				Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.caterpillar[32].x, &overworld.caterpillar[32].y);
				Event_Queue_Object_TeleportToPointer(2, 0, 0, &overworld.caterpillar[16].x, &overworld.caterpillar[16].y);
				Event_Queue_Regroup(1);
			}
			Event_Queue_SetFlag(FLAG_NOAH_JOINED, 1);
			Event_Queue_SetFlag(FLAG_ALONE, 0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000008: {
			if (profile.flags[FLAG_GREGORY_OPTIONALFIGHT]) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2740);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_UP);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2002);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000010: {
			if (profile.flags[FLAG_PLOT] <= 54 && overworld.areaId == 6) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(315);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				Event_Queue_Exit();
				
				Event_Queue_Label(1);
				Event_Queue_Dialog_Run(316);
				Event_Queue_Dialog_Run(317);
				Event_Queue_Camera_TogglePlayerFollow(true);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_QueueWalkTo(18, 16488, 8392, 3, -1);
				Event_Queue_Object_QueueWalkTo(18, 16488, 7912, 3, -1);
				Event_Queue_Object_QueueWalkTo(18, 16048, 7912, 3, -1);
				Event_Queue_Object_QueueWalkTo(18, 16048, 7760, 3, -1);
				Event_Queue_Object_QueueWalkTo(18, 16392, 7760, 3, -1);
				Event_Queue_Object_QueueWalkTo(18, 16392, 7688, 3, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_WaitFrames(17);
				Event_Queue_Object_QueueWalkTo(0, 16488, 8392, 3, -1);
				Event_Queue_Object_QueueWalkTo(0, 16488, 7912, 3, -1);
				Event_Queue_Object_QueueWalkTo(0, 16048, 7912, 3, -1);
				Event_Queue_Object_QueueWalkTo(0, 16048, 7760, 3, -1);
				Event_Queue_Object_QueueWalkTo(0, 16424, 7760, 3, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				
				Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(40);
				Event_Queue_Object_Destroy(18);
				Event_Queue_WaitFrames(5);
				Event_Queue_Object_WalkTo(0, 16392, 7688, 2, OBJECT_DIRECTION_UP);
				Event_Queue_GotoArea(9, 9608, 8432, -1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				
				Event_Queue_Camera_TogglePlayerFollow(false);
				Event_Queue_Dialog_Run(308);
				Event_Queue_Dialog_Run(309);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveToRelative(0, -96, 2);
				Event_Queue_Object_QueueWalkTo(70, 9608, 8256, 2, -1);
				Event_Queue_Object_QueueWalkTo(70, 9752, 8256, 2, -1);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				
				Event_Queue_Regroup(1);
				Event_Queue_RemoveCurrentTrigger();
				Event_Queue_SetFlag(FLAG_PLOT, 55);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_PLOT] <= 55) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(310);
				Event_Queue_Dialog_Run(311);
				Event_Queue_Dialog_Run(312);
				if (profile.flags[FLAG_ALONE]) {
					Event_Queue_Dialog_Run(318);
					Event_Queue_Dialog_Run(319);
					Event_Queue_Object_Destroy(10);
					Event_Queue_Party_Join(6);
					Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				}
				else {
					Event_Queue_Dialog_Run(313);
					Event_Queue_Dialog_Run(314);
					Event_Queue_Object_Destroy(10);
					Event_Queue_Party_Join(6);
					Event_Queue_Object_TeleportToPointer(3, 0, 0, &overworld.objects[10].x, &overworld.objects[10].y);
				}
				
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(3006);
				Event_Queue_SetFlag(FLAG_PLOT, 56);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(698);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000011: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Profile_KeyItemAdd(161);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_Player_SetPositionSync(true);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Object_WalkToPointer(3, -32, 0, 1, OBJECT_DIRECTION_RIGHT, &overworld.objects[0].x, &overworld.objects[0].y);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(650);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_Label(0);
				Event_Queue_Profile_KeyItemRemove(161);
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(651);
				Event_Queue_SetFlag(FLAG_PLOT, 57);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				Event_Queue_Exit();
				
				Event_Queue_Label(1);
				Event_Queue_Dialog_Run(652);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_Dialog_Run(653);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_Dialog_Run(654);
				Event_Queue_Dialog_Run(655);
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(656);
				Event_Queue_Profile_KeyItemRemove(161);
				Event_Queue_Profile_KeyItemAdd(170);
				Event_Queue_Dialog_Run(4004);
				Event_Queue_Dialog_Run(657);
				Event_Queue_SetFlag(FLAG_ALONE_PLOT, 1);
			}
			else {
				Event_Queue_Dialog_Run(320);
				Event_Queue_Object_WalkToPointer(3, -32, 0, 1, OBJECT_DIRECTION_RIGHT, &overworld.objects[0].x, &overworld.objects[0].y);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(321);
				Event_Queue_Profile_KeyItemRemove(161);
				Event_Queue_Regroup(1);
				Event_Queue_Dialog_Run(322);
			}
			Event_Queue_SetFlag(FLAG_PLOT, 57);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000012: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_JOHNNY_DIALOG]) {
				if (!profile.flags[FLAG_JOHNNY_DANDELION] && !Profile_ItemInventoryIsFull()) {
					Event_Queue_Profile_ItemAdd(27);
					Event_Queue_Dialog_Run(4004);
					Event_Queue_SetFlag(FLAG_JOHNNY_DANDELION, 1);
				}
				Event_Queue_Dialog_Run(2313);
			}
			else {
				Event_Queue_Dialog_Run(2312);
				if (Profile_ItemInventoryIsFull()) {
					Event_Queue_Dialog_Run(2314);
				}
				else {
					Event_Queue_Profile_ItemAdd(27);
					Event_Queue_Dialog_Run(4004);
					Event_Queue_SetFlag(FLAG_JOHNNY_DANDELION, 1);
				}
				Event_Queue_SetFlag(FLAG_JOHNNY_DIALOG, 1);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000013: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (caller->direction != OBJECT_DIRECTION_DOWN) {
				Event_Queue_Dialog_Run(2009);
			}
			else {
				Event_Queue_Dialog_Run(2006);
				Event_Queue_OpenShopMenu(1);
				Event_Queue_CompareIntToConst(&profile.cash, profile.cash);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_Dialog_Run(2007);
				Event_Queue_Label(0);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000014: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_COPPERS_REWARD]) {
				Event_Queue_Dialog_Run(2059);
			}
			else if (profile.flags[FLAG_PLOT] >= 14) {
				Event_Queue_Dialog_Run(2055);
				Event_Queue_AddCash(300);
				Event_Queue_Dialog_Run(2056);
				if (profile.flags[FLAG_EMMET_JOINED]) {
					Event_Queue_Dialog_Run(2057);
					Event_Queue_Dialog_Run(2058);
				}
				Event_Queue_SetFlag(FLAG_COPPERS_REWARD, 1);
			}
			else {
				Event_Queue_Dialog_Run(2054);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000015: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(2);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000016: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(3);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000017: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(4);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000018: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2011);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000019: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] >= 14) {
				Event_Queue_Dialog_Run(2013);
			}
			else {
				Event_Queue_Dialog_Run(2012);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000020: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2014);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000021: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2015);
			Event_Queue_WaitFrames(90);
			Event_Queue_Dialog_Run(2016);
			Event_Queue_EngageBattle(6, eventSystem.callerObjectId);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_SetFlag(FLAG_LEAFCREW_OPTIONALFIGHT, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000022: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (!profile.flags[FLAG_LEAFCREW_SHOP_DIALOG]) {
				Event_Queue_Dialog_Run(2017);
				Event_Queue_Dialog_Run(2018);
				Event_Queue_WaitFrames(60);
				Event_Queue_SetFlag(FLAG_LEAFCREW_SHOP_DIALOG, 1);
			}
			Event_Queue_Dialog_Run(2019);
			Event_Queue_OpenShopMenu(5);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000023: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_UP);
			if (profile.flags[FLAG_KEVIN_DIALOG] == 0) {
				Event_Queue_Dialog_Run(460);
				Event_Queue_Dialog_Run(461);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(462);
				Event_Queue_SetFlag(FLAG_KEVIN_DIALOG, 1);
			}
			Event_Queue_Dialog_Run(463);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000024: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2020);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000025: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] >= 500) {
				Event_Queue_Dialog_Run(2027);
			}
			else if (profile.flags[FLAG_PLOT] <= 16) {
				Event_Queue_Dialog_Run(2027);
				Event_Queue_Dialog_Run(2028);
			}
			else if (!profile.flags[FLAG_PURCHASED_BUS_TICKET]) {
				if (!profile.flags[FLAG_NOAH_JOINED] || !profile.flags[FLAG_EMMET_JOINED]) {
					if (profile.flags[FLAG_CANTGOALONE_WARNING] == 0 || !profile.flags[FLAG_ALONE]) {
						Event_Queue_Dialog_Run(2116);
						Event_Queue_Dialog_Run(2117);
						Event_Queue_SetFlag(FLAG_CANTGOALONE_WARNING, 1);
					}
					else {
						Event_Queue_Dialog_Run(2021);
						Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
						Event_Queue_JumpIfEqual(1);
							Event_Queue_Dialog_Run(2022);
							Event_Queue_Jump(0);
						Event_Queue_Label(2);
							Event_Queue_Dialog_Run(2025);
							Event_Queue_Jump(0);
						
						Event_Queue_Label(1);
						Event_Queue_CompareIntToConst(&profile.cash, 30);
						Event_Queue_JumpIfLess(2);
						Event_Queue_Dialog_Run(2118);
						Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
						Event_Queue_JumpIfEqual(0);
						Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 6824, 7032, 1, OBJECT_DIRECTION_DOWN);
						Event_Queue_AddCash(-30);
						Event_Queue_SetFlag(FLAG_PURCHASED_BUS_TICKET, 1);
						Event_Queue_CreateTrigger(0, 6736, 7152, 6784, 7168, 24);
					}
				}
				else {
					Event_Queue_Dialog_Run(2021);
					Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
					Event_Queue_JumpIfEqual(1);
						Event_Queue_Dialog_Run(2022);
						Event_Queue_Jump(0);
					Event_Queue_Label(2);
						Event_Queue_Dialog_Run(2025);
						Event_Queue_Jump(0);
					
					Event_Queue_Label(1);
					Event_Queue_CompareIntToConst(&profile.cash, 90);
					Event_Queue_JumpIfLess(2);
					Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 6824, 7032, 1, OBJECT_DIRECTION_DOWN);
					Event_Queue_AddCash(-90);
					Event_Queue_SetFlag(FLAG_PURCHASED_BUS_TICKET, 1);
					Event_Queue_CreateTrigger(0, 6736, 7152, 6784, 7168, 24);
				}
			}
			else {
				Event_Queue_Dialog_Run(2023);
			}
			Event_Queue_Label(0);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000026: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2024);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000027: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_ALONE_PLOT] >= 20) {
				Event_Queue_Dialog_Run(2253);
			}
			else {
				if (!profile.flags[FLAG_MANSION_DIA_GIFT] && !Profile_ItemInventoryIsFull()) {
					Event_Queue_Dialog_Run(2126);
					Event_Queue_Profile_ItemAdd(17);
					Event_Queue_Dialog_Run(4004);
					Event_Queue_SetFlag(FLAG_MANSION_DIA_GIFT, 1);
				}
				Event_Queue_Dialog_Run(2125);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(0);
				
				Event_Queue_CreateNPC(12, 10013, 7494, 7296, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_CreateNPC(31, 10014, 7512, 7296, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateNPC(32, 10014, 7528, 7296, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateNPC(33, 10014, 7544, 7296, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateNPC(34, 10014, 7560, 7296, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_CreateObject(41, 1, SPR_misc_flowergame, 7512, 7280, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(42, 1, SPR_misc_flowergame, 7528, 7280, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(43, 1, SPR_misc_flowergame, 7544, 7280, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(44, 1, SPR_misc_flowergame, 7560, 7280, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_Object_ChangeSpriteFrame(41, Random_IRange(0, 4));
				Event_Queue_Object_ChangeSpriteFrame(42, Random_IRange(0, 4));
				Event_Queue_Object_ChangeSpriteFrame(43, Random_IRange(0, 4));
				Event_Queue_Object_ChangeSpriteFrame(44, Random_IRange(0, 4));
				
				Event_Queue_SetIntPtrToPtr(&profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_1], &overworld.objects[41].spriteFrame);
				Event_Queue_SetIntPtrToPtr(&profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_2], &overworld.objects[42].spriteFrame);
				Event_Queue_SetIntPtrToPtr(&profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_3], &overworld.objects[43].spriteFrame);
				Event_Queue_SetIntPtrToPtr(&profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_4], &overworld.objects[44].spriteFrame);
				
				Event_Queue_Label(0);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000028: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2053);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000029: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(7);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000030: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(8);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000031: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(9);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000032: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2061);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_LEFT);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000033: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2060);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000034: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2062);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000035: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2063);
			Event_Queue_EngageBattle(18, eventSystem.callerObjectId);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_SetFlag(FLAG_VANDAL_OPTIONALFIGHT, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000036: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 80) {
				if (profile.flags[FLAG_AYAKA_SHOP] == 1) {
					Event_Queue_Dialog_Run(2291);
					Event_Queue_SetFlag(FLAG_AYAKA_SHOP, 2);
				}
				else {
					Event_Queue_Dialog_Run(2290);
				}
				Event_Queue_OpenShopMenu(19);
				Event_Queue_CompareIntToConst(&profile.cash, profile.cash);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_SetFlag(FLAG_AYAKA_SHOP, 3);
				Event_Queue_Dialog_Run(2065);
			}
			else {
				Event_Queue_Dialog_Run(2064);
				Event_Queue_OpenShopMenu(10);
				Event_Queue_CompareIntToConst(&profile.cash, profile.cash);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_SetFlag(FLAG_AYAKA_SHOP, 1);
				if (profile.flags[FLAG_AYAKA_SHOP] >= 1)
					Event_Queue_Dialog_Run(2065);
				else
					Event_Queue_Dialog_Run(2289);
			}
			Event_Queue_Label(0);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000037: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2066);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000038: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2067);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_UP);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000039: {
			if (profile.flags[FLAG_RCCLUB_PLOT] == 105 && !profile.flags[FLAG_ALONE]) {
				Event_Trigger(34);
			}
		} break;
		
		case 1000040: {
			if (profile.flags[FLAG_RCCLUB_PLOT] == 105 && !profile.flags[FLAG_ALONE]) {
				Event_Trigger(34);
			}
		} break;
		
		case 1000041: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_EngageBattle(37, 10);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(166);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 107);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000042: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2140);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000043: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] == 6) {
				Event_Queue_Dialog_Run(2143);
			}
			else if (profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] == 5) {
				Event_Queue_Dialog_Run(2139);
			}
			else if (profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] == 4) {
				Event_Queue_Dialog_Run(2138);
			}
			else {
				if (profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] == 0)
					Event_Queue_Dialog_Run(2127);
				else
					Event_Queue_Dialog_Run(2135);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
					Event_Queue_Dialog_Run(2128);
					Event_Queue_Jump(0);
				Event_Queue_Label(2);
					Event_Queue_Dialog_Run(2137);
					Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_CompareIntToConst(&profile.cash, 50);
				Event_Queue_JumpIfLess(2);
				if (profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] == 0)
					Event_Queue_Dialog_Run(2129);
				else
					Event_Queue_Dialog_Run(2136);
				Event_Queue_AddCash(-50);
				
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_Object_TeleportTo(0, 19272, 10568);
				Event_Queue_Object_TeleportTo(11, 19304, 10568);
				Event_Queue_Object_TeleportTo(1, 19320, 10616);
				Event_Queue_Object_TeleportTo(2, 19288, 10616);
				Event_Queue_Object_TeleportTo(3, 19256, 10616);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				if (profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] == 3 && partyMembers[0].base.attack < 24 && !profile.flags[FLAG_ALONE]) {
					Event_Queue_Object_ChangeSpriteId(2, SPR_misc_emmet_facepalm);
				}
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(2130);
				Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_ATTACK1);
				Event_Queue_Object_EnableFighterSprite(11, 48, 53, FIGHTER_STATE_ATTACK1);
				Event_Queue_WaitFrames(30);
				Event_Queue_PlaySound(SND_hit1);
				Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_ATTACK2);
				Event_Queue_Object_EnableFighterSprite(11, 48, 53, FIGHTER_STATE_ATTACK2);
				if (partyMembers[0].base.attack >= 29) {
					Event_Queue_WaitFrames(68);
					Event_Queue_Dialog_Run(2133);
					Event_Queue_PlaySound(SND_hit3);
					Event_Queue_Object_EnableFighterSprite(11, 48, 53, FIGHTER_STATE_HURT);
					Event_Queue_Object_JumpTo(11, 19320, 10568, -1, 0, 6);
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(2134);
					Event_Queue_SetFlag(FLAG_RCCLUB_BROOK_GAME_PLAYS, 5);
				}
				else if (partyMembers[0].base.attack >= 24) {
					Event_Queue_WaitFrames(95);
					Event_Queue_Dialog_Run(2132);
					Event_Queue_SetFlag(FLAG_RCCLUB_BROOK_GAME_PLAYS, 6);
				}
				else {
					Event_Queue_WaitFrames(68);
					Event_Queue_PlaySound(SND_hit3);
					Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_HURT);
					Event_Queue_Object_JumpTo(0, 19256, 10568, -1, 0, 6);
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(2131);
					Event_Queue_SetFlag(FLAG_RCCLUB_BROOK_GAME_PLAYS, profile.flags[FLAG_RCCLUB_BROOK_GAME_PLAYS] + 1);
				}
				
				Event_Queue_Label(3);
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_DisableFighterSprite(11);
				for (int i = 0; i <= 11; i++) {
					Event_Queue_Object_TeleportTo(i, overworld.objects[i].x, overworld.objects[i].y);
					Event_Queue_Object_ChangeDirection(i, overworld.objects[i].direction);
				}
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				if (partyMembers[0].base.attack >= 29) {
					Event_Queue_AddCash(100);
					Event_Queue_Dialog_Run(2141);
				}
				else if (partyMembers[0].base.attack >= 24) {
					Event_Queue_AddCash(50);
					Event_Queue_Dialog_Run(2142);
				}
				
				Event_Queue_Label(0);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000044: {
			bool fight = !profile.flags[FLAG_RCCLUB_CINDY_DEFEATED];
			for (int i = 0; i < 5; i++) {
				if (profile.party[i] < 0) break;
				PartyMember* partyMember = &partyMembers[profile.party[i]];
				if (partyMember->hpMax - partyMember->hpDamage > 40) {
					fight = false;
					break;
				}
			}
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (fight) {
				Event_Queue_Dialog_Run(2077);
				Event_Queue_Object_ChangeSpriteId(10, SPR_misc_cindy_laugh);
				Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0.125);
				Event_Queue_Dialog_Run(2078);
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(2079);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_cindy);
				Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				if (profile.flags[FLAG_ALONE]) {
					Event_Queue_Object_WalkTo(10, 20144, 10592, 1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_WalkTo(10, 20144, 10624, 1, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeSpriteId(10, SPR_misc_cindy_laugh);
					Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0.125);
					Event_Queue_Dialog_Run(2270);
				}
				else {
					Event_Queue_Dialog_Run(2080);
					Event_Queue_Dialog_Run(2081);
					Event_Queue_Object_WalkTo(10, 20144, 10592, 1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_WalkTo(10, 20144, 10624, 1, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeSpriteId(10, SPR_misc_cindy_laugh);
					Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0.125);
					Event_Queue_Dialog_Run(2082);
				}
				Event_Queue_EngageBattle(58, 10);
				
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_cindy);
				Event_Queue_Object_ChangeSpriteFrameSpeed(10, 0);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Camera_TeleportTo(20104, 10648);
				Event_Queue_Object_TeleportTo(0, 20072, 10664);
				Event_Queue_Object_TeleportTo(1, 20040, 10632);
				Event_Queue_Object_TeleportTo(2, 20040, 10696);
				Event_Queue_Object_TeleportTo(3, 20008, 10664);
				Event_Queue_Object_TeleportTo(10, 20120, 10664);
				Event_Queue_Object_EnableFighterSprite(0, 1, 1, FIGHTER_STATE_IDLE);
				if (!profile.flags[FLAG_ALONE]) {
					Event_Queue_Object_EnableFighterSprite(1, 2, 3, FIGHTER_STATE_IDLE);
					Event_Queue_Object_EnableFighterSprite(2, 3, 4, FIGHTER_STATE_IDLE);
					Event_Queue_Object_EnableFighterSprite(3, 4, 5, FIGHTER_STATE_IDLE);
				}
				Event_Queue_Object_EnableFighterSprite(10, 50, 55, FIGHTER_STATE_DOWN);
				Event_Queue_WaitFrames(70);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_DisableFighterSprite(1);
				Event_Queue_Object_DisableFighterSprite(2);
				Event_Queue_Object_DisableFighterSprite(3);
				Event_Queue_Dialog_Run(2083);
				Event_Queue_Object_EnableFighterSprite(10, 50, 55, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(2084);
				Event_Queue_Dialog_Run(2085);
				if (profile.flags[FLAG_ALONE]) {
					Event_Queue_Dialog_Run(2271);
					Event_Queue_Object_DisableFighterSprite(10);
				}
				else {
					Event_Queue_Dialog_Run(2086);
					Event_Queue_Dialog_Run(2087);
					Event_Queue_Dialog_Run(2088);
					Event_Queue_Dialog_Run(2089);
					Event_Queue_Object_DisableFighterSprite(10);
					Event_Queue_Dialog_Run(2090);
				}
				Event_Queue_Object_WalkTo(10, 20096, 10664, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_AddCash(500);
				Event_Queue_Dialog_Run(2092);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(10, 20144, 10592, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_QueueWalkTo(10, 20104, 10592, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Regroup(1);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(2091);
				Event_Queue_SetFlag(FLAG_RCCLUB_CINDY_DEFEATED, 1);
			}
			else {
				Event_Queue_Dialog_Run(2076);
				if (profile.flags[FLAG_RCCLUB_CINDY_DEFEATED])
					Event_Queue_OpenShopMenu(13);
				else
					Event_Queue_OpenShopMenu(11);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000045: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] <= 112 || (profile.flags[FLAG_PLOT] >= 114 && profile.flags[FLAG_AZURETOPHOTEL_PLOT] == 0)) {
				Event_Queue_Dialog_Run(2175);
				Event_Queue_Dialog_Run(2176);
			}
			else if (profile.flags[FLAG_PLOT] == 113) {
				Event_Queue_Dialog_Run(2093);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
					Event_Queue_Jump(0);
				Event_Queue_Label(2);
					Event_Queue_Dialog_Run(2099);
					Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_CompareIntToConst(&profile.cash, 160);
				Event_Queue_JumpIfLess(2);
				Event_Queue_AddCash(-160);
				Event_Queue_Dialog_Run(2094);
				Event_Queue_Object_WalkTo(11, 18512, 11696, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2095);
				Event_Queue_Object_WalkTo(11, 18560, 11616, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(11);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetFlag(FLAG_AZURETOPHOTEL_PLOT, 1);
				Event_Queue_SetFlag(FLAG_PLOT, 114);
			}
			else if (profile.flags[FLAG_PLOT] == 114) {
				Event_Queue_Dialog_Run(2094);
			}
			else {
				Event_Queue_Dialog_Run(2177);
			}
			Event_Queue_Label(0);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000046: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(757);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000047: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] == 114) {
				overworld.map.doors[71].enabled = true;
				Event_Queue_Dialog_Run(2096);
				Event_Queue_Dialog_Run(2097);
				Event_Queue_Object_WalkTo(10, 18560, 11280, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(10, 18560, 11248, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(10);
				Event_Queue_SetFlag(FLAG_PLOT, 115);
			}
			else {
				Event_Queue_Dialog_Run(2178);
				Event_Queue_OpenShopMenu(12);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000048: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] < 118 || (profile.flags[FLAG_PLOT] > 118 && profile.flags[FLAG_AZURETOPHOTEL_PLOT] < 2)) {
				Event_Queue_Dialog_Run(2267);
			}
			else if (profile.flags[FLAG_PLOT] == 118) {
				if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(2165);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(2166);
				Event_Queue_Object_WalkTo(11, 17560, 11824, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_Destroy(11);
				Event_Queue_SetFlag(FLAG_PLOT, 119);
				Event_Queue_SetFlag(FLAG_AZURETOPHOTEL_PLOT, 2);
			}
			else if (profile.flags[FLAG_AZURETOPHOTEL_PLOT] == 2) {
				Event_Queue_Dialog_Run(2269);
			}
			else {
				Event_Queue_Dialog_Run(2180);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000052: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] >= 122 && !profile.flags[FLAG_ADIOS_OPTIONALFIGHT]) {
				Event_Queue_Dialog_Run(2317);
			}
			else {
				Event_Queue_Dialog_Run(2316);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000054: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] >= 122 && profile.flags[FLAG_RCCLUB_PLOT] >= 112) {
				Event_Queue_Dialog_Run(2321);
			}
			else {
				Event_Queue_Dialog_Run(2318);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				
				Event_Queue_Dialog_Run(2319);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2320);
				
				Event_Queue_Label(0);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000055: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 103) {
				if (eventSystem.callerObjectId == 10 || eventSystem.callerObjectId == 11) {
					if (profile.flags[FLAG_PLOT] <= 130) {
						Event_Queue_Dialog_Run(800);
						Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
						Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
						Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
						Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
						Event_Queue_Dialog_Run(801);
						if (!profile.flags[FLAG_ALONE]) Event_Queue_Dialog_Run(802);
						Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE]) ? 811 : 803);
						Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
						Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_LEFT);
						Event_Queue_Object_EnableFighterSprite(13, 36, 38, FIGHTER_STATE_RUN);
						Event_Queue_Object_EnableFighterSprite(14, 36, 38, FIGHTER_STATE_RUN);
						Event_Queue_SetSync(true);
						Event_Queue_Object_JumpTo(13, 14040, 10200, OBJECT_DIRECTION_LEFT, 28, 46);
						Event_Queue_Object_JumpTo(14, 13816, 10200, OBJECT_DIRECTION_RIGHT, 28, 46);
						Event_Queue_SetSync(false);
						Event_Queue_Overworld_ShakeScreen(8);
						Event_Queue_Object_EnableFighterSprite(13, 36, 38, FIGHTER_STATE_IDLE);
						Event_Queue_Object_EnableFighterSprite(14, 36, 38, FIGHTER_STATE_IDLE);
						Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
						Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
						Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
						Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
						Event_Queue_Camera_MoveTo(13928, 10184, 2);
						Event_Queue_WaitFrames((profile.flags[FLAG_ALONE]) ? 90 : 60);
						Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE]) ? 812 : 804);
						Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE]) ? 813 : 805);
						Event_Queue_Dialog_Run((profile.flags[FLAG_ALONE]) ? 814 : 806);
						
						Event_Queue_EngageBattle(68, -1);
						Event_Queue_Object_DisableFighterSprite(13);
						Event_Queue_Object_DisableFighterSprite(14);
						
						Event_Queue_WaitFrames(30);
						if (profile.flags[FLAG_ALONE]) {
							Event_Queue_Dialog_Run(815);
							Event_Queue_Dialog_Run(816);
						}
						else {
							Event_Queue_Dialog_Run(807);
							Event_Queue_Dialog_Run(808);
							Event_Queue_Dialog_Run(809);
							Event_Queue_Dialog_Run(810);
						}
						Event_Queue_Object_EnableFighterSprite(13, 36, 38, FIGHTER_STATE_RUN);
						Event_Queue_Object_EnableFighterSprite(14, 36, 38, FIGHTER_STATE_RUN);
						Event_Queue_SetSync(true);
						Event_Queue_Object_JumpTo(13, 13864, 9880, OBJECT_DIRECTION_DOWN, 64, 46);
						Event_Queue_Object_JumpTo(14, 13992, 9880, OBJECT_DIRECTION_DOWN, 64, 46);
						Event_Queue_SetSync(false);
						Event_Queue_Object_DisableFighterSprite(13);
						Event_Queue_Object_DisableFighterSprite(14);
						Event_Queue_Object_WalkTo(10, 13888, 10160, 1, OBJECT_DIRECTION_DOWN);
						Event_Queue_Object_WalkTo(11, 13968, 10160, 1, OBJECT_DIRECTION_DOWN);
						
						Event_Queue_Object_Destroy(12);
						Event_Queue_Regroup(1);
						Event_Queue_SetFlag(FLAG_PLOT, 131);
					}
					else if (eventSystem.callerObjectId == 10) {
						Event_Queue_Dialog_Run(2272);
					}
					else {
						Event_Queue_Dialog_Run(2273);
					}
				}
				else if (eventSystem.callerObjectId == 15) {
					if (profile.flags[FLAG_OZONE_NINJA_HINT]) {
						Event_Queue_Dialog_Run(2209);
					}
					else {
						Event_Queue_Dialog_Run(2208);
						Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
						Event_Queue_JumpIfEqual(0);
						Event_Queue_CompareIntToConst(&profile.cash, 200);
						Event_Queue_JumpIfLess(1);
						Event_Queue_AddCash(-200);
						Event_Queue_SetFlag(FLAG_OZONE_NINJA_HINT, 1);
						Event_Queue_Dialog_Run(2209);
						Event_Queue_Jump(0);
						
						Event_Queue_Label(1);
						Event_Queue_Dialog_Run(2214);
						
						Event_Queue_Label(0);
					}
				}
				else {
					Event_Queue_Dialog_Run(2274);
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000056: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2315);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000057: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_JACKIECAFE_BROKENGLASS]) {
				Event_Queue_Dialog_Run(2325);
			}
			else {
				Event_Queue_Dialog_Run(2324);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000058: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2124);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000059: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(885);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000060: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2215);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000061: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2216);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000062: {
			if (profile.flags[FLAG_RCCLUB_PLOT] >= 112) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2162);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_RCCLUB_PLOT] >= 111) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2161);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2144);
				Event_Queue_CreateObject(70, 1, SPR_owchar_neveah, 20216, 10648, OBJECT_DIRECTION_RIGHT);
				Event_Queue_CreateObject(71, 1, SPR_owchar_kelly, 20188, 10664, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(20440, 10632, 2);
				Event_Queue_Object_WalkTo(0, 20464, 10632, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(1, 20464, 10648, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(2, 20464, 10664, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(3, 20464, 10680, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(70, 20376, 10648, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(71, 20360, 10664, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2145);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(2146);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(2147);
				Event_Queue_Dialog_Run(2148);
				Event_Queue_Dialog_Run(2149);
				Event_Queue_Dialog_Run(2150);
				Event_Queue_Dialog_Run(2151);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2152);
				Event_Queue_Dialog_Run(2153);
				
				Event_Queue_EngageBattle(40, 11);
				Event_Queue_Object_EnableFighterSprite(70, 46, 51, FIGHTER_STATE_HURT);
				Event_Queue_Object_EnableFighterSprite(71, 47, 52, FIGHTER_STATE_HURT);
				
				Event_Queue_Dialog_Run(2158);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Object_DisableFighterSprite(71);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(2159);
				Event_Queue_Object_WalkTo(70, 20216, 10648, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkTo(71, 20216, 10664, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Object_Destroy(71);
				Event_Queue_Dialog_Run(2160);
				Event_Queue_Object_WalkTo(11, 20376, 10616, 2, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_Regroup(2);
				Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 111);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000063: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Label(2);
			Event_Queue_Dialog_Run(2163);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 2);
			Event_Queue_JumpIfEqual(0);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_CustomAction(2);
			Event_Queue_Overworld_FadeOut(16, 0, 0, 0);
			Event_Queue_Jump(2);
			
			Event_Queue_Label(1);
			Event_Queue_Dialog_Run(2164);
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000068: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_AZURETOPHOTEL_PLOT] < 2) {
				Event_Queue_Dialog_Run(2268);
			}
			else {
				Event_Queue_Dialog_Run(2179);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000069: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2183);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000070: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 100) {
				Event_Queue_Dialog_Run(2207);
			}
			else if (eventSystem.callerObjectId == 14 || eventSystem.callerObjectId == 15) {
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2192);
				Event_Queue_Dialog_Run(2193);
				Event_Queue_SaveToVarInt(0, &dialogSystem.optionSelected);
				Event_Queue_Dialog_Run(2194);
				Event_Queue_SaveToVarInt(1, &dialogSystem.optionSelected);
				Event_Queue_Dialog_Run(2195);
				Event_Queue_SaveToVarInt(2, &dialogSystem.optionSelected);
				Event_Queue_Dialog_Run(2196);
				Event_Queue_SaveToVarInt(3, &dialogSystem.optionSelected);
				Event_Queue_Dialog_Run(2197);
				Event_Queue_SaveToVarInt(4, &dialogSystem.optionSelected);
				Event_Queue_Dialog_Run(2198);
				Event_Queue_SaveToVarInt(5, &dialogSystem.optionSelected);
				
				Event_Queue_CompareIntToConst(&eventSystem.vars[0].i, 2);
				Event_Queue_JumpIfNotEqual(1);
				Event_Queue_CompareIntToConst(&eventSystem.vars[1].i, 0);
				Event_Queue_JumpIfNotEqual(1);
				Event_Queue_CompareIntToConst(&eventSystem.vars[2].i, 5);
				Event_Queue_JumpIfNotEqual(1);
				Event_Queue_CompareIntToConst(&eventSystem.vars[3].i, 4);
				Event_Queue_JumpIfNotEqual(1);
				Event_Queue_CompareIntToConst(&eventSystem.vars[4].i, 2);
				Event_Queue_JumpIfNotEqual(1);
				Event_Queue_CompareIntToConst(&eventSystem.vars[5].i, 0);
				Event_Queue_JumpIfNotEqual(1);
				
				Event_Queue_Dialog_Run(2199);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2200);
				Event_Queue_Dialog_Run(2201);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(15, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(2202);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(14, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(15, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2203);
				Event_Queue_EngageBattle(60, eventSystem.callerObjectId);
				Event_Queue_Object_Destroy(14);
				Event_Queue_Object_Destroy(15);
				Event_Queue_SetFlag(FLAG_OZONE_GATEFIGHT, 1);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2205);
				
				Event_Queue_Label(0);
			}
			else if (eventSystem.callerObjectId == 13) {
				Event_Queue_Dialog_Run(2213);
			}
			else if (eventSystem.callerObjectId == 12) {
				if (overworld.player.x <= 25728 || overworld.player.y <= 12642) {
					Event_Queue_Dialog_Run(2212);
					Event_Queue_EngageBattle(59, eventSystem.callerObjectId);
					Event_Queue_Object_Destroy(eventSystem.callerObjectId);
					Event_Queue_SetFlag(FLAG_OZONE_LADDERFIGHT, 1);
				}
				else {
					Event_Queue_Dialog_Run(2211);
				}
			}
			else {
				Event_Queue_Dialog_Run(2206);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000071: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_ALONE]) {
				if (profile.flags[FLAG_PLOT] <= 100) {
					Event_Queue_Dialog_Run(1020);
					Event_Queue_Dialog_Run(1021);
					Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
					Event_Queue_SetFlag(FLAG_PLOT, 101);
				}
				else if (profile.flags[FLAG_PLOT] >= 122) {
					if (!profile.tempFlags[TEMPFLAG_LAPISCITY_ADIOS_DIALOG] && !profile.flags[FLAG_ADIOS_OPTIONALFIGHT]) {
						Event_Queue_Dialog_Run(2258);
						Event_Queue_SetTempFlag(TEMPFLAG_LAPISCITY_ADIOS_DIALOG, 1);
					}
					else {
						Event_Queue_Dialog_Run(2259);
					}
				}
				else {
					Event_Queue_Dialog_Run(973);
					Event_Queue_Dialog_Run(1022);
					Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
					Event_Queue_JumpIfEqual(0);
					Event_Queue_Dialog_Run(1023);
					Event_Queue_Object_ChangeDirection(17, OBJECT_DIRECTION_LEFT);
					Event_Queue_Dialog_Run(1024);
					Event_Queue_Object_ChangeDirection(18, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_JumpToPointer(18, 0, 64, OBJECT_DIRECTION_UP, 80, 40, &player->x, &player->y);
					Event_Queue_Overworld_ShakeScreen(10);
					Event_Queue_PlaySound(SND_slap);
					Event_Queue_WaitFrames(2);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeDirection(17, OBJECT_DIRECTION_DOWN);
					Event_Queue_Dialog_Run(1025);
					Event_Queue_Dialog_Run(1026);
					Event_Queue_WaitFrames(44);
					Event_Queue_Object_WalkToRelative(18, 0, -16, 0.25, OBJECT_DIRECTION_UP);
					Event_Queue_Dialog_Run(1027);
					
					Event_Queue_EngageBattle(73, eventSystem.callerObjectId);
					
					Event_Queue_Dialog_Run(1028);
					Event_Queue_Dialog_Run(1029);
					
					Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
					Event_Queue_Object_Destroy(13);
					Event_Queue_Object_Destroy(14);
					Event_Queue_Object_Destroy(15);
					Event_Queue_Object_Destroy(16);
					Event_Queue_Object_ChangeDirection(0, player->direction);
					Event_Queue_Object_TeleportTo(18, 27016, 4840);
					Event_Queue_WaitFrames(30);
					Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
					
					Event_Queue_Dialog_Run(1030);
					
					Event_Queue_SetFlag(FLAG_PLOT, 122);
					Event_Queue_SetFlag(FLAG_ADIOS_OPTIONALFIGHT, 1);
					Event_Queue_Label(0);
				}
			}
			else {
				if (profile.flags[FLAG_PLOT] <= 100) {
					Event_Queue_Dialog_Run(960);
					Event_Queue_Dialog_Run(961);
					Event_Queue_Dialog_Run(962);
					Event_Queue_Dialog_Run(963);
					Event_Queue_Dialog_Run(964);
					Event_Queue_Dialog_Run(965);
					Event_Queue_Dialog_Run(966);
					Event_Queue_Dialog_Run(967);
					Event_Queue_Dialog_Run(968);
					Event_Queue_Dialog_Run(969);
					Event_Queue_Dialog_Run(970);
					Event_Queue_Dialog_Run(971);
					Event_Queue_Dialog_Run(972);
					Event_Queue_Dialog_Run(976);
					Event_Queue_Dialog_Run(977);
					Event_Queue_Object_Destroy(19);
					Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
					Event_Queue_SetFlag(FLAG_PLOT, 101);
				}
				else if (profile.flags[FLAG_PLOT] >= 122) {
					if (!profile.tempFlags[TEMPFLAG_LAPISCITY_ADIOS_DIALOG]) {
						Event_Queue_Dialog_Run(2258);
						Event_Queue_SetTempFlag(TEMPFLAG_LAPISCITY_ADIOS_DIALOG, 1);
					}
					else {
						Event_Queue_Dialog_Run(2259);
					}
				}
				else {
					Event_Queue_Dialog_Run(973);
					if (profile.cash >= 5000000) {
						Event_Queue_Dialog_Run(974);
						Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
						Event_Queue_JumpIfEqual(0);
						Event_Queue_Dialog_Run(975);
						Event_Queue_Label(0);
					}
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000072: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_PLOT] >= 122) {
				Event_Queue_Dialog_Run(2257);
			}
			else {
				Event_Queue_Dialog_Run(2255);
				if (!profile.tempFlags[TEMPFLAG_LAPISCITY_BULLDOG_HINT] && profile.flags[FLAG_PLOT] <= 100) {
					Event_Queue_Dialog_Run(2256);
					Event_Queue_SetTempFlag(TEMPFLAG_LAPISCITY_BULLDOG_HINT, 1);
				}
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000073: {
			if (profile.flags[FLAG_PLOT] < 74 || profile.flags[FLAG_PLOT] >= 500) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2264);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2261);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(2);
				Event_Queue_Dialog_Run(2265);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_CompareIntToConst(&profile.cash, (profile.flags[FLAG_ALONE]) ? 70 : 280);
				Event_Queue_JumpIfLess(2);
				Event_Queue_Dialog_Run(2262);
				Event_Queue_AddCash((profile.flags[FLAG_ALONE]) ? -70 : -280);
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_Camera_TeleportTo(20328, 7096);
				Event_Queue_Object_ChangeSpriteId(0, -1);
				Event_Queue_Object_ChangeSpriteId(1, -1);
				Event_Queue_Object_ChangeSpriteId(2, -1);
				Event_Queue_Object_ChangeSpriteId(3, -1);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(30);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_WalkToRelative(13, 96, 0, 0.5, OBJECT_DIRECTION_RIGHT);
				Event_Queue_FadeOutMusic(1000);
				Event_Queue_Object_WalkToRelative(13, 192, 0, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(30);
				
				Event_Queue_GotoArea(80, 22456, 8952, SPR_tileset_day);
				
				Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000074: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2263);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000075: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2266);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000076: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(14);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000077: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2283);
			Event_Queue_OpenShopMenu(15);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_LEFT);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000078: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(16);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_LEFT);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000079: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2010);
			Event_Queue_OpenShopMenu(17);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_LEFT);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000080: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2284);
			Event_Queue_OpenShopMenu(20);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000081: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2285);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000082: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2286);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000083: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2287);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000084: {
			if (overworld.areaId == 152) {
				if (profile.flags[FLAG_PLOT] >= 100 && profile.flags[FLAG_PLOT] < 200) {
					if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] < 3) {
						Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
						Event_Queue_Dialog_Run(1090);
						Event_Queue_Dialog_Run(1104);
						Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
						Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
					}
					else {
						Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
						Event_Queue_Dialog_Run(1090);
						if (profile.flags[FLAG_ALONE]) {
							Event_Queue_Dialog_Run(1105);
						}
						else {
							Event_Queue_Dialog_Run(1091);
							Event_Queue_Dialog_Run(1092);
							Event_Queue_Dialog_Run(1093);
							Event_Queue_Dialog_Run(1094);
							Event_Queue_Dialog_Run(1095);
							Event_Queue_Dialog_Run(1096);
							Event_Queue_Dialog_Run(1097);
							Event_Queue_Dialog_Run(1098);
							Event_Queue_Dialog_Run(1099);
							Event_Queue_Dialog_Run(1100);
							Event_Queue_Dialog_Run(1101);
							Event_Queue_Dialog_Run(1102);
							Event_Queue_Dialog_Run(1103);
						}
						Event_Queue_EngageBattle(45, eventSystem.callerObjectId);
						
						Event_Queue_Object_Destroy(10);
						Event_Queue_Object_Destroy(11);
						Event_Queue_Object_Destroy(12);
						Event_Queue_Object_Destroy(13);
						
						Event_Queue_SetFlag(FLAG_PLOT, 200);
						Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
					}
				}
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2288);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000085: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2295);
			Event_Queue_OpenShopMenu(18);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000086: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2296);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000087: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2297);
			Event_Queue_Dialog_Run(2298);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000088: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2299);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000089: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2300);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000090: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2301);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000091: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2326);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000092: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2305);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000093: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2303);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000094: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2304);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000095: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2306);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000096: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2307);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000097: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3157);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000098: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2310);
			Event_Queue_OpenShopMenu(21);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000099: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2311);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000100: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2322);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(0);
			
			Event_Queue_Dialog_Run(2323);
			Event_Queue_Object_Destroy(10);
			Event_Queue_Party_Join(2);
			Event_Queue_Profile_InventoryPartyOrderAdd(2);
			Event_Queue_Object_TeleportToPointer(2, 0, 0, &overworld.objects[10].x, &overworld.objects[10].y);
			Event_Queue_Dialog_Run(3002);
			
			Event_Queue_Regroup(1);
			Event_Queue_SetFlag(FLAG_EMMET_JOINED, 1);
			Event_Queue_SetFlag(FLAG_ALONE, 0);
			
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000101: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 150) {
				if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
					Event_Queue_Dialog_Run(2682);
				}
				else {
					Event_Queue_Dialog_Run(2657);
				}
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000102: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 150) {
				if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
					Event_Queue_Dialog_Run(2682);
				}
				else {
					Event_Queue_Dialog_Run(2658);
				}
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			}
			else {
				Event_Queue_Dialog_Run(2659);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000103: {
			int correctSpot = Random_IRange(0, 69);
			for (int i = 0; i < 70; i++) {
				overworld.objects[160 + i].spriteId = SPR_misc_guide_arrow;
				overworld.objects[160 + i].vars[7].i = 0;
				OverworldObject_SetColor(160 + i, 255, 255, 255);
			}
			overworld.objects[160 + correctSpot].vars[7].i = 1;
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] == 0) {
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_Object_TeleportTo(0, 18864, 15720);
				Event_Queue_Object_TeleportTo(1, 18840, 15720);
				Event_Queue_Object_TeleportTo(2, 18888, 15720);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				
				Event_Queue_Dialog_Run(1200);
				Event_Queue_Dialog_Run(1201);
				Event_Queue_Dialog_Run(1202);
				Event_Queue_Dialog_Run(1203);
				Event_Queue_Dialog_Run(1204);
				Event_Queue_Dialog_Run(1205);
				Event_Queue_Dialog_Run(1206);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(33);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(22);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(24);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(1207);
				Event_Queue_Object_ChangeSpriteId(2, SPR_misc_sally_serious);
				Event_Queue_Object_ChangeSpriteFrame(2, 1);
				Event_Queue_Dialog_Run(1208);
				Event_Queue_Dialog_Run(1209);
				Event_Queue_Dialog_Run(1210);
				Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_sally);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(1211);
				Event_Queue_Dialog_Run(1212);
				Event_Queue_Dialog_Run(1213);
				Event_Queue_Dialog_Run(1214);
				Event_Queue_Dialog_Run(1215);
				Event_Queue_Object_ChangeSpriteId(1, SPR_misc_emmet_facepalm);
				Event_Queue_Dialog_Run(1216);
				Event_Queue_Object_JumpToRelative(2, 0, 0, OBJECT_DIRECTION_UP, 16, 8);
				Event_Queue_Dialog_Run(1217);
				Event_Queue_Dialog_Run(1218);
				Event_Queue_Object_WalkToRelative(2, 0, -4, 0.5, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(1219);
				Event_Queue_Dialog_Run(1220);
				Event_Queue_Dialog_Run(1221);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(1222);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(1223);
				Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_emmet);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(1224);
			}
			else {
				Event_Queue_Dialog_Run(2339);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(0);
			}
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Object_TeleportTo(0, 19008, 15344);
			Event_Queue_Object_TeleportTo(1, 19040, 15344);
			Event_Queue_Object_TeleportTo(2, 19072, 15344);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_TeleportTo(10, 18968, 15352);
			Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_Dialog_Run(2340);
			
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkToRelative(10, -64, 0, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_SetSync(false);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_TeleportTo(0, 19072, 15344);
			Event_Queue_Object_WalkTo(0, 19008, 15344, 3, OBJECT_DIRECTION_LEFT);
			Event_Queue_Regroup(4);
			Event_Queue_WaitFrames(8);
			Event_Queue_Dialog_Run(2341);
			for (int i = 0; i < 70; i++) {
				Event_Queue_Object_TeleportTo(160 + i, overworld.objects[160 + i].x, overworld.objects[160 + i].y + 1000);
			}
			Event_Queue_Object_TeleportTo(10, overworld.objects[10].x, overworld.objects[10].y - 1000);
			Event_Queue_Object_ChangeSpriteFrame(89, 0);
			if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] >= 4) {
				int spotX = overworld.objects[160 + correctSpot].x;
				int spotY = overworld.objects[160 + correctSpot].y + 1000;
				int invertedDirection = OBJECT_DIRECTION_DOWN;
				switch (overworld.objects[160 + correctSpot].vars[6].i) {
					case OBJECT_DIRECTION_LEFT: spotX -= 32; invertedDirection = OBJECT_DIRECTION_RIGHT; break;
					case OBJECT_DIRECTION_RIGHT: spotX += 32; invertedDirection = OBJECT_DIRECTION_LEFT; break;
					case OBJECT_DIRECTION_UP: spotY -= 32; invertedDirection = OBJECT_DIRECTION_DOWN; break;
					case OBJECT_DIRECTION_DOWN: spotY += 32; invertedDirection = OBJECT_DIRECTION_UP; break;
				}
				
				Event_Queue_CreateObject(71, 1, SPR_owchar_sally, spotX, spotY, invertedDirection);
			}
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_PlayMusic(MUS_countdown);
			Event_Queue_CreateObject(70, 101, 0, 18864, 15280, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetFlag(FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS, profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] + 1);
			
			Event_Queue_SetBoolPtr(&overworld.map.doors[174].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[175].enabled, false);
			
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000107: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 194) {
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, caller->vars[7].i);
				Event_Queue_Dialog_Run(2363);
			}
			else if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] <= 4) {
				if (!profile.tempFlags[TEMPFLAG_WHITELIGHT_SALLY_DIALOG]) {
					Event_Queue_SetTempFlag(TEMPFLAG_WHITELIGHT_SALLY_DIALOG, 1);
					Event_Queue_Dialog_Run(2354);
					Event_Queue_Dialog_Run(2355);
					Event_Queue_Dialog_Run(2356);
					Event_Queue_Dialog_Run(2357);
					Event_Queue_Dialog_Run(2358);
					Event_Queue_Dialog_Run(2359);
				}
				else {
					Event_Queue_Dialog_Run(2360);
				}
			}
			else if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] <= 6) {
				Event_Queue_Dialog_Run(2361);
			}
			else if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] == 7) {
				Event_Queue_Dialog_Run(2362);
			}
			else {
				if (!profile.tempFlags[TEMPFLAG_WHITELIGHT_SALLY_DIALOG]) {
					Event_Queue_SetTempFlag(TEMPFLAG_WHITELIGHT_SALLY_DIALOG, 1);
					Event_Queue_Dialog_Run(2362);
				}
				else {
					Event_Queue_Dialog_Run(2363);
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000108: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] >= 1) {
				Event_Queue_Dialog_Run(2378);
			}
			else {
				if (profile.flags[FLAG_ALONE])
					Event_Queue_Dialog_Run(2660);
				else
					Event_Queue_Dialog_Run(2365);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 2);
				Event_Queue_JumpIfEqual(2);
				
				Event_Queue_Label(3);
				Event_Queue_CompareIntToConst(&profile.cash, 400);
				Event_Queue_JumpIfLess(6);
				Event_Queue_Dialog_Run(2379);
				if (!profile.flags[FLAG_ALONE]) {
					Event_Queue_Dialog_Run(2380);
					Event_Queue_Dialog_Run(2381);
					Event_Queue_Dialog_Run(2382);
					Event_Queue_Dialog_Run(2383);
					Event_Queue_WaitFrames(50);
					Event_Queue_Dialog_Run(2384);
					Event_Queue_Dialog_Run(2385);
				}
				Event_Queue_AddCash(-400);
				Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 1);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(6);
				Event_Queue_Dialog_Run(2377);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(2);
				Event_Queue_Dialog_Run(2366);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(3);
				
				Event_Queue_Dialog_Run(2367);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(3);
				
				Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_MAN_ANNOYED, 1);
				Event_Queue_Dialog_Run(2368);
				Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 16960, 15984, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 16960, 15944, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_JumpTo(eventSystem.callerObjectId, 16960, 15920, OBJECT_DIRECTION_UP, 18, 16);
				Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 16784, 15920, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 16768, 15888, 2, OBJECT_DIRECTION_UP);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_WaitFrames(125);
				Event_Queue_Dialog_Run(2369);
				Event_Queue_Dialog_Run(2370);
				Event_Queue_WaitFrames(25);
				Event_Queue_CreateNPC(eventSystem.callerObjectId, 109, 16768, 15896, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(eventSystem.callerObjectId, 16984, 15920, 2, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(eventSystem.callerObjectId, 16984, 15984, OBJECT_DIRECTION_DOWN, 32, 25);
				
				Event_Queue_Dialog_Run(2371);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(5);
				
				Event_Queue_Dialog_Run(2372);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(5);
				
				Event_Queue_Object_WalkToPointer(1, -8, 0, 3, OBJECT_DIRECTION_RIGHT, &player->x, &player->y);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeSpriteId(1, SPR_misc_noah_hug);
				Event_Queue_WaitFrames(65);
				Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
				Event_Queue_Object_JumpToRelative(1, -8, 0, OBJECT_DIRECTION_RIGHT, 0, 4);
				Event_Queue_WaitFrames(20);
				Event_Queue_CompareIntToConst(&profile.cash, 400);
				Event_Queue_JumpIfLess(8);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(2374);
				
				Event_Queue_Label(5);
				Event_Queue_AddCash(-400);
				Event_Queue_Dialog_Run(2373);
				Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 1);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(8);
				Event_Queue_WaitFrames(40);
				Event_Queue_Dialog_Run(2375);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				
				Event_Queue_Label(7);
				Event_Queue_Dialog_Run(2376);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				
				Event_Queue_Label(0);
				Event_Queue_Regroup(1);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000109: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] >= 1) {
				Event_Queue_Dialog_Run(2387);
			}
			else {
				Event_Queue_Dialog_Run(2386);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				
				Event_Queue_CompareIntToConst(&profile.cash, 400);
				Event_Queue_JumpIfLess(2);
				Event_Queue_Dialog_Run(2373);
				Event_Queue_AddCash(-400);
				Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 1);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(7);
				Event_Queue_Dialog_Run(2376);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				
				Event_Queue_Label(0);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000116: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(2668);
			}
			else if (profile.flags[FLAG_AMPERCORP_FLOORS_UNLOCKED] >= 1) {
				Event_Queue_Dialog_Run(2388);
			}
			else {
				Event_Queue_Dialog_Run(2388);
				Event_Queue_Dialog_Run(2389);
				Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 1);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000119: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_AMPERCORP_FLOORS_UNLOCKED] >= 4) {
				
			}
			else {
				Event_Queue_Dialog_Run(2392);
				Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 4);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000124: {
			if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DEFEATED] > 0) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2569);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 0) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2550);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 1) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2551);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 2);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 2) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2552);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 3);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 3) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2553);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 4);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 4) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2554);
				Event_Queue_Object_WalkTo(62, 29152, 13960, 2, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2555);
				Event_Queue_Dialog_Run(2556);
				Event_Queue_Dialog_Run(2557);
				Event_Queue_Object_WalkTo(62, 29176, 13856, 2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 5);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 5) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2558);
				Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 6);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 8) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2568);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2559);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(0);
				
				if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] == 7) {
					Event_Queue_Dialog_Run(2565);
					Event_Queue_EngageBattle(86, 61);
					
					Event_Queue_CompareIntToConst(&profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG], 8);
					Event_Queue_JumpIfEqual(1);
					
					Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DEFEATED, 3);
					Event_Queue_Dialog_Run(2566);
					Event_Queue_PlaySound(SND_dodge);
					Event_Queue_Object_JumpTo(61, 29096, 13952, -1, 104, 18);
					Event_Queue_Jump(0);
					
					Event_Queue_Label(1);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_collapse_ruby);
					Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_collapse_noah);
					Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_collapse_emmet);
					Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_collapse_sally_neo);
					Event_Queue_Object_ChangeSpriteFrame(0, 1);
					Event_Queue_Object_ChangeSpriteFrame(1, 1);
					Event_Queue_Object_ChangeSpriteFrame(2, 1);
					Event_Queue_Object_ChangeSpriteFrame(3, 1);
					Event_Queue_WaitFrames(116);
					Event_Queue_Dialog_Run(2567);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
					Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
					Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_sally_neo);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
					Event_Queue_WaitFrames(65);
					Event_Queue_Regroup(1);
				}
				else {
					Event_Queue_Dialog_Run(2560);
					Event_Queue_WaitFrames(8);
					Event_Queue_Overworld_ShakeScreen(10);
					Event_Queue_CreateObject(70, 1, SPR_misc_pbsuperhero_certificate, caller->x + 8, caller->y, OBJECT_DIRECTION_DOWN);
					Event_Queue_PlaySound(SND_gunfire2);
					Event_Queue_SetSync(true);
					Event_Queue_WaitFrames(6);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_collapse_ruby);
					Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_collapse_noah);
					Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_collapse_emmet);
					Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_collapse_sally_neo);
					Event_Queue_Object_JumpToRelative(0, 0, 48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_Object_JumpToRelative(1, 0, 48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_Object_JumpToRelative(2, 0, 48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_Object_JumpToRelative(3, 0, 48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_WaitFrames(6);
					Event_Queue_Object_ChangeSpriteFrame(70, 1);
					Event_Queue_SetSync(false);
					Event_Queue_PlaySound(SND_poison);
					Event_Queue_Object_ChangeSpriteFrame(0, 1);
					Event_Queue_Object_ChangeSpriteFrame(1, 1);
					Event_Queue_Object_ChangeSpriteFrame(2, 1);
					Event_Queue_Object_ChangeSpriteFrame(3, 1);
					
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(2561);
					
					Event_Queue_SetSync(true);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_Object_ChangeSpriteId(1, SPR_owchar_noah);
					Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
					Event_Queue_Object_ChangeSpriteId(3, SPR_owchar_sally_neo);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
					Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
					Event_Queue_Object_JumpToRelative(0, 0, -48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_Object_JumpToRelative(1, 0, -48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_Object_JumpToRelative(2, 0, -48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_Object_JumpToRelative(3, 0, -48, OBJECT_DIRECTION_UP, 16, 12);
					Event_Queue_SetSync(false);
					
					Event_Queue_Dialog_Run(2562);
					Event_Queue_Dialog_Run(2563);
					Event_Queue_Object_Destroy(70);
					Event_Queue_Dialog_Run(2564);
					Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DIALOG, 7);
					Event_Queue_Regroup(1);
				}
				
				Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000125: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			
			Event_Queue_Dialog_Run(2571);
			Event_Queue_Dialog_Run(2572);
			Event_Queue_Dialog_Run(2573);
			Event_Queue_Dialog_Run(2574);
			Event_Queue_Dialog_Run(2575);
			Event_Queue_Dialog_Run(2576);
			Event_Queue_Dialog_Run(2577);
			
			Event_Queue_EngageBattle(76, 62);
			
			Event_Queue_Dialog_Run(2578);
			Event_Queue_Dialog_Run(2579);
			Event_Queue_Dialog_Run(2580);
			Event_Queue_Dialog_Run(2581);
			Event_Queue_Dialog_Run(2582);
			Event_Queue_WaitFrames(65);
			Event_Queue_Dialog_Run(2583);
			Event_Queue_Dialog_Run(2584);
			Event_Queue_Dialog_Run(2585);
			Event_Queue_Dialog_Run(2586);
			Event_Queue_Dialog_Run(2587);
			
			Event_Queue_StopMusic();
			Event_Queue_PlaySound(SND_ampbroadcast);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(62, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(true);
			Event_Queue_Object_JumpTo(0, 29176, 13896, OBJECT_DIRECTION_UP, 8, 12);
			Event_Queue_Object_JumpTo(1, 29160, 13912, OBJECT_DIRECTION_UP, 8, 12);
			Event_Queue_Object_JumpTo(2, 29144, 13896, OBJECT_DIRECTION_UP, 8, 12);
			Event_Queue_Object_JumpTo(3, 29128, 13912, OBJECT_DIRECTION_UP, 8, 12);
			Event_Queue_Camera_MoveTo(29152, 13744, 2);
			Event_Queue_SetSync(false);
			Event_Queue_CreateObject(70, 1, SPR_misc_ampbroadcast, 29152, 13712, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(70, 5);
			Event_Queue_PlaySound(SND_beep_square);
			Event_Queue_WaitFrames(45);
			Event_Queue_Object_ChangeSpriteFrame(70, 6);
			Event_Queue_WaitFrames(70);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(2588);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_Dialog_Run(2589);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Dialog_Run(2590);
			Event_Queue_Object_ChangeSpriteFrame(70, 5);
			Event_Queue_WaitFrames(6);
			Event_Queue_Object_ChangeSpriteFrame(70, 3);
			Event_Queue_WaitFrames(120);
			Event_Queue_Object_Destroy(70);
			Event_Queue_WaitFrames(60);
			Event_Queue_Camera_MoveTo(29152, 13888, 2);
			
			Event_Queue_SetIntPtr(&overworld.objects[69].vars[0].i, 1);
			
			Event_Queue_Object_ChangeDirection(62, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(2591);
			Event_Queue_Dialog_Run(2592);
			Event_Queue_Dialog_Run(2593);
			Event_Queue_Object_ChangeSpriteId(62, SPR_misc_kara_jump);
			Event_Queue_Object_ChangeSpriteFrame(62, 1);
			Event_Queue_Object_ChangeDirection(62, OBJECT_DIRECTION_LEFT);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(29056, 14016, 6);
			Event_Queue_Object_JumpTo(62, 29064, 14008, OBJECT_DIRECTION_LEFT, 32, 46);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeSpriteFrame(62, 2);
			Event_Queue_Object_ChangeDirection(62, OBJECT_DIRECTION_DOWN);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(28864, 14016, 3.5);
			Event_Queue_Object_JumpTo(62, 28852, 14080, OBJECT_DIRECTION_DOWN, 56, 68);
			Event_Queue_SetSync(false);
			Event_Queue_Object_ChangeSpriteFrame(62, 0);
			Event_Queue_PlaySound(SND_dodge);
			Event_Queue_Object_JumpTo(62, 28648, 14280, OBJECT_DIRECTION_DOWN, 20, 47);
			Event_Queue_Object_Destroy(62);
			Event_Queue_WaitFrames(50);
			
			Event_Queue_Regroup(3);
			Event_Queue_PlayMusic(MUS_amper);
			Event_Queue_Dialog_Run(2394);
			Event_Queue_SetFlag(FLAG_AMPERCORP_PLOT, 60);
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 6);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000126: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2594);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000129: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(176)) {
				if (!profile.flags[FLAG_BRILLIANT_ACCESS_GRANTED]) {
					Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_UP);
					Event_Queue_Camera_MoveTo(26992, 9600, 1);
					Event_Queue_WaitFrames(40);
					Event_Queue_Object_Destroy(11);
					Event_Queue_PlaySound(SND_slap);
					Event_Queue_Overworld_ShakeScreen(8);
					Event_Queue_WaitFrames(50);
					
					Event_Queue_Regroup(1);
					Event_Queue_SetFlag(FLAG_BRILLIANT_ACCESS_GRANTED, 1);
				}
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000130: {
			if (profile.flags[FLAG_PLOT] < 134) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2652);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.cash < 600) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2655);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_PLOT] < 500 && profile.flags[FLAG_METRO_LOCATION] != 3) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2651);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
				Event_Queue_SetFlag(FLAG_METRO_LOCATION, 3);
				Event_Queue_Dialog_Run(2653);
				Event_Queue_GotoArea(203, 22394, 9816, -1);
				Event_Queue_PlayMusic(MUS_transport);
				Event_Queue_Object_TeleportTo(1, 22394, 9840);
				Event_Queue_Object_TeleportTo(2, 22486, 9816);
				Event_Queue_Object_TeleportTo(3, 22486, 9840);
				
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_sit);
				Event_Queue_Object_ChangeSpriteFrame(0, 4);
				
				if (profile.flags[FLAG_NOAH_JOINED]) {
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_ChangeSpriteId(1, SPR_misc_noah_sit);
					Event_Queue_Object_ChangeSpriteFrame(1, 4);
				}
				
				if (profile.flags[FLAG_EMMET_JOINED]) {
					Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
					Event_Queue_Object_ChangeSpriteId(2, SPR_misc_emmet_sit);
					Event_Queue_Object_ChangeSpriteFrame(2, 4);
				}
				
				if (profile.flags[FLAG_SALLY_JOINED]) {
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
					Event_Queue_Object_ChangeSpriteId(3, (profile.flags[FLAG_SALLY_NEO]) ? SPR_misc_sally_neo_sit : SPR_misc_sally_sit);
					Event_Queue_Object_ChangeSpriteFrame(3, 4);
				}
				
				Event_Queue_WaitFrames(600);
				Event_Queue_StopMusic();
				Event_Queue_PlaySound(SND_transportend);
				Event_Queue_WaitFrames(90);
				Event_Queue_GotoArea(203, 22624, 10280, -1);
				
				Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_PLOT] < 500) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2656);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2650);
				Event_Queue_CompareIntToVar(&dialogSystem.optionSelected, &profile.flags[FLAG_METRO_LOCATION]);
				Event_Queue_JumpIfEqual(5);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(2);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 2);
				Event_Queue_JumpIfEqual(3);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 3);
				Event_Queue_JumpIfEqual(4);
				Event_Queue_Jump(0);
				
				Event_Queue_Label(1);
					Event_Queue_SetFlag(FLAG_METRO_LOCATION, 0);
					Event_Queue_Jump(10);
				Event_Queue_Label(2);
					Event_Queue_SetFlag(FLAG_METRO_LOCATION, 1);
					Event_Queue_Jump(10);
				Event_Queue_Label(3);
					Event_Queue_SetFlag(FLAG_METRO_LOCATION, 2);
					Event_Queue_Jump(10);
				Event_Queue_Label(4);
					Event_Queue_SetFlag(FLAG_METRO_LOCATION, 3);
					Event_Queue_Jump(10);
				Event_Queue_Label(5);
					Event_Queue_Dialog_Run(2654);
					Event_Queue_Jump(0);
				
				Event_Queue_Label(10);
				Event_Queue_Dialog_Run(2653);
				Event_Queue_GotoArea(203, 22394, 9816, -1);
				Event_Queue_PlayMusic(MUS_transport);
				Event_Queue_Object_TeleportTo(1, 22394, 9840);
				Event_Queue_Object_TeleportTo(2, 22486, 9816);
				Event_Queue_Object_TeleportTo(3, 22486, 9840);
				
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_sit);
				Event_Queue_Object_ChangeSpriteFrame(0, 4);
				
				if (profile.flags[FLAG_NOAH_JOINED]) {
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_ChangeSpriteId(1, SPR_misc_noah_sit);
					Event_Queue_Object_ChangeSpriteFrame(1, 4);
				}
				
				if (profile.flags[FLAG_EMMET_JOINED]) {
					Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_LEFT);
					Event_Queue_Object_ChangeSpriteId(2, SPR_misc_emmet_sit);
					Event_Queue_Object_ChangeSpriteFrame(2, 4);
				}
				
				if (profile.flags[FLAG_SALLY_JOINED]) {
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_LEFT);
					Event_Queue_Object_ChangeSpriteId(3, (profile.flags[FLAG_SALLY_NEO]) ? SPR_misc_sally_neo_sit : SPR_misc_sally_sit);
					Event_Queue_Object_ChangeSpriteFrame(3, 4);
				}
				
				Event_Queue_WaitFrames(600);
				Event_Queue_StopMusic();
				Event_Queue_PlaySound(SND_transportend);
				Event_Queue_WaitFrames(90);
				Event_Queue_GotoArea(203, 22624, 10280, -1);
				
				Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1000131: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(1483);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(0);
			
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_FadeOutMusic(1000);
			Event_Queue_Overworld_FadeIn(60, 0, 0, 0);
			Event_Queue_WaitFrames(90);
			Event_Queue_SetFlag(FLAG_PLOT, 501);
			Event_Queue_GotoArea(150, 26808, 1000, -1);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_CreateObject(70, 1, SPR_owchar_lulu_god, 26808, 1000, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(0, 26808, 1048, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(1, 26840, 1080, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(2, 26840, 1048, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(3, 26840, 1016, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(70, 26760, 1064, 1, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(1484);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(70, 26656, 1248, 2, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1485);
			Event_Queue_SetSync(false);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
			Event_Queue_Dialog_Run(1486);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Regroup(2);
			
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1000132: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2667);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		
		
		case 1010000: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_OpenSaveMenu();
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010001: {
			if (profile.flags[FLAG_MANSION_SOFA_PUSHED] == 1) {
				
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Dialog_Run(2005);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_Object_WalkToPointer(0, 32, 1, 1, OBJECT_DIRECTION_RIGHT, &overworld.objects[10].x, &overworld.objects[10].y);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkToRelative(10, -32, 0, 0.25, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_WalkToRelative(0, -32, 0, 0.25, OBJECT_DIRECTION_LEFT);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(10);
				
				Event_Queue_Regroup(2);
				Event_Queue_SetFlag(FLAG_MANSION_SOFA_PUSHED, 1);
				Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010002: {
			overworld.player.dashEnabled = false;
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(163);
			Event_Queue_Dialog_Run(4004);
			
			Event_Queue_WaitFrames(60);
			Event_Queue_StopMusic();
			Event_Queue_SetIntPtr(&overworld.overlayId, 1);
			Event_Queue_WaitFrames(10);
			Event_Queue_SetIntPtr(&overworld.overlayId, 0);
			Event_Queue_WaitFrames(40);
			Event_Queue_SetIntPtr(&overworld.overlayId, 1);
			Event_Queue_WaitFrames(60);
			Event_Queue_SetIntPtr(&overworld.overlayId, 2);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			Event_Queue_WaitFrames(10);
			Event_Queue_PlayMusic(MUS_scary);
			Event_Queue_CreateObject(70, 100, 0, 8064, 8256, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(71, 100, 0, 8048, 8384, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(72, 100, 0, 8080, 8400, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(73, 100, 0, 7872, 8448, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(74, 100, 0, 7888, 8448, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(75, 100, 0, 8112, 8480, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(76, 100, 0, 8128, 8496, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(77, 100, 0, 8112, 8512, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(78, 100, 0, 8128, 8528, OBJECT_DIRECTION_DOWN);
			
			Event_Queue_SetFlag(FLAG_MANSION_GOTKEY_GOLD, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010003: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(32);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010004: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (eventSystem.callerObjectId == 11) {
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_Destroy(11);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_PlaySound(SND_menu2);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(34);
				Event_Queue_SetFlag(FLAG_PLOT, 2);
				Event_Queue_SetFlag(FLAG_RUBY_LABCOAT, 1);
			}
			else if (profile.flags[FLAG_RUBY_LABCOAT]) {
				Event_Queue_Dialog_Run(36);
			}
			else {
				Event_Queue_Dialog_Run(33);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010005: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(35);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010006: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(7);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_ItemAdd(7);
				Event_Queue_Dialog_Run(4004);
				if (!profile.flags[FLAG_TOMATOSOUP_DIALOG] && Party_Exists(2)) {
					Event_Queue_Dialog_Run(450);
					if (Party_Exists(1)) Event_Queue_Dialog_Run(451);
					Event_Queue_Dialog_Run(452);
					if (Party_Exists(1))
						Event_Queue_Dialog_Run(453);
					else
						Event_Queue_Dialog_Run(454);
					Event_Queue_SetFlag(FLAG_TOMATOSOUP_DIALOG, 1);
				}
				switch (overworld.areaId) {
					case 0: Event_Queue_SetFlag(FLAG_ITEM_LEAFCREW_TOMATOSOUP, 1); break;
					case 4: Event_Queue_SetFlag(FLAG_ITEM_SLIMECAVE_TOMATOSOUP, 1); break;
					case 6: Event_Queue_SetFlag(FLAG_ITEM_TOWN_TOMATOSOUP, 1); break;
					case 100: Event_Queue_SetFlag(FLAG_ITEM_LAPISDESERT_TOMATOSOUP, 1); break;
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010007: {
			if (profile.flags[FLAG_PLOT] == 16) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(4376, 4384, 1);
				Event_Queue_Object_WalkTo(0, 4376, 4376, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(1, 4352, 4424, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(2, 4368, 4424, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_QueueWalkTo(2, 4416, 4424, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Dialog_Run(430);
				Event_Queue_Dialog_Run(431);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(432);
				Event_Queue_WaitFrames(180);
				Event_Queue_Dialog_Run(433);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(432);
				
				Event_Queue_SetSync(true);
				Event_Queue_CreateObject(70, 1, SPR_owchar_sora, 4576, 4504, OBJECT_DIRECTION_LEFT);
				Event_Queue_Camera_MoveTo(4376, 4464, 1);
				Event_Queue_Object_WalkTo(70, 4360, 4504, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(434);
				Event_Queue_Dialog_Run(435);
				Event_Queue_Dialog_Run(436);
				Event_Queue_Dialog_Run(437);
				Event_Queue_Dialog_Run(438);
				Event_Queue_Dialog_Run(439);
				Event_Queue_Dialog_Run(440);
				Event_Queue_Dialog_Run(441);
				Event_Queue_Dialog_Run(442);
				Event_Queue_Dialog_Run(443);
				Event_Queue_Dialog_Run(444);
				Event_Queue_Dialog_Run(445);
				Event_Queue_SetSync(true);
				Event_Queue_Camera_MoveTo(4376, 4376, 1);
				Event_Queue_Object_WalkTo(70, 4160, 4504, 2, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Dialog_Run(446);
				
				Event_Queue_Regroup(2);
				Event_Queue_SetFlag(FLAG_PLOT, 17);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else if (profile.flags[FLAG_PLOT] > 16) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(81);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(80);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010008: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(82);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010009: {
			if (profile.flags[FLAG_PLOT] >= 14) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2068);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010010: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_Dialog_Run(2123);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				Event_Queue_Exit();
				
				Event_Queue_Label(1);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_SetFlag(FLAG_PERRY_PIZZASLICES, profile.flags[FLAG_PERRY_PIZZASLICES] + 1);
				Event_Queue_WaitFrames(37);
				Event_Queue_CreateObject(71, 1, SPR_misc_perrypizza, player->x - 12, player->y, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_SetPositionZ(71, -16);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(8);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
				Event_Queue_Object_ChangeSpriteId(71, SPR_misc_perrypizza_broken);
				Event_Queue_PlaySound(SND_burn);
				Event_Queue_Object_TeleportTo(71, player->x, player->y + 10);
				Event_Queue_Object_SetPositionZ(71, 0);
				Event_Queue_WaitFrames(85);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_WaitFrames(65);
				Event_Queue_CreateObject(70, 1, SPR_owchar_perry, 9400, 8392, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_WalkTo(70, 9368, 8392, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(120);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(670);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(2);
				Event_Queue_Dialog_Run(671);
				Event_Queue_Dialog_Run(672);
				Event_Queue_Object_WalkTo(70, 9408, 8392, 1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_Destroy(70);
				Event_Queue_Jump(10);
				
				Event_Queue_Label(2);
				Event_Queue_WaitFrames(70);
				if (profile.flags[FLAG_ALONE_PLOT] >= 1) {
					Event_Queue_Dialog_Run(673);
					Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
					Event_Queue_JumpIfEqual(3);
					Event_Queue_Object_WalkTo(70, 9408, 8392, 1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_Destroy(70);
					Event_Queue_Jump(10);
					
					Event_Queue_Label(3);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_raisehands);
					Event_Queue_CreateNPC(72, 10051, player->x, player->y, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeSpriteFrame(72, 0);
					Event_Queue_Object_SetPositionZ(72, -32);
					Event_Queue_WaitFrames(70);
					Event_Queue_Dialog_Run(676);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
					Event_Queue_Object_SetPositionZ(72, 0);
					Event_Queue_Object_TeleportTo(72, player->x, player->y - 32);
					Event_Queue_SetSync(true);
					Event_Queue_PlaySound(SND_swing);
					Event_Queue_PlaySound(SND_dodge);
					Event_Queue_Object_JumpTo(72, 9296, 8312, -1, 12, 14);
					Event_Queue_WaitFrames(8);
					Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
					Event_Queue_SetSync(false);
					Event_Queue_CreateSpark(1, 9296, 8308, 0);
					Event_Queue_Overworld_ShakeScreen(12);
					Event_Queue_PlaySound(SND_explode);
					Event_Queue_Object_ChangeSpriteFrame(72, 1);
					Event_Queue_Profile_KeyItemRemove(170);
					Event_Queue_FadeOutMusic(2000);
					Event_Queue_WaitFrames(120);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(675);
					Event_Queue_Object_WalkTo(70, 9408, 8392, 0.5, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_Destroy(70);
					Event_Queue_SetFlag(FLAG_ALONE_PLOT, 2);
				}
				else {
					Event_Queue_Dialog_Run(674);
					Event_Queue_Object_WalkTo(70, 9408, 8392, 1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_Destroy(70);
				}
				
				Event_Queue_Label(10);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				Event_Queue_Exit();
				
				Event_Queue_Label(0);
			}
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(8);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_ItemAdd(8);
				Event_Queue_Dialog_Run(4004);
				Event_Queue_SetFlag(FLAG_PERRY_PIZZASLICES, profile.flags[FLAG_PERRY_PIZZASLICES] + 1);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010011: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(165);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_SetFlag(FLAG_FLASHLIGHT, 1);
			Event_Queue_PlaySound(SND_voice2);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			Event_Queue_SetIntPtr(&overworld.overlayId, 2);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(328);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010012: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2029);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010013: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_SetVarInt(0, 30);
			if (overworld.areaId == 24) {
				Event_Queue_SetVarInt(0, 20 + (eventSystem.callerObjectId - 10) * 20);
			}
			Event_Queue_PlaySound(SND_voice2);
			Event_Queue_WaitFrames(60);
			Event_Queue_Label(1);
			Event_Queue_PlaySound(SND_burn);
			Event_Queue_CustomAction(1);
			Event_Queue_WaitFrames(60);
			Event_Queue_JumpIfEqual(2);
			Event_Queue_JumpIfLess(3);
			Event_Queue_JumpIfGreater(4);
			Event_Queue_Jump(1);
			
			Event_Queue_Label(2);
			Event_Queue_Dialog_Run(2033);
			if (overworld.areaId == 19) {
				Event_Queue_PlaySound(SND_burn);
				Event_Queue_Object_ChangeSpriteFrame(41, Random_IRange(0, 4));
				Event_Queue_Object_ChangeSpriteFrame(42, Random_IRange(0, 4));
				Event_Queue_Object_ChangeSpriteFrame(43, Random_IRange(0, 4));
				Event_Queue_Object_ChangeSpriteFrame(44, Random_IRange(0, 4));
			}
			else if (overworld.areaId == 24) {
				if (eventSystem.callerObjectId == 10) {
					Event_Queue_WaitFrames(30);
					Event_Queue_PlaySound(SND_burn);
					Event_Queue_Object_Destroy(eventSystem.callerObjectId);
					Event_Queue_Object_Destroy(21);
					Event_Queue_Object_Destroy(22);
					Event_Queue_Object_Destroy(23);
					Event_Queue_Object_Destroy(24);
					Event_Queue_Object_Destroy(31);
					Event_Queue_Object_Destroy(32);
					Event_Queue_Object_Destroy(33);
					Event_Queue_Object_Destroy(34);
					Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_3, 1);
					
					Event_Queue_FadeOut(0.0625);
					Event_Queue_Camera_TeleportTo(7672, 9592);
					Event_Queue_SetIntPtr(&overworld.overlayId, 0);
					Event_Queue_FadeIn(0.0625);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ToggleGhost(110, true);
					Event_Queue_Object_WalkTo(110, 7672, 9784, 2, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_Destroy(110);
					Event_Queue_CreateEnemy(110, 50, 7672, 9784);
				}
				else if (eventSystem.callerObjectId == 11) {
					Event_Queue_WaitFrames(30);
					Event_Queue_PlaySound(SND_burn);
					Event_Queue_Object_Destroy(eventSystem.callerObjectId);
					Event_Queue_Object_Destroy(41);
					Event_Queue_Object_Destroy(42);
					Event_Queue_Object_Destroy(43);
					Event_Queue_Object_Destroy(51);
					Event_Queue_Object_Destroy(52);
					Event_Queue_Object_Destroy(53);
					Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_4, 1);
					
					Event_Queue_FadeOut(0.0625);
					Event_Queue_Camera_TeleportTo(7672, 9592);
					Event_Queue_SetIntPtr(&overworld.overlayId, 0);
					Event_Queue_FadeIn(0.0625);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ToggleGhost(111, true);
					Event_Queue_Object_WalkTo(111, 7672, 9784, 2, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_Destroy(111);
					Event_Queue_CreateEnemy(111, 50, 7672, 9784);
				}
				else if (eventSystem.callerObjectId == 12) {
					Event_Queue_WaitFrames(30);
					Event_Queue_PlaySound(SND_burn);
					Event_Queue_Object_Destroy(eventSystem.callerObjectId);
					Event_Queue_Object_Destroy(61);
					Event_Queue_Object_Destroy(62);
					Event_Queue_Object_Destroy(63);
					Event_Queue_Object_Destroy(64);
					Event_Queue_Object_Destroy(71);
					Event_Queue_Object_Destroy(72);
					Event_Queue_Object_Destroy(73);
					Event_Queue_Object_Destroy(74);
					Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_5, 1);
					
					Event_Queue_FadeOut(0.0625);
					Event_Queue_Camera_TeleportTo(7672, 9592);
					Event_Queue_SetIntPtr(&overworld.overlayId, 0);
					Event_Queue_FadeIn(0.0625);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ToggleGhost(112, true);
					Event_Queue_Object_WalkTo(112, 7672, 9784, 2, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_Destroy(112);
					Event_Queue_CreateEnemy(112, 50, 7672, 9784);
				}
				else if (eventSystem.callerObjectId == 13) {
					Event_Queue_WaitFrames(30);
					Event_Queue_PlaySound(SND_burn);
					Event_Queue_Object_Destroy(eventSystem.callerObjectId);
					Event_Queue_Object_Destroy(81);
					Event_Queue_Object_Destroy(82);
					Event_Queue_Object_Destroy(83);
					Event_Queue_Object_Destroy(91);
					Event_Queue_Object_Destroy(92);
					Event_Queue_Object_Destroy(93);
					Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_6, 1);
					
					Event_Queue_FadeOut(0.0625);
					Event_Queue_Camera_TeleportTo(7672, 9592);
					Event_Queue_SetIntPtr(&overworld.overlayId, 0);
					Event_Queue_FadeIn(0.0625);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ToggleGhost(113, true);
					Event_Queue_Object_WalkTo(113, 7672, 9784, 2, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_Destroy(113);
					Event_Queue_CreateEnemy(113, 50, 7672, 9784);
				}
				Event_Queue_FadeOut(0.0625);
				Event_Queue_Camera_TeleportTo(overworld.player.x, overworld.player.y - 8);
				Event_Queue_SetIntPtr(&overworld.overlayId, 2);
				Event_Queue_FadeIn(0.0625);
			}
			else if (overworld.areaId == 28) {
				Event_Queue_WaitFrames(60);
				Event_Queue_PlaySound(SND_encountermg);
				Event_Queue_CreateNPC(12, 10002, 7912, 8240, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(30);
				Event_Queue_PlaySound(SND_burn);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Object_Destroy(31);
				Event_Queue_Object_Destroy(32);
				Event_Queue_Object_Destroy(33);
				Event_Queue_Object_Destroy(41);
				Event_Queue_Object_Destroy(42);
				Event_Queue_Object_Destroy(43);
				Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_2, 1);
			}
			else if (overworld.areaId == 38) {
				Event_Queue_WaitFrames(60);
				Event_Queue_PlaySound(SND_encountermg);
				Event_Queue_CreateNPC(17, 10019, 8952, 7968, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(30);
				Event_Queue_PlaySound(SND_burn);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Object_Destroy(31);
				Event_Queue_Object_Destroy(32);
				Event_Queue_Object_Destroy(33);
				Event_Queue_Object_Destroy(41);
				Event_Queue_Object_Destroy(42);
				Event_Queue_Object_Destroy(43);
				Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_1, 1);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			Event_Queue_Exit();
			
			Event_Queue_Label(3);
			Event_Queue_JumpIfGreater(5);
			Event_Queue_Dialog_Run(2032);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(4);
			Event_Queue_Dialog_Run(2031);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(5);
			Event_Queue_Dialog_Run(2034);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(0);
			if (overworld.areaId == 19) {
				Event_Queue_Object_ChangeSpriteFrame(41, profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_1]);
				Event_Queue_Object_ChangeSpriteFrame(42, profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_2]);
				Event_Queue_Object_ChangeSpriteFrame(43, profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_3]);
				Event_Queue_Object_ChangeSpriteFrame(44, profile.tempFlags[TEMPFLAG_MANSION_DIA_FLOWER_4]);
			}
			else if (overworld.areaId == 24) {
				if (eventSystem.callerObjectId == 10) {
					if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_STUCK] >= 10) {
						Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_STUCK, 0);
						Event_Queue_Dialog_Run(2043);
						Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
						Event_Queue_JumpIfEqual(10);
						Event_Queue_Dialog_Run(2044);
					}
					else {
						Event_Queue_SetFlag(FLAG_MANSION_FLOWERPUZZLE_STUCK, profile.flags[FLAG_MANSION_FLOWERPUZZLE_STUCK] + 1);
					}
				}
				
				Event_Queue_Object_ChangeSpriteFrame(31, 0);
				Event_Queue_Object_ChangeSpriteFrame(32, 1);
				Event_Queue_Object_ChangeSpriteFrame(33, 2);
				Event_Queue_Object_ChangeSpriteFrame(34, 3);
				
				Event_Queue_Object_ChangeSpriteFrame(51, 3);
				Event_Queue_Object_ChangeSpriteFrame(52, 3);
				Event_Queue_Object_ChangeSpriteFrame(53, 3);
				
				Event_Queue_Object_ChangeSpriteFrame(71, 0);
				Event_Queue_Object_ChangeSpriteFrame(72, 1);
				Event_Queue_Object_ChangeSpriteFrame(73, 1);
				Event_Queue_Object_ChangeSpriteFrame(74, 0);
				
				Event_Queue_Object_ChangeSpriteFrame(91, 2);
				Event_Queue_Object_ChangeSpriteFrame(92, 1);
				Event_Queue_Object_ChangeSpriteFrame(93, 2);
			}
			else if (overworld.areaId == 28) {
				Event_Queue_Object_ChangeSpriteFrame(41, 0);
				Event_Queue_Object_ChangeSpriteFrame(42, 2);
				Event_Queue_Object_ChangeSpriteFrame(43, 1);
			}
			else if (overworld.areaId == 38) {
				Event_Queue_Object_ChangeSpriteFrame(41, 4);
				Event_Queue_Object_ChangeSpriteFrame(42, 1);
				Event_Queue_Object_ChangeSpriteFrame(43, 4);
			}
			Event_Queue_Label(10);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010014: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2030);
			Event_Queue_PlaySound(SND_voice2);
			Event_Queue_SetIntPtrToPtr(&caller->spriteFrame, &dialogSystem.optionSelected);
			Event_Queue_AddIntPtr(&caller->spriteFrame, 5);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010015: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2029);
			if (profile.flags[FLAG_SALLY_JOINED] && profile.flags[FLAG_PLOT] < 61) {
				if (profile.flags[FLAG_ALONE]) {
					Event_Queue_Dialog_Run(470);
					Event_Queue_Player_SetPositionSync(true);
					Event_Queue_SetSync(true);
					Event_Queue_Camera_MoveTo(15576, 3560, 1);
					Event_Queue_Object_WalkTo(0, 15576, 3592, 1, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(1, 15576, 3560, 1, OBJECT_DIRECTION_UP);
					Event_Queue_SetSync(false);
					Event_Queue_WaitFrames(90);
					Event_Queue_Dialog_Run(486);
					Event_Queue_Dialog_Run(487);
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_DOWN);
					Event_Queue_Dialog_Run(488);
				}
				else {
					Event_Queue_Dialog_Run(470);
					Event_Queue_Player_SetPositionSync(true);
					Event_Queue_SetSync(true);
					Event_Queue_Camera_MoveTo(15576, 3560, 1);
					Event_Queue_Object_WalkTo(0, 15576, 3592, 1, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(1, 15536, 3592, 1, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(2, 15616, 3592, 1, OBJECT_DIRECTION_UP);
					Event_Queue_Object_WalkTo(3, 15576, 3560, 1, OBJECT_DIRECTION_UP);
					Event_Queue_SetSync(false);
					Event_Queue_Dialog_Run(471);
					Event_Queue_Dialog_Run(472);
					Event_Queue_WaitFrames(90);
					Event_Queue_Dialog_Run(473);
					Event_Queue_Dialog_Run(474);
					Event_Queue_Dialog_Run(475);
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(476);
					Event_Queue_Dialog_Run(477);
					Event_Queue_Dialog_Run(478);
					Event_Queue_FadeOut(0.0625);
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(479);
					Event_Queue_Object_ChangeSpriteId(2, SPR_misc_emmet_facepalm);
					Event_Queue_FadeIn(0.0625);
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(480);
					Event_Queue_Object_ChangeSpriteId(2, SPR_owchar_emmet);
					Event_Queue_Dialog_Run(481);
					Event_Queue_Dialog_Run(482);
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_DOWN);
					Event_Queue_Dialog_Run(483);
					Event_Queue_Dialog_Run(484);
					Event_Queue_Dialog_Run(485);
				}
				Event_Queue_Object_Destroy(14);
				
				Event_Queue_Regroup(1);
				Event_Queue_SetFlag(FLAG_PLOT, 61);
				overworld.map.doors[23].enabled = true;
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010016: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(162)) {
				Event_Queue_Dialog_Run(2040);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_KeyItemRemove(162);
				Event_Queue_SetFlag(FLAG_MANSION_UNLOCKED_SILVER, 1);
				overworld.map.doors[38].enabled = true;
			}
			else {
				Event_Queue_Dialog_Run(2029);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010017: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(163)) {
				Event_Queue_Dialog_Run(2041);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_KeyItemRemove(163);
				Event_Queue_SetFlag(FLAG_MANSION_UNLOCKED_GOLD, 1);
				overworld.map.doors[30].enabled = true;
			}
			else {
				Event_Queue_Dialog_Run(2029);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010018: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(164)) {
				Event_Queue_Dialog_Run(2042);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_KeyItemRemove(164);
				Event_Queue_SetFlag(FLAG_MANSION_UNLOCKED_DIAMOND, 1);
				overworld.map.doors[27].enabled = true;
			}
			else {
				Event_Queue_Dialog_Run(2029);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010019: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(162);
			Event_Queue_Dialog_Run(4004);
			
			Event_Queue_SetFlag(FLAG_MANSION_GOTKEY_SILVER, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010020: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(164);
			Event_Queue_Dialog_Run(4004);
			
			Event_Queue_SetFlag(FLAG_MANSION_GOTKEY_DIAMOND, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010021: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2039);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010022: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2045);
			if (overworld.areaId == 38 && eventSystem.callerObjectId == 11)
				Event_Queue_Dialog_Run(2046);
			else if (overworld.areaId == 38)
				Event_Queue_Dialog_Run(2047);
			else if (overworld.areaId == 28)
				Event_Queue_Dialog_Run(2048);
			else if (overworld.areaId == 24)
				Event_Queue_Dialog_Run(2049);
			else if (overworld.areaId == 22)
				Event_Queue_Dialog_Run(2050);
			else
				Event_Queue_Dialog_Run(2051);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010023: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2035);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010024: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2036);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010025: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2037);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010026: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2038);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010027: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2052);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010028: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(167)) {
				Event_Queue_Dialog_Run(645);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_SetFlag(FLAG_RCCLUB_DISCO_UNLOCKED, 1);
				overworld.map.doors[62].enabled = true;
			}
			else if (Profile_KeyItemExists(166)) {
				if (profile.flags[FLAG_RCCLUB_PLOT] <= 107) {
					Event_Queue_Dialog_Run(640);
					Event_Queue_WaitFrames(80);
					if (profile.flags[FLAG_ALONE]) {
						Event_Queue_Dialog_Run(646);
					}
					else {
						Event_Queue_Dialog_Run(641);
						Event_Queue_Dialog_Run(642);
						Event_Queue_Dialog_Run(643);
						Event_Queue_Dialog_Run(644);
					}
					Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 108);
				}
				else {
					Event_Queue_Dialog_Run(2075);
				}
			}
			else {
				Event_Queue_Dialog_Run(2075);
				if (profile.flags[FLAG_RCCLUB_PLOT] <= 104) {
					if (!profile.flags[FLAG_ALONE]) {
						Event_Queue_Dialog_Run(623);
						Event_Queue_Dialog_Run(470);
						Event_Queue_SetSync(true);
						Event_Queue_Object_WalkTo(0, 20392, 10008, 1, OBJECT_DIRECTION_LEFT);
						Event_Queue_Object_WalkTo(1, 20408, 9992, 1, OBJECT_DIRECTION_LEFT);
						Event_Queue_Object_WalkTo(2, 20408, 10024, 1, OBJECT_DIRECTION_LEFT);
						Event_Queue_Object_WalkTo(3, 20360, 10032, 1, OBJECT_DIRECTION_UP);
						Event_Queue_SetSync(false);
						Event_Queue_WaitFrames(50);
						Event_Queue_Object_WalkTo(3, 20360, 9984, 3, OBJECT_DIRECTION_UP);
						Event_Queue_PlaySound(SND_hit1);
						Event_Queue_WaitFrames(70);
						Event_Queue_Object_WalkTo(3, 20360, 10008, 0.5, OBJECT_DIRECTION_DOWN);
						Event_Queue_Dialog_Run(624);
						Event_Queue_Dialog_Run(628);
						
						Event_Queue_Regroup(1);
					}
					Event_Queue_SetFlag(FLAG_RCCLUB_PLOT, 105);
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010029: {
			if (profile.flags[FLAG_PLOT] == 119 && profile.flags[FLAG_AZURETOPHOTEL_COMPUTER_STATUS] == 0) {
				Event_Trigger(53);
			}
		} break;
		
		case 1010030: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2098);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR]);
			Event_Queue_JumpIfEqual(1);
				Event_Queue_SetIntPtrToPtr(&profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR], &dialogSystem.optionSelected);
				Event_Queue_SetBoolPtr(&overworld.map.doors[68].enabled, false);
				Event_Queue_SetBoolPtr(&overworld.map.doors[69].enabled, false);
				Event_Queue_SetBoolPtr(&overworld.map.doors[70].enabled, false);
				
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(10);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(11);
				Event_Queue_Jump(12);
				
				Event_Queue_Label(10);
					Event_Queue_SetBoolPtr(&overworld.map.doors[68].enabled, true);
					Event_Queue_Jump(2);
				Event_Queue_Label(11);
					Event_Queue_SetBoolPtr(&overworld.map.doors[69].enabled, true);
					Event_Queue_Jump(2);
				Event_Queue_Label(12);
					Event_Queue_SetBoolPtr(&overworld.map.doors[70].enabled, true);
					Event_Queue_Jump(2);
				
				Event_Queue_Label(2);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_WaitFrames(10);
				Event_Queue_PlaySound(SND_elevator);
				Event_Queue_WaitFrames(60);
				Event_Queue_PlaySound(SND_chess_mate);
				Event_Queue_WaitFrames(30);
				Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2100);
			Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010031: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(168);
			Event_Queue_Dialog_Run(4004);
			
			Event_Queue_SetFlag(FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS, profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] | 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010032: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(169);
			Event_Queue_Dialog_Run(4004);
			
			Event_Queue_SetFlag(FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS, profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] | 2);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010033: {
			if ((profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] & 4) > 0) {
				
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				if (Profile_KeyItemExists(168) && Profile_KeyItemExists(169)) {
					Event_Queue_Dialog_Run(2113);
					Event_Queue_Object_ChangeSpriteFrame(eventSystem.callerObjectId, 1);
					Event_Queue_Profile_KeyItemRemove(168);
					Event_Queue_Profile_KeyItemRemove(169);
					Event_Queue_SetFlag(FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS, profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] | 4);
					overworld.map.doors[235].enabled = true;
				}
				else {
					Event_Queue_Dialog_Run(2174);
				}
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010034: {
			if (!profile.flags[FLAG_ALONE]) {
				//Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				//Event_Queue_Dialog_Run(2120);
				//Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Dialog_Run(2121);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				Event_Queue_Exit();
				
				Event_Queue_Label(0);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_TeleportTo(12, 10366, 8278);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_TeleportTo(12, 10370, 8284);
				Event_Queue_WaitFrames(7);
				Event_Queue_Object_TeleportTo(12, 10372, 8288);
				
				Event_Queue_Object_ChangeSpriteFrame(12, 1);
				Event_Queue_PlaySound(SND_burn);
				Event_Queue_WaitFrames(60);
				
				Event_Queue_Object_WalkTo(11, 10424, 8216, 3, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(277);
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_CreateObject(70, 1, SPR_owchar_jackie, 10104, 8248, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(70, 10392, 8248, 12, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_WalkTo(70, 10408, 8232, 12, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(10, 10232, 8152, OBJECT_DIRECTION_DOWN, 20, 4);
				Event_Queue_Object_WalkTo(10, 10360, 8152, 12, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkTo(10, 10392, 8216, 12, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_TeleportTo(0, 10392, 8280);
				Event_Queue_Camera_TeleportTo(10408, 8272);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				Event_Queue_Dialog_Run(278);
				Event_Queue_Dialog_Run(284);
				Event_Queue_Dialog_Run(285);
				
				Event_Queue_Object_DisableFighterSprite(70);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(4);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteId(10, SPR_owchar_electra);
				Event_Queue_PlaySound(SND_mana);
				Event_Queue_Overworld_FadeIn(1, 255, 255, 255);
				Event_Queue_WaitFrames(2);
				Event_Queue_Overworld_FadeOut(1, 255, 255, 255);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(286);
				Event_Queue_EngageBattle(20, 70);
				
				Event_Queue_Object_Destroy(12);
				Event_Queue_Dialog_Run(287);
				Event_Queue_Dialog_Run(288);
				Event_Queue_Dialog_Run(289);
				Event_Queue_Dialog_Run(290);
				Event_Queue_Object_WalkToPointer(70, 32, 0, 1, OBJECT_DIRECTION_LEFT, &overworld.objects[0].x, &overworld.objects[0].y);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_SPECIAL1);
				Event_Queue_Dialog_Run(293);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
				Event_Queue_Dialog_Run(294);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(295);
				Event_Queue_WaitFrames(60);
				Event_Queue_Object_DisableFighterSprite(70);
				Event_Queue_Dialog_Run(296);
				Event_Queue_Dialog_Run(291);
				Event_Queue_Object_EnableFighterSprite(70, 23, 23, FIGHTER_STATE_BLOCK);
				Event_Queue_Dialog_Run(292);
				Event_Queue_Object_DisableFighterSprite(70);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(70, 10104, 8248, 2, -1);
				Event_Queue_Object_WalkTo(10, 10488, 8112, 2, -1);
				Event_Queue_Object_WalkTo(11, 10424, 8192, 2, -1);
				Event_Queue_Object_QueueWalkTo(11, 10512, 8144, 2, OBJECT_DIRECTION_DOWN);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(70);
				Event_Queue_CreateNPC(10, 4, 10232, 8128, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_Regroup(1);
				Event_Queue_SetFlag(FLAG_PLOT, 54);
				Event_Queue_SetFlag(FLAG_JACKIECAFE_BROKENGLASS, 1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010035: {
			overworld.map.triggers[2].eventId = 0;
			overworld.map.triggers[3].eventId = 0;
			overworld.map.triggers[4].eventId = 0;
			overworld.map.triggers[5].eventId = 0;
			overworld.map.triggers[6].eventId = 0;
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Camera_TogglePlayerFollow(true);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_FadeOutMusic(2000);
			Event_Queue_Object_WalkTo(0, 9336, 9728, 2, OBJECT_DIRECTION_UP);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_Destroy(73);
			Event_Queue_Object_JumpTo(70, 9352, 9736, OBJECT_DIRECTION_DOWN, 20, 30);
			Event_Queue_Object_DisableFighterSprite(70);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_collapse_sally);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_WaitFrames(60);
			Event_Queue_Dialog_Run(705);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_sally);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(706);
			Event_Queue_WaitFrames(60);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_sally_serious);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Dialog_Run(707);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Party_Join(3);
			Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[70].x, &overworld.objects[70].y);
			
			Event_Queue_Regroup(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010036: {
			if (profile.flags[FLAG_PLOT] == 119) {
				if (profile.flags[FLAG_AZURETOPHOTEL_COMPUTER_STATUS] == 0) {
					Event_Trigger(53);
				}
				else {
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
					Event_Queue_FadeOutMusic(1500);
					Event_Queue_Dialog_Run(3063);
					Event_Queue_Overworld_FadeIn(120, 255, 255, 255);
					Event_Queue_WaitFrames(30);
					Event_Queue_PlaySound(SND_encounter);
					Event_Queue_WaitFrames(90);
					Event_Queue_GotoArea(239, 1960, 14392, -1);
					Event_Queue_WaitFrames(60);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
					Event_Queue_Dialog_Run(2172);
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
					Event_Queue_Dialog_Run(2173);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_SetFlag(FLAG_PLOT, 120);
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				}
			}
		} break;
		
		case 1010039: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_PlaySound(SND_heal);
			Event_Queue_FullyHealParty();
			Event_Queue_Dialog_Run(3123);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010040: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(3);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_ItemAdd(3);
				Event_Queue_Dialog_Run(4004);
				switch (overworld.areaId) {
					case 6: Event_Queue_SetFlag(FLAG_ITEM_TOWN_HEAL, 1); break;
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010041: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(23);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_ItemAdd(23);
				Event_Queue_Dialog_Run(4004);
				switch (overworld.areaId) {
					case 0: Event_Queue_SetFlag(FLAG_ITEM_LEAFCREW_HEAL_B, 1); break;
					case 103: Event_Queue_SetFlag(FLAG_ITEM_LAPISPEAKS_HEAL_B, 1); break;
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010042: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(24);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_ItemAdd(24);
				Event_Queue_Dialog_Run(4004);
				switch (overworld.areaId) {
					//case 0: Event_Queue_SetFlag(FLAG_ITEM_LEAFCREW_TOMATOSOUP, 1); break;
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010043: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (caller->spriteFrame > 0) {
				Event_Queue_Dialog_Run(2189);
			}
			else {
				Event_Queue_Object_ChangeSpriteFrame(eventSystem.callerObjectId, 1);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Dialog_Run(2184);
				if (caller->vars[7].i >= 160) {
					Event_Queue_Profile_KeyItemAdd(caller->vars[7].i);
					Event_Queue_Dialog_Run(4004);
					switch (overworld.areaId) {
						case 150: Event_Queue_SetFlag(FLAG_PLOT, 251); break;
					}
				}
				else if (Profile_ItemInventoryIsFull()) {
					Event_Queue_Profile_ItemAdd(caller->vars[7].i);
					Event_Queue_Dialog_Run(4005);
					Event_Queue_Object_ChangeSpriteFrame(eventSystem.callerObjectId, 0);
				}
				else {
					Event_Queue_Profile_ItemAdd(caller->vars[7].i);
					Event_Queue_Dialog_Run(4004);
					switch (overworld.areaId) {
						case 0: Event_Queue_SetFlag(FLAG_ITEM_VILLAGE_GREENTEA, 1); break;
						case 6: Event_Queue_SetFlag(eventSystem.callerObjectId == 51 ? FLAG_ITEM_TOWN_POWER : FLAG_ITEM_TOWN_ENERGYDRINK, 1); break;
						case 100: Event_Queue_SetFlag(FLAG_ITEM_LAPISDESERT_BOMB_B, 1); break;
						case 116: Event_Queue_SetFlag(FLAG_ITEM_LAPISDESERT_ENERGYDRINK, 1); break;
						case 117: Event_Queue_SetFlag(FLAG_ITEM_LAPISDESERT_BRIAN_CASE, 1); break;
						case 122: Event_Queue_SetFlag(FLAG_ITEM_SECRETBUNKER_ONYXMEAL, 1); break;
						case 150:
							if (eventSystem.callerObjectId == 51)
								Event_Queue_SetFlag(FLAG_ITEM_SAPPHIREPOLIS_ALONE_MEDKIT, 1);
							else if (eventSystem.callerObjectId == 52)
								Event_Queue_SetFlag(FLAG_ITEM_SAPPHIREPOLIS_ALONE_HEAL_G, 1);
							else
								Event_Queue_SetFlag(FLAG_ITEM_SAPPHIREPOLIS_ALONE_MEDKIT_1, 1);
							break;
					}
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010044: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(171);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_SetFlag(FLAG_ITEM_LAPISDESERT_MYSTERYKEY, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010045: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(171)) {
				Event_Queue_Dialog_Run(2252);
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_SetFlag(FLAG_LAPISDESERT_SECRETBUNKER_UNLOCKED, 1);
				overworld.map.doors[112].enabled = true;
			}
			else {
				Event_Queue_Dialog_Run(2029);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010046: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(172);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_SetFlag(FLAG_ITEM_SECRETBUNKER_CARD, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010047: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_KeyItemExists(172) && !profile.flags[FLAG_NEKIN_OPTIONALFIGHT]) {
				Event_Queue_Dialog_Run(2225);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(0);
				
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_WaitFrames(40);
				Event_Queue_PlaySound(SND_chess_mate);
				Event_Queue_WaitFrames(30);
				Event_Queue_FadeOutMusic(2000);
				Event_Queue_PlaySound(SND_elevator);
				Event_Queue_Object_ToggleGhost(10, true);
				
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkToRelative(10, 0, -64, 0.5, -1);
				Event_Queue_WaitFrames(40);
				Event_Queue_Camera_MoveTo(19272, 14816, 1);
				Event_Queue_Object_WalkTo(0, 19272, 14824, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(1, 19240, 14856, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(2, 19304, 14856, 1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_WalkTo(3, 19272, 14888, 1, OBJECT_DIRECTION_UP);
				Event_Queue_SetSync(false);
				Event_Queue_Object_Destroy(10);
				Event_Queue_WaitFrames(90);
				Event_Queue_CreateObject(70, 1, SPR_owchar_nekin, 19272, 14756, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ToggleGhost(70, true);
				Event_Queue_Object_SetColor(70, 0, 0, 0);
				Event_Queue_Object_WalkTo(70, 19272, 14784, 0.25, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ToggleGhost(70, false);
				Event_Queue_WaitFrames(30);
				Event_Queue_Dialog_Run(2226);
				Event_Queue_Object_SetColor(70, 63, 63, 63);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_SetColor(70, 159, 159, 159);
				Event_Queue_WaitFrames(20);
				Event_Queue_Object_SetColor(70, 255, 255, 255);
				Event_Queue_WaitFrames(20);
				Event_Queue_Dialog_Run(2227);
				Event_Queue_Dialog_Run(2228);
				if (profile.flags[FLAG_ALONE]) {
					Event_Queue_Dialog_Run(2275);
					Event_Queue_WaitFrames(55);
					Event_Queue_Dialog_Run(2276);
					Event_Queue_Dialog_Run(2277);
					Event_Queue_Dialog_Run(2278);
					Event_Queue_PlayMusic(MUS_oh);
					Event_Queue_Object_WalkToRelative(0, 0, -8, 0.125, OBJECT_DIRECTION_UP);
					Event_Queue_WaitFrames(40);
					Event_Queue_Dialog_Run(2279);
					Event_Queue_Dialog_Run(2280);
					Event_Queue_Object_ChangeSpriteId(70, SPR_misc_nekin_prepare);
					Event_Queue_Object_ChangeSpriteFrame(70, 0);
					Event_Queue_WaitFrames(46);
					Event_Queue_Dialog_Run(2281);
					
					Event_Queue_EngageBattle(72, 70);
					Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_collapse_nekin);
					Event_Queue_Object_ChangeSpriteFrame(70, 1);
					Event_Queue_Object_SetCollisionSize(70, 14, 8);
					Event_Queue_Object_TeleportTo(0, 19272, 14840);
					Event_Queue_CreateObject(71, 1, SPR_misc_collapseblood, 19272, 14783, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeSpriteFrame(71, 1);
					Event_Queue_WaitFrames(90);
				}
				else {
					Event_Queue_Dialog_Run(2229);
					Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Dialog_Run(2230);
					Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
					Event_Queue_Dialog_Run(2231);
					Event_Queue_Dialog_Run(2232);
					Event_Queue_Dialog_Run(2233);
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
					Event_Queue_Dialog_Run(2234);
					Event_Queue_WaitFrames(20);
					Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_RIGHT);
					Event_Queue_WaitFrames(20);
					Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
					Event_Queue_WaitFrames(20);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_Dialog_Run(2235);
					Event_Queue_Dialog_Run(2236);
					Event_Queue_Dialog_Run(2237);
					Event_Queue_PlayMusic(MUS_oh);
					Event_Queue_Object_WalkTo(70, 19272, 14792, 0.125, OBJECT_DIRECTION_DOWN);
					Event_Queue_WaitFrames(40);
					Event_Queue_Object_ChangeSpriteId(70, SPR_misc_nekin_prepare);
					Event_Queue_Object_ChangeSpriteFrame(70, 0);
					Event_Queue_WaitFrames(50);
					Event_Queue_Dialog_Run(2238);
					Event_Queue_Dialog_Run(2239);
					Event_Queue_Dialog_Run(2240);
					Event_Queue_Dialog_Run(2241);
					Event_Queue_Dialog_Run(2242);
					
					Event_Queue_EngageBattle(72, 70);
					Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_collapse_nekin);
					Event_Queue_Object_ChangeSpriteFrame(70, 1);
					Event_Queue_Object_TeleportTo(0, 19272, 14840);
					
					Event_Queue_WaitFrames(60);
					Event_Queue_Dialog_Run(2243);
					Event_Queue_Dialog_Run(2244);
					Event_Queue_Dialog_Run(2245);
					Event_Queue_Dialog_Run(2246);
					Event_Queue_Dialog_Run(2247);
					Event_Queue_Object_ChangeSpriteId(70, SPR_owchar_nekin);
					Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_DOWN);
					Event_Queue_PlaySound(SND_slap);
					Event_Queue_FadeOutMusic(2000);
					Event_Queue_WaitFrames(40);
					Event_Queue_Dialog_Run(2248);
					Event_Queue_Object_WalkTo(70, 19320, 14808, 3, -1);
					Event_Queue_Object_WalkTo(70, 19416, 14872, 3, -1);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_WalkTo(70, 19432, 14712, 3, -1);
					Event_Queue_Object_WalkTo(70, 19536, 14696, 3, -1);
					Event_Queue_Object_Destroy(70);
					Event_Queue_WaitFrames(30);
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
					Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
					Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
					Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_shrug);
					Event_Queue_Dialog_Run(2249);
					Event_Queue_Dialog_Run(2250);
					Event_Queue_Dialog_Run(2251);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				}
				
				Event_Queue_Regroup(1);
				Event_Queue_SetFlag(FLAG_NEKIN_OPTIONALFIGHT, 1);
				
				Event_Queue_Label(0);
			}
			else {
				Event_Queue_Dialog_Run(2224);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010049: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2254);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(0);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(17);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Profile_ItemAdd(17);
				Event_Queue_Dialog_Run(4004);
			}
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010051: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2282);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010052: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2292);
			Event_Queue_Dialog_Run(2293);
			Event_Queue_Dialog_Run(2294);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010053: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Profile_ItemInventoryIsFull()) {
				Event_Queue_Profile_ItemAdd(27);
				Event_Queue_Dialog_Run(4005);
			}
			else {
				Event_Queue_Object_Destroy(eventSystem.callerObjectId);
				Event_Queue_Profile_ItemAdd(27);
				Event_Queue_Dialog_Run(4004);
				switch (overworld.areaId) {
					case 0: Event_Queue_SetFlag(FLAG_ITEM_VILLAGE_DANDELION, 1); break;
					case 26: Event_Queue_SetFlag(FLAG_ITEM_MANSION_DANDELION, 1); break;
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010054: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2328);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR]);
			Event_Queue_JumpIfEqual(1);
			Event_Queue_SaveToVarInt(0, &profile.flags[FLAG_AMPERCORP_FLOORS_UNLOCKED]);
			Event_Queue_AddIntPtr(&eventSystem.vars[0].i, 1);
			Event_Queue_CompareIntToVar(&dialogSystem.optionSelected, &eventSystem.vars[0].i);
			Event_Queue_JumpIfGreater(40);
			if (profile.flags[FLAG_ALONE]) {
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 2);
				Event_Queue_JumpIfEqual(40);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 3);
				Event_Queue_JumpIfEqual(40);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 4);
				Event_Queue_JumpIfEqual(40);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 5);
				Event_Queue_JumpIfEqual(40);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 6);
				Event_Queue_JumpIfEqual(40);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 7);
				Event_Queue_JumpIfEqual(40);
			}
			
			Event_Queue_SetIntPtrToPtr(&profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR], &dialogSystem.optionSelected);
			Event_Queue_SetBoolPtr(&overworld.map.doors[124].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[125].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[126].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[127].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[128].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[129].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[186].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[189].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[130].enabled, false);
			Event_Queue_SetBoolPtr(&overworld.map.doors[131].enabled, false);
			
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(10);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(11);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 2);
			Event_Queue_JumpIfEqual(12);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 3);
			Event_Queue_JumpIfEqual(13);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 4);
			Event_Queue_JumpIfEqual(14);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 5);
			Event_Queue_JumpIfEqual(15);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 6);
			Event_Queue_JumpIfEqual(16);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 7);
			Event_Queue_JumpIfEqual(17);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 8);
			Event_Queue_JumpIfEqual(18);
			Event_Queue_Jump(19);
			
			Event_Queue_Label(10);
				Event_Queue_SetBoolPtr(&overworld.map.doors[124].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(11);
				Event_Queue_SetBoolPtr(&overworld.map.doors[125].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(12);
				Event_Queue_SetBoolPtr(&overworld.map.doors[126].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(13);
				Event_Queue_SetBoolPtr(&overworld.map.doors[127].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(14);
				Event_Queue_SetBoolPtr(&overworld.map.doors[128].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(15);
				Event_Queue_SetBoolPtr(&overworld.map.doors[129].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(16);
				Event_Queue_SetBoolPtr(&overworld.map.doors[186].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(17);
				Event_Queue_SetBoolPtr(&overworld.map.doors[189].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(18);
				Event_Queue_SetBoolPtr(&overworld.map.doors[130].enabled, true);
				Event_Queue_Jump(2);
			Event_Queue_Label(19);
				Event_Queue_SetBoolPtr(&overworld.map.doors[131].enabled, true);
				Event_Queue_Jump(2);
			
			Event_Queue_Label(2);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_WaitFrames(10);
			Event_Queue_PlaySound(SND_elevator);
			Event_Queue_WaitFrames(60);
			Event_Queue_PlaySound(SND_chess_mate);
			Event_Queue_WaitFrames(30);
			Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2100);
				Event_Queue_Jump(0);
			Event_Queue_Label(40);
				Event_Queue_PlaySound(SND_error);
				Event_Queue_Dialog_Run(2669);
			Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010055: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_DISABLED]) {
				Event_Queue_Dialog_Run(2350);
			}
			else {
				Event_Queue_Dialog_Run(2336);
			}
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(0);
			
			Event_Queue_PlaySound(SND_voice2);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TeleportTo(19496, 15576);
			Event_Queue_Object_TeleportTo(0, caller->x, caller->y + 16);
			Event_Queue_Object_TeleportTo(1, caller->x - 32, caller->y + 16);
			Event_Queue_Object_TeleportTo(2, caller->x - 64, caller->y + 16);
			Event_Queue_Object_TeleportTo(3, caller->x - 96, caller->y + 16);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
			Event_Queue_Object_ChangeDirection(3, OBJECT_DIRECTION_UP);
			Event_Queue_WaitFrames(15);
			Event_Queue_SetVarInt(0, 0);
			Event_Queue_CustomAction(5);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_WaitFrames(4);
			Event_Queue_CustomAction(5);
			Event_Queue_PlaySound(SND_sawkill);
			Event_Queue_CustomAction(5);
			Event_Queue_WaitFrames(25);
			Event_Queue_Dialog_Run(2337);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Camera_TeleportTo(overworld.camera.x, overworld.camera.y);
			Event_Queue_Object_TeleportTo(0, overworld.objects[0].x, overworld.objects[0].y);
			Event_Queue_Object_TeleportTo(1, overworld.objects[1].x, overworld.objects[1].y);
			Event_Queue_Object_TeleportTo(2, overworld.objects[2].x, overworld.objects[2].y);
			Event_Queue_Object_TeleportTo(3, overworld.objects[3].x, overworld.objects[3].y);
			Event_Queue_Object_ChangeDirection(0, overworld.objects[0].direction);
			Event_Queue_Object_ChangeDirection(1, overworld.objects[1].direction);
			Event_Queue_Object_ChangeDirection(2, overworld.objects[2].direction);
			Event_Queue_Object_ChangeDirection(3, overworld.objects[3].direction);
			Event_Queue_WaitFrames(15);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010056: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2098);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, profile.flags[FLAG_WHITELIGHT_ELEVATOR_FLOOR]);
			Event_Queue_JumpIfEqual(1);
				Event_Queue_SetIntPtrToPtr(&profile.flags[FLAG_WHITELIGHT_ELEVATOR_FLOOR], &dialogSystem.optionSelected);
				Event_Queue_SetBoolPtr(&overworld.map.doors[171].enabled, false);
				Event_Queue_SetBoolPtr(&overworld.map.doors[172].enabled, false);
				Event_Queue_SetBoolPtr(&overworld.map.doors[173].enabled, false);
				
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(10);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(11);
				Event_Queue_Jump(12);
				
				Event_Queue_Label(10);
					Event_Queue_SetBoolPtr(&overworld.map.doors[171].enabled, true);
					Event_Queue_Jump(2);
				Event_Queue_Label(11);
					Event_Queue_SetBoolPtr(&overworld.map.doors[172].enabled, true);
					Event_Queue_Jump(2);
				Event_Queue_Label(12);
					Event_Queue_SetBoolPtr(&overworld.map.doors[173].enabled, true);
					Event_Queue_Jump(2);
				
				Event_Queue_Label(2);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_WaitFrames(10);
				Event_Queue_PlaySound(SND_elevator);
				Event_Queue_WaitFrames(60);
				Event_Queue_PlaySound(SND_chess_mate);
				Event_Queue_WaitFrames(30);
				Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2100);
			Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010057: {
			if (caller->vars[7].i == 1) {
				OverworldObject_Destroy(70);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Camera_TogglePlayerFollow(true);
				Event_Queue_Object_SetColor(eventSystem.callerObjectId, 0, 255, 0);
				Event_Queue_PlaySound(SND_chess_mate);
				Event_Queue_StopMusic();
				if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] >= 5) {
					Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_DOWN);
					if (overworld.objects[71].x < 18864) {
						Event_Queue_Object_JumpTo(71, 18784, 15824, OBJECT_DIRECTION_DOWN, 24, 26);
					}
					else {
						Event_Queue_Object_JumpTo(71, 18944, 15824, OBJECT_DIRECTION_DOWN, 24, 26);
					}
					Event_Queue_Object_Destroy(71);
				}
				Event_Queue_WaitFrames(30);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Object_TeleportTo(10, caller->x, caller->y);
				if (caller->vars[6].i == OBJECT_DIRECTION_RIGHT) {
					Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
					Event_Queue_SetSync(true);
					Event_Queue_Object_JumpToRelative(10, 8, 0, OBJECT_DIRECTION_RIGHT, 8, 12);
					Event_Queue_Object_WalkToRelative(0, 18, 0, 4, OBJECT_DIRECTION_LEFT);
					Event_Queue_SetSync(false);
				}
				else if (caller->vars[6].i == OBJECT_DIRECTION_LEFT) {
					Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_LEFT);
					Event_Queue_SetSync(true);
					Event_Queue_Object_JumpToRelative(10, -8, 0, OBJECT_DIRECTION_LEFT, 8, 12);
					Event_Queue_Object_WalkToRelative(0, -18, 0, 4, OBJECT_DIRECTION_RIGHT);
					Event_Queue_SetSync(false);
				}
				else if (caller->vars[6].i == OBJECT_DIRECTION_DOWN) {
					Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
					Event_Queue_SetSync(true);
					Event_Queue_Object_JumpToRelative(10, 0, 16, OBJECT_DIRECTION_DOWN, 8, 12);
					Event_Queue_Object_WalkToRelative(0, 0, 18, 4, OBJECT_DIRECTION_UP);
					Event_Queue_SetSync(false);
				}
				else {
					Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_UP);
					Event_Queue_SetSync(true);
					Event_Queue_Object_JumpToRelative(10, 0, -8, OBJECT_DIRECTION_UP, 8, 12);
					Event_Queue_Object_WalkToRelative(0, 0, -18, 4, OBJECT_DIRECTION_DOWN);
					Event_Queue_SetSync(false);
				}
				Event_Queue_WaitFrames(10);
				Event_Queue_Dialog_Run(2343);
				Event_Queue_WaitFrames(60);
				
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] >= 5) {
					Event_Queue_Party_Join(3);
				}
				Event_Queue_Camera_TeleportTo(18864, 15676);
				Event_Queue_Object_TeleportTo(0, 18864, 15760);
				Event_Queue_Object_TeleportTo(1, 18864, 15760);
				Event_Queue_Object_TeleportTo(2, 18864, 15760);
				Event_Queue_Object_TeleportTo(3, 18864, 15760);
				Event_Queue_Object_TeleportTo(10, 18864, 15656);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_WalkToRelative(0, 0, -80, 3, OBJECT_DIRECTION_UP);
				for (int i = 0; i < 70; i++) {
					Event_Queue_Object_TeleportTo(160 + i, overworld.objects[160 + i].x, overworld.objects[160 + i].y - 1000);
				}
				Event_Queue_Regroup(3);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				Event_Queue_PlayMusic(MUS_whitelight);
				Event_Queue_Dialog_Run(2344);
				Event_Queue_Profile_KeyItemAdd(175);
				Event_Queue_Dialog_Run(4004);
				Event_Queue_Dialog_Run(2345);
				Event_Queue_SetSync(true);
				Event_Queue_Object_WalkTo(10, 18864, 15696, 3, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_QueueWalkTo(10, 18944, 15824, 3, OBJECT_DIRECTION_DOWN);
				Event_Queue_Dialog_Run(2346);
				Event_Queue_WaitFrames(32);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(25);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_Destroy(10);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(57);
				Event_Queue_Dialog_Run(2347);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(1, OBJECT_DIRECTION_UP);
				Event_Queue_Object_ChangeDirection(2, OBJECT_DIRECTION_UP);
				Event_Queue_Dialog_Run(2348);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
				
				Event_Queue_SetBoolPtr(&overworld.map.doors[174].enabled, true);
				Event_Queue_SetBoolPtr(&overworld.map.doors[175].enabled, true);
				
				Event_Queue_SetFlag(FLAG_WHITELIGHT_PLOT, 2);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Object_ChangeSpriteId(eventSystem.callerObjectId, SPR_misc_guide_cross);
				Event_Queue_Object_SetColor(eventSystem.callerObjectId, 255, 0, 0);
				Event_Queue_PlaySound(SND_chess_wrong);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010058: {
			if (profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_DISABLED] == 0) {
				for (int i = 0; i < 60; i++) {
					overworld.map.triggers[i].eventId = 0;
				}
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_PlaySound(SND_nerf);
				Event_Queue_Dialog_Run(2349);
				Event_Queue_SetFlag(FLAG_WHITELIGHT_ELECTROFLOOR_DISABLED, 1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010059: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Profile_KeyItemAdd(174);
			Event_Queue_Dialog_Run(4004);
			Event_Queue_SetFlag(FLAG_WHITELIGHT_PLOT, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010061: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2364);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, profile.flags[FLAG_SAPPHIREHOTEL_ELEVATOR_FLOOR]);
			Event_Queue_JumpIfEqual(1);
				Event_Queue_SetIntPtrToPtr(&profile.flags[FLAG_SAPPHIREHOTEL_ELEVATOR_FLOOR], &dialogSystem.optionSelected);
				Event_Queue_SetBoolPtr(&overworld.map.doors[179].enabled, false);
				Event_Queue_SetBoolPtr(&overworld.map.doors[180].enabled, false);
				Event_Queue_SetBoolPtr(&overworld.map.doors[181].enabled, false);
				
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
				Event_Queue_JumpIfEqual(10);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(11);
				Event_Queue_Jump(12);
				
				Event_Queue_Label(10);
					Event_Queue_SetBoolPtr(&overworld.map.doors[179].enabled, true);
					Event_Queue_Jump(2);
				Event_Queue_Label(11);
					Event_Queue_SetBoolPtr(&overworld.map.doors[180].enabled, true);
					Event_Queue_Jump(2);
				Event_Queue_Label(12);
					Event_Queue_SetBoolPtr(&overworld.map.doors[181].enabled, true);
					Event_Queue_Jump(2);
				
				Event_Queue_Label(2);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_WaitFrames(10);
				Event_Queue_PlaySound(SND_elevator);
				Event_Queue_WaitFrames(60);
				Event_Queue_PlaySound(SND_chess_mate);
				Event_Queue_WaitFrames(30);
				Event_Queue_Jump(0);
			
			Event_Queue_Label(1);
				Event_Queue_Dialog_Run(2100);
			Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010065: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_Dialog_Run(2391);
			Event_Queue_SetFlag(FLAG_AMPERCORP_FLOORS_UNLOCKED, 3);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010066: {
			if (eventSystem.callerObjectId == 17) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				
				Event_Queue_PlaySound(SND_amper_feedback);
				Event_Queue_Camera_MoveTo(29152, 14064, 16);
				
				float yAdd = 0;
				if (overworld.objects[85 + 34].y < 13648) {
					if (overworld.objects[85 + 48].vars[0].i == OBJECT_DIRECTION_DOWN) {
						overworld.objects[85 + 48].vars[0].i = OBJECT_DIRECTION_UP;
						Event_Queue_PlaySound(SND_elevator);
						Event_Queue_Object_JumpToRelative(85 + 48, 0, 112, -1, 0, 60);
						yAdd = 112;
					}
				}
				else {
					if (overworld.objects[85 + 34].vars[0].i == OBJECT_DIRECTION_DOWN) {
						overworld.objects[85 + 34].vars[0].i = OBJECT_DIRECTION_UP;
						Event_Queue_PlaySound(SND_elevator);
						Event_Queue_SetSync(true);
						Event_Queue_Object_JumpToRelative(85 + 34, 0, 112, -1, 0, 60);
						Event_Queue_Object_JumpToRelative(85 + 35, 0, 112, -1, 0, 60);
						Event_Queue_SetSync(false);
						yAdd = 112;
					}
				}
				
				Event_Queue_WaitFrames(10);
				Event_Queue_PlaySound(SND_slap);
				Event_Queue_Overworld_ShakeScreen(6);
				if (overworld.objects[85 + 48].y < 13648) {
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 48].y, overworld.objects[85 + 48].y + 1000);
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 49].y, overworld.objects[85 + 49].y + 1000);
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 34].y, overworld.objects[85 + 34].y - 1000 + yAdd);
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 35].y, overworld.objects[85 + 35].y - 1000 + yAdd);
				}
				else {
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 48].y, overworld.objects[85 + 48].y - 1000 + yAdd);
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 49].y, overworld.objects[85 + 49].y - 1000);
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 34].y, overworld.objects[85 + 34].y + 1000);
					Event_Queue_SetFloatPtr(&overworld.objects[85 + 35].y, overworld.objects[85 + 35].y + 1000);
				}
				Event_Queue_WaitFrames(15);
				
				Event_Queue_Regroup(16);
				
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				break;
			}
			
			int objectId[4] = { 0, 0, 0, 0 };
			int direction = -1;
			switch (eventSystem.callerObjectId) {
				case 10:
					objectId[0] = 85 + 4+8 *14;
					objectId[1] = 85 + 3+8 *14;
					direction = OBJECT_DIRECTION_LEFT;
					break;
				case 11:
					objectId[0] = 85 + 1+7 *14;
					direction = OBJECT_DIRECTION_LEFT;
					break;
				
				case 13:
					objectId[0] = 85 + 0+5 *14;
					objectId[1] = 85 + 0+4 *14;
					objectId[2] = 85 + 0+3 *14;
					if (overworld.objects[objectId[0]].vars[0].i != overworld.objects[objectId[2]].vars[0].i)
						objectId[2] = 0;
					direction = OBJECT_DIRECTION_DOWN;
					break;
				case 14:
					objectId[0] = 85 + 0+3 *14;
					direction = OBJECT_DIRECTION_UP;
					if (overworld.objects[85 + 0+5 *14].vars[0].i != OBJECT_DIRECTION_UP)
						direction = -1;
					break;
				case 15:
					objectId[0] = 85 + 1+1 *14;
					objectId[1] = 85 + 1+2 *14;
					direction = OBJECT_DIRECTION_RIGHT;
					break;
				case 16:
					objectId[0] = 85 + 6+3 *14;
					if (overworld.objects[objectId[0]].y < 13648) {
						objectId[0] = 85 + 6+2 *14;
						objectId[1] = 85 + 7+2 *14;
					}
					direction = OBJECT_DIRECTION_UP;
					break;
			}
			if (direction >= 0 && overworld.objects[objectId[0]].vars[0].i >= 0) {
				direction = overworld.objects[objectId[0]].vars[0].i;
			}
			
			/*for (int i = 0; i < 4; i++) {
				if (objectId[i] == 0) break;
				
				float x = 0, y = 0;
				switch (direction) {
					case OBJECT_DIRECTION_LEFT: x = -80; break;
					case OBJECT_DIRECTION_RIGHT: x = 80; break;
					case OBJECT_DIRECTION_UP: y = -112; break;
					case OBJECT_DIRECTION_DOWN: y = 112; break;
				}
				
				for (int j = 85; j < 85 + 168; j++) {
					if (overworld.objects[j].type == 0 || j == objectId[i]) continue;
					
					float x1 = overworld.objects[j].x;
					float x2 = overworld.objects[objectId[i]].x + x;
					float y1 = overworld.objects[j].y + overworld.objects[j].z;
					float y2 = overworld.objects[objectId[i]].x + overworld.objects[objectId[i]].z + y;
					if (x1 >= x2 - 32 && x1 <= x2 + 32
					&& y1 >= y2 - 4 && y1 <= y2 + 4) {
						bool ignore = false;
						for (int k = 0; k < 4; k++) {
							if (j == objectId[k]) {
								ignore = true;
								break;
							}
						}
						if (!ignore) {
							printf("%d is obstructing %d\n", j, objectId[i]);
							objectId[0] = 0;
							break;
						}
					}
				}
				if (objectId[0] == 0) break;
			}*/
			
			
			
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (objectId[0] == 0) {
				Event_Queue_PlaySound(SND_beep_square);
				Event_Queue_WaitFrames(15);
			}
			else if (direction == -1) {
				Event_Queue_PlaySound(SND_amper_feedback);
				Event_Queue_Camera_MoveTo(overworld.objects[objectId[0]].x, overworld.objects[objectId[0]].y - 8, 16);
				Event_Queue_PlaySound(SND_beep_square);
				Event_Queue_WaitFrames(15);
				Event_Queue_Regroup(16);
			}
			else {
				Event_Queue_PlaySound(SND_amper_feedback);
				if (eventSystem.callerObjectId == 16)
					Event_Queue_Camera_MoveTo(29152, 14064, 12);
				else
					Event_Queue_Camera_MoveTo(overworld.objects[objectId[0]].x, overworld.objects[objectId[0]].y - 8, 16);
				
				Event_Queue_PlaySound(SND_elevator);
				Event_Queue_SetSync(true);
				for (int i = 0; i < 4; i++) {
					if (objectId[i] == 0) break;
					
					float x = 0, y = 0;
					switch (direction) {
						case OBJECT_DIRECTION_LEFT: x = -80; break;
						case OBJECT_DIRECTION_RIGHT: x = 80; break;
						case OBJECT_DIRECTION_UP: y = -112; break;
						case OBJECT_DIRECTION_DOWN: y = 112; break;
					}
					
					Event_Queue_Object_JumpToRelative(objectId[i], x, y, -1, 0, 60);
					for (int j = 20; j < 60; j++) {
						if (overworld.objects[j].type == 0) continue;
						
						if (overworld.objects[j].vars[0].i == objectId[i]) {
							Event_Queue_Object_JumpToRelative(j, x, y, -1, 0, 60);
						}
					}
				}
				if (objectId[0] == 85 + 34 && profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DEFEATED] == 0) {
					Event_Queue_WaitFrames(7);
					Event_Queue_PlaySound(SND_dodge);
					Event_Queue_Object_JumpTo(61, 29096, 13952, -1, 104, 18);
					Event_Queue_SetFlag(FLAG_AMPERCORP_PBSUPERHERO_DEFEATED, 1);
				}
				Event_Queue_SetSync(false);
				
				Event_Queue_Regroup(16);
				
				
				
				switch (direction) {
					case OBJECT_DIRECTION_LEFT: direction = OBJECT_DIRECTION_RIGHT; break;
					case OBJECT_DIRECTION_RIGHT: direction = OBJECT_DIRECTION_LEFT; break;
					case OBJECT_DIRECTION_UP: direction = OBJECT_DIRECTION_DOWN; break;
					case OBJECT_DIRECTION_DOWN: direction = OBJECT_DIRECTION_UP; break;
				}
				for (int i = 0; i < 4; i++) {
					if (objectId[i] == 0) break;
					
					overworld.objects[objectId[i]].vars[0].i = direction;
				}
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010067: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(1500);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_SetSync(true);
			Event_Queue_Camera_MoveTo(3280, 5348, 0.5);
			Event_Queue_Object_WalkTo(0, 3280, 5352, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(1, 3280, 5392, 0.5, OBJECT_DIRECTION_UP);
			Event_Queue_Object_WalkTo(2, 3280, 5368, 0.5, -1);
			Event_Queue_Object_QueueWalkTo(2, 3320, 5360, 0.5, OBJECT_DIRECTION_LEFT);
			Event_Queue_Object_WalkTo(3, 3280, 5368, 0.5, -1);
			Event_Queue_Object_QueueWalkTo(3, 3240, 5360, 0.5, OBJECT_DIRECTION_RIGHT);
			Event_Queue_SetSync(false);
			Event_Queue_WaitFrames(45);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(1501);
			Event_Queue_Dialog_Run(1502);
			Event_Queue_Dialog_Run(1503);
			Event_Queue_Dialog_Run(1504);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_FadeOutMusic(1500);
			Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
			Event_Queue_WaitFrames(150);
			Event_Queue_ShowEnding(0);
			Event_Queue_Exit();
			
			Event_Queue_Label(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1010068: {
			if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] >= 2) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2662);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(2661);
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfEqual(0);
				
				Event_Queue_Camera_MoveTo(15760, 16128, 1);
				Event_Queue_Object_WalkTo(0, 15776, 16136, 1, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(0, 15776, 16120, OBJECT_DIRECTION_DOWN, 12, 16);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_sit);
				Event_Queue_Object_ChangeSpriteFrame(0, 0);
				Event_Queue_WaitFrames(98);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_JumpTo(0, 15776, 16112, OBJECT_DIRECTION_DOWN, 0, 12);
				Event_Queue_WaitFrames(24);
				Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_suppressed);
				Event_Queue_Object_ChangeSpriteFrame(0, 0);
				Event_Queue_FadeOutMusic(2000);
				Event_Queue_Overworld_FadeIn(120, 0, 0, 0);
				Event_Queue_WaitFrames(240);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
				Event_Queue_WaitFrames(90);
				Event_Queue_Object_JumpTo(0, 15776, 16136, OBJECT_DIRECTION_DOWN, 12, 24);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_run_prepare);
				Event_Queue_WaitFrames(22);
				Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
				
				Event_Queue_Regroup(1);
				Event_Queue_SetFlag(FLAG_SAPPHIREHOTEL_PLOT, 2);
				Event_Queue_SetFlag(FLAG_PLOT, 152);
				
				Event_Queue_Label(0);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
		
		case 1010069: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(2683);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(0);
			
			Event_Queue_CreateObject(70, 105, 0, caller->x, caller->y + 136, OBJECT_DIRECTION_DOWN);
			Event_Queue_Label(1);
			Event_Queue_WaitFrames(1);
			Event_Queue_CompareIntToConst(&overworld.objects[70].type, 0);
			Event_Queue_JumpIfGreater(1);
			if (!profile.flags[FLAG_GREGORY_OPTIONALFIGHT]) {
				if (profile.flags[FLAG_PLOT] >= 14) {
					Event_Queue_SetFlag(FLAG_FOREST_TELESCOPE_USED, 2);
					Event_Queue_CreateTrigger(0, 2064, 1104, 2224, 1120, 119);
				}
				else {
					Event_Queue_SetFlag(FLAG_FOREST_TELESCOPE_USED, 1);
				}
			}
			
			Event_Queue_Label(0);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		
		
		case 1060000: case 1060001: case 1060002: case 1060003: case 1060004: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3060);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		
		
		case 1070000: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3061);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
				
				Event_Queue_FadeOutMusic(1500);
				Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
				Event_Queue_WaitFrames(30);
				
				Event_Queue_Party_Leave(1);
				Event_Queue_Profile_InventoryPartyOrderRemove(1);
				Event_Queue_Party_Leave(2);
				Event_Queue_Profile_InventoryPartyOrderRemove(2);
				Event_Queue_Party_Leave(3);
				Event_Queue_Profile_InventoryPartyOrderRemove(3);
				
				Event_Queue_PlaySound(SND_encountermg);
				Event_Queue_WaitFrames(180);
				if (overworld.areaId == 110)
					Event_Queue_GotoArea(243, 4856, 11464, -1);
				else if (overworld.areaId == 19)
					Event_Queue_GotoArea(241, 4704, 10320, -1);
				else
					Event_Queue_GotoArea(240, 280, 10376, -1);
				Event_Queue_Jump(1);
			
			Event_Queue_Label(1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070001: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3100);
			if (!profile.flags[FLAG_RUBIN_HELLGATE]) {
				Event_Queue_CreateNPC(11, 70002, 280, 10376, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetFlag(FLAG_RUBIN_HELLGATE, 1);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070002: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 245 && profile.tempFlags[TEMPFLAG_ILLUSION_TIME_PUZZLECOMPLETE]) {
				Event_Queue_Dialog_Run(3154);
			}
			else if (overworld.areaId == 245 && profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] != 54321) {
				Event_Queue_Dialog_Run(3146);
			}
			else if (overworld.areaId == 240) {
				Event_Queue_Dialog_Run(3102);
			}
			else if (overworld.areaId == 242 && profile.flags[FLAG_ALONE_PLOT] < 20) {
				Event_Queue_Dialog_Run(3104);
			}
			Event_Queue_Dialog_Run(3101);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
				
				Event_Queue_FadeOutMusic(1500);
				Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
				Event_Queue_WaitFrames(30);
				
				if (profile.flags[FLAG_NOAH_JOINED]) {
					Event_Queue_Party_Join(1);
					Event_Queue_Profile_InventoryPartyOrderAdd(1);
				}
				if (profile.flags[FLAG_EMMET_JOINED]) {
					Event_Queue_Party_Join(2);
					Event_Queue_Profile_InventoryPartyOrderAdd(2);
				}
				if (profile.flags[FLAG_SALLY_JOINED]) {
					Event_Queue_Party_Join(3);
					Event_Queue_Profile_InventoryPartyOrderAdd(3);
				}
				
				Event_Queue_PlaySound(SND_encountermg);
				Event_Queue_SetTempFlag(TEMPFLAG_ILLUSION_HYPERHELL, 0);
				Event_Queue_WaitFrames(180);
				if (overworld.areaId == 245 || overworld.areaId == 231)
					Event_Queue_GotoArea(110, 8008, 12504, SPR_tileset_day);
				else if (overworld.areaId == 242)
					Event_Queue_GotoArea(19, 7432, 7240, SPR_tileset_day);
				else
					Event_Queue_GotoArea(5, 552, 1288, SPR_tileset_day_forest);
				Event_Queue_Jump(1);
			
			Event_Queue_Label(1);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070003: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3103);
			Event_Queue_CreateNPC(11, 70002, 5312, 9328, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_ALONE] && profile.flags[FLAG_ALONE_PLOT] >= 20) {
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Camera_TogglePlayerFollow(true);
				if (player->x <= 4360) {
					if (player->y < 9304)
						Event_Queue_Object_WalkTo(0, 4376, 9288, 1, -1);
					else
						Event_Queue_Object_WalkTo(0, 4376, 9328, 1, -1);
				}
				Event_Queue_Object_WalkTo(0, 4378, 9312, 1, OBJECT_DIRECTION_UP);
				
				Event_Queue_WaitFrames(30);
				Event_Queue_Object_ChangeDirection(10, OBJECT_DIRECTION_RIGHT);
				Event_Queue_WaitFrames(50);
				Event_Queue_Dialog_Run(3134);
				Event_Queue_WaitFrames(40);
				Event_Queue_Overworld_FadeIn(1, 255, 0, 0);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
				Event_Queue_Object_EnableFighterSprite(0, 1, 10, FIGHTER_STATE_ATTACK3);
				Event_Queue_PlaySound(SND_hit3);
				Event_Queue_Object_Destroy(10);
				Event_Queue_CreateObject(10, 1, SPR_misc_collapseblood, 4360, 9304, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteFrame(11, 1);
				Event_Queue_WaitFrames(1);
				Event_Queue_Overworld_FadeOut(1, 255, 0, 0);
				Event_Queue_SetSync(true);
				Event_Queue_Object_TeleportTo(11, 4952, 9312);
				Event_Queue_Object_WalkTo(11, 4440, 9312, 2, OBJECT_DIRECTION_LEFT);
				Event_Queue_WaitFrames(50);
				Event_Queue_Object_DisableFighterSprite(0);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_SetSync(false);
				Event_Queue_WaitFrames(10);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
				Event_Queue_Dialog_Run(3135);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(3136);
				Event_Queue_Object_WalkTo(11, 4424, 9312, 1, OBJECT_DIRECTION_LEFT);
				Event_Queue_Dialog_Run(3137);
				Event_Queue_WaitFrames(60);
				Event_Queue_Dialog_Run(3138);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_DOWN);
			}
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070004: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			if (!profile.tempFlags[TEMPFLAG_ILLUSION_HELL_RUBIN_DIALOG]) {
				if (profile.flags[FLAG_ILLUSION_GATE_DEFEATED]) {
					Event_Queue_Dialog_Run(3132);
					Event_Queue_Dialog_Run(3133);
				}
				else {
					Event_Queue_Dialog_Run(3124);
					Event_Queue_Dialog_Run(3125);
				}
				Event_Queue_Dialog_Run(3126);
				Event_Queue_Dialog_Run(3127);
				Event_Queue_SetTempFlag(TEMPFLAG_ILLUSION_HELL_RUBIN_DIALOG, 1);
			}
			Event_Queue_Dialog_Run(3101);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
				
				Event_Queue_FadeOutMusic(1500);
				Event_Queue_Overworld_FadeIn(90, 0, 0, 0);
				Event_Queue_WaitFrames(30);
				
				Event_Queue_PlaySound(SND_encountermg);
				Event_Queue_WaitFrames(180);
				Event_Queue_GotoArea(95, 17808, 11088, -1);
				Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				
				Event_Queue_WaitFrames(128);
				Event_Queue_Object_ToggleGhost(0, true);
				Event_Queue_Object_WalkToRelative(0, 24, 0, 0.5, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ToggleGhost(0, false);
				
				if (profile.flags[FLAG_ALONE]) {
					Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
				}
				else {
					Event_Queue_Object_ChangeDirection(11, OBJECT_DIRECTION_RIGHT);
					Event_Queue_WaitFrames(50);
					Event_Queue_Dialog_Run(790);
					Event_Queue_Object_ChangeDirection(13, OBJECT_DIRECTION_RIGHT);
					Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_think);
					Event_Queue_SetSync(true);
					Event_Queue_Object_WalkTo(12, 17864, 11160, 2, OBJECT_DIRECTION_UP);
					Event_Queue_Dialog_Run(791);
					Event_Queue_SetSync(false);
					Event_Queue_Dialog_Run(792);
					Event_Queue_Dialog_Run(793);
					Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
					Event_Queue_Object_WalkToRelative(0, 0, 16, 0.5, OBJECT_DIRECTION_DOWN);
					Event_Queue_Dialog_Run(794);
				}
				
				if (profile.flags[FLAG_NOAH_JOINED]) {
					Event_Queue_Party_Join(1);
				}
				if (profile.flags[FLAG_EMMET_JOINED]) {
					Event_Queue_Party_Join(2);
				}
				if (profile.flags[FLAG_SALLY_JOINED]) {
					Event_Queue_Party_Join(3);
				}
				Event_Queue_Object_TeleportToPointer(1, 0, 0, &overworld.objects[11].x, &overworld.objects[11].y);
				Event_Queue_Object_TeleportToPointer(2, 0, 0, &overworld.objects[12].x, &overworld.objects[12].y);
				Event_Queue_Object_TeleportToPointer(3, 0, 0, &overworld.objects[13].x, &overworld.objects[13].y);
				Event_Queue_Object_Destroy(11);
				Event_Queue_Object_Destroy(12);
				Event_Queue_Object_Destroy(13);
				Event_Queue_Regroup(1);
				Event_Queue_SetFlag(FLAG_PLOT, 122);
				Event_Queue_SetFlag(FLAG_AZURETOPHOTEL_PLOT, 3);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				Event_Queue_Exit();
			
			Event_Queue_Label(1);
			Event_Queue_Object_ChangeDirection(eventSystem.callerObjectId, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070005: {
			int keyId = caller->vars[7].i;
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_CreateObject(70, 1, SPR_misc_timelinepuzzle, player->x, player->y + 152, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_SetPositionZ(70, -168);
			Event_Queue_Object_ChangeSpriteFrame(70, keyId);
			Event_Queue_Dialog_Run(3139 + keyId);
			Event_Queue_Object_Destroy(70);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_CustomAction(3);
			Event_Queue_CustomAction(4);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070006: {
			int keyId = caller->vars[7].i - 1;
			
			int slotBase = 1;
			for (int i = 0; i < 5; i++) {
				int id = (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / slotBase) % 10;
				if (id == 9) {
					break;
				}
				slotBase *= 10;
			}
			
			if (keyId == -1 && profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] % 10 != 9
			&& (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 10) % 10 != 9
			&& (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 100) % 10 != 9
			&& (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 1000) % 10 != 9
			&& (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 10000) % 10 != 9) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(3145);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				break;
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (keyId >= 0) {
				Event_Queue_CreateObject(70, 1, SPR_misc_timelinepuzzle, player->x, player->y + 152, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_SetPositionZ(70, -168);
				Event_Queue_Object_ChangeSpriteFrame(70, keyId);
				Event_Queue_Dialog_Run(3139 + keyId);
				if (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] == 54321) {
					Event_Queue_Object_Destroy(70);
					Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
					break;
				}
			}
			Event_Queue_Dialog_Run(3144);
			Event_Queue_Object_Destroy(70);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 0);
			Event_Queue_JumpIfEqual(0);
			if (keyId >= 0) {
				Event_Queue_SetIntPtr(&caller->vars[7].i, keyId);
				if (slotBase <= 10000) {
					Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, -((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / slotBase) % 10) * slotBase);
					Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, 9 * slotBase);
				}
				Event_Queue_CustomAction(3);
				Event_Queue_CustomAction(4);
				
				Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
				Event_Queue_JumpIfNotEqual(1);
				Event_Queue_Object_ChangeSpriteId(eventSystem.callerObjectId, SPR_misc_timelineslot);
				Event_Queue_SetIntPtr(&caller->vars[7].i, 0);
				Event_Queue_Jump(0);
			}
			
			Event_Queue_Label(1);
			{
				int c = 0;
				int base = 1;
				for (int i = 0; i < 5; i++) {
					int id = (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / base) % 10;
					if (id == 9) {
						Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1 + (keyId >= 0) + c);
						Event_Queue_JumpIfEqual(2 + i);
						c++;
					}
					base *= 10;
				}
			}
			Event_Queue_Label(2);
			Event_Queue_SetIntPtr(&caller->vars[7].i, 1);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, -(profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] % 10));
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, (eventSystem.callerObjectId - 9));
			Event_Queue_Jump(9);
			
			Event_Queue_Label(3);
			Event_Queue_SetIntPtr(&caller->vars[7].i, 2);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, -((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 10) % 10) * 10);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, (eventSystem.callerObjectId - 9) * 10);
			Event_Queue_Jump(9);
			
			Event_Queue_Label(4);
			Event_Queue_SetIntPtr(&caller->vars[7].i, 3);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, -((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 100) % 10) * 100);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, (eventSystem.callerObjectId - 9) * 100);
			Event_Queue_Jump(9);
			
			Event_Queue_Label(5);
			Event_Queue_SetIntPtr(&caller->vars[7].i, 4);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, -((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 1000) % 10) * 1000);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, (eventSystem.callerObjectId - 9) * 1000);
			Event_Queue_Jump(9);
			
			Event_Queue_Label(6);
			Event_Queue_SetIntPtr(&caller->vars[7].i, 5);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, -((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 10000) % 10) * 10000);
			Event_Queue_AddFlag(FLAG_ILLUSION_TIME_PUZZLESTATE, (eventSystem.callerObjectId - 9) * 10000);
			
			Event_Queue_Label(9);
			Event_Queue_Object_ChangeSpriteId(eventSystem.callerObjectId, SPR_misc_timelineblock);
			
			Event_Queue_Label(0);
			Event_Queue_CompareIntToConst(&profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE], 54321);
			Event_Queue_JumpIfNotEqual(10);
			Event_Queue_PlaySound(SND_neutralize);
			Event_Queue_Object_Destroy(15);
			Event_Queue_Object_Destroy(16);
			Event_Queue_SetBoolPtr(&overworld.map.doors[248].enabled, true);
			Event_Queue_CustomAction(4);
			
			Event_Queue_Label(10);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070007: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (Random(1) < 0.01) {
				if (Random(1) < 0.5)
					Audio_ApplySoundFilter(Random_IRange(0, 8));
				else
					*(volatile int*)(0) = 0;
			}
			for (int i = 0; i < Random_IRange(0, 256); i++) {
				if (Random(1) < 0.5) {
					eventSystem.queue[eventSystem.queueSize].id = Random_IRange(1, 99);
					int eid = eventSystem.queue[eventSystem.queueSize].id == 28;
					while (eid == 28 || eid == 29 || eid == 34 || eid == 35 || eid == 7 || eid == 3 || eid == 5 || eid == 8 || eid == 9 || eid == 14 || eid == 26 || eid == 38 || eid == 39 || eid == 40) {
						eventSystem.queue[eventSystem.queueSize].id = Random_IRange(1, 99);
						if (Random(1) < 0.05) break;
					}
				}
				else if (Random(1) < 0.4)
					eventSystem.queue[eventSystem.queueSize].id = Random_IRange(1000, 1099);
				else
					eventSystem.queue[eventSystem.queueSize].id = Random_IRange(1, 9999);
				for (int j = 0; j < 16; j++) {
					eventSystem.queue[eventSystem.queueSize].args[j].i = Random_IRange(0, 0xffffffff);
				}
				eventSystem.queueSize++;
			}
			for (int i = 0; i < Random_IRange(1, 1048576); i++) {
				*((unsigned char*)(&actionData[0]) + Random_IRange(0, 8388608 + 1048576)) = Random_IRange(0, 255);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070008: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			if (overworld.areaId == 245) {
				if (eventSystem.callerObjectId == 20) {
					Event_Queue_Dialog_Run(3147);
				}
				else if (eventSystem.callerObjectId == 21) {
					Event_Queue_Dialog_Run(3149);
				}
			}
			else if (overworld.areaId == 246) {
				Event_Queue_Dialog_Run(3151);
			}
			else if (overworld.areaId == 247) {
				Event_Queue_Dialog_Run(3150);
			}
			else if (overworld.areaId == 249) {
				Event_Queue_Dialog_Run(3148);
			}
			else if (overworld.areaId == 250) {
				Event_Queue_Dialog_Run(3152);
			}
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070009: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3153);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070010: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Dialog_Run(3155);
			Event_Queue_StopMusic();
			Event_Queue_Overworld_FadeIn(1, 255, 0, 0);
			Event_Queue_PlaySound(SND_bonus1);
			Event_Queue_Object_Destroy(eventSystem.callerObjectId);
			Event_Queue_WaitFrames(1);
			Event_Queue_Overworld_FadeOut(1, 255, 0, 0);
			Event_Queue_WaitFrames(160);
			Event_Queue_PlayMusic(MUS_city);
			Event_Queue_SetFlag(FLAG_FUN_NOBODY_0, 1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070011: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_PlaySound(SND_bonus2);
			Event_Queue_Dialog_Run(3156);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070013: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(3180);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_StopMusic();
			Event_Queue_WaitFrames(19);
			Event_Queue_GotoArea(253, 1728, 10398, -1);
			Event_Queue_Camera_TeleportTo(1728, 10400);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_teen_draw);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(0, 0);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_WaitFrames(25);
			Event_Queue_Object_ChangeSpriteFrame(0, 0);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_WaitFrames(3);
			Event_Queue_CreateObject(70, 1, SPR_owchar_npc_41, 1536, 10432, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(70, 1712, 10432, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(3181);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_ChangeSpriteFrame(0, 2);
			Event_Queue_Dialog_Run(3182);
			Event_Queue_Dialog_Run(3183);
			Event_Queue_Object_ChangeSpriteFrame(0, 3);
			Event_Queue_Dialog_Run(3184);
			Event_Queue_Dialog_Run(3183);
			Event_Queue_Dialog_Run(3185);
			Event_Queue_Dialog_Run(3186);
			Event_Queue_Dialog_Run(3187);
			Event_Queue_Dialog_Run(3188);
			Event_Queue_Object_ChangeSpriteFrame(0, 4);
			Event_Queue_Dialog_Run(3183);
			Event_Queue_Dialog_Run(3189);
			Event_Queue_Object_ChangeSpriteFrame(0, 5);
			Event_Queue_WaitFrames(25);
			Event_Queue_Object_ChangeSpriteFrame(0, 6);
			Event_Queue_WaitFrames(24);
			Event_Queue_Object_ChangeSpriteFrame(0, 5);
			Event_Queue_WaitFrames(25);
			Event_Queue_Object_ChangeSpriteFrame(0, 6);
			Event_Queue_WaitFrames(2);
			Event_Queue_Dialog_Run(3190);
			Event_Queue_Dialog_Run(3183);
			Event_Queue_Dialog_Run(3191);
			Event_Queue_Object_ChangeSpriteFrame(0, 5);
			Event_Queue_WaitFrames(21);
			Event_Queue_Object_ChangeSpriteFrame(0, 7);
			Event_Queue_WaitFrames(21);
			Event_Queue_Object_ChangeSpriteFrame(0, 8);
			Event_Queue_WaitFrames(25);
			Event_Queue_Object_ChangeSpriteFrame(0, 7);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_ChangeSpriteFrame(0, 8);
			Event_Queue_WaitFrames(16);
			Event_Queue_Overworld_ShakeScreen(16);
			Event_Queue_Dialog_Run(3192);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportToRelative(0, -1, 0);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportToRelative(0, 2, 0);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportToRelative(0, -2, 0);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_TeleportToRelative(0, 1, 0);
			Event_Queue_Object_ChangeSpriteFrame(0, 7);
			Event_Queue_WaitFrames(15);
			Event_Queue_Dialog_Run(3193);
			Event_Queue_Object_ChangeSpriteFrame(0, 9);
			Event_Queue_Dialog_Run(3194);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(3195);
			Event_Queue_WaitFrames(30);
			Event_Queue_Dialog_Run(3196);
			Event_Queue_PlaySound(SND_voice2);
			Event_Queue_Object_ChangeSpriteFrame(0, 10);
			Event_Queue_WaitFrames(40);
			Event_Queue_Object_ChangeSpriteFrame(0, 11);
			Event_Queue_CreateObject(72, 1, SPR_misc_rubyteenartbook, 1719, 10386, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(20);
			Event_Queue_Object_ChangeSpriteFrame(0, 12);
			Event_Queue_WaitFrames(68);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_teen);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_TeleportTo(0, 1728, 10408);
			Event_Queue_WaitFrames(72);
			Event_Queue_Object_WalkTo(0, 1712, 10416, 0.25, OBJECT_DIRECTION_DOWN);
			Event_Queue_WaitFrames(37);
			Event_Queue_Object_ChangeSpriteId(0, SPR_misc_ruby_teen_slap);
			Event_Queue_Object_ChangeSpriteFrame(0, 0);
			Event_Queue_WaitFrames(18);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_ChangeSpriteId(70, SPR_misc_npc_41_slapped);
			Event_Queue_Object_ChangeSpriteFrame(70, 0);
			Event_Queue_Object_JumpTo(70, 1712, 10452, OBJECT_DIRECTION_UP, 0, 8);
			Event_Queue_WaitFrames(56);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_teen);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_WaitFrames(32);
			
			Event_Queue_Dialog_Run(3197);
			Event_Queue_Object_ChangeSpriteFrame(70, 1);
			Event_Queue_WaitFrames(32);
			Event_Queue_Object_ChangeSpriteFrame(70, 2);
			Event_Queue_WaitFrames(32);
			Event_Queue_Dialog_Run(3198);
			Event_Queue_CreateObject(71, 1, SPR_owchar_npc_42, 1536, 10432, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_WalkTo(71, 1640, 10432, 2, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(3199);
			Event_Queue_Dialog_Run(3200);
			Event_Queue_Dialog_Run(3201);
			Event_Queue_Dialog_Run(3202);
			Event_Queue_Dialog_Run(3203);
			Event_Queue_Object_WalkTo(71, 1692, 10416, 1, OBJECT_DIRECTION_RIGHT);
			Event_Queue_Dialog_Run(3204);
			Event_Queue_PlaySound(SND_swing);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_collapse_ruby_teen);
			Event_Queue_Object_ChangeSpriteFrame(0, 0);
			Event_Queue_Object_JumpTo(0, 1664, 10424, OBJECT_DIRECTION_DOWN, 0, 8);
			Event_Queue_PlaySound(SND_slap);
			Event_Queue_Object_ChangeSpriteFrame(0, 1);
			Event_Queue_WaitFrames(48);
			Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(3205);
			
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_teen);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_SetSync(true);
			Event_Queue_Object_WalkTo(71, 1488, 10432, 2, OBJECT_DIRECTION_LEFT);
			Event_Queue_WaitFrames(38);
			Event_Queue_Object_WalkTo(0, 1528, 10432, 2, OBJECT_DIRECTION_UP);
			Event_Queue_SetSync(false);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(3206);
			Event_Queue_WaitFrames(60);
			Event_Queue_SetFlag(FLAG_ILLUSION_MEMORY_GEMS, profile.flags[FLAG_ILLUSION_MEMORY_GEMS] | 0x1);
			Event_Queue_GotoArea(252, 1120, 10576, -1);
			Event_Queue_Overworld_FadeOut(1, 0, 0, 0);
			
			Event_Queue_Label(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070014: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(3180);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_StopMusic();
			Event_Queue_WaitFrames(19);
			Event_Queue_GotoArea(253, 1624, 10768, -1);
			Event_Queue_Camera_TeleportTo(1648, 10736);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_nmg);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_RIGHT);
			Event_Queue_CreateObject(70, 1, SPR_owchar_npc_43, 1672, 10768, OBJECT_DIRECTION_LEFT);
			Event_Queue_CreateObject(71, 1, SPR_owchar_npc_44, 1672, 10720, OBJECT_DIRECTION_DOWN);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_WaitFrames(55);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(3210);
			Event_Queue_Object_JumpToRelative(71, 0, 0, OBJECT_DIRECTION_DOWN, 16, 12);
			Event_Queue_Dialog_Run(3211);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(3212);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(3213);
			Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(3214);
			Event_Queue_Object_ChangeDirection(71, OBJECT_DIRECTION_DOWN);
			Event_Queue_Dialog_Run(3215);
			Event_Queue_Dialog_Run(3183);
			Event_Queue_Dialog_Run(3216);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(3217);
			Event_Queue_Dialog_Run(3218);
			Event_Queue_WaitFrames(65);
			Event_Queue_Dialog_Run(3219);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(3220);
			Event_Queue_WaitFrames(60);
			Event_Queue_SetFlag(FLAG_ILLUSION_MEMORY_GEMS, profile.flags[FLAG_ILLUSION_MEMORY_GEMS] | 0x2);
			Event_Queue_GotoArea(252, 1120, 10576, -1);
			Event_Queue_Overworld_FadeOut(1, 0, 0, 0);
			
			Event_Queue_Label(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070015: {
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
			Event_Queue_Player_SetPositionSync(true);
			Event_Queue_Dialog_Run(3180);
			Event_Queue_CompareIntToConst(&dialogSystem.optionSelected, 1);
			Event_Queue_JumpIfEqual(1);
			
			Event_Queue_Overworld_FadeIn(1, 0, 0, 0);
			Event_Queue_StopMusic();
			Event_Queue_WaitFrames(19);
			Event_Queue_GotoArea(253, 1648, 11048, -1);
			Event_Queue_Camera_TeleportTo(1664, 11040);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby_nmg);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_DOWN);
			Event_Queue_CreateObject(70, 1, SPR_owchar_npc_42, 1736, 11064, OBJECT_DIRECTION_LEFT);
			Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
			
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(3221);
			Event_Queue_Dialog_Run(3183);
			Event_Queue_Dialog_Run(3222);
			Event_Queue_Object_ChangeDirection(0, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(3223);
			Event_Queue_Dialog_Run(3224);
			Event_Queue_WaitFrames(50);
			Event_Queue_Dialog_Run(3225);
			Event_Queue_Dialog_Run(3226);
			Event_Queue_Dialog_Run(3227);
			Event_Queue_Object_WalkTo(70, 1656, 11080, 1, OBJECT_DIRECTION_LEFT);
			Event_Queue_Dialog_Run(3228);
			Event_Queue_WaitFrames(50);
			Event_Queue_Object_ChangeDirection(70, OBJECT_DIRECTION_UP);
			Event_Queue_Dialog_Run(3229);
			Event_Queue_Object_WalkTo(70, 1480, 11080, 1, OBJECT_DIRECTION_LEFT);
			
			Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
			Event_Queue_Object_ChangeSpriteId(0, SPR_owchar_ruby);
			Event_Queue_Dialog_Run(3230);
			Event_Queue_WaitFrames(60);
			Event_Queue_SetFlag(FLAG_ILLUSION_MEMORY_GEMS, profile.flags[FLAG_ILLUSION_MEMORY_GEMS] | 0x4);
			Event_Queue_GotoArea(252, 1120, 10576, -1);
			Event_Queue_Overworld_FadeOut(1, 0, 0, 0);
			
			Event_Queue_Label(1);
			Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
		} break;
		
		case 1070017: {
			if (profile.flags[FLAG_ILLUSION_MEMORY_GEMS] != 0x7) {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Dialog_Run(3231);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			else {
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_PlaySound(SND_neutralize);
				Event_Queue_CreateObject(70, 1, SPR_misc_illusmemorygems, 1104, 10448, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(71, 1, SPR_misc_illusmemorygems, 1136, 10448, OBJECT_DIRECTION_DOWN);
				Event_Queue_CreateObject(72, 1, SPR_misc_illusmemorygems, 1104, 10496, OBJECT_DIRECTION_DOWN);
				Event_Queue_Object_ChangeSpriteFrame(70, 0);
				Event_Queue_Object_ChangeSpriteFrame(71, 1);
				Event_Queue_Object_ChangeSpriteFrame(72, 2);
				Event_Queue_WaitFrames(60);
				
				Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
				Event_Queue_WaitFrames(60);
				if (profile.flags[FLAG_RUBY_GODMODE]) {
					Event_Queue_Dialog_Run(3236);
				}
				else {
					Event_Queue_Dialog_Run(3232);
				}
				Event_Queue_GotoArea(254, 2552, 12664, -1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
		} break;
	}
}
