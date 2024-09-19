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

EventSystem eventSystem;



void LoadEventData() {
	eventSystem.paused = false;
	eventSystem.callerObjectId = 0;
	eventSystem.runningSize = 0;
	eventSystem.queueSize = 0;
	eventSystem.triggerId = 0;
	eventSystem.sync = false;
	eventSystem.playerPositionSync = false;
	eventSystem.cameraPlayerFollow = false;
}



void Event_Update() {
	if (eventSystem.paused) return;
	if (eventSystem.runningSize == 0 && eventSystem.ptr >= eventSystem.queueSize) {
		eventSystem.ptr = 0;
		eventSystem.queueSize = 0;
		return;
	}
	
	if (eventSystem.playerPositionSync) {
		overworld.player.x = overworld.objects[0].x;
		overworld.player.y = overworld.objects[0].y;
		overworld.player.direction = overworld.objects[0].direction;
	}
	
	if (eventSystem.cameraPlayerFollow) {
		overworld.camera.x = overworld.objects[0].x;
		overworld.camera.y = overworld.objects[0].y - 8;
	}
	
	int ei = 0;
	while ((eventSystem.runningSize == 0 || eventSystem.sync) && eventSystem.ptr < eventSystem.queueSize && ei++ < 256) {
		EventCommand* command = &eventSystem.running[eventSystem.runningSize++];
		
		*command = eventSystem.queue[eventSystem.ptr++];
		
		switch (command->id) {
			case 1:
				Dialog_Run(command->args[0].i);
				break;
			case 2:
				overworld.state = command->args[0].i;
				command->id = 0;
				break;
			case 3:
				OverworldObject_WalkTo(command->args[0].i, overworld.objects[command->args[0].i].x + command->args[1].f, overworld.objects[command->args[0].i].y + command->args[2].f, command->args[3].f, command->args[4].i);
				break;
			case 4:
				EngageBattle(command->args[0].i, command->args[1].i);
				break;
			case 5:
				command->args[0].f += overworld.camera.x;
				command->args[1].f += overworld.camera.y;
				break;
			case 6:
				OverworldObject_WalkTo(0, overworld.player.x, overworld.player.y, command->args[0].f, overworld.player.direction);
				
				for (int i = 1; i < 8; i++) {
					if (overworld.objects[i].spriteId < 0) continue;
					OverworldObject_WalkTo(i, overworld.caterpillar[i * 16].x, overworld.caterpillar[i * 16].y, command->args[0].f, overworld.caterpillar[i * 16].direction);
				}
				break;
			case 7:
				command->args[1].i = eventSystem.sync;
				eventSystem.sync = false;
				break;
			case 8:
				OverworldObject_WalkTo(command->args[0].i, *command->args[5].pf + command->args[1].f, *command->args[6].pf + command->args[2].f, command->args[3].f, command->args[4].i);
				break;
			case 9:
				OverworldObject_WalkTo(command->args[0].i, command->args[1].f, command->args[2].f, command->args[3].f, command->args[4].i);
				break;
			case 10:
				OverworldObject_ChangeDirection(command->args[0].i, command->args[1].i);
				command->id = 0;
				break;
			case 11:
				OverworldObject_ChangeSpriteId(command->args[0].i, command->args[1].i);
				command->id = 0;
				break;
			case 12:
				OverworldObject_ChangeSpriteFrame(command->args[0].i, command->args[1].i);
				command->id = 0;
				break;
			case 13:
				OverworldObject_Destroy(command->args[0].i);
				command->id = 0;
				break;
			case 15:
				eventSystem.playerPositionSync = command->args[0].i;
				command->id = 0;
				break;
			case 16:
				overworld.objects[command->args[0].i].x = command->args[1].f;
				overworld.objects[command->args[0].i].y = command->args[2].f;
				command->id = 0;
				break;
			case 17:
				overworld.objects[command->args[0].i].x = *command->args[3].pf + command->args[1].f;
				overworld.objects[command->args[0].i].y = *command->args[4].pf + command->args[2].f;
				command->id = 0;
				break;
			case 18:
				Overworld_CreateObject(command->args[0].i, command->args[1].i, command->args[2].i, command->args[3].f, command->args[4].f, command->args[5].i);
				command->id = 0;
				break;
			case 19:
				Overworld_CreateNPC(command->args[0].i, command->args[1].i, command->args[2].f, command->args[3].f, command->args[4].i);
				command->id = 0;
				break;
			case 20:
				Overworld_CreateEnemy(command->args[0].i, command->args[1].i, command->args[2].f, command->args[3].f);
				command->id = 0;
				break;
			case 21:
				overworld.transition.id = 1;
				overworld.transition.timer = 0;
				overworld.transition.vars[0] = command->args[0].i;
				overworld.transition.vars[1] = command->args[1].f;
				overworld.transition.vars[2] = command->args[2].f;
				overworld.transition.vars[3] = command->args[3].i;
				break;
			case 22:
				OverworldObject_EnableFighterSprite(command->args[0].i, command->args[1].i, command->args[2].i, command->args[3].i);
				command->id = 0;
				break;
			case 23:
				OverworldObject_DisableFighterSprite(command->args[0].i);
				command->id = 0;
				break;
			case 24:
				OverworldObject_ChangeSpriteFrameSpeed(command->args[0].i, command->args[1].f);
				command->id = 0;
				break;
			case 25:
				OverworldObject_ToggleWalkAnimation(command->args[0].i, command->args[1].i);
				command->id = 0;
				break;
			case 26:
				OverworldObject_QueueWalkTo(command->args[0].i, command->args[1].f, command->args[2].f, command->args[3].f, command->args[4].i);
				break;
			case 27:
				eventSystem.cameraPlayerFollow = command->args[0].i;
				command->id = 0;
				break;
			case 30:
				Overworld_OpenShopMenu(command->args[0].i);
				break;
			case 31:
				Overworld_OpenSaveMenu();
				break;
			case 32:
				overworld.camera.x = command->args[0].f;
				overworld.camera.y = command->args[1].f;
				command->id = 0;
				break;
			case 33:
				OverworldObject_ToggleGhost(command->args[0].i, command->args[1].i);
				command->id = 0;
				break;
			case 34:
				Overworld_FadeIn(command->args[0].i, command->args[1].i, command->args[2].i, command->args[3].i);
				break;
			case 35:
				Overworld_FadeOut(command->args[0].i, command->args[1].i, command->args[2].i, command->args[3].i);
				break;
			case 36:
				Overworld_CreateTrigger(command->args[0].i, command->args[1].f, command->args[2].f, command->args[3].f, command->args[4].f, command->args[5].i);
				command->id = 0;
				break;
			case 37:
				Overworld_ShakeScreen(command->args[0].i);
				command->id = 0;
				break;
			case 38:
				OverworldObject_JumpTo(command->args[0].i, *command->args[6].pf + command->args[1].f, *command->args[7].pf + command->args[2].f, command->args[3].i, command->args[4].f, command->args[5].i);
				break;
			case 39:
				OverworldObject_JumpTo(command->args[0].i, command->args[1].f, command->args[2].f, command->args[3].i, command->args[4].f, command->args[5].i);
				break;
			case 40:
				OverworldObject_JumpTo(command->args[0].i, overworld.objects[command->args[0].i].x + command->args[1].f, overworld.objects[command->args[0].i].y + command->args[2].f, command->args[3].i, command->args[4].f, command->args[5].i);
				break;
			case 41:
				OverworldObject_SetColor(command->args[0].i, command->args[1].i, command->args[2].i, command->args[3].i);
				command->id = 0;
				break;
			case 42:
				Overworld_CreateSpark(command->args[0].i, command->args[1].f, command->args[2].f, command->args[3].i);
				command->id = 0;
				break;
			case 43:
				OverworldObject_SetCollisionSize(command->args[0].i, command->args[1].i, command->args[2].i);
				command->id = 0;
				break;
			case 44:
				OverworldObject_SetPositionZ(command->args[0].i, command->args[1].f);
				command->id = 0;
				break;
			
			case 1000:
				overworld.map.triggers[eventSystem.triggerId].eventId = 0;
				command->id = 0;
				break;
			case 1001:
				eventSystem.sync = command->args[0].i;
				command->id = 0;
				break;
			case 1002:
				eventSystem.vars[command->args[0].i].i = command->args[1].i;
				command->id = 0;
				break;
			case 1003:
				eventSystem.vars[command->args[0].i].f = command->args[1].f;
				command->id = 0;
				break;
			case 1004:
				eventSystem.vars[command->args[0].i].i = *command->args[1].pi;
				command->id = 0;
				break;
			case 1005:
				eventSystem.vars[command->args[0].i].f = *command->args[1].pf;
				command->id = 0;
				break;
			case 1006:
				profile.flags[command->args[0].i] = command->args[1].i;
				command->id = 0;
				break;
			case 1007:
				Party_Join(command->args[0].i);
				command->id = 0;
				break;
			case 1008:
				Party_Leave(command->args[0].i);
				command->id = 0;
				break;
			case 1009:
				Profile_InventoryPartyOrderAdd(command->args[0].i);
				command->id = 0;
				break;
			case 1010:
				Profile_InventoryPartyOrderRemove(command->args[0].i);
				command->id = 0;
				break;
			case 1011:
				*command->args[0].pi = command->args[1].i;
				command->id = 0;
				break;
			case 1012:
				*command->args[0].pf = command->args[1].f;
				command->id = 0;
				break;
			case 1013:
				profile.cash += command->args[0].i;
				command->id = 0;
				break;
			case 1014:
				profile.cash = command->args[0].i;
				command->id = 0;
				break;
			case 1015:
				Profile_ItemAdd(command->args[0].i);
				command->id = 0;
				break;
			case 1016:
				Profile_ItemRemove(command->args[0].i);
				command->id = 0;
				break;
			case 1017:
				Profile_ClearItemInventory();
				command->id = 0;
				break;
			case 1018:
				Profile_KeyItemAdd(command->args[0].i);
				command->id = 0;
				break;
			case 1019:
				Profile_KeyItemRemove(command->args[0].i);
				command->id = 0;
				break;
			case 1020:
				eventSystem.flags.equal = Profile_KeyItemExists(command->args[0].i);
				command->id = 0;
				break;
			case 1021:
				PlayMusic(command->args[0].i);
				command->id = 0;
				break;
			case 1022:
				StopMusic();
				command->id = 0;
				break;
			case 1023:
				PlaySound(command->args[0].i);
				command->id = 0;
				break;
			case 1024:
				FadeOutMusic(command->args[0].i);
				command->id = 0;
				break;
			case 1025:
				*command->args[0].pi = *command->args[1].pi;
				command->id = 0;
				break;
			case 1026:
				*command->args[0].pf = *command->args[1].pf;
				command->id = 0;
				break;
			case 1027:
				*command->args[0].pi += command->args[1].i;
				command->id = 0;
				break;
			case 1028:
				*command->args[0].pf += command->args[1].f;
				command->id = 0;
				break;
			case 1029:
				break;
			case 1030:
				for (int i = 0; i < 10; i++) {
					PartyMember* partyMember = &partyMembers[i];
					partyMember->hpDamage = 0;
					partyMember->tiredness = 0;
					partyMember->tiredLevel = 0;
				}
				command->id = 0;
				break;
			case 1031:
				profile.tempFlags[command->args[0].i] = command->args[1].i;
				command->id = 0;
				break;
			case 1032:
				profile.flags[command->args[0].i] += command->args[1].i;
				command->id = 0;
				break;
			case 1033:
				*command->args[0].pb = command->args[1].b;
				command->id = 0;
				break;
			
			case 5000:
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				command->id = 0;
				break;
			case 5001:
				if (!eventSystem.flags.equal) break;
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				
				command->id = 0;
				break;
			case 5002:
				if (!eventSystem.flags.less || eventSystem.flags.equal) break;
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				
				command->id = 0;
				break;
			case 5003:
				if (!eventSystem.flags.greater || eventSystem.flags.equal) break;
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				
				command->id = 0;
				break;
			case 5004:
				if (!eventSystem.flags.less) break;
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				
				command->id = 0;
				break;
			case 5005:
				if (!eventSystem.flags.greater) break;
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				
				command->id = 0;
				break;
			case 5006:
				if (eventSystem.flags.equal) break;
				eventSystem.ptr = eventSystem.labels[command->args[0].i];
				
				command->id = 0;
				break;
			
			case 5100:
				eventSystem.flags.equal = 0;
				eventSystem.flags.greater = 0;
				eventSystem.flags.less = 0;
				if (*command->args[0].pi == command->args[1].i) eventSystem.flags.equal = 1;
				if (*command->args[0].pi > command->args[1].i) eventSystem.flags.greater = 1;
				if (*command->args[0].pi < command->args[1].i) eventSystem.flags.less = 1;
				
				command->id = 0;
				break;
			case 5101:
				eventSystem.flags.equal = 0;
				eventSystem.flags.greater = 0;
				eventSystem.flags.less = 0;
				if (*command->args[0].pf == command->args[1].f) eventSystem.flags.equal = 1;
				if (*command->args[0].pf > command->args[1].f) eventSystem.flags.greater = 1;
				if (*command->args[0].pf < command->args[1].f) eventSystem.flags.less = 1;
				
				command->id = 0;
				break;
			case 5102:
				eventSystem.flags.equal = 0;
				eventSystem.flags.greater = 0;
				eventSystem.flags.less = 0;
				if (*command->args[0].pi == *command->args[1].pi) eventSystem.flags.equal = 1;
				if (*command->args[0].pi > *command->args[1].pi) eventSystem.flags.greater = 1;
				if (*command->args[0].pi < *command->args[1].pi) eventSystem.flags.less = 1;
				
				command->id = 0;
				break;
			case 5103:
				eventSystem.flags.equal = 0;
				eventSystem.flags.greater = 0;
				eventSystem.flags.less = 0;
				if (*command->args[0].pf == *command->args[1].pf) eventSystem.flags.equal = 1;
				if (*command->args[0].pf > *command->args[1].pf) eventSystem.flags.greater = 1;
				if (*command->args[0].pf < *command->args[1].pf) eventSystem.flags.less = 1;
				
				command->id = 0;
				break;
			case 5104:
				eventSystem.flags.equal = 0;
				eventSystem.flags.greater = 0;
				eventSystem.flags.less = 0;
				if (*command->args[0].pc == command->args[1].c) eventSystem.flags.equal = 1;
				if (*command->args[0].pc > command->args[1].c) eventSystem.flags.greater = 1;
				if (*command->args[0].pc < command->args[1].c) eventSystem.flags.less = 1;
				
				command->id = 0;
				break;
			case 5105:
				eventSystem.flags.equal = 0;
				eventSystem.flags.greater = 0;
				eventSystem.flags.less = 0;
				if (*command->args[0].pc == *command->args[1].pc) eventSystem.flags.equal = 1;
				if (*command->args[0].pc > *command->args[1].pc) eventSystem.flags.greater = 1;
				if (*command->args[0].pc < *command->args[1].pc) eventSystem.flags.less = 1;
				
				command->id = 0;
				break;
			
			case 9999:
				eventSystem.ptr = eventSystem.queueSize;
				command->id = 0;
				break;
		}
		
		if (command->id == 0) {
			eventSystem.runningSize--;
		}
	}
	
	for (int i = 0; i < eventSystem.runningSize; i++) {
		EventCommand* command = &eventSystem.running[i];
		
		Event_UpdateCommand(command);
		
		if (command->id == 0) {
			eventSystem.runningSize--;
			for (int j = i; j < eventSystem.runningSize; j++) {
				eventSystem.running[j] = eventSystem.running[j + 1];
			}
		}
	}
}

void Event_UpdateCommand(EventCommand* command) {
	switch (command->id) {
		case 1:
			if (Dialog_IsFinished()) {
				command->id = 0;
			}
			break;
		case 3: case 8: case 9: case 26: case 38: case 39: case 40:
			if (!overworld.objects[command->args[0].i].moveTarget.enabled) {
				command->id = 0;
			}
			break;
		case 4:
			if (game.scene == SCENE_OVERWORLD && (overworld.transition.id == 0 || overworld.transition.timer > 40)) {
				command->id = 0;
			}
			break;
		case 5: case 14:
			{
				float distance = PointDistance(overworld.camera.x, overworld.camera.y, command->args[0].f, command->args[1].f);
				
				if (distance <= command->args[2].f) {
					overworld.camera.x = command->args[0].f;
					overworld.camera.y = command->args[1].f;
					command->id = 0;
				}
				else {
					float direction = PointDirection(overworld.camera.x, overworld.camera.y, command->args[0].f, command->args[1].f);
					
					overworld.camera.x += cos(direction) * command->args[2].f;
					overworld.camera.y += sin(direction) * command->args[2].f;
				}
			}
			break;
		case 6:
			{
				bool finished = true;
				
				float distance = PointDistance(overworld.camera.x, overworld.camera.y, overworld.player.x, overworld.player.y - 8);
				
				if (distance <= command->args[0].f) {
					overworld.camera.x = overworld.player.x;
					overworld.camera.y = overworld.player.y - 8;
				}
				else {
					float direction = PointDirection(overworld.camera.x, overworld.camera.y, overworld.player.x, overworld.player.y - 8);
					
					overworld.camera.x += cos(direction) * command->args[0].f;
					overworld.camera.y += sin(direction) * command->args[0].f;
					finished = false;
				}
				
				for (int i = 0; i < 8; i++) {
					if (overworld.objects[i].moveTarget.enabled) {
						finished = false;
						break;
					}
				}
				
				if (finished) {
					command->id = 0;
				}
			}
			break;
		case 7:
			if (--command->args[0].i <= 0) {
				eventSystem.sync = command->args[1].i;
				command->id = 0;
			}
			break;
		case 21:
			if (overworld.transition.id != 1 || overworld.transition.timer >= 24) {
				command->id = 0;
			}
			break;
		case 28:
			overworld.fadeAlpha += command->args[0].f;
			if (overworld.fadeAlpha >= 1) {
				overworld.fadeAlpha = 1;
				command->id = 0;
			}
			break;
		case 29:
			overworld.fadeAlpha -= command->args[0].f;
			if (overworld.fadeAlpha <= 0) {
				overworld.fadeAlpha = 0;
				command->id = 0;
			}
			break;
		case 30: case 31:
			if (overworld.state == OVERWORLD_STATE_IDLE) {
				overworld.state = OVERWORLD_STATE_EVENT;
				command->id = 0;
			}
			break;
		case 34: case 35:
			if (overworld.transition.id == 0) {
				command->id = 0;
			}
			break;
		
		case 1029:
			{
				bool finished = true;
				switch (command->args[0].i) {
					case 1: {
						// Flower game
						
						bool stalemate = true;
						char fieldDamage[20];
						for (int i = 0; i < 20; i++) fieldDamage[i] = 0;
						
						for (int i = 0; i < 20; i++) {
							if (overworld.objects[eventSystem.vars[0].i + i].type == 0) continue;
							int opposite = i + 10 - (i >= 10) * 20;
							
							switch ((overworld.objects[eventSystem.vars[0].i + i].spriteFrame % 5)) {
								case 0:
									fieldDamage[opposite]++;
									break;
								case 1:
									fieldDamage[opposite - 1]++;
									fieldDamage[opposite + 1]++;
									break;
								case 2:
									fieldDamage[opposite]++;
									fieldDamage[i - 1]++;
									fieldDamage[i + 1]++;
									break;
							}
						}
						for (int i = 0; i < 20; i++) {
							if (overworld.objects[eventSystem.vars[0].i + i].type == 0) continue;
							if (overworld.objects[eventSystem.vars[0].i + i].spriteFrame % 5 == 4) continue;
							
							if (fieldDamage[i] >= 1) stalemate = false;
							
							int hp = 1 + (overworld.objects[eventSystem.vars[0].i + i].spriteFrame % 5);
							if (hp - fieldDamage[i] >= 1)
								overworld.objects[eventSystem.vars[0].i + i].spriteFrame -= fieldDamage[i];
							else
								overworld.objects[eventSystem.vars[0].i + i].spriteFrame = (overworld.objects[eventSystem.vars[0].i + i].spriteFrame / 5) * 5 + 4;
						}
						
						// End condition check
						eventSystem.flags.equal = 1; // Draw
						eventSystem.flags.less = 1; // Lose
						eventSystem.flags.greater = 1; // Win
						for (int i = 0; i < 10; i++) {
							if (overworld.objects[eventSystem.vars[0].i + i].type == 0) continue;
							if (overworld.objects[eventSystem.vars[0].i + i].spriteFrame % 5 == 4) continue;
							eventSystem.flags.less = 0;
							eventSystem.flags.equal = 0;
							break;
						}
						for (int i = 10; i < 20; i++) {
							if (overworld.objects[eventSystem.vars[0].i + i].type == 0) continue;
							if (overworld.objects[eventSystem.vars[0].i + i].spriteFrame % 5 == 4) continue;
							eventSystem.flags.greater = 0;
							eventSystem.flags.equal = 0;
							break;
						}
						if (!eventSystem.flags.equal && !eventSystem.flags.less && !eventSystem.flags.greater && stalemate) {
							eventSystem.flags.less = 1;
							eventSystem.flags.greater = 1;
						}
					} break;
					
					case 2: {
						// Chess puzzle skill check
						overworld.lastMusicId = audioSystem.currentMusicId;
						ChangeScene(SCENE_CHESS);
						eventSystem.paused = true;
					} break;
					
					case 3: {
						// Get timeline key
						int base = 1;
						for (int i = 0; i < overworld.objects[eventSystem.callerObjectId].vars[7].i; i++) {
							base *= 10;
						}
						profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] -= ((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / base) % 10) * base;
						profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] += 9 * base;
					} break;
					
					case 4: {
						// Get timeline key
						int keyId = overworld.objects[eventSystem.callerObjectId].vars[7].i;
						int color[3] = { (profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] & 0xff0000) >> 16, (profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] & 0xff00) >> 8, profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] & 0xff };
						int target[3] = { 255, 255, 255 };
						if (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] != 54321) {
							switch (keyId) {
								case 0: target[0] = 0; break;
								case 1: target[0] = 0; target[2] = 0; break;
								case 2: target[0] = 0; target[1] = 0; break;
								case 3: target[1] = 0; break;
								case 4: target[1] = 0; target[2] = 0; break;
							}
						}
						for (int i = 0; i < 3; i++) {
							if (color[i] < target[i]) {
								finished = false;
								color[i] += 3;
								if (color[i] > target[i]) color[i] = target[i];
							}
							else if (color[i] > target[i]) {
								finished = false;
								color[i] -= 3;
								if (color[i] < target[i]) color[i] = target[i];
							}
						}
						profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] = (color[0] << 16) | (color[1] << 8) | color[2];
					} break;
				}
				if (finished) command->id = 0;
			}
			break;
		
		default:
			command->id = 0;
			break;
	}
}



void Event_Queue_Dialog_Run(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Overworld_SetState(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 2;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Object_WalkToRelative(int id, float x, float y, float speed, int direction) {
	eventSystem.queue[eventSystem.queueSize].id = 3;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].f = speed;
	eventSystem.queue[eventSystem.queueSize].args[4].i = direction;
	eventSystem.queueSize++;
}

void Event_Queue_EngageBattle(int id, int enemyObjectId) {
	eventSystem.queue[eventSystem.queueSize].id = 4;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].i = enemyObjectId;
	eventSystem.queueSize++;
}

void Event_Queue_Camera_MoveToRelative(float x, float y, float speed) {
	eventSystem.queue[eventSystem.queueSize].id = 5;
	eventSystem.queue[eventSystem.queueSize].args[0].f = x;
	eventSystem.queue[eventSystem.queueSize].args[1].f = y;
	eventSystem.queue[eventSystem.queueSize].args[2].f = speed;
	eventSystem.queueSize++;
}

void Event_Queue_Regroup(float cameraSpeed) {
	eventSystem.queue[eventSystem.queueSize].id = 6;
	eventSystem.queue[eventSystem.queueSize].args[0].f = cameraSpeed;
	eventSystem.queueSize++;
}

void Event_Queue_WaitFrames(int frames) {
	eventSystem.queue[eventSystem.queueSize].id = 7;
	eventSystem.queue[eventSystem.queueSize].args[0].i = frames;
	eventSystem.queueSize++;
}

void Event_Queue_Object_WalkToPointer(int id, float x, float y, float speed, int direction, float* px, float* py) {
	eventSystem.queue[eventSystem.queueSize].id = 8;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].f = speed;
	eventSystem.queue[eventSystem.queueSize].args[4].i = direction;
	eventSystem.queue[eventSystem.queueSize].args[5].pf = px;
	eventSystem.queue[eventSystem.queueSize].args[6].pf = py;
	eventSystem.queueSize++;
}

void Event_Queue_Object_WalkTo(int id, float x, float y, float speed, int direction) {
	eventSystem.queue[eventSystem.queueSize].id = 9;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].f = speed;
	eventSystem.queue[eventSystem.queueSize].args[4].i = direction;
	eventSystem.queueSize++;
}

void Event_Queue_Object_ChangeDirection(int objectId, int direction) {
	eventSystem.queue[eventSystem.queueSize].id = 10;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = direction;
	eventSystem.queueSize++;
}

void Event_Queue_Object_ChangeSpriteId(int objectId, int spriteId) {
	eventSystem.queue[eventSystem.queueSize].id = 11;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = spriteId;
	eventSystem.queueSize++;
}

void Event_Queue_Object_ChangeSpriteFrame(int objectId, int spriteFrame) {
	eventSystem.queue[eventSystem.queueSize].id = 12;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = spriteFrame;
	eventSystem.queueSize++;
}

void Event_Queue_Object_Destroy(int objectId) {
	eventSystem.queue[eventSystem.queueSize].id = 13;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queueSize++;
}

void Event_Queue_Camera_MoveTo(float x, float y, float speed) {
	eventSystem.queue[eventSystem.queueSize].id = 14;
	eventSystem.queue[eventSystem.queueSize].args[0].f = x;
	eventSystem.queue[eventSystem.queueSize].args[1].f = y;
	eventSystem.queue[eventSystem.queueSize].args[2].f = speed;
	eventSystem.queueSize++;
}

void Event_Queue_Player_SetPositionSync(bool value) {
	eventSystem.queue[eventSystem.queueSize].id = 15;
	eventSystem.queue[eventSystem.queueSize].args[0].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_Object_TeleportTo(int id, float x, float y) {
	eventSystem.queue[eventSystem.queueSize].id = 16;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queueSize++;
}

void Event_Queue_Object_TeleportToPointer(int id, float x, float y, float* px, float* py) {
	eventSystem.queue[eventSystem.queueSize].id = 17;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].pf = px;
	eventSystem.queue[eventSystem.queueSize].args[4].pf = py;
	eventSystem.queueSize++;
}

void Event_Queue_CreateObject(int objectId, int type, int id, float x, float y, int direction) {
	eventSystem.queue[eventSystem.queueSize].id = 18;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = type;
	eventSystem.queue[eventSystem.queueSize].args[2].i = id;
	eventSystem.queue[eventSystem.queueSize].args[3].f = x;
	eventSystem.queue[eventSystem.queueSize].args[4].f = y;
	eventSystem.queue[eventSystem.queueSize].args[5].i = direction;
	eventSystem.queueSize++;
}

void Event_Queue_CreateNPC(int objectId, int id, float x, float y, int direction) {
	eventSystem.queue[eventSystem.queueSize].id = 19;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = id;
	eventSystem.queue[eventSystem.queueSize].args[2].f = x;
	eventSystem.queue[eventSystem.queueSize].args[3].f = y;
	eventSystem.queue[eventSystem.queueSize].args[4].i = direction;
	eventSystem.queueSize++;
}

void Event_Queue_CreateEnemy(int objectId, int id, float x, float y) {
	eventSystem.queue[eventSystem.queueSize].id = 20;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = id;
	eventSystem.queue[eventSystem.queueSize].args[2].f = x;
	eventSystem.queue[eventSystem.queueSize].args[3].f = y;
	eventSystem.queueSize++;
}

void Event_Queue_GotoArea(int areaId, float x, float y, int tilesetSpriteId) {
	eventSystem.queue[eventSystem.queueSize].id = 21;
	eventSystem.queue[eventSystem.queueSize].args[0].i = areaId;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].i = tilesetSpriteId;
	eventSystem.queueSize++;
}

void Event_Queue_Object_EnableFighterSprite(int objectId, int headId, int bodyId, int fighterState) {
	eventSystem.queue[eventSystem.queueSize].id = 22;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = headId;
	eventSystem.queue[eventSystem.queueSize].args[2].i = bodyId;
	eventSystem.queue[eventSystem.queueSize].args[3].i = fighterState;
	eventSystem.queueSize++;
}

void Event_Queue_Object_DisableFighterSprite(int objectId) {
	eventSystem.queue[eventSystem.queueSize].id = 23;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queueSize++;
}

void Event_Queue_Object_ChangeSpriteFrameSpeed(int objectId, float spriteFrameSpeed) {
	eventSystem.queue[eventSystem.queueSize].id = 24;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].f = spriteFrameSpeed;
	eventSystem.queueSize++;
}

void Event_Queue_Object_ToggleWalkAnimation(int objectId, bool value) {
	eventSystem.queue[eventSystem.queueSize].id = 25;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_Object_QueueWalkTo(int id, float x, float y, float speed, int direction) {
	eventSystem.queue[eventSystem.queueSize].id = 26;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].f = speed;
	eventSystem.queue[eventSystem.queueSize].args[4].i = direction;
	eventSystem.queueSize++;
}

void Event_Queue_Camera_TogglePlayerFollow(bool value) {
	eventSystem.queue[eventSystem.queueSize].id = 27;
	eventSystem.queue[eventSystem.queueSize].args[0].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_FadeOut(float speed) {
	eventSystem.queue[eventSystem.queueSize].id = 28;
	eventSystem.queue[eventSystem.queueSize].args[0].f = speed;
	eventSystem.queueSize++;
}

void Event_Queue_FadeIn(float speed) {
	eventSystem.queue[eventSystem.queueSize].id = 29;
	eventSystem.queue[eventSystem.queueSize].args[0].f = speed;
	eventSystem.queueSize++;
}

void Event_Queue_OpenShopMenu(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 30;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_OpenSaveMenu() {
	eventSystem.queue[eventSystem.queueSize].id = 31;
	eventSystem.queueSize++;
}

void Event_Queue_Camera_TeleportTo(float x, float y) {
	eventSystem.queue[eventSystem.queueSize].id = 32;
	eventSystem.queue[eventSystem.queueSize].args[0].f = x;
	eventSystem.queue[eventSystem.queueSize].args[1].f = y;
	eventSystem.queueSize++;
}

void Event_Queue_Object_ToggleGhost(int objectId, bool value) {
	eventSystem.queue[eventSystem.queueSize].id = 33;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_Overworld_FadeIn(int time, uint8_t r, uint8_t g, uint8_t b) {
	eventSystem.queue[eventSystem.queueSize].id = 34;
	eventSystem.queue[eventSystem.queueSize].args[0].i = time;
	eventSystem.queue[eventSystem.queueSize].args[1].i = r;
	eventSystem.queue[eventSystem.queueSize].args[2].i = g;
	eventSystem.queue[eventSystem.queueSize].args[3].i = b;
	eventSystem.queueSize++;
}

void Event_Queue_Overworld_FadeOut(int time, uint8_t r, uint8_t g, uint8_t b) {
	eventSystem.queue[eventSystem.queueSize].id = 35;
	eventSystem.queue[eventSystem.queueSize].args[0].i = time;
	eventSystem.queue[eventSystem.queueSize].args[1].i = r;
	eventSystem.queue[eventSystem.queueSize].args[2].i = g;
	eventSystem.queue[eventSystem.queueSize].args[3].i = b;
	eventSystem.queueSize++;
}

void Event_Queue_CreateTrigger(int id, float x1, float y1, float x2, float y2, int eventId) {
	eventSystem.queue[eventSystem.queueSize].id = 36;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x1;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y1;
	eventSystem.queue[eventSystem.queueSize].args[3].f = x2;
	eventSystem.queue[eventSystem.queueSize].args[4].f = y2;
	eventSystem.queue[eventSystem.queueSize].args[5].i = eventId;
	eventSystem.queueSize++;
}

void Event_Queue_Overworld_ShakeScreen(int timer) {
	eventSystem.queue[eventSystem.queueSize].id = 37;
	eventSystem.queue[eventSystem.queueSize].args[0].i = timer;
	eventSystem.queueSize++;
}

void Event_Queue_Object_JumpToPointer(int id, float x, float y, int direction, float jumpHeight, int jumpTime, float* px, float* py) {
	eventSystem.queue[eventSystem.queueSize].id = 38;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].i = direction;
	eventSystem.queue[eventSystem.queueSize].args[4].f = jumpHeight;
	eventSystem.queue[eventSystem.queueSize].args[5].i = jumpTime;
	eventSystem.queue[eventSystem.queueSize].args[6].pf = px;
	eventSystem.queue[eventSystem.queueSize].args[7].pf = py;
	eventSystem.queueSize++;
}

void Event_Queue_Object_JumpTo(int id, float x, float y, int direction, float jumpHeight, int jumpTime) {
	eventSystem.queue[eventSystem.queueSize].id = 39;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].i = direction;
	eventSystem.queue[eventSystem.queueSize].args[4].f = jumpHeight;
	eventSystem.queue[eventSystem.queueSize].args[5].i = jumpTime;
	eventSystem.queueSize++;
}

void Event_Queue_Object_JumpToRelative(int id, float x, float y, int direction, float jumpHeight, int jumpTime) {
	eventSystem.queue[eventSystem.queueSize].id = 40;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].i = direction;
	eventSystem.queue[eventSystem.queueSize].args[4].f = jumpHeight;
	eventSystem.queue[eventSystem.queueSize].args[5].i = jumpTime;
	eventSystem.queueSize++;
}

void Event_Queue_Object_SetColor(int objectId, uint8_t r, uint8_t g, uint8_t b) {
	eventSystem.queue[eventSystem.queueSize].id = 41;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = r;
	eventSystem.queue[eventSystem.queueSize].args[2].i = g;
	eventSystem.queue[eventSystem.queueSize].args[3].i = b;
	eventSystem.queueSize++;
}

void Event_Queue_CreateSpark(int id, float x, float y, int depth) {
	eventSystem.queue[eventSystem.queueSize].id = 42;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = x;
	eventSystem.queue[eventSystem.queueSize].args[2].f = y;
	eventSystem.queue[eventSystem.queueSize].args[3].i = depth;
	eventSystem.queueSize++;
}

void Event_Queue_Object_SetCollisionSize(int objectId, int w, int h) {
	eventSystem.queue[eventSystem.queueSize].id = 43;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].i = w;
	eventSystem.queue[eventSystem.queueSize].args[2].i = h;
	eventSystem.queueSize++;
}

void Event_Queue_Object_SetPositionZ(int objectId, float z) {
	eventSystem.queue[eventSystem.queueSize].id = 44;
	eventSystem.queue[eventSystem.queueSize].args[0].i = objectId;
	eventSystem.queue[eventSystem.queueSize].args[1].f = z;
	eventSystem.queueSize++;
}



void Event_Queue_RemoveCurrentTrigger() {
	eventSystem.queue[eventSystem.queueSize].id = 1000;
	eventSystem.queueSize++;
}

void Event_Queue_SetSync(bool value) {
	eventSystem.queue[eventSystem.queueSize].id = 1001;
	eventSystem.queue[eventSystem.queueSize].args[0].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetVarInt(int id, int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1002;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetVarFloat(int id, float value) {
	eventSystem.queue[eventSystem.queueSize].id = 1003;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].f = value;
	eventSystem.queueSize++;
}

void Event_Queue_SaveToVarInt(int id, int* value) {
	eventSystem.queue[eventSystem.queueSize].id = 1004;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].pi = value;
	eventSystem.queueSize++;
}

void Event_Queue_SaveToVarFloat(int id, float* value) {
	eventSystem.queue[eventSystem.queueSize].id = 1005;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].pf = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetFlag(int id, int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1006;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_Party_Join(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1007;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Party_Leave(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1008;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_InventoryPartyOrderAdd(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1009;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_InventoryPartyOrderRemove(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1010;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_SetIntPtr(int* p, int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1011;
	eventSystem.queue[eventSystem.queueSize].args[0].pi = p;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetFloatPtr(float* p, float value) {
	eventSystem.queue[eventSystem.queueSize].id = 1012;
	eventSystem.queue[eventSystem.queueSize].args[0].pf = p;
	eventSystem.queue[eventSystem.queueSize].args[1].f = value;
	eventSystem.queueSize++;
}

void Event_Queue_AddCash(int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1013;
	eventSystem.queue[eventSystem.queueSize].args[0].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetCash(int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1014;
	eventSystem.queue[eventSystem.queueSize].args[0].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_ItemAdd(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1015;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_ItemRemove(int inventoryId) {
	eventSystem.queue[eventSystem.queueSize].id = 1016;
	eventSystem.queue[eventSystem.queueSize].args[0].i = inventoryId;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_ClearItemInventory() {
	eventSystem.queue[eventSystem.queueSize].id = 1017;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_KeyItemAdd(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1018;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_KeyItemRemove(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1019;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_Profile_KeyItemExists(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1020;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_PlayMusic(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1021;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_StopMusic() {
	eventSystem.queue[eventSystem.queueSize].id = 1022;
	eventSystem.queueSize++;
}

void Event_Queue_PlaySound(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1023;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_FadeOutMusic(int ms) {
	eventSystem.queue[eventSystem.queueSize].id = 1024;
	eventSystem.queue[eventSystem.queueSize].args[0].i = ms;
	eventSystem.queueSize++;
}

void Event_Queue_SetIntPtrToPtr(int* p, int* value) {
	eventSystem.queue[eventSystem.queueSize].id = 1025;
	eventSystem.queue[eventSystem.queueSize].args[0].pi = p;
	eventSystem.queue[eventSystem.queueSize].args[1].pi = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetFloatPtrToPtr(float* p, float* value) {
	eventSystem.queue[eventSystem.queueSize].id = 1026;
	eventSystem.queue[eventSystem.queueSize].args[0].pf = p;
	eventSystem.queue[eventSystem.queueSize].args[1].pf = value;
	eventSystem.queueSize++;
}

void Event_Queue_AddIntPtr(int* p, int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1027;
	eventSystem.queue[eventSystem.queueSize].args[0].pi = p;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_AddFloatPtr(float* p, float value) {
	eventSystem.queue[eventSystem.queueSize].id = 1028;
	eventSystem.queue[eventSystem.queueSize].args[0].pf = p;
	eventSystem.queue[eventSystem.queueSize].args[1].f = value;
	eventSystem.queueSize++;
}

void Event_Queue_CustomAction(int id) {
	eventSystem.queue[eventSystem.queueSize].id = 1029;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queueSize++;
}

void Event_Queue_FullyHealParty() {
	eventSystem.queue[eventSystem.queueSize].id = 1030;
	eventSystem.queueSize++;
}

void Event_Queue_SetTempFlag(int id, int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1031;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_AddFlag(int id, int value) {
	eventSystem.queue[eventSystem.queueSize].id = 1032;
	eventSystem.queue[eventSystem.queueSize].args[0].i = id;
	eventSystem.queue[eventSystem.queueSize].args[1].i = value;
	eventSystem.queueSize++;
}

void Event_Queue_SetBoolPtr(bool* p, bool value) {
	eventSystem.queue[eventSystem.queueSize].id = 1033;
	eventSystem.queue[eventSystem.queueSize].args[0].pb = p;
	eventSystem.queue[eventSystem.queueSize].args[1].b = value;
	eventSystem.queueSize++;
}



void Event_Queue_Jump(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5000;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfEqual(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5001;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfTrue(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5001;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfLess(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5002;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfGreater(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5003;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfLessEqual(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5004;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfGreaterEqual(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5005;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfNotEqual(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5006;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}

void Event_Queue_JumpIfFalse(int label) {
	eventSystem.queue[eventSystem.queueSize].id = 5006;
	eventSystem.queue[eventSystem.queueSize].args[0].i = label;
	eventSystem.queueSize++;
}



void Event_Queue_CompareIntToConst(int* a, const int b) {
	eventSystem.queue[eventSystem.queueSize].id = 5100;
	eventSystem.queue[eventSystem.queueSize].args[0].pi = a;
	eventSystem.queue[eventSystem.queueSize].args[1].i = b;
	eventSystem.queueSize++;
}

void Event_Queue_CompareFloatToConst(float* a, const float b) {
	eventSystem.queue[eventSystem.queueSize].id = 5101;
	eventSystem.queue[eventSystem.queueSize].args[0].pf = a;
	eventSystem.queue[eventSystem.queueSize].args[1].f = b;
	eventSystem.queueSize++;
}

void Event_Queue_CompareIntToVar(int* a, int* b) {
	eventSystem.queue[eventSystem.queueSize].id = 5102;
	eventSystem.queue[eventSystem.queueSize].args[0].pi = a;
	eventSystem.queue[eventSystem.queueSize].args[1].pi = b;
	eventSystem.queueSize++;
}

void Event_Queue_CompareFloatToVar(float* a, float* b) {
	eventSystem.queue[eventSystem.queueSize].id = 5103;
	eventSystem.queue[eventSystem.queueSize].args[0].pf = a;
	eventSystem.queue[eventSystem.queueSize].args[1].pf = b;
	eventSystem.queueSize++;
}

void Event_Queue_CompareCharToConst(char* a, const char b) {
	eventSystem.queue[eventSystem.queueSize].id = 5104;
	eventSystem.queue[eventSystem.queueSize].args[0].pc = a;
	eventSystem.queue[eventSystem.queueSize].args[1].c = b;
	eventSystem.queueSize++;
}

void Event_Queue_CompareCharToVar(char* a, char* b) {
	eventSystem.queue[eventSystem.queueSize].id = 5105;
	eventSystem.queue[eventSystem.queueSize].args[0].pc = a;
	eventSystem.queue[eventSystem.queueSize].args[1].pc = b;
	eventSystem.queueSize++;
}



void Event_Queue_Exit() {
	eventSystem.queue[eventSystem.queueSize].id = 9999;
	eventSystem.queueSize++;
}

void Event_Queue_Label(int id) {
	if (id < 0 || id >= 64) return;
	
	eventSystem.labels[id] = eventSystem.queueSize;
}
