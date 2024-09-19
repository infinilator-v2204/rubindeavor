#include "generic.h"
#include "dialog.h"
#include "overworld.h"
#include "battlesystem.h"
#include "action.h"
#include "armor.h"
#include "party.h"
#include "items.h"
#include "sprites.h"
#include "audio.h"
#include "profile.h"
#include "event.h"

DialogSystem dialogSystem;

unsigned char dialogData[0x40000];
int dialogPointerData[6000];



void LoadDialogData() {
	dialogSystem.state = DIALOG_STATE_IDLE;
	dialogSystem.textLength = 0;
	dialogSystem.ptr = 0;
	dialogSystem.timer = 0;
	dialogSystem.time = -1;
	
	SetDialogString(0, "\x10Ruby\x10Hello, world!\x01.\x03\x10.\x03\x10.\x03\x10\x10\x10This is just a test.\x01.");
	SetDialogString(1, "Hello again!\x01 What's up!\x01\nOkay.\x01");
	SetDialogString(2, "You have Lulu's armor!\x01");
	SetDialogString(3, "\x10Lulu\x10""Are you a police officer?\x11Yes\nNo\x11");
	SetDialogString(4, "\x10Lulu\x10No? What a shame!\x01");
	SetDialogString(5, "\x10Lulu\x10Liar!\x01");
	SetDialogString(6, "\x10Lulu\x10Wow, you really are a cop!\x01\nI'm impressed.\x01");
	
	SetDialogString(10, "           Welcome to Gemia.\x01");
	SetDialogString(11, "A highly advanced country full of\nmyths and legends.\x01");
	SetDialogString(12, "The Ancient Gems are one of those.\nThey are rare and supposedly contain\nenormous power.\x01");
	SetDialogString(13, "They do indeed exist, but even with\nadvanced technology, nobody was able\nto use their power properly.\x01");
	SetDialogString(14, "Eventually, somebody has to discover\ntheir mystery...\x01");
	SetDialogString(15, "\x03\x20Somewhere in Sapphireland of Gemia...\x01");
	SetDialogString(16, "\x03\x20Rivergreen Town, Ruby's House\x01");
	SetDialogString(17, "\x03\x20This is you, Ruby. A smart girl,\nwith a brilliant mind.\x01");
	SetDialogString(18, "You will be the one to uncover\nthe mystery of the Ancient Gems.\x01");
	SetDialogString(19, "You know where 5 of them are.\x01");
	SetDialogString(20, "The sooner you set off on an\nendeavor, the higher chances of\nsuccess you'll have.\x01");
	SetDialogString(21, ".\x03\x20.\x03\x20.\x03\x20\x01");
	SetDialogString(22, "Ruby.\x03\x40 It's time for you to wake up.\x01");
	
	SetDialogString(30, "\x10""Ruby\x10" "(Well...\x03\x10 the time has come.\x01\nTime for an adventure!)\x01");
	SetDialogString(31, "\x10""Ruby\x10" "(I've been preparing for this day\nfor a while, and I think I'm all\nset now.\x01\nAll I need to do now is grab the\nlabcoat from the laboratory.)\x01");
	SetDialogString(32, "\x10""Ruby\x10" "(My computer. Pretty good I'd say.\x01\nI use Arch by the way. Much better\nthan Glasspane, that's a fact!)\x01");
	SetDialogString(33, "\x10""Ruby\x10" "(A labcoat!\x01 ...nope, this isn't it.\x01\nI need the labcoat I've prepared for\nthis day.)\x01");
	SetDialogString(34, "\x10""Ruby\x10" "(Now I'm all set!\x01 I've got\nthe magical gem and the magical\nlabcoat.\x01 Let's begin the quest\nfor the Ancient Gems, shall we?)\x01");
	SetDialogString(35, "\x10""Ruby\x10" "(I need to get the labcoat first.)\x01");
	SetDialogString(36, "A regular labcoat.\x01");
	SetDialogString(37, "\x10""Ruby\x10" "(I can run away by pressing C or\nEnter and selecting \"Flee\".)\x01");
	SetDialogString(38, "\x10""Ruby\x10" "(I can defend myself by pressing Z\nduring the enemy's attack.\x01 If timed\ncorrectly, the damage I take will\nbe halved.)\x01");
	
	SetDialogString(40, "\x10""River\x10" "Hey, you!\x01");
	SetDialogString(41, "\x10""Ruby\x10" "What?\x01");
	SetDialogString(42, "\x10""River\x10" "Ruby, you remember me?\x01");
	SetDialogString(43, "\x10""Ruby\x10" "I think I remember you, River.\x01");
	SetDialogString(44, "\x10""River\x10" "Oh, I'm surprised.\x01 So...\x01 Give\nme money, or else!\x01");
	SetDialogString(45, "\x10""Ruby\x10" "Why?\x01");
	SetDialogString(46, "\x10""River\x10" "Because I'm a member of the Navy\nGang!\x01 Navy Gangsters can do anything\nthey wish, or something like that...\x01");
	SetDialogString(47, "\x10""Ruby\x10" "Well, I don't think you can use\nmy money more efficiently than me.\x01");
	SetDialogString(48, "\x10""River\x10" "So be it...\x01 I'll take it by\nforce!\x01");
	SetDialogString(49, "\x10""River\x10" "Heh, I'm way stronger than you.\x01\nGive up!\x01");
	SetDialogString(50, "\x10""River\x10" "Ouch! What the heck!\x01 I'm going to\nlose at this rate!\x01");
	SetDialogString(51, "\x10""River\x10" "Enough, I give up!\x01");
	SetDialogString(52, "\x10""Ruby\x10" "(...Yes! The Magical Gem is\nworking!)\x01");
	SetDialogString(53, "\x10""Ruby\x10" "Well, thanks for being my,\nuh... I mean, good fighting!\x01");
	SetDialogString(54, "\x10""River\x10" "No, that sucked.\x01 I'm outta\nhere, I'm meeting up with my\nleader Sally and other members.\x01");
	SetDialogString(55, "\x10""Ruby\x10" "(Sally?\x01 That might be an old\nfriend of mine.\x01 Maybe I can get\nto the bottom of this whole\nNavy Gang thing.)\x01");
	SetDialogString(56, "\x10""Ruby\x10" "(Anyway, I should check on my\ninventory by pressing C/Enter.)\x01");
	SetDialogString(57, "\x10""Ruby\x10" "(Oh, and I should go ask my\npartner Noah to join me. Would make\nmy life easier.)\x01");
	
	SetDialogString(80, "\x10""Ruby\x10" "(This is where Sally lives, but\nI won't bother her for now.)\x01");
	SetDialogString(81, "\x10""Ruby\x10" "(Sally definitely isn't there.)\x01");
	SetDialogString(82, "\x10""Ruby\x10" "(Noah's computer. Looks identical\nto mine.\x01 It also uses Arch.)\x01");
	
	SetDialogString(90, "\x10""Ruby\x10" "I have something to discuss about\nwith your leader.\x01");
	SetDialogString(91, "\x10""Leaf Crew A\x10" "Uh-oh. I don't like your tone.\x01");
	SetDialogString(92, "\x10""Leaf Crew B\x10" "Get ready!\x01");
	SetDialogString(93, "\x10""Ruby\x10" "(I'm not ready to take on them\nyet...\x01 I should bring Noah with\nme.)\x01");
	
	SetDialogString(100, "\x10Navy Gang\x10Hey! You think you're so tough,\ngirl, trying to take on both of\nus alone?\x01 What a fool!\x01");
	SetDialogString(101, "\x10Navy Gang\x10Stop right here! You cannot pass.\x01\nActually, we're going to cut it right\nhere and beat you up.\x01");
	SetDialogString(102, "\x10Leaf Crew\x10Keep out!\x01 This is a private area for\nLeaf Crew personnel only.\x01");
	SetDialogString(103, "\x10Leaf Crew\x10Oh, hey. Welcome to Leaf Crew.\x03\x0a.\x03\x0a.\x03\x0a\nYou're a member of Leaf Crew, aren't\nyou?\x01");
	SetDialogString(104, "\x10Leaf Crew B\x10They are our enemies! They don't have\nour uniform, can't you see?\x01");
	SetDialogString(105, "\x10Leaf Crew A\x10Oh, okay.\x01");
	SetDialogString(106, "\x10Leaf Crew A\x10Guess we have to fight you then?\x01");
	SetDialogString(107, "\x10Leaf Crew C\x10Those are the ones who beat me up!\x01\nKick them off already!\x01");
	SetDialogString(108, "\x10Leaf Crew B\x10You heard him. Don't hold anything\nback.\x01");
	
	SetDialogString(110, "\x10Sally\x10Huh?\x01\nWhat are you doing here!\x01");
	SetDialogString(111, "\x10Ruby\x10...What's going on?\x01");
	SetDialogString(112, "\x10""Emmet\x10Ruby! I could use your help right now.\x01\nSally and her gang is trying to steal\nmoney from me!\x01");
	SetDialogString(113, "\x10Ruby\x10Uh, sure... I'm not fond of the \"Navy\nGang\" anyway.\x01");
	SetDialogString(114, "\x10Sally\x10Ugh, please stay away Ruby!\x01\nI won't hesitate to smash you both with\nmy club!\x01");
	SetDialogString(115, "\x10""Emmet\x10""...Yup. Sally's gotten messed up.\nDon't bother talking to her.\x01\nI'm not sure if we can beat\nher to senses...\x01");
	SetDialogString(116, "\x10Ruby\x10""Oh don't worry Emmet, we got\nthis. Navy Gangsters are more bark\nthan a bite.\x01");
	SetDialogString(117, "\x10Sally\x10I... That's it. Get ready to\x01\nlie on the ground after this.\x01");
	SetDialogString(118, "\x10Sally\x10...\x01");
	SetDialogString(119, "\x10""Emmet\x10""Looks like you lost. Too\nbad!\x01");
	SetDialogString(120, "\x10Sally\x10Shut up.\x01");
	SetDialogString(121, "\x10""Frank\x10Hey, wait for us!\x01");
	SetDialogString(122, "\x10""Emmet\x10Thanks, Ruby. I would've been toast\nif it weren't for you.\x01\nI hope Sally will be okay after\nthis.\x01");
	SetDialogString(123, "\x10Ruby\x10""Oh, I'm just... I've set off on\nan adventure, so to speak...\x01");
	SetDialogString(124, "\x10""Emmet\x10Ohh, an adventure? Sounds cool.\x01\nDon't mind if I tag along?\x11""Join\nRefuse\x11");
	SetDialogString(125, "\x10Ruby\x10Sure, this adventure will be tough,\nso I don't mind extra assistance...\x01");
	SetDialogString(126, "\x10""Emmet\x10Oh, thanks.\x01");
	SetDialogString(127, "\x10Ruby\x10Nah, I can take care of myself.\x01");
	SetDialogString(128, "\x10""Emmet\x10...I see. Guess I'll go home now. Cya,\nRuby!\x01");
	SetDialogString(129, "\x10""Emmet\x10""I trust you on this, Ruby.\x01");
	SetDialogString(130, "\x10""River\x10""...\x01");
	SetDialogString(131, "\x10Ruby\x10Nah, I and Noah can take care of\nourselves.\x01");
	SetDialogString(132, "\x10""Noah\x10" "Wait, Ruby! Emmet will be useful,\x01\nbring him along!\x01");
	SetDialogString(133, "\x10""Ruby\x10" "...\x01 Okay, whatever you say.\x01");
	
	SetDialogString(140, "\x10""???\x10" "Hey!! What are you doing?\x01");
	SetDialogString(141, "\x10""???\x10" "...\x01 Oh no...\x01");
	SetDialogString(142, "\x10""???\x10" "Look at what you've done with your\nfilthy hands...\x01 There's green stuff\non this tree now!\x01");
	SetDialogString(143, "\x10""Ruby\x10" "Oh, I... I was fighting some slimes\nin a nearby cave.\x01 And the this thing\nwas blocking the path, so I pushed it\nover...\x01 Sorry.\x01");
	SetDialogString(144, "\x10""???\x10" "Hmph! Should've asked me to move it\nthen!\x01 But no, you fools HAVE to mess\neverything up!\x01 What am I gonna do\nnow...\x01");
	SetDialogString(145, "\x10""???\x10" "What's your name, slimey gal?\x01");
	SetDialogString(146, "\x10""Ruby\x10" "Ruby. And... what's your name?\x01");
	SetDialogString(147, "\x10""???\x10" "My name shall be the last word\x01\nyou'll ever hear!\x01 \x10Lulu\x10Lulu's my name! And\nyou will pay for what you've done!\x01");
	SetDialogString(148, "\x10""Lulu\x10" "Prepare to die!\x01");
	SetDialogString(149, "\x10""Lulu\x10" "...Lulu!\x01");
	SetDialogString(150, "\x10""Lulu\x10" "No!\x03\x10 I won't let you get away with this!\x01");
	SetDialogString(151, "\x10""Lulu\x10" "Sayonara, idiots!\x01");
	SetDialogString(152, "\x10""Lulu\x10" "Sayonara, Ruby...\x01");
	
	SetDialogString(160, "\x10""Ruby\x10" "Hi, Noah, wanna join me in my\nadventure?\x01");
	SetDialogString(161, "\x10""Noah\x10" "Hi, Ruby... sure, what adventure?\x01");
	SetDialogString(162, "\x10""Ruby\x10" "Oh, I was going to search for\nthe Ancient Gems. You remember those?\x01");
	SetDialogString(163, "\x10""Noah\x10" "Yeah, I know about those. I\ncan help you out if you want.\x01");
	SetDialogString(164, "\x10""Ruby\x10" "Sure! It's going to be tough,\nbut don't worry, it'll be\nhard to stop us together.\x01");
	
	SetDialogString(170, "\x10""Ruby\x10" "Hmm.\x03\x10.\x03\x10.\x03\x10 this is in my way.\x01\nMaybe I can push it out of the way?\x01");
	SetDialogString(171, "\x10""Ruby\x10" "Hmm.\x03\x10.\x03\x10.\x03\x10 this is not in my way.\x01");
	
	SetDialogString(172, "\x10""Police Officer\x10" "Good day. Are you affiliated with\nLeaf Crew by chance?\x01");
	SetDialogString(173, "\x10""Ruby\x10" "No, sir.\x01");
	SetDialogString(174, "\x10""Police Officer\x10" "I see, I see. Call me Mr. Coppers.\x01\x10Mr. Coppers\x10\nI'm on the lookout for members\nof the Leaf Crew.\x01 You know, they\nstand out with green camouflaged\nclothes and such.\x01");
	SetDialogString(175, "\x10""Mr. Coppers\x10" "Problem is, their leader is damn\nstrong. We can't do anything to\nher!\x01");
	SetDialogString(176, "\x10""Ruby\x10" "Hmm... I think we can help.\x01");
	SetDialogString(177, "\x10""Mr. Coppers\x10" "Help with what? Taking down the\nLeaf Crew?\x01 I don't think you can\ndo that, ma'am! Are you mad?\x01");
	SetDialogString(178, "\x10""Ruby\x10" "...I know what I'm doing.\x01");
	SetDialogString(179, "\x10""Mr. Coppers\x10" "Well, your help would be much\nappreciated then, haha.\x01 I'll give you\nlots of money if you eliminate the Leaf\nCrew, got it?\x01");
	
	SetDialogString(180, "\x10""???\x10" "Oh, hello. Who are you?\x01");
	SetDialogString(181, "\x10""Ruby\x10" "My name's Ruby.\x01 You're Lisao, right?\x01");
	SetDialogString(182, "\x10""Lisao\x10" "Yep! You're smart.\x01");
	SetDialogString(183, "\x10""Lisao\x10" "I'm Lisao, the leader of the Leaf Crew.\nI wield powerful vine magic.\x01");
	SetDialogString(184, "\x10""Emmet\x10" "Vine magic? Sounds cool.\x01");
	SetDialogString(185, "\x10""Ruby\x10" "So, I heard you and your crew is\ntargetting and attacking people you\ndon't like. Is that true?\x01");
	SetDialogString(186, "\x10""Lisao\x10" "...\x01\nSo what if it's true.\x01\nWhat are you gonna do about it?\x01");
	SetDialogString(187, "\x10""Ruby\x10" "I'm just curious.\x01");
	SetDialogString(188, "\x10""Emmet\x10" "Don't you think that's going too far?\nWhat did they do to you?\x01");
	SetDialogString(189, "\x10""Lisao\x10" "...\x01");
	SetDialogString(190, "\x10""Ruby\x10" "Lisao?\x01");
	SetDialogString(191, "\x10""Lisao\x10" "I have nothing to say to you fools.\x01");
	SetDialogString(192, "\x10""Ruby\x10" "...\x01");
	SetDialogString(193, "\x10""Lisao\x10" "You think you're the \"heroes\", yes?\nYou're actually fools wishing for\ndeath...\x01");
	SetDialogString(194, "\x10""Lisao\x10" "I'll make sure to give you what you\ndeserve! Prepare... to face the power\nof vines!\x01");
	SetDialogString(195, "\x10""Lisao\x10" "...\x01");
	SetDialogString(196, "\x10""Lisao\x10" "I guess I was a pushover, after all.\nNothing more than a joke...\x01");
	SetDialogString(197, "\x10""Lisao\x10" "I...\x01\n.\x03\10.\x03\10.\x01\nI think.\x03\10.\x03\10.\x01\nI think I'll go take a nap.\x03\10.\x03\10.\x01");
	SetDialogString(198, "\x10""Noah\x10" "I think we went a bit too hard on her...\nI hope she'll be okay.\x01");
	SetDialogString(199, "\x10""Emmet\x10" "I wonder what's up with her.\x01");
	SetDialogString(200, "\x10""Ruby\x10" "Lisao has something important in her\nhouse I believe. Let's check it out.\x01");
	SetDialogString(201, "\x10""Ruby\x10" "(Leaf Crew's hideout is north from\nmy house. This is where I should\nbe heading to now.)\x01");
	SetDialogString(202, "\x10""Emmet\x10" "Ruby, why not bring Noah with us?\x01\nMr. Coppers said taking on the\nLeaf Crew would be pretty difficult...\x01\nI think having a third person\nwith us would make the job\nsignificantly easier.\x01");
	SetDialogString(203, "\x10""Ruby\x10" "I guess you're right...\x01\n(I should ask Noah to join me\nbefore going to the hideout.)\x01");
	SetDialogString(204, "\x10""Lisao\x10" "With what purpose have you decided\nto pay me a visit?\x01");
	SetDialogString(205, "\x10""Ruby\x10" "Oh, I came here to take the\nAncient Gem.\x01");
	SetDialogString(206, "\x10""Lisao\x10" "Well...\x03\x20 You see...\x01\nThat \"Ancient Gem\" is a treasure of\nmy grandfather.\x01 I will NOT give it\nup for someone like you. No chance!\x01");
	SetDialogString(207, "\x10""Ruby\x10" "But I need it...!\x01");
	SetDialogString(208, "\x10""Lisao\x10" "...\x01You think you're entitled\nto that gem?\x01");
	SetDialogString(209, "\x10""Lisao\x10" "You're just like the others.\x01\nPathetic scumbags that plague the\nwhole world...\x01");
	
	SetDialogString(210, "\x10""Ruby\x10" "There it is!\x01");
	SetDialogString(211, "\x10""Emmet\x10" "What's that?\x01");
	SetDialogString(212, "\x10""Ruby\x10" "This is the Emerald of Earth, one of\nthe Ancient Gems.\x01 There's a bunch\nof legends about these things.\x01");
	SetDialogString(213, "\x10""Emmet\x10" "I see... And you want to get them\nall, am I correct?\x01");
	SetDialogString(214, "\x10""Ruby\x10" "Uhhh, no... There's a plenty of them.\nI just need 5 of them.\x01");
	SetDialogString(215, "\x10""Emmet\x10" "Uh, what do you need them for if you\ndon't mind sharing?\x01");
	SetDialogString(216, "\x10""Ruby\x10" "These gems are very powerful, so I\nwanted to research them and maybe make\ndiscoveries by myself.\x01");
	SetDialogString(217, "\x10""Ruby\x10" "The next Ancient Gem should be in\nBluesteel Town.\x01 But before that I'm\ngoing to try to convince Sally to\njoin us.\x01");
	SetDialogString(218, "\x10""Emmet\x10" "Hmmm... I guess it wouldn't hurt\nto have her in our team.\x01");
	SetDialogString(219, "\x10""Ruby\x10" "I think she will be very helpful\nstill. Anyways, let's go.\x01");
	
	SetDialogString(220, "\x10""Lulu\x10" "I'm BACK, suckers!\x01");
	SetDialogString(221, "\x10""Ruby\x10" "...\x01");
	SetDialogString(222, "\x10""Lulu\x10" "Nerds like you REALLY piss me off...\x01");
	SetDialogString(223, "\x10""Lulu\x10" "See what I've got here?\x01");
	SetDialogString(224, "\x10""Ruby\x10" "A red sword?\x01");
	SetDialogString(225, "\x10""Lulu\x10" "Hah! It's not any ordinary red-colored\nsword, you naive woman... It's a\nlegendary, powerful blazin' katana!\x01\nIt used to belong to a legendary\nsuperhero!! It's that powerful!\x01");
	SetDialogString(226, "\x10""Ruby\x10" "Interesting...\x01");
	SetDialogString(227, "\x10""Emmet\x10" "Really? I think you're simply trying\nto scare us.\x01");
	SetDialogString(228, "\x10""Lulu\x10" "Oh, you'd better get ready to\nbeg for forgiveness...\x01");
	SetDialogString(229, "\x10""Lulu\x10" "Oh-ho-ho, You're so screwed now...\x01\nFor I am the legendary, and\nformidable, uh...\x01\nBlazin' Lulu!!\x01\nDie!!!\x01");
	SetDialogString(230, "\x10""Lulu\x10" "Wh... what?\x01 What was that?!\x01");
	SetDialogString(231, "\x10""Noah\x10" "Lulu, come on...\x03\x20There's no need\nto get so worked up over such a\nminor thing...\x01");
	SetDialogString(232, "\x10""Lulu\x10" "Even with a legendary weapon in my\nhands... I was...\x01");
	SetDialogString(233, "\x10""Lulu\x10" "AAAAAAAAAARRRRGGGHHHHHH!!!!!!!!!!\x01");
	SetDialogString(234, "\x10""Lulu\x10" "But you're just weaklings! How?!\x01");
	SetDialogString(235, "\x10""Ruby\x10" "We got stronger as well...\x01");
	SetDialogString(236, "\x10""Emmet\x10" "Not to mention... You tried to\ntake on all of us... alone!\x01");
	SetDialogString(237, "\x10""Lulu\x10" "...\x01");
	SetDialogString(238, "\x10""Lulu\x10" "Bah! You know what, Ruby?\x01\nThis means war, and I will not\ngive up so easily!!\x01");
	SetDialogString(239, "\x10""Lulu\x10" "See ya later!!\x01");
	SetDialogString(240, "\x10""Lulu\x10" "But you're just a weakling! How?!\x01");
	
	SetDialogString(250, "\x10""Noah\x10" "Wow. I've never been here\nbefore...\x01");
	SetDialogString(251, "\x10""Emmet\x10" "Wait until you see the Lapis City,\nNoah. You'd be in awe!\x01 So\nwhat are we gonna do now, Ruby?\x01");
	SetDialogString(252, "\x10""Ruby\x10" "I dunno, maybe we should take a bit\nof a break.\x01");
	SetDialogString(253, "\x10""Emmet\x10" "Yeah, we did lots of stuff today...\x01\nWait, I know where we should hang\naround.\x01 Club Jackie!\x01");
	SetDialogString(254, "\x10""Ruby\x10" "Club Jackie? Sure I guess.\x01 Where\nis it?\x01");
	SetDialogString(255, "\x10""Emmet\x10" "In the south part of this town.\x01\nLet's go there!\x01");
	SetDialogString(256, "\x10""Ruby\x10" "(Hmmm...\x01 what do I do now?)\x01");
	SetDialogString(257, "\x10""Ruby\x10" "(Either way, the Ancient Gem should\nbe in an abandoned mansion to the\nnorth of the town.\x01\nNo need for a rush though,\nI can take my time here.)\x01");
	
	SetDialogString(260, "\x10""Emmet\x10" "We're here!\x01\nLet's get some drinks and relax.\x01\nBartender Electra is over here.\x01");
	
	SetDialogString(261, "\x10""Electra\x10" "Hello, what do you wanna order\nright now?\x01");
	SetDialogString(262, "\x10""Emmet\x10" "Three orange juices, please.\x01");
	SetDialogString(263, "\x10""Electra\x10" "That'll be $9.\x11Yes\nNo\x11");
	SetDialogString(264, "\x10""Electra\x10" "Here you go.\x01");
	SetDialogString(265, "\x10""Emmet\x10" "Darn, we don't have money.\x01");
	SetDialogString(266, "\x10""Electra\x10" "That's OK. I can give you\nthree glasses of water for free.\x01");
	SetDialogString(267, "\x10""Emmet\x10" "Oh cool, thanks!\x01");
	SetDialogString(268, "\x10""Emmet\x10" "C'mon, Ruby. If you don't like\norange juice, we can get water\ninstead.\x01");
	SetDialogString(269, "\x10""Electra\x10" "I'll give you three glasses\nof water for free.\x01");
	
	SetDialogString(270, "\x10""Emmet\x10" "Well...\x01 what do we wanna talk\nabout?\x01");
	SetDialogString(271, "\x10""Ruby\x10" "...\x01");
	SetDialogString(272, "\x10""Emmet\x10" "Not much to talk about, eh?\x01\nMaybe we could actually bring\nSally, she could brighten up the\nmood.\x01 (or ruin it)\x01");
	SetDialogString(273, "\x10""Noah\x10" "Sure.\x01");
	SetDialogString(274, "\x10""Ruby\x10" "Well, she should be somewhere in\nthis area. If Sora wasn't lying,\nthat is. Even then, we have to\nconvince her to join us...\x01");
	SetDialogString(275, "\x10""Emmet\x10" "What a whole year of shut-in life\ndoes to a person... I mean, we've\nall been through tough times, but\nstill I feel sorry for Sally-\x01");
	SetDialogString(276, "\x10""Noah\x10" "Oops, I dropped my glass.\x01");
	SetDialogString(277, "\x10""Ray\x10" "Jackie! Electra! There are violators in\nthis club!\x01");
	SetDialogString(278, "\x10""Jackie\x10" "Now you've done it people!\x01\nYou will not get away with this!\x01");
	SetDialogString(279, "\x10""Emmet\x10" "Good job, Noah.\x01");
	SetDialogString(280, "\x10""Noah\x10" "It was an accident...\x01");
	SetDialogString(281, "\x10""Jackie\x10" "An accident you say.\x01 Accident.\x01\nAccidents kill millions of people every\nday! You know that, fellas?\x01");
	SetDialogString(282, "\x10""Emmet\x10" "This is just a broken cup of glass.\nSay, how about we pay our way\nout of this and leave?\x01");
	SetDialogString(283, "\x10""Jackie\x10" "Awesome idea! I agree!\x01\nYou'll pay your way out with your\nlives. Sounds like a great deal, no?\x01");
	SetDialogString(284, "\x10""Ruby\x10" "...\x01");
	SetDialogString(285, "\x10""Jackie\x10" "Ladies and gentlemen! Prepare for...\x01");
	SetDialogString(286, "\x10""Jackie\x10" "...a comedy show!\x01 (Blood effects\nincluded)\x01");
	
	SetDialogString(287, "\x10""Jackie\x10" "Wowzers... You're playing the wrong\nroles!\x01");
	SetDialogString(288, "\x10""Electra\x10" "Jackie, maybe we should let them go.\nIt's not worth pursuing them over\na small thing.\x01");
	SetDialogString(289, "\x10""Ray\x10" "They outsmarted my Ninja instincts.\x01\nIt's no use!\x01");
	SetDialogString(290, "\x10""Jackie\x10" "Fine! I'll let you go. Not\nlike I can force you to oblige.\x01");
	SetDialogString(291, "\x10""Ruby\x10" "Cool.\x01");
	SetDialogString(292, "\x10""Jackie\x10" "Not as cool as my 3D glasses!\x01\nCome back later, only if you bring\nthe undeserved fines!\x01 Shoe!\x01");
	SetDialogString(293, "\x10""Jackie\x10" "Just give me a handshake and you're\noff the hook.\x01\n...Do it! Shake hands!\x01");
	SetDialogString(294, "\x10""Ruby\x10" "And what if I refuse?\x01 What\nare you gonna do?\x01");
	SetDialogString(295, "\x10""Jackie\x10" "I will.\x03\x30.\x03\x30.\x03\x30 I will protest and bother\nthe government to make refusing\nshaking hands punishable with $160000\nfinancial fines and a death penalty\nwith bass-boosted Meat Factory playing\nover your ears at 4 mdB with\nChorus/Flanger filter enabled!\x01 Or an\nequally harsh punishment of forcing\nyou to do janitor work for a 72\nminute period!\x01");
	SetDialogString(296, "\x10""Jackie\x10" "Hold up! You're already off the\nhook!\x01 My bad, we are not pirates.\x01");
	SetDialogString(297, "\x10""Emmet\x10" "That was...\x03\x50 something.\x01");
	
	SetDialogString(300, "\x10""Ruby\x10" "Well, that didn't go well.\x01");
	SetDialogString(301, "\x10""Emmet\x10" "It's pretty late now. Maybe\nwe could stay in a nearby hotel?\x01");
	SetDialogString(302, "\x10""Ruby\x10" "Sure, let's go.\x01");
	SetDialogString(303, "\x10""???\x10" "Hey!\x01");
	SetDialogString(304, "\x10""Emmet\x10" "Huh? Perry?\x01");
	SetDialogString(305, "\x10""Perry\x10" "Yeah, hello Emmet, Ruby and Noah!\x01\nYou can stay in my house\nif you want.\x01");
	SetDialogString(306, "\x10""Emmet\x10" "Oh cool. Thanks Perry.\x01");
	SetDialogString(307, "\x10""Perry\x10" "No problem. Follow me. It's not\nfar from here.\x01");
	SetDialogString(308, "\x10""Perry\x10" "Behold! My house.\x01 It's been a\nwhile since I had visitors aside\nfrom my brother...\x01");
	SetDialogString(309, "\x10""Perry\x10" "Let's go to my room.\x01");
	SetDialogString(310, "\x10""Perry\x10" "Don't mind if I ask a favor?\x01");
	SetDialogString(311, "\x10""Ruby\x10" "Go ahead.\x01");
	SetDialogString(312, "\x10""Perry\x10" "I need to get something from\nthe basement, but...\x01\nThere are spiders!\x01 I mean,\nbig and dangerous spiders! I\ncould really use your help.\x01");
	SetDialogString(313, "\x10""Emmet\x10" "Spiders? It's nothing. Leave it\nto us, Perry.\x01");
	SetDialogString(314, "\x10""Perry\x10" "Haha, thanks. I'll follow you\nguys.\x01");
	
	SetDialogString(315, "\x10""Perry\x10" "Oh, hello, Ruby.\x01 Wanna come to\nmy house?\x11Sure\nNope\x11");
	SetDialogString(316, "\x10""Ruby\x10" "Sure.\x01");
	SetDialogString(317, "\x10""Perry\x10" "Cool! Follow me.\x01");
	SetDialogString(318, "\x10""Ruby\x10" "I'll help.\x01");
	SetDialogString(319, "\x10""Perry\x10" "Oh, thanks! I'll be following you\nthen.\x01");
	
	SetDialogString(320, "\x10""Perry\x10" "Gimme that!\x01");
	SetDialogString(321, "\x10""Perry\x10" "Thanks a lot! You're awesome!\x01\nIt's a present for my brother.\nHe's coming late tomorrow from\ncollege.\x01");
	SetDialogString(322, "\x10""Noah\x10" "I'm feeling exhausted...\x01");
	
	SetDialogString(323, "\x10""Perry\x10" "It's late. I'll go to sleep.\x01\nYou can go sleep in my room too\nif you want.\x01");
	SetDialogString(324, "\x10""Ruby\x10" "Sure.\x01");
	SetDialogString(325, "\x10""Perry\x10" "I'll go make some beds for y'all\nthen.\x01");
	SetDialogString(326, "\x10""Noah\x10" "It's quite dark in here.\x01");
	SetDialogString(327, "\x10""Perry\x10" "There should be a flashlight\nsomewhere.\x01");
	SetDialogString(328, "\x10""Perry\x10" "That's better.\x01 You can keep it,\nRuby. I can get another one.\x01");
	SetDialogString(329, "\x10""Perry\x10" "Okay, I'll make a bed for you\nthen.\x01");
	
	SetDialogString(330, "\x10""Perry\x10" "Good morning!\x01");
	SetDialogString(331, "\x10""Emmet\x10" "Good morning, Perry. Thanks for\nletting us stay the night.\x01");
	SetDialogString(332, "\x10""Perry\x10" "It's about 5:30 AM right now, so\nit's still dark outside...\x01");
	SetDialogString(333, "\x10""Perry\x10" "So... wanna have a breakfast?\x01");
	SetDialogString(334, "\x10""Ruby\x10" "No thanks. We gotta go.\x01");
	SetDialogString(335, "\x10""Perry\x10" "Wait, can you take a slice of\nmy pizza that I just made at least?\x01");
	SetDialogString(336, "\x10""Perry\x10" "Oh, you must be on some important\nquest or something.\x01 I'd ask\nto help, but I'd just be a burden\nto you all, considering I'm weak...\x01");
	SetDialogString(337, "\x10""Perry\x10" "Uh... anyway, bye! You can visit me\nany day.\x01");
	SetDialogString(338, "\x10""Perry\x10" "Check out the kitchen, it's\nin there.\x01 I'm bad at cooking,\nbut I hope you'll like it!\x01");
	
	SetDialogString(340, "\x10""Noah\x10" "What's next?\x01");
	SetDialogString(341, "\x10""Ruby\x10" "We pay a visit to an abandoned\nmansion.\x01 It's to the north of\nthe town.\x01");
	SetDialogString(342, "\x10""Ruby\x10" "(The next Ancient Gem should be at\nLapis City.\x01 I can travel there via\npublic water transport at the east of\nthe town.)\x01");
	
	SetDialogString(350, "\x10""Police 1\x10" "Halt, ma'am! Do you know anything\nabout the Leaf Crew?\x11Yes\nNo\x11");
	SetDialogString(351, "\x10""Police 1\x10" "Oh, hm...\x01");
	SetDialogString(352, "\x10""Police 2\x10" "My senses tell me that they are\nfrom the Leaf Crew.\x01");
	SetDialogString(353, "\x10""Police 1\x10" "That's what I thought. You'd better\nsurrender and come with us now.\x01");
	SetDialogString(354, "\x10""Emmet\x10" "What? No way!\x01");
	SetDialogString(355, "\x10""Police 1\x10" "I see. You'd better prepare to\nget knocked out!\x01");
	SetDialogString(356, "\x10""Emmet\x10" "...\x01 What's your problem?\nWe're not from the Leaf Crew,\nI swear!\x01");
	SetDialogString(357, "\x10""Police 1\x10" "You should've listened to me...\nLooks like I have to call backup.\x01");
	SetDialogString(358, "\x10""Emmet\x10" "You can't arrest people just because\nthey disobey your orders, am I\nwrong?\x01");
	SetDialogString(359, "\x10""Police 1\x10" "...\x01");
	SetDialogString(360, "\x10""Police 2\x10" "...\x01");
	SetDialogString(361, "\x10""Police 1\x10" "Whatever you say...\x01");
	SetDialogString(362, "\x10""Police 2\x10" "Don't get in our way when\nwe're dealing with the Vandals.\x01");
	SetDialogString(363, "\x10""Emmet\x10" "Phew, we managed to win against\nthe cops. Anyway, let's go to\nClub Jackie.\x01");
	SetDialogString(364, "\x10""Ruby\x10" "The Leaf Crew has already disbanded.\x01\nAnd I was the one who defeated\ntheir leader.\x01 Why did you think I'm\nfrom the Leaf Crew?\x01");
	SetDialogString(365, "\x10""Police 1\x10" "Wait, what?\x03\x20 I'll need to consult my\nboss about this.\x01");
	SetDialogString(366, "\x10""Police 2\x10" "I guess that's a good idea.\x01\nExcuse us for trouble, ma'am.\x01");
	
	SetDialogString(370, "\x10""???\x10" "'ey. Are you Ruby?\x01");
	SetDialogString(371, "\x10""Ruby\x10" "...Who are you?\x01");
	SetDialogString(372, "\x10""Josh\x10" "I'm Josh, the operator of the\nSYNC office. Nice to meet you.\x01");
	SetDialogString(373, "\x10""Ruby\x10" "Uh, nice to meet you too. I'm\nRuby.\x01");
	SetDialogString(374, "\x10""Emmet\x10" "I'm Emmet, and he's Noah.\x01");
	SetDialogString(375, "\x10""Josh\x10" "Ah, okay then. You are in my\nhit list.\x01 I've come here to\nbeat you up, y'know.\x01");
	SetDialogString(376, "\x10""Ruby\x10" "...Why?\x01");
	SetDialogString(377, "\x10""Josh\x10" "You're in my hit list as\nI said.\x01");
	SetDialogString(378, "\x10""SYNC Member\x10" "We snap anyone's neck\nin that list.\x01 That's the rules\nof the SYNC.\x01");
	SetDialogString(379, "\x10""Josh\x10" "Get ready.\x01");
	SetDialogString(380, "\x10""Josh\x10" "Damn. You're better than\nI thought.\x01");
	
	SetDialogString(390, "\x10""Emmet\x10" "Wait, is that Sally over\nthere?\x01");
	SetDialogString(391, "\x10""Sally\x10" "What do you want from me.\x01");
	SetDialogString(392, "\x10""Emmet\x10" "What are you doing out here\nalone?\x01 Why did you leave the Navy\nGang?\x01");
	SetDialogString(393, "\x10""Sally\x10" "Heh. None of your business.\x01");
	SetDialogString(394, "\x10""Emmet\x10" "...\x01");
	SetDialogString(395, "\x10""Sally\x10" "I gave my position to someone\nnamed Sora. And went my ways.\x01\nThat's all, now get outta here.\x01");
	SetDialogString(396, "\x10""Ruby\x10" "Hey, Sally. Why don't you join\nus.\x01");
	SetDialogString(397, "\x10""Sally\x10" "Join what?\x01");
	SetDialogString(398, "\x10""Ruby\x10" "Our... team? We're on an\nimportant quest, so your help would\nbe very much appreciated...\x01");
	SetDialogString(399, "\x10""Sally\x10" "Huh. Well, I've got my own\nmatters... my own important quest.\x01\nSo... nah.\x01");
	SetDialogString(400, "\x10""Emmet\x10" "What \"important quest\" do you\nhave exactly?\x01");
	SetDialogString(401, "\x10""Sally\x10" "Wh... How about YOU tell me\nfirst, greedy man.\x01");
	SetDialogString(402, "\x10""Emmet\x10" "Uhh, Ruby's the one who's\nsupposed to tell-\x01");
	SetDialogString(403, "\x10""Sally\x10" "I know. Stop stalling and just\nsay it loud!\x01");
	SetDialogString(404, "\x10""Emmet\x10" "...\x01");
	SetDialogString(405, "\x10""Ruby\x10" "It's about finding very rare\nitems called \"Ancient Gems\".\x01");
	SetDialogString(406, "\x10""Sally\x10" "Ancient Gems..?\x01");
	SetDialogString(407, "\x10""Ruby\x10" "Yes. They're mysterious but\nvery powerful.\x01");
	SetDialogString(408, "\x10""Sally\x10" "...\x01 And I am trying to\nget stronger.\x01");
	SetDialogString(409, "\x10""Emmet\x10" "You'll get stronger much\nfaster if you simply join us.\x01");
	SetDialogString(410, "\x10""Sally\x10" "Shut it, Emmet.\x01 Anyway...\x01");
	SetDialogString(411, "\x10""Sally\x10" "Okay, you know what.\x01\nI'll accept your offer, Ruby,\nbut...\x01 YOU will help me\nin my quest of getting stronger.\x01\nDo we call it a deal?\x01");
	SetDialogString(412, "\x10""Ruby\x10" "...Yeah.\x01");
	SetDialogString(413, "\x10""Emmet\x10" "But you were already going to\nget stron-");
	SetDialogString(414, "\x10""Sally\x10" "I said shut it! Ruby, I also need\nyou to put duct tape on Emmet's\nmouth.\x01");
	SetDialogString(415, "\x10""Ruby\x10" "Well, he's kind of right. But\nfine, I'll make sure he won't\ntalk too much.\x01");
	SetDialogString(416, "\x10""Emmet\x10" "...\x01");
	SetDialogString(417, "\x10""Sally\x10" "Cool. I'll follow behind you\nthen, Ruby. Just don't make\nme do anything funny or else.\x01");
	
	SetDialogString(430, "\x10""Emmet\x10" "Is she even home?\x01");
	SetDialogString(431, "\x10""Ruby\x10" "I don't know, but I guess we're\nabout to find out.\x01");
	SetDialogString(432, "\x10""Ruby\x10" "*knock* knock* Hello? Sally?\x01");
	SetDialogString(433, "\x10""Emmet\x10" "She usually comes out after like\n2 minutes of knocking... Try again?\x01");
	SetDialogString(434, "\x10""Emmet\x10" "...\x01 Hello?\x01");
	SetDialogString(435, "\x10""Sora\x10" "Yeah? Are you looking for Sally?\x01");
	SetDialogString(436, "\x10""Emmet\x10" "Uh... yes! You know where is\nshe right now?\x01");
	SetDialogString(437, "\x10""Sora\x10" "Oh, she gave me the leadership\nfor the Navy Gang just a few hours\nago. She was acting strangely,\ndon't know why.\x01");
	SetDialogString(438, "\x10""Emmet\x10" "She's pretty unstable indeed.\nWhere is she now?\x01");
	SetDialogString(439, "\x10""Sora\x10" "She said she was going to Bluesteel\nTown.\x01");
	SetDialogString(440, "\x10""Emmet\x10" "Got it.\x01");
	SetDialogString(441, "\x10""Sora\x10" "So... anything else you need\nfrom me?\x01");
	SetDialogString(442, "\x10""Emmet\x10" "You're Sora, the new leader of\nthose Navy Gangsters, I hope you\nwon't be as troublesome as Sally\nwas...\x01");
	SetDialogString(443, "\x10""Sora\x10" "Okay, whatever you say.\x01");
	SetDialogString(444, "\x10""Ruby\x10" "We were going to Bluesteel Town\nanyway, so that makes it convenient\nfor us.\x01");
	SetDialogString(445, "\x10""Sora\x10" "See ya then!\x01");
	SetDialogString(446, "\x10""Ruby\x10" "Well, we did everything here.\x01\nLet's take a bus to the Bluesteel\nTown.\x01");
	
	SetDialogString(450, "\x10""Emmet\x10" "You think... we should take\nthat?\x01 Has it not expired?\x01");
	SetDialogString(451, "\x10""Noah\x10" "No, it's not.\x01");
	SetDialogString(452, "\x10""Ruby\x10" "Did you know canned tomato soup\ncan be stored up to 737 years?\x01\nSounds unbelievable, but I can confirm\nfrom my own experiments.\x01");
	SetDialogString(453, "\x10""Emmet\x10" "Damn. Well, I trust you two\non that then.\x01");
	SetDialogString(454, "\x10""Emmet\x10" "Damn. Well, I trust you\non that, Ruby.\x01");
	
	SetDialogString(460, "\x10""Kevin\x10" "...\x01Hold on, I'm busy speedrunning\nYour Mom 4.\x01");
	SetDialogString(461, "\x10""Ruby\x10" "Oh wow, you're pretty good at\nit. Impressive!\x01");
	SetDialogString(462, "\x10""Kevin\x10" "Crap, I'm bad at my Kick Card\nskips.\x01");
	SetDialogString(463, "\x10""Ruby\x10" "(I won't bother him for now.)\x01");
	
	SetDialogString(470, "\x10""Sally\x10" "Hold on, I got this.\x01");
	SetDialogString(471, "\x10""Emmet\x10" "Are you gonna break open the\ndoor by brute force?\x01");
	SetDialogString(472, "\x10""Sally\x10" "No... I'm gonna use this random\nkey I found earlier.\x01 Just a\nmoment...\x01");
	SetDialogString(473, "\x10""Sally\x10" "...\x03\x30 Ugh...\x01");
	SetDialogString(474, "\x10""Ruby\x10" "It doesn't fit?\x01");
	SetDialogString(475, "\x10""Sally\x10" "Uhhh... there's like 40 keys\non this keychain.\x01 I'm trying\nthem all.\x01");
	SetDialogString(476, "\x10""Emmet\x10" "...This is going to take forever.\x01");
	SetDialogString(477, "\x10""Sally\x10" "...\x01");
	SetDialogString(478, "\x10""Ruby\x10" "Be patient, Emmet. Take your\ntime, Sally.\x01");
	SetDialogString(479, "11 minutes later...\x01");
	SetDialogString(480, "\x10""Sally\x10" "...\x03\x20""Finally! Frickin' hell, of\ncourse the last one I try is the\none that works.\x01");
	SetDialogString(481, "\x10""Emmet\x10" "Oh, you actually opened it?\x01");
	SetDialogString(482, "\x10""Ruby\x10" "Well, at least you found the\nactual key.\x01 Let's come in.\x01");
	SetDialogString(483, "\x10""Sally\x10" "Why are we going there anyway,\nRuby?\x01");
	SetDialogString(484, "\x10""Ruby\x10" "To get the Ancient Gem in there.\x01");
	SetDialogString(485, "\x10""Sally\x10" "Oh. Right. That's what you're\nlooking for after all.\x01");
	SetDialogString(486, "\x10""Sally\x10" "Hell yes! First try.\x01");
	SetDialogString(487, "\x10""Ruby\x10" "You unlocked it?\x01");
	SetDialogString(488, "\x10""Sally\x10" "Of course I did. Now, let's go\nsearch for that gem you're looking\nfor,\x03\x20 I guess.\x01");
	
	SetDialogString(490, "\x10""???\x10" "......\x01\nSo you have come.\x01");
	SetDialogString(491, "\x10""Ruby\x10" "Hello...? Are you Dia?\x01");
	SetDialogString(492, "\x10""Dia\x10" "...Yes. What business do you have\nhere? Why are you infiltrating my\nhome?\x01");
	SetDialogString(493, "\x10""Ruby\x10" "Oh, I just wanted to...\x01");
	SetDialogString(494, "\x10""Sally\x10" "So you must be the witch of this\nmansion then.\x01 Let alone killing whoever\ncomes here, I heard you also send\nyour 'pets' to attack the people\nout of the mansion.\x01 You think\nyou can get away with those crimes?\x01");
	SetDialogString(495, "\x10""Dia\x10" "Of course, all of you have to drop\nthat \"witch\" word at me. But what\nyou said about me killing people and\nreleasing my pets to the wild is true.\x01\nOh, and I'm also responsible for\nthe death of Diana's parents.\x01");
	SetDialogString(496, "\x10""Emmet\x10" "Why would you do that?\x01");
	SetDialogString(497, "\x10""Dia\x10" "If you don't know, you don't\nknow, you empty buckets for skulls.\x01");
	SetDialogString(498, "\x10""Sally\x10" "Think you're tough, huh. You'd\nbetter give us the Ancient Gem,\nunless you want to get squished\ninto a strawberry pancake within 1.2\nfemtoseconds.\x01\nOr a mustard avocado pancake.\x01");
	SetDialogString(499, "\x10""Emmet\x10" "Sally! Stop it!\x01");
	SetDialogString(500, "\x10""Sally\x10" "Shut up! I show no mercy to\ncriminal witches.\x01");
	SetDialogString(501, "\x10""Dia\x10" "...\x01");
	SetDialogString(502, "\x10""Dia\x10" "Well, I've had enough of your\ntrashtalk. If you really insist on\nfollowing your fallacies, then I shall\nburn you all down.\x01");
	SetDialogString(503, "\x10""Sally\x10" "Phew... That's it. Time to\nfinish you off.\x01");
	SetDialogString(504, "\x10""Dia\x10" "Then do it...\x03\x30 Swing with all\nstrength you have...\x03\x30 I dare you...\x01");
	SetDialogString(505, "\x10""Ruby\x10" "Stop, Sally! That's enough!\x01\nWe don't have to go that far.\x01");
	SetDialogString(506, "\x10""Sally\x10" "...\x01");
	SetDialogString(507, "\x10""Ruby\x10" "Dia, I can tell you had it pretty\nrough.\x01 So, uh...\x01");
	SetDialogString(508, "\x10""Dia\x10" "...Diana?\x01");
	SetDialogString(509, "\x10""Ruby\x10" "...\x01");
	SetDialogString(510, "\x10""Dia\x10" "Only she would understand my\npain.\x01 Everyone else was a mindless\nnumbskull.\x01 You remind me of\nDiana...\x01");
	SetDialogString(511, "\x10""Ruby\x10" "Oh? I'm Ruby, not Diana.\nStill, I don't think you deserve\nto suffer.\x01 And not everyone is a\n\"mindless numbskull\" like you say.\nThere are some cool people,\nthey just get overshadowed by\nthe bad apples...\x01 That's just the\nreality you have to deal with.\x01");
	SetDialogString(512, "\x10""Emmet\x10" "Yeah, you gotta treat everyone\ndifferently.\x01");
	SetDialogString(513, "\x10""Dia\x10" "I thought you would just try\nto finish me off... But you're actually\nsomewhat nice people...\x01\n...except for her.\x01");
	SetDialogString(514, "\x10""Sally\x10" "...\x01");
	SetDialogString(515, "\x10""Ruby\x10" "Well... I can be your friend\nif you want to.\x01");
	SetDialogString(516, "\x10""Dia\x10" "Oh... really?\x01");
	SetDialogString(517, "\x10""Ruby\x10" "Well, yeah, as long as you\ndon't pull any shenanigans on me or\nsomething.\x01");
	SetDialogString(518, "\x10""Dia\x10" "...Thanks.\x01 I don't know much about\nyou, but you're definitely not one\nof those...\x01\nWait, why did you come here\nin the first place?\x01");
	SetDialogString(519, "\x10""Ruby\x10" "I believe you have an Ancient Gem,\ndo you?\x01 If so, can I have it please?\x01");
	SetDialogString(520, "\x10""Dia\x10" "...\x01I don't know what an \"Ancient\nGem\" is...\x01\nBut... maybe you'll find it in my\nand Diana's room.\x01");
	SetDialogString(521, "\x10""Dia\x10" "Wait!\x01");
	SetDialogString(522, "\x10""Dia\x10" "I'm trying to recover... don't\ncause any trouble please.\x01");
	SetDialogString(523, "\x10""Dia\x10" "Flame yourselves!\x01");
	SetDialogString(524, "\x10""Dia\x10" "Take this.\x01");
	SetDialogString(525, "\x10""Dia\x10" "I hope you come back soon.\x01");
	SetDialogString(526, "\x10""Ruby\x10" "...My pockets are full.\x01");
	SetDialogString(527, "\x10""Dia\x10" "Oh, I'll hold onto this Aqua Berry\nthen...\x01");
	
	SetDialogString(530, "\x10""Ruby\x10" "2 down, 3 more to go.\x01");
	SetDialogString(531, "\x10""Sally\x10" "Looks...\x03\x30 charming...\x03\x30\x01\nSo that's an Ancient Gem.\x01");
	SetDialogString(532, "\x10""Ruby\x10" "Yeah. Maybe I'll be able to uncover\ntheir true nature.\x01");
	SetDialogString(533, "\x10""Ruby\x10" "Let's go look for the next one.\x01");
	
	SetDialogString(540, "\x10""Lulu\x10" "There you are!!\x01");
	SetDialogString(541, "\x10""Noah\x10" "Oh no... Not her again.\x01");
	SetDialogString(542, "\x10""Lulu\x10" "I brought a team this time.\x01\nSurely that should be ENOUGH to\ndemolish you.\x01");
	SetDialogString(543, "\x10""Ruby\x10" "Oh... maybe it is enough...\x01 but\nwe have got the powers of\na witch now.\x01");
	SetDialogString(544, "\x10""Lulu\x10" "A witch? What? You mean that\nnew friend-\x01 Bah, who\ncares!\x01");
	SetDialogString(545, "\x10""Lulu\x10" "Gentlemen, show NO MERCY!\x01");
	SetDialogString(546, "\x10""Emmet\x10" "Wait, so you're the one who\nput us in the hit list of the...\nSYNC or whatever it was called?\x01");
	SetDialogString(547, "\x10""Lulu\x10" "Yes! Now let me show you the\npower of the stronger than before\nBlazin' Lulu and some random\nSYNC members!\x01");
	SetDialogString(548, "\x10""Lulu\x10" "No... No... It can't be...\x01");
	SetDialogString(549, "\x10""Josh\x10" "Well well... Hello, Lulu.\x01 You're\ndoing fine right now I assume?\x01");
	SetDialogString(550, "\x10""Lulu\x10" "SYNC leader? What are you\ndoing here?.\x01");
	SetDialogString(551, "\x10""Josh\x10" "Oh, nothing special. Just wanted\nto request promised money.\x01");
	SetDialogString(552, "\x10""Lulu\x10" "Money? I'm not gonna give you\nmoney.\x01");
	SetDialogString(553, "\x10""Josh\x10" "I see. Then you shall be on\nour hit list.\x01 Just a moment,\nplease don't go anywhere.\x01");
	SetDialogString(554, "\x10""Lulu\x10" "Don't you dare!\x01 Ugh... Why would\nI even pay for you to not even\nhave your job done properly?\x01");
	SetDialogString(555, "\x10""Josh\x10" "You remember what the contract\nsaid, right?\x01 Or did you read it\nat least?\x01");
	SetDialogString(556, "\x10""SYNC Member\x10" "We're riskin' our lives for\nthis kind of job. Pay is expected\nregardless if we succeed or fail.\x01");
	SetDialogString(557, "\x10""SYNC Member\x10" "You're barely standing right\nnow. You won't be able to escape\nnor fight back.\x01");
	SetDialogString(558, "\x10""Lulu\x10" "...\x01""FINE!\x01 Take your $999!\x01");
	SetDialogString(559, "\x10""Lulu\x10" "Useless pieces of crap, calling\nthemselves professionals... Can't even\ntake on some random commoners!\x01");
	SetDialogString(560, "\x10""Josh\x10" "Whew, what an annoying gal.\x01\nBut at least she did pay\nwith the money in the end.\x01");
	SetDialogString(561, "\x10""Sally\x10" "So... did something happen between\nyou and her?\x01");
	SetDialogString(562, "\x10""Ruby\x10" "Lulu's trying to kill me. Or,\nrather, humiliate me.\x01 All because she\nput that tree statue in front\nof the Slime Cave entrance...\x01");
	SetDialogString(563, "\x10""Sally\x10" "...Whatever, let's go.\x01");
	SetDialogString(564, "\x10""Lulu\x10" "Ruby?\x01 Any last words?\x01");
	SetDialogString(565, "\x10""Lulu\x10" "Cat got your tongue, eh?\x01 Well,\nRuby, you can't run forever...\x03\x20\nYou'll have to pay the taxes.\x01\nIncluding the Lulu Tax...\x03\x30 which you\nwill pay RIGHT NOW!!\x01");
	SetDialogString(566, "\x10""Lulu\x10" "...\x01""FINE!\x01 Take your $998!\x01");
	SetDialogString(567, "\x10""Lulu\x10" "Useless pieces of crap, calling\nthemselves professionals... Can't even\ntake on a LONE MUSCLELESS GIRL...\x01 What\na f***ing joke...\x01");
	SetDialogString(568, "\x10""Lulu\x10" "I brought a team this time.\x01\nSurely that should be ENOUGH to\ndestroy you.\x01");
	
	SetDialogString(570, "\x10""Sally\x10" "What the...\x01");
	SetDialogString(571, "\x10""Lulu\x10" "Don't think you're going anywhere,\nRuby!!\x01");
	SetDialogString(572, "\x10""Emmet\x10" "Wait, didn't we just fight you\na few moments ago?\x01");
	SetDialogString(573, "\x10""Lulu\x10" "Uh... yes. But, when I realized\nthat the demo is going to be over\nsoon...\x01 I decided to speedrun my\nwalk to Sapphirepolis to change\nmyself into Omega Lulu,\x01 and also\nmanipulate cosmic rays 6 parallel\nuniverses far from ours to make\nme recover instantly.\x01 Then I used\na glitch to get here instantly as\nwell.\x01");
	SetDialogString(574, "\x10""Sally\x10" ".\x03\x20.\x03\x20.\x03\x20the hell are you talking about?\x01");
	SetDialogString(575, "\x10""Lulu\x10" "Forget it! I'm just going to\ndestroy you all, once and for\nall.\x01 I'll ruin the whole game\nfor you!\x01");
	SetDialogString(576, "\x10""Lulu\x10" "Face the Ultimate Power of the\nOmega Lulu, bitches!!!\x01");
	SetDialogString(577, "\x10""Lulu\x10" "No.\x03\x20.\x03\x20.\x03\x20.\x01 I won't be defeated again!\x01");
	SetDialogString(578, "\x10""Lulu\x10" "N-No... Apparently this power wasn't\nenough to beat you...\x01");
	SetDialogString(579, "\x10""Lulu\x10" "How could I lose...\x01");
	SetDialogString(580, "WARNING: NEGATIVE ENERGY OVERFLOWING\x01\nDO NOT PROCEED FURTHER OR YOU WILL\nREGRET IT\x01");
	SetDialogString(581, "\x10""Lulu\x10" "You.\x03\x20.\x03\x20.\x03\x20. Ruby.\x03\x20.\x03\x20.\x03\x20.\x03\x80\nYOU WON'T GET AWAY THIS TIME!!!\x01");
	SetDialogString(582, "\x10""Lulu\x10" "HAHAHAHAHA! Suck it, n****rs! You\nare completely useless now.\x01 Omega\nLulu is undefeatable!\x01");
	SetDialogString(583, "\x10""Lulu\x10" "That's enough messing around.\x01\nTime for my special attack!\x01\nGet ready, idiots!!\x01");
	SetDialogString(584, "\x10""Lulu\x10" "What? How did you survive that?\x01\nFuck you, dirty cheater! It's\nsoftlock time!\x02");
	SetDialogString(585, "\x10""Lulu\x10" "Hey, Ruby, wanna see my special\nattack?\x01 It's extremely EXTREME, RAW\nand DEMONIC...\x01 and EVIL!\x01 I'm gonna\nuse it next turn, so I'd suggest you\ndie right now, cause it won't be fun\nfor you at all!\x01");
	
	SetDialogString(590, "\x10""Bouncer? 1\x10" "H-Hold on!\x03\x20 Where's your membership\ncard?\x01 This is the Razor Chaos club,\nand you cannot pass without one!\x01");
	SetDialogString(591, "\x10""Ruby\x10" "...Where do I get it?\x01");
	SetDialogString(592, "\x10""Bouncer? 1\x10" ".\x03\x20.\x03\x20.\x03\x20""From Sanji of course, dummy!\x01");
	SetDialogString(593, "\x10""Emmet\x10" "Doesn't seem like you can stop\nus from entering anyway...\x01");
	SetDialogString(594, "\x10""Bouncer? 2\x10" "...Are you sure?\x01 Kelly, you know\nwhat to do.\x01");
	SetDialogString(595, "\x10""Kelly\x10" "Yes, Neveah.\x01");
	SetDialogString(596, "\x10""Kelly\x10" "I warn you, this thing I'm holding\nis pretty deadly.\x01 One whip, and you'll\nend up in hospital!\x01");
	SetDialogString(597, "\x10""Sally\x10" "Oh, okay. How about this?\x01");
	SetDialogString(598, "\x10""Sally\x10" "One swing, and you'll end up\nin a different planet.\x01");
	SetDialogString(599, "\x10""Neveah\x10" "That piece of trash you're holding?\nI beg to differ.\x01");
	SetDialogString(600, "\x10""Kelly\x10" "Girl, time for a little shock\ntherapy!\x01");
	SetDialogString(601, "\x10""Kelly\x10" "...No!\x01 What are you?\x01");
	SetDialogString(602, "\x10""Neveah\x10" "You won this one.\x01 But Sanji will\nbe rather mad to hear about this,\nI think.\x01 Let's go, sis.\x01");
	SetDialogString(603, "\x10""Bouncer? 2\x10" "*sigh* Kelly, let's kick her out.\x01");
	SetDialogString(604, "\x10""Kelly\x10" "Of course, Neveah!\x03\x20 We will knock the\nlight out of your glasses, nerd!\x01");
	
	SetDialogString(610, "\x10""Sally\x10" "Y'all ready to storm those damn\npirates?\x01");
	SetDialogString(611, "\x10""Emmet\x10" "Are you gonna-\x01");
	SetDialogString(612, "\x10""Sally\x10" "Yes, I'm gonna break down this\ndoor.\x01 Let's throw 'em a big party!\x01");
	SetDialogString(613, "\x10""Emmet\x10" "Wait-\x01");
	SetDialogString(614, "\x10""Sally\x10" "...\x01");
	SetDialogString(615, "\x10""Kelly\x10" "...\x01");
	SetDialogString(616, "\x10""Sally\x10" "Ummm...\x01 oops?\x01");
	SetDialogString(617, "\x10""Kelly\x10" "What are you doing, you\nbarbarians!\x01");
	SetDialogString(618, "\x10""Ruby\x10" "Sally? The club is to the right\nof the entrance.\x01");
	SetDialogString(619, "\x10""Sally\x10" "...This is a weird place for a\nrestroom!\x01");
	
	SetDialogString(620, "\x10""Sally\x10" "Alright, this time we're going in\nfor real!\x01");
	SetDialogString(621, "\x10""Sally\x10" "Hmm...\x01 I hear music over there.\x01");
	SetDialogString(622, "\x10""Ruby\x10" "Let's check it out.\x01");
	SetDialogString(623, "\x10""Ruby\x10" "Locked. We really needed a\nmembership card after all.\x01");
	SetDialogString(624, "\x10""Sally\x10" "Nevermind, this one's tough.\x01");
	SetDialogString(625, "\x10""Noah\x10" "I think those guards have one\x01of those.\x01");
	SetDialogString(626, "\x10""Sally\x10" "Right! We should go and threaten\nthose brats to give us a card!\x01");
	SetDialogString(627, "\x10""Noah\x10" "We saw them in restroom, we\nshould go there.\x01");
	SetDialogString(628, "\x10""Noah\x10" "Let's just look for a card.\x01");
	
	SetDialogString(630, "\x10""Kelly\x10" "What do you want from us?\x01");
	SetDialogString(631, "\x10""Sally\x10" "A card.\x01");
	SetDialogString(632, "\x10""Neveah\x10" "You mean, the membership card?\x01\nNo chance we're giving it away.\nThose cards belong to us.\x01");
	SetDialogString(633, "\x10""Sally\x10" "You want another fight or what?\x01");
	SetDialogString(634, "\x10""Neveah\x10" "Wow, how violent. Okay, I'll\ngive you mine.\x01 Get ready...\x01");
	SetDialogString(635, "\x10""Neveah\x10" "...run!\x01");
	SetDialogString(636, "\x10""Sally\x10" "Those degenerates got away...\x01\nNext time I'll just cut to the\nchase...\x01");
	SetDialogString(637, "\x10""Ruby\x10" "It's fine. I will eventually find\none lying somewhere.\x01");
	
	SetDialogString(640, "You used the RC Membership Card.\x01");
	SetDialogString(641, "\x10""Emmet\x10" "It didn't open?\x01");
	SetDialogString(642, "\x10""Noah\x10" "Looks like it.\x01");
	SetDialogString(643, "\x10""Sally\x10" "Great. How do we get in now?\x01");
	SetDialogString(644, "\x10""Ruby\x10" "I'll figure it out.\x01\n(Maybe this card is broken or\nnot \"good enough\"...)\x01");
	SetDialogString(645, "You used the RC VIP Card.\x01\nYou unlocked the door.\x01");
	SetDialogString(646, "\x10""Ruby\x10" "(Didn't open...\x03\x20 maybe this card is\nbroken or not \"good enough\"...)\x01");
	
	SetDialogString(650, "\x10""Perry\x10" "Wow! Thanks a lot! You're a\nreal life saver, Ruby!\x01 I knew\nI could count on you!\x01 It's a\npresent for my brother, so... give\nit to me please?\x11Give back\nDon't give back\x11");
	SetDialogString(651, "\x10""Perry\x10" "Phew, I think that's all for\ntoday. Let's go back.\x01");
	SetDialogString(652, "\x10""Perry\x10" "...Ruby?\x01 It's a present for my\nbrother, I wanna surprise him with\nsuch an expensive gaming console!\x01\n...Please?\x11Okay\nNope\x11");
	SetDialogString(653, "\x10""Perry\x10" "Ruby...\x03\x40 If you really want this,\nI'll give you this later on your\nbirthday...\x01 I used parents' money to\nget this one, so please...\x11Okay\nIt's mine now\x11");
	SetDialogString(654, "\x10""Ruby\x10" "It's mine now.\x01");
	SetDialogString(655, "\x10""Perry\x10" "...\x01Okay, fine, this is a present\nfor you then.\x01 Take good care of\nit, okay?\x01");
	SetDialogString(656, "You unwrapped the present.\x01");
	SetDialogString(657, "\x10""Perry\x10" "...Ruby?\x03\x40 Let's go back.\x01");
	
	SetDialogString(660, "\x10""Perry\x10" "Good night!\x01");
	SetDialogString(661, "\x10""Perry\x10" "Good morning!\x01 It's about 5:30 AM\nright now, so it's still dark outside...\x01");
	SetDialogString(662, "\x10""Perry\x10" "Wanna have a breakfast?\x01 I made\nyou a pizza slice, by the way.\x01");
	
	SetDialogString(663, "\x10""Perry\x10" "R-Ruby...\x03\x30 Wh-what are you d-doing here?\x01");
	SetDialogString(664, "\x10""Perry\x10" "P-Please.\x03\x20.\x03\x20.\x03\x20 leave.\x03\x20.\x03\x20.\x01");
	SetDialogString(665, "\x10""Perry\x10" "W-Why aren't you saying anything?\x01\nI'm s-scared...\x03\x20 please...\x01");
	SetDialogString(666, "\x10""Perry\x10" "Ruby...\x03\x20 I believed you to be\na person who...\x01");
	SetDialogString(667, "\x10""Perry\x10" "Like...\x03\x30 you could be tr-trusted...\x03\x40\nand...\x03\x20 and n-... not...\x01");
	SetDialogString(668, "\x10""Perry\x10" "I-\x03\x10 p-please...\x01");
	SetDialogString(669, "\x10""Perry\x10" "Stop it!\x03\x20 Or else...\x01");
	
	SetDialogString(670, "\x10""Perry\x10" "Oh...\x03\x20 did you drop it on accident?\x11Yes, sorry\n...\x11");
	SetDialogString(671, "\x10""Ruby\x10" "Yeah... sorry.\x03\x20 I didn't mean to do\nthat.\x01");
	SetDialogString(672, "\x10""Perry\x10" "It's nothing.\x01 Just be more careful\nnext time, okay?\x01");
	SetDialogString(673, "\x10""Perry\x10" "Ruby?\x03\x30 Something's wrong?\x01 Don't drop\nanything more, okay?\x11OK\nDrop the OFF\x11");
	SetDialogString(674, "\x10""Perry\x10" "Ruby?\x03\x30 Something's wrong?\x01 Don't drop\nanything more, okay?\x01");
	SetDialogString(675, "\x10""Perry\x10" ".\x03\x20.\x03\x20.\x01");
	SetDialogString(676, "\x10""Perry\x10" "W-Wait, please don'-\x01");
	SetDialogString(677, "\x10""Perry\x10" "Ruby...\x03\x30 Don't make me do this,\nplease...\x01");
	SetDialogString(678, "\x10""Perry\x10" "P\x03\x5L\x03\x5""E\x03\x5""A\x03\x5s\x03\x5""E\x03\x5! I\x03\x5 b\x03\x5""e\x03\x5g\x03\x5 y\x03\x5o\x03\x5u\x03\x5.\x03\x5.\x03\x5.\x01");
	SetDialogString(679, "\x11""Spare\nFight\x11");
	
	SetDialogString(680, "\x10""Sally\x10" "Ruby!\x01");
	SetDialogString(681, "\x10""Sally\x10" "Hello...\x01 What are you doing here?\x01");
	SetDialogString(682, "\x10""Ruby\x10" "Looking for Ancient Gems.\x01");
	SetDialogString(683, "\x10""Sally\x10" "...huh.\x01 Don't mind if I join in\nyour quest?\x01");
	SetDialogString(684, "\x10""Ruby\x10" "Weren't you suppose to lead the Navy\nGang?\x01");
	SetDialogString(685, "\x10""Sally\x10" "Oh, forget that.\x03\x20 I handed the leadership\nto someone else, 'cause I didn't want\nto do anything with it anymore...\x01");
	SetDialogString(686, "\x10""Sally\x10" "So... wanna invite me to the party?\x11Sure\nNope\x11");
	SetDialogString(687, "\x10""Sally\x10" "So... wanna invite me to the party?\x11Okay\nNo\x11");
	SetDialogString(688, "\x10""Ruby\x10" "Hmmm, okay, sure.\x01");
	SetDialogString(689, "\x10""Sally\x10" "Cool.\x03\x20 Let's go, I guess.\x01");
	SetDialogString(690, "\x10""Ruby\x10" "Nope, I don't need any help.\x01");
	SetDialogString(691, "\x10""Ruby\x10" "No, I don't need any help.\x01");
	SetDialogString(692, "\x10""Sally\x10" "Too bad.\x03\x20 I'm gonna join you,\nwhether you like it or not.\x01\nC'mon, I don't have anything\nbetter to do...\x01");
	SetDialogString(693, "\x10""Ruby\x10" "...fine.\x01");
	SetDialogString(694, "\x10""Ruby\x10" "Hmmm, okay.\x01");
	SetDialogString(695, "\x10""Ruby\x10" "...\x01");
	SetDialogString(696, "\x10""Perry\x10" "R-Ruby?\x03\x20 P-Please...\x01");
	SetDialogString(697, "\x10""Ruby\x10" "Perry...\x03\x20 I'm sorry...\x01 I...\x01");
	SetDialogString(698, "\x10""Perry\x10" "...\x01");
	SetDialogString(699, "\x10""Ruby\x10" "I'm so tired of all this...\x01");
	
	SetDialogString(700, "\x10""Sally\x10" "Eeek!!!!\x01");
	SetDialogString(701, "\x10""Sally\x10" "Ugh, what the hell! I'm stuck\nin this spider web...\x01");
	SetDialogString(702, "\x10""Sally\x10" "Help me, Ruby!\x03\x40 I can't get out!\x01");
	SetDialogString(703, "\x10""Sally\x10" "No! Where are you going!\x01\nDon't leave!\x03\x30 Please, help me!\x01");
	SetDialogString(704, "\x10""Sally\x10" "HEEELP!!\x03\x40 RUBY!!\x03\x40 PLEASE!!\x03\x40 HELP\x03\x20 ME!!\x01");
	SetDialogString(705, "\x10""Sally\x10" "Oh my god...\x03\x70 Oh...\x03\x40 The hell with\nthose spiders...\x01");
	SetDialogString(706, "\x10""Sally\x10" "Thanks, Ruby...\x03\x50 You're a real brave,\x03\x20\nand,\x03\x20 uh,\x03\x20 not a coward\x03\x40 hero...\x01");
	SetDialogString(707, "\x10""Sally\x10" "...Nevermind, let's f*** those spiders\nup beyond repair.\x01");
	SetDialogString(708, "\x10""Ruby\x10" "(I can't leave Sally to die.)\x01");
	SetDialogString(709, "\x10""Ruby\x10" "(Anyway,\x03\x20 let's continue looking for\nAncient Gems like nothing happened.)\x01");
	
	SetDialogString(710, "\x10""Brook\x10" "Who's this?\x01");
	SetDialogString(711, "\x10""Brook\x10" "You're the intruders, right?\x01");
	SetDialogString(712, "\x10""Ruby\x10" "...\x03\x40Yes.\x01");
	SetDialogString(713, "\x10""Brook\x10" "Wow, you're honest.\x03\x20 Did you fool\nthe bouncers at the entrance?\x01");
	SetDialogString(714, "\x10""Sally\x10" "We beat 'em up, actually.\x01 What's\nthe matter?\x01");
	SetDialogString(715, "\x10""Brook\x10" "You waited for us to take a\nbreak, huh?\x01 Cowards!\x01");
	SetDialogString(716, "\x10""Brook\x10" "Tom, whaddya think we should do?\x01");
	SetDialogString(717, "\x10""Tom\x10" "Uhh...\x03\x40 remove the intruders?\x01");
	SetDialogString(718, "\x10""Brook\x10" "Right, you said it...\x01");
	SetDialogString(719, "\x10""Brook\x10" "Hey friends, let me safely escort\nyou back to the entrance!\x01");
	SetDialogString(720, "\x10""Brook\x10" "Oof...\x03\x20 that's some firepower you\ngot there...\x01");
	SetDialogString(721, "\x10""Ruby\x10" "It's pretty cool, isn't it?\x01");
	SetDialogString(722, "\x10""Tom\x10" "If only we had Cindy with us...\x01\nAnyway, you won and I suppose I\nhave to give you something.\x01");
	SetDialogString(723, "\x10""Tom\x10" "This lets you access the disco\nroom without verification.\x01");
	SetDialogString(724, "\x10""Brook\x10" "You're an intruder, right?\x01");
	SetDialogString(725, "\x10""Tom\x10" "Uhh...\x03\x40 remove the intruder?\x01");
	SetDialogString(726, "\x10""Brook\x10" "I hate to do this, but I need\nto escort you back to the entrance,\nglasses gal!\x01");
	SetDialogString(727, "\x10""Perry\x10" "I think you really need help...\x01\nWhat you did was not okay.\x01 I\ndon't care much about the pizza,\x03\x20\nbut the OFF was so expensive...\x01 My\nchance to surprise my brother was\nruined...\x01");
	SetDialogString(728, "\x10""Perry\x10" "I'll forgive you...\x03\x40 but please...\x03\x40\nthink about what you've done, okay?\x01");
	SetDialogString(729, "\x10""Perry\x10" "...I'll go rest.\x01 Hope you feel better,\nRuby.\x01");
	
	SetDialogString(730, "\x10""???\x10" "A legendary pirate lord that has\nqualities of a hero...\x01 One, who does\nnaught but make the world a better\nplace,\x03\x40 and clashing against the\nEvil all by self...\x01");
	SetDialogString(731, "\x10""Sally\x10" "Hello, Sanji.\x01 We know who you\nare.\x01");
	SetDialogString(732, "\x10""Sanji\x10" "You do not know your manners, do\nyou?\x01 Anyhow, who are you all.\x01");
	SetDialogString(733, "\x10""Sally\x10" "Oh, uh...\x03\x40 My name's Sally.\x01\n...The girl in labcoat is Ruby.\x01");
	SetDialogString(734, "\x10""Sanji\x10" "She's the leader.\x03\x20 Got it.\x01 I shall call\ny'all...\x03\x40\"The Ruby Gang\".\x01");
	SetDialogString(735, "\x10""Emmet\x10" "What's in those shelves, may I ask?\x01");
	SetDialogString(736, "\x10""Sanji\x10" "Completely legal copies of games,\nmovies and other media, of course.\x01");
	SetDialogString(737, "\x10""Emmet\x10" "That's a very convincing statement.\x01\nEspecially from the leader of a\ncriminal cartel of pirates.\x01");
	SetDialogString(738, "\x10""Sanji\x10" "\"Criminal cartel\"?\x01 What are you, an\nevil corporate lawyer?\x01");
	SetDialogString(739, "\x10""Sally\x10" "I agree!\x01");
	SetDialogString(740, "\x10""Sally\x10" "Screw those ancient gems or whatever.\x03\x20\nI'm joining the bad- I mean, good\nguys.\x01");
	SetDialogString(741, "\x10""Emmet\x10" "What are you doing?!\x01");
	SetDialogString(742, "\x10""Ruby\x10" "Come back, Sally!\x01");
	SetDialogString(743, "\x10""Sally\x10" "I told you not to make me do anything\nstupid...\x01 Why would I go against the\npeople who provide stuff for-\x01");
	SetDialogString(744, "\x10""Sanji\x10" "Don't try to fool me.\x01 I know\na betrayal coming from miles away,\x03\x20\nespecially from someone possibly\nbelonging to an evil organization...\x01");
	SetDialogString(745, "\x10""Emmet\x10" "Thanks, Sanji, for trying to knock\nsome sense into her.\x01 I guess some\nvillains aren't all bad after all.\x01");
	SetDialogString(746, "\x10""Sanji\x10" "What...\x01");
	SetDialogString(747, "\x10""Sanji\x10" "WHAT makes you think me of\na VILLAIN?!\x01");
	SetDialogString(748, "\x10""Sanji\x10" "What's your goal?\x01 What are you\ndoing this for?\x01 Do you even know\nwhere you're coming from?\x01");
	SetDialogString(749, "\x10""Ruby\x10" "I need you to shut down this piracy\noperation.\x01");
	SetDialogString(750, "\x10""Sanji\x10" "Hah, of course.\x01 What makes you think\nyou're different from other \"good\nguys\"?!\x01 SHOW ME!!!\x01");
	SetDialogString(751, "\x10""Sanji\x10" "No.\x03\x20.\x03\x20.\x03\x60 You must be...\x01");
	SetDialogString(752, "\x10""Ruby\x10" "You have been thwarted.\x01 Now you have\nno choice but to follow the law.\x01");
	SetDialogString(753, "\x10""Sanji\x10" "Whatever you say.\x01 You want me to\nstop operating here?\x01 Okay, I will\nshut down the Razor Chaos club and all\nof our websites.\x01 I will also get\nrid of all copyright-infringing\x01\nmaterial. Oh, and I'll pay the fines.\x03\x20\nIs that all you need from me?\x01");
	SetDialogString(754, "\x10""Ruby\x10" "...\x01 I guess so.\x01");
	SetDialogString(755, "\x10""Sanji\x10" "Okay then. Everything should be done\nby tonight.\x01 Promise.\x01");
	SetDialogString(756, "\x10""Ruby\x10" "Let's get going, then?\x01");
	SetDialogString(757, "\x10""Sanji\x10" "Don't worry, we are ceasing our\noperations and preparing to shut\ndown tonight.\x01");
	
	SetDialogString(760, "\x10""Emmet\x10" "I can't believe we stopped such\na powerful organization of pirates\nin less than a day...\x01");
	SetDialogString(761, "\x10""Noah\x10" "Maybe we should rest?\x01");
	SetDialogString(762, "\x10""Sally\x10" "Yes...\x01 I want to take a\nbreak.\x01");
	SetDialogString(763, "\x10""Ruby\x10" "I saw a hotel nearby.\x03\x20 Let's go\nthere.\x01");
	
	SetDialogString(770, "\x10""???\x10" "STAHP RIGHT HERE!!!\x01");
	SetDialogString(771, "\x10""Sally\x10" "...Did you hear that?\x01");
	SetDialogString(772, "\x10""Sally\x10" "Someone's up there!\x01");
	SetDialogString(773, "\x10""Lulu\x10" "We meet again!!\x01");
	SetDialogString(774, "\x10""Ruby\x10" "And we'll beat you again.\x01");
	SetDialogString(775, "\x10""Lulu\x10" "SHUT UP!!\x01 I have gotten MUCH\nstronger since our last encounter.\x01\nSanji is a hobo compared to the\nOmega Lulu.\x01");
	SetDialogString(776, "\x10""Sally\x10" "Those are some big words you're\nthrowing, lady.\x01");
	SetDialogString(777, "\x10""Lulu\x10" "Yes.\x03\x20 And I can support my claims\nvery easily.\x01");
	SetDialogString(778, "\x10""Ruby\x10" "We'll see about that.\x01");
	SetDialogString(779, "\x10""Lulu\x10" "It's over, Ruby!\x01 You can't win this\nfight!\x01");
	
	SetDialogString(780, "\x10""Sally\x10" "Wow, they got a PlayTon X here.\x01");
	SetDialogString(781, "\x10""Emmet\x10" "I wonder if it works.\x01");
	SetDialogString(782, "\x10""Emmet\x10" "It does.\x01 I guess we can chill\nout and play a few games?\x01");
	SetDialogString(783, "\x10""Sally\x10" "Hell yes!\x03\x20 Let me pick a good\ngame to play...\x01");
	SetDialogString(784, "\x10""Sally\x10" "Nevermind, we have to watch these\nads first...\x01");
	SetDialogString(785, "\x10""Ruby\x10" "Well, that was a lot of fun.\x01");
	SetDialogString(786, "\x10""Sally\x10" "I agree, we should do this\nagain tomorrow.\x01");
	SetDialogString(787, "\x10""Noah\x10" "Yeah.\x01");
	
	SetDialogString(790, "\x10""Noah\x10" "You're awake, Ruby?\x01");
	SetDialogString(791, "\x10""Ruby\x10" "What happened?\x01");
	SetDialogString(792, "\x10""Emmet\x10" "Oh, good morning.\x01 You fell asleep\nin the boss' room it seems.\x01 We\nhad to carry you to here.\x01");
	SetDialogString(793, "\x10""Ruby\x10" "Wow... okay.\x01 Let's go.\x01");
	SetDialogString(794, "\x10""Sally\x10" "I wish we stayed here a bit longer...\x01\nEh,\x03\x20 sure,\x03\x20 let's go beat up some bad\nguys.\x01 It pays us money apparently.\x01");
	
	SetDialogString(800, "\x10""Ninja 1\x10" "Only local residents may visit the\nVolcano Dojo.\x01 Who are you?!\x01");
	SetDialogString(801, "\x10""Ninja 2\x10" "You're so eager to pass through,\nhuh?\x01");
	SetDialogString(802, "\x10""Sally\x10" "Y'all think you're tough?\x01 We can\neasily take you two.\x01");
	SetDialogString(803, "\x10""Ninja 1\x10" "Two?\x03\x40 *claps hands*\x01");
	SetDialogString(804, "\x10""Ninja 3\x10" "Trespassers!\x01");
	SetDialogString(805, "\x10""Sally\x10" "...Oh.\x01");
	SetDialogString(806, "\x10""Ninja 4\x10" "Take this..\x03\x05!!!\x01");
	SetDialogString(807, "\x10""Ninja 1\x10" "You beat us...\x01");
	SetDialogString(808, "\x10""Sally\x10" "Stop wasting time and get outta\nour way.\x01");
	SetDialogString(809, "\x10""Ninja 1\x10" "Of course, masters.\x03\x20 Beware of Sir\nVulkan, he is not someone you want to\nmess with!\x01");
	SetDialogString(810, "\x10""Sally\x10" "Sure sure.\x01");
	SetDialogString(811, "\x10""Ninja 1\x10" "Alright, let's see you deal with\nTHIS...\x03\x40 *claps hands*\x01");
	SetDialogString(812, "\x10""Ninja 3\x10" "...That's it??\x01");
	SetDialogString(813, "\x10""Ninja 4\x10" "Don't underestimate her!\x03\x20 She could\nbe a Demi-God for all we know...\x01");
	SetDialogString(814, "\x10""Ninja 3\x10" "Hmph...\x03\x20 let's verify that!\x01");
	SetDialogString(815, "\x10""Ninja 3\x10" "Ouch!!\x03\x20 You're tough!\x01");
	SetDialogString(816, "\x10""Ninja 1\x10" "You won,\x03\x20 therefore you are granted\npermission to see Sir Vulkan.\x01 Though,\nit's worth to mention that Sir\nVulkan will not be messing around.\x01");
	
	SetDialogString(820, "\x10""Ninjas\x10" "KYAH!!\x01");
	SetDialogString(821, "\x10""Ninja 1\x10" "Did the Master give you an\ninvitation to the Dojo?\x01");
	SetDialogString(822, "\x10""Ninja 2\x10" "Master warns us beforehand if\nguests are to be expected...\x01 You,\nthough, are UNEXPECTED.\x01");
	SetDialogString(823, "\x10""Ninja 1\x10" "So,\x03\x20 whaddya say-\x01");
	SetDialogString(824, "\x10""Vulkan\x10" "...\x01What's going on.\x01 Unexpected guests,\x03\x20\nyou say?\x01");
	SetDialogString(825, "\x10""Ninjas\x10" "...\x01");
	SetDialogString(826, "\x10""Vulkan\x10" "Now, jump back to your posts.\x01");
	SetDialogString(827, "\x10""Vulkan\x10" "I said JUMP BACK TO YOUR POSTS,\x03\x20\nYOU TWO.\x01");
	SetDialogString(828, "\x10""Ninjas\x10" "Roger!\x01");
	SetDialogString(829, "\x10""Vulkan\x10" "Ruby, eh?\x01 Nice to meet you.\x01");
	SetDialogString(830, "\x10""Ruby\x10" "You know me..?\x01");
	SetDialogString(831, "\x10""Vulkan\x10" "I heard you're looking for shiny\ngems.\x01 I happen to have one of those.\x01");
	SetDialogString(832, "\x10""Ruby\x10" "...\x01");
	SetDialogString(833, "\x10""Vulkan\x10" "How do I know?\x03\x20 Well, it's a secret\nof a ninja.\x01 Actually, I have a few\nsubordinates that inform me about\nbasically everything going on in Lapis\nCity...\x01");
	SetDialogString(834, "\x10""Emmet\x10" "So you have spies working for you,\nam I right?\x01");
	SetDialogString(835, "\x10""Vulkan\x10" "That's correct,\x03\x20 if I haven't made it\nobvious enough.\x01");
	SetDialogString(836, "\x10""Ruby\x10" "So, what about the Ancient Gem?\x03\x20\nYou have it for real?\x01");
	SetDialogString(837, "\x10""Vulkan\x10" "Hmm.\x01 Ruby.\x01");
	SetDialogString(838, "\x10""Ruby\x10" "What is it?\x01");
	SetDialogString(839, "\x10""Vulkan\x10" "Let's enter the building and\ncontinue our discussion there.\x01");
	SetDialogString(840, "\x10""Sally\x10" "...\x03\x30""Do we trust this guy?\x01");
	SetDialogString(841, "\x10""Ruby\x10" "I think so.\x01 Let's go in...\x01");
	SetDialogString(842, "\x10""Ruby\x10" "Okay...\x03\x30 what about the gem?\x01");
	SetDialogString(843, "\x10""Ruby\x10" "Hm?\x01");
	
	SetDialogString(850, "\x10""Vulkan\x10" "Even though you might know\na lot about the Ancient Gems,\x03\x20 you\nshould still listen to me.\x01");
	SetDialogString(851, "\x10""Vulkan\x10" "Ancient Gems are an unsolved mystery.\x01\nPeople know they exist, but have no\nidea of their purpose or usability.\x01");
	SetDialogString(852, "\x10""Vulkan\x10" "Even the government,\x03\x20 the Onyx Ministry,\x03\x20\nwasn't able to find the answers.\x01\nHowever, they have made significant\nprogress...\x01");
	SetDialogString(853, "\x10""Vulkan\x10" "You know about the \"Supernaturals\",\x03\x20\nthey are human beings that wield\nimmense power, not unlike magic.\x01 They\nhave the power to destroy a town or\nsometimes a whole country...\x01");
	SetDialogString(854, "\x10""Vulkan\x10" "The research shows that a lot of\nSupernaturals were \"born\" from the\nAncient Gems.\x01 People with such a gem,\x03\x20\ncoupled with some sort of intense\nstress or something,\x03\x20 ascend into much\nmore powerful beings...\x01");
	SetDialogString(855, "\x10""Vulkan\x10" "Or so I recall...\x01 However, despite this\ninformation,\x03\x20 the Ministry scientists\nhaven't been able to replicate such a\nphenomenon,\x01 nor were they able to\nfind anything else to make use of the\ngems...\x01");
	SetDialogString(856, "\x10""Vulkan\x10" "Tell me,\x03\x20 Ruby.\x01 Considering the fact\nthat the government couldn't crack\nopen such a well-known mystery despite\ntrying their BEST...\x01 Do you really\nthink you can turn the lights on all\nof this by yourself?\x01");
	SetDialogString(857, "\x10""Ruby\x10" "I-I'm sure of it...\x01");
	SetDialogString(858, "\x10""Vulkan\x10" "...\x01If you say so.\x01");
	SetDialogString(859, "\x10""Sally\x10" "So are you gonna give us the Ancient\nGem or what?\x01");
	SetDialogString(860, "\x10""Vulkan\x10" "Hmm?\x01 Don't think I will give it away\nfor free.\x01");
	SetDialogString(861, "\x10""Sally\x10" "Ah, we gotta fight for it.\x03\x20 Got it,\nlet's duke it out.\x01");
	SetDialogString(862, "\x10""Vulkan\x10" "QUIET!\x03\x20 Do not speak for your leader!\x01\nRuby, so what is it gonna be?\x01");
	SetDialogString(863, "\x10""Ruby\x10" "I'll fight for the Ancient Gem.\x01");
	SetDialogString(864, "\x10""Vulkan\x10" "Hmm,\x03\x20 you're pretty aggressive for\nsomeone who looks like a scientist...\x01\nOkay,\x03\x20 if you're willing to battle\nme,\x03\x20 then...\x01");
	SetDialogString(865, "\x10""Vulkan\x10" "Don't hold anything back!!\x01");
	SetDialogString(866, "\x10""Vulkan\x10" "Well done.\x03\x20 You have proved yourself\nworthy.\x01 In fact, I am actually very\nimpressed with your feats.\x01");
	SetDialogString(867, "\x10""Vulkan\x10" "I've never seen this shape-shifting\nmagic before...\x01 And I think it also\ncopied my likeness and prowess...\x01\nQuite a dangerous weapon you've got\nthere, lady.\x01");
	SetDialogString(868, "\x10""Ruby\x10" "I've been gifted this power...\x01");
	SetDialogString(869, "\x10""Vulkan\x10" "...Ah, excuse me.\x01 The Ancient Gem is\nin the backyard,\x03\x20 just beyond me.\x01");
	SetDialogString(870, "\x10""Vulkan\x10" "You're free to take it as you please.\x01\nJust take good care of it,\x03\x20 it is\nan item of high rarity after all.\x01");
	
	SetDialogString(871, "\x10""Luna\x10" "...\x01Visitors here.\x01");
	SetDialogString(872, "\x10""Nate\x10" "Who are you?\x01");
	SetDialogString(873, "\x10""Ruby\x10" "I'm Ruby, and I'm looking for the\nAncient Gems.\x01 Do you have one of\nthese?\x01");
	SetDialogString(874, "\x10""Luna\x10" "...\x01Maybe I do.\x01 You want it?\x01");
	SetDialogString(875, "\x10""Ruby\x10" "Uh... yes?\x01");
	SetDialogString(876, "\x10""Luna\x10" "Then get lost.\x01");
	SetDialogString(877, "\x10""Don\x10" "I think we should capture them.\x01");
	SetDialogString(878, "\x10""Nate\x10" "Why?\x01");
	SetDialogString(879, "\x10""Don\x10" "They beat up some of our buddies,\nNate.\x01");
	SetDialogString(880, "\x10""Luna\x10" "Good idea.\x01 If you want the Ancient\nGem, you defeat us.\x01 Otherwise,\x03\x20 you\nwill be punished.\x01");
	SetDialogString(881, "\x10""Emmet\x10" "Ah, right, you criminals always\nresort to violence so quickly...\x01");
	SetDialogString(882, "\x10""Luna\x10" "Shut up...\x01");
	SetDialogString(883, "\x10""Nate\x10" "Let's fire at them!\x01");
	SetDialogString(884, "\x10""Don\x10" "But of course.\x01");
	SetDialogString(885, "\x10""Luna\x10" "...\x01");
	SetDialogString(886, "\x10""Sally\x10" "We won, now give us the gem.\x01");
	SetDialogString(887, "\x10""Luna\x10" ".\x03\x20.\x03\x20.\x03\x40I don't have it.\x01");
	SetDialogString(888, "\x10""Sally\x10" "Ugh...\x01");
	SetDialogString(889, "\x10""Luna\x10" "Volcano does.\x01");
	SetDialogString(890, "\x10""Ruby\x10" "Volcano?\x01");
	SetDialogString(891, "\x10""Don\x10" "Volcano Clan.\x01 It's a clan of ninjas.\x01\nTheir leader, Vulkan, is formidable.\x01");
	SetDialogString(892, "\x10""Nate\x10" "Yeah!\x03\x20 Very scary...\x03\x20 I wouldn't go\nnear him if I were you...\x01");
	SetDialogString(893, "\x10""Ruby\x10" "Where can I find him?\x01");
	SetDialogString(894, "\x10""Luna\x10" "I'll tell you.\x01 North of here.\x01\nIn the Volcano Dojo.\x01");
	SetDialogString(895, "\x10""Ruby\x10" "Oh, thanks, I'll go look there.\x01");
	SetDialogString(896, "\x10""Ruby\x10" "I won.\x03\x20 Where's the gem?\x01");
	SetDialogString(897, "\x10""Ruby\x10" "Yes.\x03\x20 Just get to the point and\nfight me already.\x01");
	SetDialogString(898, "\x10""Vulkan\x10" "Fight?\x01 Mmm, if you say so.\x01\nIf you're willing to battle me,\x03\x20\nthen...\x01");
	
	SetDialogString(901, "\x10""Luna\x10" "...\x01That thing you have there...\x01\nYou have it from Vulkan?\x01");
	SetDialogString(902, "\x10""Ruby\x10" "What?\x01");
	SetDialogString(903, "\x10""Luna\x10" "The blue gem.\x01 Give that to me\nplease.\x01");
	SetDialogString(904, "\x10""Ruby\x10" "I don't think I will, why?\x01");
	SetDialogString(905, "\x10""Luna\x10" "If you don't, you will be punished.\x01");
	SetDialogString(906, "\x10""Don\x10" "You made a big mistake coming here.\x01\nYou beat up our buddies, and you\nshall pay.\x01");
	SetDialogString(907, "\x10""Nate\x10" "That's right! That's your consequence\nfor stepping foot in Ozone Castle!\x01");
	SetDialogString(908, "\x10""Sally\x10" "Well, then punish us then.\x03\x20 I dare\nyou.\x03\x20 Do it.\x01");
	SetDialogString(909, "\x10""Luna\x10" "Don,\x03\x20 Nate,\x03\x20 get them.\x01");
	SetDialogString(910, "\x10""Luna\x10" "Impossible...\x01");
	SetDialogString(911, "\x10""Ruby\x10" "You have some good powers.\x01 Don't\nmind if I borrow them...\x01");
	SetDialogString(912, "\x10""Luna\x10" "What..?\x01 Fine, leave me alone.\x03\x20\nI don't need that blue gem.\x01");
	SetDialogString(913, "\x10""Emmet\x10" "Then why'd you ask in the first\nplace?\x01 Ah,\x03\x20 whatever.\x01");
	SetDialogString(914, "\x10""Ruby\x10" "Okay, let's go.\x01");
	
	SetDialogString(915, "\x11""Continue\nKill him\x11");
	SetDialogString(916, "\x10""Vulkan\x10" "You don't get it, child, do you?\x01\nYou already won,\x03\x20 so I suggest you\ntake what you've earned...\x01 Otherwise,\x03\x20\nif you try that dirty trick of\nyours again...\x01 you might not live\nlong enough to regret your decision.\x01");
	SetDialogString(917, "You have been poisoned.\x01");
	SetDialogString(918, "\x10""Vulkan\x10" "I warned you, you did not listen.\x03\x40\nThis is merely a self-defense\nact.\x01 I was not going to take\nany chances here, but here we are...\x01\nShould've known better.\x01");
	SetDialogString(919, "\x10""Vulkan\x10" "Good, now get that gem before\nI change my mind.\x01");
	
	SetDialogString(920, "\x10""Ruby\x10" "Hello, Dia.\x03\x20 I'm here to get the\nAncient Gem.\x01");
	SetDialogString(921, "\x10""Dia\x10" "Ancient Gem...?\x03\x20 What are you talking\nabout?\x01");
	SetDialogString(922, "\x10""Ruby\x10" "Hmmm...\x01");
	SetDialogString(923, "\x10""Ruby\x10" "You are in my way.\x01");
	SetDialogString(924, "\x10""Dia\x10" "You're not welcome to my room...\x01\nOh, and who are you?\x01");
	SetDialogString(925, "\x10""Ruby\x10" "I'm Ruby, and I am looking for\nAncient Gems.\x01 You have one in that\nroom behind you, right?\x01");
	SetDialogString(926, "\x10""Dia\x10" "I do...\x03\x20 But...\x03\x20 I can't let you\npass...\x01");
	SetDialogString(927, "\x10""Ruby\x10" "Okay, then I will get to the room\nthe hard way...\x01");
	SetDialogString(928, "\x10""Dia\x10" "Oh...\x01 you're gonna go outside and\nclimb up to the window?\x01");
	SetDialogString(929, "\x10""Ruby\x10" "What?\x03\x20 I will simply fight you.\x01");
	SetDialogString(930, "\x10""Dia\x10" "I see...\x01 If you really dare to\nfight me, then I shall burn you down.\x01");
	SetDialogString(931, "\x10""Dia\x10" "...\x01You are just like me.\x01");
	SetDialogString(932, "\x10""Ruby\x10" "You're down.\x01");
	SetDialogString(933, "\x10""Dia\x10" "No, I still won't let you pass.\x01\nOnly over my dead body...\x01");
	SetDialogString(934, "\x10""Ruby\x10" "Okay, if you say so...\x01 But I'm\nlooking for something else as\nwell...\x01");
	SetDialogString(935, "\x10""Dia\x10" "You've gotten enough...\x01 You should\nleave my house.\x01");
	SetDialogString(936, "\x10""Ruby\x10" "N-No, I was wondering if you'd\nbe...\x01 my friend...\x01");
	SetDialogString(937, "\x10""Dia\x10" "...?\x01 Why?\x01");
	SetDialogString(938, "\x10""Ruby\x10" "I've read the diary notes... You\nmust've had a rough life here...\x01");
	SetDialogString(939, "\x10""Ruby\x10" "I've had it a bit rough as well...\x01\nAnd I've been lonely lately just\nlike you...\x01");
	SetDialogString(940, "\x10""Dia\x10" "Oh...\x01 So you don't think I'm\nevil?\x01");
	SetDialogString(941, "\x10""Ruby\x10" "No, you deserved better...\x01 Anyway,\nwanna be my friend?\x01");
	SetDialogString(942, "\x10""Dia\x10" "Only if you promise to never leave\nme...\x03\x40 at least for long.\x01");
	SetDialogString(943, "\x10""Ruby\x10" "Okay, I promise that.\x01");
	SetDialogString(944, "\x10""Dia\x10" "You're kind of nice, actually...\x01");
	SetDialogString(945, "\x10""Dia\x10" "...\x01I'll let you go to my room...\x01\nJust don't break the promise, okay?\x01");
	SetDialogString(946, "\x10""Sally\x10" "Why are you befriending her??\x01");
	SetDialogString(947, "\x10""Ruby\x10" "I understand her pain...\x01 Simple as\nthat.\x01");
	SetDialogString(948, "\x10""Sally\x10" "Should've killed her to be honest...\x01\nEh, whatever...\x01 We can get the thing\nanyway I guess.\x01");
	SetDialogString(949, "\x10""Dia\x10" "Flame yourself!!\x01");
	
	SetDialogString(950, "\x10""Dia\x10" "Oh, also...\x03\x20 Take this.\x01");
	SetDialogString(951, "\x10""Dia\x10" "Thanks for understanding me...\x01");
	SetDialogString(952, "\x11""Accept her\nKill her\x11");
	SetDialogString(953, "\x10""Dia\x10" "Please come back soon, Ruby.\x01");
	SetDialogString(954, "\x10""Ruby\x10" "Dia...\x01");
	SetDialogString(955, "\x10""Dia\x10" "Huh?\x01");
	SetDialogString(956, "\x10""Ruby\x10" "I want you to take this as\nwell.\x01");
	SetDialogString(957, "\x10""Ruby\x10" "Look at this.\x01");
	SetDialogString(958, "\x10""Dia\x10" "What's this?\x01");
	
	SetDialogString(960, "\x10""Adios\x10" "Hm, the path's blocked for now.\x01\nDid you want to pass through?\x01");
	SetDialogString(961, "\x10""Ruby\x10" "It leads to Lapis Peaks, right?\x01");
	SetDialogString(962, "\x10""Adios\x10" "Of course.\x01 The blockade will last\nfor a few days I think,\x03\x20 but I\ncan let you pass through early...\x01");
	SetDialogString(963, "\x10""Ruby\x10" "Really?\x01");
	SetDialogString(964, "\x10""Adios\x10" "Hmm...\x03\x30 You see, I've been given a\nmission to stop the Razor Chaos Club,\x03\x20\none of the biggest piracy organizations\nin Gemia...\x01");
	SetDialogString(965, "\x10""Sally\x10" "Razor... Chaos?\x01 Isn't that...\x01");
	SetDialogString(966, "\x10""Adios\x10" "Yes, there's an anime about that...\x03\x20\nIt shows how strong Sanji actually is.\x01\nHis strength is the reason why I\nand Bulldog failed to stop these\npirates...\x01 and also why it hasn't\nbeen taken down for a while.\x01");
	SetDialogString(967, "\x10""Emmet\x10" "Do you think we can stop a huge\npiracy organization all by ourselves?\x01\nCouldn't you just call a hero or a\nMinistry agent to deal with those\ncriminals?\x01");
	SetDialogString(968, "\x10""Adios\x10" "That wouldn't be a bad idea,\x03\x20 but\na regular hero wouldn't do the job\nfor sure...\x01 Hiring a Superhero would\nbe too expensive and the Ministries\nwouldn't do anything about it.\x01");
	SetDialogString(969, "\x10""Sally\x10" "But piracy is cool, right?\x03\x20 Free video\ngames and-\x01");
	SetDialogString(970, "\x10""Emmet\x10" "Sally! Don't say that!\x03\x20 Especially not\nin front of an officer!\x01");
	SetDialogString(971, "\x10""Adios\x10" "Well,\x03\x20 I am not expecting you to\ntake down the Razor Chaos Club at\nall...\x01 But that's the only way you\ncan possibly pass through, so...\x01 just\nsaying in case someone's actually\ncapable of defeating Sanji and co.\x01");
	SetDialogString(972, "\x10""Adios\x10" "Unless you bribe me like $5000000...\x03\x20\nBut I'd recommend you just wait out.\x01");
	SetDialogString(973, "\x10""Adios\x10" "The path will be open for you the\nmoment Razor Chaos Club ceases to\noperate.\x01");
	SetDialogString(974, "\x10""Adios\x10" "Hm?\x11""Bribe $5000000\nLeave\x11");
	SetDialogString(975, "\x10""Adios\x10" "Hm...\x03\x20 interesting.\x01 You really have\nthat much money?\x01 Doubt.\x01 Seems\ntoo fishy if you ask.\x01");
	SetDialogString(976, "\x10""Ruby\x10" "Where is the Razor Chaos Club located\nat?\x01");
	SetDialogString(977, "\x10""Adios\x10" "In the upper left of this district.\x01\nYou need to look a bit for it, but\nit's not too hidden.\x01");
	
	SetDialogString(980, "\x10""Sally\x10" "Hey, Ruby, why didn't you bring\nNoah and Emmet to our team?\x01");
	SetDialogString(981, "\x10""Sally\x10" "Well... let me call Emmet real\nquick.\x01 If you don't mind having\nmore people...\x01");
	SetDialogString(982, "\x10""Sally\x10" "Hello, Emmet?\x03\x20 It's me.\x01");
	SetDialogString(983, "\x10""Sally\x10" "Ruby's looking for Ancient Gems or\nwhatever, wanna help us?\x01");
	SetDialogString(984, "\x10""Sally\x10" "Don't ask...\x01 Come to Bluesteel Town\nnow or I'll come to your house and\nkill you.\x01 Bye.\x01 Oh and bring Noah\nas well now bye\x01");
	SetDialogString(985, "\x10""Sally\x10" "Okay, they should be here in a\nmoment...\x01 Let's wait at the bus\nstop.\x01");
	SetDialogString(986, "\x10""Emmet\x10" "We're here.\x03\x20 Hello, Ruby.\x01");
	SetDialogString(987, "\x10""Noah\x10" "Hello.\x03\x20 You're looking for Ancient\nGems, right?\x01");
	SetDialogString(988, "\x10""Ruby\x10" "Yes.\x01");
	SetDialogString(989, "\x10""Emmet\x10" "Okay... what do we do now?\x01");
	SetDialogString(990, "\x10""Sally\x10" "Just keep quiet and follow Ruby.\x03\x20\nThat's all you have to do. Now\nlet's go, don't waste any more\ntime.\x01");
	
	SetDialogString(1000, "\x10""Noah\x10" "Wow, what a huge urban city...\x01");
	SetDialogString(1001, "\x10""Ruby\x10" "It is a city, indeed.\x01");
	SetDialogString(1002, "\x10""Sally\x10" "I always wanted to live in a city\nlike this...\x01 Dreams come true!\x03\x20 Sort\nof.\x01");
	SetDialogString(1003, "\x10""Emmet\x10" "Speaking of cities, how do you think\nDiego is doing in Sapphirepolis?\x01");
	SetDialogString(1004, "\x10""Ruby\x10" "Fine, I think.\x01");
	SetDialogString(1005, "\x10""Sally\x10" "We haven't seen Diego for years...\x01\nHe's probably forgotten about us\nand is swimming in cash like a busy\nbusinessman.\x01");
	SetDialogString(1006, "\x10""Emmet\x10" "No, he definitely haven't forgotten\nabout us...\x03\x20 I'm sure he misses us.\x01");
	SetDialogString(1007, "\x10""Ruby\x10" "We'll eventually reach Sapphirepolis,\nso we might see him very soon...\x01\nAnyway, our next Ancient Gem is\nlocated at Lapis Peaks.\x01");
	SetDialogString(1008, "\x10""Emmet\x10" "Lapis Peaks?\x03\x20 Hmm... that place is the\nhome of the Volcano Clan of ninjas\nand Ozone Mafia...\x01");
	SetDialogString(1009, "\x10""Sally\x10" "They won't stand a chance against\nus, right Ruby?\x01");
	SetDialogString(1010, "\x10""Ruby\x10" "Not sure, I haven't seen them in\naction yet...\x01");
	SetDialogString(1011, "\x10""Sally\x10" "Good point...\x03\x20 Anyway, let's continue\nour walk.\x01");
	
	SetDialogString(1020, "\x10""Adios\x10" "Hm, the path's blocked for now.\x01\nDid you want to pass through?\x01\nThe blockade will last for a few days,\x03\x20\nbut I can give you the pass early...\x01");
	SetDialogString(1021, "\x10""Adios\x10" "That's never happening though...\x01\nUnless you can defeat the Razor\nChaos Club all by yourself.\x01");
	SetDialogString(1022, "\x10""Adios\x10" "Hm?\x11""Fight\nLeave\x11");
	SetDialogString(1023, "\x10""Adios\x10" "Oh, so you want to FIGHT for the\npass, huh?\x01 Are you a hero or\nsomething?\x03\x20 'Cause you don't look\nstrong at all...\x01");
	SetDialogString(1024, "\x10""Adios\x10" "Oh well...\x03\x20 BULLDOG!\x01");
	SetDialogString(1025, "\x10""Bulldog\x10" "What's the matter, pal?\x01");
	SetDialogString(1026, "\x10""Adios\x10" "This girl insists on fighting us to\nget past the barrier.\x03\x20 Are you\nready to teach her a basic lesson?\x01");
	SetDialogString(1027, "\x10""Bulldog\x10" "Hmmm...\x03\x20 something's definitely off with\nher.\x01 Is she evil?\x01 Bah, who cares!\x03\x20\nYou!\x03\x20 Begone!\x03\x20 BEGONE, I said...\x01");
	SetDialogString(1028, "\x10""Adios\x10" "Interesting...\x03\x20 Very interesting...\x01\nBulldog, remove the barricade for\nthis gal.\x01");
	SetDialogString(1029, "\x10""Bulldog\x10" "Can't believe I lost to this...\x01\nFine!\x01");
	SetDialogString(1030, "\x10""Adios\x10" "You better be careful.\x03\x20 This little\n\"invention\" you have might be of\ninterest of corporations or even the\nMinistries...\x01");
	
	SetDialogString(1040, "\x10""???\x10" "That hero I'm talking about?\x03\x20 You're\nlooking at him right now.\x01\x10""Sanji\x10 My\nname's Sanji, who are you?\x01");
	SetDialogString(1041, "\x10""Ruby\x10" "Name's Ruby.\x03\x20 I am here to take\nyour club down.\x01");
	SetDialogString(1042, "\x10""Sanji\x10" "I'm impressed you managed to get\npast every other club member...\x01");
	SetDialogString(1043, "\x10""Sanji\x10" "But can you get past ME?\x01 You\nwill fall, just like every other\nvillain!!\x01 Show me what you're truly\ncapable of, Ruby!!\x01");
	
	SetDialogString(1050, "\x10""Luna\x10" "...\x01""A visitor.\x01");
	SetDialogString(1051, "\x10""Ruby\x10" "I'm Ruby, and I'm looking for the\nAncient Gems.\x01 I decided to pay\nyou a visit.\x01");
	SetDialogString(1052, "\x10""Luna\x10" "...\x01Okay.\x01 You think I have it?\x01");
	SetDialogString(1053, "\x10""Ruby\x10" "Dunno, I'm about to find out.\x01");
	SetDialogString(1054, "\x10""Don\x10" "What do you mean?\x03\x20 Are you going\nto attack us or what?\x01");
	SetDialogString(1055, "\x10""Ruby\x10" "Exactly, let's get to the point.\x01");
	SetDialogString(1056, "\x10""Ruby\x10" "Take this, please.\x01");
	SetDialogString(1057, "\x10""Luna\x10" "...\x01What-\x03\x20.\x03\x20.\x03\x20.\x03\x40 what did you do?\x01");
	SetDialogString(1058, "\x10""Luna\x10" "AAAAAAAAAAAAAAAAAAAAARGH!!!\x01\nAAAEEEEEEAAAEEEEEEEEEEEEEE!!!\x01\nH-HELP MEEEE-AAAAAAAAAHHHHH!!!\x01");
	SetDialogString(1059, "\x10""Nate\x10" "Luna!\x03\x20 No!\x01");
	SetDialogString(1060, "\x10""Nate\x10" "Are you okay?\x01");
	SetDialogString(1061, "\x10""Don\x10" "What did you do to her, you\nbastard?\x01");
	SetDialogString(1062, "\x10""Ruby\x10" "Oh, that was one of my special\ndarts.\x01 It specializes on making the\ntarget suffer as much as possible\x01\nbefore the inevitable death.\x01 At\nleast that's how it usually-\x01");
	SetDialogString(1063, "\x10""Nate\x10" "But Luna cannot die, she's immortal!\x01");
	SetDialogString(1064, "\x10""Don\x10" "So Luna is doomed to eternal suffering,\nam I right?\x01");
	SetDialogString(1065, "\x10""Ruby\x10" "I guess so.\x01");
	SetDialogString(1066, "\x10""Nate\x10" "That can't be true...\x03\x60 No...\x01");
	SetDialogString(1067, "\x10""Don\x10" "Ruby...\x03\x20 you bastard...\x01 Do you know what\nyou have just done?\x03\x20 Do you?\x01");
	SetDialogString(1068, "\x10""Ruby\x10" "That's just part of my ultimate\ngoal...\x01 (That was a good use of\nmy dart.)\x01");
	SetDialogString(1069, "\x10""Nate\x10" "Leave!\x01 Please, leave us alone!\x01");
	SetDialogString(1070, "\x10""Ruby\x10" "Okay, whatever you say.\x03\x20 I'm all out\nof darts anyway.\x01");
	SetDialogString(1071, "\x10""Luna\x10" "It hurts...\x03\x20 so much...\x01");
	
	SetDialogString(1080, "\x10""Lulu\x10" "Don't think you're going anywhere,\nRuby!!\x01");
	SetDialogString(1081, "\x10""Lulu\x10" "This time, I won't be defeated by\nsome falling piece of plastic...\x01\nNow you're in trouble!!\x01");
	SetDialogString(1082, "\x10""Lulu\x10" "Prepare for the finale!!\x01");
	SetDialogString(1083, "\x10""Lulu\x10" "N-no...\x03\x40 NNOOOOOOOOOOOOO!!!\x01\nNOOOOOOOOOOOOOOOOO!!!!\x01\nHow did you defeat me?!\x03\x20 HOW?!\x01");
	SetDialogString(1084, "\x10""Lulu\x10" "Screw you, Ruby!\x03\x20 Next time, we meet,\x03\x20\nyou will be SO dead...\x01 you will\nno longer exist!\x01 Sayonara!\x01");
	SetDialogString(1085, "\x10""Lulu\x10" "Oh, and this is the end of the\ndemo.\x01 You can't continue your\nadventure, but you can enjoy whatever\nyou haven't enjoyed in Lapis City...\x01\nWhat a loser!\x01");
	SetDialogString(1086, "This is the end of Chapter 3.\x01\nStay tuned for Rubindeavor's last\ntwo chapters!\x01");
	SetDialogString(1087, "\x10""Lulu\x10" "You really think you're smart,\nhuh?\x01 Well, this shall be your downfall!!\x01");
	
	
	
	SetDialogString(2000, "\x10""Border Officer\x10" "Do you want to go to Bluesteel Town?\x11Yes\nNo\x11");
	SetDialogString(2001, "\x10""Electra\x10" "I'm the bartender here and such.\x01\nWhat do you wanna order right\nnow?\x01");
	SetDialogString(2002, "Lisao is fast asleep.\x01");
	SetDialogString(2003, "\x10""Ray\x10" "I'm the supervisor of the club.\x01\nWe don't have any security guards,\nbut please don't cause trouble.\x01");
	SetDialogString(2004, "\x10""Border Officer\x10" "Do you want to go to Lapis City?\x11Yes\nNo\x11");
	SetDialogString(2005, "Do you want to push the sofa\nout of the way?\x11Yes\nNo\x11");
	SetDialogString(2006, "\x10""Lily\x10" "Hello! I'm selling my own home-made\nbread. Take a look!\x01");
	SetDialogString(2007, "\x10""Lily\x10" "Thanks, I hope you like it!\x01");
	SetDialogString(2008, "\x10""Lily\x10" "Oh, see you later then!\x01");
	SetDialogString(2009, "\x10""Lily\x10" "Hello! If you want to buy my\nstuff, stand in front of me, okay?\x01");
	SetDialogString(2010, "\x10""Cashier\x10" "Hello, anything you want to\nbuy?\x01");
	SetDialogString(2011, "\x10""Viola\x10" "Don't mind me. I'm trying to find\nsomething.\x01");
	SetDialogString(2012, "\x10""Leaf Crew\x10" "Good fight there, I'm not really\nfit for this kind of job...\x01\nOur leader Lisao is up ahead.\x01\nShe wields powerful vine magic.\nSo... be careful.\x01");
	SetDialogString(2013, "\x10""Leaf Crew\x10" "You talked it out with Lisao?\nShe's kinda scary and unstable,\nso I hope you didn't have any\ncomplications...\x01");
	SetDialogString(2014, "\x10""Leaf Crew\x10" "I have no intentions of fighting\nyou.\x01 Just don't cause any\ntrouble.\x01");
	SetDialogString(2015, "\x10""Leaf Crew\x10" "You beat up my friend, didn't\nyou?\x01");
	SetDialogString(2016, "\x10""Leaf Crew\x10" "...\x03\x20""Can't you say something at\nleast?\x01");
	SetDialogString(2017, "\x10""Leaf Crew\x10" "Lisao may be somewhat nice to\nus, but she's rather unstable.\x01\nThe recent events took away her\nrelatives, and now she's the only one\nleft in the family of a legendary\nSupernatural...\x01");
	SetDialogString(2018, "\x10""Leaf Crew\x10" "Now Lisao is trying to build a\npowerful group to get revenge\nor whatever she wants to do.\x01");
	SetDialogString(2019, "\x10""Leaf Crew\x10" "By the way, I'm willing to trade\nmy stuff with your money. What\ndo you say?\x01");
	SetDialogString(2020, "\x10""Border Officer\x10" "We're having brickwall issues.\x01\nPlease come back later.\x01");
	SetDialogString(2021, "\x10""Border Officer\x10" "It'll cost $30 per person for a\nbus to Bluesteel Town, ma'am.\x01 Buy\na ticket!\x11Yes\nNo\x11");
	SetDialogString(2022, "\x10""Border Officer\x10" "What are you doing here then?\x01");
	SetDialogString(2023, "\x10""Border Officer\x10" "Hurry up, the bus is leaving\nsoon!\x01");
	SetDialogString(2024, "\x10""Border Officer\x10" "Bluesteel Town is pretty fascinating.\nGood luck in your adventures!\x01");
	SetDialogString(2025, "\x10""Border Officer\x10" "You don't have enough money!\x01");
	SetDialogString(2026, "\x10""Ruby\x10" "(The bus is leaving soon.)\x01");
	SetDialogString(2027, "\x10""Border Officer\x10" "The bus hasn't arrived yet.\nYou'll have to wait for a bit.\x01");
	SetDialogString(2028, "\x10""Ruby\x10" "(I could go look for Sally while\nI still have time.)\x01");
	SetDialogString(2029, "The door is locked.\x01");
	SetDialogString(2030, "Which flower will you place?\x11Red\nCyan\nPink\nBlack\nNone\x11");
	SetDialogString(2031, "Victory!\x01");
	SetDialogString(2032, "Defeat!\x01");
	SetDialogString(2033, "Draw!\x01");
	SetDialogString(2034, "Stalemate!\x01");
	SetDialogString(2035, "RED - attacks straight\nDies on damage\x01");
	SetDialogString(2036, "CYAN - attacks diagonally\nTurns RED on damage\x01");
	SetDialogString(2037, "PINK - attacks straight and\nsideways\nTurns CYAN on damage\x01");
	SetDialogString(2038, "BLACK - does nothing\nTurns PINK on damage\x01");
	SetDialogString(2039, "A wax figure is blocking the way.\x01");
	SetDialogString(2040, "You unlocked the door with the\nSilver Key.\x01");
	SetDialogString(2041, "You unlocked the door with the\nGolden Key.\x01");
	SetDialogString(2042, "You unlocked the door with the\nDiamond Key.\x01");
	SetDialogString(2043, "\x10""!!!!!\x10" "This one might be tough. Did you\nwant the answer to be revealed?\n\x11Yes\nNo\x11");
	SetDialogString(2044, "\x10""!!!!!\x10" "Red > Cyan > Black > Red\x01");
	SetDialogString(2045, "There's a torn note on the floor.\x01");
	SetDialogString(2046, "\"My sister really liked to play\ngames... So I've made up a game\nI thought she would like: 'Flower\nWar'.\x01 Rules were simple, flowers\nof one side attacked the flowers\nof the other side each turn.\x01 If\nsomeone's flowers all die, they\nlose.\"\x01");
	SetDialogString(2047, "\"I felt bad winning against my\nsister, and I didn't want to throw\nthe game either, so...\x01 I was trying\nto DRAW the game instead.\"\x01");
	SetDialogString(2048, "\"Dia's just not the same as\nbefore... I don't know what's\nhappening.\x01 My parents told me that\nthe curse is beginning... What could\nit even mean?\"\x01");
	SetDialogString(2049, "\"They said I'm behaving worse and\nworse because of Dia... I am\nnot buying that at all.\"\x01");
	SetDialogString(2050, "\"I feel more and more anxious.\x01\nWhat is going to even happen?\nI'm clueless.\"\x01");
	SetDialogString(2051, "(The handwriting is different from\nother notes.)\x01\n\"We will burn Dia to ashes.\nDia is non-human and has no human\nrights!\x01 Nobody will remember her\nexistence, not even me, Diana.\x01\nGlory to the Mints family!\"\x01");
	SetDialogString(2052, "For some reason,\x03\x20 a brickwall that\nis totally not out-of-place is\nblocking the path.\x01");
	SetDialogString(2053, "\x10""Police\x10" "We took care of the brick wall.\x01\nWe don't know where these come\nfrom, though, but we are investigating\nit.\x01");
	SetDialogString(2054, "\x10""Mr. Coppers\x10" "I'm looking out for any members\nof the Leaf Crew. Be careful!\x01");
	SetDialogString(2055, "\x10""Mr. Coppers\x10" "You really did take care of the\nLeaf Crew! I'm super impressed!\x01 Take\nthe reward.\x01");
	SetDialogString(2056, "You got $300.\x01");
	SetDialogString(2057, "\x10""Emmet\x10" "Uhh, that's not a lot of money.\x01\nEspecially from an official bounty\nfrom the police.\x01");
	SetDialogString(2058, "\x10""Mr. Coppers\x10" "I never said it was an official\nbounty, did I? And $300 is already\nexceeding my monthly salary...\x01 So take\nit or leave it, will you?\x01");
	SetDialogString(2059, "\x10""Mr. Coppers\x10" "I'm doing my regular police work.\x01\nDon't be distracting me.\x01");
	SetDialogString(2060, "\x10""Farmer\x10" "Ever landed a CRITICAL hit on your\nfoe?\x01 It happens when you land a\nhit just after they let their guard\ndown.\x01 It's really difficult to time\nit correctly though, and it won't work\nif the foe is much faster than you.\x01\nKeep that in mind! I'm talking from\nmy experience.\x01");
	SetDialogString(2061, "\x10""River\x10" "I'm chillin' here everyday.\x01 Ever\nwondered what lies beyond the borders\nof Gemia?\x01 Just a random thought.\x01");
	SetDialogString(2062, "\x10""Woman\x10" "I hope I can get everything in time...\x01\nAnd I hope I won't run into Vandals...\x01");
	SetDialogString(2063, "\x10""Vandal\x10" "Did you know that having higher speed\nthan your enemy's allows you to not\nonly act first...\x01 but also deal extra\ndamage and block attacks more easily?\x01\nHehehe, take that hint, you fool!\x01\nGirls, sick 'em!\x01");
	SetDialogString(2064, "\x10""Ayaka\x10" "Hello! I'm Ayaka. I'm selling some\ncool stuff, with a special discount.\x01\nWanna take a look?\x01");
	SetDialogString(2065, "\x10""Ayaka\x10" "Have fun!\x01");
	SetDialogString(2066, "\x10""Kevin\x10" "Hello. My sister is cooking right\nnow.\x01");
	SetDialogString(2067, "\x10""Viola\x10" "Oh, hello. I'm cooking right now.\x01");
	SetDialogString(2068, "\x10""Ruby\x10" "(Hmm...\x03\x30 it looks like the game\nis speedrunning itself.)\x01");
	SetDialogString(2069, "\x10""Ruby\x10" "(I should ask Noah to join me\nfirst.)\x01");
	SetDialogString(2070, "\x10""Ruby\x10" "(Uh oh, it appears that I can't\nrefuse this \"new party member\" offer.\x01\nNot because I don't want to, but\nbecause this is the side effect of\nmy special \"protagonist\" labcoat...)\x01");
	SetDialogString(2071, "\x10""Emmet\x10" "But thou must!\x01");
	SetDialogString(2072, "\x10""Electra\x10" "I'm not sure if you're supposed to\nbe here or not.\x01 Jackie is certainly\na person you wouldn't wanna mess\nwith.\x01");
	SetDialogString(2073, "\x10""Lulu\x10" "You little piece of shit... I\nam going to KILL you for that\nhandshake trick!!\x01");
	SetDialogString(2074, "\x10""Lulu\x10" "Oh my GOD!! How did I fall for\nthat AGAIN?\x01");
	SetDialogString(2075, "The door cannot be opened without\na membership card.\x01");
	SetDialogString(2076, "\x10""Cindy\x10" "Hello! Wanna buy some drinks\nand meals?\x01");
	SetDialogString(2077, "\x10""Cindy\x10" "Hello! I'm doing some bartender\nwork here. I'd ask if you wanna\norder meals and drinks, but...\x01\nUnfortunately...\x01");
	SetDialogString(2078, "\x10""Cindy\x10" "Hahahahahahahahahahaha!\x01\nHahahahahahahahahahaha!\x01\nHahahahahaha-hehe-hahahaha!\x01");
	SetDialogString(2079, "\x10""Emmet\x10" "Wh-what are you laughing at?\x01");
	SetDialogString(2080, "\x10""Cindy\x10" "Oh, it's simple you pitiful beings.\x01\nLook at you!!\x03\x20 You look all beat up.\x01\nYou made a big mistake coming\nhere.\x01");
	SetDialogString(2081, "\x10""Sally\x10" "Hmm? We can take you on.\x01");
	SetDialogString(2082, "\x10""Cindy\x10" "And I say \"No\".\x01 Consider\nyourself defeated.\x01 Tee-hee!\x01\nBye!\x01");
	SetDialogString(2083, "\x10""Cindy\x10" "...\x01");
	SetDialogString(2084, "\x10""Cindy\x10" "Don't hurt me, please.\x01\nI didn't want you dead, I\njust...\x01");
	SetDialogString(2085, "\x10""Cindy\x10" "I wanted to have a little fun.\x01");
	SetDialogString(2086, "\x10""Emmet\x10" "Those wicked spells you casted\non us could've killed us, you know.\x01\nI think you owe us a special\napology. What do you think, Cindy?\x01");
	SetDialogString(2087, "\x10""Cindy\x10" "Uhh...\x03\x20 umm...\x03\x20 I'll give you a 75%\ndiscount!\x03\x20 Is that good enough?\x01");
	SetDialogString(2088, "\x10""Emmet\x10" "75% discount? That's all you can\noffer?\x01");
	SetDialogString(2089, "\x10""Ruby\x10" "I think that's good enough.\x01");
	SetDialogString(2090, "\x10""Cindy\x10" "Okay... I'll give you $500 as\nwell.\x01");
	SetDialogString(2091, "\x10""Cindy\x10" "I sell good drinks and stuff.\x01\nDon't hesitate! I won't bite...\x03\x20\nanymore.\x01");
	SetDialogString(2092, "You got $500.\x01");
	SetDialogString(2093, "\x10""Receptionist\x10" "Welcome to Azure Top Hotel!\x01 Do\nyou want to reserve a room here?\nIt'll be $160 for you all.\x11Yes\nNo\x11");
	SetDialogString(2094, "\x10""Receptionist\x10" "The bellboy will guide you towards\nyour room. Enjoy your stay!\x01");
	SetDialogString(2095, "\x10""Bellboy\x10" "Greetings, ma'am. Your room is\n1-2, which is on the second floor.\x01\nI will be standing next to your\nroom.\x01");
	SetDialogString(2096, "\x10""Bellboy\x10" "This is the room you reserved,\nma'am. I think you will enjoy\nyour stay here.\x01 If you wanna order\nfood or ask questions, drop by on\nthe first floor, I will be\nthere most of the time.\x01");
	SetDialogString(2097, "\x10""Bellboy\x10" "Have a good rest of your day,\nsirs and ma'ams.\x01");
	SetDialogString(2098, "Where do you want to go?\x11""Floor 1\nFloor 2\nFloor 3\x11");
	SetDialogString(2099, "\x10""Receptionist\x10" "Wait... Sorry, but you are short on\nmoney.\x01");
	SetDialogString(2100, "You're already there.\x01");
	SetDialogString(2101, "\x10""Secretary\x10" "Sorry for bothering you ma'am,\nbut... uh... Can I ask you\nsomething?\x01");
	SetDialogString(2102, "\x10""Ruby\x10" "...What is it?\x01");
	SetDialogString(2103, "\x10""Secretary\x10" "Are you.\x03\x20.\x03\x20.\x03\x40 good at computers?\x01");
	SetDialogString(2104, "\x10""Ruby\x10" "Hmmm... you need a computer\nlesson or?\x01");
	SetDialogString(2105, "\x10""Secretary\x10" "...\x01");
	SetDialogString(2106, "\x10""Secretary\x10" "I mean, if you can... can you\nfix a problem in one of our\ncomputers?\x01");
	SetDialogString(2107, "\x10""Ruby\x10" "I think I can.\x01");
	SetDialogString(2108, "\x10""Secretary\x10" "Really? Cool! Follow me, Miss Ruby.\x01");
	SetDialogString(2109, "\x10""Sally\x10" "We can stay here, right, Ruby?\x01");
	SetDialogString(2110, "\x10""Ruby\x10" "Of course, why wouldn't I let\nyou?\x01");
	SetDialogString(2111, "\x10""Secretary\x10" "You're coming, Miss Ruby?\x01 Follow\nme to the Executive's room.\x01");
	SetDialogString(2112, "\x10""Secretary\x10" "To the First Floor\x01\nWe Go\x01");
	SetDialogString(2113, "You unlocked the door.\x01");
	SetDialogString(2114, "\x10""Ruby\x10" "(I should ask Noah to join me\nfirst.)\x01\n\x03\x40(Or maybe not.)\x11""Find Noah\nContinue anyway\x11");
	SetDialogString(2115, "\x10""Ruby\x10" "(I need to get the Ancient Gem\nfirst.)\x01");
	SetDialogString(2116, "\x10""Border Officer\x10" "It'll cost $30 per person for a\nbus to Bluesteel Town, ma'am.\x01 Buy\na ticket!\x01");
	SetDialogString(2117, "\x10""Ruby\x10" "(I probably should take Noah and\nEmmet with me first.)\x01");
	SetDialogString(2118, "\x8f\x01WARNING!\x03\x40 The adventure onwards will\n\x8f\x01""be brutal and dark if you go alone.\x01\nHaving allies will be more important\nthan ever.\x01\nWhat will you do?\x11Look for friends\nContinue anyway\x11");
	SetDialogString(2119, "There is no going back.\x01");
	SetDialogString(2120, "Glass of orange juice.\x01");
	SetDialogString(2121, "Glass of orange juice.\x11""Break it\nLeave it\x11");
	SetDialogString(2122, "Ruby has become stronger.\x01\nHer stats have improved.\x01");
	SetDialogString(2123, "A pizza slice that Perry has made\nfor you.\x11Take\nThrow away\nLeave\x11");
	SetDialogString(2124, "Perry is down,\x03\x20 maybe dead.\x01");
	SetDialogString(2125, "\x10""Dia\x10" "Wanna play Flower War?\x11Yes\nNo\x11");
	SetDialogString(2126, "\x10""Dia\x10" "...Here.\x01");
	SetDialogString(2127, "\x10""Brook\x10" "You're too reliant on tech and\nmagic...\x01 But can you beat me in\na game of strength?\x01 You and I\nbet $50 and the winner wins it all.\x11Sure\nNope\x11");
	SetDialogString(2128, "\x10""Brook\x10" "Good choice.\x03\x20 You saved yourself\nsome money.\x01 And pride.\x01");
	SetDialogString(2129, "\x10""Brook\x10" "Oh, for sure?\x03\x20 Then let's give\nTom $50 each.\x01");
	SetDialogString(2130, "\x10""Brook\x10" "Alright, punch the punch!\x01");
	SetDialogString(2131, "\x10""Brook\x10" "Well, I didn't expect much from\na glasses girl...\x01 Thanks for the\ndonation!\x01");
	SetDialogString(2132, "\x10""Brook\x10" "Whoa... you're stronger than I\nexpected...\x01 Let's call it a draw.\x01");
	SetDialogString(2133, "\x10""Brook\x10" "Yikes!\x01");
	SetDialogString(2134, "\x10""Brook\x10" "How in the world?!\x01 Did you take\nvitamins before this?\x01 Well, guess I\nwill take the loss.\x01");
	SetDialogString(2135, "\x10""Brook\x10" "What's up? You wanna test your\nstrength again?\x11Sure\nNope\x11");
	SetDialogString(2136, "\x10""Brook\x10" "I'm just gonna win again, but\nI appreciate your selflessness.\x01");
	SetDialogString(2137, "\x10""Brook\x10" "Hmm... you want to go in debt?\x01\nNope.\x03\x20 Get a bit of cash first.\x01");
	SetDialogString(2138, "\x10""Brook\x10" "Nah, I'm not gonna steal from\nyou anymore.\x01 Buy yourself some\nmilkshake instead.\x01");
	SetDialogString(2139, "\x10""Brook\x10" "No rematch, I'm convinced you'll\njust beat me again.\x01");
	SetDialogString(2140, "\x10""Tom\x10" "If you're looking for Sanji, he's\nsomewhere in the second floor.\x01\nBeneath the disco room.\x01");
	SetDialogString(2141, "You got $100.\x01");
	SetDialogString(2142, "You got $50 back.\x01");
	SetDialogString(2143, "\x10""Brook\x10" "What's up? I'm not in the mood for\nstrength games anymore.\x01");
	SetDialogString(2144, "\x10""Pirate Captain\x10" "Hm?\x03\x40 You're not here to dance,\nare you?\x01 Too bad!\x03\x20 You'll have to dance\nreal hard to get past me.\x01 Get ready-\x01");
	SetDialogString(2145, "\x10""Kelly\x10" "Uh-oh, they're here!!\x01");
	SetDialogString(2146, "\x10""Neveah\x10" "Hey, we ought to help the old\nman out,\x03\x20 don't you think so?\x01");
	SetDialogString(2147, "\x10""Pirate Captain\x10" "What are you doing here?\x01 Get\nback to your post, ladies!\x01");
	SetDialogString(2148, "\x10""Neveah\x10" "...\x01");
	SetDialogString(2149, "\x10""Kelly\x10" "How rude, old geezer!\x01 We just wanted\nto help you out, and this is how\nyou treat us?\x01");
	SetDialogString(2150, "\x10""Pirate Captain\x10" "B-but you should be guarding the\nentrance-\x01");
	SetDialogString(2151, "\x10""Kelly\x10" "Our job is not to stand over the\nentrance like statues...\x01 It's to kick\nout any unwanted faces!\x03\x20 Get it?\x01\nNow let us join your party.\x01");
	SetDialogString(2152, "\x10""Pirate Captain\x10" "...I was going to bring a few henchmen\nalongside me, but...\x01 Fine! Just don't\nmess this up.\x01");
	SetDialogString(2153, "\x10""Neveah\x10" "Haha, let's see what you've got.\x01");
	SetDialogString(2154, "Neveah uses Hyperenergizer!\x02");
	SetDialogString(2155, "\x10""Neveah\x10" "You're gonna force me to use\nthis...\x03\x40 aren't you?\x01 Ah screw it!\x01");
	SetDialogString(2156, "\x10""Neveah\x10" "LET'S F***ING GO!!!\x03\x30 You won't land a\nhit on me anymore!!\x01");
	SetDialogString(2157, "\x10""Sally\x10" "That's it?\x01 Time to SMACK the bitch\nDOWN!!\x01");
	SetDialogString(2158, "\x10""Pirate Captain\x10" "Damn it!\x01");
	SetDialogString(2159, "\x10""Kelly\x10" "...Ugh...\x01 Neveah, let's just go back.\x01");
	SetDialogString(2160, "\x10""Pirate Captain\x10" "Guess I can't stop you from entering\nSanji's room.\x01 He is truly a warrior to\nbe feared,\x03\x40 and the anime does not\nexaggerate his skills that much.\x01\nContinue at your own risk, foes.\x01");
	SetDialogString(2161, "\x10""Pirate Captain\x10" "If you want any advice from me...\x01\nJust be prepared for his deadly\nRazor Chaos phase.\x01 Sanji will lose\nall of his blood to ensure his foes\nare defeated...\x01");
	SetDialogString(2162, "\x10""Pirate Captain\x10" "Hmph...\x03\x40 You all seem to possess\nsome sort of dark magic.\x01 Or perhaps\nyou are undercover agents of a\nMinistry,\x03\x20 messing around in this club?\x01");
	SetDialogString(2163, "\x10""Pirate\x10" "Hey,\x03\x20 what is 1+1?\x11""2\n3\nIgnore\x11");
	SetDialogString(2164, "\x10""Pirate\x10" "Everyone knows 1+1 is 2.\x01\nEven cats and plants do!\x01");
	SetDialogString(2165, "\x10""Secretary\x10" "So your name's actually Ruby?\x01\nI was just taking a wild guess...\x01");
	SetDialogString(2166, "\x10""Secretary\x10" "Right, there's the computer that\nis broken.\x03\x20 It crashes very often\nlately.\x01 If you can find and fix\nthe issue,\x03\x20 I'll be in your debt.\x01\nThanks!\x01");
	SetDialogString(2167, "\x10""Ruby\x10" "(Okay...\x03\20 Already see the problem.\x01\nIt's using Glasspane 22.)\x01");
	SetDialogString(2168, "\x10""Ruby\x10" "(Stupid ad-fill of an operating\nsystem...)\x01");
	SetDialogString(2169, "\x10""Ruby\x10" "(Oh, I forgot there are ads popping\nup in diagnostic mode...\x01 What a\nload of crap.)\x01");
	SetDialogString(2170, "\x10""Ruby\x10" "(It triple-faulted...\x03\x20 Didn't even show\nthe blue screen...\x01 Working as intended\nby N-Soft!)\x01");
	SetDialogString(2171, "\x10""Ruby\x10" "(Well, lemme check the case.)\x01");
	SetDialogString(2172, "\x10""Ruby\x10" "(What happened?\x01 Did I get transported\ninto another world?\x01 Maybe I'm\nhallucinating?)\x01");
	SetDialogString(2173, "\x10""Ruby\x10" "(Interesting. Time to explore.)\x01");
	SetDialogString(2174, "This door has 2 keyholes in it\nand is locked.\x01");
	SetDialogString(2175, "\x10""Receptionist\x10" "Welcome to Azure Top Hotel!\x01 Do\nyou want to reserve a room here?\x01");
	SetDialogString(2176, "\x10""Ruby\x10" "Maybe later.\x01");
	SetDialogString(2177, "\x10""Receptionist\x10" "I hope you are enjoying your time\nhere!\x01");
	SetDialogString(2178, "\x10""Bellboy\x10" "Hello, ma'am.\x03\x20 You wanted to order\nsomething?\x01");
	SetDialogString(2179, "\x10""Hotel Boss\x10" "Hm?\x03\x20 My computer's working fine.\x01\nThanks for your assistance.\x01");
	SetDialogString(2180, "\x10""Secretary\x10" "Glad you're doing fine.\x01 I was worried\nthat something bad happened to you.\x01");
	SetDialogString(2181, "\x10""Brian\x10" "Hold on, let me find my taser\nfirst...\x01");
	SetDialogString(2182, "\x10""Brian\x10" "Found it, now we can proceed.\x01");
	SetDialogString(2183, "\x10""???\x10" "...\x03\x30Where did the capsule go?\x01");
	SetDialogString(2184, "You opened the briefcase.\x01");
	SetDialogString(2185, "\x10""Brian\x10" "Hey.\x01 You have the Heal Capsule...\x03\x20\nGive it back or I have to use\nmy taser.\x11""Fight\nGive it up\x11");
	SetDialogString(2186, "\x10""Brian\x10" "Nice,\x03\x20 farewell.\x01");
	SetDialogString(2187, "\x10""Brian\x10" "F-fine, you can k-keep it...\x03\x20 Haha.\x01");
	SetDialogString(2188, "You gave up the \x80\x07.\x01");
	SetDialogString(2189, "The briefcase is empty.\x01");
	SetDialogString(2190, "\x10""Brian\x10" "You lost it...\x01 Well...\x01");
	SetDialogString(2191, "\x10""Brian\x10" "O-okay, I'm in the wrong.\x01 L-let's\npart ways, haha.\x01");
	SetDialogString(2192, "\x10""Ozone Mafia\x10" "You want to enter the Ozone Castle?\x03\x20\nThen answer my questions correctly.\x01");
	SetDialogString(2193, "\x10""Ozone Mafia\x10" "First question.\x01\nWho is the boss of the Ozone\nMafia?\x11""Ozone\nSanji\nLuna\nLulu\nKalo\x11");
	SetDialogString(2194, "\x10""Ozone Mafia\x10" "Second question.\x01\nWhat is the model of the gun\nI'm holding right now?\x11""H-O2\nNe-28\nLuna's Custom\nO-H47\x11");
	SetDialogString(2195, "\x10""Ozone Mafia\x10" "Third question.\x01\nWhat is the highest ranking in\nOzone Mafia's hierarchy?\x11""S\nBoss\nPresident\nLeader\nLuna\nThere is none\x11");
	SetDialogString(2196, "\x10""Ozone Mafia\x10" "Fourth question.\x01\nName our badge.\x11""All For Ozone\nOzone Mania\nPower Rush\nMOGEKO\nOzone Danger\nWhat badge?\x11");
	SetDialogString(2197, "\x10""Ozone Mafia\x10" "Fifth question.\x01\nWhat keychain does Luna have?\x11""Gold keychain\nRazor Chaos brand\nPlastic noodles\nDuncan made\nStinkbugs\nSilly BBQ\x11");
	SetDialogString(2198, "\x10""Ozone Mafia\x10" "Last question.\x01\nWho is responsible for placing the\nladders?\x11""Duncan\nVulkan\nDuster\nLuna\nNubert\nNorimaro\x11");
	SetDialogString(2199, "\x10""Ozone Mafia\x10" "All of your answers were...\x03\x40\ncorrect!\x01 Now...\x01 can you answer the\nactual last question?\x01");
	SetDialogString(2200, "\x10""Ozone Mafia\x10" "Who is?\x11""Zacharie\nLuna\nHungary\nLewis\nCheetahmen\nIb\nKurtis\nDoshi\nUpdog\x11");
	SetDialogString(2201, "\x10""Ozone Mafia\x10" "Oh wow...\x01 Well...\x01 Guess we have\nto...\x01");
	SetDialogString(2202, "\x10""Ozone Mafia\x10" "Open!\x01");
	SetDialogString(2203, "\x10""Ozone Mafia\x10" "Open the fire!\x03\x20 You are completely\nwrong!\x01");
	SetDialogString(2204, "\x10""Ozone Mafia\x10" "All of your answers were...\x03\x40\nincorrect.\x01");
	SetDialogString(2205, "\x10""Ozone Mafia\x10" "All of your answers were...\x03\x40\nI mean, not all of your answers\nwere correct.\x01");
	SetDialogString(2206, "\x10""Ozone Mafia\x10" "We are occupying this area.\x01 Ozone\nMafia does not waste time - bad actors\nwill be shot from H-O2 immediately.\x01");
	SetDialogString(2207, "\x10""Ozone Mafia\x10" "Luna, our boss, does not enforce\ninequality.\x01 We don't get promoted,\x03\x20\nwe simply gain more trust.\x01");
	SetDialogString(2208, "\x10""Ninja\x10" "Psst...\x03\x20 I can tell you valuable\ninformation about Ozone Mafia.\x01 You\ngive me only $200, and I tell you a\nsecret.\x11Yes\nNo\x11");
	SetDialogString(2209, "\x10""Ninja\x10" "Okay...\x01 You know Luna, the leader?\x01\nShe puts her keys in a ring of\nplastic noodles.\x01 Was that helpful?\x01");
	SetDialogString(2210, "\x10""Sally\x10" "(You f**kin' kidding me?\x03\x20 HOW IS THAT\nIN ANY WAY AND CIRCLE OF HELL\nHELPFUL>!)\x01");
	SetDialogString(2211, "\x10""Ozone Mafia\x10" "Don't think you're climbing up\nhere!\x01"); //SetDialogString(2211, "\x10""Ozone Mafia\x10" "Don't think you're climbing up\nhere!\x01 Duncan made these for US,\x03\x40\nnot YOU!\x01");
	SetDialogString(2212, "\x10""Ozone Mafia\x10" "What the-\x01");
	SetDialogString(2213, "\x10""Ozone Mafia\x10" "Duncan should start placing stairs\ninstead of ladders.\x01 Or elevators, even!\x01");
	SetDialogString(2214, "\x10""Ruby\x10" "(I don't have enough money.)\x01");
	SetDialogString(2215, "\x10""Don\x10" "What?\x03\x20 You're gonna ask for money\nor other valuable stuff?\x01");
	SetDialogString(2216, "\x10""Nate\x10" "Ozone will always live on, just\nlike Luna!\x01");
	SetDialogString(2217, "\x10""Ruby\x10" "(I need to find the taser of\ncourse...)\x01");
	SetDialogString(2218, "\x10""Noah\x10" "N-no! My weapon!\x01");
	SetDialogString(2219, "\x10""Noah\x10" "Wh-where is my taser?\x01");
	SetDialogString(2220, "\x10""Emmet\x10" "Oops, I think I lost my weapon...\x01");
	SetDialogString(2221, "\x10""Emmet\x10" "Wait, where is my weapon?\x01");
	SetDialogString(2222, "\x10""Sally\x10" "How in the hell I don't have a\ntaser in my hand?\x01");
	SetDialogString(2223, "\x10""Sally\x10" "Sh*t, lemme find the frickin' taser\nfirst!\x01");
	SetDialogString(2224, "A card slot.\x01");
	SetDialogString(2225, "Use the Mystery Card?\x11Yes\nNo\x11");
	SetDialogString(2226, "\x10""???\x10" "...\x01");
	SetDialogString(2227, "\x10""???\x10" "You released me?\x03\x20 Thanks.\x01\x10Nekin\x10 I'm\nNekin, and you are?\x01");
	SetDialogString(2228, "\x10""Ruby\x10" "Ruby.\x01");
	SetDialogString(2229, "\x10""Emmet\x10" "Why were you locked in there?\x01");
	SetDialogString(2230, "\x10""Nekin\x10" "I...\x03\x20 I don't know...\x01\nI don't remember anything at all...\x01");
	SetDialogString(2231, "\x10""Nekin\x10" "But I belong to a royal family...\x01\nA family that used to rule a whole\ncountry...\x01");
	SetDialogString(2232, "\x10""Sally\x10" "Oh, an ancestor of yours has ruled\nGemia?\x01");
	SetDialogString(2233, "\x10""Nekin\x10" "Exactly...\x03\x20 It was centuries long\nago.\x01");
	SetDialogString(2234, "\x10""Ruby\x10" "I'm not too fond of Gemia at it's\ncurrent state...\x01");
	SetDialogString(2235, "\x10""Nekin\x10" "Maybe I can help..?\x01");
	SetDialogString(2236, "\x10""Nekin\x10" "I can help you leave Gemia...\x01");
	SetDialogString(2237, "\x10""Ruby\x10" "How exactly?\x01");
	SetDialogString(2238, "\x10""Ruby\x10" "Oh.\x01");
	SetDialogString(2239, "\x10""Sally\x10" "Knew you were a sicko.\x01 Well, ya\nknow what to do.\x01");
	SetDialogString(2240, "\x10""Nekin\x10" "I need your shape-shifting thingy,\nRuby...\x01 I'd be able to rule all\nof Gemia with this.\x01 Stay still,\x03\x20\nwill you?\x01");
	SetDialogString(2241, "\x10""Ruby\x10" "How did you know that?\x01");
	SetDialogString(2242, "\x10""Nekin\x10" "I won't tell you anything.\x01\nNow's your chance to escape Gemia!!\x01");
	SetDialogString(2243, "\x10""Nekin\x10" "Oww...\x01");
	SetDialogString(2244, "\x10""Emmet\x10" "What a crazy person...\x03\x20 she almost\nkilled us...\x01");
	SetDialogString(2245, "\x10""Noah\x10" "Indeed...\x01");
	SetDialogString(2246, "\x10""Sally\x10" "So you want me to kill her?\x01");
	SetDialogString(2247, "\x10""Emmet\x10" "No...\x01");
	SetDialogString(2248, "\x10""Nekin\x10" "Goodbye...\x01");
	SetDialogString(2249, "\x10""Ruby\x10" "Well... at least we got something\nout of this fight.\x01");
	SetDialogString(2250, "\x10""Noah\x10" "Nekin's armor and skills?\x01");
	SetDialogString(2251, "\x10""Ruby\x10" "Yeah.\x03\x20 Might help us out a lot.\x01");
	SetDialogString(2252, "You unlocked the door with the\nMystery Key.\x01");
	SetDialogString(2253, "A naive corpse of Dia.\x01");
	SetDialogString(2254, "A tree with Aqua Berries. Take one?\x11Yes\nNo\x11");
	SetDialogString(2255, "\x10""Bulldog\x10" "Do not cross the barrier!\x03\x20\nOr else you'll be torn apart!\x01");
	SetDialogString(2256, "\x10""Bulldog\x10" "Talk to Adios on the other side if\nyou need to pass through!\x03\x20 He's\nin a red suit and wears a cowboy\nhat.\x03\x20 Got it?\x01");
	SetDialogString(2257, "\x10""Bulldog\x10" "Only you can pass.\x03\x20 Nobody else!\x01");
	SetDialogString(2258, "\x10""Adios\x10" "You made quite a show for yourself,\x03\x20\ndidn't you?\x01 There are already news\nabout your involvement in the Razor\nChaos Club shutdown.\x01");
	SetDialogString(2259, "\x10""Adios\x10" "You can pass, in case the lack of\nbarricade hasn't made it clear...\x01");
	SetDialogString(2260, "\x10""Ruby\x10" "(No.)\x01");
	SetDialogString(2261, "\x10""Border Officer\x10" "The ship stops on Lapis City.\x01 It\nwill cost $70 for each person.\x03\x20 Do\nyou want to buy a ticket to Lapis\nCity?\x11Yes\nNo\x11");
	SetDialogString(2262, "\x10""Border Officer\x10" "The ship will leave soon. All aboard\nthe ship!\x01");
	SetDialogString(2263, "\x10""Border Officer\x10" "The river is the border between\nBluesteel Town and Lapis City.\x01 There\nis public transport in form of ships.\x01");
	SetDialogString(2264, "\x10""Border Officer\x10" "The ship to Lapis City will arrive\nsoon.\x01");
	SetDialogString(2265, "\x10""Border Officer\x10" "You don't have money, ma'am...\x01");
	SetDialogString(2266, "\x10""Border Officer\x10" "Welcome to Lapis City!\x01");
	SetDialogString(2267, "\x10""Secretary\x10" "Don't mind me.\x01");
	SetDialogString(2268, "\x10""Hotel Boss\x10" "I'm busy, I don't have time for\nquestions!\x01");
	SetDialogString(2269, "\x10""Secretary\x10" "Thanks for fixing the computers!\x03\x20\nOr at least I think you fixed them...\x01\nThey started working again.\x01");
	SetDialogString(2270, "\x10""Cindy\x10" "Look at you!!\x03\x20 You look all beat up.\x01\nYou made a big mistake coming\nhere.\x01 Tee-hee! Bye!\x01");
	SetDialogString(2271, "\x10""Cindy\x10" "Forgive me, please...\x03\x20 I'll give you a\nspecial 75% discount.\x01 And $500...\x03\x20 okay?\x01");
	SetDialogString(2272, "\x10""Ninja\x10" "You are permitted to go to the\nVolcano Dojo.\x01");
	SetDialogString(2273, "\x10""Ninja\x10" "You're permitted to go to the\nVolcano Dojo.\x01");
	SetDialogString(2274, "\x10""Ninja\x10" "...\x01");
	SetDialogString(2275, "\x10""Nekin\x10" "Oh, hello, Ruby.\x01 You okay?\x01");
	SetDialogString(2276, "\x10""Nekin\x10" "Well, I'm not okay at all.\x01 My\nfamily used to rule Gemia...\x03\x20 and\nhere I am,\x03\x20 locked up in this\nunderground prison for no reason...\x01");
	SetDialogString(2277, "\x10""Ruby\x10" "Gemia is horrible.\x03\x20 It needs to be\npurified.\x01");
	SetDialogString(2278, "\x10""Nekin\x10" "...Purified?\x01 What exactly are you going\nto do?\x01");
	SetDialogString(2279, "\x10""Ruby\x10" "I'll start with purifying you...\x01");
	SetDialogString(2280, "\x10""Nekin\x10" "What?\x01");
	SetDialogString(2281, "\x10""Nekin\x10" "No, you won't!\x03\x20 I'll be the one to\npurify you!!\x01 Begone!!\x01");
	SetDialogString(2282, "A broken OFF Series Omega.\x01");
	SetDialogString(2283, "\x10""Cashier\x10" "Hm, you wanna buy something?\x01");
	SetDialogString(2284, "\x10""Cashier\x10" "Heya! Buy yourself food at a cheap\nprice!\x03\x20 How can I help you?\x01");
	SetDialogString(2285, "\x10""Man\x10" "The prices really are cheap here!\x01");
	SetDialogString(2286, "\x10""Woman\x10" "This is a great place for a\nquick snack!\x01");
	SetDialogString(2287, "\x10""Lulu\x10" "I'll meet you later...\x03\x20 Don't you\ndare touch my food or stuff!\x01");
	SetDialogString(2288, "\x10""Agent\x10" "There's maintenance going on.\x01 Come back\nwhen you're able to travel to\nSapphirepolis.\x01");
	SetDialogString(2289, "\x10""Ayaka\x10" "Have fun! If you're looking for a\nshop, it's like 3 crossroads to north\nand then a bit to west.\x01");
	SetDialogString(2290, "\x10""Ayaka\x10" "Hello, I'm selling more cool and\ncheap stuff.\x01");
	SetDialogString(2291, "\x10""Ayaka\x10" "Oh, you're here too?\x03\x20 What a\ncoincidence!\x01 Anyway, thanks to my\nengineering skills, I'm able to sell\neven more cool stuff!\x01");
	SetDialogString(2292, "There is a note on the door.\x01");
	SetDialogString(2293, "\"Razor Chaos Club has been shut down.\x03\x20\nThanks for your patience.\"\x01");
	SetDialogString(2294, "Below it says:\n\"P.S. in case you're a newbie, it obv\nhasn't shutdown, it only moved to\nanother location lol\"\x01");
	SetDialogString(2295, "\x10""Doctor\x10" "This is the Bluesteel Hospital.\x01\nAre you looking to get some\nmedicine?\x01");
	SetDialogString(2296, "\x10""Nurse\x10" "Some of my co-workers decided to\ntreat injured Vandals outside...\x01 I'm\nnot even sure why, maybe they are\non the Vandals' side.\x01");
	SetDialogString(2297, "\x10""Man\x10" "I broke my leg trying to run as\nfast as possible...\x01 You should be\ncareful not to end up in a situation\nlike me!\x01");
	SetDialogString(2298, "Note: running won't break your leg\nor hurt you in any capacity.\x01\nDon't worry about that, just clearing\nup possible misinformation...\x01 If that\nwas actually a thing, it would be\ncalled \"bad gameplay design\".\x01");
	SetDialogString(2299, "\x10""Lulu\x10" "...\x01");
	SetDialogString(2300, "\x10""Woman\x10" "Gotta take selfies everywhere I can!\x01\x03\x20\nI'm sure this one will be the one\nto get a lot of likes..!\x01");
	SetDialogString(2301, "\x10""Woman\x10" "Have you ever thrown a coin into\na fountain?\x01 It's probably just a myth,\nbut be careful not to throw \"dirty\"\ncoins or you might end up angering an\nevil water beast!\x01");
	SetDialogString(2302, "\x10""Police\x10" "If there's one area the Vandals\nshouldn't step in,\x03\x20 it's this one.\x01 They\nneed to be teached a thorough lesson!\x01");
	SetDialogString(2303, "\x10""Receptionist\x10" "Welcome to the Leaf Good Hotel!\x03\x02\nNo, this has nothing to do with the\nLeaf Crew from Rivergreen Town.\x01 Do you\nwant to reserve a room?\x01");
	SetDialogString(2304, "\x10""Woman\x10" "I'm busy doing janitor work...\x01");
	SetDialogString(2305, "\x10""Justin\x10" "What's up?\x03\x20 You're a Vandal?\x03\x20 To the\nwoods you shall go!\x01 Well, just saying...\x01\nIf you were one of them, I'd take you\ndown in just a single RPG turn...\x01\nThat's how awesome I am!\x01");
	SetDialogString(2306, "\x10""Man\x10" "You might not believe it, but Justin,\x03\x20\nthat guy with a black cap...\x01 He beat up\na gang of Vandals...\x03\x20 with style.\x01");
	SetDialogString(2307, "\x10""Woman\x10" "I'm a fan of Justin's amazing combat\nskills!\x01");
	SetDialogString(2308, "\x10""Lulu\x10" "Super Duper Hyper Ultra Omegatron\nNega Ultimate Dark Space Overdrive\nDoom Breaker Destructive Sniper Killer\nBeam of Mass Fucking Apocalypse\nHellcleansing Extreme Smooth Criminal\nThriller Moonwalker 9000 Spartan Trolls\nDemonic Ass-blasting Trooper-stomping\nGiga Yetta Fileshredder Uber-Great\nHorizontal Shitsplits of Massive\nLulu-tastic Wills of Hades And Crazy\nCatastrophes Limit Breaker\x03\x99 (and Knuckles)\x01");
	SetDialogString(2309, "\x10""Lulu\x10" "YOU'RE DONE FOR!!!!\x03\x20 SAY GOODBYE!!\x01");
	SetDialogString(2310, "\x10""Merchant\x10" "I'm only a merchant who sells stuff.\x01\nWhat items shall you get from me?\x01");
	SetDialogString(2311, "\x10""Woman\x10" "I heard that the leader of Ozone\nis immortal or undead...\x01 Is she\na zombie?\x03\x20 Should I be afraid?\x01");
	SetDialogString(2312, "\x10""Johnny\x10" "Hey!\x03\x20 I think I know you.\x01 Ruby,\nisn't it?\x03\x20 I'm Johnny.\x01 Take this,\nI think it might help you out a\nton in near future...\x01");
	SetDialogString(2313, "\x10""Johnny\x10" "I'm trying Volcano's ninja training\nprogram.\x01 So far, it's going great!\x03\x20\nThough Vulkan tends to be strict...\x01");
	SetDialogString(2314, "\x10""Johnny\x10" "Nevermind, I'll give it to you when\nyou have space in your pockets.\x01");
	SetDialogString(2315, "\x10""Vulkan\x10" "What's the matter?\x03\x20 Go get that gem\nand skedaddle.\x01");
	SetDialogString(2316, "\x10""Woman\x10" "Hey, they said that it's gonna\nrain tomorrow morning...\x01 I'll make\nsure to leave my umbrella at home by\nthen so it doesn't get wet...\x01");
	SetDialogString(2317, "\x10""Woman\x10" "No signs of rain at all...\x01 Strange,\x03\x20\nthe weather predictions are usually\nsuper accurate.\x01");
	SetDialogString(2318, "\x10""Woman\x10" "Are you confused at how combat\nworks?\x03\x20 Or did you want to learn\nsome useful tricks and things?\x01\nIf so, I'll give you a Combat book.\x03\x20\nWant one?\x11Yes\nNo\x11");
	SetDialogString(2319, "\x10""Woman\x10" "Too bad, it got confiscated by the\npolice...\x03\x20 So dumb, if this were to be\nsome sort of RPG game...\x03\x20 well...\x01\nSorry, maybe I'll have it in the\nfar future...\x01");
	SetDialogString(2320, "\x10""Woman\x10" "Oh, that's fine.\x01 I don't have it\nanyway...\x01");
	SetDialogString(2321, "\x10""Woman\x10" "Hey, aren't you the one who\nbeat Sanji?\x01 Wow!\x03\x20 I wish I was\nas smart and strong as you!\x01");
	SetDialogString(2322, "\x10""Emmet\x10" "Hi, Ruby! You wanted me to tag\nalong, right?\x11Yes\nNo\x11");
	SetDialogString(2323, "\x10""Emmet\x10" "Just as I thought!\x01");
	SetDialogString(2324, "\x10""Pirate\x10" "This place's not popular, but is\npretty chill!\x01");
	SetDialogString(2325, "\x10""Pirate\x10" "...\x01");
	SetDialogString(2326, "\x10""Police\x10" "Hey, lady, here's a good tip for\nfighting battles.\x01 You gotta have the\nskill to PROTECT others...\x01 You can\nsee that we, the police, do that all\nthe time!\x01 It can save a barely\nstanding ally from defeat by taking\nthe hit yourself!\x01");
	
	SetDialogString(3000, "Ruby has joined the party.\x01");
	SetDialogString(3001, "Noah has joined the party.\x01");
	SetDialogString(3002, "Emmet has joined the party.\x01");
	SetDialogString(3003, "Sally has joined the party.\x01");
	SetDialogString(3004, "Diego has joined the party.\x01");
	SetDialogString(3005, "Tony has joined the party.\x01");
	SetDialogString(3006, "Perry has joined the party.\x01");
	
	SetDialogString(3060, "It radiates with power.\x01");
	SetDialogString(3061, "A strange and ominous portal.\x01\nDo you want to enter it?\x11Yes\nNo\x11");
	SetDialogString(3062, "You can now equip Badges.\x01");
	SetDialogString(3063, "?\x03\x30?\x03\x30?\x03\x30?\x03\x30?\x03\x30?\x03\x30?\x03\x30?\x03\x30?\x03\x30\x01");
	
	SetDialogString(3070, "You got the Ruby of Stars.\x01\nYou were fully healed.\x01");
	SetDialogString(3071, "You got the Emerald of Earth.\x01\nYou were fully healed.\x01");
	SetDialogString(3072, "You got the Diamond of Sky.\x01\nYou were fully healed.\x01");
	SetDialogString(3073, "You got the Sapphire of Ocean.\x01\nYou were fully healed.\x01");
	SetDialogString(3074, "You got the Onyx of Death.\x01\nYou were fully healed.\x01");
	
	SetDialogString(3100, "A huge gate.\x03\x20 It's locked.\x01");
	SetDialogString(3101, "\x10""!!!!!\x10" "Did you want to return?\x11Yes\nNo\x11");
	SetDialogString(3102, "\x10""!!!!!\x10" "A huge red gate... I wonder what's\nthe meaning of that.\x01");
	SetDialogString(3103, "\x10""?????\x10" "Sapphireton's Laboratory is going\nto be closed down, you know?\x01 Perhaps\nyou can go home for now.\x01");
	SetDialogString(3104, "\x10""!!!!!\x10" "This place seems familiar.\x01");
	SetDialogString(3105, "You shall burn in hell.\x02");
	SetDialogString(3106, "\x80\x01 has melted down...\x01");
	SetDialogString(3107, "\x10""Ruby\x10" "(My body...\x03\x20 it feels like it's\nstarting to lose form.\x01 I bet\nthis armor has something to do\nwith it.\x01 Grgghh... I don't wanna\nuse this armor anymore..!)\x01");
	SetDialogString(3108, "\x10""Noah\x10" "...\x01\nI feel sick...\x01\nRuby, can you...\x03\x20 can you\nh-help?\x01 I'm losing my mind!\x01");
	SetDialogString(3109, "\x10""Ruby\x10" "What's wrong, Noah?\x01");
	SetDialogString(3110, "\x10""Noah\x10" "I don't know!\x03\x20 Wait...\x01");
	SetDialogString(3111, "\x10""Ruby\x10" "(Oh no... his body is losing\nform...\x01 I need to remove that\narmor as soon as possible!!)\x01");
	SetDialogString(3112, "\x10""Ruby\x10" "Please, hang on Noah! Try\nyour best not to... melt down!\x01");
	SetDialogString(3113, "\x10""Emmet\x10" "...\x01\nI feel kinda funky...\x01\nUmmm..... Ruby?\x01");
	SetDialogString(3114, "\x10""Ruby\x10" "Yes, Emmet?\x01");
	SetDialogString(3115, "\x10""Emmet\x10" "What's happening to me?\x01 I think\nyour \"magical gem\" is starting\nto fail!\x01");
	SetDialogString(3116, "\x10""Ruby\x10" "!!! That can't be..!\x01\nNo, I think it's the armor\nthat's causing it.\x01 I can help\x01\nafter this battle's over, just\ntry to hold out, okay?\x01");
	SetDialogString(3117, "\x10""Sally\x10" "...\x01\nHm..?\x01\n...EEEEEKKKKK!!!\x01\nRuby, what the HELL? Is it me,\nor am I...\x03\x20 melting?\x01 No, I AM\nmelting!\x01");
	SetDialogString(3118, "\x10""Ruby\x10" "You're right, Sally! Your body\nis indeed losing form!\x01");
	SetDialogString(3119, "\x10""Sally\x10" "Wh-WHAT? Ruby! Can you like...\nSTOP THIS?!\x01 I don't wanna turn\ninto tomato sauce! I blame this\nweird ass suit..!\x01");
	SetDialogString(3120, "\x10""Ruby\x10" "Try to not lose it before the\nend of the battle.\x01 You won't have\nto wear it again after this.\x01\nSorry.\x01");
	SetDialogString(3121, "\x10""Sally\x10" "Waaaahh!!! I hate you!\x01");
	SetDialogString(3122, "\x80\x01's body is starting to lose\nform.\x01 Be careful!\x01");
	SetDialogString(3123, "A strange green geyser fully\nhealed you.\x01");
	SetDialogString(3124, "\x10""!!!!!\x10" "Ruby...\x03\x30 You should not be here..\x01");
	SetDialogString(3125, "\x10""!!!!!\x10" "I will always be with you,\x03\x40 even\nif I have to burn in hell with you.\x01");
	SetDialogString(3126, "\x10""!!!!!\x10" "This is merely an illusion.\x03\x40\nOr is it?\x01 I don't know at this\npoint...\x01");
	SetDialogString(3127, "\x10""!!!!!\x10" "Regardless, I still have the power\nto return you back to the \"real\nworld\"...\x01");
	SetDialogString(3128, "\x10""???\x10" "There you are.\x01");
	SetDialogString(3129, "\x10""???\x10" "You are an entity that should be\nerased from existence.\x01 Actually,\x03\x20\nthere's a place for entities like you.\x01");
	SetDialogString(3130, "\x10""???\x10" "Heh heh heh.\x03\x40 It's time to visit that\nplace right now.\x01 You had better show\nno resistance or you will suffer even\nmore.\x01");
	SetDialogString(3131, "The Gate has been destroyed.\x02\x01");
	SetDialogString(3132, "\x10""!!!!!\x10" "Wow... you destroyed the gate...\x01\nI don't know why, but...\x01");
	SetDialogString(3133, "\x10""!!!!!\x10" "I hope you don't try to undo the\nthing you've done before...\x01 Your best\ninvention... \x01 Anyway...\x01");
	SetDialogString(3134, "\x10""?????\x10" "Umm...\x03\x20 Are you okay?\x01 What are you\ndoing?\x01");
	SetDialogString(3135, "\x10""!!!!!\x10" "...\x01Why did you do that?\x01");
	SetDialogString(3136, "\x10""!!!!!\x10" "It's okay...\x03\x20 I understand you.\x01\nI will support you even beyond the\nend of the time...\x01");
	SetDialogString(3137, "\x10""!!!!!\x10" "I can cheer you up if you want.\x01");
	SetDialogString(3138, "\x10""!!!!!\x10" "Nope?\x03\x30 Okay.\x01");
	SetDialogString(3139, "Key H\n\"Full of hatred\"\x01");
	SetDialogString(3140, "Key E\n\"Enlightenment\"\x01");
	SetDialogString(3141, "Key C\n\"Laboratory is closed\"\x01");
	SetDialogString(3142, "Key B\n\"There is a better solution\"\x01");
	SetDialogString(3143, "Key U\n\"Ultimate plan\"\x01");
	SetDialogString(3144, "\x80\x08");
	SetDialogString(3145, "An empty key slot.\x01");
	SetDialogString(3146, "\x10""!!!!!\x10" "The timeline puzzle...\x03\x20 The origins of\nyour power...\x01 I think a door will\nappear if you solve this.\x01");
	SetDialogString(3147, "\"Cyan is the beginning of time.\nTimeline is from left to right\"\x01");
	SetDialogString(3148, "\"Green comes after blue.\"\x01");
	SetDialogString(3149, "\"Blue comes before magenta.\"\x01");
	SetDialogString(3150, "\"Magenta comes after green.\x01 Err, I\nmean blue xd\x01\nGreen comes after cyan by the way.\"\x01");
	SetDialogString(3151, "\"The finale is intense red.\"\x01");
	SetDialogString(3152, "Fun is \x80\x09.\x01");
	SetDialogString(3153, "The world has decided this door\nwill not open itself.\x01 True chaos and\npain is behind this door.\x01");
	SetDialogString(3154, "\x10""!!!!!\x10" "There's nothing but a locked door\nin there?\x03\x20 Oh well...\x01");
	SetDialogString(3155, "\x10""???\x10" "R-Ruby...\x03\x40 I'm so sorry.\x03\x40.\x03\x40.\x01 I...\x03\x30 can...\x03\x30\nI...\x03\x30 can...\x03\x12");
	SetDialogString(3156, "\"Thou shall always favor your family\nand never raise hands against them.\x01\nOnly a foolish evil mind would think\nof attempting that ridiculousness.\"\x01");
	SetDialogString(3157, "\x10""Viku\x10" "What,\x03\x20 didn't expect an agent from Ruby\nMinistry to be in a place like this?\x01\nC'mon, let me live my life...\x01");
	SetDialogString(3158, "Unknown Hard Error\x01");
	
	SetDialogString(4000, "\x80\x01 uses \x80\x02!\x02");
	SetDialogString(4001, "You won!\nYou got \x80\x03 EXP and $\x80\x04.\x01\x80\x06\x02");
	SetDialogString(4002, "\n\x80\x05\x02");
	SetDialogString(4003, "You lost...\x01");
	SetDialogString(4004, "You got the \x80\x07.\x01");
	SetDialogString(4005, "You found the \x80\x07,\nbut you are carrying too many goods.\x01");
	SetDialogString(4006, "\x80\x01 counters!\x02");
	SetDialogString(4007, "\x80\x01 was fatally injured...\x02");
	SetDialogString(4008, "Ruby ran away!\x02");
	
	SetDialogString(4010, "Well, I can always try again.\x02");
	SetDialogString(4011, "...not!\x02");
	SetDialogString(4012, "Not so fast! I can try again.\x02");
	SetDialogString(4013, "Little did they know I can\nretry...\x02");
	SetDialogString(4014, "Well, time for a small reset!\x02");
	SetDialogString(4015, "They have no idea what hit\nthem.\x02");
	SetDialogString(4016, "It's rewind time!\x02");
	SetDialogString(4017, "Mmm... no.\x02");
	SetDialogString(4018, "I will come back better than\never.\x02");
	SetDialogString(4019, "Game over? No problem.\x02");
	SetDialogString(4020, "I've got infinite tries...\x02");
	SetDialogString(4021, "I really only need to win\nonce.\x02");
	
	SetDialogString(4030, "Dammit.\x01");
	SetDialogString(4031, "What? That's unfortunate.\x01");
	SetDialogString(4032, "What in the world?\x01");
	SetDialogString(4033, "Well, there goes my whole\nendeavor...\x01");
	SetDialogString(4034, "Oh, you're still alive, Ruby?\x01\nToo bad! This is the end of the\ndemo.\x01 Bye!\x01 See you in a few\nmonths I guess!\x01");
	
	SetDialogString(4500, "Does nothing.");
	SetDialogString(4501, "Heals 30% of base HP.\nNot very good on its own.");
	SetDialogString(4502, "Heals 70% of base HP.\nA tasty and healthy slice of a\npizza.");
	SetDialogString(4503, "Heals 15 HP. Can be used during\na battle.");
	SetDialogString(4504, "Use it against an enemy to deal\n15 damage.");
	SetDialogString(4505, "Heals 20% of base HP.\nGood for making sandwiches.");
	SetDialogString(4506, "Heals 50% of base HP.");
	SetDialogString(4507, "Heals 85% of base HP.\nA can of tomato soup, an universal\nchoice of food.");
	SetDialogString(4508, "Heals 110% of base HP.\nNo hair, no saliva, no other\nunwanted nonsense. Finally, a cook\nwith at least 0.375% of decency!!");
	SetDialogString(4509, "Heals 2% of base HP and gets\nrid of tiredness.\nEssence of life. Always helps if\nyou're tired.");
	SetDialogString(4510, "Heals 20% of base HP and gets\nrid of tiredness.");
	SetDialogString(4511, "Heals 30% of base HP and gets\nrid of tiredness.");
	SetDialogString(4512, "Heals 30% of base HP and gets\nrid of tiredness.");
	SetDialogString(4513, "Heals 80% of base HP.");
	SetDialogString(4514, "Heals 30% of base HP and gets\nrid of tiredness.");
	SetDialogString(4515, "Heals 60% of base HP and gets\nrid of tiredness.");
	SetDialogString(4516, "A nuke that only obliterates the\nhalf it's facing. Use in battles.");
	SetDialogString(4517, "Heals 35% of base HP and gets\nrid of tiredness.\nGrows on trees.");
	SetDialogString(4518, "Heals 70% of base HP.");
	SetDialogString(4519, "Heals 80% of base HP.\nMario's favorite food.");
	SetDialogString(4520, "Heals 90% of base HP.\nHealthy ingredients only!");
	SetDialogString(4521, "Heals 110% of base HP.\nExpensive artifical meal that is\nfocused on providing energy with\nefficiency.");
	SetDialogString(4522, "Heals 300% of base HP and gets\nrid of tiredness.\nMasterfully-crafted meal, made for the\nMinistry agents.");
	SetDialogString(4523, "Heals 25 HP. Can be used during\na battle.");
	SetDialogString(4524, "Heals 40 HP. Can be used during\na battle.");
	SetDialogString(4525, "Heals 90% of base HP and gets\nrid of tiredness.\nExpensive drink that provides a very\nefficient energy boost.");
	SetDialogString(4526, "Gain 40 Strength during a battle.");
	SetDialogString(4527, "Removes all status effects during\na battle.");
	SetDialogString(4528, "Removes Bleed, Poison and Paralysis\nduring a battle. If used outside of a\nbattle, heals 100% of base HP.");
	SetDialogString(4529, "Restores 15 MP during a battle.");
	SetDialogString(4530, "Use it against an enemy to deal\n30 damage.");
	SetDialogString(4531, "Use it against an enemy to deal\n60 damage.");
	
	SetDialogString(4660, "Ruby's invention that gives the\nability to capture and equip the\nenemy's armor and skills. Not an\nAncient Gem.");
	SetDialogString(4661, "A present for Perry's brother.");
	SetDialogString(4662, "A silver key found in Dia's\nMansion.");
	SetDialogString(4663, "A golden key found in Dia's\nMansion.");
	SetDialogString(4664, "A diamond key found in Dia's\nMansion.");
	SetDialogString(4665, "Its usage shines in dark places.");
	SetDialogString(4666, "A card for Razor Chaos club members.");
	SetDialogString(4667, "A card for Razor Chaos club VIPs.");
	SetDialogString(4668, "A key for unlocking the door.");
	SetDialogString(4669, "A key for unlocking the door.");
	SetDialogString(4670, "A powerful gaming console from\nprevious generation, made by N-Soft\ncorporation.");
	SetDialogString(4671, "A black key that should open a\ncertain door.");
	SetDialogString(4672, "A card found in a bunker at Lapis\nPeaks.");
	SetDialogString(4673, "Ruby's own toolkit that might\nbe useful later.");
	
	SetDialogString(4750, "An Ancient Gem that radiates with\npower.");
	SetDialogString(4751, "An Ancient Gem that radiates with\npower.");
	SetDialogString(4752, "An Ancient Gem that radiates with\npower.");
	SetDialogString(4753, "An Ancient Gem that radiates with\npower.");
	SetDialogString(4754, "An Ancient Gem that radiates with\npower.");
	
	SetDialogString(5000, "Does nothing");
	SetDialogString(5001, "");
	SetDialogString(5002, "");
	SetDialogString(5003, "");
	SetDialogString(5004, "");
	SetDialogString(5005, "");
	SetDialogString(5006, "");
	SetDialogString(5007, "Restores 6 MP");
	SetDialogString(5008, "");
	SetDialogString(5009, "");
	SetDialogString(5010, "Inflicts 8 Bind");
	SetDialogString(5011, "Inflicts 10 Feeble");
	SetDialogString(5012, "Inflicts 4 Bind");
	SetDialogString(5013, "Inflicts 6 Bind");
	SetDialogString(5014, "Inflicts 2 Bleed");
	SetDialogString(5015, "Attacks first, restores 15\nMP");
	SetDialogString(5016, "Attacks first, inflicts 7\nBurn");
	SetDialogString(5017, "Slashes many times");
	SetDialogString(5018, "Inflicts 3 Burn");
	SetDialogString(5019, "Inflicts 4 Burn");
	SetDialogString(5020, "Gain 15 Strength if blocked");
	SetDialogString(5021, "Inflicts 1 Bleed");
	SetDialogString(5022, "Inflicts 3 Poison");
	SetDialogString(5023, "Inflicts 2 Bleed");
	SetDialogString(5024, "Inflicts 20 Bind");
	SetDialogString(5025, "Guard and take 1 less damage");
	SetDialogString(5026, "Protects an ally, take 2\nless damage");
	SetDialogString(5027, "Heals an ally 10 HP");
	SetDialogString(5028, "Targets all enemies\nInflicts 8 Burn");
	SetDialogString(5029, "Inflicts 2 Disarm");
	SetDialogString(5030, "Gain 8 Haste");
	SetDialogString(5031, "Allies gain 3 Strength and\nHaste");
	SetDialogString(5032, "Zaps the enemy with a\nhandshake, Inflicts 2\nParalysis, one-use");
	SetDialogString(5033, "Inflicts 3 Disarm");
	SetDialogString(5034, "Gain 8 Feeble");
	SetDialogString(5035, "Attacks first, inflicts 2\nBleed");
	SetDialogString(5036, "Restores 8 MP");
	SetDialogString(5037, "");
	SetDialogString(5038, "Unblockable, inflicts 4\nBleed");
	SetDialogString(5039, "Gain 15 Strength");
	SetDialogString(5040, "Inflicts 3 Bleed");
	SetDialogString(5041, "Redirects all enemies'\nattacks onto self, attacks\nafter being attacked");
	SetDialogString(5042, "Targets all enemies\nInflicts 4 Bleed");
	SetDialogString(5043, "Kunai sticks and explodes\nafter a turn, dealing 15\ndamage");
	SetDialogString(5044, "Gain 18 Haste");
	SetDialogString(5045, "Attacks first, undodgable,\nuses Speed instead of Attack\nfor damage");
	SetDialogString(5046, "Attacks first, inflicts 6\nParalysis");
	SetDialogString(5047, "50% or less HP required");
	SetDialogString(5048, "Protects an ally, take 5\nless damage");
	SetDialogString(5049, "Inflicts 1 Paralysis");
	SetDialogString(5050, "Restores 16 MP");
	SetDialogString(5051, "Attacks first");
	SetDialogString(5052, "Rocket explodes violently,\ninflicts 4 Burn, undodgable");
	SetDialogString(5053, "Inflicts 2 Paralysis");
	SetDialogString(5054, "Unstoppable beam of\ndestruction");
	SetDialogString(5055, "Restores 55 MP, cannot\nact next turn");
	SetDialogString(5056, "Inflicts 3 Flower");
	SetDialogString(5057, "Heals 70 HP, gain 12 Flower");
	SetDialogString(5058, "Restores 40 MP, gain 9\nFlower");
	SetDialogString(5059, "Attacks first, +80 damage if\ntarget has Flower,\nundodgable, unblockable");
	SetDialogString(5060, "Targets all enemies\nAttacks first, +6 damage if\ntarget has Flower,\nundodgable, unblockable");
	SetDialogString(5061, "Attacks first, inflicts 10\nParalysis");
	SetDialogString(5062, "Inflicts 3 Feeble");
	SetDialogString(5063, "Inflicts 4 Paralysis");
	SetDialogString(5064, "Inflicts 7 Paralysis");
	SetDialogString(5065, "");
	SetDialogString(5066, "Inflicts 4 Bind");
	SetDialogString(5067, "Gives an ally 20 Strength");
	SetDialogString(5068, "Gives an ally 15 Endurance");
	SetDialogString(5069, "Gain 20 Haste");
	SetDialogString(5070, "Targets all enemies\nAttacks first, insta-defeats\nenemies at 40 HP or less");
	SetDialogString(5071, "Attacks first, inflicts 8\nChill, undodgable,\nunblockable");
	SetDialogString(5072, "Restores 20 MP");
	SetDialogString(5073, "Inflicts 2 Bind");
	SetDialogString(5074, "Heals an ally 40 HP");
	SetDialogString(5075, "Attacks first");
	SetDialogString(5076, "Gain 1 Charge");
	SetDialogString(5077, "1 Charge required");
	SetDialogString(5078, "Inflicts 1 Burn");
	SetDialogString(5079, "Inflicts 10 Burn and Timed\nBomb");
	SetDialogString(5080, "Inflicts 18 Feeble");
	SetDialogString(5081, "50% or less HP required\nTargets all enemies\nInflicts 15 Timed Bomb,\nundodgable");
	SetDialogString(5082, "Removes all status effects\nfrom an ally or enemy");
	SetDialogString(5083, "Revives a defeated ally\nand heals 20 HP");
	SetDialogString(5084, "1 Charge required\nInflicts 12 Paralysis");
	SetDialogString(5085, "Top priority\nProtects an ally, take 2\nless damage");
	SetDialogString(5086, "50% or less HP required\nLethal, inflicts 20 Bleed,\nunblockable");
	SetDialogString(5087, "Inflicts 6 Bleed");
	SetDialogString(5088, "50% or less HP required\nInflicts 20 Bleed,\nunblockable");
	SetDialogString(5089, "Attacks first, inflicts 9\nBleed");
	SetDialogString(5090, "Targets all enemies\nAttacks first, inflicts 2\nBleed, undodgable,\nunblockable");
	SetDialogString(5091, "Attacks first, inflicts 24\nFeeble");
	SetDialogString(5092, "Inflicts 12 Feeble, gain\n12 Feeble");
	SetDialogString(5093, "Deals critical damage if\nunblocked");
	SetDialogString(5094, "Gain 20 Strength");
	SetDialogString(5095, "Gain 15 Endurance");
	SetDialogString(5096, "Shoot the enemy with gun");
	
	SetDialogString(5191, "??????");
	
	SetDialogString(5200, "Heals 15 HP");
	SetDialogString(5201, "Attacks first");
	SetDialogString(5202, "Targets all enemies\nAttacks first");
	SetDialogString(5203, "Heals 25 HP");
	SetDialogString(5204, "Heals 40 HP");
	SetDialogString(5205, "Gain 40 Strength");
	SetDialogString(5206, "Removes all status effects\nfrom self");
	SetDialogString(5207, "Removes Bleed, Poison and\nParalysis from self");
	SetDialogString(5208, "Restores 15 MP");
	SetDialogString(5209, "Attacks first");
	SetDialogString(5210, "Attacks first");
}

void SetDialogString(int id, const char* value) {
	dialogPointerData[id] = dialogSystem.ptr;
	
	int i = 0;
	while (dialogSystem.ptr < 0x40000) {
		if (value[i] == 0) break;
		dialogData[dialogSystem.ptr++] = value[i];
		i++;
	}
	
	if (++dialogSystem.ptr >= 0x40000) {
		printf("WARNING: Dialog data overflow\n");
	}
}

char* GetDialogString(int id) {
	return &dialogData[dialogPointerData[id]];
}



void Dialog_Run(int id) {
	if (dialogSystem.state != DIALOG_STATE_IDLE) return;
	
	dialogSystem.state = DIALOG_STATE_RUN;
	dialogSystem.ptr = dialogPointerData[id];
	dialogSystem.bufferPtr = -1;
	dialogSystem.bufferLength = 0;
	dialogSystem.name[0] = 0;
	dialogSystem.timer = 0;
	dialogSystem.time = -1;
	dialogSystem.voiceSoundId = SND_voice1;
	dialogSystem.voiceCooldown = 0;
	dialogSystem.voiceTickDelay = 0;
	dialogSystem.voiceDelayTimer = 0;
	Menu_ClearOptions(&dialogSystem.menu);
}

void Dialog_RunVoiced(int id, int voiceId) {
	Dialog_Run(id);
	switch (voiceId) {
		case 1:
			dialogSystem.voiceSoundId = SND_voice2;
			dialogSystem.voiceTickDelay = 1;
			break;
	}
}

void Dialog_Jump(int id) {
	dialogSystem.ptr = dialogPointerData[id];
}

void Dialog_Continue() {
	if (dialogSystem.state != DIALOG_STATE_WAIT && dialogSystem.state != DIALOG_STATE_INPUTWAIT) return;
	
	dialogSystem.state = DIALOG_STATE_RUN;
}

void Dialog_AppendString(const char* string) {
	dialogSystem.bufferPtr = 0;
	dialogSystem.bufferLength = 0;
	for (int i = 0; i < DIALOG_BUFFER_SIZE; i++) {
		if (string[i] == 0) break;
		dialogSystem.buffer[i] = string[i];
		dialogSystem.bufferLength++;
	}
}

bool Dialog_IsFinished() {
	return dialogSystem.state == DIALOG_STATE_IDLE;
}

bool Dialog_IsWaiting() {
	return dialogSystem.state == DIALOG_STATE_WAIT;
}

unsigned char Dialog_GetChar() {
	if (dialogSystem.bufferPtr >= 0 && dialogSystem.bufferPtr < dialogSystem.bufferLength) {
		return dialogSystem.buffer[dialogSystem.bufferPtr++];
	}
	return dialogData[dialogSystem.ptr++];
}

void Dialog_Update() {
	if (dialogSystem.state == DIALOG_STATE_IDLE) return;
	
	if (dialogSystem.voiceCooldown > 0) dialogSystem.voiceCooldown--;
	
	int d = 0;
	
	if (dialogSystem.state == DIALOG_STATE_INPUTWAIT) {
		if (dialogSystem.menu.optionCount > 0) {
			Menu_Update(&dialogSystem.menu);
			
			if (dialogSystem.menu.optionPressed >= 0) {
				dialogSystem.optionSelected = dialogSystem.menu.optionPressedValue;
				Menu_ClearOptions(&dialogSystem.menu);
				dialogSystem.state = DIALOG_STATE_RUN;
			}
		}
		else {
			if (PlayerButtonPressed(PLAYER_BUTTON_Z) || (PlayerButtonHeld(PLAYER_BUTTON_C) && game.settings.textSkip)) {
				dialogSystem.state = DIALOG_STATE_RUN;
			}
		}
	}
	if (dialogSystem.state == DIALOG_STATE_WAIT && dialogSystem.time >= 0) {
		if (PlayerButtonPressed(PLAYER_BUTTON_X) || (PlayerButtonHeld(PLAYER_BUTTON_C) && game.settings.textSkip)) {
			dialogSystem.timer = dialogSystem.time;
		}
		if (dialogSystem.timer >= dialogSystem.time) {
			dialogSystem.state = DIALOG_STATE_RUN;
			dialogSystem.timer = 0;
			dialogSystem.time = -1;
		}
		dialogSystem.timer++;
	}
	
	if (dialogSystem.voiceDelayTimer < dialogSystem.voiceTickDelay && !PlayerButtonPressed(PLAYER_BUTTON_X) && (!PlayerButtonHeld(PLAYER_BUTTON_C) || !game.settings.textSkip)) {
		dialogSystem.voiceDelayTimer++;
		return;
	}
	
	while (dialogSystem.state == DIALOG_STATE_RUN && d++ < 256) {
		unsigned char c = Dialog_GetChar();
		
		if ((c >= 0x20 && c <= 0x7e) || c == 0x90) {
			dialogSystem.voiceDelayTimer = 0;
			dialogSystem.text[dialogSystem.textLength++] = c;
			if (c == 0x90) {
				dialogSystem.text[dialogSystem.textLength++] = Dialog_GetChar();
			}
			if (dialogSystem.voiceCooldown <= 0 && c != ' ') {
				PlaySoundInterrupt(dialogSystem.voiceSoundId);
				dialogSystem.voiceCooldown = 2;
			}
			if (!PlayerButtonPressed(PLAYER_BUTTON_X) && (!PlayerButtonHeld(PLAYER_BUTTON_C) || !game.settings.textSkip)) break;
		}
		else if (c == '\n') {
			dialogSystem.text[dialogSystem.textLength++] = c;
			
			int newLines = 0;
			int firstNewLine = -1;
			for (int i = 0; i < dialogSystem.textLength; i++) {
				if (dialogSystem.text[i] == '\n') {
					if (firstNewLine < 0) firstNewLine = i + 1;
					newLines++;
				}
			}
			
			if (newLines >= 4) {
				dialogSystem.textLength -= firstNewLine;
				for (int i = 0; i < dialogSystem.textLength; i++) {
					dialogSystem.text[i] = dialogSystem.text[i + firstNewLine];
				}
			}
			
			if (!PlayerButtonPressed(PLAYER_BUTTON_X) && (!PlayerButtonHeld(PLAYER_BUTTON_C) || !game.settings.textSkip)) break;
		}
		else if (c == 0x8f) {
			dialogSystem.text[dialogSystem.textLength++] = c;
			dialogSystem.text[dialogSystem.textLength++] = Dialog_GetChar();
		}
		else if (c == 0x00) {
			dialogSystem.state = DIALOG_STATE_IDLE;
			dialogSystem.textLength = 0;
			break;
		}
		else if (c == 0x01) {
			dialogSystem.state = DIALOG_STATE_INPUTWAIT;
			break;
		}
		else if (c == 0x02) {
			dialogSystem.state = DIALOG_STATE_WAIT;
			dialogSystem.timer = 0;
			dialogSystem.time = -1;
			break;
		}
		else if (c == 0x03) {
			dialogSystem.state = DIALOG_STATE_WAIT;
			dialogSystem.timer = 0;
			dialogSystem.time = Dialog_GetChar();
			if (!PlayerButtonPressed(PLAYER_BUTTON_X) && (!PlayerButtonHeld(PLAYER_BUTTON_C) || !game.settings.textSkip)) break;
		}
		else if (c == 0x10) {
			unsigned char ca;
			int i = 0;
			while ((ca = Dialog_GetChar()) != 0x10) {
				dialogSystem.name[i++] = ca;
			}
			dialogSystem.name[i] = 0;
			if (!PlayerButtonPressed(PLAYER_BUTTON_X) && (!PlayerButtonHeld(PLAYER_BUTTON_C) || !game.settings.textSkip)) break;
		}
		else if (c == 0x11) {
			unsigned char ca;
			char temp[32];
			int i = 0;
			Menu_New(&dialogSystem.menu, 0, 1, 999, 0);
			Menu_ResetCursor(&dialogSystem.menu);
			while ((ca = Dialog_GetChar()) != 0) {
				if (ca == 0x11) {
					temp[i] = 0;
					Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, temp);
					break;
				}
				if (ca == '\n') {
					temp[i] = 0;
					Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, temp);
					i = 0;
					continue;
				}
				temp[i++] = ca;
			}
			
			dialogSystem.state = DIALOG_STATE_INPUTWAIT;
			break;
		}
		else if (c == 0x80) {
			unsigned char ca = Dialog_GetChar();
			
			if (ca == 0x01) {
				Dialog_AppendString(battle.attacker->name);
			}
			else if (ca == 0x02) {
				Dialog_AppendString(actionData[battle.attacker->actionId].name);
			}
			else if (ca == 0x03) {
				snprintf(game.textBuffer, 9, "%d", battle.expEarned);
				Dialog_AppendString(game.textBuffer);
			}
			else if (ca == 0x04) {
				snprintf(game.textBuffer, 9, "%d", battle.cashEarned);
				Dialog_AppendString(game.textBuffer);
			}
			else if (ca == 0x05) {
				if (battle.levelUp.partyId >= 0) {
					int textLength = 0;
					
					textLength += snprintf(game.textBuffer, 256, "%s's level is now %d!\x01", partyMembers[battle.levelUp.partyId].name, partyMembers[battle.levelUp.partyId].level);
					if (battle.levelUp.hpGain > 0)
						textLength += snprintf(game.textBuffer + textLength, 256 - textLength, "\nHealth increased by %d!\x01", battle.levelUp.hpGain);
					if (battle.levelUp.mpGain > 0)
						textLength += snprintf(game.textBuffer + textLength, 256 - textLength, "\nMana increased by %d!\x01", battle.levelUp.mpGain);
					if (battle.levelUp.attackGain > 0)
						textLength += snprintf(game.textBuffer + textLength, 256 - textLength, "\nAttack increased by %d!\x01", battle.levelUp.attackGain);
					if (battle.levelUp.defenseGain > 0)
						textLength += snprintf(game.textBuffer + textLength, 256 - textLength, "\nDefense increased by %d!\x01", battle.levelUp.defenseGain);
					if (battle.levelUp.speedGain > 0)
						textLength += snprintf(game.textBuffer + textLength, 256 - textLength, "\nSpeed increased by %d!\x01", battle.levelUp.speedGain);
					if (battle.levelUp.actionId > 0)
						textLength += snprintf(game.textBuffer + textLength, 256 - textLength, "\n%s learned %s!\x01", partyMembers[battle.levelUp.partyId].name, actionData[battle.levelUp.actionId].name);
					
					Dialog_AppendString(game.textBuffer);
				}
			}
			else if (ca == 0x06) {
				if (battle.levelUp.partyId >= 0) {
					int textLength = 0;
					
					for (int i = 0; i < battle.rewardCount; i++) {
						if (battle.rewards[i].type == 0) {
							textLength += snprintf(game.textBuffer + textLength, 512 - textLength, "\nObtained %dx %s!\x01", battle.rewards[i].count, actionData[battle.rewards[i].id].name);
						}
						else {
							textLength += snprintf(game.textBuffer + textLength, 512 - textLength, "\nObtained %dx %s's armor!\x01", battle.rewards[i].count, armorData[battle.rewards[i].id].name);
						}
					}
					
					if (textLength > 0) Dialog_AppendString(game.textBuffer);
				}
			}
			else if (ca == 0x07) {
				Dialog_AppendString(itemData[profile.lastGotItemId].name);
			}
			else if (ca == 0x08) {
				Menu_New(&dialogSystem.menu, 0, 1, 999, 0);
				Menu_ResetCursor(&dialogSystem.menu);
				
				Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Leave");
				if (overworld.objects[eventSystem.callerObjectId].spriteId == SPR_misc_timelineblock) {
					Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Take");
				}
				int base = 1;
				for (int i = 0; i < 5; i++) {
					int id = (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / base) % 10;
					if (id == 9) {
						switch (i) {
							case 0: Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Put key H"); break;
							case 1: Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Put key E"); break;
							case 2: Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Put key C"); break;
							case 3: Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Put key B"); break;
							case 4: Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Put key U"); break;
							default: Menu_AddOption(&dialogSystem.menu, true, dialogSystem.menu.optionCount, "Wonder"); break;
						}
					}
					base *= 10;
				}
				
				dialogSystem.state = DIALOG_STATE_INPUTWAIT;
				break;
			}
			else if (ca == 0x09) {
				snprintf(game.textBuffer, 9, "%d", profile.flags[FLAG_FUN]);
				Dialog_AppendString(game.textBuffer);
			}
		}
	}
}
