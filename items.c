#include "generic.h"
#include "items.h"
#include "battlesystem.h"
#include "action.h"
#include "sprites.h"
#include "party.h"
#include "profile.h"
#include "audio.h"
#include "dialog.h"

Item itemData[OBJECT_COUNT_MAX];

void LoadItemData() {
	Item* item;
	
	item = &itemData[0];
	SetString(item->name, "null");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[1];
	SetString(item->name, "Bread");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 30;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[2];
	SetString(item->name, "Pizza Slice");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 70;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[3];
	SetString(item->name, "Heal Capsule");
	item->type = 1;
	item->actionId = 200;
	item->vars[0].i = 15;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[4];
	SetString(item->name, "Bomb");
	item->type = 2;
	item->actionId = 201;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[5];
	SetString(item->name, "Cheese");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 20;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[6];
	SetString(item->name, "Cheese Sandwich");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 50;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[7];
	SetString(item->name, "Tomato Soup");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 85;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[8];
	SetString(item->name, "Perry's Pizza");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 110;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[9];
	SetString(item->name, "Cup of Water");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 2;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[10];
	SetString(item->name, "Orange Juice");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 20;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[11];
	SetString(item->name, "Black Tea");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 30;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[12];
	SetString(item->name, "Green Tea");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 30;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[13];
	SetString(item->name, "Hamburger");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 80;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[14];
	SetString(item->name, "Coffee");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 30;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[15];
	SetString(item->name, "Milkshake");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 60;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[16];
	SetString(item->name, "Semi-Nuke");
	item->type = 2;
	item->actionId = 202;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[17];
	SetString(item->name, "Aqua Berry");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 35;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[18];
	SetString(item->name, "Chicken Wing");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 70;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[19];
	SetString(item->name, "Spaghetti");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 80;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[20];
	SetString(item->name, "Healthy Salad");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 90;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[21];
	SetString(item->name, "Energy Meal");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 110;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[22];
	SetString(item->name, "Onyx Meal");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 300;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[23];
	SetString(item->name, "Heal B Capsule");
	item->type = 1;
	item->actionId = 203;
	item->vars[0].i = 30;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[24];
	SetString(item->name, "Heal G Capsule");
	item->type = 1;
	item->actionId = 204;
	item->vars[0].i = 50;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[25];
	SetString(item->name, "Energy Drink");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 90;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[26];
	SetString(item->name, "Power Capsule");
	item->type = 2;
	item->actionId = 205;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[27];
	SetString(item->name, "Dandelion Neo");
	item->type = 2;
	item->actionId = 206;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[28];
	SetString(item->name, "Medkit");
	item->type = 1;
	item->actionId = 207;
	item->vars[0].i = 100;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[29];
	SetString(item->name, "Mana Capsule");
	item->type = 1;
	item->actionId = 208;
	item->vars[0].i = 15;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[30];
	SetString(item->name, "Bomb B");
	item->type = 2;
	item->actionId = 209;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[31];
	SetString(item->name, "Bomb G");
	item->type = 2;
	item->actionId = 210;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[32];
	SetString(item->name, "Superburger");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 95;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[33];
	SetString(item->name, "Multi-Fresh");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 70;
	item->vars[1].i = 1;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[34];
	SetString(item->name, "Pizza Slice DX");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 80;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[35];
	SetString(item->name, "Gem Sandwich");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 70;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[36];
	SetString(item->name, "Bread DX");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 40;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	item = &itemData[37];
	SetString(item->name, "Cheese DX");
	item->type = 1;
	item->actionId = 0;
	item->vars[0].i = 35;
	item->vars[1].i = 0;
	item->vars[2].i = 1;
	item->vars[3].i = 0;
	
	
	
	item = &itemData[160];
	SetString(item->name, "Magical Gem");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[161];
	SetString(item->name, "Perry's Present");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[162];
	SetString(item->name, "Silver Key");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[163];
	SetString(item->name, "Golden Key");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[164];
	SetString(item->name, "Diamond Key");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[165];
	SetString(item->name, "Flashlight");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[166];
	SetString(item->name, "RC Membership Card");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[167];
	SetString(item->name, "RC VIP Card");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[168];
	SetString(item->name, "Magenta Key");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[169];
	SetString(item->name, "Cyan Key");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[170];
	SetString(item->name, "OFF Series Omega");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[171];
	SetString(item->name, "Mystery Key");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[172];
	SetString(item->name, "Mystery Card");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[173];
	SetString(item->name, "Ruby's Toolkit");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[174];
	SetString(item->name, "Whitelight Pass");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[175];
	SetString(item->name, "Whitelight Pass 2");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[176];
	SetString(item->name, "BM Entry Permit");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[177];
	SetString(item->name, "Forestpath Guide");
	item->type = 3;
	item->actionId = 0;
	item->vars[0].i = 120;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	
	
	item = &itemData[250];
	SetString(item->name, "Ruby of Stars");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[251];
	SetString(item->name, "Emerald of Earth");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[252];
	SetString(item->name, "Diamond of Sky");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[253];
	SetString(item->name, "Sapphire of Ocean");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
	
	item = &itemData[254];
	SetString(item->name, "Onyx of Death");
	item->type = 0;
	item->actionId = 0;
	item->vars[0].i = 0;
	item->vars[1].i = 0;
	item->vars[2].i = 0;
	item->vars[3].i = 0;
}



void Item_UseInOverworld(int inventoryId, int partyId) {
	Item* item = &itemData[profile.itemInventory[inventoryId]];
	PartyMember* partyMember = &partyMembers[partyId];
	
	switch (item->type) {
		case 1: {
			if (item->vars[2].i == 1) {
				partyMember->hpDamage -= (item->vars[0].i * partyMember->base.hpMax + 99) / 100;
			}
			else {
				partyMember->hpDamage -= item->vars[0].i;
			}
			
			if (partyMember->hpDamage < 0) partyMember->hpDamage = 0;
			
			if (item->vars[1].i == 1) {
				Audio_PlaySound(SND_mana);
				partyMember->tiredness -= partyMember->tiredThreshold;
				if (partyMember->tiredness < 0) partyMember->tiredness = 0;
				
				if (partyMember->tiredness >= partyMember->tiredThreshold * 2) {
					partyMember->tiredness = partyMember->tiredThreshold * 2;
					partyMember->tiredLevel = 2;
				}
				else if (partyMember->tiredness >= partyMember->tiredThreshold) {
					partyMember->tiredLevel = 1;
				}
				else {
					partyMember->tiredLevel = 0;
				}
			}
			else {
				Audio_PlaySound(SND_heal);
			}
			
			Profile_ItemRemove(inventoryId);
		} break;
	}
}
