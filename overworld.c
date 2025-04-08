#include "generic.h"
#include "overworld.h"
#include "sprites.h"
#include "audio.h"
#include "dialog.h"
#include "party.h"
#include "battlesystem.h"
#include "profile.h"
#include "action.h"
#include "armor.h"
#include "items.h"
#include "passives.h"
#include "event.h"
#include "fighters.h"

Overworld overworld;



void OverworldObject_Destroy(int objectId) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->type = 0;
}

void OverworldObject_SetCollisionSize(int objectId, int w, int h) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->w = w;
	object->h = h;
}

void OverworldObject_SetPositionZ(int objectId, float z) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->z = z;
}

void OverworldObject_ChangeDirection(int objectId, int direction) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->direction = direction;
	if (object->spriteType == 1) {
		switch (object->direction) {
			case OBJECT_DIRECTION_LEFT: object->spriteFrame = 2; break;
			case OBJECT_DIRECTION_RIGHT: object->spriteFrame = 2; break;
			case OBJECT_DIRECTION_UP: object->spriteFrame = 1; break;
			case OBJECT_DIRECTION_DOWN: object->spriteFrame = 0; break;
		}
	}
}

void OverworldObject_ChangeSpriteId(int objectId, int spriteId) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->spriteId = spriteId;
	object->spriteType = 0;
	if (spriteId >= FIRST_SPR_owchar && spriteId <= LAST_SPR_owchar) {
		object->spriteType = 1;
	}
}

void OverworldObject_ChangeSpriteFrame(int objectId, int spriteFrame) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->spriteFrame = spriteFrame;
}

void OverworldObject_ChangeSpriteFrameSpeed(int objectId, float spriteFrameSpeed) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->spriteFrameSpeed = spriteFrameSpeed;
}

void OverworldObject_WalkTo(int objectId, float x, float y, float speed, int direction) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->moveTarget.enabled = true;
	object->moveTarget.x = x;
	object->moveTarget.y = y;
	object->moveTarget.speed = speed;
	object->moveTarget.direction = direction;
	object->moveTarget.jumpTime = -1;
}

void OverworldObject_QueueWalkTo(int objectId, float x, float y, float speed, int direction) {
	OverworldObject* object = &overworld.objects[objectId];
	if (!object->moveTarget.enabled) {
		OverworldObject_WalkTo(objectId, x, y, speed, direction);
		return;
	}
	MoveTarget* moveTarget = NULL;
	for (int i = 0; i < MOVETARGET_QUEUE_MAX; i++) {
		if (!object->moveTargetQueue[i].enabled) {
			moveTarget = &object->moveTargetQueue[i];
			break;
		}
	}
	
	if (moveTarget == NULL) return;
	
	moveTarget->enabled = true;
	moveTarget->x = x;
	moveTarget->y = y;
	moveTarget->speed = speed;
	moveTarget->direction = direction;
	moveTarget->jumpTime = -1;
}

void OverworldObject_JumpTo(int objectId, float x, float y, int direction, float jumpHeight, int jumpTime) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->moveTarget.enabled = true;
	object->moveTarget.x = x;
	object->moveTarget.y = y;
	object->moveTarget.speed = PointDistance(object->x, object->y, x, y) / jumpTime;
	object->moveTarget.direction = direction;
	object->moveTarget.jumpTime = jumpTime;
	object->moveTarget.jumpHeight = jumpHeight;
}

void OverworldObject_TryMove(int objectId, float xMove, float yMove) {
	OverworldObject* object = &overworld.objects[objectId];
	
	float xNew = object->x + xMove;
	float yNew = object->y + yMove;
	
	if (!object->ghost) {
		for (int i = 0; i < DECORATION_COUNT_MAX; i++) {
			OverworldObject* object2 = &overworld.map.decorations[i];
			
			if (xNew + 7 > object2->x - object2->w / 2 + object2->collisionOffsetX && xNew - 7 < object2->x + object2->w / 2 + object2->collisionOffsetX && yNew + 8 > object2->y - object2->h + object2->collisionOffsetY && yNew - 16 < object2->y + object2->collisionOffsetY) {
				return;
			}
		}
		
		if ((overworld.state == OVERWORLD_STATE_IDLE || overworld.state == OVERWORLD_STATE_PAUSED) && object->type != 3) {
			if (overworld.player.x + 7 > xNew - object->w / 2 && overworld.player.x - 7 < xNew + object->w / 2 && overworld.player.y + 8 > yNew - object->h && overworld.player.y - 16 < yNew) {
				return;
			}
			
			for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
				if ((i >= 8 || overworld.objects[i].spriteId < 0) && (overworld.objects[i].type == 0 || overworld.objects[i].type == 1 || overworld.objects[i].type == 3 || i == objectId)) continue;
				if (overworld.objects[i].w == 0 || overworld.objects[i].h == 0 || overworld.objects[i].ghost) continue;
				
				OverworldObject* object2 = &overworld.objects[i];
				
				if (xNew + 7 > object2->x - object2->w / 2 + object2->collisionOffsetX && xNew - 7 < object2->x + object2->w / 2 + object2->collisionOffsetX && yNew + 8 > object2->y - object2->h + object2->collisionOffsetY && yNew - 16 < object2->y + object2->collisionOffsetY) {
					return;
				}
			}
		}
		
		for (int j = object->y / 16 - 2; j <= object->y / 16 + 2; j++)
		for (int i = object->x / 16 - 2; i <= object->x / 16 + 2; i++) {
			if (i < 0 || i >= overworld.map.w || j < 0 || j >= overworld.map.h) continue;
			
			int data = overworld.map.tileData[overworld.map.tileMap[j][i]];
			float tileX = i * 16;
			float tileY = j * 16;
			
			if (data == 1 || (data >= 60 && data < 100)) {
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
			}
			if (data == 2 || data == 6 || data == 7) {
				if (object->x + 7 > tileX && object->x - 7 < tileX + 16 && object->y > tileY && object->y - 8 < tileY + 16)
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY-16 && yNew - 8 < tileY-16 + 16) {
					return;
				}
				if (object->x + 7 > tileX && object->x - 7 < tileX + 16 && object->y > tileY-16 && object->y - 8 < tileY-16 + 16)
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
			}
			if (data == 3 || data == 8 || data == 9) {
				if (object->x + 7 > tileX && object->x - 7 < tileX + 16 && object->y > tileY && object->y - 8 < tileY + 16)
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY+16 && yNew - 8 < tileY+16 + 16) {
					return;
				}
				if (object->x + 7 > tileX && object->x - 7 < tileX + 16 && object->y > tileY+16 && object->y - 8 < tileY+16 + 16)
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
			}
			if (data == 4 || data == 6 || data == 8) {
				if (object->x + 7 > tileX && object->x - 7 < tileX + 16 && object->y > tileY && object->y - 8 < tileY + 16)
				if (xNew + 7 > tileX-16 && xNew - 7 < tileX-16 + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
				if (object->x + 7 > tileX-16 && object->x - 7 < tileX-16 + 16 && object->y > tileY && object->y - 8 < tileY + 16)
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
			}
			if (data == 5 || data == 7 || data == 9) {
				if (object->x + 7 > tileX && object->x - 7 < tileX + 16 && object->y > tileY && object->y - 8 < tileY + 16)
				if (xNew + 7 > tileX+16 && xNew - 7 < tileX+16 + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
				if (object->x + 7 > tileX+16 && object->x - 7 < tileX+16 + 16 && object->y > tileY && object->y - 8 < tileY + 16)
				if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
					return;
				}
			}
		}
	}
	
	object->x = xNew;
	object->y = yNew;
}

void OverworldObject_EnableFighterSprite(int objectId, int headId, int bodyId, int fighterState) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->headId = headId;
	object->bodyId = bodyId;
	object->fighterState = fighterState;
}

void OverworldObject_DisableFighterSprite(int objectId) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->bodyId = -1;
}

void OverworldObject_ToggleWalkAnimation(int objectId, bool value) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->walkAnimationEnabled = value;
}

void OverworldObject_SetColor(int objectId, uint8_t r, uint8_t g, uint8_t b) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->color[0] = r;
	object->color[1] = g;
	object->color[2] = b;
}

void OverworldObject_ToggleGhost(int objectId, bool value) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->ghost = value;
}



void Overworld_Init() {
	overworld.shakeTimer = 0;
	Player_TryMove(0, 0);
	
	if (profile.flags[FLAG_PLOT] == 0) {
		profile.flags[FLAG_PLOT] = 1;
		Event_Trigger(22);
	}
}

void Overworld_Update() {
	bool walking = 0;
	
	if (overworld.player.invincibleFrames > 0) overworld.player.invincibleFrames--;
	
	if (overworld.shakeTimer > 0) overworld.shakeTimer--;
	
	if (overworld.state == OVERWORLD_STATE_IDLE && overworld.transition.id == 0) {
		int previousPlayerState = overworld.player.state;
		if (overworld.player.state == PLAYER_STATE_FLINCH) {
			if (overworld.player.timer >= 28) {
				overworld.player.state = PLAYER_STATE_IDLE;
				overworld.player.timer = 0;
			}
		}
		else {
			//bool running = (!game.settings.autoRun && PlayerButtonHeld(PLAYER_BUTTON_X)) || (game.settings.autoRun && !PlayerButtonHeld(PLAYER_BUTTON_X));
			bool running = !PlayerButtonHeld(PLAYER_BUTTON_X);
			
			if (PlayerButtonHeld(PLAYER_BUTTON_LEFT)) {
				walking = 1;
				if (overworld.player.state == PLAYER_STATE_IDLE) {
					overworld.player.state = PLAYER_STATE_WALK;
					overworld.player.timer = 0;
				}
				
				if ((!PlayerButtonHeld(PLAYER_BUTTON_UP) && !PlayerButtonHeld(PLAYER_BUTTON_DOWN)) || previousPlayerState == PLAYER_STATE_IDLE) overworld.player.direction = OBJECT_DIRECTION_LEFT;
				Player_TryMove(-1, 0);
				Player_TryMove(-1, 0);
				if (PlayerButtonHeld(PLAYER_BUTTON_A) && game.debug) {
					Player_TryMove(-4, 0);
					Player_TryMove(-4, 0);
				}
				else if (overworld.player.dashing) {
					Player_TryMove(-2, 0);
					Player_TryMove(-2, 0);
				}
				else if (running) {
					Player_TryMove(-1, 0);
				}
			}
			if (PlayerButtonHeld(PLAYER_BUTTON_RIGHT)) {
				walking = 1;
				if (overworld.player.state == PLAYER_STATE_IDLE) {
					overworld.player.state = PLAYER_STATE_WALK;
					overworld.player.timer = 0;
				}
				
				if ((!PlayerButtonHeld(PLAYER_BUTTON_UP) && !PlayerButtonHeld(PLAYER_BUTTON_DOWN)) || previousPlayerState == PLAYER_STATE_IDLE) overworld.player.direction = OBJECT_DIRECTION_RIGHT;
				Player_TryMove(1, 0);
				Player_TryMove(1, 0);
				if (PlayerButtonHeld(PLAYER_BUTTON_A) && game.debug) {
					Player_TryMove(4, 0);
					Player_TryMove(4, 0);
				}
				else if (overworld.player.dashing) {
					Player_TryMove(2, 0);
					Player_TryMove(2, 0);
				}
				else if (running) {
					Player_TryMove(1, 0);
				}
			}
			if (PlayerButtonHeld(PLAYER_BUTTON_UP)) {
				walking = 1;
				if (overworld.player.state == PLAYER_STATE_IDLE) {
					overworld.player.state = PLAYER_STATE_WALK;
					overworld.player.timer = 0;
				}
				
				if ((!PlayerButtonHeld(PLAYER_BUTTON_LEFT) && !PlayerButtonHeld(PLAYER_BUTTON_RIGHT)) || previousPlayerState == PLAYER_STATE_IDLE) overworld.player.direction = OBJECT_DIRECTION_UP;
				Player_TryMove(0, -1);
				Player_TryMove(0, -1);
				if (PlayerButtonHeld(PLAYER_BUTTON_A) && game.debug) {
					Player_TryMove(0, -4);
					Player_TryMove(0, -4);
				}
				else if (overworld.player.dashing) {
					Player_TryMove(0, -2);
					Player_TryMove(0, -2);
				}
				else if (running) {
					Player_TryMove(0, -1);
				}
			}
			if (PlayerButtonHeld(PLAYER_BUTTON_DOWN)) {
				walking = 1;
				if (overworld.player.state == PLAYER_STATE_IDLE) {
					overworld.player.state = PLAYER_STATE_WALK;
					overworld.player.timer = 0;
				}
				
				if ((!PlayerButtonHeld(PLAYER_BUTTON_LEFT) && !PlayerButtonHeld(PLAYER_BUTTON_RIGHT)) || previousPlayerState == PLAYER_STATE_IDLE) overworld.player.direction = OBJECT_DIRECTION_DOWN;
				Player_TryMove(0, 1);
				Player_TryMove(0, 1);
				if (PlayerButtonHeld(PLAYER_BUTTON_A) && game.debug) {
					Player_TryMove(0, 4);
					Player_TryMove(0, 4);
				}
				else if (overworld.player.dashing) {
					Player_TryMove(0, 2);
					Player_TryMove(0, 2);
				}
				else if (running) {
					Player_TryMove(0, 1);
				}
			}
			if (!walking) {
				if (game.timer % 60 == 0) {
					OverworldObject* object1 = NULL;
					OverworldObject* object2 = NULL;
					for (int i = 0; i < 5; i++) {
						if (profile.party[i] == 0)
							object1 = &overworld.objects[i];
						else if (profile.party[i] == 1)
							object2 = &overworld.objects[i];
					}
					
					if (object1 != NULL && object2 != NULL) {
						if ((object1->direction == OBJECT_DIRECTION_LEFT && object2->direction == OBJECT_DIRECTION_RIGHT && object1->x >= object2->x)
						|| (object1->direction == OBJECT_DIRECTION_RIGHT && object2->direction == OBJECT_DIRECTION_LEFT && object1->x <= object2->x)
						|| (object1->direction == OBJECT_DIRECTION_UP && object2->direction == OBJECT_DIRECTION_DOWN && object1->y >= object2->y)
						|| (object1->direction == OBJECT_DIRECTION_DOWN && object2->direction == OBJECT_DIRECTION_UP && object1->y <= object2->y)
						) {
							overworld.player.blushTimer++;
							
							if (overworld.player.blushTimer == 26 && object1->spriteId == SPR_owchar_ruby) {
								object1->spriteId = SPR_owchar_ruby_blush;
							}
						}
						else
							overworld.player.blushTimer = 0;
					}
					else
						overworld.player.blushTimer = 0;
				}
				
				if (overworld.player.dashing) {
					switch (overworld.player.direction) {
						case OBJECT_DIRECTION_LEFT:
							Player_TryMove(-2, 0);
							Player_TryMove(-2, 0);
							Player_TryMove(-2, 0);
							break;
						case OBJECT_DIRECTION_RIGHT:
							Player_TryMove(2, 0);
							Player_TryMove(2, 0);
							Player_TryMove(2, 0);
							break;
						case OBJECT_DIRECTION_UP:
							Player_TryMove(0, -2);
							Player_TryMove(0, -2);
							Player_TryMove(0, -2);
							break;
						case OBJECT_DIRECTION_DOWN:
							Player_TryMove(0, 2);
							Player_TryMove(0, 2);
							Player_TryMove(0, 2);
							break;
					}
					walking = 1;
					
					if (PlayerButtonHeld(PLAYER_BUTTON_X)) {
						overworld.player.dashing = false;
						Party_UpdateCaterpillar();
					}
				}
				else if (overworld.player.dashEnabled && profile.flags[FLAG_RUBY_LABCOAT]) {
					int dashChargeTimerMax = 50 - (profile.flags[FLAG_RUBY_GODMODE] > 0) * 49;
					if (PlayerButtonHeld(PLAYER_BUTTON_X)) {
						overworld.player.dashChargeTimer++;
						if (overworld.player.dashChargeTimer == 1 || overworld.player.dashChargeTimer == dashChargeTimerMax) {
							Party_UpdateCaterpillar();
						}
					}
					else {
						if (overworld.player.dashChargeTimer >= dashChargeTimerMax) {
							overworld.player.dashing = true;
							overworld.player.state = PLAYER_STATE_WALK;
							overworld.player.timer = 0;
							walking = 1;
						}
						if (overworld.player.dashChargeTimer > 0) {
							overworld.player.dashChargeTimer = 0;
							Party_UpdateCaterpillar();
						}
					}
				}
			}
			else {
				overworld.player.blushTimer = 0;
				if (overworld.player.dashChargeTimer > 0) {
					overworld.player.dashChargeTimer = 0;
					Party_UpdateCaterpillar();
				}
			}
			
			if (PlayerButtonPressed(PLAYER_BUTTON_S) && false) {
				Event_Trigger(-1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Camera_TogglePlayerFollow(true);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Object_JumpToRelative(0, -64 * (overworld.player.direction == OBJECT_DIRECTION_LEFT) + 64 * (overworld.player.direction == OBJECT_DIRECTION_RIGHT), -64 * (overworld.player.direction == OBJECT_DIRECTION_UP) + 64 * (overworld.player.direction == OBJECT_DIRECTION_DOWN), -1, 64, 120);
				Event_Queue_Regroup(4);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
			}
			
			if (PlayerButtonPressed(PLAYER_BUTTON_C) && profile.flags[FLAG_RUBY_LABCOAT]) {
				overworld.state = OVERWORLD_STATE_PAUSED;
				Overworld_ChangeMenu(1);
				Menu_ResetCursor(&overworld.menu);
				
				if (overworld.player.dashEnabled) {
					overworld.player.dashing = false;
					overworld.player.dashChargeTimer = 0;
					Party_UpdateCaterpillar();
				}
			}
		}
	}
	else if (overworld.state == OVERWORLD_STATE_PAUSED) {
		if (PlayerButtonPressed(PLAYER_BUTTON_C) && overworld.menu.id < 10000) {
			overworld.state = OVERWORLD_STATE_IDLE;
			Audio_PlaySound(SND_menu3);
		}
	}
	
	
	
	float futurePlayerX = overworld.player.x;
	float futurePlayerY = overworld.player.y;
	
	overworld.player.x = futurePlayerX;
	overworld.player.y = futurePlayerY;
	
	OverworldObject* playerObject = &overworld.objects[0];
	
	overworld.player.timer++;
	
	if (!walking && overworld.player.state == PLAYER_STATE_WALK) {
		overworld.player.state = PLAYER_STATE_IDLE;
		overworld.player.timer = 0;
		
		switch (overworld.player.direction) {
			case OBJECT_DIRECTION_LEFT: playerObject->spriteFrame = 2; break;
			case OBJECT_DIRECTION_RIGHT: playerObject->spriteFrame = 2; break;
			case OBJECT_DIRECTION_UP: playerObject->spriteFrame = 1; break;
			case OBJECT_DIRECTION_DOWN: playerObject->spriteFrame = 0; break;
		}
		
		for (int i = 1; i < 8; i++) {
			OverworldObject* object = &overworld.objects[i];
			
			switch (overworld.caterpillar[i * 16].direction) {
				case OBJECT_DIRECTION_LEFT: object->spriteFrame = 2; break;
				case OBJECT_DIRECTION_RIGHT: object->spriteFrame = 2; break;
				case OBJECT_DIRECTION_UP: object->spriteFrame = 1; break;
				case OBJECT_DIRECTION_DOWN: object->spriteFrame = 0; break;
			}
		}
	}
	
	if (overworld.player.state == PLAYER_STATE_WALK) {
		if (overworld.player.dashing && overworld.player.timer % 3 == 0) {
			overworld.player.timer++;
		}
		switch (overworld.player.direction) {
			case OBJECT_DIRECTION_LEFT: playerObject->spriteFrame = 2; break;
			case OBJECT_DIRECTION_RIGHT: playerObject->spriteFrame = 2; break;
			case OBJECT_DIRECTION_UP: playerObject->spriteFrame = 1; break;
			case OBJECT_DIRECTION_DOWN: playerObject->spriteFrame = 0; break;
		}
		
		int addSpriteFrames = 0;
		
		if (overworld.player.timer < 10) {
			addSpriteFrames = 3;
		}
		else if (overworld.player.timer < 20) {
			addSpriteFrames = 0;
		}
		else if (overworld.player.timer < 30) {
			addSpriteFrames = 6;
		}
		else if (overworld.player.timer < 40) {
			addSpriteFrames = 0;
		}
		else {
			overworld.player.timer = 0;
		}
		
		playerObject->timer = overworld.player.timer;
		playerObject->spriteFrame += addSpriteFrames;
		if (playerObject->state == OBJECT_STATE_CLIMB) playerObject->spriteFrame /= 3;
		
		for (int i = 1; i < 8; i++) {
			OverworldObject* object = &overworld.objects[i];
			
			switch (overworld.caterpillar[i * 16].direction) {
				case OBJECT_DIRECTION_LEFT: object->spriteFrame = 2; break;
				case OBJECT_DIRECTION_RIGHT: object->spriteFrame = 2; break;
				case OBJECT_DIRECTION_UP: object->spriteFrame = 1; break;
				case OBJECT_DIRECTION_DOWN: object->spriteFrame = 0; break;
			}
			
			object->timer = overworld.player.timer;
			object->spriteFrame += addSpriteFrames;
			if (object->state == OBJECT_STATE_CLIMB) object->spriteFrame /= 3;
		}
	}
	
	if (overworld.player.x != overworld.player.xPrev || overworld.player.y != overworld.player.yPrev) {
		for (int j = 0; j < 2 + overworld.player.dashing; j++)
		for (int i = 127; i >= 1; i--) {
			overworld.caterpillar[i] = overworld.caterpillar[i - 1];
		}
		
		overworld.caterpillar[0].x = overworld.player.x;
		overworld.caterpillar[0].y = overworld.player.y;
		overworld.caterpillar[0].direction = overworld.player.direction;
	}
	
	if (overworld.state == OVERWORLD_STATE_IDLE) {
		Player_UpdateObject();
	}
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		OverworldObject* object = &overworld.objects[i];
		
		object->timer++;
		
		if (object->spriteFrameSpeed != 0 && object->spriteId >= 0) {
			object->spriteFrameFraction += object->spriteFrameSpeed;
			
			object->spriteFrame += (int)object->spriteFrameFraction;
			object->spriteFrameFraction -= (int)object->spriteFrameFraction;
			
			int spriteFrameMax = drawerSystem.sprites[object->spriteId].subImages;
			
			while (object->spriteFrame < 0 && spriteFrameMax >= 1) {
				object->spriteFrame += spriteFrameMax;
			}
			while (object->spriteFrame >= spriteFrameMax && spriteFrameMax >= 1) {
				object->spriteFrame -= spriteFrameMax;
			}
		}
		
		object->depth = -object->y;
		
		if (object->climbSpriteId >= 0 && (object->x != object->xPrev || object->y != object->yPrev)) {
			int k = object->x / 16;
			int j = object->y / 16;
			if (k >= 0 && k < overworld.map.w && j >= 0 && j < overworld.map.h) {
				int data = overworld.map.tileData[overworld.map.tileMap[j][k]];
				float tileX = k * 16;
				float tileY = j * 16;
				
				if (data == 10) {
					object->state = OBJECT_STATE_CLIMB;
				}
			}
		}
		
		if (object->state == OBJECT_STATE_CLIMB) {
			if (object->x != object->xPrev || object->y != object->yPrev) {
				bool climbing = false;
				int k = object->x / 16;
				int j = object->y / 16;
				if (k >= 0 && k < overworld.map.w && j >= 0 && j < overworld.map.h) {
					int data = overworld.map.tileData[overworld.map.tileMap[j][k]];
					float tileX = k * 16;
					float tileY = j * 16;
					
					if (data == 10) {
						climbing = true;
					}
					if (!climbing) {
						object->state = OBJECT_STATE_IDLE;
					}
				}
			}
			else {
				object->timer = 39;
			}
		}
		
		if (object->moveTarget.enabled) {
			if (object->moveTarget.jumpTime >= 0) {
				if (object->state != OBJECT_STATE_JUMP) {
					object->state = OBJECT_STATE_JUMP;
					object->timer = 0;
				}
				
				float distance = PointDistance(object->x, object->y, object->moveTarget.x, object->moveTarget.y);
				
				if (object->timer >= object->moveTarget.jumpTime) {
					object->state = OBJECT_STATE_IDLE;
					object->timer = 0;
					if (object->moveTarget.direction >= 0) OverworldObject_ChangeDirection(i, object->moveTarget.direction);
					object->x = object->moveTarget.x;
					object->y = object->moveTarget.y;
					if (object->moveTarget.jumpHeight != 0) {
						object->z = 0;
					}
					object->moveTarget.enabled = false;
				}
				else {
					if (object->moveTarget.speed > 0) {
						float direction = PointDirection(object->x, object->y, object->moveTarget.x, object->moveTarget.y);
						
						object->x += cos(direction) * object->moveTarget.speed;
						object->y += sin(direction) * object->moveTarget.speed;
					}
					
					if (object->moveTarget.jumpHeight != 0) {
						float zVel = 8 * (-0.5 + (float)object->timer / object->moveTarget.jumpTime) / object->moveTarget.jumpTime;
						object->z += zVel * object->moveTarget.jumpHeight;
					}
				}
			}
			else {
				if (object->x > object->moveTarget.x) {
					OverworldObject_TryMove(i, -object->moveTarget.speed, 0);
					if (object->walkAnimationEnabled) OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_LEFT);
					if (object->x <= object->moveTarget.x) {
						object->x = object->moveTarget.x;
					}
				}
				if (object->x < object->moveTarget.x) {
					OverworldObject_TryMove(i, object->moveTarget.speed, 0);
					if (object->walkAnimationEnabled) OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_RIGHT);
					if (object->x >= object->moveTarget.x) {
						object->x = object->moveTarget.x;
					}
				}
				if (object->y > object->moveTarget.y) {
					OverworldObject_TryMove(i, 0, -object->moveTarget.speed);
					if (object->walkAnimationEnabled) OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_UP);
					if (object->y <= object->moveTarget.y) {
						object->y = object->moveTarget.y;
					}
				}
				if (object->y < object->moveTarget.y) {
					OverworldObject_TryMove(i, 0, object->moveTarget.speed);
					if (object->walkAnimationEnabled) OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_DOWN);
					if (object->y >= object->moveTarget.y) {
						object->y = object->moveTarget.y;
					}
				}
				
				if ((object->x == object->moveTarget.x && object->y == object->moveTarget.y) || (object->x == object->xPrev && object->y == object->yPrev)) {
					object->moveTarget.enabled = false;
					object->state = OBJECT_STATE_IDLE;
					object->timer = 0;
					if (object->moveTarget.direction >= 0) OverworldObject_ChangeDirection(i, object->moveTarget.direction);
					else OverworldObject_ChangeDirection(i, object->direction);
					for (int j = 0; j < MOVETARGET_QUEUE_MAX; j++) {
						if (object->moveTargetQueue[j].enabled) {
							object->moveTarget = object->moveTargetQueue[j];
							object->moveTargetQueue[j].enabled = false;
							break;
						}
					}
				}
				else if (object->state == OBJECT_STATE_IDLE) {
					object->state = OBJECT_STATE_WALK;
					object->timer = 0;
				}
			}
		}
		
		if ((object->state == OBJECT_STATE_WALK || object->state == OBJECT_STATE_CLIMB) && object->spriteType == 1 && object->walkAnimationEnabled) {
			switch (object->direction) {
				case OBJECT_DIRECTION_LEFT: object->spriteFrame = 2; break;
				case OBJECT_DIRECTION_RIGHT: object->spriteFrame = 2; break;
				case OBJECT_DIRECTION_UP: object->spriteFrame = 1; break;
				case OBJECT_DIRECTION_DOWN: object->spriteFrame = 0; break;
			}
			
			int addSpriteFrames = 0;
			
			if (object->timer < 10) {
				addSpriteFrames = 3;
			}
			else if (object->timer < 20) {
				addSpriteFrames = 0;
			}
			else if (object->timer < 30) {
				addSpriteFrames = 6;
			}
			else if (object->timer < 40) {
				addSpriteFrames = 0;
			}
			else {
				object->timer = 0;
			}
			
			object->spriteFrame += addSpriteFrames;
			if (object->state == OBJECT_STATE_CLIMB) object->spriteFrame /= 3;
		}
		
		switch (object->type) {
			case 2:
				if (overworld.state != OVERWORLD_STATE_IDLE || overworld.transition.id > 0) break;
				
				if (object->vars[0].i == 1 && object->timer >= 30 && Random(1) < 0.05) {
					if (Random(1) < 0.5)
						OverworldObject_WalkTo(i, object->vars[2].f + Random_IRange(-48, 48), object->vars[3].f + Random_IRange(-48, 48), 1, Random_IRange(-1, 3));
					else
						OverworldObject_ChangeDirection(i, Random_IRange(0, 3));
					object->timer = 0;
				}
				
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) && eventSystem.queueSize == 0) {
					float interactX = overworld.player.x + (overworld.player.direction == OBJECT_DIRECTION_RIGHT) * 8 - (overworld.player.direction == OBJECT_DIRECTION_LEFT) * 8;
					float interactY = overworld.player.y + (overworld.player.direction == OBJECT_DIRECTION_DOWN) * 8 - (overworld.player.direction == OBJECT_DIRECTION_UP) * 8;
					float interactW = 16 - object->vars[1].i * 12;
					float interactH = 16 - object->vars[1].i * 4;
					if (interactX + interactW > object->x - object->w / 2 && interactX - interactW < object->x + object->w / 2 && interactY + interactH > object->y - object->h && interactY - interactH - 8 < object->y) {
						if (object->spriteType == 1) {
							switch (overworld.player.direction) {
								case OBJECT_DIRECTION_LEFT:
									OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_RIGHT);
									break;
								case OBJECT_DIRECTION_RIGHT:
									OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_LEFT);
									break;
								case OBJECT_DIRECTION_UP:
									OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_DOWN);
									break;
								case OBJECT_DIRECTION_DOWN:
									OverworldObject_ChangeDirection(i, OBJECT_DIRECTION_UP);
									break;
							}
						}
						object->moveTarget.enabled = false;
						object->state = OBJECT_STATE_IDLE;
						object->timer = 0;
						overworld.player.dashing = false;
						overworld.player.dashChargeTimer = 0;
						Party_UpdateCaterpillar();
						eventSystem.callerObjectId = i;
						Event_Trigger(1000000 + object->id);
					}
				}
				break;
			case 3:
				if (overworld.state != OVERWORLD_STATE_IDLE) break;
				if (overworld.transition.id > 0 && object->vars[0].i != ENEMY_STATE_FIGHT) {
					OverworldObject_WalkTo(i, object->x, object->y, 1, -1);
					break;
				}
				
				if (object->x < overworld.camera.x - 500 || object->x > overworld.camera.x + 500 || object->y < overworld.camera.y - 500 || object->y > overworld.camera.y + 500) break;
				
				switch (object->vars[0].i) {
					case ENEMY_STATE_IDLE: {
						if (object->timer >= 30 && Random(1) < 0.05) {
							if (Random(1) < 0.5)
								OverworldObject_WalkTo(i, object->vars[2].f + Random_IRange(-48, 48), object->vars[3].f + Random_IRange(-48, 48), 1, Random_IRange(-1, 3));
							else
								OverworldObject_ChangeDirection(i, Random_IRange(0, 3));
							object->timer = 0;
						}
						
						if (PointDistance(object->x, object->y, overworld.player.x, overworld.player.y) < 88) {
							object->vars[0].i = ENEMY_STATE_CHASE;
							object->timer = 0;
						}
					} break;
					
					case ENEMY_STATE_CHASE: {
						OverworldObject_WalkTo(i, overworld.player.x, overworld.player.y, 2, -1);
						
						if (PointDistance(object->x, object->y, overworld.player.x, overworld.player.y) > 104
						|| overworld.player.x >= object->vars[2].f + 144 || overworld.player.x <= object->vars[2].f - 144 || overworld.player.y >= object->vars[3].f + 144 || overworld.player.y <= object->vars[3].f - 144) {
							object->vars[0].i = ENEMY_STATE_IDLE;
							object->timer = 0;
							OverworldObject_WalkTo(i, object->x, object->y, 1, -1);
						}
					} break;
					
					case ENEMY_STATE_FIGHT: {
						if (overworld.transition.id == 2 && overworld.transition.timer >= 40) {
							OverworldObject_Destroy(i);
						}
					} break;
					
					case ENEMY_STATE_KNOCKED: {
						if (!object->moveTarget.enabled) {
							object->vars[0].i = ENEMY_STATE_IDLE;
							object->timer = 0;
						}
					} break;
				}
				
				if (object->vars[0].i != ENEMY_STATE_FIGHT && object->vars[0].i != ENEMY_STATE_KNOCKED && object->x + 8 >= overworld.player.x - 8 && object->x - 8 <= overworld.player.x + 8 && object->y >= overworld.player.y - 16 && object->y - 16 <= overworld.player.y) {
					bool knockAway = false;
					if (overworld.player.dashing && (overworld.player.x != overworld.player.xPrev || overworld.player.y != overworld.player.yPrev)) {
						PartyMember* partyMember = &partyMembers[profile.partyOrder[0]];
						FighterData* enemy = &fighterData[battleEncounterData[object->id].fighterIds[0]];
						
						int playerStatSum = partyMember->hpMax + partyMember->mpMax + (partyMember->attack + partyMember->defense + partyMember->speed) * 4;
						int enemyStatSum = enemy->hpMax + enemy->mpMax + (enemy->attack + enemy->defense + enemy->speed) * 4;
						
						if (playerStatSum >= enemyStatSum * 2) {
							knockAway = true;
						}
					}
					
					if (knockAway) {
						object->vars[4].i++;
						Audio_PlaySound(SND_hit3);
						object->vars[0].i = ENEMY_STATE_KNOCKED;
						object->timer = 0;
						OverworldObject_JumpTo(i, object->x, object->y, -1, 40, 24);
						Overworld_CreateSpark(1, object->x, object->y - 16, 1);
						OverworldObject_ChangeDirection(i, object->direction);
					}
					else {
						object->vars[0].i = ENEMY_STATE_FIGHT;
						OverworldObject_WalkTo(i, object->x, object->y, 1, -1);
						EngageBattle(object->id, i);
						if (object->id != 50) battle.canFlee = true;
						battle.encounterVars[0].i = object->vars[1].i;
						overworld.player.dashing = false;
						Party_UpdateCaterpillar();
					}
				}
				break;
			
			case 100:
				if (overworld.state != OVERWORLD_STATE_IDLE) break;
				
				if (object->timer <= 1) {
					if (object->timer < 28 && overworld.player.x + 4 >= object->x - 16 && overworld.player.x - 4 <= object->x + 32 && overworld.player.y >= object->y - 16 && overworld.player.y - 8 <= object->y + 32) {
						Audio_PlaySoundInterrupt(SND_swing);
						object->timer = 1;
					}
					else {
						object->timer = 0;
					}
				}
				if (object->timer >= 8 && object->timer < 28 && overworld.player.x + 4 >= object->x && overworld.player.x - 4 <= object->x + 16 && overworld.player.y >= object->y && overworld.player.y - 8 <= object->y + 16) {
					Player_TakeDamage(8);
				}
				if (object->timer >= 100) {
					object->timer = 0;
				}
				
				switch (object->timer) {
					case 1: case 32: object->spriteId = SPR_misc_spikes; object->spriteFrame = 0; break;
					case 8: object->spriteFrame = 1; break;
					case 40: object->spriteId = -1; break;
				}
				break;
			case 101:
				if (object->timer >= 900 && overworld.state == OVERWORLD_STATE_IDLE) {
					overworld.player.dashing = false;
					overworld.player.dashChargeTimer = 0;
					Party_UpdateCaterpillar();
					eventSystem.callerObjectId = i;
					Event_Trigger(64);
					OverworldObject_Destroy(i);
				}
				break;
			case 102:
				if (overworld.state != OVERWORLD_STATE_IDLE || overworld.transition.id > 0 || !object->vars[0].i) break;
				
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) && eventSystem.queueSize == 0) {
					float interactX = overworld.player.x + (overworld.player.direction == OBJECT_DIRECTION_RIGHT) * 8 - (overworld.player.direction == OBJECT_DIRECTION_LEFT) * 8;
					float interactY = overworld.player.y + (overworld.player.direction == OBJECT_DIRECTION_DOWN) * 8 - (overworld.player.direction == OBJECT_DIRECTION_UP) * 8;
					float interactW = 16 - object->vars[1].i * 12;
					float interactH = 16 - object->vars[1].i * 4;
					if (interactX + interactW > object->x - object->w / 2 && interactX - interactW < object->x + object->w / 2 && interactY + interactH > object->y - object->h && interactY - interactH - 8 < object->y) {
						object->moveTarget.enabled = false;
						object->state = OBJECT_STATE_IDLE;
						object->timer = 0;
						overworld.player.dashing = false;
						overworld.player.dashChargeTimer = 0;
						Party_UpdateCaterpillar();
						
						object->vars[1].i = !object->vars[1].i;
						Audio_PlaySoundInterrupt(SND_swing);
						Audio_PlaySoundInterrupt(SND_slap);
						if (object->vars[1].i == 1)
							OverworldObject_WalkTo(i, 29384, 10608, 8, -1);
						else
							OverworldObject_WalkTo(i, 28296, 10608, 8, -1);
						
					}
				}
				break;
			case 103:
				if (object->vars[0].i == 1) {
					if (!overworld.objects[70].moveTarget.enabled) {
						overworld.objects[10].vars[0].i = 0;
						overworld.objects[10].vars[1].i = 0;
						OverworldObject_ToggleGhost(10, false);
						
						for (int j = 0; j < MOVETARGET_QUEUE_MAX; j++) overworld.objects[70].moveTargetQueue[j].enabled = false;
						overworld.player.dashing = false;
						overworld.player.dashChargeTimer = 0;
						Party_UpdateCaterpillar();
						eventSystem.callerObjectId = i;
						Event_Trigger(74);
						OverworldObject_Destroy(i);
					}
					break;
				}
				
				object->x = overworld.camera.x;
				object->y = overworld.camera.y + 120;
				
				if (object->timer == 31) {
					overworld.objects[10].vars[0].i = 1;
					OverworldObject_ToggleGhost(10, true);
					
					OverworldObject_WalkTo(70, 29384, 10336, 1.5, -1);
					OverworldObject_QueueWalkTo(70, 29384, 10544, 1.5, -1);
				}
				if (object->timer == 720) {
					OverworldObject_WalkTo(70, 29384, 10336, 3, -1);
					OverworldObject_QueueWalkTo(70, 28296, 10336, 3, -1);
					OverworldObject_QueueWalkTo(70, 28296, 10544, 3, -1);
				}
				if (object->timer == 1300) {
					OverworldObject_WalkTo(70, 28296, 10336, 3, -1);
				}
				if (object->timer == 1450) {
					OverworldObject_WalkTo(70, 28296, 10544, 4, -1);
				}
				if (object->timer == 1620) {
					OverworldObject_WalkTo(70, 28296, 10336, 1.5, -1);
					OverworldObject_QueueWalkTo(70, 29384, 10336, 5, -1);
					OverworldObject_QueueWalkTo(70, 29384, 10544, 5, -1);
					OverworldObject_QueueWalkTo(70, 29384, 10458, 4, -1);
					OverworldObject_QueueWalkTo(70, 29416, 10376, 4, -1);
					OverworldObject_QueueWalkTo(70, 29368, 10328, 4, -1);
					OverworldObject_QueueWalkTo(70, 29344, 10360, 4, -1);
					OverworldObject_QueueWalkTo(70, 29352, 10488, 4, -1);
					OverworldObject_QueueWalkTo(70, 29384, 10544, 5, -1);
					
				}
				if (object->timer == 2220) {
					OverworldObject_QueueWalkTo(70, 29416, 10392, 5, -1);
					OverworldObject_QueueWalkTo(70, 28296, 10336, 5, -1);
					OverworldObject_QueueWalkTo(70, 28296, 10544, 5, -1);
					
					OverworldObject_QueueWalkTo(70, 28296, 10376, 5, -1);
					OverworldObject_QueueWalkTo(70, 28848, 10336, 5, -1);
				}
				if (object->timer == 2520) {
					OverworldObject_QueueWalkTo(70, 28782, 10336, 10, -1);
					OverworldObject_QueueWalkTo(70, 28842, 10336, 10, -1);
					OverworldObject_QueueWalkTo(70, 28812, 10336, 10, -1);
					OverworldObject_QueueWalkTo(70, 28862, 10336, 10, -1);
					OverworldObject_QueueWalkTo(70, 28622, 10336, 10, -1);
					OverworldObject_QueueWalkTo(70, 28822, 10336, 10, -1);
					OverworldObject_QueueWalkTo(70, 29322, 10336, 8, -1);
					OverworldObject_QueueWalkTo(70, 29384, 10544, 6, -1);
					
					OverworldObject_QueueWalkTo(70, 29384, 10392, 6, -1);
					OverworldObject_QueueWalkTo(70, 28376, 10336, 6, -1);
					OverworldObject_QueueWalkTo(70, 28344, 10368, 6, -1);
					OverworldObject_QueueWalkTo(70, 28296, 10544, 3, -1);
				}
				if (object->timer == 3200) {
					OverworldObject_QueueWalkTo(70, 28296, 10336, 3, -1);
				}
				
				if (overworld.objects[70].y >= 10544) {
					if (overworld.objects[70].x < 28832 && overworld.objects[10].x > 28368) {
						OverworldObject_JumpTo(70, 28296, 10632, OBJECT_DIRECTION_DOWN, 16, 12);
						object->vars[0].i = 1;
					}
					else if (overworld.objects[70].x > 28832 && overworld.objects[10].x < 29312) {
						OverworldObject_JumpTo(70, 29384, 10632, OBJECT_DIRECTION_DOWN, 16, 12);
						object->vars[0].i = 1;
					}
				}
				
				if (object->timer >= 3252 && overworld.state == OVERWORLD_STATE_IDLE) {
					overworld.objects[10].vars[0].i = 0;
					overworld.objects[10].vars[1].i = 0;
					OverworldObject_ToggleGhost(10, false);
					
					overworld.player.dashing = false;
					overworld.player.dashChargeTimer = 0;
					Party_UpdateCaterpillar();
					eventSystem.callerObjectId = i;
					Event_Trigger(73);
					OverworldObject_Destroy(i);
				}
				break;
			case 104:
				if (object->timer % 14 == 6) {
					for (int j = 20; j < 60; j++) {
						if (overworld.objects[j].type == 0) continue;
						
						overworld.objects[j].spriteFrame++;
					}
				}
				else if (object->timer % 14 == 13) {
					for (int j = 20; j < 60; j++) {
						if (overworld.objects[j].type == 0) continue;
						
						overworld.objects[j].spriteFrame--;
					}
				}
				
				if (object->vars[0].i == 1) {
					for (int j = 20; j < 60; j++) {
						OverworldObject_Destroy(j);
					}
					object->vars[0].i = 0;
				}
				
				if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DEFEATED] == 0) {
					if (object->timer >= 10585 && object->timer % 14 < 6 && overworld.state != OVERWORLD_STATE_IDLE) {
						object->timer = 10584;
					}
					if (object->timer >= 10800 && overworld.state == OVERWORLD_STATE_IDLE) {
						overworld.player.dashing = false;
						overworld.player.dashChargeTimer = 0;
						Party_UpdateCaterpillar();
						eventSystem.callerObjectId = i;
						Event_Trigger(77);
					}
				}
				break;
			case 105:
				if (PlayerButtonHeld(PLAYER_BUTTON_LEFT)) {
					object->vars[0].f -= 4;
					if (object->vars[0].f < -134) object->vars[0].f = -134;
				}
				if (PlayerButtonHeld(PLAYER_BUTTON_RIGHT)) {
					object->vars[0].f += 4;
					if (object->vars[0].f > 134) object->vars[0].f = 134;
				}
				if (PlayerButtonHeld(PLAYER_BUTTON_UP)) {
					object->vars[1].f -= 4;
					if (object->vars[1].f < -94) object->vars[1].f = -94;
				}
				if (PlayerButtonHeld(PLAYER_BUTTON_DOWN)) {
					object->vars[1].f += 4;
					if (object->vars[1].f > 94) object->vars[1].f = 94;
				}
				
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) || PlayerButtonPressed(PLAYER_BUTTON_X)) {
					OverworldObject_Destroy(i);
				}
				break;
			case 106:
				if (object->timer < 10) break;
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) || PlayerButtonPressed(PLAYER_BUTTON_X)) {
					OverworldObject_Destroy(i);
				}
				break;
		}
		
		object->xPrev = object->x;
		object->yPrev = object->y;
	}
	
	overworld.player.xPrev = overworld.player.x;
	overworld.player.yPrev = overworld.player.y;
	
	if (game.timer % 20 == 0) {
		for (int j = overworld.map.areas[overworld.areaId].y1; j <= overworld.map.areas[overworld.areaId].y2; j++)
		for (int i = overworld.map.areas[overworld.areaId].x1; i <= overworld.map.areas[overworld.areaId].x2; i++) {
			int data = overworld.map.tileData[overworld.map.tileMap[j][i]];
			
			if (data < 20) continue;
			
			if (data >= 61 && data <= 79) {
				overworld.map.tileMap[j][i] += data - 60;
			}
			else if (data >= 81 && data <= 99) {
				overworld.map.tileMap[j][i] -= data - 80;
			}
			else if (data >= 21 && data <= 39) {
				overworld.map.tileMap[j][i] += data - 20;
			}
			else if (data >= 41 && data <= 59) {
				overworld.map.tileMap[j][i] -= data - 40;
			}
		}
	}
	
	switch (overworld.transition.id) {
		case 1:
			overworld.transition.timer++;
			if (overworld.transition.timer < 24) {
				if (overworld.fadeAlpha < 1) {
					overworld.fadeAlpha = fmin(1, (float)overworld.transition.timer / 16);
					overworld.fadeColor[0] = 0;
					overworld.fadeColor[1] = 0;
					overworld.fadeColor[2] = 0;
				}
			}
			else if (overworld.transition.timer == 24) {
				if ((int)overworld.transition.vars[3] >= 0) overworld.map.tilesetSpriteId = (int)overworld.transition.vars[3];
				Player_TeleportTo(overworld.transition.vars[1], overworld.transition.vars[2]);
				Overworld_ChangeArea((int)overworld.transition.vars[0]);
				Player_UpdateObject();
			}
			else if (overworld.transition.timer < 41) {
				overworld.fadeAlpha = fmin(1, (float)(41 - overworld.transition.timer) / 16);
			}
			else {
				overworld.fadeAlpha = 0;
				overworld.transition.id = 0;
				if (overworld.state == OVERWORLD_STATE_TRANSITION) {
					overworld.state = OVERWORLD_STATE_IDLE;
					Player_TryMove(0, 0);
				}
			}
			break;
		case 2:
			overworld.transition.timer++;
			if (overworld.transition.timer < 40) {
				
			}
			else if (overworld.transition.timer == 40) {
				ChangeScene(SCENE_BATTLE);
				overworld.fadeAlpha = 1;
				overworld.fadeColor[0] = 0;
				overworld.fadeColor[1] = 0;
				overworld.fadeColor[2] = 0;
			}
			else if (overworld.transition.timer < 56) {
				overworld.fadeAlpha = fmin(1, (float)(56 - overworld.transition.timer) / 16);
			}
			else {
				overworld.fadeAlpha = 0;
				overworld.transition.id = 0;
			}
			break;
		case 3:
			overworld.transition.timer++;
			if (overworld.transition.timer == 60) {
				Player_TeleportTo(overworld.transition.vars[1], overworld.transition.vars[2]);
				Overworld_ChangeArea((int)overworld.transition.vars[0]);
				Player_UpdateObject();
				if ((int)overworld.transition.vars[3] >= 0) overworld.map.tilesetSpriteId = (int)overworld.transition.vars[3];
			}
			else if (overworld.transition.timer > 120) {
				overworld.transition.id = 0;
				if (overworld.state == OVERWORLD_STATE_TRANSITION) {
					overworld.state = OVERWORLD_STATE_IDLE;
					Player_TryMove(0, 0);
				}
			}
			break;
		case 4:
			overworld.transition.timer++;
			if (overworld.transition.timer < overworld.transition.vars[0]) {
				overworld.fadeAlpha = fmin(1, (float)overworld.transition.timer / overworld.transition.vars[0]);
			}
			else {
				overworld.fadeAlpha = 1;
				overworld.transition.id = 0;
			}
			break;
		case 5:
			overworld.transition.timer++;
			if (overworld.transition.timer < overworld.transition.vars[0]) {
				overworld.fadeAlpha = fmax(0, 1 - (float)overworld.transition.timer / overworld.transition.vars[0]);
			}
			else {
				overworld.fadeAlpha = 0;
				overworld.transition.id = 0;
			}
			break;
	}
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (overworld.sparks[i].id <= 0) continue;
		
		overworld.sparks[i].timer++;
		overworld.sparks[i].x += overworld.sparks[i].xVel;
		overworld.sparks[i].y += overworld.sparks[i].yVel;
		
		switch (overworld.sparks[i].id) {
			case 1:
				if (overworld.sparks[i].timer >= 20) {
					overworld.sparks[i].id = 0;
				}
				break;
			case 2:
				if (overworld.sparks[i].timer >= 16) {
					overworld.sparks[i].id = 0;
				}
				break;
			case 3:
				if (overworld.sparks[i].timer >= 24) {
					overworld.sparks[i].id = 0;
				}
				break;
			case 4:
				if (overworld.sparks[i].timer >= 16) {
					overworld.sparks[i].id = 0;
				}
				break;
		}
	}
	
	if (overworld.state == OVERWORLD_STATE_PAUSED) {
		Overworld_UpdateMenu();
	}
	
	if (overworld.cameraClamping) {
		overworld.camera.x = Max(overworld.map.areas[overworld.areaId].x1 * 16 + 160, Min(overworld.map.areas[overworld.areaId].x2 * 16 - 144, overworld.camera.x));
		overworld.camera.y = Max(overworld.map.areas[overworld.areaId].y1 * 16 + 120, Min(overworld.map.areas[overworld.areaId].y2 * 16 - 104, overworld.camera.y));
	}
}

void Overworld_Draw() {
	Drawer_SetProjection(320, 240, 1);
	
	Drawer_SetDrawColor(0, 0, 0);
	Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Drawer_SetDrawColor(255, 255, 255);
	
	
	switch (overworld.backgroundId) {
		case 1:
			Drawer_DrawSprite(SPR_misc_backdrop_brilliant, overworld.map.areas[overworld.areaId].x1 * 16 + 160 - overworld.camera.x, 0, 0, 2, 2);
			break;
		case 2:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			{
				Drawer_SetDrawAlpha(159);
				Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
				float x, y, scale;
				x = ((game.timer * 3 / 4) % 128);
				y = ((game.timer * 3 / 4) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				x = ((game.timer * 4 / 3) % 128);
				y = ((game.timer * 4 / 3) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				Drawer_SetDrawAlpha(255);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			break;
	}
	
	
	
	Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
	
	if (overworld.shakeTimer == 0)
		Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
	else
		Drawer_SetProjection(overworld.camera.x + Random_Range(-overworld.shakeTimer, overworld.shakeTimer), overworld.camera.y + Random_Range(-overworld.shakeTimer, overworld.shakeTimer), overworld.camera.zoom);
	
	Overworld_DrawMap();
	
	int objectCount = 0;
	int objectOrder[OBJECT_COUNT_MAX];
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (overworld.objects[i].type == 0) continue;
		OverworldObject* object = &overworld.objects[i];
		if (!overworld.areaWrap && (object->x < overworld.camera.x - SCREEN_WIDTH / 4 - 196 || object->x > overworld.camera.x + SCREEN_WIDTH / 4 + 196 || object->y < overworld.camera.y - SCREEN_HEIGHT / 4 - 196 || object->y > overworld.camera.y + SCREEN_HEIGHT / 4 + 196)) continue;
		objectOrder[objectCount++] = i;
	}
	
	for (int i = 0; i < overworld.map.decorationCount; i++) {
		if (objectCount >= OBJECT_COUNT_MAX) break;
		OverworldObject* object = &overworld.map.decorations[i];
		if (object->x < overworld.camera.x - SCREEN_WIDTH / 4 - 196 || object->x > overworld.camera.x + SCREEN_WIDTH / 4 + 196 || object->y < overworld.camera.y - SCREEN_HEIGHT / 4 - 196 || object->y > overworld.camera.y + SCREEN_HEIGHT / 4 + 196) continue;
		objectOrder[objectCount++] = 10000 + i;
	}
	
	for (int i = 0; i < objectCount; i++) {
		for (int j = 0; j < objectCount - 1; j++) {
			OverworldObject* object1;
			OverworldObject* object2;
			
			if (objectOrder[j] >= 10000)
				object1 = &overworld.map.decorations[objectOrder[j] - 10000];
			else
				object1 = &overworld.objects[objectOrder[j]];
			
			if (objectOrder[j+1] >= 10000)
				object2 = &overworld.map.decorations[objectOrder[j+1] - 10000];
			else
				object2 = &overworld.objects[objectOrder[j+1]];
			
			if (object1->depth < object2->depth) {
				int temp = objectOrder[j];
				objectOrder[j] = objectOrder[j+1];
				objectOrder[j+1] = temp;
			}
		}
	}
	
	for (int i = 0; i < objectCount; i++) {
		OverworldObject* object;
		
		if (objectOrder[i] >= 10000)
			object = &overworld.map.decorations[objectOrder[i] - 10000];
		else
			object = &overworld.objects[objectOrder[i]];
		
		Drawer_SetDrawColor(object->color[0], object->color[1], object->color[2]);
		
		if (object->type == 106) {
			Drawer_DrawSprite(object->id, overworld.camera.x + object->vars[0].f, overworld.camera.y + object->vars[1].f, object->vars[2].i, 1, 1);
		}
		else if (object->type == 105) {
			Drawer_DrawSprite(SPR_misc_backdrop_lisaohouse, overworld.camera.x - 160 - object->vars[0].f, overworld.camera.y - 120 - object->vars[1].f, profile.flags[FLAG_PLOT] >= 14 && !profile.flags[FLAG_GREGORY_OPTIONALFIGHT], 1, 1);
			Drawer_DrawSprite(SPR_misc_darkoverlay, overworld.camera.x, overworld.camera.y, 0, 1, 1);
		}
		else if (object->type == 103) {
			Drawer_DrawSprite(SPR_misc_retichase_minimap, overworld.camera.x - 160, overworld.camera.y - 120, 0, 1, 1);
			Drawer_SetDrawColor(0, 0, 0);
			Drawer_FillRect(overworld.camera.x - 156 + (int)(overworld.objects[10].x - 28256) / 16 - 5, overworld.camera.y - 117 + (int)(overworld.objects[10].y - 10304) / 16, 10, 2);
			Drawer_SetDrawColor(255, 255, 0);
			Drawer_DrawSprite(SPR_misc_retichase_dot, overworld.camera.x - 156 + (int)(overworld.objects[0].x - 28256) / 16, overworld.camera.y - 117 + (int)(overworld.objects[0].y - 10304) / 16, 0, 1, 1);
			Drawer_SetDrawColor(255, 0, 0);
			Drawer_DrawSprite(SPR_misc_retichase_dot, overworld.camera.x - 156 + (int)(overworld.objects[70].x - 28256) / 16, overworld.camera.y - 117 + (int)(overworld.objects[70].y - 10304) / 16, 0, 1, 1);
		}
		else if (object->type == 4) {
			for (int k = 0; k < object->vars[1].i; k++)
			for (int j = 0; j < object->vars[0].i; j++) {
				Drawer_DrawSprite(overworld.map.tilesetSpriteId, object->x - 8 - (object->vars[1].i - 1) * 8 + k * 16, object->y - 16 * (1 + j), object->id - 64 * j + k, 1, 1);
			}
		}
		else if (object->bodyId >= 0) {
			DrawFighterChar(object->headId, object->bodyId, object->fighterState, object->x, object->y + object->z, 1, 1, 1 - (object->direction == OBJECT_DIRECTION_LEFT) * 2);
		}
		else if (object->spriteId >= 0) {
			if (object->state == OBJECT_STATE_CLIMB && object->climbSpriteId >= 0)
				Drawer_DrawSprite(object->climbSpriteId, object->x, object->y + object->z, object->spriteFrame, 1, 1);
			else if (object->direction == OBJECT_DIRECTION_LEFT)
				Drawer_DrawSprite(object->spriteId, object->x, object->y + object->z, object->spriteFrame, -1, 1);
			else
				Drawer_DrawSprite(object->spriteId, object->x, object->y + object->z, object->spriteFrame, 1, 1);
			
			if (overworld.areaWrap) {
				int x1 = overworld.map.areas[overworld.areaId].x1;
				int y1 = overworld.map.areas[overworld.areaId].y1;
				int x2 = overworld.map.areas[overworld.areaId].x2;
				int y2 = overworld.map.areas[overworld.areaId].y2;
				int w = x2 - x1 + 1;
				int h = y2 - y1 + 1;
				
				for (int jj = -1; jj <= 1; jj++)
				for (int ii = -1; ii <= 1; ii++) {
					if (ii == 0 && jj == 0) continue;
					if (object->direction == OBJECT_DIRECTION_LEFT)
						Drawer_DrawSprite(object->spriteId, object->x + ii * w * 16, object->y + object->z + jj * h * 16, object->spriteFrame, -1, 1);
					else
						Drawer_DrawSprite(object->spriteId, object->x + ii * w * 16, object->y + object->z + jj * h * 16, object->spriteFrame, 1, 1);
				}
			}
		}
	}
	Drawer_SetDrawColor(255, 255, 255);
	
	float overlayAngle = 0;
	switch (overworld.player.direction) {
		case OBJECT_DIRECTION_LEFT: overlayAngle = 0; break;
		case OBJECT_DIRECTION_RIGHT: overlayAngle = 180; break;
		case OBJECT_DIRECTION_UP: overlayAngle = 90; break;
		case OBJECT_DIRECTION_DOWN: overlayAngle = 270; break;
	}
	switch (overworld.overlayId) {
		case 1:
			Drawer_DrawSprite_Angle(SPR_misc_darkoverlay, overworld.objects[0].x, overworld.objects[0].y - 12, 0, 1, 1, overlayAngle);
			break;
		case 2:
			Drawer_DrawSprite_Angle(SPR_misc_darkoverlay_flashlight, overworld.objects[0].x, overworld.objects[0].y - 12, 0, 1, 1, overlayAngle);
			break;
		case 3:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			if (game.timer % 240 >= 180 && game.timer % 6 < 3)
				Drawer_SetDrawColor(255, 255, 255);
			else if (game.timer % 60 < 30)
				Drawer_SetDrawColor(207, 0, 0);
			else
				Drawer_SetDrawColor(0, 103, 207);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 4:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			if (game.timer % 90 < 30)
				Drawer_SetDrawColor(255, 63, 0);
			else if (game.timer % 90 < 60)
				Drawer_SetDrawColor(31, 191, 0);
			else
				Drawer_SetDrawColor(0, 191, 255);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 5:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 255, 255);
			{
				Drawer_SetDrawAlpha(127);
				Drawer_SetDrawColor(255, 255, 255);
				float x, y, scale;
				/*x = (game.timer % 128);
				y = (game.timer % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}*/
				Drawer_SetDrawColor(255, 0, 63);
				x = ((game.timer * 3 / 4) % 128);
				y = ((game.timer * 3 / 4) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				Drawer_SetDrawColor(255, 0, 0);
				x = ((game.timer * 4 / 3) % 128);
				y = ((game.timer * 4 / 3) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				Drawer_SetDrawAlpha(255);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 6:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 0, 0);
			{
				Drawer_SetDrawAlpha(223);
				Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
				Drawer_SetDrawAlpha(159);
				float x, y, scale;
				x = ((game.timer * 3 / 4) % 128);
				y = ((game.timer * 3 / 4) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				x = ((game.timer * 4 / 3) % 128);
				y = ((game.timer * 4 / 3) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				Drawer_SetDrawAlpha(255);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 7:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 255, 255);
			{
				Drawer_SetDrawAlpha(191);
				float x, y, scale;
				Drawer_SetDrawColor(0, 0, 159);
				x = 0;
				y = 0;
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				Drawer_SetDrawColor(63, 0, 31);
				x = 52;
				y = 52;
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				Drawer_SetDrawAlpha(255);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 8:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 127, 255);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 9:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(127, 0, 95);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 10:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(160, 160, 160);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 11:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor((uint8_t)((profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] & 0xff0000) >> 16), (uint8_t)((profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] & 0xff00) >> 8), (uint8_t)(profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] & 0xff));
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 12:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 0, 0);
			{
				Drawer_SetDrawAlpha(223);
				Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
				Drawer_SetDrawAlpha(159);
				float x, y, scale;
				x = ((game.timer * 6) % 128);
				y = ((game.timer * 6) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				x = ((game.timer * 12) % 128);
				y = ((game.timer * 12) % 128);
				scale = 2;
				for (int j = -2; j < 7; j++)
				for (int i = -2; i < 7; i++) {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_1, x + 64*i*scale, y + 64*j*scale, 0, scale, scale);
				}
				
				Drawer_SetDrawAlpha(127);
				Drawer_SetDrawBlend(BLENDMODE_ADD);
				for (int j = 0; j < 10; j++) {
					float t = (float)(game.timer + j) * 0.9;
					for (int i = 0; i < 5; i++) {
						Drawer_DrawSprite(SPR_misc_bossbattlebg_1, 160*i + sin(t) * 16 - 32, 64*j, 0, 1, 1);
						Drawer_DrawSprite(SPR_misc_bossbattlebg_1, 160*i + sin(t * 0.9 + i * 0.25) * 15 + 64, (64 + sin(t / 13) * 2)*j, 0, 1, 1);
					}
				}
				Drawer_SetDrawAlpha(95);
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
				for (int j = 0; j < 10; j++) {
					float t = (float)(game.timer + j) * 0.7;
					for (int i = 0; i < 5; i++) {
						Drawer_DrawSprite(SPR_misc_bossbattlebg_1, 160*i + sin(t) * 14 - 32, 64*j, 0, 1, 1);
						Drawer_DrawSprite(SPR_misc_bossbattlebg_1, 160*i + sin(t * 0.9 + i * 0.25) * 13 + 64, (64 + sin(t / 13) * 2)*j, 0, 1, 1);
					}
				}
				Drawer_SetDrawAlpha(255);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 13:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 63, 255);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
		case 14:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			if (game.timer % 60 < 20)
				Drawer_SetDrawColor(255, 0, 0);
			else if (game.timer % 60 < 40)
				Drawer_SetDrawColor(0, 255, 0);
			else
				Drawer_SetDrawColor(0, 103, 255);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			
			if (game.timer % 27 == 20)
				Overworld_ShakeScreen(18);
			break;
		case 15:
			Drawer_SetProjection(320, 240, 1);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(profile.tempFlags[TEMPFLAG_POSTFINALDIALOG_BRIGHTNESS], 255, 255);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
			break;
	}
	
	if (overworld.shakeTimer == 0)
		Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
	else
		Drawer_SetProjection(overworld.camera.x + Random_Range(-overworld.shakeTimer, overworld.shakeTimer), overworld.camera.y + Random_Range(-overworld.shakeTimer, overworld.shakeTimer), overworld.camera.zoom);
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (overworld.sparks[i].id <= 0) continue;
		
		float x = overworld.sparks[i].x;
		float y = overworld.sparks[i].y;
		
		switch (overworld.sparks[i].id) {
			case 1:
				Drawer_SetDrawColor(255, 191, 0);
				Drawer_DrawSprite(SPR_spark_star, x, y, overworld.sparks[i].timer / 5, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 2:
				Drawer_SetDrawColor(255, 0, 0);
				Drawer_DrawSprite(SPR_spark_boost, x, y, overworld.sparks[i].timer / 4, 1, 1);
				Drawer_DrawSprite(SPR_spark_ring, x, y - 12, overworld.sparks[i].timer / 4, 1, 1);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 3:
				Drawer_SetDrawColor(255, 127, 0);
				Drawer_DrawSprite(SPR_spark_spark, x, y, overworld.sparks[i].timer / 8, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 4:
				Drawer_DrawSprite(SPR_spark_blazeimpact, x, y, overworld.sparks[i].timer / 4, 1, 1);
				break;
		}
	}
	
	Drawer_SetProjection(320, 240, 1);
	
	if (overworld.fadeAlpha > 0) {
		Drawer_SetDrawColor(overworld.fadeColor[0], overworld.fadeColor[1], overworld.fadeColor[2]);
		Drawer_SetDrawAlpha(overworld.fadeAlpha * 255);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
	
	switch (overworld.transition.id) {
		case 2:
			if (overworld.transition.timer <= 40) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(0, 0, SCREEN_WIDTH, overworld.transition.timer * SCREEN_HEIGHT / 40);
				Drawer_FillRect(0, SCREEN_HEIGHT - overworld.transition.timer * SCREEN_HEIGHT / 40, SCREEN_WIDTH, overworld.transition.timer * SCREEN_HEIGHT / 40);
				Drawer_SetDrawColor(255, 255, 255);
				
				Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
				for (int i = 0; i < objectCount; i++) {
					OverworldObject* object;
					
					if (objectOrder[i] >= 10 && objectOrder[i] != (int)overworld.transition.vars[0]) continue;
					
					object = &overworld.objects[objectOrder[i]];
					
					Drawer_SetDrawColor(object->color[0], object->color[1], object->color[2]);
					
					if (object->bodyId >= 0) {
						DrawFighterChar(object->headId, object->bodyId, object->fighterState, object->x, object->y, 1, 1, 1 - (object->direction == OBJECT_DIRECTION_LEFT) * 2);
					}
					else if (object->spriteId >= 0) {
						if (object->direction == OBJECT_DIRECTION_LEFT)
							Drawer_DrawSprite(object->spriteId, object->x, object->y, object->spriteFrame, -1, 1);
						else
							Drawer_DrawSprite(object->spriteId, object->x, object->y, object->spriteFrame, 1, 1);
					}
				}
				Drawer_SetProjection(320, 240, 1);
			}
			break;
		case 3:
			if (overworld.transition.timer > 60)
				Drawer_SetDrawAlpha(255 - (overworld.transition.timer - 61) * 255 / 60);
			else
				Drawer_SetDrawAlpha(overworld.transition.timer * 255 / 60);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawAlpha(255);
			break;
	}
	
	if (dialogSystem.state != DIALOG_STATE_IDLE) {
		Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		
		DrawDialogBox(0, SCREEN_HEIGHT - 128, SCREEN_WIDTH, 128);
		Drawer_DrawText(dialogSystem.text, dialogSystem.textLength, 8, SCREEN_HEIGHT - 124, 2, 2);
		
		if (dialogSystem.menu.optionCount > 0) {
			int longestWidth = 1;
			for (int i = 0; i < dialogSystem.menu.optionCount; i++) {
				int width = StringLength(dialogSystem.menu.options[i].name) + 1;
				
				if (width > longestWidth) {
					longestWidth = width;
				}
			}
			DrawDialogBox(0, SCREEN_HEIGHT - 144 - dialogSystem.menu.optionCount * 28, 28 + longestWidth * 16, 16 + dialogSystem.menu.optionCount * 28);
			
			Menu_DrawOptions(&dialogSystem.menu, 0, SCREEN_HEIGHT - 144 - dialogSystem.menu.optionCount * 28, 28 + longestWidth * 16);
		}
		if (dialogSystem.name[0] != 0) {
			Drawer_SetFontAlignment(FONT_ALIGN_RIGHT | FONT_ALIGN_TOP);
			DrawDialogBox(SCREEN_WIDTH - 16 - StringLength(dialogSystem.name) * 16, SCREEN_HEIGHT - 172, 16 + StringLength(dialogSystem.name) * 16, 44);
			Drawer_DrawText(dialogSystem.name, 32, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 168, 2, 2);
		}
	}
	
	if (overworld.state == OVERWORLD_STATE_PAUSED) {
		Overworld_DrawMenu();
	}
}

void Overworld_DrawMap() {
	int minX = overworld.camera.x / 16 - 20 / overworld.camera.zoom - 1;
	int maxX = minX + 40 / overworld.camera.zoom + 2;
	int minY = overworld.camera.y / 16 - 15 / overworld.camera.zoom - 1;
	int maxY = minY + 30 / overworld.camera.zoom + 2;
	
	if (minX < 0) minX = 0;
	if (minX >= overworld.map.w) minX = overworld.map.w - 1;
	if (maxX < 0) maxX = 0;
	if (maxX >= overworld.map.w) maxX = overworld.map.w - 1;
	
	if (minY < 0) minY = 0;
	if (minY >= overworld.map.h) minY = overworld.map.h - 1;
	if (maxY < 0) maxY = 0;
	if (maxY >= overworld.map.h) maxY = overworld.map.h - 1;
	
	for (int j = minY; j <= maxY; j++)
	for (int i = minX; i <= maxX; i++) {
		int tile = overworld.map.tileMap[j][i];
		float tileX = i * 16;
		float tileY = j * 16;
		if (game.scene != SCENE_MAPEDITOR) {
			if (overworld.areaWrap) {
				int x1 = overworld.map.areas[overworld.areaId].x1;
				int y1 = overworld.map.areas[overworld.areaId].y1;
				int x2 = overworld.map.areas[overworld.areaId].x2;
				int y2 = overworld.map.areas[overworld.areaId].y2;
				int w = x2 - x1 + 1;
				int h = y2 - y1 + 1;
				int i2 = i;
				int j2 = j;
				
				if (i2 < x1) i2 = i + w;
				if (i2 > x2) i2 = i - w;
				if (j2 < y1) j2 = j + h;
				if (j2 > y2) j2 = j - h;
				
				tile = overworld.map.tileMap[j2][i2];
			}
			else if (i < overworld.map.areas[overworld.areaId].x1 || i > overworld.map.areas[overworld.areaId].x2 || j < overworld.map.areas[overworld.areaId].y1 || j > overworld.map.areas[overworld.areaId].y2)
				continue;
		}
		
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_DrawSprite(overworld.map.tilesetSpriteId, tileX, tileY, tile, 1, 1);
	}
}

void Overworld_DrawCharBox(int partyId, int x, int y, bool selected) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (selected)
		Drawer_SetDrawColor(255, 255, 0);
	else
		Drawer_SetDrawColor(127, 127, 127);
	
	Drawer_DrawSprite(SPR_gui_owcharbox, x, y, 0, 2, 2);
	
	Drawer_DrawText(partyMember->name, 6, x + 8, y + 4, 2, 2);
	
	Drawer_DrawSprite(SPR_gui_portraitbg, x + 10, y + 36, 0, 2, 2);
	
	Drawer_SetDrawColor(255, 255, 255);
	DrawFighterChar(partyMember->headId, partyMember->bodyId, FIGHTER_STATE_IDLE, x + 54, y + 104, 2, 2, FACING_RIGHT);
	
	int hp = partyMember->hpMax - partyMember->hpDamage;
	if (hp < 1) hp = 1;
	
	Drawer_SetDrawColor(255, 0, 0);
	Drawer_FillRect(x + 12, y + 126, 88 * hp / partyMember->hpMax, 6);
	
	Drawer_SetDrawColor(255, 255, 255);
	Drawer_SetFontSprite(SPR_font_small);
	snprintf(game.textBuffer, 32, "%d / %d", hp, partyMember->hpMax);
	Drawer_DrawText(game.textBuffer, 32, x + 10, y + 110, 2, 2);
	
	if (partyMember->tiredLevel >= 2) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_DrawText("FATIGUED", 32, x + 12, y + 38, 2, 2);
		Drawer_DrawText("FATIGUED", 32, x + 14, y + 36, 2, 2);
		Drawer_DrawText("FATIGUED", 32, x + 16, y + 38, 2, 2);
		Drawer_DrawText("FATIGUED", 32, x + 14, y + 40, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_DrawText("FATIGUED", 32, x + 14, y + 38, 2, 2);
	}
	else if (partyMember->tiredLevel == 1) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_DrawText("TIRED", 32, x + 12, y + 38, 2, 2);
		Drawer_DrawText("TIRED", 32, x + 14, y + 36, 2, 2);
		Drawer_DrawText("TIRED", 32, x + 16, y + 38, 2, 2);
		Drawer_DrawText("TIRED", 32, x + 14, y + 40, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_DrawText("TIRED", 32, x + 14, y + 38, 2, 2);
	}
	Drawer_SetFontSprite(SPR_font_main);
}

void Overworld_UpdateMenu() {
	Menu_Update(&overworld.menu);
	if (overworld.menu.id == 1) {
		if (overworld.menu.optionPressed == 0) {
			overworld.menuBuffer[0] = overworld.menu;
			
			Overworld_ChangeMenu(2);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == 1) {
			overworld.menuBuffer[0] = overworld.menu;
			
			Overworld_ChangeMenu(11);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == 2) {
			overworld.menuBuffer[0] = overworld.menu;
			
			overworld.menu.cursors[1] = 1;
			Overworld_ChangeMenu(7);
			overworld.menu.cursors[1] = 0;
			Menu_ResetCursor(&overworld.menu);
			
			overworld.menuBuffer[1] = overworld.menu;
			overworld.menuBuffer[1].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(14);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == 3) {
			overworld.menuBuffer[0] = overworld.menu;
			
			Overworld_ChangeMenu(12);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			overworld.state = OVERWORLD_STATE_IDLE;
		}
	}
	else if (overworld.menu.id == 2) {
		if (overworld.menu.optionPressed >= 0) {
			Overworld_ChangeMenu(3);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(1);
		}
	}
	else if (overworld.menu.id == 3) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		
		if (overworld.menu.optionPressed == 0) {
			Overworld_ChangeMenu(5);
			Menu_ResetCursor(&overworld.menu);
			
			overworld.menuBuffer[2] = overworld.menu;
			overworld.menuBuffer[2].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(4);
			Menu_ResetCursor(&overworld.menu);
			
			overworld.menuBuffer[1] = overworld.menu;
		}
		else if (overworld.menu.optionPressed == 1) {
			Overworld_ChangeMenu(6);
			Menu_ResetCursor(&overworld.menu);
			
			for (int i = 0; i < overworld.menu.optionCount; i++) {
				MenuOption* option = &overworld.menu.options[i];
				
				if (option->value == partyMember->armorId) {
					Menu_SetCursor(&overworld.menu, i);
					break;
				}
			}
		}
		else if (overworld.menu.optionPressed == 2) {
			Overworld_ChangeMenu(10);
			Menu_ResetCursor(&overworld.menu);
			
			overworld.menuBuffer[2] = overworld.menu;
			overworld.menuBuffer[2].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(9);
			Menu_ResetCursor(&overworld.menu);
			
			overworld.menuBuffer[1] = overworld.menu;
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(2);
		}
	}
	else if (overworld.menu.id == 4) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		
		if (overworld.menu.optionPressed >= 0) {
			overworld.menuBuffer[1] = overworld.menu;
			
			Overworld_ChangeMenu(5);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(3);
		}
	}
	else if (overworld.menu.id == 5) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		
		if (overworld.menu.optionPressed >= 0) {
			Audio_PlaySound(SND_menu2);
			if (overworld.menu.optionPressedValue == 0) {
				Profile_UnequipAction(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.cursors[3]);
				Overworld_ChangeMenu(5);
				overworld.menuBuffer[2] = overworld.menu;
				
				Overworld_ChangeMenu(4);
				
				if (overworld.menu.cursors[3] > 0) overworld.menu.cursors[3]--;
			}
			else if (overworld.menu.cursors[3] == partyMember->movesetCount) {
				Profile_EquipAction(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.optionPressedValue);
			}
			else {
				Profile_SwapAction(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.cursors[3], overworld.menu.optionPressedValue);
			}
			Overworld_ChangeMenu(5);
			overworld.menuBuffer[2] = overworld.menu;
			overworld.menuBuffer[2].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(4);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(5);
			overworld.menuBuffer[2] = overworld.menu;
			overworld.menuBuffer[2].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(4);
		}
	}
	else if (overworld.menu.id == 6) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		
		if (overworld.menu.optionPressed >= 0) {
			Audio_PlaySound(SND_menu2);
			Profile_EquipArmor(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.optionPressedValue);
			Overworld_ChangeMenu(6);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(3);
		}
	}
	else if (overworld.menu.id == 7) {
		if (overworld.menu.optionPressed >= 0 && profile.itemInventory[0] > 0) {
			if (overworld.menu.cursors[1] == 1) {
				Profile_ItemRemove(overworld.menu.cursors[2]);
				Overworld_ChangeMenu(7);
				if (overworld.menu.cursors[2] > 0) Menu_SetCursor(&overworld.menu, overworld.menu.cursors[2] - 1);
			}
			else {
				overworld.menuBuffer[1] = overworld.menu;
				
				Overworld_ChangeMenu(8);
			}
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			int temp = overworld.menu.cursors[1];
			overworld.menu.cursors[1] = 1;
			Overworld_ChangeMenu(7);
			overworld.menu.cursors[1] = temp;
			
			overworld.menuBuffer[1] = overworld.menu;
			overworld.menuBuffer[1].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(14);
		}
	}
	else if (overworld.menu.id == 8) {
		if (overworld.menu.optionPressed >= 0) {
			Item_UseInOverworld(overworld.menu.cursors[2], profile.partyOrder[overworld.menu.cursors[3]]);
			Overworld_ChangeMenu(7);
			if (overworld.menu.cursors[2] > 0) Menu_SetCursor(&overworld.menu, overworld.menu.cursors[2] - 1);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(7);
		}
	}
	else if (overworld.menu.id == 9) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		
		if (overworld.menu.optionPressed >= 0) {
			overworld.menuBuffer[1] = overworld.menu;
			
			Overworld_ChangeMenu(10);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(3);
		}
	}
	else if (overworld.menu.id == 10) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		
		if (overworld.menu.optionPressed >= 0) {
			Audio_PlaySound(SND_menu2);
			if (overworld.menu.optionPressedValue == 0) {
				Profile_UnequipPassive(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.cursors[3] - partyMember->passiveCount + partyMember->extraPassiveCount);
				Overworld_ChangeMenu(10);
				overworld.menuBuffer[2] = overworld.menu;
				
				Overworld_ChangeMenu(9);
				
				if (overworld.menu.cursors[3] > 0) overworld.menu.cursors[3]--;
			}
			else if (overworld.menu.cursors[3] == partyMember->passiveCount) {
				Profile_EquipPassive(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.optionPressedValue);
			}
			else {
				Profile_SwapPassive(profile.partyOrder[overworld.menu.cursors[1]], overworld.menu.cursors[3] - partyMember->passiveCount + partyMember->extraPassiveCount, overworld.menu.optionPressedValue);
			}
			Overworld_ChangeMenu(10);
			overworld.menuBuffer[2] = overworld.menu;
			overworld.menuBuffer[2].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(9);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(10);
			overworld.menuBuffer[2] = overworld.menu;
			overworld.menuBuffer[2].cursors[overworld.menu.cursorId] = -1;
			
			Overworld_ChangeMenu(9);
		}
	}
	else if (overworld.menu.id == 11) {
		if (overworld.menu.optionPressed >= 0) {
			
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(1);
		}
	}
	else if (overworld.menu.id == 12) {
		if (overworld.menu.optionPressed >= 0 && profile.keyItemInventory[0] > 0) {
			Item* item = &itemData[profile.keyItemInventory[overworld.menu.cursors[1]]];
			if (item->type == 3) {
				overworld.state = OVERWORLD_STATE_IDLE;
				Event_Trigger(item->vars[0].i);
			}
			else {
				overworld.menuBuffer[1] = overworld.menu;
				
				Overworld_ChangeMenu(13);
				Menu_ResetCursor(&overworld.menu);
			}
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(1);
		}
	}
	else if (overworld.menu.id == 13) {
		if (overworld.menu.optionPressed >= 0) {
			CreatePopup("You can't use key items, Jim!");
			Overworld_ChangeMenu(12);
			if (overworld.menu.cursors[1] > 0) overworld.menu.cursors[1]--;
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(12);
		}
	}
	else if (overworld.menu.id == 14) {
		if (overworld.menu.optionPressed >= 0) {
			overworld.menuBuffer[2] = overworld.menu;
			
			Overworld_ChangeMenu(8);
			Menu_ResetCursor(&overworld.menu);
			
			Overworld_ChangeMenu(7);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(1);
		}
	}
	else if (overworld.menu.id == 10001) {
		if (overworld.menu.optionPressed >= 0) {
			Overworld_ChangeMenu(10001);
			overworld.menuBuffer[0] = overworld.menu;
			
			Overworld_ChangeMenu(10002);
			Menu_ResetCursor(&overworld.menu);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			overworld.state = OVERWORLD_STATE_IDLE;
		}
	}
	else if (overworld.menu.id == 10002) {
		if (overworld.menu.optionPressed == 0) {
			if (profile.cash >= overworld.shop.items[overworld.menu.cursors[0]].cost && !Profile_ItemInventoryIsFull()) {
				Audio_PlaySound(SND_menu2);
				
				profile.cash -= overworld.shop.items[overworld.menu.cursors[0]].cost;
				Profile_ItemAdd(overworld.shop.items[overworld.menu.cursors[0]].id);
			}
			else {
				Audio_PlaySound(SND_menu1);
			}
			
			Overworld_ChangeMenu(10001);
		}
		else if (overworld.menu.optionPressed == 1 || overworld.menu.optionPressed == MENUOPTION_BACK) {
			Overworld_ChangeMenu(10001);
		}
	}
	else if (overworld.menu.id == 10003) {
		if (overworld.menu.optionPressed >= 0 && !overworld.lockSaving) {
			profile.flags[FLAG_SAVECOUNT]++;
			int ret = Profile_SaveGameSlot(overworld.menu.optionPressed);
			if (ret == 1) {
				Audio_PlaySound(SND_save);
				overworld.lockSaving = true;
				game.saveFileNumber = overworld.menu.optionPressed;
				overworld.menu.canNavigate = false;
			}
			else if (ret == -1) {
				profile.flags[FLAG_SAVECOUNT]--;
				Audio_PlaySound(SND_no);
				CreatePopup("Failed to save. Make sure you have\npermission to modify the save folder\nand the file isn't used by other\nprograms.");
			}
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			overworld.state = OVERWORLD_STATE_IDLE;
		}
	}
	else if (overworld.menu.id == 10004) {
		if (overworld.menu.optionPressed >= 0) {
			overworld.state = OVERWORLD_STATE_IDLE;
			Event_Trigger(72);
		}
		else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
			
		}
	}
}

void Overworld_DrawMenu() {
	if (overworld.menu.id < 10000) {
		DrawDialogBox(0, 0, 640, 72);
	}
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	if (overworld.menu.id == 1)
		Menu_DrawOptions(&overworld.menu, 0, 0, 632);
	else if (overworld.menu.id < 10000)
		Menu_DrawOptions(&overworld.menuBuffer[0], 0, 0, 632);
	
	if (overworld.menu.id >= 1 && overworld.menu.id < 10000) {
		for (int i = 0; i < 5; i++) {
			if (profile.partyOrder[i] < 0) break;
			
			Overworld_DrawCharBox(profile.partyOrder[i], 4 + i * 116, SCREEN_HEIGHT - 144, overworld.menu.cursors[1] == i && (overworld.menu.id == 2 || overworld.menu.id == 8));
		}
	}
	if (overworld.menu.id == 3) {
		DrawDialogBox(0, 128, 144, 72 + profile.flags[FLAG_BADGES_UNLOCKED] * 28);
		
		Menu_DrawOptions(&overworld.menu, 0, 128, 136);
	}
	if (overworld.menu.id == 4 || overworld.menu.id == 5) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		Armor* armor;
		if (partyMember->armorId == 0)
			armor = &armorData[partyMember->defaultArmorId];
		else
			armor = &armorData[partyMember->armorId];
		
		DrawDialogBox(0, 0, 320, 196);
		DrawDialogBox(320, 0, 320, 196);
		
		Drawer_DrawText(partyMember->name, 32, 520, 4, 2, 2);
		
		Drawer_SetDrawColor(0, 127, 255);
		Drawer_DrawSprite(SPR_gui_portraitbg, 524, 40, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawFighterChar(partyMember->headId, partyMember->bodyId, FIGHTER_STATE_IDLE, 568, 108, 2, 2, FACING_RIGHT);
		
		Drawer_DrawText(armor->name, 32, 328, 4, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x01 %d (+%d)", partyMember->hpMax, armor->hp);
		Drawer_DrawText(game.textBuffer, 32, 328, 32, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x02 %d (+%d)", partyMember->mpMax, armor->mp);
		Drawer_DrawText(game.textBuffer, 32, 328, 60, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x03 %d (+%d)", partyMember->attack, armor->attack);
		Drawer_DrawText(game.textBuffer, 32, 328, 88, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x04 %d (+%d)", partyMember->defense, armor->defense);
		Drawer_DrawText(game.textBuffer, 32, 328, 116, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x05 %d (+%d)", partyMember->speed, armor->speed);
		Drawer_DrawText(game.textBuffer, 32, 328, 144, 2, 2);
		
		if (overworld.menu.id == 4)
			Menu_DrawOptions(&overworld.menu, 0, 0, 312);
		else
			Menu_DrawOptions(&overworld.menuBuffer[1], 0, 0, 312);
		
		DrawDialogBox(0, 196, 640, 156);
		
		if (overworld.menu.id == 5)
			Menu_DrawOptions(&overworld.menu, 0, 196, 632);
		else
			Menu_DrawOptions(&overworld.menuBuffer[2], 0, 196, 632);
		
		int actionId = overworld.menu.options[overworld.menu.cursors[overworld.menu.cursorId]].value;
		Action* action = &actionData[actionId];
		DrawActionDetailBox(actionId, 0, SCREEN_HEIGHT - 128, 0, action->armorOnlyId > 0 && action->armorOnlyId != partyMember->armorId, action->ranged && !armor->ranged);
		
		if (actionId > 0) {
			if (overworld.menu.id == 5) {
				snprintf(game.textBuffer, 128, "Left: %d", profile.actions[actionId] - profile.actionsEquipped[actionId]);
				//DrawText(game.textBuffer, 128, 488, 316, 2, 2);
			}
		}
	}
	if (overworld.menu.id == 6) {
		Menu* menu = &overworld.menu;
		
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		Armor* armor;
		if (partyMember->armorId == 0)
			armor = &armorData[partyMember->defaultArmorId];
		else
			armor = &armorData[partyMember->armorId];
		
		DrawDialogBox(0, 0, 320, 44);
		DrawDialogBox(0, 44, 320, 252);
		DrawDialogBox(320, 0, 320, 296);
		
		snprintf(game.textBuffer, 64, "\x90\x07 %d / %d", profile.gp, profile.gpMax);
		Drawer_DrawText(game.textBuffer, 32, 8, 4, 2, 2);
		
		Drawer_DrawText(partyMember->name, 32, 520, 4, 2, 2);
		
		Drawer_SetDrawColor(0, 127, 255);
		Drawer_DrawSprite(SPR_gui_portraitbg, 524, 40, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawFighterChar(partyMember->headId, partyMember->bodyId, FIGHTER_STATE_IDLE, 568, 108, 2, 2, FACING_RIGHT);
		
		Drawer_DrawText(armor->name, 32, 328, 4, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x01 %d (+%d)", partyMember->hpMax, armor->hp);
		Drawer_DrawText(game.textBuffer, 32, 328, 32, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x02 %d (+%d)", partyMember->mpMax, armor->mp);
		Drawer_DrawText(game.textBuffer, 32, 328, 60, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x03 %d (+%d)", partyMember->attack, armor->attack);
		Drawer_DrawText(game.textBuffer, 32, 328, 88, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x04 %d (+%d)", partyMember->defense, armor->defense);
		Drawer_DrawText(game.textBuffer, 32, 328, 116, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x05 %d (+%d)", partyMember->speed, armor->speed);
		Drawer_DrawText(game.textBuffer, 32, 328, 144, 2, 2);
		
		Drawer_SetDrawColor(0, 127, 255);
		for (int i = 0; i < partyMember->passiveCount; i++) {
			if (i >= partyMember->passiveCount - partyMember->extraPassiveCount) Drawer_SetDrawColor(0, 127, 0);
			Drawer_DrawText(passiveData[partyMember->passives[i]].name, 32, 328, 172 + i * 28, 2, 2);
		}
		Drawer_SetDrawColor(255, 255, 255);
		
		
		
		Armor* armor2 = NULL;
		if (menu->optionCount > 0)
			armor2 = &armorData[menu->options[menu->cursors[menu->cursorId]].value];
		
		if (armor2 != NULL) {
			snprintf(game.textBuffer, 64, "%s \x90\x07 %d", armor2->name, Party_CalculateArmorCost(menu->options[menu->cursors[menu->cursorId]].value));
			Drawer_DrawText(game.textBuffer, 32, 8, 48, 2, 2);
			snprintf(game.textBuffer, 64, "\x90\x01 %d", armor2->hp);
			Drawer_DrawText(game.textBuffer, 32, 8, 76, 2, 2);
			snprintf(game.textBuffer, 64, "\x90\x02 %d", armor2->mp);
			Drawer_DrawText(game.textBuffer, 32, 152, 76, 2, 2);
			snprintf(game.textBuffer, 64, "\x90\x03 %d", armor2->attack);
			Drawer_DrawText(game.textBuffer, 32, 8, 104, 2, 2);
			snprintf(game.textBuffer, 64, "\x90\x04 %d", armor2->defense);
			Drawer_DrawText(game.textBuffer, 32, 152, 104, 2, 2);
			snprintf(game.textBuffer, 64, "\x90\x05 %d", armor2->speed);
			Drawer_DrawText(game.textBuffer, 32, 8, 132, 2, 2);
			
			Drawer_SetDrawColor(0, 127, 255);
			for (int i = 0; i < armor2->passiveCount; i++) {
				Drawer_DrawText(passiveData[armor2->passives[i]].name, 32, 8, 160 + i * 28, 2, 2);
			}
			Drawer_SetDrawColor(255, 255, 255);
		}
		
		DrawDialogBox(0, 296, 640, 184);
		
		int c = 0;
		for (int i = menu->pageColumns * menu->pageRows * menu->page; i < menu->pageColumns * menu->pageRows * (menu->page + 1) && i < menu->optionCount; i++) {
			MenuOption* option = &menu->options[i];
			
			Armor* armor3 = &armorData[option->value];
			int x = 14 + (c % menu->pageColumns) * 104;
			int y = 310 + (c / menu->pageColumns) * 82;
			
			if (i == menu->cursors[menu->cursorId])
				Drawer_SetDrawColor(255, 255, 0);
			else if (option->value == partyMember->armorId)
				Drawer_SetDrawColor(255, 255, 255);
			else if (profile.armors[option->value] - profile.armorsEquipped[option->value] == 0)
				Drawer_SetDrawColor(63, 63, 63);
			else
				Drawer_SetDrawColor(127, 127, 127);
			
			Drawer_DrawSprite(SPR_gui_portraitbg, x, y, 0, 2, 2);
			
			if (option->value == partyMember->armorId)
				Drawer_SetDrawColor(255, 255, 255);
			else if (!option->enabled || profile.armors[option->value] - profile.armorsEquipped[option->value] == 0)
				Drawer_SetDrawColor(0, 0, 0);
			else
				Drawer_SetDrawColor(255, 255, 255);
			
			DrawFighterChar(armor3->headId, armor3->bodyId, FIGHTER_STATE_IDLE, x + 44, y + 68, 2, 2, FACING_RIGHT);
			Drawer_SetDrawColor(255, 255, 255);
			
			c++;
		}
	}
	if (overworld.menu.id == 7 || overworld.menu.id == 8 || overworld.menu.id == 14) {
		DrawDialogBox(0, 72, 640, 44);
		
		if (overworld.menu.id == 14)
			Menu_DrawOptions(&overworld.menu, 0, 72, 632);
		else
			Menu_DrawOptions(&overworld.menuBuffer[2], 0, 72, 632);
		
		
		
		DrawDialogBox(0, 116, 640, 128);
		
		if (overworld.menu.id == 7)
			Menu_DrawOptions(&overworld.menu, 0, 116, 632);
		else
			Menu_DrawOptions(&overworld.menuBuffer[1], 0, 116, 632);
		
		DrawDialogBox(0, 244, 640, 128);
		if (overworld.menu.id == 7 && profile.itemInventory[0] > 0) {
			Drawer_DrawText(GetDialogString(4500 + overworld.menu.options[overworld.menu.cursors[2]].value), 128, 8, 248, 2, 2);
		}
		
		if (overworld.menu.id == 8) {
			for (int i = 0; i < 5; i++) {
				if (profile.partyOrder[i] < 0) break;
				
				Overworld_DrawCharBox(profile.partyOrder[i], 4 + i * 116, SCREEN_HEIGHT - 144, overworld.menu.cursors[3] == i);
			}
		}
	}
	if (overworld.menu.id == 9 || overworld.menu.id == 10) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		Armor* armor;
		if (partyMember->armorId == 0)
			armor = &armorData[partyMember->defaultArmorId];
		else
			armor = &armorData[partyMember->armorId];
		
		DrawDialogBox(0, 0, 320, 44);
		DrawDialogBox(0, 44, 320, 152);
		DrawDialogBox(320, 0, 320, 196);
		
		snprintf(game.textBuffer, 64, "\x90\x07 %d / %d", profile.gp, profile.gpMax);
		Drawer_DrawText(game.textBuffer, 32, 8, 4, 2, 2);
		
		Drawer_DrawText(partyMember->name, 32, 520, 4, 2, 2);
		
		Drawer_SetDrawColor(0, 127, 255);
		Drawer_DrawSprite(SPR_gui_portraitbg, 524, 40, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawFighterChar(partyMember->headId, partyMember->bodyId, FIGHTER_STATE_IDLE, 568, 108, 2, 2, FACING_RIGHT);
		
		Drawer_DrawText(armor->name, 32, 328, 4, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x01 %d (+%d)", partyMember->hpMax, armor->hp);
		Drawer_DrawText(game.textBuffer, 32, 328, 32, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x02 %d (+%d)", partyMember->mpMax, armor->mp);
		Drawer_DrawText(game.textBuffer, 32, 328, 60, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x03 %d (+%d)", partyMember->attack, armor->attack);
		Drawer_DrawText(game.textBuffer, 32, 328, 88, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x04 %d (+%d)", partyMember->defense, armor->defense);
		Drawer_DrawText(game.textBuffer, 32, 328, 116, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x05 %d (+%d)", partyMember->speed, armor->speed);
		Drawer_DrawText(game.textBuffer, 32, 328, 144, 2, 2);
		
		int passiveId = overworld.menu.options[overworld.menu.cursors[overworld.menu.cursorId]].value;
		
		if (overworld.menu.id == 9)
			Menu_DrawOptions(&overworld.menu, 0, 44, 312);
		else
			Menu_DrawOptions(&overworld.menuBuffer[1], 0, 44, 312);
		
		DrawDialogBox(0, 196, 640, 156);
		
		if (overworld.menu.id == 10)
			Menu_DrawOptions(&overworld.menu, 0, 196, 632);
		else
			Menu_DrawOptions(&overworld.menuBuffer[2], 0, 196, 632);
		
		DrawDialogBox(0, SCREEN_HEIGHT - 128, 640, 128);
		if (passiveId > 0) {
			snprintf(game.textBuffer, 160, "%s \x90\x07 %d", passiveData[passiveId].name, passiveData[passiveId].cost);
			Drawer_DrawText(game.textBuffer, 160, 8, 4 + SCREEN_HEIGHT - 128, 2, 2);
			Drawer_DrawText(passiveData[passiveId].desc, 160, 8, 32 + SCREEN_HEIGHT - 128, 2, 2);
			if (overworld.menu.id == 10) {
				snprintf(game.textBuffer, 128, "Left: %d", profile.passives[passiveId] - profile.passivesEquipped[passiveId]);
				Drawer_DrawText(game.textBuffer, 128, 488, 4 + SCREEN_HEIGHT - 128, 2, 2);
			}
		}
	}
	if (overworld.menu.id == 11) {
		PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
		Armor* armor;
		if (partyMember->armorId == 0)
			armor = &armorData[partyMember->defaultArmorId];
		else
			armor = &armorData[partyMember->armorId];
		
		DrawDialogBox(0, 72, 400, 352);
		DrawDialogBox(400, 72, 240, 352);
		
		Drawer_DrawText(partyMember->name, 32, 8, 76, 2, 2);
		
		Drawer_SetFontAlignment(FONT_ALIGN_RIGHT | FONT_ALIGN_TOP);
		snprintf(game.textBuffer, 64, "$%d", profile.cash);
		Drawer_DrawText(game.textBuffer, 32, 392, 76, 2, 2);
		Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		
		Drawer_SetDrawColor(0, 127, 255);
		Drawer_DrawSprite(SPR_gui_portraitbg, 12, 112, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawFighterChar(partyMember->headId, partyMember->bodyId, FIGHTER_STATE_IDLE, 56, 180, 2, 2, FACING_RIGHT);
		
		snprintf(game.textBuffer, 64, "Level %d", partyMember->level);
		Drawer_DrawText(game.textBuffer, 32, 8, 216, 2, 2);
		snprintf(game.textBuffer, 64, "EXP: %d (%d left)", partyMember->exp, partyMember->expNext - partyMember->exp);
		Drawer_DrawText(game.textBuffer, 32, 8, 244, 2, 2);
		snprintf(game.textBuffer, 64, "Rank: ");
		switch (partyMember->rank) {
			case 0: SetString(game.textBuffer + 6, "None"); break;
			case 1: SetString(game.textBuffer + 6, "Amateur"); break;
			case 2: SetString(game.textBuffer + 6, "Intermediate"); break;
			case 3: SetString(game.textBuffer + 6, "Professional"); break;
			case 4: SetString(game.textBuffer + 6, "Low Hero"); break;
			case 5: SetString(game.textBuffer + 6, "Medium Hero"); break;
			case 6: SetString(game.textBuffer + 6, "Top Hero"); break;
			case 7: SetString(game.textBuffer + 6, "Superhero"); break;
			case 8: SetString(game.textBuffer + 6, "Supernatural"); break;
			case 9: SetString(game.textBuffer + 6, "Top Supernatural"); break;
			case 10: SetString(game.textBuffer + 6, "Demigod"); break;
			case 11: SetString(game.textBuffer + 6, "\x8f\x01God\x8f\xff"); break;
			default: SetString(game.textBuffer + 6, "Unknown"); break;
		}
		Drawer_DrawText(game.textBuffer, 32, 8, 384, 2, 2);
		
		
		
		Drawer_DrawText(armor->name, 32, SCREEN_WIDTH - 232, 76, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x01 %d (+%d)", partyMember->hpMax, armor->hp);
		Drawer_DrawText(game.textBuffer, 32, SCREEN_WIDTH - 232, 104, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x02 %d (+%d)", partyMember->mpMax, armor->mp);
		Drawer_DrawText(game.textBuffer, 32, SCREEN_WIDTH - 232, 132, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x03 %d (+%d)", partyMember->attack, armor->attack);
		Drawer_DrawText(game.textBuffer, 32, SCREEN_WIDTH - 232, 160, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x04 %d (+%d)", partyMember->defense, armor->defense);
		Drawer_DrawText(game.textBuffer, 32, SCREEN_WIDTH - 232, 188, 2, 2);
		snprintf(game.textBuffer, 64, "\x90\x05 %d (+%d)", partyMember->speed, armor->speed);
		Drawer_DrawText(game.textBuffer, 32, SCREEN_WIDTH - 232, 216, 2, 2);
		
		Drawer_SetDrawColor(0, 127, 255);
		for (int i = 0; i < partyMember->passiveCount; i++) {
			if (i >= partyMember->passiveCount - partyMember->extraPassiveCount) Drawer_SetDrawColor(0, 127, 0);
			Drawer_DrawText(passiveData[partyMember->passives[i]].name, 32, SCREEN_WIDTH - 232, 244 + i * 28, 2, 2);
		}
		Drawer_SetDrawColor(255, 255, 255);
	}
	if (overworld.menu.id == 12 || overworld.menu.id == 13) {
		DrawDialogBox(0, 72, 640, 280);
		
		if (overworld.menu.id == 12)
			Menu_DrawOptions(&overworld.menu, 0, 72, 632);
		else
			Menu_DrawOptions(&overworld.menuBuffer[1], 0, 72, 632);
		
		DrawDialogBox(0, SCREEN_HEIGHT - 128, 640, 128);
		if (profile.keyItemInventory[0] > 0) {
			Drawer_DrawText(GetDialogString(4500 + overworld.menu.options[overworld.menu.cursors[1]].value), 128, 8, 4 + SCREEN_HEIGHT - 128, 2, 2);
		}
		
		if (overworld.menu.id == 13) {
			for (int i = 0; i < 5; i++) {
				if (profile.partyOrder[i] < 0) break;
				
				Overworld_DrawCharBox(profile.partyOrder[i], 4 + i * 116, SCREEN_HEIGHT - 144, overworld.menu.cursors[2] == i);
			}
		}
	}
	
	if (overworld.menu.id == 10001 || overworld.menu.id == 10002) {
		DrawDialogBox(0, 0, 400, 288);
		DrawDialogBox(400, 0, 240, 128);
		DrawDialogBox(400, 128, 240, 160);
		
		Drawer_DrawText("Shop", 32, 8, 4, 2, 2);
		
		if (overworld.menu.id == 10001)
			Menu_DrawOptions(&overworld.menu, 0, 28, 312);
		else
			Menu_DrawOptions(&overworld.menuBuffer[0], 0, 28, 312);
		
		if (profile.cash < overworld.shop.items[overworld.menu.cursors[0]].cost)
			Drawer_SetDrawColor(255, 0, 0);
		else
			Drawer_SetDrawColor(255, 255, 0);
		snprintf(game.textBuffer, 128, "$%d", profile.cash);
		Drawer_DrawText(game.textBuffer, 128, 408, 4, 2, 2);
		
		if (Profile_ItemInventoryIsFull())
			Drawer_SetDrawColor(255, 0, 0);
		else
			Drawer_SetDrawColor(255, 255, 255);
		int itemCount = 0;
		for (itemCount = 0; itemCount < 16; itemCount++) {
			if (profile.itemInventory[itemCount] == 0) {
				break;
			}
		}
		snprintf(game.textBuffer, 128, "Goods: %d/16", itemCount);
		Drawer_DrawText(game.textBuffer, 128, 408, 32, 2, 2);
		
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawDialogBox(0, 288, 640, 128);
		Drawer_DrawText(GetDialogString(4500 + overworld.shop.items[overworld.menu.cursors[0]].id), 128, 8, 292, 2, 2);
		
		if (overworld.menu.id == 10002) {
			Menu_DrawOptions(&overworld.menu, 400, 128, 312);
		}
	}
	if (overworld.menu.id == 10003) {
		DrawDialogBox(24, 0, 592, SCREEN_HEIGHT);
		Drawer_DrawText("Save", 128, 32, 4, 2, 2);
		Menu* menu = &overworld.menu;
		int c = 0;
		for (int i = menu->pageColumns * menu->pageRows * menu->page; i < menu->pageColumns * menu->pageRows * (menu->page + 1) && i < menu->optionCount; i++) {
			int x = 32;
			int y = 40 + (c / menu->pageColumns) * 100;
			DrawSaveFile(i, x, y, 3 * (menu->cursors[0] == i && overworld.lockSaving), menu->cursors[0] == i);
			c++;
		}
		
		Drawer_SetDrawColor(255, 255, 255);
		if (menu->page + 1 < menu->pageCount)
			Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 4, 456, 0, 2, 2);
		if (menu->page - 1 >= 0)
			Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 32, 456, 0, -2, 2);
	}
	if (overworld.menu.id == 10004) {
		DrawDialogBox(0, 0, 640, 128);
		
		Menu_DrawOptions(&overworld.menu, 0, 0, 632);
		
		DrawDialogBox(0, 352, 640, 128);
		DrawDialogBox(0, 308, 640, 44);
		switch (overworld.menu.cursors[0]) {
			case 0:
				Drawer_DrawText("Ruby's idea", 128, 8, 312, 2, 2);
				Drawer_DrawText("The idea is simple - you fight the\nmanager.\n\nSuccess chance: decent", 128, 8, 356, 2, 2);
				break;
			case 1:
				Drawer_DrawText("Noah's idea", 128, 8, 312, 2, 2);
				Drawer_DrawText("Revolves around using the rolling\nfurniture to block the manager's path.\n\nSuccess chance: great (in theory)", 128, 8, 356, 2, 2);
				break;
			case 2:
				Drawer_DrawText("Emmet's idea", 128, 8, 312, 2, 2);
				Drawer_DrawText("Bribe the manager by offering lots of\nmoney.\n\nSuccess chance: poor unless you're rich", 128, 8, 356, 2, 2);
				break;
			case 3:
				Drawer_DrawText("Sally's idea", 128, 8, 312, 2, 2);
				Drawer_DrawText("Involves convincing the manager to\nnot proceed by words.\n\nSuccess chance: (doe, she know)", 128, 8, 356, 2, 2);
				break;
			default:
				Drawer_DrawText("Glitch idea", 128, 8, 312, 2, 2);
				Drawer_DrawText("This is an error. DO NOT TRY AT\nHOME OR YOUR SAVE FILES MIGHT BE\nLOST FOREVER!!! Report this first!\nSuccess chance: N/A", 128, 8, 356, 2, 2);
				break;
		}
	}
}

void Overworld_ChangeMenu(int id) {
	overworld.menu.id = id;
	switch (id) {
		case 1:
			Menu_New(&overworld.menu, 1, 2, 2, 0);
			Menu_AddOption(&overworld.menu, true, 0, "Equipment");
			Menu_AddOption(&overworld.menu, true, 1, "Stats");
			Menu_AddOption(&overworld.menu, profile.itemInventory[0] > 0, 2, "Goods");
			Menu_AddOption(&overworld.menu, profile.keyItemInventory[0] > 0, 3, "Key Items");
			break;
		case 2:
			Menu_New(&overworld.menu, 2, 999, 1, 1);
			for (int i = 0; i < 5; i++) {
				if (profile.partyOrder[i] < 0) break;
				
				PartyMember* partyMember = &partyMembers[profile.partyOrder[i]];
				
				Menu_AddOption(&overworld.menu, true, i, partyMember->name);
			}
			break;
		case 3:
			Menu_New(&overworld.menu, 3, 1, 3, 2);
			Menu_AddOption(&overworld.menu, true, 0, "Skills");
			Menu_AddOption(&overworld.menu, true, 1, "Armor");
			if (profile.flags[FLAG_BADGES_UNLOCKED]) Menu_AddOption(&overworld.menu, true, 2, "Badges");
			break;
		case 4:
			Menu_New(&overworld.menu, 4, 1, 6, 3);
			{
				PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
				
				for (int i = 0; i < 6; i++) {
					if (i >= partyMember->movesetCount) {
						Menu_AddOption(&overworld.menu, true, 0, "--------");
						break;
					}
					
					Menu_AddOption(&overworld.menu, true, partyMember->moveset[i], actionData[partyMember->moveset[i]].name);
				}
			}
			break;
		case 5:
			Menu_New(&overworld.menu, 5, 2, 5, 4);
			Menu_AddOption(&overworld.menu, true, 0, "--------");
			for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
				if (profile.actions[i] <= 0) continue;
				
				Action* action = &actionData[i];
				PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
				
				Menu_AddOption(&overworld.menu, profile.actionsEquipped[i] < profile.actions[i] && !(action->armorOnlyId > 0 && action->armorOnlyId != partyMember->armorId) && (!action->ranged || armorData[partyMember->armorId].ranged), i, action->name);
			}
			break;
		case 6:
			Menu_New(&overworld.menu, 6, 6, 2, 3);
			for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
				if (profile.armors[i] <= 0) continue;
				
				Armor* armor = &armorData[i];
				
				Menu_AddOption(&overworld.menu, true, i, armor->name);
			}
			break;
		case 7:
			Menu_New(&overworld.menu, 7, 2, 4, 2);
			for (int i = 0; i < 16; i++) {
				if (profile.itemInventory[i] == 0) continue;
				
				Item* item = &itemData[profile.itemInventory[i]];
				
				Menu_AddOption(&overworld.menu, item->type == 1 || item->type == 3 || overworld.menu.cursors[1] == 1, profile.itemInventory[i], item->name);
			}
			break;
		case 8:
			Menu_New(&overworld.menu, 8, 999, 1, 3);
			for (int i = 0; i < 5; i++) {
				if (profile.partyOrder[i] < 0) break;
				
				PartyMember* partyMember = &partyMembers[profile.partyOrder[i]];
				
				Menu_AddOption(&overworld.menu, true, i, partyMember->name);
			}
			break;
		case 9:
			Menu_New(&overworld.menu, 9, 1, 4, 3);
			{
				PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
				
				for (int i = 0; i < 4; i++) {
					if (i >= partyMember->passiveCount) {
						Menu_AddOption(&overworld.menu, true, 0, "--------");
						break;
					}
					
					Menu_AddOption(&overworld.menu, i >= partyMember->passiveCount - partyMember->extraPassiveCount, partyMember->passives[i], passiveData[partyMember->passives[i]].name);
				}
			}
			break;
		case 10:
			Menu_New(&overworld.menu, 10, 2, 5, 4);
			Menu_AddOption(&overworld.menu, true, 0, "--------");
			{
				PartyMember* partyMember = &partyMembers[profile.partyOrder[overworld.menu.cursors[1]]];
				
				for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
					if (profile.passives[i] <= 0) continue;
					
					Passive* passive = &passiveData[i];
					
					bool alreadyEquipped = false;
					for (int j = 0; j < partyMember->passiveCount; j++) {
						if (partyMember->passives[j] == i) {
							alreadyEquipped = true;
							break;
						}
					}
					
					Menu_AddOption(&overworld.menu, profile.passivesEquipped[i] < profile.passives[i] && !alreadyEquipped, i, passive->name);
				}
			}
			break;
		case 11:
			Menu_New(&overworld.menu, 11, 999, 1, 1);
			for (int i = 0; i < 5; i++) {
				if (profile.partyOrder[i] < 0) break;
				
				PartyMember* partyMember = &partyMembers[profile.partyOrder[i]];
				
				Menu_AddOption(&overworld.menu, true, i, partyMember->name);
			}
			break;
		case 12:
			Menu_New(&overworld.menu, 12, 2, 9, 1);
			for (int i = 0; i < 64; i++) {
				if (profile.keyItemInventory[i] == 0) continue;
				
				Item* item = &itemData[profile.keyItemInventory[i]];
				
				Menu_AddOption(&overworld.menu, item->type == 1 || item->type == 3, profile.keyItemInventory[i], item->name);
			}
			break;
		case 13:
			Menu_New(&overworld.menu, 13, 999, 1, 2);
			for (int i = 0; i < 5; i++) {
				if (profile.partyOrder[i] < 0) break;
				
				PartyMember* partyMember = &partyMembers[profile.partyOrder[i]];
				
				Menu_AddOption(&overworld.menu, true, i, partyMember->name);
			}
			break;
		case 14:
			Menu_New(&overworld.menu, 14, 3, 1, 1);
			Menu_AddOption(&overworld.menu, true, 0, "Use");
			Menu_AddOption(&overworld.menu, true, 1, "Drop");
			break;
		
		case 10001:
			Menu_New(&overworld.menu, 10001, 1, 8, 0);
			
			for (int i = 0; i < 16; i++) {
				if (overworld.shop.items[i].id == 0) break;
				snprintf(game.textBuffer, 64, "%s - $%d", itemData[overworld.shop.items[i].id].name, overworld.shop.items[i].cost);
				Menu_AddOption(&overworld.menu, true, overworld.shop.items[i].id, game.textBuffer);
			}
			break;
		case 10002:
			Menu_New(&overworld.menu, 10002, 1, 2, 1);
			Menu_AddOption(&overworld.menu, true, 0, "Buy");
			Menu_AddOption(&overworld.menu, true, 1, "Cancel");
			break;
		case 10003:
			Menu_New(&overworld.menu, 10003, 1, 4, 0);
			for (int i = 0; i < 32; i++) {
				Menu_AddOption(&overworld.menu, true, i, "");
			}
			overworld.lockSaving = false;
			break;
		case 10004:
			Menu_New(&overworld.menu, 10004, 2, 2, 0);
			Menu_ResetCursor(&overworld.menu);
			
			Menu_AddOption(&overworld.menu, true, 0, "Ruby");
			Menu_AddOption(&overworld.menu, true, 1, "Noah");
			Menu_AddOption(&overworld.menu, true, 2, "Emmet");
			Menu_AddOption(&overworld.menu, true, 3, "Sally");
			break;
	}
}

void Overworld_OpenShopMenu(int id) {
	for (int i = 0; i < 16; i++) {
		overworld.shop.items[i].id = 0;
	}
	
	switch (id) {
		case 1:
			overworld.shop.items[0].id = 1;
			overworld.shop.items[0].cost = 2;
			break;
		case 2:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 10;
			overworld.shop.items[1].id = 5;
			overworld.shop.items[1].cost = 2;
			overworld.shop.items[2].id = 3;
			overworld.shop.items[2].cost = 39;
			break;
		case 3:
			overworld.shop.items[0].id = 9;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 10;
			overworld.shop.items[1].cost = 4;
			overworld.shop.items[2].id = 11;
			overworld.shop.items[2].cost = 6;
			break;
		case 4:
			overworld.shop.items[0].id = 1;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 13;
			overworld.shop.items[1].cost = 12;
			overworld.shop.items[2].id = 7;
			overworld.shop.items[2].cost = 13;
			break;
		case 5:
			overworld.shop.items[0].id = 5;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 12;
			overworld.shop.items[1].cost = 3;
			break;
		case 6:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 9;
			overworld.shop.items[1].id = 9;
			overworld.shop.items[1].cost = 1;
			overworld.shop.items[2].id = 10;
			overworld.shop.items[2].cost = 3;
			overworld.shop.items[3].id = 14;
			overworld.shop.items[3].cost = 4;
			overworld.shop.items[4].id = 15;
			overworld.shop.items[4].cost = 9;
			break;
		case 7:
			overworld.shop.items[0].id = 9;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 1;
			overworld.shop.items[1].cost = 3;
			overworld.shop.items[2].id = 5;
			overworld.shop.items[2].cost = 2;
			overworld.shop.items[3].id = 7;
			overworld.shop.items[3].cost = 16;
			overworld.shop.items[4].id = 6;
			overworld.shop.items[4].cost = 8;
			break;
		case 8:
			overworld.shop.items[0].id = 13;
			overworld.shop.items[0].cost = 15;
			overworld.shop.items[1].id = 2;
			overworld.shop.items[1].cost = 12;
			overworld.shop.items[2].id = 10;
			overworld.shop.items[2].cost = 5;
			overworld.shop.items[3].id = 11;
			overworld.shop.items[3].cost = 7;
			overworld.shop.items[4].id = 12;
			overworld.shop.items[4].cost = 7;
			overworld.shop.items[5].id = 14;
			overworld.shop.items[5].cost = 7;
			break;
		case 9:
			overworld.shop.items[0].id = 9;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 3;
			overworld.shop.items[1].cost = 39;
			break;
		case 10:
			overworld.shop.items[0].id = 11;
			overworld.shop.items[0].cost = 3;
			overworld.shop.items[1].id = 3;
			overworld.shop.items[1].cost = 26;
			overworld.shop.items[2].id = 4;
			overworld.shop.items[2].cost = 44;
			break;
		case 11:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 10;
			overworld.shop.items[1].id = 13;
			overworld.shop.items[1].cost = 12;
			overworld.shop.items[2].id = 14;
			overworld.shop.items[2].cost = 4;
			overworld.shop.items[3].id = 15;
			overworld.shop.items[3].cost = 10;
			break;
		case 12:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 12;
			overworld.shop.items[1].id = 7;
			overworld.shop.items[1].cost = 16;
			overworld.shop.items[2].id = 19;
			overworld.shop.items[2].cost = 14;
			overworld.shop.items[3].id = 21;
			overworld.shop.items[3].cost = 24;
			overworld.shop.items[4].id = 9;
			overworld.shop.items[4].cost = 1;
			overworld.shop.items[5].id = 11;
			overworld.shop.items[5].cost = 3;
			overworld.shop.items[6].id = 14;
			overworld.shop.items[6].cost = 3;
			overworld.shop.items[7].id = 25;
			overworld.shop.items[7].cost = 29;
			break;
		case 13:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 13;
			overworld.shop.items[1].cost = 3;
			overworld.shop.items[2].id = 14;
			overworld.shop.items[2].cost = 1;
			overworld.shop.items[3].id = 15;
			overworld.shop.items[3].cost = 2;
			break;
		case 14:
			overworld.shop.items[0].id = 9;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 1;
			overworld.shop.items[1].cost = 3;
			overworld.shop.items[2].id = 5;
			overworld.shop.items[2].cost = 2;
			overworld.shop.items[3].id = 7;
			overworld.shop.items[3].cost = 16;
			overworld.shop.items[4].id = 6;
			overworld.shop.items[4].cost = 8;
			overworld.shop.items[5].id = 2;
			overworld.shop.items[5].cost = 12;
			overworld.shop.items[6].id = 21;
			overworld.shop.items[6].cost = 24;
			break;
		case 15:
			overworld.shop.items[0].id = 9;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 10;
			overworld.shop.items[1].cost = 4;
			overworld.shop.items[2].id = 11;
			overworld.shop.items[2].cost = 7;
			overworld.shop.items[3].id = 12;
			overworld.shop.items[3].cost = 7;
			overworld.shop.items[4].id = 14;
			overworld.shop.items[4].cost = 7;
			overworld.shop.items[5].id = 15;
			overworld.shop.items[5].cost = 12;
			overworld.shop.items[6].id = 25;
			overworld.shop.items[6].cost = 29;
			break;
		case 16:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 12;
			overworld.shop.items[1].id = 13;
			overworld.shop.items[1].cost = 15;
			overworld.shop.items[2].id = 7;
			overworld.shop.items[2].cost = 16;
			overworld.shop.items[3].id = 18;
			overworld.shop.items[3].cost = 12;
			overworld.shop.items[4].id = 20;
			overworld.shop.items[4].cost = 18;
			break;
		case 17:
			overworld.shop.items[0].id = 9;
			overworld.shop.items[0].cost = 2;
			overworld.shop.items[1].id = 3;
			overworld.shop.items[1].cost = 20;
			overworld.shop.items[2].id = 23;
			overworld.shop.items[2].cost = 71;
			overworld.shop.items[3].id = 28;
			overworld.shop.items[3].cost = 25;
			break;
		case 18:
			overworld.shop.items[0].id = 28;
			overworld.shop.items[0].cost = 25;
			break;
		case 19:
			overworld.shop.items[0].id = 11;
			overworld.shop.items[0].cost = 3;
			overworld.shop.items[1].id = 3;
			overworld.shop.items[1].cost = 17;
			overworld.shop.items[2].id = 23;
			overworld.shop.items[2].cost = 56;
			overworld.shop.items[3].id = 26;
			overworld.shop.items[3].cost = 29;
			overworld.shop.items[4].id = 4;
			overworld.shop.items[4].cost = 34;
			overworld.shop.items[5].id = 30;
			overworld.shop.items[5].cost = 98;
			overworld.shop.items[6].id = 16;
			overworld.shop.items[6].cost = 18000;
			break;
		case 20:
			overworld.shop.items[0].id = 2;
			overworld.shop.items[0].cost = 5;
			overworld.shop.items[1].id = 18;
			overworld.shop.items[1].cost = 5;
			overworld.shop.items[2].id = 13;
			overworld.shop.items[2].cost = 8;
			overworld.shop.items[3].id = 15;
			overworld.shop.items[3].cost = 8;
			break;
		case 21:
			overworld.shop.items[0].id = 12;
			overworld.shop.items[0].cost = 3;
			overworld.shop.items[1].id = 6;
			overworld.shop.items[1].cost = 4;
			overworld.shop.items[2].id = 28;
			overworld.shop.items[2].cost = 30;
			overworld.shop.items[3].id = 27;
			overworld.shop.items[3].cost = 160;
			overworld.shop.items[4].id = 30;
			overworld.shop.items[4].cost = 120;
			break;
	}
	
	overworld.shop.id = id;
	
	overworld.state = OVERWORLD_STATE_PAUSED;
	Overworld_ChangeMenu(10001);
	Menu_ResetCursor(&overworld.menu);
}

void Overworld_OpenSaveMenu() {
	overworld.state = OVERWORLD_STATE_PAUSED;
	Overworld_ChangeMenu(10003);
	Menu_ResetCursor(&overworld.menu);
	Menu_SetCursor(&overworld.menu, game.saveFileNumber);
}

void Overworld_FadeIn(int time, uint8_t r, uint8_t g, uint8_t b) {
	overworld.transition.id = 4;
	overworld.transition.timer = 0;
	overworld.transition.vars[0] = time;
	overworld.fadeColor[0] = r;
	overworld.fadeColor[1] = g;
	overworld.fadeColor[2] = b;
}

void Overworld_FadeOut(int time, uint8_t r, uint8_t g, uint8_t b) {
	overworld.transition.id = 5;
	overworld.transition.timer = 0;
	overworld.transition.vars[0] = time;
	overworld.fadeColor[0] = r;
	overworld.fadeColor[1] = g;
	overworld.fadeColor[2] = b;
}

void Overworld_ShakeScreen(int timer) {
	overworld.shakeTimer = timer;
}



void Overworld_CreateObject(int objectId, int type, int id, float x, float y, int direction) {
	OverworldObject* object = &overworld.objects[objectId];
	
	if (object->type > 0 && objectId >= 8) {
		printf("Note: replacing existing object %d\n", objectId);
	}
	
	object->type = type;
	object->id = id;
	object->state = OBJECT_STATE_IDLE;
	object->timer = 0;
	object->x = x;
	object->y = y;
	object->z = 0;
	object->w = 0;
	object->h = 0;
	object->collisionOffsetX = 0;
	object->collisionOffsetY = 0;
	object->direction = direction;
	object->depth = -y;
	object->spriteId = -1;
	object->spriteFrame = 0;
	object->spriteType = 0;
	object->spriteFrameFraction = 0;
	object->spriteFrameSpeed = 0;
	object->color[0] = 255; object->color[1] = 255; object->color[2] = 255;
	object->xPrev = x;
	object->yPrev = y;
	object->bodyId = -1;
	object->walkAnimationEnabled = true;
	object->ghost = false;
	object->climbSpriteId = -1;
	object->moveTarget.enabled = false;
	for (int i = 0; i < MOVETARGET_QUEUE_MAX; i++) object->moveTargetQueue[i].enabled = false;
	for (int i = 0; i < 8; i++) object->vars[i].i = 0;
	
	if (type == 1) {
		OverworldObject_ChangeSpriteId(objectId, id);
	}
	
	if (direction >= 0) OverworldObject_ChangeDirection(objectId, direction);
}

void Overworld_CreateNPC(int objectId, int id, float x, float y, int direction) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->type = 2;
	object->id = id;
	object->state = OBJECT_STATE_IDLE;
	object->x = x;
	object->y = y;
	object->z = 0;
	object->w = 14;
	object->h = 8;
	object->collisionOffsetX = 0;
	object->collisionOffsetY = 0;
	object->direction = direction;
	object->depth = -y;
	object->spriteId = SPR_owchar_ruby;
	object->spriteFrame = 0;
	object->spriteType = 0;
	object->spriteFrameFraction = 0;
	object->spriteFrameSpeed = 0;
	object->color[0] = 255; object->color[1] = 255; object->color[2] = 255;
	object->xPrev = x;
	object->yPrev = y;
	object->bodyId = -1;
	object->walkAnimationEnabled = true;
	object->ghost = false;
	object->climbSpriteId = -1;
	object->moveTarget.enabled = false;
	for (int i = 0; i < MOVETARGET_QUEUE_MAX; i++) object->moveTargetQueue[i].enabled = false;
	object->vars[0].i = 0;
	object->vars[1].i = 0;
	object->vars[2].f = x;
	object->vars[3].f = y;
	object->vars[4].i = 0;
	object->vars[5].i = 0;
	object->vars[6].i = 0;
	object->vars[7].i = 0;
	
	switch (id) {
		case 0:
			object->spriteId = SPR_owchar_noah;
			break;
		case 1:
			object->spriteId = SPR_owchar_lulu;
			break;
		case 2:
			object->spriteId = SPR_owchar_leafcrew;
			break;
		case 3:
			object->spriteId = SPR_owchar_police_0;
			break;
		case 4:
			object->spriteId = SPR_owchar_electra_purple;
			break;
		case 5:
			object->spriteId = SPR_owchar_ray;
			break;
		case 6:
			object->spriteId = SPR_misc_silversakura;
			break;
		case 7:
			object->spriteId = SPR_owchar_noah;
			break;
		case 8:
			if (profile.flags[FLAG_GREGORY_OPTIONALFIGHT]) {
				object->spriteId = SPR_owchar_lisao;
				break;
			}
			object->spriteId = SPR_misc_lisao_sleep;
			object->spriteFrameSpeed = 0.01;
			break;
		case 9:
			object->spriteId = SPR_owchar_electra_purple;
			break;
		case 10:
			object->spriteId = SPR_owchar_perry;
			break;
		case 11:
			object->spriteId = SPR_misc_present;
			break;
		case 12:
			object->spriteId = SPR_owchar_npc_0;
			break;
		case 13:
			object->spriteId = SPR_owchar_npc_1;
			break;
		case 14:
			object->spriteId = SPR_owchar_npc_8;
			break;
		case 15:
			object->spriteId = SPR_owchar_npc_5;
			break;
		case 16:
			object->spriteId = SPR_owchar_npc_6;
			break;
		case 17:
			object->spriteId = SPR_owchar_npc_7;
			break;
		case 18:
			object->spriteId = SPR_owchar_npc_3;
			break;
		case 19:
			object->spriteId = SPR_owchar_leafcrew_alt;
			break;
		case 20:
			object->spriteId = SPR_owchar_leafcrew;
			break;
		case 21:
			object->spriteId = SPR_owchar_leafcrew;
			break;
		case 22:
			object->spriteId = SPR_owchar_leafcrew;
			break;
		case 23:
			object->spriteId = SPR_owchar_npc_2;
			break;
		case 24:
			object->spriteId = SPR_owchar_police_0;
			object->w = 34;
			break;
		case 25:
			object->spriteId = SPR_owchar_policecap;
			break;
		case 26:
			object->spriteId = SPR_owchar_police_1;
			break;
		case 27:
			object->spriteId = SPR_owchar_dia;
			if (profile.flags[FLAG_ALONE_PLOT] >= 20) {
				object->spriteId = SPR_owchar_collapse_dia;
				object->spriteFrame = 1;
			}
			break;
		case 28:
			object->spriteId = SPR_owchar_police_0;
			break;
		case 29:
			object->spriteId = SPR_owchar_npc_5;
			break;
		case 30:
			object->spriteId = SPR_owchar_npc_7;
			break;
		case 31:
			object->spriteId = SPR_owchar_nurse;
			break;
		case 32:
			object->spriteId = SPR_owchar_river;
			break;
		case 33:
			object->spriteId = SPR_owchar_farmer_1;
			break;
		case 34:
			object->spriteId = SPR_owchar_npc_4;
			break;
		case 35:
			object->spriteId = SPR_owchar_vandal_knife;
			break;
		case 36:
			object->spriteId = SPR_owchar_ayaka;
			break;
		case 37:
			object->spriteId = SPR_owchar_npc_2;
			break;
		case 38:
			object->spriteId = SPR_owchar_npc_3;
			break;
		case 39:
			object->spriteId = SPR_owchar_kelly;
			break;
		case 40:
			object->spriteId = SPR_owchar_neveah;
			break;
		case 41:
			object->spriteId = SPR_owchar_pirate;
			break;
		case 42:
			object->spriteId = SPR_owchar_tom;
			break;
		case 43:
			object->spriteId = SPR_owchar_brook;
			break;
		case 44:
			object->spriteId = SPR_owchar_cindy;
			break;
		case 45:
			object->spriteId = SPR_owchar_npc_13;
			break;
		case 46:
			object->spriteId = SPR_owchar_sanji;
			break;
		case 47:
			object->spriteId = SPR_owchar_npc_15;
			break;
		case 48:
			object->spriteId = SPR_owchar_npc_16;
			break;
		case 49:
			object->spriteId = SPR_owchar_npc_11;
			break;
		case 50:
			object->spriteId = SPR_owchar_npc_12;
			break;
		case 51:
			object->spriteId = SPR_owchar_npc_9;
			break;
		case 52:
			object->spriteId = SPR_owchar_npc_19;
			break;
		case 53:
			object->spriteId = SPR_owchar_npc_11;
			break;
		case 54:
			object->spriteId = SPR_owchar_npc_18;
			break;
		case 55:
			object->spriteId = SPR_owchar_ninja;
			break;
		case 56:
			object->spriteId = SPR_owchar_volcano;
			break;
		case 57:
			object->spriteId = SPR_owchar_pirate_1;
			break;
		case 58:
			object->spriteId = SPR_owchar_collapse_perry;
			object->spriteFrame = 1;
			break;
		case 59:
			object->spriteId = SPR_owchar_luna;
			break;
		case 60:
			object->spriteId = SPR_owchar_don;
			break;
		case 61:
			object->spriteId = SPR_owchar_nate;
			break;
		case 62:
			object->spriteId = SPR_owchar_piratecap;
			break;
		case 63:
			object->spriteId = SPR_owchar_pirate;
			break;
		case 64:
			object->spriteId = SPR_owchar_pirate_1;
			break;
		case 65:
			object->spriteId = SPR_owchar_noah;
			break;
		case 66:
			object->spriteId = SPR_owchar_emmet;
			break;
		case 67:
			object->spriteId = SPR_owchar_sally;
			break;
		case 68:
			object->spriteId = SPR_owchar_npc_14;
			break;
		case 69:
			object->spriteId = SPR_owchar_brian;
			break;
		case 70:
			object->spriteId = SPR_owchar_ozone;
			break;
		case 71:
			object->spriteId = SPR_owchar_adios;
			break;
		case 72:
			object->spriteId = SPR_owchar_bulldog;
			break;
		case 73:
			object->spriteId = SPR_owchar_bpolice_0;
			break;
		case 74:
			object->spriteId = SPR_owchar_bpolice_1;
			break;
		case 75:
			object->spriteId = SPR_owchar_bpolice_0;
			break;
		case 76:
			object->spriteId = SPR_owchar_npc_21;
			break;
		case 77:
			object->spriteId = SPR_owchar_npc_20;
			break;
		case 78:
			object->spriteId = SPR_owchar_npc_7;
			break;
		case 79:
			object->spriteId = SPR_owchar_nurse;
			break;
		case 80:
			object->spriteId = SPR_owchar_npc_5;
			break;
		case 81:
			object->spriteId = SPR_owchar_npc_11;
			break;
		case 82:
			object->spriteId = SPR_owchar_npc_12;
			break;
		case 83:
			object->spriteId = SPR_owchar_lulu_omega;
			break;
		case 84:
			object->spriteId = SPR_owchar_agent;
			break;
		case 85:
			object->spriteId = SPR_owchar_npc_23;
			break;
		case 86:
			object->spriteId = SPR_owchar_nurse;
			break;
		case 87:
			object->spriteId = SPR_owchar_hobo;
			break;
		case 88:
			object->spriteId = SPR_owchar_collapse_lulu_omega;
			object->spriteFrame = 1;
			break;
		case 89:
			object->spriteId = SPR_misc_npc_22_phone;
			break;
		case 90:
			object->spriteId = SPR_owchar_npc_12;
			break;
		case 91:
			object->spriteId = SPR_owchar_policecap;
			break;
		case 92:
			object->spriteId = SPR_owchar_npc_10;
			break;
		case 93:
			object->spriteId = SPR_owchar_npc_27;
			break;
		case 94:
			object->spriteId = SPR_owchar_hobo_1;
			break;
		case 95:
			object->spriteId = SPR_owchar_npc_11;
			break;
		case 96:
			object->spriteId = SPR_owchar_npc_12;
			break;
		case 97:
			object->spriteId = SPR_owchar_viku;
			break;
		case 98:
			object->spriteId = SPR_owchar_npc_26;
			break;
		case 99:
			object->spriteId = SPR_owchar_npc_25;
			break;
		case 100:
			object->spriteId = SPR_owchar_emmet;
			break;
		case 101:
			object->spriteId = SPR_owchar_whitelight_0;
			break;
		case 102:
			object->spriteId = SPR_owchar_whitelight_1;
			break;
		case 103:
			object->spriteId = SPR_owchar_timon;
			break;
		case 104:
			object->spriteId = SPR_owchar_rob;
			break;
		case 105:
			object->spriteId = SPR_owchar_mani;
			break;
		case 106:
			object->spriteId = SPR_owchar_timon;
			break;
		case 107:
			if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] >= 8 && overworld.areaId != 194) {
				object->spriteId = SPR_misc_sally_serious;
				object->spriteFrame = 1;
				break;
			}
			object->spriteId = SPR_owchar_sally;
			break;
		case 108:
			object->spriteId = SPR_owchar_npc_31;
			break;
		case 109:
			object->spriteId = SPR_owchar_npc_32;
			break;
		case 110:
			object->spriteId = SPR_misc_npc_33_arms;
			break;
		case 111:
			object->spriteId = SPR_owchar_npc_34;
			break;
		case 112:
			object->spriteId = SPR_owchar_npc_35;
			break;
		case 113:
			object->spriteId = SPR_owchar_npc_36;
			break;
		case 114:
			object->spriteId = SPR_owchar_npc_37;
			break;
		case 115:
			object->spriteId = SPR_owchar_npc_38;
			break;
		case 116:
			object->spriteId = SPR_owchar_npc_28;
			break;
		case 117:
			object->spriteId = SPR_owchar_npc_39;
			break;
		case 118:
			object->spriteId = SPR_misc_redgreenbatterlookingidiot;
			object->spriteFrameSpeed = 0.125;
			break;
		case 119:
			object->spriteId = SPR_owchar_npc_30;
			break;
		case 120:
			object->spriteId = SPR_owchar_npc_40;
			break;
		case 121:
			object->spriteId = SPR_owchar_kyle;
			break;
		case 122:
			object->spriteId = SPR_owchar_tia;
			break;
		case 123:
			object->spriteId = SPR_owchar_dirk;
			break;
		case 124:
			object->spriteId = SPR_misc_pbsuperhero;
			object->spriteFrameSpeed = 0.125;
			break;
		case 125:
			object->spriteId = SPR_owchar_kara;
			break;
		case 126:
			object->spriteId = SPR_owchar_agent;
			break;
		case 127:
			object->spriteId = SPR_owchar_flora;
			break;
		case 128:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
				object->spriteId = SPR_owchar_collapse_amp;
				object->spriteFrame = 1;
			}
			else if (profile.flags[FLAG_PLOT] >= 250)
				object->spriteId = SPR_misc_amp_sit;
			else
				object->spriteId = SPR_owchar_amp;
			break;
		case 129:
			object->spriteId = SPR_owchar_gpolice_0;
			break;
		case 130:
			if (profile.flags[FLAG_METRO_LOCATION] == 0)
				object->spriteId = SPR_owchar_police_0;
			else if (profile.flags[FLAG_METRO_LOCATION] == 1)
				object->spriteId = SPR_owchar_police_1;
			else if (profile.flags[FLAG_METRO_LOCATION] == 2)
				object->spriteId = SPR_owchar_bpolice_1;
			else
				object->spriteId = SPR_owchar_gpolice_0;
			break;
		case 131:
			object->spriteId = SPR_owchar_lulu_god;
			break;
		case 132:
			object->spriteId = SPR_owchar_collapse_panda;
			object->spriteFrame = 1;
			break;
		case 133:
			if (profile.flags[FLAG_ALONE_PLOT] >= 100) {
				object->spriteId = SPR_owchar_collapse_maline;
				object->spriteFrame = 1;
				break;
			}
			object->spriteId = SPR_owchar_maline;
			break;
		case 134:
			if (profile.flags[FLAG_ALONE_PLOT] >= 100) {
				object->spriteId = SPR_owchar_collapse_cory;
				object->spriteFrame = 1;
				break;
			}
			object->spriteId = SPR_owchar_cory;
			break;
		
		case 1000:
			object->spriteId = SPR_owchar_hobo;
			break;
		case 1001:
			object->spriteId = SPR_owchar_hobo_1;
			break;
		case 1002:
			object->spriteId = SPR_owchar_police_0;
			break;
		case 1003:
			object->spriteId = SPR_owchar_police_1;
			break;
		case 1004:
			object->spriteId = SPR_owchar_npc_11;
			break;
		case 1005:
			object->spriteId = SPR_owchar_npc_12;
			break;
		case 1006:
			object->spriteId = SPR_owchar_agent;
			break;
		case 1007:
			object->spriteId = SPR_owchar_agent;
			break;
		case 1008:
			object->spriteId = SPR_owchar_bpolice_0;
			break;
		case 1009:
			object->spriteId = SPR_owchar_bpolice_1;
			break;
		case 1010:
			object->spriteId = SPR_owchar_ninja;
			break;
		
		case 10000:
			object->spriteId = SPR_misc_savegem;
			object->spriteFrameSpeed = 0.125;
			break;
		case 10001:
			object->spriteId = SPR_misc_mansionsofa;
			object->w = 32;
			object->h = 32;
			break;
		case 10002:
			object->spriteId = SPR_misc_key;
			OverworldObject_SetColor(objectId, 255, 223, 0);
			break;
		case 10003:
			object->spriteId = SPR_misc_rubycomputer;
			break;
		case 10004:
			object->spriteId = SPR_misc_labcoat;
			break;
		case 10005:
			object->spriteId = -1;
			break;
		case 10006:
			object->spriteId = SPR_misc_tomatosoup;
			object->w = 10;
			object->h = 6;
			break;
		case 10007:
			object->spriteId = -1;
			break;
		case 10008:
			object->spriteId = SPR_misc_rubycomputer;
			break;
		case 10009:
			object->spriteId = SPR_misc_kevincomputer;
			object->spriteFrameSpeed = 0.0625;
			break;
		case 10010:
			object->spriteId = SPR_misc_perrypizza;
			break;
		case 10011:
			object->spriteId = SPR_misc_flashlight;
			object->w = 10;
			object->h = 32;
			object->collisionOffsetY = 8;
			break;
		case 10012:
			object->spriteId = -1;
			break;
		case 10013:
			object->spriteId = SPR_misc_flowergame_button;
			object->w = 2;
			object->h = 4;
			object->ghost = true;
			break;
		case 10014:
			object->spriteId = SPR_misc_flowergame;
			object->spriteFrame = 9;
			object->w = 8;
			object->h = 4;
			object->vars[1].i = 1;
			object->ghost = true;
			break;
		case 10015:
			object->spriteId = -1;
			break;
		case 10016:
			object->spriteId = -1;
			break;
		case 10017:
			object->spriteId = -1;
			break;
		case 10018:
			object->spriteId = -1;
			break;
		case 10019:
			object->spriteId = SPR_misc_key;
			OverworldObject_SetColor(objectId, 207, 207, 207);
			break;
		case 10020:
			object->spriteId = SPR_misc_key;
			OverworldObject_SetColor(objectId, 63, 255, 255);
			break;
		case 10021:
			object->spriteId = SPR_owchar_waxknight;
			object->w = 32;
			break;
		case 10022:
			object->spriteId = SPR_misc_diarynote;
			object->w = 4;
			object->h = 4;
			object->ghost = true;
			break;
		case 10023:
			object->spriteId = SPR_misc_flowergame;
			object->spriteFrame = 5;
			object->w = 8;
			object->h = 4;
			break;
		case 10024:
			object->spriteId = SPR_misc_flowergame;
			object->spriteFrame = 6;
			object->w = 8;
			object->h = 4;
			break;
		case 10025:
			object->spriteId = SPR_misc_flowergame;
			object->spriteFrame = 7;
			object->w = 8;
			object->h = 4;
			break;
		case 10026:
			object->spriteId = SPR_misc_flowergame;
			object->spriteFrame = 8;
			object->w = 8;
			object->h = 4;
			break;
		case 10027:
			object->spriteId = SPR_misc_brickwall;
			object->w = 96;
			object->h = 176;
			object->collisionOffsetY = 176;
			break;
		case 10028:
			object->spriteId = -1;
			break;
		case 10029:
			object->spriteId = SPR_misc_computer;
			break;
		case 10030:
			object->spriteId = -1;
			break;
		case 10031:
			object->spriteId = SPR_misc_key;
			OverworldObject_SetColor(objectId, 255, 0, 255);
			break;
		case 10032:
			object->spriteId = SPR_misc_key;
			OverworldObject_SetColor(objectId, 0, 255, 255);
			break;
		case 10033:
			object->spriteId = SPR_misc_illusdoor;
			object->ghost = true;
			if ((profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] & 4) > 0) object->spriteFrame = 1;
			break;
		case 10034:
			object->spriteId = SPR_misc_bar_glass;
			object->ghost = true;
			break;
		case 10035:
			object->spriteId = -1;
			break;
		case 10036:
			object->spriteId = SPR_misc_computer_1;
			break;
		case 10037:
			object->spriteId = SPR_misc_ozonethrone;
			object->w = 34;
			object->h = 24;
			object->collisionOffsetY = 4;
			break;
		case 10038:
			object->spriteId = SPR_misc_computer;
			break;
		case 10039:
			object->spriteId = SPR_misc_healgeyser;
			object->spriteFrameSpeed = 0.125;
			break;
		case 10040:
			object->spriteId = SPR_misc_healcapsule;
			object->spriteFrame = 0;
			object->w = 6;
			object->h = 4;
			break;
		case 10041:
			object->spriteId = SPR_misc_healcapsule;
			object->spriteFrame = 1;
			object->w = 6;
			object->h = 4;
			break;
		case 10042:
			object->spriteId = SPR_misc_healcapsule;
			object->spriteFrame = 2;
			object->w = 6;
			object->h = 4;
			break;
		case 10043:
			object->spriteId = SPR_misc_briefcase;
			object->spriteFrame = 0;
			break;
		case 10044:
			object->spriteId = SPR_misc_key;
			OverworldObject_SetColor(objectId, 31, 31, 31);
			break;
		case 10045:
			object->spriteId = -1;
			break;
		case 10046:
			object->spriteId = SPR_misc_secretbosskey;
			object->w = 8;
			object->h = 4;
			object->z = -24;
			object->ghost = true;
			break;
		case 10047:
			object->spriteId = SPR_misc_secretbosskeylock;
			object->w = 8;
			object->h = 4;
			object->z = -16;
			object->ghost = true;
			break;
		case 10048:
			object->spriteId = SPR_misc_secretbossdoor;
			object->w = 48;
			object->h = 8;
			object->collisionOffsetY = -8;
			break;
		case 10049:
			object->spriteId = SPR_misc_aquatree;
			break;
		case 10050:
			object->spriteId = SPR_misc_policebarrier;
			object->w = 32;
			object->h = 8;
			object->collisionOffsetY = -8;
			break;
		case 10051:
			object->spriteId = SPR_misc_offserieso;
			object->spriteFrame = 1;
			break;
		case 10052:
			object->spriteId = -1;
			break;
		case 10053:
			object->spriteId = SPR_misc_dandelionneo;
			object->spriteFrameSpeed = 0.0625;
			object->w = 4;
			object->h = 4;
			break;
		case 10054:
			object->spriteId = -1;
			break;
		case 10055:
			object->spriteId = SPR_misc_rubycomputer;
			break;
		case 10056:
			object->spriteId = -1;
			break;
		case 10057:
			object->spriteId = SPR_misc_guide_arrow;
			object->w = 2;
			object->h = 2;
			object->ghost = true;
			object->collisionOffsetY = 3;
			break;
		case 10058:
			object->spriteId = SPR_misc_flowergame_button;
			object->ghost = true;
			break;
		case 10059:
			object->spriteId = SPR_misc_secretbosskey;
			object->w = 8;
			object->h = 4;
			object->ghost = true;
			break;
		case 10060:
			object->spriteId = SPR_misc_key;
			object->w = 8;
			object->h = 4;
			object->ghost = true;
			break;
		case 10061:
			object->spriteId = -1;
			break;
		case 10062:
			object->spriteId = SPR_misc_discotable;
			object->spriteFrameSpeed = 0.125;
			object->w = 41;
			object->h = 1;
			object->collisionOffsetY = -4;
			break;
		case 10063:
			object->spriteId = SPR_misc_turbospeaker;
			object->spriteFrameSpeed = 0.144;
			object->w = 40;
			object->h = 32;
			object->collisionOffsetY = -8;
			break;
		case 10064:
			object->spriteId = SPR_misc_janitorbucket;
			object->w = 10;
			object->h = 2;
			object->collisionOffsetY = -4;
			break;
		case 10065:
			object->spriteId = SPR_misc_secretbosskey;
			object->w = 8;
			object->h = 4;
			object->ghost = true;
			break;
		case 10066:
			object->spriteId = SPR_misc_amper_movebutton;
			object->collisionOffsetY = -8;
			break;
		case 10067:
			object->spriteId = -1;
			break;
		case 10068:
			object->spriteId = -1;
			object->w = 104;
			object->h = 32;
			break;
		case 10069:
			object->spriteId = SPR_misc_spyingtelescope;
			break;
		
		case 60000:
			object->spriteId = SPR_misc_gems;
			object->spriteFrame = 0;
			break;
		case 60001:
			object->spriteId = SPR_misc_gems;
			object->spriteFrame = 1;
			break;
		case 60002:
			object->spriteId = SPR_misc_gems;
			object->spriteFrame = 2;
			break;
		case 60003:
			object->spriteId = SPR_misc_gems;
			object->spriteFrame = 3;
			break;
		case 60004:
			object->spriteId = SPR_misc_gems;
			object->spriteFrame = 4;
			break;
		
		case 70000:
			object->spriteId = SPR_misc_voidportal;
			object->spriteFrameSpeed = 0.125;
			if (overworld.areaId == 202)
				OverworldObject_SetColor(objectId, 255, 0, 0);
			else if (overworld.areaId == 165)
				OverworldObject_SetColor(objectId, 63, 63, 63);
			else if (overworld.areaId == 110)
				OverworldObject_SetColor(objectId, 0, 0, 255);
			else if (overworld.areaId == 19)
				OverworldObject_SetColor(objectId, 0, 255, 255);
			else if (overworld.areaId == 5)
				OverworldObject_SetColor(objectId, 0, 255, 0);
			break;
		case 70001:
			object->spriteId = SPR_misc_hellgate;
			object->w = 48;
			object->h = 8;
			object->collisionOffsetY = -8;
			break;
		case 70002:
			object->spriteId = SPR_owchar_rubin;
			if (profile.flags[FLAG_PLOT] >= 100)
				OverworldObject_SetColor(objectId, 63, 63, 63);
			else
				OverworldObject_SetColor(objectId, 0, 0, 0);
			break;
		case 70003:
			object->spriteId = SPR_owchar_sapphireton_diana;
			OverworldObject_SetColor(objectId, 255, 0, 0);
			break;
		case 70004:
			object->spriteId = SPR_owchar_rubin;
			break;
		case 70005:
			object->spriteId = SPR_misc_timelineblock;
			object->w = 4;
			object->h = 4;
			break;
		case 70006:
			object->spriteId = SPR_misc_timelineslot;
			object->w = 4;
			object->h = 4;
			object->z = -24;
			object->collisionOffsetY = -2;
			break;
		case 70007:
			if (Random(1) < 0.5) {
				object->spriteId = SPR_body_unknown1;
			}
			else {
				object->spriteId = SPR_body_unknown2;
			}
			break;
		case 70008:
			object->spriteId = SPR_misc_sign_1;
			break;
		case 70009:
			object->spriteId = -1;
			break;
		case 70010:
			object->spriteId = SPR_misc_rubynobody_0;
			break;
		case 70011:
			object->spriteId = SPR_misc_illusmonolith;
			object->w = 34;
			object->h = 24;
			break;
		case 70012:
			object->spriteId = SPR_misc_hellgate_open;
			object->w = 48;
			object->h = 8;
			object->z = 32;
			object->collisionOffsetY = 24;
			break;
		case 70013:
			object->spriteId = SPR_misc_illusmemorygems;
			object->spriteFrame = 0;
			break;
		case 70014:
			object->spriteId = SPR_misc_illusmemorygems;
			object->spriteFrame = 1;
			break;
		case 70015:
			object->spriteId = SPR_misc_illusmemorygems;
			object->spriteFrame = 2;
			break;
		case 70016:
			object->spriteId = SPR_misc_illusmemorygems;
			object->spriteFrame = 3;
			break;
		case 70017:
			object->spriteId = -1;
			break;
	}
	
	OverworldObject_ChangeSpriteId(objectId, object->spriteId);
	OverworldObject_ChangeDirection(objectId, direction);
}

void Overworld_CreateNPC_Wandering(int objectId, int id, float x, float y, int direction) {
	Overworld_CreateNPC(objectId, id, x, y, direction);
	
	OverworldObject* object = &overworld.objects[objectId];
	
	object->vars[0].i = 1;
}

void Overworld_CreateEnemy(int objectId, int id, float x, float y) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->type = 3;
	object->id = id;
	object->state = OBJECT_STATE_IDLE;
	object->x = x;
	object->y = y;
	object->z = 0;
	object->w = 14;
	object->h = 8;
	object->collisionOffsetX = 0;
	object->collisionOffsetY = 0;
	object->direction = OBJECT_DIRECTION_DOWN;
	object->depth = -y;
	object->spriteId = SPR_owchar_ruby;
	object->spriteFrame = 0;
	object->spriteType = 0;
	object->spriteFrameFraction = 0;
	object->spriteFrameSpeed = 0;
	object->color[0] = 255; object->color[1] = 255; object->color[2] = 255;
	object->xPrev = x;
	object->yPrev = y;
	object->bodyId = -1;
	object->walkAnimationEnabled = true;
	object->ghost = false;
	object->climbSpriteId = -1;
	object->moveTarget.enabled = false;
	for (int i = 0; i < MOVETARGET_QUEUE_MAX; i++) object->moveTargetQueue[i].enabled = false;
	object->vars[0].i = ENEMY_STATE_IDLE;
	object->vars[1].i = 0;
	object->vars[2].f = x;
	object->vars[3].f = y;
	object->vars[4].i = 0;
	object->vars[5].i = 0;
	object->vars[6].i = 0;
	object->vars[7].i = 0;
	
	switch (id) {
		case 1: case 2:
			{
				int r = Random_IRange(0, 1);
				object->vars[1].i = r;
				if (r == 1)
					object->spriteId = SPR_owchar_hobo_1;
				else
					object->spriteId = SPR_owchar_hobo;
			}
			break;
		case 3: case 4:
			{
				int r = Random_IRange(0, 1);
				object->vars[1].i = r;
				if (r == 1)
					object->spriteId = SPR_owchar_navygang_1;
				else
					object->spriteId = SPR_owchar_navygang;
			}
			break;
		case 5:
			object->spriteId = SPR_owchar_sally;
			break;
		case 6: case 7: case 23:
			object->spriteId = SPR_owchar_leafcrew;
			break;
		case 8:
			object->spriteId = SPR_owchar_lisao;
			break;
		case 9: case 10: case 21:
			object->spriteId = SPR_owchar_lulu;
			break;
		case 11:
			{
				int r = Random_IRange(0, 1);
				object->vars[1].i = r;
				if (r == 1)
					object->spriteId = SPR_owchar_police_1;
				else
					object->spriteId = SPR_owchar_police_0;
			}
			break;
		case 12:
			object->spriteId = SPR_owchar_farmer;
			break;
		case 13: case 14:
			object->spriteId = SPR_owchar_knifethug;
			break;
		case 15: case 17: case 18: case 19:
			object->spriteId = SPR_owchar_vandal_knife;
			break;
		case 16:
			object->spriteId = SPR_owchar_vandal_flail;
			break;
		case 20:
			object->spriteId = SPR_owchar_jackie;
			break;
		case 22: case 70:
			object->spriteId = SPR_owchar_lulu_omega;
			break;
		case 24: case 25:
			object->spriteId = SPR_owchar_slime;
			break;
		case 26:
			object->spriteId = SPR_owchar_slimeboss;
			break;
		case 27:
			object->spriteId = SPR_owchar_bashura;
			break;
		case 28:
			object->spriteId = SPR_owchar_dia;
			break;
		case 29: case 30: case 31: case 33:
			object->spriteId = SPR_owchar_spider;
			break;
		case 32:
			object->spriteId = SPR_owchar_spiderboss;
			break;
		case 34: case 35:
			object->spriteId = SPR_owchar_sync;
			break;
		case 36:
			object->spriteId = SPR_owchar_josh;
			break;
		case 37: case 38: case 39:
			{
				int r = Random_IRange(0, 1);
				object->vars[1].i = r;
				if (r == 1)
					object->spriteId = SPR_owchar_pirate_1;
				else
					object->spriteId = SPR_owchar_pirate;
			}
			break;
		case 40:
			object->spriteId = SPR_owchar_piratecap;
			break;
		case 41:
			object->spriteId = SPR_owchar_sanji;
			break;
		case 42: case 43: case 44: case 68:
			object->spriteId = SPR_owchar_ninja;
			break;
		case 45:
			object->spriteId = SPR_owchar_agent;
			break;
		case 46:
			{
				int r = Random_IRange(0, 1);
				object->vars[1].i = r;
				if (r == 1)
					object->spriteId = SPR_owchar_bpolice_1;
				else
					object->spriteId = SPR_owchar_bpolice_0;
			}
			break;
		case 47:
			object->spriteId = SPR_owchar_gpolice_0;
			break;
		case 50:
			object->spriteId = SPR_owchar_waxknight;
			break;
		case 51:
			object->spriteId = SPR_owchar_flora;
			break;
		case 52:
			object->spriteId = SPR_body_deathknife;
			OverworldObject_EnableFighterSprite(objectId, 0, 47, FIGHTER_STATE_IDLE);
			break;
		case 53:
			object->spriteId = SPR_body_energyentity;
			OverworldObject_EnableFighterSprite(objectId, 0, 48, FIGHTER_STATE_IDLE);
			break;
		case 54:
			object->spriteId = SPR_body_deathweight;
			OverworldObject_EnableFighterSprite(objectId, 0, 49, FIGHTER_STATE_IDLE);
			break;
		case 55:
			object->spriteId = SPR_misc_hellgateboss;
			OverworldObject_EnableFighterSprite(objectId, 0, 50, FIGHTER_STATE_IDLE);
			break;
		case 56:
			object->spriteId = SPR_owchar_kelly;
			break;
		case 57:
			object->spriteId = SPR_owchar_tom;
			break;
		case 58:
			object->spriteId = SPR_owchar_cindy;
			break;
		case 59: case 60: case 61: case 62:
			object->spriteId = SPR_owchar_ozone;
			break;
		case 63:
			object->spriteId = SPR_owchar_luna;
			break;
		case 64:
			object->spriteId = SPR_owchar_volcano;
			break;
		case 65:
			object->spriteId = SPR_body_unknown1;
			OverworldObject_EnableFighterSprite(objectId, 0, 63, FIGHTER_STATE_IDLE);
			break;
		case 66:
			object->spriteId = SPR_body_unknown2;
			OverworldObject_EnableFighterSprite(objectId, 0, 64, FIGHTER_STATE_IDLE);
			break;
		case 67:
			object->spriteId = SPR_gui_status;
			break;
		case 69:
			object->spriteId = SPR_owchar_perry;
			break;
		case 71:
			object->spriteId = SPR_owchar_brian;
			break;
		case 72:
			object->spriteId = SPR_owchar_nekin;
			break;
		case 73:
			object->spriteId = SPR_owchar_adios;
			break;
		case 74:
			object->spriteId = SPR_owchar_builder;
			break;
		case 75:
			object->spriteId = SPR_owchar_kyle;
			break;
		case 76:
			object->spriteId = SPR_owchar_kara;
			break;
		case 77:
			object->spriteId = SPR_owchar_ayinoying;
			break;
		case 78:
			object->spriteId = SPR_owchar_aztec;
			break;
		case 79:
			object->spriteId = SPR_misc_gemini;
			break;
		case 80:
			object->spriteId = SPR_owchar_rob;
			break;
		case 81: case 82:
			{
				int r = Random_IRange(0, 1);
				object->vars[1].i = r;
				if (r == 1)
					object->spriteId = SPR_owchar_whitelight_1;
				else
					object->spriteId = SPR_owchar_whitelight_0;
			}
			break;
		case 83:
			object->spriteId = SPR_owchar_gregory;
			break;
		case 84:
			object->spriteId = SPR_owchar_sally_neo;
			break;
		case 85:
			object->spriteId = SPR_owchar_reti;
			break;
		case 86:
			object->spriteId = SPR_misc_pbsuperhero;
			break;
		case 87:
			object->spriteId = SPR_owchar_lulu_master;
			break;
		case 88:
		case 96:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 0;
			object->ghost = true;
			break;
		case 89:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 1;
			object->ghost = true;
			break;
		case 90:
		case 97:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 2;
			object->ghost = true;
			break;
		case 91:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 3;
			object->ghost = true;
			break;
		case 98:
		case 92:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 4;
			object->ghost = true;
			break;
		case 93:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 5;
			object->ghost = true;
			break;
		case 94:
		case 99:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 6;
			object->ghost = true;
			break;
		case 95:
			object->spriteId = SPR_misc_gemini;
			object->spriteFrame = 7;
			object->ghost = true;
			break;
	}
	
	OverworldObject_ChangeSpriteId(objectId, object->spriteId);
	OverworldObject_ChangeDirection(objectId, OBJECT_DIRECTION_DOWN);
}

void Overworld_CreateWall(int objectId, float x, float y, float w, float h) {
	OverworldObject* object = &overworld.objects[objectId];
	
	object->type = 4;
	object->id = 0;
	object->state = OBJECT_STATE_IDLE;
	object->x = x;
	object->y = y;
	object->z = 0;
	object->w = w;
	object->h = h;
	object->collisionOffsetX = 0;
	object->collisionOffsetY = 0;
	object->direction = OBJECT_DIRECTION_DOWN;
	object->depth = -y;
	object->spriteId = -1;
	object->spriteFrame = 0;
	object->spriteType = 0;
	object->spriteFrameFraction = 0;
	object->spriteFrameSpeed = 0;
	object->color[0] = 255; object->color[1] = 255; object->color[2] = 255;
	object->xPrev = x;
	object->yPrev = y;
	object->bodyId = -1;
	object->walkAnimationEnabled = true;
	object->ghost = false;
	object->climbSpriteId = -1;
	object->moveTarget.enabled = false;
	for (int i = 0; i < MOVETARGET_QUEUE_MAX; i++) object->moveTargetQueue[i].enabled = false;
	for (int i = 0; i < 8; i++) object->vars[i].i = 0;
	
	OverworldObject_ChangeDirection(objectId, OBJECT_DIRECTION_DOWN);
}

void Overworld_CreateArea(int id, int x1, int y1, int x2, int y2) {
	overworld.map.areas[id].x1 = x1;
	overworld.map.areas[id].y1 = y1;
	overworld.map.areas[id].x2 = x2;
	overworld.map.areas[id].y2 = y2;
}

void Overworld_CreateDoor(int id, int x1, int y1, int area1, int x2, int y2, int area2, int direction1, int direction2) {
	overworld.map.doors[id].enabled = true;
	overworld.map.doors[id].x1 = x1;
	overworld.map.doors[id].y1 = y1;
	overworld.map.doors[id].area1 = area1;
	overworld.map.doors[id].x2 = x2;
	overworld.map.doors[id].y2 = y2;
	overworld.map.doors[id].area2 = area2;
	overworld.map.doors[id].direction1 = direction1;
	overworld.map.doors[id].direction2 = direction2;
	overworld.map.doors[id].w1 = 16;
	overworld.map.doors[id].h1 = 16;
	overworld.map.doors[id].w2 = 16;
	overworld.map.doors[id].h2 = 16;
}

void Overworld_CreateDoor_Advanced(int id, int x1, int y1, int area1, int x2, int y2, int area2, int direction1, int direction2, int w1, int h1, int w2, int h2) {
	overworld.map.doors[id].enabled = true;
	overworld.map.doors[id].x1 = x1;
	overworld.map.doors[id].y1 = y1;
	overworld.map.doors[id].area1 = area1;
	overworld.map.doors[id].x2 = x2;
	overworld.map.doors[id].y2 = y2;
	overworld.map.doors[id].area2 = area2;
	overworld.map.doors[id].direction1 = direction1;
	overworld.map.doors[id].direction2 = direction2;
	overworld.map.doors[id].w1 = w1;
	overworld.map.doors[id].h1 = h1;
	overworld.map.doors[id].w2 = w2;
	overworld.map.doors[id].h2 = h2;
}

void Overworld_CreateTrigger(int id, float x1, float y1, float x2, float y2, int eventId) {
	overworld.map.triggers[id].eventId = eventId;
	overworld.map.triggers[id].x1 = x1;
	overworld.map.triggers[id].y1 = y1;
	overworld.map.triggers[id].x2 = x2;
	overworld.map.triggers[id].y2 = y2;
}

void Overworld_CreateDecoration(float x, float y, int tileId, int width, int height) {
	if (overworld.map.decorationCount >= DECORATION_COUNT_MAX) return;
	
	OverworldObject* object = &overworld.map.decorations[overworld.map.decorationCount++];
	
	object->type = 4;
	object->id = tileId;
	object->state = OBJECT_STATE_IDLE;
	object->timer = 0;
	object->x = x + 8;
	object->y = y + 16;
	object->w = 16;
	object->h = 16;
	object->collisionOffsetX = 0;
	object->collisionOffsetY = 0;
	object->direction = OBJECT_DIRECTION_DOWN;
	object->depth = -(y + 15);
	object->spriteId = -1;
	object->spriteFrame = 0;
	object->spriteType = 0;
	object->spriteFrameFraction = 0;
	object->spriteFrameSpeed = 0;
	object->color[0] = 255; object->color[1] = 255; object->color[2] = 255;
	object->xPrev = x;
	object->yPrev = y;
	object->bodyId = -1;
	object->walkAnimationEnabled = false;
	object->ghost = false;
	object->vars[0].i = height;
	object->vars[1].i = width;
}

void Overworld_DeleteDecoration(int id) {
	if (id >= overworld.map.decorationCount) return;
	
	overworld.map.decorationCount--;
	for (int i = id; i < overworld.map.decorationCount; i++) {
		overworld.map.decorations[i] = overworld.map.decorations[i + 1];
	}
}

void Overworld_CreateSpark(int id, float x, float y, int depth) {
	int sparkId = overworld.sparkCounter;
	
	overworld.sparks[sparkId].id = id;
	overworld.sparks[sparkId].x = x;
	overworld.sparks[sparkId].y = y;
	overworld.sparks[sparkId].depth = depth;
	overworld.sparks[sparkId].timer = 0;
	overworld.sparks[sparkId].xVel = 0;
	overworld.sparks[sparkId].yVel = 0;
	
	overworld.sparkCounter++;
	if (overworld.sparkCounter >= OBJECT_COUNT_MAX) overworld.sparkCounter = 0;
}



int Overworld_LoadMap(const char* path) {
	FILE* file = fopen(path, "rb");
	
	if (file == NULL) return 0;
	
	overworld.map.w = fgetc(file);
	overworld.map.w += fgetc(file) << 8;
	overworld.map.h = fgetc(file);
	overworld.map.h += fgetc(file) << 8;
	
	for (int j = 0; j < overworld.map.h; j++)
	for (int i = 0; i < overworld.map.w; i++) {
		overworld.map.tileMap[j][i] = fgetc(file);
		overworld.map.tileMap[j][i] += fgetc(file) << 8;
		
		if (overworld.map.tileMap[j][i] < 0) overworld.map.tileMap[j][i] = -overworld.map.tileMap[j][i];
	}
	
	int decorationCount;
	decorationCount = fgetc(file);
	decorationCount += fgetc(file) << 8;
	
	overworld.map.decorationCount = 0;
	
	for (int i = 0; i < decorationCount; i++) {
		int x, y, tileId, width, height;
		
		x = fgetc(file);
		x += fgetc(file) << 8;
		y = fgetc(file);
		y += fgetc(file) << 8;
		tileId = fgetc(file);
		tileId += fgetc(file) << 8;
		height = fgetc(file);
		height += fgetc(file) << 8;
		width = fgetc(file);
		width += fgetc(file) << 8;
		
		Overworld_CreateDecoration(x, y, tileId, width, height);
	}
	
	fclose(file);
	return 1;
}



void Player_UpdateObject() {
	OverworldObject* playerObject = &overworld.objects[0];
	
	playerObject->x = overworld.player.x;
	playerObject->y = overworld.player.y;
	playerObject->direction = overworld.player.direction;
	playerObject->depth = -overworld.player.y;
	
	for (int i = 1; i < 8; i++) {
		OverworldObject* object = &overworld.objects[i];
		
		object->x = overworld.caterpillar[i * 16].x;
		object->y = overworld.caterpillar[i * 16].y;
		object->direction = overworld.caterpillar[i * 16].direction;
		object->depth = -object->y;
	}
	
	overworld.camera.x = overworld.player.x;
	overworld.camera.y = overworld.player.y - 8;
	overworld.camera.zoom = 2;
}

void Player_TeleportTo(int x, int y) {
	overworld.player.x = x;
	overworld.player.y = y;
	
	for (int i = 0; i < 128; i++) {
		overworld.caterpillar[i].x = overworld.player.x;
		overworld.caterpillar[i].y = overworld.player.y;
		overworld.caterpillar[i].direction = overworld.player.direction;
	}
}

void Player_TeleportToTile(int tileX, int tileY) {
	overworld.player.x = tileX * 16 + 8;
	overworld.player.y = tileY * 16 + 8;
	
	for (int i = 0; i < 128; i++) {
		overworld.caterpillar[i].x = overworld.player.x;
		overworld.caterpillar[i].y = overworld.player.y;
		overworld.caterpillar[i].direction = overworld.player.direction;
	}
}

void Player_TakeDamage(int damage) {
	if (overworld.player.invincibleFrames > 0) return;
	
	Audio_PlaySound(SND_hit3);
	overworld.player.state = PLAYER_STATE_FLINCH;
	overworld.player.timer = 0;
	overworld.player.invincibleFrames = 40;
	for (int i = 0; i < 5; i++) {
		if (profile.party[i] < 0) break;
		partyMembers[profile.party[i]].hpDamage += damage;
	}
}

void Player_TryMove(float xMove, float yMove) {
	float xNew = overworld.player.x + xMove;
	float yNew = overworld.player.y + yMove;
	
	if (overworld.areaWrap) {
		int x1 = overworld.map.areas[overworld.areaId].x1 * 16;
		int y1 = overworld.map.areas[overworld.areaId].y1 * 16;
		int x2 = overworld.map.areas[overworld.areaId].x2 * 16 + 16;
		int y2 = overworld.map.areas[overworld.areaId].y2 * 16 + 16;
		int w = x2 - x1;
		int h = y2 - y1;
		
		if (xNew < x1) xNew += w;
		if (xNew >= x2) xNew -= w;
		if (yNew < y1) yNew += h;
		if (yNew >= y2) yNew -= h;
	}
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (overworld.objects[i].type == 0 || overworld.objects[i].type == 3) continue;
		if (overworld.objects[i].w == 0 || overworld.objects[i].h == 0 || overworld.objects[i].ghost) continue;
		
		OverworldObject* object = &overworld.objects[i];
		
		if (xNew + 7 > object->x - object->w / 2 + object->collisionOffsetX && xNew - 7 < object->x + object->w / 2 + object->collisionOffsetX && yNew + 8 > object->y - object->h + object->collisionOffsetY && yNew - 16 < object->y + object->collisionOffsetY) {
			Player_StopDashing();
			return;
		}
	}
	for (int i = 0; i < DECORATION_COUNT_MAX; i++) {
		OverworldObject* object = &overworld.map.decorations[i];
		
		if (xNew + 7 > object->x - object->w / 2 && xNew - 7 < object->x + object->w / 2 && yNew > object->y - object->h && yNew - 8 < object->y) {
			Player_StopDashing();
			return;
		}
	}
	
	if (overworld.state == OVERWORLD_STATE_IDLE) {
		for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
			if (overworld.map.triggers[i].eventId == 0) continue;
			
			float x1 = overworld.map.triggers[i].x1;
			float y1 = overworld.map.triggers[i].y1;
			float x2 = overworld.map.triggers[i].x2;
			float y2 = overworld.map.triggers[i].y2;
			
			if (xNew > x1 && xNew < x2 && yNew > y1 && yNew < y2) {
				if (eventSystem.queueSize == 0) {
					eventSystem.triggerId = i;
					Event_Trigger(overworld.map.triggers[i].eventId);
					overworld.player.dashing = false;
					overworld.player.dashChargeTimer = 0;
					Party_UpdateCaterpillar();
				}
				return;
			}
		}
		
		for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
			if (!overworld.map.doors[i].enabled) continue;
			
			int doorTouchedWhich = -1;
			int doorX1 = overworld.map.doors[i].x1;
			int doorY1 = overworld.map.doors[i].y1;
			int doorX2 = overworld.map.doors[i].x2;
			int doorY2 = overworld.map.doors[i].y2;
			int doorW1 = overworld.map.doors[i].w1;
			int doorH1 = overworld.map.doors[i].h1;
			int doorW2 = overworld.map.doors[i].w2;
			int doorH2 = overworld.map.doors[i].h2;
			
			if (xNew + 7 > doorX1 + 8 - doorW1 / 2 && xNew - 7 < doorX1 + 8 + doorW1 / 2 && yNew > doorY1 + 8 - doorH1 / 2 && yNew - 8 < doorY1 + 8 + doorH1 / 2)
				doorTouchedWhich = 0;
			else if (xNew + 7 > doorX2 + 8 - doorW2 / 2 && xNew - 7 < doorX2 + 8 + doorW2 / 2 && yNew > doorY2 + 8 - doorH2 / 2 && yNew - 8 < doorY2 + 8 + doorH2 / 2)
				doorTouchedWhich = 1;
			
			if (doorTouchedWhich >= 0) {
				int targetX, targetY, targetArea, direction;
				if (doorTouchedWhich == 0) {
					targetX = doorX2;
					targetY = doorY2;
					targetArea = overworld.map.doors[i].area2;
					direction = overworld.map.doors[i].direction1;
				}
				else {
					targetX = doorX1;
					targetY = doorY1;
					targetArea = overworld.map.doors[i].area1;
					direction = overworld.map.doors[i].direction2;
				}
				overworld.transition.id = 1;
				overworld.transition.timer = 0;
				overworld.transition.vars[0] = targetArea;
				switch (direction) {
					case OBJECT_DIRECTION_LEFT:
						overworld.transition.vars[1] = targetX - 8;
						overworld.transition.vars[2] = targetY + 8;
						break;
					case OBJECT_DIRECTION_RIGHT:
						overworld.transition.vars[1] = targetX + 24;
						overworld.transition.vars[2] = targetY + 8;
						break;
					case OBJECT_DIRECTION_UP:
						overworld.transition.vars[1] = targetX + 8;
						overworld.transition.vars[2] = targetY - 8;
						break;
					case OBJECT_DIRECTION_DOWN:
						overworld.transition.vars[1] = targetX + 8;
						overworld.transition.vars[2] = targetY + 24;
						break;
				}
				overworld.transition.vars[3] = -1;
				if (i == 0 && profile.flags[FLAG_PLOT] <= 2) {
					overworld.transition.id = 3;
				}
				
				if (i == 8 && doorTouchedWhich == 1) {
					profile.flags[FLAG_FOREST_FORK_PROGRESS] = 0;
				}
				else if (i == 9 && doorTouchedWhich == 1) {
					if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 1006) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 1005;
					}
				}
				else if (i == 10 && doorTouchedWhich == 1) {
					if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 104) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 103;
					}
				}
				else if (i == 9 && doorTouchedWhich == 0) {
					if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 1005) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 1006;
						
						overworld.transition.vars[1] = 2256;
						overworld.transition.vars[2] = 1288;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] == 101 || profile.flags[FLAG_FOREST_FORK_PROGRESS] == 102) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] < 1 || profile.flags[FLAG_FOREST_FORK_PROGRESS] == 1003) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] == 10) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 1000;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] == 11) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 100;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] > 11) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 0;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 0;
					}
				}
				else if (i == 10 && doorTouchedWhich == 0) {
					if (profile.flags[FLAG_FOREST_FORK_PROGRESS] == 1002 || profile.flags[FLAG_FOREST_FORK_PROGRESS] == 1004) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 103) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 104;
						
						overworld.transition.vars[1] = 4112;
						overworld.transition.vars[2] = 1416;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 10 && profile.flags[FLAG_FOREST_FORK_PROGRESS] < 17) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] < 10 || profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 20) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 10;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 0;
					}
				}
				else if (i == 11 && doorTouchedWhich == 0) {
					if (profile.flags[FLAG_FOREST_FORK_PROGRESS] == 1000 || profile.flags[FLAG_FOREST_FORK_PROGRESS] == 1001) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] == 100) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 20 && profile.flags[FLAG_FOREST_FORK_PROGRESS] < 21) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS]++;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] < 20) {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 20;
						
						overworld.transition.vars[1] = 3040;
						overworld.transition.vars[2] = 1912;
					}
					else {
						profile.flags[FLAG_FOREST_FORK_PROGRESS] = 0;
					}
				}
				
				if ((i == 7 || i == 202) && doorTouchedWhich == 0) {
					overworld.transition.vars[3] = SPR_tileset_day_forest;
				}
				if (i == 55 && doorTouchedWhich == 0) {
					overworld.transition.vars[3] = SPR_tileset_day_autumn;
				}
				if ((i == 7 || i == 55 || i == 202) && doorTouchedWhich == 1) {
					overworld.transition.vars[3] = SPR_tileset_day;
				}
				
				if (profile.flags[FLAG_PLOT] >= 57 && profile.flags[FLAG_PLOT] <= 71) {
					if (targetArea == 6)
						overworld.transition.vars[3] = SPR_tileset_night;
					else
						overworld.transition.vars[3] = SPR_tileset_day;
				}
				if (profile.flags[FLAG_PLOT] >= 112 && profile.flags[FLAG_PLOT] <= 121) {
					if (targetArea == 80)
						overworld.transition.vars[3] = SPR_tileset_night;
					else
						overworld.transition.vars[3] = SPR_tileset_day;
				}
				
				if (i == 43 && profile.flags[FLAG_FUN] >= 140 && profile.flags[FLAG_FUN] < 150 && profile.flags[FLAG_PLOT] < 50) {
					profile.flags[FLAG_FUN_RIVERGREEN_MYSTERY_ROOM] = 1;
				}
				
				overworld.player.dashing = false;
				Party_UpdateCaterpillar();
				overworld.state = OVERWORLD_STATE_TRANSITION;
				return;
			}
		}
	}
	
	for (int j = overworld.player.y / 16 - 2; j <= overworld.player.y / 16 + 2; j++)
	for (int i = overworld.player.x / 16 - 2; i <= overworld.player.x / 16 + 2; i++) {
		if (i < 0 || i >= overworld.map.w || j < 0 || j >= overworld.map.h) {
			float tileX = i * 16;
			float tileY = j * 16;
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
			continue;
		}
		
		int data = overworld.map.tileData[overworld.map.tileMap[j][i]];
		float tileX = i * 16;
		float tileY = j * 16;
		if (overworld.areaWrap) {
			int x1 = overworld.map.areas[overworld.areaId].x1;
			int y1 = overworld.map.areas[overworld.areaId].y1;
			int x2 = overworld.map.areas[overworld.areaId].x2;
			int y2 = overworld.map.areas[overworld.areaId].y2;
			int w = x2 - x1 + 1;
			int h = y2 - y1 + 1;
			int i2 = i;
			int j2 = j;
			
			if (i2 < x1) i2 = i + w;
			if (i2 > x2) i2 = i - w;
			if (j2 < y1) j2 = j + h;
			if (j2 > y2) j2 = j - h;
			
			data = overworld.map.tileData[overworld.map.tileMap[j2][i2]];
			tileX = i2 * 16;
			tileY = j2 * 16;
		}
		
		if (data == 1 || (data >= 60 && data < 100)) {
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
		}
		if (data == 2 || data == 6 || data == 7) {
			if (overworld.player.y > tileY && overworld.player.y - 8 < tileY + 16)
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY-16 && yNew - 8 < tileY-16 + 16) {
				Player_StopDashing();
				return;
			}
			if (overworld.player.y > tileY-16 && overworld.player.y - 8 < tileY-16 + 16)
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
		}
		if (data == 3 || data == 8 || data == 9) {
			if (overworld.player.y > tileY && overworld.player.y - 8 < tileY + 16)
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY+16 && yNew - 8 < tileY+16 + 16) {
				Player_StopDashing();
				return;
			}
			if (overworld.player.y > tileY+16 && overworld.player.y - 8 < tileY+16 + 16)
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
		}
		if (data == 4 || data == 6 || data == 8) {
			if (overworld.player.x + 7 > tileX && overworld.player.x - 7 < tileX + 16)
			if (xNew + 7 > tileX-16 && xNew - 7 < tileX-16 + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
			if (overworld.player.x + 7 > tileX-16 && overworld.player.x - 7 < tileX-16 + 16)
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
		}
		if (data == 5 || data == 7 || data == 9) {
			if (overworld.player.x + 7 > tileX && overworld.player.x - 7 < tileX + 16)
			if (xNew + 7 > tileX+16 && xNew - 7 < tileX+16 + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
			if (overworld.player.x + 7 > tileX+16 && overworld.player.x - 7 < tileX+16 + 16)
			if (xNew + 7 > tileX && xNew - 7 < tileX + 16 && yNew > tileY && yNew - 8 < tileY + 16) {
				Player_StopDashing();
				return;
			}
		}
		
		if (data >= 100 && data <= 139) {
			if (xNew > tileX && xNew < tileX + 16 && yNew > tileY && yNew < tileY + 16) {
				overworld.player.dashing = false;
				Party_UpdateCaterpillar();
				
				int direction = (data / 10) % 10;
				switch (direction) {
					case 0: direction = OBJECT_DIRECTION_RIGHT; break;
					case 1: direction = OBJECT_DIRECTION_UP; break;
					case 2: direction = OBJECT_DIRECTION_DOWN; break;
					case 3: direction = OBJECT_DIRECTION_LEFT; break;
				}
				int distance = 64 + ((data % 10) - 1) * 80;
				int newX = tileX + 8 - distance * (direction == OBJECT_DIRECTION_LEFT) + distance * (direction == OBJECT_DIRECTION_RIGHT);
				int newY = tileY + 8 - distance * (direction == OBJECT_DIRECTION_UP) + distance * (direction == OBJECT_DIRECTION_DOWN);
				int newTile = overworld.map.tileMap[newY / 16][newX / 16];
				int newData = overworld.map.tileData[newTile];
				bool fail = false;
				
				Event_Trigger(-1);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_EVENT);
				Event_Queue_Camera_TogglePlayerFollow(true);
				Event_Queue_Player_SetPositionSync(true);
				Event_Queue_Object_WalkTo(0, tileX + 8, tileY + 8, 2, direction);
				Event_Queue_WaitFrames(15);
				Event_Queue_PlaySound(SND_gunfire);
				Event_Queue_PlaySound(SND_swing);
				Event_Queue_Object_JumpTo(0, newX, newY, -1, 64, 28);
				
				if (newData == 1) {
					Event_Queue_PlaySound(SND_dodge);
					fail = true;
				}
				else if ((newTile == 4063 && overworld.objects[10].spriteFrame == 1) || (newTile == 4064 && overworld.objects[10].spriteFrame == 0)) {
					Event_Queue_PlaySound(SND_reset);
					fail = true;
				}
				
				if (fail) {
					Event_Queue_Overworld_FadeIn(30, 0, 0, 0);
					if (newX >= 1360) {
						profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_OOB_COUNT]++;
					}
					
					if (profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_OOB_COUNT] == 3) {
						Event_Queue_GotoArea(232, 184, 14952, -1);
						profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_OOB_COUNT]++;
					}
					else if (overworld.objects[10].spriteFrame == 0) {
						Event_Queue_Object_TeleportTo(0, 744, 12776);
						Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
					}
					else {
						Event_Queue_Object_TeleportTo(0, 1064, 13864);
						Event_Queue_Overworld_FadeOut(30, 0, 0, 0);
					}
				}
				
				Event_Queue_Regroup(4);
				Event_Queue_Overworld_SetState(OVERWORLD_STATE_IDLE);
				return;
			}
		}
	}
	
	overworld.player.x = xNew;
	overworld.player.y = yNew;
}

void Player_StopDashing() {
	if (!overworld.player.dashing) return;
	Audio_PlaySound(SND_hit1);
	overworld.player.dashing = false;
	overworld.player.dashChargeTimer = 0;
	Party_UpdateCaterpillar();
}
