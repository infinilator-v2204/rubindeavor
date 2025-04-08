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

const char* dialogRandomWordCollection[136] = {
	"abacus", "abbreviation", "abrogation", "abuse", "academics", "attenuation", "appointment", "awareness",
	"barometer", "bifocals", "blossom", "battleship", "beanstalk", "breastplate", "brother-in-law", "butterfly",
	"cappuccino", "carboxyl", "carriage", "curriculum", "certification", "chain", "characteristic", "commission",
	"debate", "dashboard", "decryption", "denominator", "dilapidation", "dune", "dysfunction", "disclaimer",
	"egg", "eardrum", "e-mail", "eclipse", "edition", "embassy", "equity", "expedition",
	"faucet", "feather", "faculty", "forage", "framework", "fishnet", "forum", "functionality",
	"gamma-ray", "garage", "gem", "generator", "gladiolus", "goat", "gravity", "gunpowder",
	"habitat", "haircut", "hammer", "hazelnut", "hierarchy", "honesty", "houseboat", "hydrogen",
	"icicle", "ideology", "implementation", "interloper", "jewelry", "jelly", "justice", "joint",
	"kebab", "keyboard", "king", "kitchen", "labor", "lacquerware", "lilac", "lunchroom",
	"mailman", "marker", "melatonin", "methodology", "mincemeat", "missionary", "moustache", "multimedia",
	"observatory", "octave", "omelet", "oversight", "passion", "peak", "photograph", "publicity",
	"qualification", "racecar", "radiator", "realization", "recess", "refrigerator", "rocket", "runway",
	"salesman", "sample", "scenery", "scotch", "supermarket", "sensor", "shoulder", "subcontractor",
	"tabletop", "tank", "typhoon", "thunderstorm", "tone", "truck", "twilight", "tube",
	"ultimatum", "understanding", "urge", "utility", "vehicle", "vibraphone", "voice", "vulture",
	"wall", "washtub", "wheat", "wisdom", "withdrawal", "yacht", "yoga", "zoologist",
};



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
	SetDialogString(685, "\x10""Sally\x10" "Oh, forget that.\x03\x20 I handed leadership\nto someone else, 'cause I didn't want\nto do anything with it anymore...\x01");
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
	
	SetDialogString(1090, "\x10""Agent\x10" "Only authorised and invited people are\nallowed to enter.\x03\x20 What business do you have\nin here?\x01");
	SetDialogString(1091, "\x10""Ruby\x10" "Well, uhh...\x01\n I am only here to get the\nAncient Gem.\x01");
	SetDialogString(1092, "\x10""Agent\x10" "Your first and last name, please.\x01");
	SetDialogString(1093, "\x10""Ruby\x10" "Uhh....\x01 Can you tell me how to\nget in touch with the CEO?\x01");
	SetDialogString(1094, "\x10""Sally\x10" "Do you really think the CEO will\nallow us, Ruby?\x01");
	SetDialogString(1095, "\x10""Ruby\x10" "Good point...\x03\x20 Let's just get this over\nwith.\x01");
	SetDialogString(1096, "\x10""Noah\x10" "W-wait!\x03\x20 What are you doing?\x01");
	SetDialogString(1097, "\x10""Emmet\x10" "Ruby, we would be waging a war against\nthis big company!\x03\x20 Do you REALLY want\nto fight them with the risk of getting\nin HUGE trouble??\x01");
	SetDialogString(1098, "\x10""Noah\x10" "...\x01");
	SetDialogString(1099, "\x10""Sally\x10" "She knows what she's doing, boys...\x03\x20\nCut it out with your cowardness.\x01");
	SetDialogString(1100, "\x10""Emmet\x10" "...I thought we would be asking nicely.\x01\nBesides...\x01");
	SetDialogString(1101, "\x10""Sally\x10" "These big companies only have one thing\nin their mind...\x03\x20 It's all about making\nstupidly high profits and scamming poor\npeople-\x01");
	SetDialogString(1102, "\x10""Agent\x10" "That's enough, you've entertained us enough\nwith your presence...\x01 Get out and\ncontinue your conversation outside...\x01");
	SetDialogString(1103, "\x10""Ruby\x10" "Fight us first.\x01");
	SetDialogString(1104, "\x10""Ruby\x10" "Oh, nothing.\x01 (I will come back later.)\x01");
	SetDialogString(1105, "\x10""Ruby\x10" "...\x03\x20None of your business.\x01");
	
	SetDialogString(1120, "\x10""Sally\x10" "Look!\x03\x20 Terry's Restaurant!\x01");
	SetDialogString(1121, "\x10""Sally\x10" "Ruby, let's go there please!\x01");
	SetDialogString(1122, "\x10""Ruby\x10" "Didn't I just give you-\x03\x10");
	SetDialogString(1123, "\x10""Sally\x10" "Don't care, I'm still hungry!\x01");
	SetDialogString(1124, "\x10""Ruby\x10" "Okay, fine.\x01");
	SetDialogString(1125, "\x10""Sally\x10" "I heard that Superheroes include\nSuperburgers in their diet.\x01 I wanna\ntry one!\x03\x20 What about you three?\x01");
	SetDialogString(1126, "\x10""Ruby\x10" "Hm, okay.\x01");
	SetDialogString(1127, "\x10""Emmet\x10" "Eh, sure.\x01");
	SetDialogString(1128, "\x10""Sally\x10" "Alrighty! Gonna buy one for each of\nyou.\x01");
	SetDialogString(1129, "\x10""Sally\x10" "Enjoy, boys and girls!\x03\x20 Damn, these\nare expensive, but it might be worth\nit.\x01");
	SetDialogString(1130, "\x10""Emmet\x10" "Wait, you have lots of money?\x01");
	SetDialogString(1131, "\x10""Sally\x10" "Uhhh...\x03\x40 yeah.\x03\x20 Don't ask where I got\nit from.\x01");
	SetDialogString(1132, "\x10""Sally\x10" "Ruby, you can lend my money.\x01");
	SetDialogString(1133, "You got $484.\x01");
	SetDialogString(1134, "\x10""Sally\x10" "Lunch time!\x03\x20 Or supper time?\x03\x20\nSuper supper time?\x01");
	
	SetDialogString(1140, "\x10""Sally\x10" "Mmm...\x03\x20 I really like it!\x03\x20 Much\nbetter than Rivergreen's food.\x01");
	SetDialogString(1141, "\x10""Emmet\x10" "Is it?\x03\x20 I won't deny that it\ntastes better though.\x01");
	SetDialogString(1142, "\x10""Sally\x10" "Noah, why aren't you eating?\x01");
	SetDialogString(1143, "\x10""Noah\x10" "I'm not hungry.\x01");
	SetDialogString(1144, "\x10""Sally\x10" "Well, I'll have yours if you\ndon't mind.\x01");
	SetDialogString(1145, "\x10""Noah\x10" "Ruby, I need to say something...\x01");
	SetDialogString(1146, "\x10""Ruby\x10" "Hm?\x01");
	SetDialogString(1147, "\x10""Noah\x10" "...\x03\x40Well...\x01");
	SetDialogString(1148, "\x10""Noah\x10" "I'm leaving.\x01");
	SetDialogString(1149, "\x10""Ruby\x10" "Leaving what?\x01");
	SetDialogString(1150, "\x10""Noah\x10" "Your team.\x01 I've thought about it for a\nwhile, but I don't want to follow you\nanymore.\x01");
	SetDialogString(1151, "\x10""Noah\x10" "I thought this was going to be a short\nand fun trip, but...\x01 You all keep\nfighting and fighting for no reason...\x03\x20\nSo much, that it feels like there's\nno end to this.\x01");
	SetDialogString(1152, "\x10""Ruby\x10" "I.. I'm-\x01");
	SetDialogString(1153, "\x10""Sally\x10" "Hey, you and Ruby are like best\nfriends!\x03\x20 Why would you suddenly leave\nher right now?\x01");
	SetDialogString(1154, "\x10""Ruby\x10" "Noah, you can not participate in\ncombat if you want.\x01");
	SetDialogString(1155, "\x10""Noah\x10" "Then there's no point to following\nyou, is there?\x01");
	SetDialogString(1156, "\x10""Noah\x10" "I can never be as skilled as you are.\x03\x20\nYou are always above me at\neverything...\x03\x20 except at being a\nfailure.\x01");
	SetDialogString(1157, "\x10""Emmet\x10" "Wait, are you going out alone?\x01\nWhat would you do if the police or\ncrooks get in your way?\x01");
	SetDialogString(1158, "\x10""Noah\x10" "I...\x03\x20 I'll figure that out myself.\x01");
	SetDialogString(1159, "\x10""Noah\x10" "Ruby, can I have a quarter of the\nmoney?\x01");
	SetDialogString(1160, "You gave 25% of your money to Noah.\x01");
	SetDialogString(1161, "\x10""Ruby\x10" "I don't have any money, sorry.\x01");
	SetDialogString(1162, "\x10""Noah\x10" "...\x01");
	SetDialogString(1163, "\x10""Sally\x10" "You're not worried about him, Ruby?\x01");
	SetDialogString(1164, "\x10""Ruby\x10" "He's gotten stronger for sure at this\npoint.\x03\x20 I think he should be fine.\x01");
	SetDialogString(1165, "\x10""Sally\x10" "Oh yeah, wanted to ask you about\ncollecting those gems...\x01 Why are you\ntrying to do it so hastily?\x01");
	SetDialogString(1166, "\x10""Emmet\x10" "We are probably getting in a lot\nof dirt in Ruby's mission, so we should\ndo it as quickly as possible to avoid\ntrouble...\x03\x40 I think that's why.\x01");
	SetDialogString(1167, "\x10""Ruby\x10" "Yeah. The faster, the better.\x01\nEspecially the last Ancient Gem in the\nBrilliant Mountains...\x01");
	SetDialogString(1168, "\x10""Sally\x10" "Huh, what's special about the last\none?\x01");
	SetDialogString(1169, "\x10""Ruby\x10" "Apparently it's much more powerful\nthan others.\x01 It's also extremely\ndifficult to get that, so we should\nbe prepared.\x01");
	SetDialogString(1170, "\x10""Sally\x10" "Ohhh, I see.\x01 Can't wait to see what\nkind of crazy stuff you'll make with\nthose things.\x01 A gem that gives you\nDemi-God powers?\x03\x20 That'd be SICK.\x01\nOr a gem that transforms you into\nanything you want without needing\nto fight him or her.\x03\x40 Or...\x01");
	SetDialogString(1171, "\x10""Ruby\x10" "That would be cool for sure.\x01");
	SetDialogString(1172, "\x10""Ruby\x10" "Let's take our final rest at a\nhotel.\x01");
	SetDialogString(1173, "\x10""Emmet\x10" "\"Final\" rest?\x01");
	SetDialogString(1174, "\x10""Ruby\x10" "Final rest before we complete the\nmission.\x01");
	SetDialogString(1175, "\x10""Sally\x10" "Ohh! Better have a good sleep, then.\x01\nSad that Noah has betrayed us...\x01");
	SetDialogString(1176, "\x10""Emmet\x10" "He didn't betray us.\x03\x20 He's not obligated\nto risk his life for a dangerous\nmission, is he?\x01");
	SetDialogString(1177, "\x10""Sally\x10" "Yeah, yeah. Let's go already.\x01");
	SetDialogString(1178, "\x10""Noah\x10" "Bye.\x01");
	
	SetDialogString(1180, "\x10""???\x10" "Yo, Ruby!\x03\x20 Noah was kidnapped.\x03\x20\nYour Noah!\x01");
	SetDialogString(1181, "\x10""Ruby\x10" "Um, proof?\x01");
	SetDialogString(1182, "\x10""???\x10" "Come visit us at Whitelight, and you'll\nsee the proof.\x01 CEO wants to make a\ndeal with you.\x01");
	SetDialogString(1183, "\x10""Ruby\x10" "What kind of deal, may I ask?\x01");
	SetDialogString(1184, "\x10""???\x10" "He... he has an Ancient Gem.\x01 That's\nall, folks!\x03\x20 Lololololololol bye\x03\x04\x03\x10");
	SetDialogString(1185, "\x10""Emmet\x10" "Hm, that's suspicious,\x03\x20 don't you\nthink?\x01");
	SetDialogString(1186, "\x10""Ruby\x10" "Indeed, I wouldn't put it past-\x01");
	SetDialogString(1187, "\x10""Sally\x10" "Omega Doodoo-blazin' F-er?\x01\nUgh, screw her!\x03\x20 Let's beat 'em up\nand save Noah.\x01");
	SetDialogString(1188, "\x10""Ruby\x10" "Haha, yeah.\x01");
	SetDialogString(1189, "\x10""Emmet\x10" "You don't look worried at all,\nRuby.\x01");
	SetDialogString(1190, "\x10""Ruby\x10" "Oh, it's nothing.\x03\x20 If they mess with\nhim, it'd be big mistake, right?\x01");
	SetDialogString(1191, "\x10""Sally\x10" "Damn right!\x03\x20 But they already made\na big mistake messing with us!\x01\nWhat could they POSSIBLY do against\na team of Sanji, Vulkan and...\x03\x40 other\nsuper powerful persona?\x01");
	SetDialogString(1192, "\x10""Emmet\x10" "Sounds like you have this under\ncontrol.\x01 Very well,\x03\x20 Whitelight company,\x03\x20\nwas it?\x01");
	SetDialogString(1193, "\x10""Sally\x10" "So that was its employee with a\nkettle mask?\x03\x20 How hilarious!\x01");
	SetDialogString(1194, "\x10""Emmet\x10" "The mask is for masking identity,\nobviously.\x01 Anyway, let's not waste more\ntime and find Noah in the Whitelight's\nbuilding.\x01");
	SetDialogString(1195, "\x10""Ruby\x10" "And the Ancient Gem, apparently?\x01\nWhatever the kettleman meant by that.\x01");
	SetDialogString(1196, "\x10""Emmet\x10" "...right.\x01");
	
	SetDialogString(1200, "\x10""???\x10" "Yo! Congratulations on passing the\nfirst floor.\x01");
	SetDialogString(1201, "\x10""Sally\x10" "It's that kettlehead we met earlier!\x03\x20\nNow tell us, where is Noah?\x01");
	SetDialogString(1202, "\x10""???\x10" "Where are your manners, blue gunk of\nhair?\x03\x20 Shouldn't we exchange our names\nfirst?\x01");
	SetDialogString(1203, "\x10""Ruby\x10" "I'm Ruby, he's Emmet and she's\nSally.\x01");
	SetDialogString(1204, "\x10""???\x10" "Heh, a nice and brief introduction,\nis it?\x03\x20 Name's \x10Timon\x10 Timon by the way.\x01\nSo what have you come for again?\x03\x20\nHaving a teaparty?\x01");
	SetDialogString(1205, "\x10""Sally\x10" "Yeah, after we beat you up and\nrescue Noah.\x01");
	SetDialogString(1206, "\x10""Emmet\x10" "No, no, we're just here to bring\nNoah with us...\x03\x20 You know where he is?\x01");
	SetDialogString(1207, "\x10""Timon\x10" "Which Noah are we talking about?\x01\nThat character from the film \"Threads\nof the Wacky Geese\"?\x01 That's... a\nfictional character, right?\x01 Or are you\ntrying to get in contact with its\nactor?\x01");
	SetDialogString(1208, "\x10""Sally\x10" "Ugh... what an idiot.\x01");
	SetDialogString(1209, "\x10""Ruby\x10" "My Noah, the one you said that got\nkidnapped, right?\x01");
	SetDialogString(1210, "\x10""Timon\x10" "I'm just messing with ya.\x03\x20 Man, your\nfaces are priceless!\x03\x20 Your Noah is\nhanging around in the 3rd floor.\x01\nDid you want to get access to there?\x01");
	SetDialogString(1211, "\x10""Emmet\x10" "Yes, but I suppose we have to do\nsomething first?\x01");
	SetDialogString(1212, "\x10""Timon\x10" "Certainly, yes.\x03\x20 You will have to beat\nme at Hide and Seek.\x01");
	SetDialogString(1213, "\x10""Emmet\x10" "Wait, what?\x01");
	SetDialogString(1214, "\x10""Timon\x10" "You will be the seekers, and I will\nbe the hider.\x01");
	SetDialogString(1215, "\x10""Sally\x10" "Hide and Seek?\x03\x20 Are\x03\x10 you\x03\x10 SERIOUS?\x01");
	SetDialogString(1216, "\x10""Timon\x10" "Now, listen carefully.\x03\x20 At the start,\nyou three will begin a countdown inside\nthe wardrobes on that corner of this\nroom.\x01 You will count to 10, and I will\nfind myself a hiding spot in that\ntime.\x01");
	SetDialogString(1217, "\x10""Sally\x10" "Hey, LISTEN, we need to rescue\nNoah!\x03\x20 We ain't got NO time for\nthis nonsense!\x03\x20 Just-\x01");
	SetDialogString(1218, "\x10""Timon\x10" "After you're done counting, you\ncome out of the wardrobes and start\nlooking for-\x01");
	SetDialogString(1219, "\x10""Sally\x10" "STOP wasting our time!\x03\x20 We know\nhow to-\x03\x06");
	SetDialogString(1220, "\x10""Timon\x10" "...15 seconds before you find\nme.\x03\x20 If you manage to find me,\nyou get the access to the third\nfloor.\x01 Otherwise, you will have to try\nagain.\x01 Did you get the rules?\x01");
	SetDialogString(1221, "\x10""Sally\x10" "Nah, we'll break your kettle and\nget the access our-\x01");
	SetDialogString(1222, "\x10""Ruby\x10" "Calm down, Sally.\x03\x20 Let's just play along\nfor now.\x01");
	SetDialogString(1223, "\x10""Sally\x10" ".\x03\x20.\x03\x20.\x03\x20okay.\x01");
	SetDialogString(1224, "\x10""Timon\x10" "Now, follow me, folks.\x01");
	
	SetDialogString(1230, "\x10""Sally\x10" "Noah!\x01");
	SetDialogString(1231, "\x10""Sally\x10" "You're okay?\x03\x20 We're here to save you.\x01");
	SetDialogString(1232, "\x10""???\x10" "Hold it!\x01");
	SetDialogString(1233, "\x10""???\x10" "Oh, if it isn't Ruby,\x03\x20 the young and\nbrilliant inventor.\x01");
	SetDialogString(1234, "\x10""Ruby\x10" "You're the Whitelight CEO?\x01");
	SetDialogString(1235, "\x10""???\x10" "Indeed,\x03\x20 my name is \x10Rob\x10Rob.\x01 I brought\nyou here to discuss an important deal.\x01");
	SetDialogString(1236, "\x10""Emmet\x10" "What is Noah doing here, by the\nway?\x01");
	SetDialogString(1237, "\x10""Rob\x10" "He's working a part-time job.\x03\x20 As a\nbutler of this office.\x01 You may be\nconcerned about him, but he's doing\nwell, don't you see?\x01");
	SetDialogString(1238, "\x10""Emmet\x10" "This seems rather shady to me...\x01");
	SetDialogString(1239, "\x10""Noah\x10" "He's right, I'm doing fine.\x01 Don't worry\nabout me...\x01");
	SetDialogString(1240, "\x10""Emmet\x10" "Have you signed a phony contract per\nchance, Noah?\x03\x20 If so, we won't be able\nto help much.\x01 Turning a blind eye to\nthis sort of stuff is more dangerous\nthan you might think, you know.\x01");
	SetDialogString(1241, "\x10""Ruby\x10" "So what is the deal exactly about?\x03\x20\nEmployee Timon said it involved Ancient\nGems or something, correct?\x01");
	SetDialogString(1242, "\x10""Rob\x10" "I'm afraid he was wrong.\x03\x20 It was a\npart of bait, you see.\x01 What I really\nwant from you is that little thingy\nthat gives you powers and shape from\nother people...\x01");
	SetDialogString(1243, "\x10""Ruby\x10" "Oh no, I am not giving the Magical\nGem away.\x03\x20 It was made by me,\x03\x20 and it\nshall be mine forever.\x01");
	SetDialogString(1244, "\x10""Rob\x10" "I see...\x03\x40 Mani.\x01");
	SetDialogString(1245, "\x10""Mani\x10" "H-Huh?\x01");
	SetDialogString(1246, "\x10""Rob\x10" "Brief the Report of the Light, please.\x01");
	SetDialogString(1247, "\x10""Mani\x10" "Uhh, okay.\x03\x20 Um...\x01 No anomalies are\ndetected, sir.\x01");
	SetDialogString(1248, "\x10""Rob\x10" "Too brief, can you give a bit more\ndetail?\x01");
	SetDialogString(1249, "\x10""Mani\x10" "Oh sorry...\x03\x20 So...\x01 No anomalies have\nbeen detected in at least 28 hours...\x01\nPrognosis states that it will remain\nthat way for the next 2 hours or\nmore...\x01");
	SetDialogString(1250, "\x10""Rob\x10" "...\x03\x20""Are you certain, Mani?\x01");
	SetDialogString(1251, "\x10""Mani\x10" "M-yes!\x03\x20 The report has been verified\nby the responsible section of\nWhitelight,\x03\x20 sir.\x01");
	SetDialogString(1252, "\x10""Rob\x10" "Ah,\x03\x20 so,\x03\x20 like,\x03\x20 no policing for a few\nhours,\x03\x20 am I correct?\x01");
	SetDialogString(1253, "\x10""Mani\x10" "...Yes.\x03\x20 Report of the Light says the\ncurrent level of Availability is 4\nout of 5.\x01");
	SetDialogString(1254, "\x10""Rob\x10" "Well, that's perfect.\x01");
	SetDialogString(1255, "\x10""Emmet\x10" "Excuse me?\x03\x20 What are you talking\nabout?\x01");
	SetDialogString(1256, "\x10""Rob\x10" "Business stuff, you know.\x01");
	SetDialogString(1257, "\x10""Timon\x10" "Availability level 4?\x03\x20 Are you gonna\nfight them or-...\x03\x20 err...\x01");
	SetDialogString(1258, "\x10""Sally\x10" "Fight who, us?\x03\x20 I've heard that\ncorrectly?\x01");
	SetDialogString(1259, "\x10""Rob\x10" "Yeah, our Availability level is high\nenough for us to apply violence\nwithout many consequences.\x01 If it was\nlevel 3, I would've offered you a bunch\nof cash, but...\x01\nRuby, you'd better accept this trade\nright now.\x01 I get your Magical Gem, and\nyou get nothing...\x03\x20 and won't have\nto suffer an unnecessary battle.\x01");
	SetDialogString(1260, "\x10""Ruby\x10" "No.\x01");
	SetDialogString(1261, "\x10""Sally\x10" "Hmph.\x03\x20 *yawns*\x03\x20 Easy victory.\x01 Thanks\nfor the free armor and skills, who's\nnext?\x01");
	SetDialogString(1262, "\x10""Emmet\x10" "Wait, let's...\x01");
	SetDialogString(1263, "\x10""Emmet\x10" "Hey, Noah, come with us!\x01");
	SetDialogString(1264, "\x10""Timon\x10" "Yo, don't you dare to bother him!\x03\x20\nHe needs to pay his rent, after all!\x01");
	SetDialogString(1265, "\x10""Ruby\x10" "Hm?\x03\x20 You're joining us?\x01");
	SetDialogString(1266, "\x10""Noah\x10" "Umm, yeah.\x01 Thinking about it, that\nRob guy really is shady.\x03\x20 I'm dumb,\nI shouldn't have applied for this...\x01");
	SetDialogString(1267, "\x10""Ruby\x10" "Don't worry, just...\x01");
	SetDialogString(1268, "\x10""Rob\x10" "You...\x03\x20 you can't just retire on your\nfirst day.\x01 Are you nuts?\x01");
	SetDialogString(1269, "\x10""Sally\x10" "Too bad!\x03\x20 What are you gonna do\nabout it?\x01");
	SetDialogString(1270, "\x10""Rob\x10" "Anyway,\x03\x20 Ruby,\x03\x20 I'll give you a minute to\nrethink your decision.\x01 Take another\nstep, and the fight will start, is that\nclear?\x01");
	SetDialogString(1271, "\x10""Ruby\x10" "(This is my chance to open inventory\nand adjust Noah's skills and armor!)\x01");
	SetDialogString(1272, "\x10""Rob\x10" "So you made your decision then.\x01\nMani, Timon, let's do our job!\x01");
	SetDialogString(1273, "\x10""Mani\x10" "Okay!\x01");
	SetDialogString(1274, "\x10""Timon\x10" "But of course!\x03\x20 Yo, I'll send you folks\nstraight to a teaparty!\x01");
	SetDialogString(1275, "\x10""Sally\x10" "ok\x03\x02");
	SetDialogString(1276, "\x10""Rob\x10" "Wow... I must have underestimated you.\x01\nYou are getting way too strong.\x01");
	SetDialogString(1277, "\x10""Sally\x10" "Told you, easy victory for us.\x01");
	SetDialogString(1278, "\x10""Rob\x10" "Okay, since I couldn't defeat you...\x01\nI'll give you $5000000 for that Magical\nGem.\x03\x20 Deal?\x01");
	SetDialogString(1279, "\x10""Ruby\x10" "$5000000?\x01");
	SetDialogString(1280, "\x10""Ruby\x10" "(But that's my only Magical Gem...\x03\x20\nIf I give it away, I might never make\nanother one.\x01 But with that money,\x03\x20 I\ncould move into a better country and\nlive a nice life for many years...)\x01");
	SetDialogString(1281, "\x10""Ruby\x10" "(Wait, no.\x03\x20 I wouldn't be able to\ncomplete my mission.\x03\x20 That would go\nagainst the Contract.)\x01");
	SetDialogString(1282, "\x10""Ruby\x10" "Mmm... nope.\x01");
	SetDialogString(1283, "\x10""Rob\x10" "...So there's nothing I can do to\nget hands on that powerful weapon...\x01\nDude, just imagine what we could do\nwith this awesome power.\x03\x20 We could\noverthrow the government with this!\x01");
	SetDialogString(1284, "\x10""Rob\x10" "Anywho... I have nothing else to talk\nabout.\x03\x20 Noah, you're fired, by the way.\x01");
	SetDialogString(1285, "\x10""Noah\x10" "Okay.\x01");
	
	SetDialogString(1290, "\x10""Ruby\x10" "Finally,\x03\x20 let's rest ourselves in a\nhotel.\x01");
	SetDialogString(1291, "\x10""Sally\x10" "Yes!\x03\x20 Today was a bit rough...\x01");
	SetDialogString(1292, "\x10""Emmet\x10" "At least we got Noah back in our\nteam.\x01");
	SetDialogString(1293, "\x10""Ruby\x10" "Yeah...\x03\x20 Hey, Noah.\x01");
	SetDialogString(1294, "\x10""Noah\x10" "What?\x01");
	SetDialogString(1295, "\x10""Noah\x10" "...Thanks?\x01");
	SetDialogString(1296, "\x10""Ruby\x10" "Sorry about that.\x01");
	SetDialogString(1297, "\x10""Sally\x10" "Nah, it's fine to hug once in a\nwhile!\x01");
	SetDialogString(1298, "\x10""Ruby\x10" "I guess. Let's move on.\x01");
	SetDialogString(1299, "\x10""Noah\x10" "Wait, Ruby, you can have the money\nback.\x01 And my first-time Whitelight job\nreward.\x01");
	SetDialogString(1300, "You got $400 + the money given to\nNoah earlier.\x01");
	
	SetDialogString(1301, "\x10""???\x10" "Hold up right there..\x01");
	SetDialogString(1302, "\x10""Amp\x10" "What are you four doing here?!\x01\nWho let you in here?\x01");
	SetDialogString(1303, "\x10""Ruby\x10" "Flora did.\x03\x20 I only wanted to get\nthe Ancient Gem over there.\x01");
	SetDialogString(1304, "\x10""Amp\x10" "Hold the phone...\x03\x30 That is the\ntreasure of my family.\x01 It was earned\nvia hard work,\x03\x20 so if anyone wanted\nto get their hands on it...\x01 they'd\nhave to offer millions of cash or fight\nfor it.\x01");
	SetDialogString(1305, "\x10""Ruby\x10" "I see...\x03\x30 We'll fight for it.\x01");
	SetDialogString(1306, "\x10""Amp\x10" "Ah,\x03\x20 I think I know how you\nmanaged to get this far.\x01 You used\nthe power of modern technology to\ncapture and replicate the likeness\nand prowess of the opposing entities.\x01\nVery clever,\x03\x20 Ruby.\x01");
	SetDialogString(1307, "\x10""Amp\x10" "However...\x03\x30 let me tell you this.\x01\nAncient Gems are an unsolved mystery.\x01\nPeople know they exist, but have no\nidea of their-\x01");
	SetDialogString(1308, "\x10""Sally\x10" "Blah blah...\x03\x20 we've heard it before,\x03\x20\nso cut it with your history lesson.\x01");
	SetDialogString(1309, "\x10""Amp\x10" "Oh...\x03\x20 so you know everything about\nit.\x01 Then what are we waiting for?\x03\x30\nI'll fight you,\x03\x20 but first,\x03\x20 let's\ngive ourselves more space.\x01");
	SetDialogString(1310, "\x10""Amp\x10" "Ruby,\x03\x20 Emmet,\x03\x20 Sally,\x03\x20 Noah.\x01\nYour adventure ends here!!\x01");
	SetDialogString(1311, "\x10""Amp\x10" "So that's how it concludes.\x01");
	SetDialogString(1312, "\x10""Amp\x10" "With how powerful you're becoming\nquickly...\x03\x30 I'm sure the Onyx\nMinistry must be aware of your\nantics at this point.\x01");
	SetDialogString(1313, "\x10""Ruby\x10" "So I can't take a break, huh.\x01");
	SetDialogString(1314, "\x10""Sally\x10" "The Onyx Ministry knows?\x03\x20 Is that a\ngood sign?\x01");
	SetDialogString(1315, "\x10""Emmet\x10" "Hmmm...\x03\x20 I don't know, Sally.\x01\nDo you want to be hunted down by\nthe Gemia's government for a long\ntime?\x01");
	SetDialogString(1316, "\x10""Sally\x10" "Eh,\x03\x20 we can eventually overpower\nthem.\x01 Not worried at all,\x03\x20 plus that'd\ngive us a chance to become the\nstrongest force in the world,\x03\x20\nright?\x01");
	SetDialogString(1317, "\x10""Emmet\x10" "Hahaha.\x03\x20 You're so funny.\x01");
	SetDialogString(1318, "\x10""Sally\x10" "What?\x03\x20 What're you laughing at?\x01");
	SetDialogString(1319, "\x10""Amp\x10" "I can't really know about your\nlimits,\x03\x20 but...\x03\x30 I HIGHLY doubt\nyou can ever become strong enough to\ntake on any Ministry of Gemia.\x01\nIt is extremely unlikely.\x01");
	SetDialogString(1320, "\x10""Amp\x10" "Now...\x03\x20 where was I?\x01 The Ancient\nGem.\x03\x20 Take it and kindly leave.\x01");
	
	SetDialogString(1321, "\x10""Kara\x10" "Ruby!\x03\x20 Did you settle things with\nAmp?\x01");
	SetDialogString(1322, "\x10""Ruby\x10" "Yes.\x03\x20 I fought her and got the\nAncient Gem.\x01");
	SetDialogString(1323, "\x10""Kara\x10" ".\x03\x20.\x03\x20.\x03\x20you defeated her?\x03\x20 Seriously?\x01");
	SetDialogString(1324, "\x10""Ruby\x10" "Seriously.\x01");
	SetDialogString(1325, "\x10""Kara\x10" "You are a star, Ruby!\x03\x30 Oh,\x03\x20 you\nare stars too!\x01");
	SetDialogString(1326, "\x10""Ruby\x10" "Uh, thanks.\x03\x20 We're going to Brilliant\nMountains next.\x01");
	SetDialogString(1327, "\x10""Noah\x10" "Brilliant... Mountains?\x03\x20 Why?\x01");
	SetDialogString(1328, "\x10""Ruby\x10" "Oh, well...\x01");
	SetDialogString(1329, "\x10""Emmet\x10" "That's where the last Ancient Gem\nis, Noah.\x01 I recall her saying that\ngem is the most powerful and valuable\nout of the others...\x01");
	SetDialogString(1330, "\x10""Sally\x10" "Yeah,\x03\x20 the 4 gems we have right\nnow are all...\x03\x40 just part of training?\x01");
	SetDialogString(1331, "\x10""Kara\x10" "Are you...\x03\x30 selling artifacts for a\nliving?\x01");
	SetDialogString(1332, "\x10""Ruby\x10" "...\x03\x20I guess,\x03\x20 if you put it that\nway.\x01");
	SetDialogString(1333, "\x10""Emmet\x10" "How are we going to get to the\nmountains, Ruby?\x01 The border is closed,\x03\x20\nand the officers will not let any\nordinary citizen or tourist to pass\nthrough...\x01 Did you think of a\nplan?\x01");
	SetDialogString(1334, "\x10""Ruby\x10" "I...\x03\x30 umm...\x03\x40 I don't know.\x01");
	SetDialogString(1335, "\x10""Kara\x10" "Hey,\x03\x20 I can help you out if\nyou want, Ruby.\x01");
	SetDialogString(1336, "\x10""Ruby\x10" "Oh...\x03\x20sure!\x03\x20 I don't mind help at\nall.\x01");
	SetDialogString(1337, "\x10""Kara\x10" "I know a friend of mine that works\nin a border job.\x01 If you want,\x03\x20 I can\ngive 'im a quick call and get\nyou papers prepared for entry.\x01");
	SetDialogString(1338, "\x10""Ruby\x10" "How long will it take?\x01");
	SetDialogString(1339, "\x10""Kara\x10" "Oh,\x03\x20 you won't have to wait for\nlong at all.\x01 It's a really short\nand quick process...\x03\x40 You will get\nthe documents ready literally in\n5 days after the call!\x01 Can you\nbelieve it?\x03\x30 I don't,\x03\x20 but it really\nis that quick!\x01");
	SetDialogString(1340, "\x10""Ruby\x10" "5 days?\x03\x20 That's...\x03\x30 too long?\x01\nI'd prefer...\x03\x30 5 minutes at most.\x01");
	SetDialogString(1341, "\x10""Kara\x10" "Oh...\x01 did you want to get there\nimmediately?\x01 Well, don't worry.\x03\x20\n'cause this is what we call...\x01");
	SetDialogString(1342, "\x10""Kara\x10" "Kara EX MACHINA!!!\x01\nI have just the solution you seek!\x01\nBehold...\x01");
	SetDialogString(1343, "\x10""Kara\x10" "My own papers!\x03\x30 Hahaha...\x01");
	SetDialogString(1344, "\x10""Ruby\x10" "Thanks.\x03\x20 I will return it when\nI finish my trip there.\x01 If I\nsurvive, that is.\x01");
	SetDialogString(1345, "\x10""Kara\x10" "Ah,\x03\x20 keep it please.\x01 I give\nit to you permamently.\x01");
	SetDialogString(1346, "\x10""Kara\x10" "Bye, visit us again sometime!\x01");
	SetDialogString(1347, "\x10""Emmet\x10" "I wonder...\x03\x30 why is Kara helping us\nso passionately?\x01");
	SetDialogString(1348, "\x10""Ruby\x10" "She seems trustworthy.\x01 These papers\nwon't hurt us, right?\x01 I don't sense\npoison nor see any illegal symbols\nprinted in there that could imprison\nus...\x01");
	SetDialogString(1349, "\x10""Sally\x10" "If I were to go to prison for\naccidentally showing \"illegal\nsymbols\"...\x01 That would absolutely break\nme.\x01\nOkay let's go, we talked enough.\x01");
	SetDialogString(1350, "\x10""Ruby\x10" "So true...\x01");
	
	SetDialogString(1351, "\x10""???\x10" "...\x01You must be heading towards the\nBrilliant Mountains.\x01");
	SetDialogString(1352, "\x10""???\x10" "The place of the cursed.\x03\x40\nThe place of the abandoned.\x03\x40\nThe place of the illusion.\x03\x40\nThe place of the doom.\x01\nBrilliant Mountains.\x03\x40 The graveyard of\nthe technology and experiments.\x01\nIt is the beginning of a blur\nbetween the Real Space and the\x03\x20\nMaya.\x01");
	SetDialogString(1353, "\x10""???\x10" "Hello?\x03\x20 Do you... hear me?\x01");
	SetDialogString(1354, "\x10""Ruby\x10" "Yes, I've heard you the entire\ntime.\x01");
	SetDialogString(1355, "\x10""???\x10" "Ah, okay!\x01 Lemme see...\x03\x40 Hmmm.\x01\nWho are you, may I ask?\x01");
	SetDialogString(1356, "\x10""Ruby\x10" "Ruby.\x03\x20 Who are you?\x01");
	SetDialogString(1357, "\x10""???\x10" "...\x03\x30I am an...\x03\x20 undercover agent.\x01\nSo you're headed to Brilliant\nMountains, am I correct?\x01");
	SetDialogString(1358, "\x10""Ruby\x10" "Mhm.\x01");
	SetDialogString(1359, "\x10""???\x10" "I'll tell you advice.\x01 Beware the\nGeminis...\x03\x30 The sentient floating gems\nthat inhibit intense power.\x01\nGeminis can easily wipe your\nface off the earth if you are\nunderprepared, haha.\x01 That's one of\nthe legends of Gemia.\x01");
	SetDialogString(1360, "\x10""???\x10" "And,\x03\x20 um,\x03\x20 I ran out of useful things\nto say.\x03\x30 Sorry...\x01");
	SetDialogString(1361, "\x10""Ruby\x10" "It happens,\x03\x20 don't worry.\x01");
	SetDialogString(1362, "\x10""???\x10" "Haha...\x03\x30 I was only wondering.\x01\nI was wondering about you,\x03\x20 'cause\nI was going to...\x03\x20 go to Brilliant\nMountains,\x03\x20 y'know...\x03\x20 to relax,\x03\x20\nto collect some sorts of unique\nplants,\x03\x20 and 'cause I am Lulu\nand I came here to destroy you.\x03\x30");
	SetDialogString(1363, "\x10""Lulu\x10" "Yes, you heard it correctly!\x01\nI'm Lulu...\x03\x30 Master Lulu.\x01\nBown dow!!\x01");
	SetDialogString(1364, "\x10""Lulu\x10" "I mean,\x03\x20 bown dow-\x03\x20.\x03\x20.\x03\x20.\x03\x40\nDown bow...\x03\x20 BOLLOCKS!\x03\x20 You get\nit.\x01");
	SetDialogString(1365, "\x10""Emmet\x10" "Wow, didn't recognize that voice\nat first...\x03\x20 did it become deeper?\x01");
	SetDialogString(1366, "\x10""Sally\x10" "The voice is the first thing you\nnotice?\x01 She's got a really big\nwig this time for some reason...\x01\nA wigtail?\x01");
	SetDialogString(1367, "\x10""Lulu\x10" "That is because I haven't seen you\nin a month.\x01 No,\x03\x20 I'm serious.\x03\x20 While\na day has passed for you,\x03\x20 I was\ntraining hard in a time-accelerated\nenvironment.\x01 It was really costly,\x03\x20 but\nnow I've surpassed all of my relatives\nat this point!\x01");
	SetDialogString(1368, "\x10""Noah\x10" "Is she an oligarch?\x01");
	SetDialogString(1369, "\x10""Ruby\x10" "Looks like it.\x03\x30 Or it was a part of\na very shady experiment or deal,\x03\x20 not\nunlike that SYNC hit-list stuff.\x01");
	SetDialogString(1370, "\x10""Lulu\x10" "I feel sorry for you, Ruby.\x01\nYou dare to have the name\n\"Ruby\" and be in the poor class?\x01");
	SetDialogString(1371, "\x10""Ruby\x10" "Look at my pockets, peasant.\x01");
	SetDialogString(1372, "\x10""Lulu\x10" "O_O\x01\nHAW DO YUU HAVWH SW MOOCH\nMOUNEH\x01");
	SetDialogString(1373, "\x10""Ruby\x10" "I was mining off-camera.\x01 Anyway,\x03\x20\ndid you just try to poor-shame\nme right now?\x01");
	SetDialogString(1374, "\x10""Ruby\x10" "Are you resorting to poor-shaming\nme?\x01");
	SetDialogString(1375, "\x10""Lulu\x10" "No, no.\x03\x20 Let's be friends!\x01\nWait,\x03\x20 I didn't train myself for\neternity for no reason!\x01");
	SetDialogString(1376, "\x10""Lulu\x10" "Ruby...\x03\x30 This is our \x03\x10""F\x03\x10I\x03\x10N\x03\x10""A\x03\x10L\x03\x10 battle.\x01\nAnd I'll make this one COUNT!!\x01");
	SetDialogString(1377, "\x10""Lulu\x10" "Ok, and?\x03\x30 That's not impressive at\nall.\x01 If you had JUST 1 more dollar...\x03\x50\nnow THAT would make my jaw drop\nand make me mega-jealous for the\nrest of my life.\x01");
	SetDialogString(1378, "\x10""Lulu\x10" "N-no....\x03\x30 No...\x03\x40 Hhh...\x01");
	SetDialogString(1379, "NOTE: All swear words and slurs will\nbe replaced with following words:\x01\n\x80\x0a\x01,\x03\x20 \x80\x0a\x02,\x03\x20 \x80\x0a\x03,\x03\x20 \x80\x0a\x04,\x03\x20 \x80\x0a\x05,\x03\x20 \x80\x0a\x06,\x03\x20 \x80\x0a\x07,\x03\x20 and \x80\x0a\x08.\x01");
	SetDialogString(1380, "\x10""Lulu\x10" "\x80\x0a\x03 \x80\x0a\x01 \x80\x0a\x04 OF \x80\x0a\x02!!\x01\n\x80\x0a\x06 \x80\x0a\x07 \x80\x0a\x02 YOUR \x80\x0a\x08 \x80\x0a\x04 \x80\x0a\x06 WITH \x80\x0a\x01 \x80\x0a\x02!!!\x01 \x80\x0a\x05 TO \x80\x0a\x04 \x80\x0a\x01 \x80\x0a\x02,\x03\x20 \x80\x0a\x06 \x80\x0a\x07 \x80\x0a\x08!!\x01\n\x80\x0a\x01 RUBY \x80\x0a\x02 THE \x80\x0a\x03 \x80\x0a\x04,\x03\x20 \x80\x0a\x05 \x80\x0a\x06 ON \x80\x0a\x07 \x80\x0a\x08!!!\x01\nYOU ALL NEED TO \x80\x0a\x06 \x80\x0a\x03 \x80\x0a\x01 AND \x80\x0a\x08 \x80\x0a\x02 \x80\x0a\x01!!!\x01");
	SetDialogString(1381, "\x10""Sally\x10" "Holy crap,\x03\x20 calm down.\x01 How many\nmore offensive words are you going to\nthrow at us?\x01");
	SetDialogString(1382, "\x10""Lulu\x10" "\x80\x0a\x06 SALLY \x80\x0a\x04!!!\x01 \x80\x0a\x03 THE \x80\x0a\x08 \x80\x0a\x01!!!\x01");
	SetDialogString(1383, "\x10""Sally\x10" "No,\x03\x20 D.I.Y. (Do It Yourself.)\x01");
	SetDialogString(1384, "\x10""Emmet\x10" "Yes,\x03\x20 there are guides for that\nonline!\x01 You could learn how to clear\nyour thoughts,\x03\x20 take a deep breath and\nadmit that you have lost.\x01");
	SetDialogString(1385, "\x10""Noah\x10" "Yes,\x03\x20 even the strongest heroes have\nlost to us.\x01 There's no shame in losing\nto us,\x03\x20 Lulu.\x01");
	SetDialogString(1386, "\x10""Ruby\x10" "(actually we lost to one but don't\ntell her noah)\x01");
	SetDialogString(1387, "\x10""Lulu\x10" "But I thought I could dodge\nEVERYTHING!\x03\x20 And I still lost!\x01");
	SetDialogString(1388, "\x10""Lulu\x10" "*sigh*\x03\x30 I can't believe this!\x01\nI cant...\x03\x30 I...\x01");
	SetDialogString(1389, "\x10""Noah\x10" "...?!\x01");
	SetDialogString(1390, "\x10""Sally\x10" "What are you doing?\x03\x20 Release him or\nelse!\x01");
	SetDialogString(1391, "\x10""Lulu\x10" "Haha...\x03\x20 Let's meet up again someday,\x03\x20\nNoah.\x01");
	SetDialogString(1392, "\x10""Noah\x10" "...\x01");
	SetDialogString(1393, "\x10""Noah\x10" "I guess we're not seeing her again?\x01");
	SetDialogString(1394, "\x10""Emmet\x10" "Looks like Lulu has accepted her\nultimate loss.\x01 Don't think she's coming\nback.\x01");
	SetDialogString(1395, "\x10""Sally\x10" "Thank GOD,\x03\x20 those must be the most\ninsane skills I've ever seen...\x03\x20 Holy\nhell.\x01 But at least we get to use\nit on others!\x01");
	SetDialogString(1396, "\x10""Ruby\x10" "Uh,\x03\x20 well done Noah?\x01");
	SetDialogString(1397, "\x10""Noah\x10" "What?\x01");
	SetDialogString(1398, "\x10""Ruby\x10" "For convincing Lulu.\x01");
	SetDialogString(1399, "\x10""Noah\x10" "I don't think that did anything.\x01\nThough,\x03\x20 I wish I hugged her back,\x03\x20\nshe was kinda cute there...\x01");
	SetDialogString(1400, "\x10""Sally\x10" "C'mon, Noah, don't fall for her!\x03\x30\nLet's instead complete the mission once\nand for all!\x01");
	SetDialogString(1401, "\x10""Noah\x10" "Ok, Sally...\x03\x20 let's go.\x01");
	
	SetDialogString(1410, "\x10""Sally\x10" "What the hell?\x03\x30 Is that a flying\npiece of minerals?\x01");
	SetDialogString(1411, "\x10""Noah\x10" "...I think so.\x01");
	SetDialogString(1412, "\x10""Ruby\x10" "It is approaching.\x03\x20 Be careful!\x01");
	SetDialogString(1413, "\x10""Emmet\x10" "That must be one of Geminis!\x01");
	SetDialogString(1414, "\x10""Ruby\x10" "Yes,\x03\x20 Lulu warned us about them.\x01\nI wonder how strong they are...\x03\x30\nlet's find out!\x01");
	SetDialogString(1415, "\x10""Ruby\x10" "Wow,\x03\x20 those skills are killers!\x01");
	SetDialogString(1416, "\x10""Sally\x10" "Dammit.\x03\x20 Really wish I could summon a\ntsunami out of nowhere.\x01");
	
	SetDialogString(1420, "\x10""Noah\x10" "What happened?\x03\x30 Did you get it, Ruby?\x01");
	SetDialogString(1421, "\x10""Ruby\x10" "Uh...\x03\x30 I don't think so.\x01");
	SetDialogString(1422, "\x10""???\x10" "I did.\x01");
	SetDialogString(1423, "\x10""Emmet\x10" "Wait,\x03\x20 what's going on?\x01 Is this supposed\nto happen?\x01");
	SetDialogString(1424, "\x10""Sally\x10" "Is it me or I am hearing somebody's\nvoice?\x01");
	SetDialogString(1425, "\x10""Ruby\x10" "I heard it as well.\x01 I have a feeling\nthat...\x01");
	SetDialogString(1426, "\x10""???\x10" "Look up, idiots!!\x01");
	SetDialogString(1427, "\x10""Lulu\x10" "Psyche!\x01 Nice to meet you all...\x03\x30\ndid you miss me?\x01");
	SetDialogString(1428, "\x10""Sally\x10" "Get the HELL outta here.\x01");
	SetDialogString(1429, "\x10""Lulu\x10" "Oh okay,\x03\x20 see you later then!\x01\nHope you don't mind me taking the red\nbrilliant thingy with me!\x01");
	SetDialogString(1430, "\x10""Sally\x10" "NO WAIT!\x01");
	SetDialogString(1431, "\x10""Lulu\x10" "Hahahaha!\x01");
	SetDialogString(1432, "\x10""Ruby\x10" "Lulu,\x03\x20 please give that gem to me.\x01");
	SetDialogString(1433, "\x10""Lulu\x10" "Why would I?\x01");
	SetDialogString(1434, "\x10""Ruby\x10" "...\x03\x20we worked hard for it.\x01");
	SetDialogString(1435, "\x10""Lulu\x10" "And?\x01");
	SetDialogString(1436, "\x10""Emmet\x10" "You're trying to steal from us!\x01\nWe got it fair and square,\x03\x20 we had to\ndefeat an extremely powerful monster\nin the process!\x01 And now you're trying\nto ruin Ruby's whole plan?!\x01");
	SetDialogString(1437, "\x10""Lulu\x10" "There, there, don't worry, boys and\ngirls,\x03\x20 I'll give it back, okay?\x01\n...after you defeat me, of course.\x01");
	SetDialogString(1438, "\x10""Sally\x10" "She'll never learn, huh?\x03\x30 Let's kick\nher ass once again.\x01");
	SetDialogString(1439, "\x10""Lulu\x10" "No,\x03\x20 you will be fighting a scripted\nloss battle.\x01 No matter what you do,\x03\x20\nyou can never win.\x01 Why?\x03\x20 Because\nI am now a GOD.\x03\x30 God Lulu!!\x01");
	SetDialogString(1440, "\x10""Lulu\x10" "Come at me,\x03\x20 fools!!\x01");
	SetDialogString(1441, "\x10""Lulu\x10" "It's over, Ruby.\x01 You are going to die\nright now!!\x01");
	SetDialogString(1442, "\x10""Ruby\x10" "No, I won't.\x01 What actually will happen\nis that you will get ready to unleash\na final attack on me...\x01 but stop at\nthe last moment because you can't kill\na person or something.\x01");
	SetDialogString(1443, "\x10""Lulu\x10" "What?\x03\x20 Of course I CAN kill a person,\x03\x20\nwhat are you talking about??\x01");
	SetDialogString(1444, "\x10""Ruby\x10" "Because you are a fool who only\ngives false promises.\x01 Am I wrong?\x01");
	SetDialogString(1445, "\x10""Ruby\x10" "You can't kill me and you can't\nprove me wrong...\x03\x30 I can guarantee you\nthat 100% without any doubts.\x01");
	SetDialogString(1446, "\x10""Lulu\x10" "You don't get to decide who can\nbe killed or not!!\x03\x30 I WILL prove you\nwrong,\x03\x20 bastard!!\x01");
	SetDialogString(1447, "\x10""Lulu\x10" "D\x03\x10""I\x03\x10""E\x03\x10"",\x03\x10"" \x03\x10""R\x03\x10""U\x03\x10""B\x03\x10""Y\x03\x10""!\x01");
	SetDialogString(1448, "\x10""Lulu\x10" ".\x01");
	SetDialogString(1449, "\x10""Ruby\x10" "And you failed,\x03\x20 yet again.\x01");
	SetDialogString(1450, "\x10""Lulu\x10" "Shut up.\x01 I just...\x03\x20 realized something.\x01");
	SetDialogString(1451, "\x10""Lulu\x10" "I c-can't...\x03\x30 I don't want...\x03\x40\nI don't...\x01");
	SetDialogString(1452, "\x10""Lulu\x10" "SCREW EVERYTHING!!\x01");
	SetDialogString(1453, "\x10""Sally\x10" "Oof...\x03\x30 did we...\x03\x30 win?\x01");
	SetDialogString(1454, "\x10""Emmet\x10" "No, we did not.\x01 I have no clue why\nshe's crying right now...\x01");
	SetDialogString(1455, "\x10""Sally\x10" "So she really isn't a god that she\nclaimed to be then?\x01");
	SetDialogString(1456, "\x10""Lulu\x10" "Of course not!\x01 I'm no more than your\naverage Supernatural...\x01");
	SetDialogString(1457, "\x10""Emmet\x10" "Makes sense.\x01 There has never been a\nrecorded instance of a being having the\ntitle of a \"GOD\"...\x01");
	SetDialogString(1458, "\x10""Sally\x10" "What about Gemia and the Goddess\nTrinity?\x01");
	SetDialogString(1459, "\x10""Emmet\x10" "Shhhh...\x03\x30 (they aren't real \"gods\")\x01");
	SetDialogString(1460, "\x10""Ruby\x10" "Hey,\x03\x20 don't cry, Lulu.\x01 Maybe you need\nhelp with something?\x01");
	SetDialogString(1461, "\x10""Lulu\x10" "Why did I do this?!\x01 I'm going to be\nbullied by the elite because I've got\ntoo strong or scary...\x01 And now I have\nb-betrayed my family...\x03\x30 and my loans\nare h-huge...\x01 I don't know what to do.\x01");
	SetDialogString(1462, "\x10""Emmet\x10" "Hey,\x03\x30 you can sell that Ancient-\x03\x10");
	SetDialogString(1463, "\x10""Emmet\x10" "Oh,\x03\x20 oops.\x01");
	SetDialogString(1464, "\x10""Lulu\x10" "I...\x03\x20 I know,\x03\x20 but...\x01");
	SetDialogString(1465, "\x10""Ruby\x10" "Well...\x03\x20 I don't know how we're going\nto solve your huge loans,\x03\x20 but...\x01\nMaybe we could reach some sort of\nagreement?\x01");
	SetDialogString(1466, "\x10""Lulu\x10" "You won't help me with anything!\x01\nGo away!\x01");
	SetDialogString(1467, "\x10""Ruby\x10" "...\x01");
	SetDialogString(1468, "\x11Leave alone\nHug\x11");
	SetDialogString(1469, "\x10""Lulu\x10" "No...\x03\x30 step away.\x01");
	SetDialogString(1470, "\x10""Lulu\x10" "Are you doing this because I hugged\nyour friend a while ago?\x01 I'm sorry, ok?\x01");
	SetDialogString(1471, "\x10""Noah\x10" "D-don't be sorry.\x01");
	SetDialogString(1472, "\x10""Lulu\x10" "Huh...?\x01 Ummm...\x03\x30 err...\x03\x30 thanks.\x01");
	SetDialogString(1473, "\x10""Ruby\x10" "I'll leave you alone...\x03\x20 but it'd be\nnice if you gave me that red gem.\x01 As\nEmmet said,\x03\x20 we kinda worked hard for\nit...\x01\nand you coming to take our prize\naway is a bit unnice,\x03\x20 don't you think?\x01");
	SetDialogString(1474, "\x10""Ruby\x10" "About that gem...\x01 would be really nice\nof you to give that gem back to me...\x01");
	SetDialogString(1475, "\x10""Lulu\x10" "Whatever,\x03\x20 these gems aren't worth\nmuch anyway.\x01 Be my guest.\x01");
	SetDialogString(1476, "\x10""Lulu\x10" "Well...\x01 I am going to go to confront\nmy family by myself.\x01 I hope they'll\nforgive me for making rushed and\nselfish decisions...\x01");
	SetDialogString(1477, "\x10""Ruby\x10" "Hey,\x03\x20 if they won't accept you...\x01\n...well,\x03\x20 you're not going to like\nit.\x01");
	SetDialogString(1478, "\x10""Lulu\x10" "Thanks for trying to support me...\x03\x40\neven though I treated you all like\nshoes with shoelaces...\x01");
	
	SetDialogString(1480, "\x10""Noah\x10" "Are you ok, Ruby?\x01");
	SetDialogString(1481, "\x10""Ruby\x10" "I am fine,\x03\x20 let's go.\x01");
	SetDialogString(1482, "\x10""Ruby\x10" "(I wonder what Lulu is up to now.)\x01");
	SetDialogString(1483, "\x10""Lulu\x10" "Hi Ruby, let's leave this place\nalready.\x11Sure (back to Sapphirepolis)\nNot yet\x11");
	SetDialogString(1484, "\x10""Lulu\x10" "See you all later...\x03\x40 allies.\x01");
	SetDialogString(1485, "\x10""Ruby\x10" "Bye, Lulu.\x01");
	SetDialogString(1486, "\x10""Ruby\x10" "(Now that I've finally accomplished my\nmission...\x03\x30 The real last thing left\nto do is to return to my home via\nSapphireland Metro.\x01 But I can still\nspend the rest of the day on more\nexploration,\x03\x20 side-quests and even some\nextra battles.)\x01");
	
	SetDialogString(1490, "\x10""Sally\x10" "It feels good to be back home!\x01\nI'm sure people here won't recognize\nme at all...\x01");
	SetDialogString(1491, "\x10""Ruby\x10" "You all can stay at my home if you\nwant.\x01");
	SetDialogString(1492, "\x10""Noah\x10" "Sure.\x01");
	SetDialogString(1493, "\x10""Emmet\x10" "I don't mind at all!\x01");
	SetDialogString(1494, "\x10""Sally\x10" "Hell yes!\x03\x20 Let's throw a party at Ruby's\nhouse!\x01");
	SetDialogString(1495, "\x10""Ruby\x10" "Good idea,\x03\x20 let's celebrate this\nimportant day of my life!\x01");
	
	SetDialogString(1500, "Your adventure will end once you enter\nyour house.\x11""Don't end\nEnd\x11");
	SetDialogString(1501, "\x10""Ruby\x10" "Actually,\x03\x20 let's throw the party\nin a few days.\x01 I want to take a little\nrest first.\x01");
	SetDialogString(1502, "\x10""Emmet\x10" "Oh,\x03\x20 that's fine.\x03\x20 I also want to\nrest after insane fighting...\x03\x20 nobody\nwould blame you.\x01");
	SetDialogString(1503, "\x10""Sally\x10" "Yeah...\x01 now that I think about it,\x03\x20\ntaking a nap is actually a really good\nidea right now.\x01 Bye,\x03\x20 Ruby!\x01");
	SetDialogString(1504, "\x10""Ruby\x10" "Bye, everyone.\x01");
	
	SetDialogString(1510, "\x10""Ruby\x10" "(Wow, what a huge and beautiful city...\x01\nThe next Ancient Gem is at Amper Corp.\x01\nBut first, I should take a rest at a\nnearby hotel and regain my strength\nfor the final stretch.)\x01");
	
	SetDialogString(1520, "\x10""Panda\x10" "Hello,\x03\x20 Ruby...\x01 I'm Panda.\x01");
	SetDialogString(1521, "\x10""Panda\x10" "So I've been told about the murder of\nmy little sister...\x03\x50 you know a thing\nabout that,\x03\x20 do you?\x01");
	SetDialogString(1522, "\x10""Ruby\x10" "Did you figure out who killed her?\x01");
	SetDialogString(1523, "\x10""Panda\x10" "...\x01There's lots of evidence that you\ndid it,\x03\x20 Ruby.\x01 I...\x03\x20 I can't believe\nyou would've done this...\x01");
	SetDialogString(1524, "\x10""Panda\x10" "There's...\x03\x30 uh,\x03\x20 let's go in a less\ncrowded area,\x03\x20 I need to tell you\nsomething.\x01");
	SetDialogString(1525, "\x10""Panda\x10" "Perry meant a lot to me...\x01 We\nspent so much time together,\x03\x20 played\nvideo games,\x03\x20 did homework together,\x03\x20\nhelped each other at difficult times...\x01");
	SetDialogString(1526, "\x10""Panda\x10" "She was kind to everyone and had a pure\nheart...\x01 She definitely wouldn't attack\nanyone,\x03\x20 and I know that well!\x01");
	SetDialogString(1527, "\x10""Panda\x10" "A-are you going to say anything?\x01\nRuby?\x03\x20 You r-really killed my sis?\x03\x20\nPlease tell me why!!\x01");
	SetDialogString(1528, "\x10""Ruby\x10" "Yes...\x03\x20 uhh...\x01");
	SetDialogString(1529, "\x10""Panda\x10" "Look,\x03\x20 if I didn't know any better,\x03\x20\nI would've called the police on you.\x01\nBut my...\x03\x20 friends urged me to instead\ndeal with you on my own.\x01");
	SetDialogString(1530, "\x10""Panda\x10" "Haha...\x03\x30 I really want to kill you...\nso much.\x01");
	SetDialogString(1531, "\x10""Ruby\x10" "Surely you have parents and friends\nyou wouldn't want to lose?\x01");
	SetDialogString(1532, "\x10""Panda\x10" "...\x01");
	SetDialogString(1533, "\x10""Panda\x10" "My parents and friends...?\x01\n.\x03\x20.\x03\x20.\x03\x20I do,\x03\x20 but...\x01");
	SetDialogString(1534, "\x10""Panda\x10" "You're going to kill them next,\x03\x20\nright?\x03\x30 I'm protecting them from you!\x01\nIf I were to let you be near them...\x01");
	SetDialogString(1535, "\x10""Panda\x10" "...it would be OVER MY DEAD BODY!!\x01");
	SetDialogString(1536, "\x10""Panda\x10" "I remember you and other friends of\nPerry regularly visiting us...\x01 You were\nreally quiet compared to everyone else.\x01");
	SetDialogString(1537, "\x10""Panda\x10" "Even thought you didn't interact with\nme much...\x03\x30 you and Perry went along\ntogether,\x03\x20 didn't you?\x01 What did I or\nPerry do specially wrong to deserve\nthis treatment?!\x01");
	SetDialogString(1538, "\x10""Panda\x10" "No,\x03\x20 you must be a cold-blooded\nserial killer at this point...\x01 You know\nabout Sally's disappearance as well,\x03\x20\nright?\x01");
	SetDialogString(1539, "\x10""Ruby\x10" "Enough talking,\x03\x20 you are barely standing\nright now already.\x01 You already lost.\x01");
	SetDialogString(1540, "\x10""Panda\x10" "Not yet,\x03\x20 I've brought a ton of useful\nitems with me!\x01");
	SetDialogString(1541, "\x10""Panda\x10" "When I saw Perry's lifeless body...\x03\x40\nand blood...\x03\x40 I was paralyzed.\x01 I was\nshaking uncontrollably hard,\x03\x20 I did not\nknow what to do.\x01");
	SetDialogString(1542, "\x10""Panda\x10" "I went outside.\x03\x20 Then I met a nice\ngentleman and lady that were in a\nsimilar situation.\x01 Long story short,\x03\x20\nthey offered to help me and gave me\nsome \"very powerful items\"...\x01");
	SetDialogString(1543, "\x10""Ruby\x10" "..!\x01");
	SetDialogString(1544, "\x10""Panda\x10" "The gentleman convinced me that\nI should take revenge on one who\nkilled her,\x03\x20 my sister.\x01 And that's how I\nended up here in the first place!\x01");
	SetDialogString(1545, "\x10""Panda\x10" "I have no choice but to use this...\x01\nDon't worry,\x03\x20 Ruby,\x03\x20 it won't hurt.\x01 All I\nwant to do is put you to sleep...\x03\x30\nand keep you out of trouble,\x03\x20 okay?\x01\nStand still.\x01");
	SetDialogString(1546, "\x10""Ruby\x10" "(That doesn't sound good.\x01 That needle..\x03\x20\nI should dodge it at all costs.\x01\nLet's imagine we're dodging it like a\nshuriken!)\x01");
	SetDialogString(1547, "\x10""Panda\x10" "You've realized it by now, Ruby.\x01\nEach one of these capsules makes me\nstronger and faster...\x03\x30 soon enough,\x03\x20\nyou won't be able to keep up with me..!\x01");
	SetDialogString(1548, "\x10""Panda\x10" "And if you still keep up with your\n\"self-defense\"...\x03\x30 then I'll have to\nresort to putting you to sleep the\n\"easy\" way.\x01");
	SetDialogString(1549, "\x10""Panda\x10" "You are making this harder for both you\nand me.\x01 Why do you still keep going?\x03\x20\nWhy?\x01");
	SetDialogString(1550, "\x10""Ruby\x10" "Considering you all are out to kill\nor torture me now...\x03\x30 You leave me no\nchoice but to keep going the \"evil\"\npath.\x01 Stopping right now would be a\nstupid idea, no?\x01 When the door to a\nhappy life is closed, and everybody\ntreats me like a supervillain...\x01 Might\nas well cause as much destruction as\npossible.\x01");
	SetDialogString(1551, "\x10""Panda\x10" "...\x01So those are your points.\x01\nShouldn't have done evil deeds in the\nfirst place!!\x01");
	SetDialogString(1552, "\x10""Panda\x10" "I missed twice,\x03\x20 but this time,\x03\x20\nI won't miss...!\x01");
	SetDialogString(1553, "\x10""Panda\x10" "What is this?!\x03\x20 What are you?\x01\nWhatever,\x03\x20 I'll just-\x01");
	SetDialogString(1554, "\x10""Panda\x10" "...\x01I ran out of everything.\x01 Curses!\x03\x20\nI hate you, Ruby...\x01");
	SetDialogString(1555, "\x10""Panda\x10" "I don't know what I was doing\nto be honest...\x01 I accept this as an\noutcome,\x03\x30 at least I'll be able to see\nPerry again...\x01");
	SetDialogString(1556, "\x10""Panda\x10" "Ruby...\x03\x40 I truly wanted best for you.\x01\nI don't think you are truly evil...\x03\x30\nI'm so sorry...\x01");
	SetDialogString(1557, "\x10""Panda\x10" "P-please...\x03\x30 d-don't...\x03\x20 h-hurt\nany-anyone...\x03\x20 el-...\x01\n.\x03\x40.\x03\x40.\x03\x40");
	SetDialogString(1558, "\x10""Ruby\x10" "I've already chosen my path,\x03\x20 and I am\nnever turning back.\x01");
	SetDialogString(1559, "\x10""Ruby\x10" "(N-no...\x03\x30 What's going on?\x01 What\nhave I done?\x01 I curse this world forever...)\x01");
	SetDialogString(1560, "\x10""Ruby\x10" "(I really should've left much\nearlier...\x01 I wish I was never born,\x03\x20\nI wish I have never existed!!)\x01");
	SetDialogString(1561, "\x10""Ruby\x10" "(There really is no point in going\nforward...\x03\x30 I'll eventually get caught\nby the Ministries and be tortured for\nmillenias...)\x01");
	
	SetDialogString(1570, "\x10""Kara\x10" "Oh hi,\x03\x20 my name's Kara, I am the\nmanager here.\x01 How'd you get past\nthe guards?\x01");
	SetDialogString(1571, "\x10""Ruby\x10" "How do I get to the last floor?\x01");
	SetDialogString(1572, "\x10""Kara\x10" "You need a special permission to be\nallowed to travel to a certain floor.\x01\nOnly the CEO and co-executives can\ngrant you access to the last floor...\x01\nFlora is a co-executive and a friend\nof mine,\x03\x20 so I can let you to Floor 9\nwhich is where she works at.\x01");
	SetDialogString(1573, "\x10""Ruby\x10" "Will you let me to Floor 9 then?\x01");
	SetDialogString(1574, "\x10""Kara\x10" "Only if you say please!\x01");
	SetDialogString(1575, "\x10""Kara\x10" "Haha...\x03\x20 just kidding,\x03\x20 here you go.\x01");
	SetDialogString(1576, "\x10""Kara\x10" "Just go to the elevator and you should\nnow be able to access Floor 9.\x01\nSee you later.\x01");
	
	SetDialogString(1580, "\x10""Amp\x10" "...!!!\x01");
	SetDialogString(1581, "\x10""Amp\x10" "Who in the HELL is here?!?!!\x03\x20\nWho in the world allowed you to show\nup and invade my privacy\?\?!\?!\?\?!\x01");
	SetDialogString(1582, "\x10""Amp\x10" "You...\x03\x20 Who are you?\x03\x20 Answer me!\x01\nTell me who had the bright idea of\nclearing the way to my little room for\nyou!\x01");
	SetDialogString(1583, "\x10""Amp\x10" "That's it...\x03\x20 Get outta here before I\nthrow you out of that window!\x01");
	SetDialogString(1584, "\x10""Ruby\x10" "...\x01Nope.\x01");
	SetDialogString(1585, "\x10""Amp\x10" "Then out of the window you go..!\x01");
	SetDialogString(1586, "\x10""Amp\x10" "...\x03\x20Okay...\x03\x20 I underestimated you...\x01\nHave mercy on me...\x01");
	SetDialogString(1587, "\x10""Amp\x10" "!!!\x01\nWhat...\x03\x20 what are you doing?!\x03\x20\nPut down your weapon!\x01");
	SetDialogString(1588, "\x10""Ruby\x10" "Why would I?\x01 This's just avenging those\nthat you big company owners didn't\nhesitate to bully or even kill.\x01 You\nthink you are above the law and can\ndo a lot that the average being\ncannot...\x01 But you are,\x03\x20 in fact,\x03\x20\ntotal waste of economic and ecological\nspace.\x01 Looks like karma has caught up\nto you finally.\x01");
	SetDialogString(1589, "\x10""Amp\x10" "T-That's...\x03\x30 You're just generalizing!\x01\nI swear,\x03\x20 I didn't do anything\n\"evil\"...\x03\x20 nor I meant to in the first\nplace!\x01");
	SetDialogString(1590, "\x10""Amp\x10" "P-please...\x03\x20 don't hurt me!\x03\x20 I\ncan even give you money if you\nw-want...\x01");
	SetDialogString(1591, "\x10""Ruby\x10" "Aaaand of course you plead mercy when\nyour life is under threat.\x01 If there's\nsomeone to be spared...\x03\x30 you're the one\nwho should spare me cliches.\x01");
	SetDialogString(1592, "\x10""Amp\x10" "I know...\x03\x20 but please...\x03\x20 leave me alone\nand I'll give you $100000...\x03\x30 and we can\nforget this ever happened,\x03\x20 okay?\x01\nIf you kill me,\x03\x20 you will regret it\nvery much...\x03\x30 you will be hunted down\nby Superheroes and such...\x01\nSo please don't do it for your sake.\x01");
	SetDialogString(1593, "\x11""Spare for $100000\nKill\x11");
	SetDialogString(1594, "\x10""Ruby\x10" "You're not bribing your way out of this\none,\x03\x20 greedy conglomerate witch.\x01\nGood riddance.\x01");
	SetDialogString(1595, "\x10""Amp\x10" "AAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHH\x03\x20");
	SetDialogString(1596, "\x10""Ruby\x10" "Will you give me that black Ancient\nGem as well?\x01");
	SetDialogString(1597, "\x10""Amp\x10" "...O-Of course,\x03\x20 if you want...\x01");
	SetDialogString(1598, "\x10""Ruby\x10" "I guess killing you would really not\nsolve anything...\x03\x30 but my point still\nstands.\x01");
	SetDialogString(1599, "\x10""Amp\x10" "T-Thank you...\x01");
	SetDialogString(1600, "\x10""Ruby\x10" "Mercy?\x03\x20 Why?\x01 You were living way\ntoo well,\x03\x20 meanwhile I had to suffer\nwith little to no money.\x01");
	SetDialogString(1601, "\x10""Amp\x10" "I...\x03\x20 I'm sorry for you then.\x01 How 'bout\nI give you something as a reward?\x01");
	SetDialogString(1602, "\x10""Ruby\x10" "A reward?\x03\x30 That Ancient Gem right over\nthere.\x01");
	SetDialogString(1603, "\x10""Amp\x10" "Oh...\x03\x20 you're free to take it then.\x01\nThat's all?\x03\x20 I guess that's all, good\nluck then.\x01");
	SetDialogString(1604, "\x10""Amp\x10" "Do you...\x03\x20 want to talk with me perhaps?\x01");
	SetDialogString(1605, "\x10""Amp\x10" "I see...\x03\x20 good luck then.\x01");
	SetDialogString(1606, "You got $100000.\x03\x20 Wow!\x01");
	
	SetDialogString(1610, "\x10""Ruby\x10" "Don't stand in my way, Lulu.\x01");
	SetDialogString(1611, "\x10""???\x10" "...what are you talking ab-\x01");
	SetDialogString(1612, "\x10""???\x10" "Okay,\x03\x20 there's no need for a dramatic\nprelude anyway.\x01");
	SetDialogString(1613, "\x10""Lulu\x10" "Behold,\x03\x20 Ruby!\x03\x20 I am now-\x03\x04");
	SetDialogString(1614, "\x10""Ruby\x10" "Get out of my way before I end your\nlife.\x01");
	SetDialogString(1615, "\x10""Lulu\x10" "B-\x03\x20""but what is-\x03\x08");
	SetDialogString(1616, "\x10""Ruby\x10" "I said get out of my way before I end\nyour life.\x03\x20 I guess you don't want to\nlive anymore?\x01 Then that can be\narranged right now.\x01");
	SetDialogString(1617, "\x10""Lulu\x10" "How dare you speak to me in that\nmanner?!\x01 I am Master Lulu,\x03\x20 and I will\nteach you how you should treat your\nsuperiors!!\x01");
	SetDialogString(1618, "\x10""Ruby\x10" "I suppose that's how I should treat my\n\"superiors\"...\x01 No need to carry all the\nburden by myself like a slave,\x03\x20 riot\nagainst your \"masters\" instead and show\nwho's the REAL boss.\x01");
	SetDialogString(1619, "\x10""Lulu\x10" "No!\x03\x20 Don't you dare-\x03\x10");
	SetDialogString(1620, "\x10""Lulu\x10" "I am...\x03\x40 bleeding hard?\x01 W-what's wrong\nwith you...\x01");
	SetDialogString(1621, "\x10""Ruby\x10" "I am on a strict schedule,\x03\x20 y'know...\x01\nWe could've avoided drawing blood had\nyou listened to me and stayed out of\nmy way.\x01 But I guess you're too stupid,\x03\x20\nso this will be the last mistake you'll\never make.\x01");
	SetDialogString(1622, "\x10""Ruby\x10" "You will NOT get away this time, Lulu,\x03\x20\nand I am going to make sure this will\nbe our FINAL encounter!!\x01");
	SetDialogString(1623, "\x10""Ruby\x10" "(...\x03\x20She got away apparently.)\x01");
	
	SetDialogString(1630, "\x10""???\x10" "Look who's over there!\x01");
	SetDialogString(1631, "\x10""???\x10" "Hmmm...\x03\x20 You look familiar...\x03\x20 Ruby,\nisn't it?\x01 \x10""Maline\x10Maline's my name.\x01");
	SetDialogString(1632, "\x10""???\x10" "Wait,\x03\x20 you two know each other?\x01");
	SetDialogString(1633, "\x10""Maline\x10" "Of course, Cory!\x03\x20 I know a lot of people\ncoming from rural areas...\x01 I've been\nselling stuff to those poor people for\na while.\x01");
	SetDialogString(1634, "\x10""Cory\x10" "Hey,\x03\x20 Ruby.\x03\x20 Did you know you are an\ninternational threat?\x01 I'm not kidding,\ntake a look at those newspapers.\x01");
	SetDialogString(1635, "\x10""Maline\x10" "What?\x03\x20 She already made it to the\nheadlines?\x01");
	SetDialogString(1636, "\x10""Cory\x10" "Yes,\x03\x20 these newspapers come from...\x03\x40\nwait,\x03\x20 what was that country called\nagain?\x01 Or was it a town?\x03\x20 Or a wildlife\nobservatory area?\x01");
	SetDialogString(1637, "\x10""Maline\x10" "What.\x01 Why would that come from a...\x03\x30\nwildlife observatory area?\x03\x20 Really?\x01");
	SetDialogString(1638, "\x10""Cory\x10" "I dunno,\x03\x20 maybe Ruby is a monkey or\nsomething.\x01");
	SetDialogString(1639, "\x10""Ruby\x10" "Humans' average IQ is lower than\nmonkeys',\x03\x20 that I can say for sure.\x01\nAnyway,\x03\x20 I'm an international threat?\x03\x20\nThen I have no choice but to go\nforward.\x01");
	SetDialogString(1640, "\x10""Maline\x10" "Ruby,\x03\x20 you've hurt a lot of people.\x01\nWe can't just let you pass through,\x03\x20\nwe've been hired to kill you and...\x03\x20 I\nmean capture you,\x03\x20 oops.\x01\nI may be just a regular shopkeeper,\x03\x20\nbut I am in fact a secret mercenary.\x01");
	SetDialogString(1641, "\x10""Cory\x10" "I'm going to kill you for killing my\nbusiness partner!!\x01");
	SetDialogString(1642, "\x10""Maline\x10" "\"CAPTURE\",\x03\x20 Cory,\x03\x20 \"CAPTURE\".\x01");
	SetDialogString(1643, "\x10""Cory\x10" "I'm going to capture you for killing my\nbusiness partner!!\x03\x40 ...and kill you\nafterwards.\x01");
	SetDialogString(1644, "\x10""Maline\x10" "Cory!\x03\x20 Ruby hasn't even attacked us yet!\x01\nWe're going to go to jail if we decide\nto kill her!\x01");
	SetDialogString(1645, "\x10""Cory\x10" "Fine!\x03\x20 Then I'll torture her.\x01");
	SetDialogString(1646, "\x10""Maline\x10" "No!\x01");
	SetDialogString(1647, "\x10""Cory\x10" "Then I'll hire another mercenary to\nkill her for me.\x01");
	SetDialogString(1648, "\x10""Maline\x10" "Now that's a great idea!\x01");
	SetDialogString(1649, "\x10""Ruby\x10" "Just die already.\x01");
	SetDialogString(1650, "\x10""Maline\x10" "Try your absolute best attacks,\x03\x20 Ruby.\x01");
	SetDialogString(1651, "\x10""Maline\x10" "Hmmm...\x03\x20 you're already struggling?\x01\nDon't worry,\x03\x20 it only gets worse.\x01");
	SetDialogString(1652, "\x10""Maline\x10" "You really are stubborn,\x03\x20 aren't you?\x01\nWell,\x03\x20 let me tell you this:\x03\x20 You will\nnot last for very long.\x01 Even if you\nmanage to get past us,\x03\x20 what makes you\nthink you'll be able to handle the\nOnyx Ministry all by yourself?\x01 Have\nyou thought about that?\x03\x20 Did you ever\nthink you could defeat the Onyx agents?\x01\nRuby,\x03\x20 you'd better just stop fighting\nback,\x03\x20 you have ZERO chance to win the\nwar,\x03\x20 you are just setting up yourself\nfor disappointment.\x01");
	SetDialogString(1653, "\x10""Maline\x10" "Guess it's time for my ultimate attack.\x01\nI tried to warn you, Ruby,\x03\x20 but I\nsuppose you just want to keep going no\nmatter what.\x01 Guess you'll learn the\ntruth the hard way.\x01");
	SetDialogString(1654, "\x10""Maline\x10" "Cory!!\x01 ...G-Guess I'll go all-out.\x01");
	SetDialogString(1655, "\x10""Cory\x10" "Yeah,\x03\x20 listen to Maline you monkey!\x01\nThere's no reward waiting you at\nthe end of all this.\x01 Unless you\nconsider getting captured by Onyx\nMinistry as a \"reward\"...\x01");
	SetDialogString(1656, "\x10""Cory\x10" "Screw this,\x03\x20 I'm going to kill you.\x01");
	SetDialogString(1657, "\x10""Maline\x10" "Wait,\x03\x20 don't-\x03\x20");
	SetDialogString(1658, "\x10""Cory\x10" "Yes, I will.\x01 Die,\x03\x20 international threat!\x01");
	SetDialogString(1659, "\x10""Cory\x10" "What the heck!\x03\x20 How are you still not\ndefeated?!\x01 Alright,\x03\x20 let's just end this\nonce and for all.\x01");
	SetDialogString(1660, "\x10""Cory\x10" "Welp.\x03\x20 That's what you get when you\nto be soft with these kinds of people.\x01\nIf only I used my ultimate attack\nearlier...\x01");
	SetDialogString(1661, "\x10""Cory\x10" "I...\x03\x40 I..\x03\x40 I won't die..!\x01");
	
	SetDialogString(1670, "\x10""Lulu\x10" "Huh?\x01 Did you just follow me to here?\x01");
	SetDialogString(1671, "\x10""Lulu\x10" "You...\x03\x30 You'd better stay away.\x01\nYou wanted to get that gem?\x03\x20 Sorry, it's\nmine now,\x03\x20 and you can't do\nanything about it.\x01 Why?\x03\x20 Because I am\nnow a GOD.\x03\x20 Which means you won't be\nable to make me bleed at all.\x01");
	SetDialogString(1672, "\x10""Ruby\x10" "Actually,\x03\x20 I can easily make you bleed\nwith an undodgable sharp attack.\x01");
	SetDialogString(1673, "\x10""Lulu\x10" "So?\x03\x30 You still won't put a dent to me.\x01\nAnd,\x03\x20 I saved you the trouble of\nfighting that weird magical rock,\x03\x20 so\nyou'd better thank me for that!\x01");
	SetDialogString(1674, "\x10""Ruby\x10" "Only after you let me grab the Ancient\nGem.\x01");
	SetDialogString(1675, "\x10""Lulu\x10" "Nuh-uh.\x01 After trying to actually kill\nme?\x03\x20 What a greedy idiot.\x01 Get a load of\nthis!\x01");
	SetDialogString(1676, "\x10""Lulu\x10" "Wha...\x03\x30 what's going on?\x01 Nevermind,\x03\x20\nI'll just knock you down again.\x01\nSuffer more, Ruby!\x01");
	SetDialogString(1677, "\x10""Ruby\x10" "(Looks like I've become much stronger.\x01\nWait,\x03\x20 there's no way...\x03\x30 hmmm...\x01\nLet's check my new powers.)\x01");
	SetDialogString(1678, "\x10""Ruby\x10" "(WOW,\x03\x20 THIS FEELS AMAZING!!!\x01 Now I\nwill have no problem of taking care of\nthis fool.)\x01");
	SetDialogString(1679, "\x10""Lulu\x10" "Oww....\x03\x20 how did you-\x01");
	SetDialogString(1680, "\x10""Lulu\x10" "Wait,\x03\x20 did you just defeat me?\x01\nBut... what happened?\x01");
	SetDialogString(1681, "\x10""Ruby\x10" "I have no idea...\x03\x30 but now there's\nnothing left you but a painful death.\x01");
	SetDialogString(1682, "\x10""Lulu\x10" "R-Ruby...\x03\x40 You...\x03\x40 You...\x03\x50\nYOU WON'T GET AWAY WITH THIS!!!\x01");
	SetDialogString(1683, "\x10""Ruby\x10" "(..?\x01 Don't tell me that she's...)\x01");
	SetDialogString(1684, "\x10""Lulu\x10" "Hahahahahaha...\x03\x20 I guess we're even now.\x01\nLet me show you the ULTIMATE power of\nGod Lulu!!!\x01");
	SetDialogString(1685, "\x10""Lulu\x10" "You're SOOOO screwed, Ruby.\x03\x20 You made a\nHUGE mistake...\x03\x20 and I will see to it\nthat it'll cost you EVERYTHING!!\x01");
	SetDialogString(1686, "\x10""Lulu\x10" "Heh...\x03\x20 what are you even fighting for,\x03\x20\nanyway?\x03\x20 To satisfy your criminal...\x03\x20\nthirst?\x01 Me?\x03\x20 I am fighting not only to\ndefend myself...\x03\x20 but to protect the\nworld as well.\x01 I am the chosen one,\x03\x20 I\nAM THE ONE WHO WILL SAVE THE WORLD FROM\nTHE DESTRUCTION OF THE DEVIL!!\x01 YOU ARE\nTHE DEVIL THAT NEEDS TO BE BANISHED\nINTO THE DEPTHS OF YOU-KNOW-WHAT\nPLACE!!\x01 HELL!!!\x01");
	SetDialogString(1687, "\x10""Ruby\x10" "And so it all ends.\x01");
	SetDialogString(1688, "\x10""Lulu\x10" "Even with my god powers...\x03\x20 you still\ndefeated me easily?\x01");
	SetDialogString(1689, "\x10""Lulu\x10" "Just kidding,\x03\x20 did you really think\nit was gonna be this easy?\x01 You haven't\neven seen phase 2 of the Ultimate Lulu\nyet!!\x01");
	SetDialogString(1690, "\x10""Ruby\x10" "You GOTTA be kidding me.\x01");
	SetDialogString(1691, "\x10""Lulu\x10" "A true heroine NEVER gives up!!\x01\nGet ready to-\x03\x04");
	SetDialogString(1692, "\x10""Ruby\x10" "You are barely standing.\x03\x20 Face it,\nyou lost this fight.\x01");
	SetDialogString(1693, "\x10""Lulu\x10" "You aren't the one calling the shots,\nidiot!\x01");
	SetDialogString(1694, "\x10""Ruby\x10" "Well, then you still have the power to\ntake me down easily,\x03\x20 right?\x01 C'mon,\nlet's see what you've still got.\x01");
	SetDialogString(1695, "\x10""Lulu\x10" "Of course I do!!\x01 PREPARE TO DIE!!!\x01");
	SetDialogString(1696, "Ultimate Lulu uses UltL Overdrive!\x02");
	
	SetDialogString(1700, "\x10""???\x10" "...\x01");
	SetDialogString(1701, "\x10""???\x10" "Someone's coming our way!\x01");
	SetDialogString(1702, "\x10""???\x10" "Oh, Ohio?\x03\x30 That must be someone we're\nlooking for, right?\x01");
	SetDialogString(1703, "\x10""???\x10" "Indeed,\x03\x20 that lady over there is Ruby\nChan.\x01");
	SetDialogString(1704, "\x10""???\x10" "Let's show good manners,\x03\x20 she's\nlistening to us right now.\x01");
	SetDialogString(1705, "\x10""???\x10" "Well...\x03\x30 hello, Ruby.\x01 It's a nice day\noutside, isn't it?\x01 Name's \x10Vincent\x10Vincent.\x03\x20\nMeet me, Jerry, Ohio and Kaiser,\x01\nyour fellow superagents of the\nstrongest organization in the country,\x03\x20\nthe Onyx Ministry.\x01");
	SetDialogString(1706, "\x10""Vincent\x10" "Where are you going, ma'am?\x01");
	SetDialogString(1707, "\x10""Ruby\x10" "Don't stand in my way.\x01");
	SetDialogString(1708, "\x10""Vincent\x10" "Alright,\x03\x20 let me just tell you the\nhard truth.\x03\x20 You're going to be charged\nfor the following crimes:\x01\nmurder,\x03\x20 possession of illicit goods,\x03\x20\nuse of torture devices, etc.\x01");
	SetDialogString(1709, "\x10""Ohio\x10" "What an awful being!\x03\x20 I feel bad for her\nvictims...\x01");
	SetDialogString(1710, "\x10""Ruby\x10" "That's my revenge for making my life\nmiserable.\x01 Born in an awful family,\x03\x20\nshutdown of Sapphireton's Lab,\x03\x20 and now\nyou're trying to send me to a really\nterrible prison.\x01");
	SetDialogString(1711, "\x10""Jerry\x10" "Sapphireton's Lab?\x03\x20 Pardon,\x03\x20 isn't that\nthe lab that had possessed a bunch of\nterrible chemicals and some of\nSophien's research stuff?\x01");
	SetDialogString(1712, "\x10""Kaiser\x10" "Yikes,\x03\x20 who'd in their right mind would\nwant to work in that place\nanyway?\x01 Especially with stuff from the\nMr. S?\x01");
	SetDialogString(1713, "\x10""Vincent\x10" "So that explains where you'd get those\n\"illicit goods\" from.\x01 Ruby,\x03\x20 you know\nthat we are able to defeat even the\nmost powerful of the Demi-gods...\x01\nSo I advise you to surrender right now\nso you won't suffer a more harsh\npunishment.\x01");
	SetDialogString(1714, "\x10""Ruby\x10" "I can easily take you down.\x03\x20 Prepare\nto die.\x01");
	SetDialogString(1715, "\x10""Vincent\x10" "Well, let's not choke against this\nfella, mates.\x01");
	
	
	
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
	SetDialogString(2305, "\x10""Justin\x10" "What's up?\x03\x20 You're a Vandal?\x03\x20 To the\nwoods you shall go!\x01 Well, just saying..\x01\nIf you were one of them, I'd take you\ndown in just a single RPG turn...\x01\nThat's how awesome I am!\x01");
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
	SetDialogString(2327, "\x10""Border Officer\x10" "Do you want to go to Sapphirepolis?\x11Yes\nNo\x11");
	SetDialogString(2328, "Where do you want to go?\x11""Floor 1\nFloor 2\nFloor 3\nFloor 4\nFloor 5\nFloor 6\nFloor 7\nFloor 8\nFloor 9\nFloor 10\x11");
	SetDialogString(2329, "\x10""Sally\x10" "Ouch! What the hell is this?\x01");
	SetDialogString(2330, "\x10""Emmet\x10" "Electric floor?\x03\x20 Seems like some sort\nof security measure.\x01");
	SetDialogString(2331, "\x10""Sally\x10" "That really hurt...\x01");
	SetDialogString(2332, "\x10""Ruby\x10" "(I should look for some clues...)\x01");
	SetDialogString(2333, "\x10""Ruby\x10" "(I think I already looked at the\nsolution in that black-white room...)\x01");
	SetDialogString(2334, "\x10""Sally\x10" "Another one?\x03\x20 Please no.\x01");
	SetDialogString(2335, "\x10""Sally\x10" "Dammit.\x01 Try using the same pattern\nI guess?\x01");
	SetDialogString(2336, "Play the Snake game?\x11Yes\nNo\x11");
	SetDialogString(2337, "Game over!\x01");
	SetDialogString(2338, "Where do you want to go?\x11""Floor 1\nFloor 2\x11");
	SetDialogString(2339, "\x10""Timon\x10" "Do you wanna try again to beat me\nat Hide and Seek?\x11Yes\nNo\x11");
	SetDialogString(2340, "\x10""Timon\x10" "Alright, hide in these wardrobes\nand start counting to 10!\x03\x20 Don't\nlook or you will not win!\x01");
	SetDialogString(2341, "10,\x03\x36 9,\x03\x36 8,\x03\x34 7,\x03\x2e 6,\x03\x24 5,\x03\x1c 4,\x03\x12 3,\x03\x06 2,\x03\x04 1,\x03\x03\nGO!\x03\x14");
	SetDialogString(2342, "\x10""Timon\x10" "Time out!\x03\x20 You failed to find me.\x01");
	SetDialogString(2343, "\x10""Timon\x10" "Oof, you...\x03\x20 you FOUND me!\x01");
	SetDialogString(2344, "\x10""Timon\x10" "Okay, okay.\x03\x20 You won this fair and\nsquare.\x03\x20 Your prize is...\x01");
	SetDialogString(2345, "\x10""Timon\x10" "Rob is waiting for you on the third\nfloor.\x03\x20 Be quick!\x01");
	SetDialogString(2346, "\x10""Emmet\x10" "If he was waiting for us, then...\x01");
	SetDialogString(2347, "\x10""Emmet\x10" "...why did he put these dumb obstactles\nto begin with?\x03\x40... is what I was about\nto ask.\x01");
	SetDialogString(2348, "\x10""Ruby\x10" "Beats me.\x03\x20 We'll find out in floor 3, I\nguess?\x01");
	SetDialogString(2349, "Electric floor has been deactivated.\x01");
	SetDialogString(2350, "Playing the Snake game will activate\nthe electric floor. Proceed anyway?\x11Yes\nNo\x11");
	SetDialogString(2351, "\x10""Emmet\x10" "Sally?\x01");
	SetDialogString(2352, "\x10""Emmet\x10" "Did she give up now?\x01");
	SetDialogString(2353, "\x10""Ruby\x10" "(Maybe I should follow her.)\x01");
	SetDialogString(2354, "\x10""Sally\x10" "Psst.\x03\x20 I have a plan.\x01");
	SetDialogString(2355, "\x10""Ruby\x10" "Oh, nice. Tell me?\x01");
	SetDialogString(2356, "\x10""Sally\x10" "Uhh...\x03\x20 I will show where he will\nbe hiding.\x01 You two go play Hide and\nSeek.\x01");
	SetDialogString(2357, "\x10""Emmet\x10" "A sneak peek to help us?\x01");
	SetDialogString(2358, "\x10""Sally\x10" "Yes...\x03\x20 I'll point you to his hiding\nspot.\x01");
	SetDialogString(2359, "\x10""Ruby\x10" "Okay, let's go Emmet.\x01");
	SetDialogString(2360, "\x10""Sally\x10" "I'll be back to give you a hint\nfor that stupid game, ok?\x01");
	SetDialogString(2361, "\x10""Sally\x10" "Hopefully you get my hints...\x01");
	SetDialogString(2362, "\x10""Sally\x10" "Stop being so SLOW or STUPID!\x03\x20\nI'm telling you EXACTLY where to\nfind him.\x01");
	SetDialogString(2363, "\x10""Sally\x10" "...\x01");
	SetDialogString(2364, "Where do you want to go?\x11""Floor 1\nFloor 2\nFloor 3\nFloor 4\nFloor 5\x11");
	SetDialogString(2365, "\x10""Receptionist\x10" "Sapphire Hotel, baby.\x01 $400 and such.\x11Yes\nNo\nWhat\x11");
	SetDialogString(2366, "\x10""Receptionist\x10" "...\x01\nYou're confused, huh.\x01 *sigh*\x03\x20\n$400, you get it?\x03\x20 For you all.\x01\nYou, er, buying a room?\x03\x40 I mean...\x03\x20\nyou get it.\x03\x20 Just pay now.\x11Yes\nNo\nWhat\x11");
	SetDialogString(2367, "\x10""Receptionist\x10" "Ugh...\x03\x20 $400 for each person, you\nunderstand?\x01 $400 for all faces of your,\ner, band.\x01 Girl,\x03\x20 MAKE A DECISION,\x03\x20 you\nare hogging the queue!\x03\x30 Three people are\nwaiting behind you for their turns!\x11Yes\nNo\nWhat.\x11");
	SetDialogString(2368, "\x10""Receptionist\x10" "I hate this job.\x01");
	SetDialogString(2369, "\x10""Sally\x10" "What.\x01");
	SetDialogString(2370, "\x10""Emmet\x10" "I don't think he is good at his\njob...\x03\x20 but you understand how the\nhotels work, right, Ruby?\x01 We had\nreserved a room back in Lapis City,\nremember?\x01");
	SetDialogString(2371, "\x10""Receptionist\x10" "Sorry for the trouble!\x03\x20 Poor guy\nran out of willpower.\x01 So, renting a\nroom will cost $400 a room, or\n$400 for all of you.\x03\x20 Do you\nwant to do that?\x11Yes\nNo\nWhat\x11");
	SetDialogString(2372, "\x10""Receptionist\x10" "You came to reserve a room in this\nhotel, right?\x03\x20 So you simply give me\n$400 and you get the room,\x03\x20 for\nyou and your mates,\x03\x20 gotcha?\x11Yes\nNo\nWhat\x11");
	SetDialogString(2373, "\x10""Receptionist\x10" "Here we go!\x03\x20 Umm...\x03\x40 Your room number\nis 9, on floor 3.\x01 Now go and take your\nwell-deserved break there.\x01");
	SetDialogString(2374, "\x10""Noah\x10" "Here.\x01");
	SetDialogString(2375, "\x10""Noah\x10" "Uhhh...\x03\x20 I don't think you have enough,\nRuby.\x01");
	SetDialogString(2376, "\x10""Receptionist\x10" "Can't afford?\x03\x20 Well, sorry then.\x01\nCome back with more cash, okay?\x01");
	SetDialogString(2377, "\x10""Receptionist\x10" "No money...\x03\x20 waste of time.\x03\x20 Next.\x01");
	SetDialogString(2378, "He ignores you.\x01");
	SetDialogString(2379, "\x10""Receptionist\x10" "9\x01");
	SetDialogString(2380, "\x10""Emmet\x10" "9?\x03\x20 That's our number?\x01 What floor\nis it?\x01");
	SetDialogString(2381, "\x10""Receptionist\x10" "*yawn*\x03\x40 second.\x01");
	SetDialogString(2382, "\x10""Emmet\x10" "Second floor, got it.\x03\x20 Let's go,\neveryone.\x01");
	SetDialogString(2383, "\x10""Receptionist\x10" "No, I meant \"wait a second\".\x03\x30 It's\nthird floor.\x01");
	SetDialogString(2384, "\x10""Receptionist\x10" "Or was it second?\x03\x30 Who cares, you'll\nfind the room eventually.\x01");
	SetDialogString(2385, "\x10""Emmet\x10" "Okay...\x01");
	SetDialogString(2386, "\x10""Receptionist\x10" "Hiya! This is Sapphire Hotel.\x03\x20 The rooms\nwe provide will not blow your mind...\x03\x20\nwhich is a good thing!\x01 Rent one to\nexperience true invincibility of your mind!\x11Yes\nNo\x11");
	SetDialogString(2387, "\x10""Receptionist\x10" "Hiya again!\x03\x20 In case you forgot,\nyour room number is 9 on floor 3.\x01\nRelax, our service is one of the\nbest in this country!\x03\x20 Even Gemia\nherself approves!\x01");
	SetDialogString(2388, "\x10""Tyler\x10" "Hello!\x03\x20 So you want to go to\nlast floor?\x01 Sorry, I can't do that.\x03\x20\nBut I can give you access to the\nnext floor.\x01");
	SetDialogString(2389, "Floor 3 is now accessible.\x01");
	SetDialogString(2390, "Floor 4 is now accessible.\x01");
	SetDialogString(2391, "Floor 5 is now accessible.\x01");
	SetDialogString(2392, "Floor 6 is now accessible.\x01");
	SetDialogString(2393, "Floor 7 is now accessible.\x01");
	SetDialogString(2394, "Floor 8 is now accessible.\x01");
	SetDialogString(2395, "Floor 9 is now accessible.\x01");
	SetDialogString(2396, "Floor 10 is now accessible.\x01");
	SetDialogString(2397, "\x10""Sally\x10" "..........................\x01");
	SetDialogString(2398, "\x10""Ruby\x10" "..........................\x01");
	SetDialogString(2399, "\x10""Sally\x10" ".........................!\x03\x20\n.........................!\x01");
	SetDialogString(2400, "\x10""???\x10" "Oh, howdy!\x01");
	SetDialogString(2401, "\x10""???\x10" "...Who are you guys?\x01");
	SetDialogString(2402, "*You introduce yourselves and such*\x01");
	SetDialogString(2403, "\x10""Ford\x10" "Okay, you want to go to the last\nfloor?\x01 That's way beyond my paygrade,\ndude.\x03\x20 But...\x03\x20 I can get you to floor 3\nif you want.\x01");
	SetDialogString(2404, "\x10""Ruby\x10" "Yeah.\x01");
	SetDialogString(2405, "\x10""Ford\x10" "Hold on, you need to do me a\nfavor first.\x01 I got a word that a\nmanager is going to come very soon.\x01");
	SetDialogString(2406, "\x10""Tuna\x10" "Manager?\x03\x20 Who?\x01");
	SetDialogString(2407, "\x10""Garry\x10" "Yeah, who?\x03\x20 Please tell it's Kara.\x01");
	SetDialogString(2408, "\x10""Marta\x10" "Yeah,\x03\x20 Kara is the best!\x03\x20\nDoesn't rat her friends out!\x01");
	SetDialogString(2409, "\x10""Ford\x10" "AHAHAHAHAHAHAHAHAHAHAHA\nno.\x01 It's Reti that extremely old and\nstrict hagbag.\x01");
	SetDialogString(2410, "\x10""Tuna\x10" "...\x01\nTime to jump off the building?\x01");
	SetDialogString(2411, "\x10""Ford\x10" "Not yet.\x01 Ruby,\x03\x20 buddy,\x03\x20 stop that\nmanager,\x03\x20 please.\x01 If we don't get in\ntrouble, I will let you in to the next\nfloor.\x03\x20 Capiche?\x01");
	SetDialogString(2412, "\x10""Sally\x10" "Can't you just stop partying and\ngo to your offices or something?\x01");
	SetDialogString(2413, "\x10""Ford\x10" "It may be too late.\x03\x20 I'm relying on\ny'all to cover our backs now.\x01");
	SetDialogString(2414, "\x10""Emmet\x10" "What do you want us to do?\x01");
	SetDialogString(2415, "\x10""Ford\x10" "I don't know!\x03\x20 Barricade her,\x03\x20 push her,\x03\x20\ntalk it out or something.\x01 There is\nlittle time!\x01");
	SetDialogString(2416, "\x10""Ruby\x10" "Okay, we'll try our best.\x01");
	SetDialogString(2417, "\x10""Ford\x10" "Thanks a million.\x01 We'll be resuming our\nparty then.\x01");
	SetDialogString(2418, "\x10""Emmet\x10" "Don't-\x03\x30...\x01");
	SetDialogString(2419, "\x10""Emmet\x10" "Any ideas, anyone?\x01");
	SetDialogString(2420, "\x10""Sally\x10" "Hmmm...\x03\x40 I have one...\x03\x20 but it's probably\nthe worst idea of all time.\x01");
	SetDialogString(2421, "\x10""Emmet\x10" "What is it?\x01");
	SetDialogString(2422, "\x10""Sally\x10" "Like,\x03\x20 actually talking it out with that\nmanager.\x03\x20 Don't know how, but...\x01");
	SetDialogString(2423, "\x10""Sally\x10" "Ummm...\x03\x40 did you have a better\nplan, Emmet?\x01");
	SetDialogString(2424, "\x10""Emmet\x10" "Of course, Sally!\x03\x20 We can bribe the\nmanager with money.\x03\x20 Money is much more\npowerful than words, isn't that\ncorrect?\x01");
	SetDialogString(2425, "\x10""Sally\x10" "Brilliant!\x03\x20 Now the question is,\x03\x20 how\nMUCH money are we willing to bribe?\x01");
	SetDialogString(2426, "\x10""Emmet\x10" "Err...\x03\x40 Dunno.\x01");
	SetDialogString(2427, "\x10""Ruby\x10" "No,\x03\x20 I have a WAY better idea.\x01\nHear me out!\x01");
	SetDialogString(2428, "\x10""Noah\x10" "Wait, I know what you're thinking\nabout, Ruby.\x01");
	SetDialogString(2429, "\x10""Noah\x10" "This.\x01");
	SetDialogString(2430, "\x10""Ruby\x10" "Ohh!\x03\x20 Using that as a barricade?\x03\x20\nThat's a pretty creative idea!\x01");
	SetDialogString(2431, "\x10""Noah\x10" "Thanks!\x01");
	SetDialogString(2432, "\x10""Noah\x10" "Wait...\x03\x40 you were thinking about\nsomething else?\x01");
	SetDialogString(2433, "\x10""Ruby\x10" "Indeed, my plan was to fight the\nmanager.\x01");
	SetDialogString(2434, "\x10""Noah\x10" "Oh.\x01");
	SetDialogString(2435, "\x10""Ruby\x10" "But I think your ideas might be\nbetter than mine, haha.\x01");
	SetDialogString(2436, "\x10""Reti\x10" "...\x01");
	SetDialogString(2437, "\x10""Reti\x10" "Hmph!\x03\x20 Who needs yer asses spanked fer\nslacking off at worktime?\x01 Y'all had\nbetter not fumble,\x03\x20 or y'all shall get\na whip so hard that yer will fly\nto space and get STDs!\x01");
	SetDialogString(2438, "\x10""Sally\x10" "Huh?\x01 Was that the manager?\x01");
	SetDialogString(2439, "\x10""Emmet\x10" "Uhh... let's not waste any more time.\x03\x20\nWe'll let Ruby decide which one's\nthe best to go along with.\x01");
	SetDialogString(2440, "\x10""Ruby\x10" "Okay,\x03\x20 let me think for a second...\x01");
	SetDialogString(2441, "\x10""Ruby\x10" "(If I interact with this shelf, it\nshould move all the way to left\nor right.)\x01");
	SetDialogString(2442, "\x10""Noah\x10" "It worked!\x01");
	SetDialogString(2443, "\x10""Emmet\x10" "Not so fast!\x03\x20 I hear her walking\ntowards the other side.\x01");
	SetDialogString(2444, "\x10""Sally\x10" "So this is the game we're playing,\nhuh.\x01 Let's outmaneuver that hag!\x01");
	SetDialogString(2445, "\x10""Reti\x10" "Ugh....\x03\x30 I can't do this anymore...\x03\x30 If\nonly...\x01\nCurses!\x03\x20 These whippersnappers just keep\nshoving that thing left and right...\x01\nPhew...\x03\x20 I'm bringing a builder with me\nnext time.\x01 Next time...\x03\x40 yer won't be\nso lucky.\x01");
	SetDialogString(2446, "\x10""Reti\x10" "What?\x03\x20 Who are you?\x01");
	SetDialogString(2447, "\x10""Reti\x10" "Step aside!\x01");
	SetDialogString(2448, "\x10""Sally\x10" "We,\x03\x20 uh,\x03\x40 won't.\x01");
	SetDialogString(2449, "\x10""Reti\x10" "What?\x03\x20 That troublemaker Ford hired you\nto guard the door...\x03\x30 didn't he?\x01\nHah,\x03\x20 of course he did!\x03\x20 Too obvious!\x01\nScram, right now!\x01");
	SetDialogString(2450, "\x10""Sally\x10" "And what if we don't, huh?\x01");
	SetDialogString(2451, "\x10""Reti\x10" "Arrogant child...\x01 I'll nicely ask one\nmore time.\x01");
	SetDialogString(2452, "\x10""Reti\x10" "STEP ASIDE!\x01 Yer don't know my true\npower...\x03\x30 you had better listen to\nme before I discipline you with good\nol' ass spanking!\x01");
	SetDialogString(2453, "\x10""Reti\x10" "ARRGGHH!!!\x03\x30 Don't say I didn't WARN\nYOU!!\x01");
	SetDialogString(2454, "\x10""Reti\x10" "This...\x03\x20 is ridiculous.\x01");
	SetDialogString(2455, "\x10""Sally\x10" "You never had a chance.\x01 You cannot\npass.\x01");
	SetDialogString(2456, "\x10""Reti\x10" "Silence...\x01 Yer will not get away-\x03\x10");
	SetDialogString(2457, "\x10""Sally\x10" "SCRAM!\x01");
	SetDialogString(2458, "\x10""Ruby\x10" "I guess we're done?\x01 Let's check up on\nFord.\x01");
	SetDialogString(2459, "\x10""Ruby\x10" "Did you want to go to this door?\x01");
	SetDialogString(2460, "\x10""Reti\x10" "On the money!\x01 I just cannot ignore\nthe loud ass music coming from here,\x03\x20\ncan I?\x01");
	SetDialogString(2461, "\x10""Ruby\x10" "Can I bribe you money?\x01");
	SetDialogString(2462, "\x10""Reti\x10" "...\x01Oooooohhhhhh!\x03\x20 Yer think I'm corrupt,\nhuh?\x01 Guess I can allow myself...\x01\nLet's say,\x03\x20 $150000 sounds like a\nfair deal, right?\x01");
	SetDialogString(2463, "\x10""Ruby\x10" "That's...\x03\x20 way too much.\x01");
	SetDialogString(2464, "\x10""Reti\x10" "Eh?\x03\x20 Too much,\x03\x20 you say?\x01\nI guess it is.\x01 $10000,\x03\x20 I will not go\nlower than that.\x01");
	SetDialogString(2465, "\x10""Ruby\x10" "(Do I give $10000 to the manager?)\x11Yes\nNo\x11");
	SetDialogString(2466, "You handed over $10000.\x01");
	SetDialogString(2467, "\x10""Reti\x10" "Wonderful!\x03\x20 Guess I have to let this\nslide this once.\x01 Farewell, children!\x01");
	SetDialogString(2468, "\x10""Ruby\x10" "I...\x03\x20 don't have that amount of money.\x01");
	SetDialogString(2469, "\x10""Reti\x10" "You don't have $10000?\x01 Ma'am,\x03\x20 how do\nyou even LIVE in here?\x01 Step aside,\x03\x20 I\nhave something to take care of.\x01");
	SetDialogString(2470, "\x10""Ruby\x10" "You cannot go there.\x01");
	SetDialogString(2471, "\x10""Reti\x10" "Yer gonna command me?\x01 I am the\nMANAGER here,\x03\x20 please tell me why\nI wouldn't be able to go there?\x01");
	SetDialogString(2472, "\x10""Ruby\x10" "Um...\x11It's locked\nMy rank is higher\nPolice investigation\nThe room is poisoned\x11");
	SetDialogString(2473, "\x10""Ruby\x10" "That room is locked.\x03\x20 I tried to enter,\nbut I couldn't.\x01 Do you have the key?\x01");
	SetDialogString(2474, "\x10""Reti\x10" "Nonsense!\x03\x20 Out of my way!\x01");
	SetDialogString(2475, "\x10""Ruby\x10" "My position in this company is\nhigher than yours...\x03\x20 Am I wrong?\x01");
	SetDialogString(2476, "\x10""Reti\x10" "What exactly?\x01");
	SetDialogString(2477, "\x10""Ruby\x10" "...\x01""Co-executive.\x01");
	SetDialogString(2478, "\x10""Reti\x10" "Co-executive?\x01 Which floor are you from?\x01");
	SetDialogString(2479, "\x10""Ruby\x10" "Floor...\x03\x20 9.\x01");
	SetDialogString(2480, "\x10""Reti\x10" "Floor 9?\x03\x20 Really?\x01");
	SetDialogString(2481, "\x10""Reti\x10" "I wonder why I have never seen yer\nbefore...\x03\x40 Very curious!\x01");
	SetDialogString(2482, "\x10""Ruby\x10" "Because I was employed very recently...\x01");
	SetDialogString(2483, "\x10""Reti\x10" "Enough with this bullcrap!\x03\x30 Even\na caveman could tell yer a fraud!\x01\nScram!\x01");
	SetDialogString(2484, "\x10""Ruby\x10" "Because there is a police\ninvestigation going on.\x01");
	SetDialogString(2485, "\x10""Reti\x10" "Wh...\x03\x40 are you serious?\x01");
	SetDialogString(2486, "\x10""Ruby\x10" "Yes...\x03\x20 It's a...\x03\x40 crime scene.\x01");
	SetDialogString(2487, "\x10""Sally\x10" "Believe us!\x03\x20 It's a...\x03\x40 very disgusting\x03\x20\nCRIME that has been committed in here!\x01");
	SetDialogString(2488, "\x10""Reti\x10" "I won't believe yer 'il I see it\nmyself!\x01");
	SetDialogString(2489, "\x10""Ruby\x10" "Well...\x03\x20 the room is poisoned.\x01\nWith mercury.\x01");
	SetDialogString(2490, "\x10""Reti\x10" "I...\x03\x30 er,\x03\x20 really?\x01");
	SetDialogString(2491, "\x10""Emmet\x10" "She's right,\x03\x20 we were told to keep\neveryone from entering this room.\x01\nAt least until the...\x03\x30 the poisoning\ngoes away.\x01");
	SetDialogString(2492, "\x10""Reti\x10" "Yer just a bunch of liars!\x01");
	SetDialogString(2493, "\x10""Emmet\x10" "No, we would not be lying about a\nserious threat to human lives.\x01 Please\ncome back later.\x01");
	SetDialogString(2494, "\x10""Reti\x10" "*sigh*\x01 Whatever.\x01");
	SetDialogString(2495, "\x10""Reti\x10" "Hello again!\x03\x20 Now I am prepared.\x01");
	SetDialogString(2496, "\x10""Sally\x10" "Go away!\x03\x20 The poisoning didn't disappear\nyet!\x01");
	SetDialogString(2497, "\x10""Reti\x10" "Mhm...\x01");
	SetDialogString(2498, "\x10""Reti\x10" "Don't you see?\x03\x20 I brought poison-\nprotecting equipment.\x01 Let me through\nthis instant or else!\x01");
	SetDialogString(2499, "\x10""Ford\x10" "Yo!\x03\x20 Did you scare her away?\x01");
	SetDialogString(2500, "\x10""Ruby\x10" "Yeah, we did.\x01");
	SetDialogString(2501, "\x10""Sally\x10" "What the hell is wrong with her?\x01");
	SetDialogString(2502, "\x10""Ford\x10" "Don't ask me.\x01 Anyhow...\x03\x20 Very nicely\ndone, pals!\x01");
	SetDialogString(2503, "\x10""Tuna\x10" "Yessss!!!!!\x03\x20 Let's celebrate!\x01");
	SetDialogString(2504, "\x10""Garry\x10" "Weren't we already celebrating?\x01");
	SetDialogString(2505, "\x10""Tuna\x10" "Uhhh...\x01 celebrate it squared?\x01");
	SetDialogString(2506, "\x10""Marta\x10" "No, no.\x03\x30 How about CUBED?\x01");
	SetDialogString(2507, "\x10""Ruby\x10" "*cough*\x03\x20 Ford?\x01");
	SetDialogString(2508, "\x10""Ford\x10" "Wha-\x03\x20 oh, you wanted to go to a\nhigher floor, I remember.\x01");
	SetDialogString(2509, "\x10""Ford\x10" "Here, buddy.\x01");
	SetDialogString(2510, "\x10""Ford\x10" "Thanks again for saving our careers.\x03\x20\nYou're always welcome here.\x01");
	
	SetDialogString(2511, "\x10""Kyle\x10" "...and when they least expected\nit...\x03\x40 I started throwing 'em dozens\nof punches super quickly until they\nretreated out of surprise.\x01");
	SetDialogString(2512, "\x10""Tia\x10" "Wow.\x03\x20 How exactly did you-\x01");
	SetDialogString(2513, "\x10""Amp\x10" "Important announcement for all\nAmpercorp employees.\x01");
	SetDialogString(2514, "\x10""Amp\x10" "There have been reports of 4\nuninvited people wandering in this\nbuilding.\x01 It's a group led by a\ngirl named Ruby, who has a white\nlabcoat and a red gem on their head.\x01");
	SetDialogString(2515, "\x10""Amp\x10" "If you see the described group,\x03\x20\nI suggest capturing the group and\nbringing them to the first floor.\x01");
	SetDialogString(2516, "\x10""Amp\x10" "I do have to warn you though...\x01\nIt will not be that easy,\x03\x20 so...\x03\x40\nI decided to motivate you all with\na prize...\x01");
	SetDialogString(2517, "\x10""Amp\x10" "Defeat Ruby and their followers...\x03\x40\nand you are promoted to Floor 9, to\nwork as a manager.\x03\x40 And $1000 of course.\x01\nI would do it myself, but I am a\nlittle busy at the moment.\x01");
	SetDialogString(2518, "\x10""Amp\x10" "Good luck,\x03\x20 work smart and...\x03\x30 stay\nvigilant.\x01");
	SetDialogString(2519, "\x10""Tia\x10" "Hmmm,\x03\x20 a floor 9 promotion?\x01");
	SetDialogString(2520, "\x10""Kyle\x10" "Yes, Tia.\x01 This is our time to shine.\x01");
	SetDialogString(2521, "\x10""Dirk\x10" "A group of 4 bozos?\x03\x30 Tsk.\x03\x30 An easy\npromotion for us!\x01");
	SetDialogString(2522, "\x10""Dirk\x10" "Wait...\x03\x40 do we all get a promotion\nif we beat 'em together?\x01");
	SetDialogString(2523, "\x10""Tia\x10" "Hell if I know.\x01");
	SetDialogString(2524, "\x10""Dirk\x10" "Who is that over there?\x03\x30 Is that...\x01");
	SetDialogString(2525, "\x10""Tia\x10" "Those people?\x01");
	SetDialogString(2526, "\x10""Kyle\x10" "It's someone who has a labcoat,\x03\x20 a\ndark red hair and a red gem on\ntheir head...\x01 Of course it is!!\x01");
	SetDialogString(2527, "\x10""Dirk\x10" "Talk about a COINCIDENCE.\x01");
	SetDialogString(2528, "\x10""Dirk\x10" "You!\x01 Come with us or...\x03\x30 I will\ngrab you all and fold you into\npaper airplanes within 3 seconds!\x01");
	SetDialogString(2529, "\x10""Sally\x10" "Try us!\x01");
	SetDialogString(2530, "\x10""Kyle\x10" "Refusing to cooperate?\x03\x20 Then we resort\nto beating you to pulp.\x01");
	SetDialogString(2531, "\x10""Kyle\x10" "Tia,\x03\x20 let's try it for once.\x01");
	SetDialogString(2532, "\x10""Tia\x10" "What?\x01");
	SetDialogString(2533, "\x10""Kyle\x10" "Give me strength,\x03\x20 and,\x03\x20 well,\x03\x20 you'll\nsee.\x01");
	SetDialogString(2534, "\x10""Tia\x10" "...Okay.\x01");
	SetDialogString(2535, "\x10""Dirk\x10" "I've been had.\x01");
	SetDialogString(2536, "\x10""Kyle\x10" "But...\x03\x40 how did we mess this up?\x01");
	SetDialogString(2537, "\x10""Tia\x10" "They had a better plan.\x03\x30 They outsmarted\nus.\x01");
	SetDialogString(2538, "\x10""Kyle\x10" "Tia,\x03\x20 Dirk.\x01");
	SetDialogString(2539, "\x10""Dirk\x10" "Yes?\x01");
	SetDialogString(2540, "\x10""Kyle\x10" "Let's get some drinks.\x03\x20 Tabs on\nme.\x01");
	SetDialogString(2541, "\x10""Tia\x10" "So...\x03\x40 we're kind of similar,\x03\x20 aren't\nwe?\x01 Eh,\x03\x20 anyway...\x01");
	SetDialogString(2542, "\x10""Tia\x10" "Hey, lady...\x01");
	SetDialogString(2543, "\x10""Tia\x10" "You want to hang out with us?\x01");
	SetDialogString(2544, "\x10""Tia\x10" "Cool.\x01");
	SetDialogString(2545, "\x10""Tia\x10" "Floor 7 is where I, Kyle and Dirk\nwork at.\x01 Visit whenever you want.\x01");
	
	SetDialogString(2550, "\x10""Man\x10" "What's up?\x01");
	SetDialogString(2551, "\x10""Man\x10" "I'm fine, thanks.\x01");
	SetDialogString(2552, "\x10""Man\x10" "Heyo,\x03\x20 you have any manners?\x01\nSay something, will you?\x01");
	SetDialogString(2553, "\x10""Man\x10" "What,\x03\x20 you need to pass through?\x01\nNah, madam.\x03\x20 Not so fast.\x01\nLemme finish smoking this pipe\nand I'll skedaddle away, gotcha?\x01");
	SetDialogString(2554, "\x10""Man\x10" "Looks like you didn't get the memo.\x03\x20\nI'm too lazy to move outta here...\x01\nCope harder, pal.\x03\x20 Life is not always\nfair.\x01 Sometimes,\x03\x20 you just cannot\ndo anything about people blocking\nyour paths...\x03\x40 but it is what it is.\x01");
	SetDialogString(2555, "\x10""Kara\x10" "Yo, Ruby!\x03\x20 Kara the manager here!\x01\nHey mister,\x03\x20 let 'em through!\x01");
	SetDialogString(2556, "\x10""Man\x10" "We're discussing important stuff.\x01");
	SetDialogString(2557, "\x10""Kara\x10" "Oh, ok.\x01");
	SetDialogString(2558, "\x10""Man\x10" "Madame.\x03\x20 Did you know you are a\nrabid elephant?\x01 By the way,\x03\x20 I can say\nanything I want and you cannot do\nanything about it.\x01 Actually,\x03\x20 you can\nprobably cry,\x03\x20 that's about it...\x03\x40\nrabid elephant.\x01 Hahahahahaha!\x01");
	SetDialogString(2559, "\x10""Ruby\x10" "\x11""Deal with it\nFight\x11");
	SetDialogString(2560, "\x10""Man\x10" "What?\x03\x20 Don't tell me...\x03\x40 are\nyou trying to pick a FIGHT with me?\x01\nHoo buddy...\x03\x30 I will inform you this.\x01");
	SetDialogString(2561, "\x10""Man\x10" "Tell me,\x03\x20 what do you see right now?\x01");
	SetDialogString(2562, "\x10""Ruby\x10" "Superhero certificate?\x01");
	SetDialogString(2563, "\x10""Sally\x10" "No way.\x03\x20.\x03\x20.\x03\x40 a superhero?!\x01");
	SetDialogString(2564, "\x10""Man\x10" "That's right.\x01 If you try to land a\nfinger on me,\x03\x20 I will land a whole\nmonth on you,\x03\x20 get me?\x01 If I were\nyou,\x03\x20 I'd throw the towel and try to\nfind a creative workaround instead.\x01");
	SetDialogString(2565, "\x10""Man\x10" "So you're doublin' down.\x01 Let's see\nwhat you've got then!\x01");
	SetDialogString(2566, "\x10""Man\x10" "Whoa, chill.\x03\x20 You got some hands\nthere!\x01 Fine, I'll move away.\x01");
	SetDialogString(2567, "\x10""Man\x10" "And that's that!\x01");
	SetDialogString(2568, "\x10""Man\x10" "Sorry,\x03\x20 not movin' away.\x01 If you feel\nstumped,\x03\x20 you could try pushing me\nwith those cubicles.\x01 But you can also\njust wait,\x03\x20 y'know...\x03\x30 I'm not going\nto stay here forever.\x01");
	SetDialogString(2569, "\x10""Man\x10" "I'm only here to talk business\nmatters with some person in here...\x01\nI'm just waitin' for that person\nto come,\x03\x20 but I don't have all time\nin the world.\x01 Eh, no big deal.\x01");
	SetDialogString(2570, "\x10""Man\x10" "n00bs destroyed\x01");
	
	SetDialogString(2571, "\x10""Kara\x10" "Hello!\x03\x20 I'm Kara the manager.\x01\nYou're just in time!\x01");
	SetDialogString(2572, "\x10""Emmet\x10" "Are you friends with Ford?\x01");
	SetDialogString(2573, "\x10""Kara\x10" "Yes!\x03\x20 I assume you're friends with\nhim too.\x01 I heard you wanted to go\nto Amp's floor?\x01");
	SetDialogString(2574, "\x10""Ruby\x10" "Yes, floor 10.\x01");
	SetDialogString(2575, "\x10""Kara\x10" "I'm so sorry, but...\x03\x40 This is\ninevitable.\x01");
	SetDialogString(2576, "\x10""Sally\x10" "Hey, what do you mean?\x01");
	SetDialogString(2577, "\x10""Kara\x10" "...\x01\nIntruder alert!\x03\x20 I must do what Amp\nsays and bring you to floor 1!\x01\nI am is a manager!\x03\x20 And\x03\x30.\x03\x30.\x03\x30.\x03\x30\nget ready.\x01");
	SetDialogString(2578, "\x10""Kara\x10" "Haha,\x03\x20 I underestimated you!\x01 Excuse me\nfor being aggressive...\x01 If I didn't\nfight you,\x03\x20 others would've gotten\nsuspicious and Amp could've docked my\npay...\x01");
	SetDialogString(2579, "\x10""Emmet\x10" "You work on floor 9.\x03\x20 Are you able to\nbring us to the tenth floor?\x01");
	SetDialogString(2580, "\x10""Kara\x10" "Ah...\x03\x20 no, I am not.\x01");
	SetDialogString(2581, "\x10""Sally\x10" "Great...\x03\x20 how do we get there\nthen?\x03\x20 Please tell us.\x01");
	SetDialogString(2582, "\x10""Kara\x10" "Ummm...\x03\x20 other than Amp herself...\x03\x20 only\nthe co-executives have permission to\ndo so.\x01 I tried to convince Flora,\na co-executive, to let you in, but...\x01\nShe refused.\x01");
	SetDialogString(2583, "\x10""Kara\x10" "But don't worry!\x03\x20 I can still bring\nyou to 9th floor to talk to her!\x01\nShe's pretty chill,\x03\x20 I think you will\nget along well.\x01");
	SetDialogString(2584, "\x10""Sally\x10" "Nice.\x01");
	SetDialogString(2585, "\x10""Kara\x10" "Wait!\x01");
	SetDialogString(2586, "\x10""Sally\x10" "What now.\x01");
	SetDialogString(2587, "\x10""Kara\x10" "Floor 9 might have to wait a bit\nlonger...\x03\x30 Because of...\x03\x40 y'know...\x01");
	SetDialogString(2588, "\x10""Amp\x10" "Attention!\x03\x20 The event is starting in a\nfew minutes!\x01");
	SetDialogString(2589, "\x10""Amp\x10" "Y'all better get to floor\n8 in time or you'll be fired frame 1!\x01\nI repeat, do NOT miss it.\x01");
	SetDialogString(2590, "\x10""Amp\x10" "That's all.\x03\x20 Pause your work and take\na mandatory break right now.\x01");
	SetDialogString(2591, "\x10""Kara\x10" "...because of that.\x01 Listen,\x03\x20 I will help\nyou out once the event ends, ok?\x01\nCome and relax at floor 8, I'll\nsee you there!\x01");
	SetDialogString(2592, "\x10""Sally\x10" "How do you even navigate in this\nhuge maze?\x01");
	SetDialogString(2593, "\x10""Kara\x10" "Oh, very simple.\x01 Managers are trained\nto jump professionally to be able to\nget to a point very quickly.\x01\nThat fact motivates workers to not\nslack off in fear of a manager\nairdashing into them from farthest\ncorners within seconds.\x01\nAnyway,\x03\x20 see you in floor 8!\x01");
	
	SetDialogString(2594, "\x10""Employee\x10" "Man, I'm so tired of confiscating\nchairs...\x03\x40 Just why did they all\nsuddenly decide to come here with their\nrolling chairs?\x01 I blame Amp for\ndeciding to remove seats in theatre\nlast time for no reason.\x01");
	SetDialogString(2595, "\x10""Kara\x10" "Hey!\x03\x20 Follow me, I have seats for\nyou.\x01");
	SetDialogString(2596, "\x10""Sally\x10" "Are we going to watch a movie?\x01");
	SetDialogString(2597, "\x10""Kara\x10" "Yes,\x03\x20 or at least I heard there was\ngoing to be an animation of sorts...\x01");
	SetDialogString(2598, "\x10""Kara\x10" "The event should begin about right\nnow.\x01");
	SetDialogString(2599, "\x10""Woman\x10" "Is that everyone?\x01 I see fewer people\nthan in the last event...\x03\x40 Gee,\x03\x20 I wonder\nwhy.\x01");
	SetDialogString(2600, "\x10""Kara\x10" "Look, that's Flora.\x01");
	SetDialogString(2601, "\x10""Flora\x10" "Welp.\x03\x20 Without further ado,\x03\x20 let's\nbegin the event,\x03\x20 shall we?\x01");
	SetDialogString(2602, "\x10""Flora\x10" "I think you all know me,\x03\x20 but I already\nsee newcomers on the seats, so...\x01\nI'm Flora,\x03\x20 a co-executive manager of\nAmpercorp.\x01 This event has been\norganized for educational and\nmotivational purposes.\x01 And\nentertainment...\x03\x30\nbecause I think we all should have fun\neven at work!\x01 Well,\x03\x20 FUN is an alien\nconcept for some managers...\x03\x30 anyway,\x03\x20\nmoving on.\x01");
	SetDialogString(2603, "\x10""Flora\x10" "That person to the left of me is\na producer and director of the film.\x01\nHis name's Rex.\x01");
	SetDialogString(2604, "\x10""Rex\x10" "Uh...\x03\x20 greetings.\x01 I hope you enjoy the\nfilm.\x01");
	SetDialogString(2605, "One film later...\x01");
	SetDialogString(2606, "\x10""Flora\x10" "And that's everything.\x01 The event\nis over,\x03\x20 now you may go back\nto work.\x01");
	SetDialogString(2607, "\x10""Kara\x10" "Flora should be in the next floor.\x01");
	SetDialogString(2608, "\x10""Emmet\x10" "Wait,\x03\x20 how are we going to\nnegotiate with her?\x03\x20 You could not\nconvince her despite working in the\nsame floor, right?\x01");
	SetDialogString(2609, "\x10""Kara\x10" "...\x01I don't know how.\x01 I'm afraid you\nmay have to fight her.\x01");
	SetDialogString(2610, "\x10""Sally\x10" "Huh?\x03\x20 We can take her easily.\x01");
	SetDialogString(2611, "\x10""Kara\x10" "Is that so?\x01 You see...\x03\x40 Flora is\na Medium Hero.\x01 She's WAY stronger than\neven me and other managers.\x01 She's a\nFLOWER BEAST.\x01");
	SetDialogString(2612, "\x10""Ruby\x10" "I think we're able to compete with\nher.\x01");
	SetDialogString(2613, "\x10""Kara\x10" "Well,\x03\x20 you're on your own.\x01 I don't\nthink other co-executives will\ncooperate,\x03\x20 so I'm sure this is your\nbest chance to get to Amp's floor.\x01");
	SetDialogString(2614, "\x10""Kara\x10" "I wonder why you'd want to get to\nAmp's floor so badly, but...\x03\x20 I won't\nquestion it.\x01 See you later, Ruby...\x03\x20\nnot covered in flowers hopefully.\x01");
	
	SetDialogString(2615, "\x10""Flora\x10" "Hm...\x03\x20 really persistent,\x03\x20 aren't\nwe?\x01");
	SetDialogString(2616, "\x10""Flora\x10" "Like,\x03\x20 what kind of stunt are you\ntrying to pull?\x01 What kind of business\ndo you have with Amp?\x01");
	SetDialogString(2617, "\x10""Flora\x10" "Ah, don't mind it.\x03\x20 I'll leave\nthis sort of interrogation to Amp.\x01\nDo you,\x03\x20 like,\x03\x20 have any sort of\ndocument to prove yourself worthy\nto officially meet up with Amp?\x01");
	SetDialogString(2618, "\x10""Ruby\x10" "Pretty sure I don't have such\n\"documents\"...\x01");
	SetDialogString(2619, "\x10""Flora\x10" "Ok then!\x03\x20 Let's have a face-off!\x01\nDefeat me and I'll permit you to\nenter floor 10.\x01");
	SetDialogString(2620, "\x10""Sally\x10" "Are you really a Medium Hero?\x01");
	SetDialogString(2621, "\x10""Flora\x10" "Indeed I am.\x01 But soon enough,\x03\x20 I will\nrise to the ranks of Top Hero\nand possibly even Superhero...\x01\nThey call me a \"prodigy\" for a reason,\ny'know.\x01");
	SetDialogString(2622, "\x10""Sally\x10" "We've beaten Sanji before,\x03\x20 so...\x01\nWe can totally handle you!\x01");
	SetDialogString(2623, "\x10""Flora\x10" "Sanji?\x03\x20 He's a fraud.\x03\x30 He's not even\nrecognized as a Low Hero.\x01 I challenged\nhim to a duel once...\x03\x30 and it ended\nup in him losing so badly I felt bad\nfor him.\x01");
	SetDialogString(2624, "\x10""Sally\x10" "Really?\x03\x30 I never heard about it.\x01");
	SetDialogString(2625, "\x10""Flora\x10" "I'd love to talk more,\x03\x20 but I don't\nhave all time in the world.\x01 Ruby,\x03\x20\nare you ready to fight me??\x01");
	SetDialogString(2626, "\x10""Ruby\x10" "Of course,\x03\x20 let's settle this.\x01");
	SetDialogString(2627, "\x10""Flora\x10" "Um...\x03\x30 En garden!\x01");
	SetDialogString(2628, "\x10""Flora\x10" "No way!!\x03\x30 How did I lose to some\nrandom street muggers?!\x01");
	SetDialogString(2629, "\x10""Ruby\x10" "Calm down.\x01 We didn't use our own\npowers...\x03\x20 we instead borrowed the\npowers of multiple strong people.\x01");
	SetDialogString(2630, "\x10""Noah\x10" "But we still won...\x01");
	SetDialogString(2631, "\x10""Flora\x10" "...\x01");
	SetDialogString(2632, "\x10""Flora\x10" "I think I'll drink some tea to\nrelax...\x01 Come in if you want.\x01");
	
	SetDialogString(2633, "\x10""Ruby\x10" "Flora,\x03\x20 would you allow us to\nenter floor 10, please?\x01");
	SetDialogString(2634, "\x10""Flora\x10" "Okay,\x03\x20 but you have to tell me\nwhat exactly are you going to do\nin that floor.\x01");
	SetDialogString(2635, "\x10""Ruby\x10" "Getting the Ancient Gem,\x03\x20 that's it.\x01");
	SetDialogString(2636, "\x10""Flora\x10" "Amp isn't present yet...\x03\x30 you aren't\nplanning to steal it...\x03\x20 right?\x01");
	SetDialogString(2637, "\x10""Emmet\x10" "We're not going to steal it,\x03\x20\npromise.\x01 We'll get permission from\nAmp first.\x01");
	SetDialogString(2638, "\x10""Flora\x10" "Okay...\x03\x20 I trust you then.\x01");
	SetDialogString(2639, "\x10""Sally\x10" "Finally.\x03\x20 We're near the end of\nthis corporate adventure.\x01");
	SetDialogString(2640, "\x10""Flora\x10" "Wait.\x03\x20 Ruby.\x01");
	SetDialogString(2641, "\x10""Flora\x10" "I must warn you about Amp.\x01\nHer rank...\x03\x20 is Top Hero.\x01 Yes,\x03\x20\nTop Hero,\x03\x20 even better than me, the\nMedium Hero.\x01");
	SetDialogString(2642, "\x10""Flora\x10" "Y'know...\x03\x20 Amp was my mentor.\x01\nShe teached me pretty much everything\nnecessary to become a powerful Hero\nof our country Gemia.\x01 I always\nwanted to best her,\x03\x20 but she always\noverpowered me,\x03\x20 even with my\ncurrent powers.\x01");
	SetDialogString(2643, "\x10""Flora\x10" "I'm sure you will end up fighting\nAmp...\x03\x30 kick her for me, ok?\x01");
	
	SetDialogString(2644, "\x10""Lulu\x10" "Hahahaha...\x03\x30 What's the matter?\x03\x20\nCan't land a hit on me?\x01 Well...\x03\x20\nI can dodge EVERYTHING now,\x03\x20 so you\nmight as well surrender!!\x01");
	SetDialogString(2645, "\x10""Lulu\x10" "No!!!\x01 How did you hit me?!\x03\x20 That's\nnot fair!!\x01 That's it,\x03\x20 I'm going\nALL-OUT!!!\x01");
	SetDialogString(2646, "\x10""Sally\x10" "Oh my god,\x03\x20 this is going to\ntake a while.\x01");
	SetDialogString(2647, "\x10""Lulu\x10" "Don't you \"oh my god\" me!!\x01 I told you\nI am a God!!\x01 I can do anything,\x03\x20 I\ncan defeat you easily,\x03\x20 I can also\nmake you naked instantly if I want!!\x01\nHahaha!!\x01");
	SetDialogString(2648, "\x10""Lulu\x10" "Look at you!!\x03\x30 Trying your best to\ndefeat me?!\x01 Pathetic weaklings!\x03\x20 Let\nme show you how I try MY best to defeat\nyou.\x01");
	SetDialogString(2649, "\x10""Ruby\x10" "(My team has been defeated...)\x01\n(What am I even supposed to do?\x03\x30\nLulu's WAY too strong for some reason.)\x01\n(Is this how it really ends?\x03\x30 I'll\njust see what happens next...)\x01");
	
	SetDialogString(2650, "\x10""Border Officer\x10" "Metro tickets cost $150 per person.\x01\nChoose which location you want to stop\nin.\x11Rivergreen Town\nBluesteel Town\nLapis City\nSapphirepolis\nDon't buy\x11");
	SetDialogString(2651, "\x10""Border Officer\x10" "Metro tickets cost $150 per person.\x01\nChoose which location you want to stop\nin.\x11Sapphirepolis\nDon't buy\x11");
	SetDialogString(2652, "\x10""Border Officer\x10" "Sorry, the Sapphireland Metro is under\nshort maintenance.\x03\x20 Please check back\nlater.\x01");
	SetDialogString(2653, "\x10""Border Officer\x10" "Here's your ticket.\x03\x20 Have a great trip!\x01");
	SetDialogString(2654, "\x10""Border Officer\x10" "Ma'am...\x03\x40 you are already there.\x01");
	SetDialogString(2655, "\x10""Border Officer\x10" "Metro tickets cost $150 per person.\x01\nOh,\x03\x20 you aren't carrying enough cash?\x03\x20\nPlease come back with sufficient money.\x01");
	SetDialogString(2656, "\x10""Ruby\x10" "(I'd rather not waste my money right\nnow.\x03\x20 I'll come back after my journey\nis finished.)\x01");
	SetDialogString(2657, "\x10""WL Employee\x10" "Sorry, the Whitelight HQ is temporarily\nclosed.\x03\x20 Come back later.\x01");
	SetDialogString(2658, "\x10""WL Employee\x10" "We're not allowing anyone to enter\nbecause some rooms are under\nrenovation.\x01 When to come back?\x03\x20\nDunno,\x03\x20 maybe whenever you'll see\na kettlehead appear out of nowhere?\x01");
	SetDialogString(2659, "\x10""WL Employee\x10" "Hum dum,\x03\x20 hello,\x03\x20 food is nice,\x03\x20 do\nyou like food and such,\x03\x20 haha.\x01");
	SetDialogString(2660, "\x10""Receptionist\x10" "Sapphire Hotel, baby.\x01 $400 and such.\x11Yes\nNo\x11");
	SetDialogString(2661, "Do you want to rest?\x11Yes\nNo\x11");
	SetDialogString(2662, "You have already rested.\x01");
	SetDialogString(2663, "\x10""Lulu\x10" "...\x01How the f*** did I fall for that\nthree times\?!\?\?!\?!!\x01");
	SetDialogString(2664, "\x10""Sally\x10" "'Cause you're stupid, that's why.\x01");
	SetDialogString(2665, "\x10""Lulu\x10" "GO F*** YOURSELF!\x01");
	SetDialogString(2666, "\x10""Lulu\x10" "I fell for it again...\x03\x50 That's it I am\ngoing ALL-OUT and COMPLETELY DESTROY\nyou at all costs and I will sacrifice\neverything I have in order to kill you.\x01");
	SetDialogString(2667, "Perry's dead brother,\x03\x20 Panda.\x01");
	SetDialogString(2668, "\x10""Tyler\x10" "Kara's a really nice manager,\x03\x20 so you\ngot pretty lucky I guess!\x01 Other\nmanagers, especially Reti, would\nhave...\x03\x30 been more repressive.\x01");
	SetDialogString(2669, "Access denied.\x01");
	
	SetDialogString(2670, "\x10""???\x10" "...Hello?\x01 Who are you looking for?\x01");
	SetDialogString(2671, "\x10""Ruby\x10" "I'm looking for someone who can get\nme to Floor 10.\x01");
	SetDialogString(2672, "\x10""???\x10" "Who sent you here?\x03\x20 It was Kara,\x03\x20 wasn't\nit??\x01");
	SetDialogString(2673, "\x10""Ruby\x10" "Yes...\x03\x20 Are you Flora?\x01");
	SetDialogString(2674, "\x10""Flora\x10" "Ah,\x03\x20 yes.\x01 I am that person you were\nlooking for,\x03\x20 I can grant access to\nAmp's floor to anyone at will.\x01 But I\nam not giving it to everyone like free\ncandy,\x03\x20 so...\x01");
	SetDialogString(2675, "\x10""Flora\x10" "What makes you think you'd be able to\nget it in the first place?\x01");
	SetDialogString(2676, "\x10""Ruby\x10" "I really need something from that\nfloor.\x03\x20 I'd fight you for it.\x01");
	SetDialogString(2677, "\x10""Flora\x10" "Are you challenging me for a fight?\x03\x20\nAre you mad?\x01 For your sake,\x03\x20 I'm gonna\nwarn you that I am a Medium Hero.\x01\nDo you REALLY want to fight me?\x01");
	SetDialogString(2678, "\x10""Ruby\x10" "Let's settle this already.\x01");
	SetDialogString(2679, "\x10""Flora\x10" "Ow!\x03\x20 Enough,\x03\x20 enough!\x01 You're much\nstronger than I thought.\x01");
	SetDialogString(2680, "\x10""Flora\x10" "Holy crap...\x03\x20 I've never seen this\nwizardry before in my eyes...\x01 You would\neasily take down Amp,\x03\x20 I'm sure of\nthat.\x01");
	SetDialogString(2681, "\x10""Flora\x10" "Do whatever you want...\x03\x20 Just let me\nrelax for now.\x01");
	
	SetDialogString(2682, "\x10""WL Employee\x10" "No entry allowed.\x01");
	SetDialogString(2683, "An odd-looking telescope.\x11Use\nLeave\x11");
	SetDialogString(2684, "\x10""???\x10" "Who the hell's snooping around my\nprivate property?\x01 You three!\x03\x20 What are\nyou doing here?\x01");
	SetDialogString(2685, "\x10""???\x10" "Get the hell outta here!\x01");
	SetDialogString(2686, "\x10""Emmet\x10" "Sorry, we got a bit lost.\x03\x20 Who are you?\x01");
	SetDialogString(2687, "\x10""???\x10" "Who am I?\x01");
	SetDialogString(2688, "\x10""Emmet\x10" "Yes...\x03\x20 I just wanted to ask a few\nquick questions.\x01");
	SetDialogString(2689, "\x10""???\x10" "I ain't have no time to talk with the\nlikes of you.\x01");
	SetDialogString(2690, "\x10""Emmet\x10" "There's something very shady going on,\x03\x20\nisn't there?\x01");
	SetDialogString(2691, "\x10""Gregory\x10" "*sigh* Gregory's my name.\x01 And don't\nthink I didn't see you touching that\ntelescope of mine!\x03\x20 What were you doing?\x01");
	SetDialogString(2692, "\x10""Emmet\x10" "Just...\x03\x20 collecting evidence.\x01 By the\nway, why is the \"telescope\" directed at\nLisao's house?\x01");
	SetDialogString(2693, "\x10""Gregory\x10" "Oh,\x03\x20 uh...\x03\x30 what house?\x01");
	SetDialogString(2694, "\x10""Emmet\x10" "Lisao's house,\x03\x20 y'know that small wooden\nhouse owned by a lady using vine magic?\x01");
	SetDialogString(2695, "\x10""Gregory\x10" "Ohhhh, you mean that green-haired girl?\x03\x20\nErr... I was looking out for her, 't's\nall.\x01 It's a dangerous creature after\nall,\x03\x20 gotta do what yer can.\x01");
	SetDialogString(2696, "\x10""Emmet\x10" "She may be dangerous...\x03\x20 but you're\nspying on her in her own house,\x03\x20\nviolating her privacy and all...\x01 Isn't\nthat going a bit too far?\x01");
	SetDialogString(2697, "\x10""Gregory\x10" "I'll be harvesting your hair and blood\nif you keep asking foolish questions.\x01\nThat bitch is sub-human,\x03\x20 or should I\nsay,\x03\x20 an animal,\x03\x20 an inferior being.\x01 And\nnow those beings are trying to take\nover us real humans.\x01 Disgusting wastes\nof space!\x03\x20\nThey're the reason this world has gone\nto crap!\x01 These \"supernaturals\" should\nbe globally terminated if we ever hope\nto bring back the golden years of\nhumanity...\x01");
	SetDialogString(2698, "\x10""Emmet\x10" "Wh... what's your problem?\x01");
	SetDialogString(2699, "\x10""Ruby\x10" "This nutcase thinks all problems are\ncaused by the existence of \"gifted\"\npeople.\x01 Only a non-human being would\nmake that stuff up, am I right?\x01");
	SetDialogString(2700, "\x10""Gregory\x10" "Watch yer mouth, ma'am!\x03\x20 Even the\npolice want that sheep dead.\x01\nHey! Tell me one good thing those\n\"gifted\" dipcraps have done, will you?\x01\nNothing?\x03\x20 That's my point, these\nwretched sub-humans have no reason to\nexist in this world but to hurt people!\x01");
	SetDialogString(2701, "\x10""Ruby\x10" "People like you are the reason why\ngifted people don't get along with\nothers well.\x01");
	SetDialogString(2702, "\x10""Gregory\x10" "That's enough, I needn't hear more\nfrom you!\x03\x20 I give you last chance to\nget out unharmed...\x01");
	SetDialogString(2703, "\x10""Noah\x10" "Ruby...\x03\x30 I-I think we should stay away-\x01");
	SetDialogString(2704, "\x10""Ruby\x10" "No, we shouldn't.\x01");
	SetDialogString(2705, "\x10""Gregory\x10" "Well...\x03\x20 don't say I didn't warn\nyou.\x01");
	SetDialogString(2706, "\x10""Ruby\x10" "Don't mind if I take those things...\x01");
	SetDialogString(2707, "You got Gregory's Scythe and Gregory's\nGun.\x01");
	SetDialogString(2708, "\x10""Gregory\x10" "Hey!!\x03\x20 I need those-\x01");
	SetDialogString(2709, "\x10""Ruby\x10" "I think we should give the weapons to\nLisao, what do you think?\x01");
	SetDialogString(2710, "\x10""Emmet\x10" "What for..?\x01");
	SetDialogString(2711, "\x10""Gregory\x10" "GIVE MY WEAPONS-\x03\x20 I mean, TOOLS back\nto me!!\x01 Or else...\x01");
	SetDialogString(2712, "\x10""Ruby\x10" "Some people never learn, huh?\x01 Let's\npay Lisao a visit and give her\nadvantage over this psychopath.\x01");
	SetDialogString(2713, "\x10""Ruby\x10" "Hello?\x03\x20 Wake up, Lisao.\x01");
	SetDialogString(2714, "\x10""Ruby\x10" "So...\x03\x20 I need to warn you about\nsomething.\x01");
	SetDialogString(2715, "\x10""Lisao\x10" "What...\x03\x30 you're gonna kill me.\x01\nJust end my misery...\x01");
	SetDialogString(2716, "\x10""Emmet\x10" "No, we're here to help you!\x01");
	SetDialogString(2717, "\x10""Lisao\x10" "Help me fall asleep forever...\x01");
	SetDialogString(2718, "\x10""Emmet\x10" "No!\x03\x20 You're...\x03\x20 Well...\x01");
	SetDialogString(2719, "\x10""Ruby\x10" "I have a gift for you.\x01");
	SetDialogString(2720, "\x10""Lisao\x10" "Why are you giving it to me?\x01");
	SetDialogString(2721, "\x10""Emmet\x10" "We got it from a psycho that spies on\nyou and thinks you're non-human or\nwhatever.\x01");
	SetDialogString(2722, "\x10""Ruby\x10" "You're free to use it for whatever\nyou want.\x01 And yes,\x03\x20 you need to be\ncareful of that psycho who goes by the\nname of Gregory.\x01");
	SetDialogString(2723, "\x10""Noah\x10" "Hey...\x03\x30 you're not sub-human.\x01");
	SetDialogString(2724, "\x10""Lisao\x10" "...I'm so confused.\x01");
	SetDialogString(2725, "\x10""Ruby\x10" "It's okay.\x03\x20 Just be aware that someone's\nout to spy on you and kill you.\x01\nYou could share that info with the\nLeaf Crew.\x01");
	SetDialogString(2726, "\x10""Noah\x10" "Don't you think we should... apologize\nto her?\x01");
	SetDialogString(2727, "\x10""Ruby\x10" "Right.\x03\x20 Sorry for beating you up, Lisao.\x01\nAnd sorry for stealing the Ancient Gem.\x01");
	SetDialogString(2728, "\x10""Lisao\x10" "Take it,\x03\x20 I don't mind.\x01 I need to think\nabout this.\x01");
	SetDialogString(2729, "\x10""Emmet\x10" "You're a good person, Lisao.\x03\x20 Don't\nlisten to those who say you're not\nhuman.\x01 You're far more human than\nthose losers will ever be.\x01");
	SetDialogString(2730, "\x10""Lisao\x10" "Heh...\x03\x20 thanks.\x01");
	SetDialogString(2731, "\x10""Emmet\x10" "......\x01");
	SetDialogString(2732, "\x10""Lisao\x10" "Wait...\x03\x20 I don't know your names.\x01");
	SetDialogString(2733, "\x10""Ruby\x10" "I'm Ruby,\x03\x20 that's Noah, and the one you\nkissed is Emmet.\x01");
	SetDialogString(2734, "\x10""Lisao\x10" "Want to join the Leaf Crew?\x01");
	SetDialogString(2735, "\x10""Emmet\x10" "Uh... no thanks, we're busy.\x01");
	SetDialogString(2736, "\x10""Lisao\x10" "Whatever,\x03\x20 bye.\x01");
	SetDialogString(2737, "\x10""Ruby\x10" "Wait, almost forgot!\x03\x20 Take this.\x01");
	SetDialogString(2738, "You handed over the Forestpath Guide\nto Lisao.\x01");
	SetDialogString(2739, "\x10""Ruby\x10" "This will help you find that\npsychopath's hideout if you ever feel\nlike being on the offensive.\x01 Wish you\ngood luck with slaying that monster.\x01");
	SetDialogString(2740, "\x10""Lisao\x10" "Leave me and my thoughts alone for\nnow, please.\x01");
	
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
	SetDialogString(3064, "You try to stay away from the portal.\x01\nBut the portal's force is too big,\x03\x20 you\nget sucked in anyway.\x01");
	
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
	SetDialogString(3159, "\x10""!!!!!\x10" "You have passed your final challenge.\x01\nThe final Ancient Gem is nearby...\x03\x20 it\nis time to finish our mission.\x01");
	SetDialogString(3160, "\x10""!!!!!\x10" "The mission of obtaining the Ancient\nGems...\x03\x40 maybe it is something you\nshould've done earlier...\x01\nBut it doesn't matter,\x03\x20 all that matters\nis that you've done it.\x01");
	SetDialogString(3161, "\x10""!!!!!\x10" "...\x01");
	SetDialogString(3162, "\x10""!!!!!\x10" "Do you see and hear me well?\x01\nInteresting...\x03\x30 it must be due to the\ninfluence of the final Ancient Gem,\x03\x20\nright?\x01");
	SetDialogString(3163, "\x10""!!!!!\x10" "This is why you have followed me.\x01\nHad you erased yourself at that time...\x03\x40\nThe Ultimate Evil would've continued to\nconsume the world,\x03\x20 unpunished.\x01");
	SetDialogString(3164, "\x10""!!!!!\x10" "The success of the Ultimate Plan\nchanged your life forever.\x01 It was the\nhappiest day of your life...\x01 Nothing\ncould've brought your mood down.\x01");
	SetDialogString(3165, "\x10""!!!!!\x10" "But the world was still plagued\nwith the essence of dark and rotten.\x01\nThe evil can be punished and be\naccountable for its sins,\x03\x30 it is a\ntheory you have proven yourself.\x01");
	SetDialogString(3166, "\x10""!!!!!\x10" "So why not bring justice to the\nrest of the Gemia,\x03\x20 and maybe even the\nworld?\x01 That is when we decided to work\non the Rubindeavor.\x01");
	SetDialogString(3167, "\x10""!!!!!\x10" "We created the Protagonist's Labcoat,\x03\x20\nletting us equip lots of items at\nease...\x01 We created the Magical Gem,\x03\x20\ncapable of transferring the enemy's\nphysical and spiritual form into\nyourself.\x01");
	SetDialogString(3168, "\x10""!!!!!\x10" "Had it not been for Sapphireton Lab\nand its leftovers,\x03\x20 Rubindeavor would\nhave never turned into reality.\x01\nAnd...\x03\x30 we wouldn't be here at all,\x03\x30\nlet alone be alive.\x01");
	SetDialogString(3169, "\x10""!!!!!\x10" "The question is,\x03\x20 when I will become\nreal?\x01 If I ever became real,\x03\x20 all\nof your wishes and needs would've been\nfulfilled...\x01");
	SetDialogString(3170, "\x10""Rubin\x10" "I'm very proud of you,\x03\x20 Ruby.\x01\nYou are talented indeed,\x03\x20 unlike those\ndisgusting smoothbrains whose sole\npurpose is to drag you down.\x01");
	SetDialogString(3171, "\x10""Rubin\x10" "I am rooting for you to make your\ndreams come true!\x01");
	SetDialogString(3172, "\x10""Ruby\x10" "(I am not turning back.)\x01");
	SetDialogString(3173, "\x10""Rubin\x10" "Hmmm...\x03\x30 looks like you have to face it\nyet again, Ruby.\x01 Yes, it is THAT time.\x01");
	SetDialogString(3174, "\x10""Ruby\x10" "Huh?\x01");
	SetDialogString(3175, "\x10""Rubin\x10" "The bad memories of your past...\x03\x40\nThe fears...\x03\x30 The hatred...\x03\x30 And THEM...\x01\nAll that lies beyond this gate.\x01");
	SetDialogString(3176, "\x10""Ruby\x10" "I don't have time to deal with this.\x01\nCan you return me, please?\x01");
	SetDialogString(3177, "\x10""Rubin\x10" "I'm afraid I cannot.\x01 But at least while\nyou're here,\x03\x30 the time will pass very\nslowly in the real world.\x01 C'mon,\x03\x30 don't\nignore the possibility of the seed of\nthe Evil manifesting in your mind.\x01 If\nyou aren't careful,\x03\x20 you might end up\nbecoming the one you always swore to\ndestroy.\x01");
	SetDialogString(3178, "\x10""Rubin\x10" "Face the Evil,\x03\x30 and only then you can\ngo back to the real world.\x01");
	SetDialogString(3179, "\x8f\x01""My younger years were a complete joke.\x01\nNever would I want to return to old\ntimes ever,\x03\x20 miss me with that.\x01");
	SetDialogString(3180, "\x8f\x01""Gem of trauma.\x11""Take and remind self\nNot now\x11");
	
	SetDialogString(3181, "\x10""Mother\x10" "Ruby.\x01");
	SetDialogString(3182, "\x10""Mother\x10" "What did I ask you to do earlier this\nmorning?\x01 Hm?\x03\x20 Clean the dishes?\x01");
	SetDialogString(3183, "\x10""Ruby\x10" "...\x01");
	SetDialogString(3184, "\x10""Mother\x10" "And why are the dishes still dirty?\x01\nI asked you nicely,\x03\x20 \"please clean the\ndishes while I am away\".\x01 What's\ngotten to you right now?\x01");
	SetDialogString(3185, "\x10""Mother\x10" "Playing silent,\x03\x20 aren't we?\x01 Why are you\nnot saying anything?\x01 Did you do school\nhomework?\x01");
	SetDialogString(3186, "\x10""Mother\x10" "No?\x01 Your eyes are saying no,\x03\x20 correct?\x01\nI'll ask again.\x01 Did.\x03\x20 You.\x03\x20 Do.\x03\x20\nSchool.\x03\x20 Homework?\x01 Answer my question.\x01");
	SetDialogString(3187, "\x10""Ruby\x10" "...\x01No.\x01");
	SetDialogString(3188, "\x10""Mother\x10" "Why?\x01 Because you got too cocky,\x03\x20\nam I wrong?\x01 You were living a bit too\nwell...\x03\x30 maybe we didn't restrict you\nenough.\x01 Shame on you,\x03\x20 Ruby.\x01");
	SetDialogString(3189, "\x10""Mother\x10" "What are you looking at me like\nthat?!\x01 How long will this circus\nkeep going?\x01 You started it,\x03\x20 and you are\nkeen on continuing it like a total\nclown you are...\x01");
	SetDialogString(3190, "\x10""Mother\x10" "Oh,\x03\x20 look at you,\x03\x20 pathetic baby...\x03\x30\nGo,\x03\x20 cry me a river.\x01 The one who should\nbe crying is ME,\x03\x20 not YOU.\x01 I work\nall day,\x03\x20 all week,\x03\x20 all year,\x03\x20 am\ntired.\x01 And seeing you treat me like\nthis...\x03\x30 it aches my heart.\x01");
	SetDialogString(3191, "\x10""Mother\x10" "Ruby.\x03\x20 Stop crying right now.\x01\nYou have NO reason to cry whatsoever.\x01\nImagine if I were to cease my work...\x03\x30\nI would get fired and have no income\nto pay rent,\x03\x20 taxes,\x03\x20 buy food,\x03\x20 et\ncetera.\x01 That's what you are doing\nright now,\x03\x20 am I wrong?\x01");
	SetDialogString(3192, "\x10""Mother\x10" "I said STOP CRYING.\x01 I do NOT need\nto see your filthy tears.\x01 You are\nliving a GOLDEN life,\x03\x20 and your\nstupidity is missing out on GOLDEN\nopportunities!\x01");
	SetDialogString(3193, "\x10""Mother\x10" "Oh my god...\x03\x30 STOP CRYING YOU BITCH!\x01\nStop crying or I will shred that\nalbum of yours and f*ckin' throw it in\ntrash.\x01 You're killing me right now.\x01");
	SetDialogString(3194, "\x10""Ruby\x10" "Shut up.\x01");
	SetDialogString(3195, "\x10""Mother\x10" "H...\x03\x40How dare you...\x03\x50 You tell me\nto...\x03\x30 shut up?\x01");
	SetDialogString(3196, "\x10""Mother\x10" "You are scum...\x03\x40 you are going to\nregret this,\x03\x20 mark my words,\x03\x20 you\novergrown piece of sh*t.\x01 You're going\nto talk to dad about this.\x01");
	SetDialogString(3197, "\x10""Mother\x10" "You...\x03\x40 YOU F*CKING BITCH.\x01 YOU ARE\nOUT OF YOUR F*CKING MIND?!\x01");
	SetDialogString(3198, "\x10""Mother\x10" "Violence against your parents...\x03\x30 kids\nlike you should be locked up in\nbasements and NEVER see the light of\nday ever again!\x01");
	SetDialogString(3199, "\x10""Father\x10" "What's going on here?!\x01");
	SetDialogString(3200, "\x10""Mother\x10" "Ruby...\x03\x30 she slapped me right in the\nface!\x01 Please,\x03\x20 help me,\x03\x20 I am SO\nfed up with this sh*t...\x01");
	SetDialogString(3201, "\x10""Father\x10" "...\x01""You can't be serious.\x01 Ruby would\nnever do that!\x01");
	SetDialogString(3202, "\x10""Mother\x10" "Please...\x03\x20 I'm telling you truth...\x01\nDo something about Ruby,\x03\x20 PLEASE...\x01");
	SetDialogString(3203, "\x10""Father\x10" "Ruby,\x03\x30 it is best if you come\nwith me.\x01");
	SetDialogString(3204, "\x10""Father\x10" "Come with me right now,\x03\x20 we need\nto discuss this situation.\x01");
	SetDialogString(3205, "\x10""Father\x10" "Do I need to drag you all the way?\x01\nC'mon,\x03\x20 c'mere Ruby.\x01");
	SetDialogString(3206, "\x8f\x01""When I started to really think\nsomething's not right...\x01 Is that really\nhow it works?\x01 Am I the one who should\ncarry all the burden,\x03\x20 not them?\x01");
	
	SetDialogString(3210, "\x10""Director\x10" "You say she wouldn't listen at\nall.\x01 Are you sure?\x01");
	SetDialogString(3211, "\x10""Professor\x10" "I'm telling you!\x01 Ruby kept skipping my\nclasses...\x03\x20 haven't made any essays...\x03\x20\nand refused to cooperate with me!\x01\nI tried many times to convince her to\ncatch up with the program...\x03\x40 zero\neffect.\x01 She doesn't want to study,\x03\x20\nit's best for her to be expelled.\x01");
	SetDialogString(3212, "\x10""Director\x10" "I see.\x01 Ruby,\x03\x20 you've got plenty of\nstrikes,\x03\x30 enough for me to consider\nexpelling you and not dealing with your\nnonsense.\x01 Do you have anything to say\nabout it?\x01");
	SetDialogString(3213, "\x10""Ruby\x10" "These classes are useless.\x01 I'd rather\nfocus on science and technology,\x03\x30 not\nwriting pointless 20 page essays every\nweek...\x01");
	SetDialogString(3214, "\x10""Professor\x10" "These classes are MEANT for making\ncreative and educated personalities...\x01\nThey are DIRECTLY related to science\nand technology you \"like so much\".\x01");
	SetDialogString(3215, "\x10""Director\x10" "She is right,\x03\x20 Ruby.\x01 These so-called\n\"useless\" studies are included in the\nprogram for a reason.\x01 They are\nMANDATORY,\x03\x20 can you not understand?\x01");
	SetDialogString(3216, "\x10""Director\x10" "Without history,\x03\x20 sociology,\x03\x20 philosophy,\x03\x20\npolitics,\x03\x20 economics...\x03\x40 How can one\ncall themselves a \"scientist\" if they\ndon't know a THING about these\nsciences?\x01\nWe don't need students like you...\x03\x30\nwho think they're smarter than everyone\nand try to backseat their professors...\x01\nIf you're really as knowledgable as\nyou claim,\x03\x20 WHY are you studying here\nin the first place?\x01");
	SetDialogString(3217, "\x10""Ruby\x10" "...\x03\x20""Because...\x03\x30 I need the degree.\x01");
	SetDialogString(3218, "\x10""Director\x10" "You need to work hard for a degree,\x03\x20\nma'am.\x01 Not everything is going to be\nhanded over you by platter,\x03\x20 you know\nthat?\x01");
	SetDialogString(3219, "\x10""Director\x10" "I suppose that's all I have to say.\x01\nAny objections?\x03\x30 No?\x03\x30 Then you're\nexpelled.\x01 Take your documents and\ngo home and find a job...\x03\x30 or a \"better\"\nplace to study for that degree you\nso badly want.\x01 Get outta here!\x01");
	SetDialogString(3220, "\x8f\x01""The people at Sapphireton's Laboratory\npraised me for having such a\n\"brilliant\" mind...\x01 How naive on\ntheir part.\x01");
	
	SetDialogString(3221, "\x10""Father\x10" "How are you going to survive, Ruby?\x01\nWe've given you the opportunity to show\nyour true skills,\x03\x20 and...\x01 All that\nproves that you are not competent\nenough to live by yourself.\x01 You\ncouldn't even realize the basic\npromises.\x01");
	SetDialogString(3222, "\x10""Father\x10" "What's wrong,\x03\x20 cat got your tongue?\x01\nA truly brilliant mind,\x03\x20 indeed...\x03\x30\nDoesn't know how to count money.\x01");
	SetDialogString(3223, "\x10""Ruby\x10" "I can...\x01");
	SetDialogString(3224, "\x10""Father\x10" "No,\x03\x20 stop feeding me these lies.\x01\nI can clearly see the pattern:\x03\x30\nyou make a claim,\x03\x20 you fail to support\nthat claim.\x01 You are not just lying\nto me,\x03\x20 you are lying to YOURSELF first\nand foremost.\x01 You had a BRILLIANT\ncareer opportunity,\x03\x20 but too bad,\x03\x20 your\nlittle narcissistic attitude led you to\ngetting expelled from an expensive\nschool...\x01");
	SetDialogString(3225, "\x10""Father\x10" "Don't mistake this for an insult.\x01\nA stranger in the streets would've\nbroken your arm at best after your\nshenanigans.\x01 Now the question is if\nyou will be alive after the ROSE...\x01\nIf we couldn't raise the traits that\nmake you a honest person,\x03\x20 then the\nROSE definitely will weed out your\ndirty self.\x01");
	SetDialogString(3226, "\x10""Ruby\x10" "I will handle it just fine.\x01");
	SetDialogString(3227, "\x10""Father\x10" "Will you?\x01 If you say so...\x03\x30\nI am just mad that the so-called\n\"brilliant mind\" is turning out to be a\nfraud.\x01");
	SetDialogString(3228, "\x10""Father\x10" "This is the girl I and mom have\nraised ourselves...\x01 Guess I'll know\nbetter next time not to trust\nand give a son or daughter even a\nlittle bit of luxurious freedom...\x01");
	SetDialogString(3229, "\x10""Father\x10" "I'm not yelling or swearing at you,\x03\x20\nbut...\x01 How can a scientist not be\nable to recite the whole periodic\ntable by heart?\x01 It's embarassing,\x03\x20\nto be honest.\x01");
	SetDialogString(3230, "\x8f\x01""Sometimes I wish I never made such\nblatantly simple mistakes...\x01 They would\nkeep haunting me like real nightmares.\x01");
	
	SetDialogString(3231, "\x8f\x01""Requires 3 gems of trauma.\x01");
	SetDialogString(3232, "\x8f\x01""It is time to face the Tree of Evil.\x01\nIt may be tough,\x03\x20 but the deed must\nbe done.\x01");
	
	SetDialogString(3233, "\x10""Rubin\x10" "Looks like it's time to suppress the\nTree of Evil yet again.\x01 But it seems\nthat your newfound powers will give you\nthe ability to destroy that tree\nforever.\x01");
	SetDialogString(3234, "\x10""Rubin\x10" "The final Ancient Gem, Ruby of Stars,\nmust have been responsible for the\ninvigoration of your superpowers...\x03\x30\nand Lulu's,\x03\x20 I guess.\x01\nWe must be very close to solving the\nmystery,\x03\x20 nothing shall stand in our\nway now.\x01");
	SetDialogString(3235, "\x8f\x01""So this is the young Ruby.\x01 It has been\na while,\x03\x20 hasn't it?\x01");
	SetDialogString(3236, "\x8f\x01""It is time to obliterate the Tree of\nEvil.\x01 Its influence will never see the\nday of light again.\x01");
	
	
	
	SetDialogString(4000, "\x80\x01 uses \x80\x02!\x02");
	SetDialogString(4001, "You won!\nYou got \x80\x03 EXP and $\x80\x04.\x01\x80\x06\x02");
	SetDialogString(4002, "\n\x80\x05\x02");
	SetDialogString(4003, "You lost...\x01");
	SetDialogString(4004, "You got the \x80\x07.\x01");
	SetDialogString(4005, "You found the \x80\x07,\nbut you are carrying too many goods.\x01");
	SetDialogString(4006, "\x80\x01 counters!\x02");
	SetDialogString(4007, "\x80\x01 was fatally injured...\x02");
	SetDialogString(4008, "Ruby ran away!\x02");
	SetDialogString(4009, "\x80\x01 uses \x80\x02!\x03\x40\n...but MP is too low!\x03\x60");
	
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
	SetDialogString(4034, "Oh, you're still alive, Ruby?\x01\nToo bad! This is the end of the\ndemo.\x01 Bye!\x01 See you in the\nnext year I guess!\x01");
	
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
	SetDialogString(4523, "Heals 30 HP. Can be used during\na battle.");
	SetDialogString(4524, "Heals 50 HP. Can be used during\na battle.");
	SetDialogString(4525, "Heals 90% of base HP and gets\nrid of tiredness.\nExpensive drink that provides a very\nefficient energy boost.");
	SetDialogString(4526, "Gain 40 Strength during a battle.");
	SetDialogString(4527, "Removes all status effects during\na battle.");
	SetDialogString(4528, "Removes Bleed, Poison and Paralysis\nduring a battle. If used outside of a\nbattle, heals 100% of base HP.");
	SetDialogString(4529, "Restores 15 MP during a battle.");
	SetDialogString(4530, "Use it against an enemy to deal\n30 damage.");
	SetDialogString(4531, "Use it against an enemy to deal\n60 damage.");
	SetDialogString(4532, "Heals 95% of base HP.\nIt's not AS GOOD as the\nadvertisements claim it to be, but\nstill not bad.");
	SetDialogString(4533, "Heals 70% of base HP and gets\nrid of tiredness.\nMultiple fruits in one fresh!");
	SetDialogString(4534, "Heals 80% of base HP.\nA tasty and healthy slice of a\npizza. Higher quality, presumably due\nto competition.");
	SetDialogString(4535, "Heals 70% of base HP.\nA well-advertised sandwich product\nfor wealthy people. Has a good combo\nof ingredients, including JAM.");
	SetDialogString(4536, "Heals 40% of base HP.\nNot very good on its own, but the\nquality is higher presumably due to\nhaving competition.");
	SetDialogString(4537, "Heals 35% of base HP.\nGood for making sandwiches. This\none is of higher quality, presumably\ndue to actual competition.");
	
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
	SetDialogString(4673, "Ruby's own toolkit that might be\nuseful later.");
	SetDialogString(4674, "A cardkey to unlock the elevator of\nWhitelight.");
	SetDialogString(4675, "Lets you access floor 3 of\nWhitelight.");
	SetDialogString(4676, "Allows you to travel to Brilliant\nMountains.");
	SetDialogString(4677, "A strange sheet found in the forest.");
	
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
	SetDialogString(5010, "Inflict 10 Bind");
	SetDialogString(5011, "Inflict 16 Feeble");
	SetDialogString(5012, "Inflict 4 Bind");
	SetDialogString(5013, "Inflict 6 Bind");
	SetDialogString(5014, "Inflict 2 Bleed");
	SetDialogString(5015, "Attacks first, restores 15\nMP");
	SetDialogString(5016, "Attacks first, inflict 8\nBurn");
	SetDialogString(5017, "");
	SetDialogString(5018, "Inflict 3 Burn");
	SetDialogString(5019, "Inflict 4 Burn");
	SetDialogString(5020, "Gain 15 Strength if blocked");
	SetDialogString(5021, "Inflict 1 Bleed");
	SetDialogString(5022, "Inflict 3 Poison");
	SetDialogString(5023, "Inflict 2 Bleed");
	SetDialogString(5024, "Inflict 20 Bind");
	SetDialogString(5025, "Guard and take 1 less damage");
	SetDialogString(5026, "Protects an ally, take 2\nless damage");
	SetDialogString(5027, "Heals an ally 10 HP");
	SetDialogString(5028, "Targets all enemies\nInflict 8 Burn");
	SetDialogString(5029, "Inflict 2 Disarm");
	SetDialogString(5030, "Gain 12 Haste");
	SetDialogString(5031, "Allies gain 4 Strength &\nHaste");
	SetDialogString(5032, "One-use\nZaps the enemy with a\nhandshake, inflict 3\nParalysis");
	SetDialogString(5033, "Inflict 4 Disarm");
	SetDialogString(5034, "Gain 12 Feeble");
	SetDialogString(5035, "Attacks first, inflict 2\nBleed");
	SetDialogString(5036, "Restores 8 MP");
	SetDialogString(5037, "");
	SetDialogString(5038, "Unblockable, inflict 4\nBleed");
	SetDialogString(5039, "Gain 15 Strength");
	SetDialogString(5040, "Inflict 3 Bleed");
	SetDialogString(5041, "Redirects all enemies'\nattacks onto self, attacks\nafter being attacked");
	SetDialogString(5042, "Targets all enemies\nInflict 4 Bleed");
	SetDialogString(5043, "Attacks first, kunai sticks\nand explodes after a turn,\ndealing 15 damage");
	SetDialogString(5044, "Gain 18 Haste");
	SetDialogString(5045, "Attacks first, undodgable,\nuses Speed instead of Attack\nfor damage");
	SetDialogString(5046, "Attacks first, inflict 6\nParalysis");
	SetDialogString(5047, "50% or less HP required");
	SetDialogString(5048, "Protects an ally, take 5\nless damage");
	SetDialogString(5049, "Inflict 1 Paralysis");
	SetDialogString(5050, "Restores 16 MP");
	SetDialogString(5051, "Attacks first");
	SetDialogString(5052, "Rocket explodes violently,\ninflict 4 Burn, undodgable");
	SetDialogString(5053, "Inflict 10 Paralysis");
	SetDialogString(5054, "1 Charge required\nUnstoppable beam of\ndestruction, undodgable,\nunblockable");
	SetDialogString(5055, "Restores 55 MP, gain 1\nCharge, cannot act next\nturn");
	SetDialogString(5056, "Inflict 3 Flower");
	SetDialogString(5057, "Heals 70 HP, gain 12 Flower");
	SetDialogString(5058, "Restores 40 MP, gain 9\nFlower");
	SetDialogString(5059, "Attacks first, +80 damage if\ntarget has Flower,\nundodgable, unblockable");
	SetDialogString(5060, "Targets all enemies\nAttacks first, +8 damage if\ntarget has Flower,\nundodgable, unblockable");
	SetDialogString(5061, "Attacks first, inflict 10\nParalysis");
	SetDialogString(5062, "Inflict 3 Feeble");
	SetDialogString(5063, "Inflict 4 Paralysis");
	SetDialogString(5064, "Inflict 7 Paralysis");
	SetDialogString(5065, "");
	SetDialogString(5066, "Inflict 4 Bind");
	SetDialogString(5067, "Gives an ally 20 Strength");
	SetDialogString(5068, "Gives an ally 10 Endurance");
	SetDialogString(5069, "Gain 20 Haste");
	SetDialogString(5070, "Targets all enemies\nAttacks first, insta-defeats\nenemies at 40 HP or less,\nundodgable, unblockable");
	SetDialogString(5071, "Attacks first, inflict 10\nChill, undodgable,\nunblockable");
	SetDialogString(5072, "Restores 20 MP");
	SetDialogString(5073, "Inflict 2 Bind");
	SetDialogString(5074, "Heals an ally 40 HP");
	SetDialogString(5075, "Attacks first");
	SetDialogString(5076, "Gain 1 Charge");
	SetDialogString(5077, "1 Charge required");
	SetDialogString(5078, "Inflict 1 Burn");
	SetDialogString(5079, "Inflict 10 Burn & Timed\nBomb");
	SetDialogString(5080, "Inflict 18 Feeble");
	SetDialogString(5081, "50% or less HP required\nTargets all enemies\nInflict 15 Timed Bomb,\nundodgable");
	SetDialogString(5082, "Removes all status effects\nfrom an ally or enemy");
	SetDialogString(5083, "Revives a defeated ally\nand heals 20 HP");
	SetDialogString(5084, "1 Charge required\nInflict 12 Paralysis");
	SetDialogString(5085, "Top priority\nProtects an ally, take 2\nless damage");
	SetDialogString(5086, "50% or less HP required\nLethal, inflict 20 Bleed,\nunblockable");
	SetDialogString(5087, "Inflict 6 Bleed");
	SetDialogString(5088, "50% or less HP required\nInflict 20 Bleed,\nunblockable");
	SetDialogString(5089, "Attacks first, inflict 9\nBleed");
	SetDialogString(5090, "Targets all enemies\nAttacks first, inflict 2\nBleed, undodgable,\nunblockable");
	SetDialogString(5091, "1 Charge required\nAttacks first, inflict 24\nFeeble");
	SetDialogString(5092, "Inflict 12 Feeble, gain\n12 Feeble");
	SetDialogString(5093, "Deals critical damage if\nunblocked");
	SetDialogString(5094, "Gain 20 Strength");
	SetDialogString(5095, "Gain 10 Endurance");
	SetDialogString(5096, "Shoot the enemy with gun");
	SetDialogString(5097, "Top priority\nProtects an ally, take 12\nless damage");
	SetDialogString(5098, "Gives an ally 60 Endurance");
	SetDialogString(5099, "Targets all enemies\nAttacks first, clears status\neffects, inflict 12 Disarm,\nundodgable, unblockable");
	SetDialogString(5100, "Requires exactly 3\nParalysis, 5 Skills and MP\ndivisible by 8\nInflict 3 Bleed, Paralysis");
	SetDialogString(5101, "Heals 20 HP if the rightmost\ndigit of user's MP is equal\nto factorial of target's\nnatural Defense");
	SetDialogString(5102, "Restores 20 MP, gain 1\nParalysis, lose 5 HP if user\ndoesn't have Unknown Badge\nbadge");
	SetDialogString(5103, "Steals 7 MP from enemies,\ngain 1 Strength for every\n2nd stolen MP starting from\n2nd MP after reaching max MP");
	SetDialogString(5104, "Inflict 12 Bleed & Poison,\ngain 20 Feeble & Bind (only\nif target didn't block via\ntiming or defensive skill)");
	SetDialogString(5105, "One-use\nExtra power equal to HP+MP\ndivided by 8 (rounded down),\nsets HP & MP to 1 & 0");
	SetDialogString(5106, "Skills cost 20 less MP next\nturn");
	SetDialogString(5107, "Skills cost 10 less MP next\n3 turns");
	SetDialogString(5108, "Restores MP equal to 75% of\ninflicted damage (rounded\ndown)");
	SetDialogString(5109, "One-use, 50% or less HP\nrequired\nBoosts ATK +15, DEF +5,\nSPD +15, heals 40 HP");
	SetDialogString(5110, "Doubles Attack until the\nend of next turn");
	SetDialogString(5111, "Dodge all dodgable attacks");
	SetDialogString(5112, "Attacks an ally, restores\n15 MP to an ally, gives 10\nStrength");
	SetDialogString(5113, "Removes 9 HP from self");
	SetDialogString(5114, "Inflict 30 Strength");
	SetDialogString(5115, "");
	SetDialogString(5116, "Gives an ally 80 Strength");
	SetDialogString(5117, "Heals an ally 50 HP, but\ninflict 12 Poison");
	SetDialogString(5118, "[-=-=-= LUXURY SKILL =-=-=-]\n[     Inflict 1 Charge     ]\n[                          ]\n[-=-=-=-=-=-=--=-=-=-=-=-=-]");
	SetDialogString(5119, "");
	SetDialogString(5120, "Guard and take 12 less\ndamage, gain 8 Endurance");
	SetDialogString(5121, "Protects an ally, take 2\nless damage, deflects MP\nwith power 3");
	SetDialogString(5122, "Inflict 9 Disarm");
	SetDialogString(5123, "Gives an ally 80 Absorption");
	SetDialogString(5124, "Ignore second attack if the\nfirst doesn't deal 24+\ndamage, inflict 15 Feeble on\nsecond hit");
	SetDialogString(5125, "First 15 attacks deal max 1\ndamage & increase final\npower by 2, final attack is\nundodgable & unblockable");
	SetDialogString(5126, "Redirects all enemies'\nattacks onto self, take 4\nless damage, deflects MP\nwith power 6");
	SetDialogString(5127, "Deal max 10 damage, inflict\n1 Disarm");
	SetDialogString(5128, "Prevents enemy from blocking\nnext turn on hit");
	SetDialogString(5129, "Attacks first, inflict 1\nBurn, undodgable,\nunblockable");
	SetDialogString(5130, "Inflict 20 Feeble");
	SetDialogString(5131, "Inflict 10 Disarm");
	SetDialogString(5132, "Removes 6 HP from self,\ninflict 2 Bind");
	SetDialogString(5133, "1 Charge required\nAttacks first, prevents\nenemy from blocking next\nturn, undodg., unblock.");
	SetDialogString(5134, "Restores 12 MP, lose 3 HP,\ngain 8 Strength");
	SetDialogString(5135, "Inflict 1 Bleed, steal 2 MP\nfrom target on damage");
	SetDialogString(5136, "Inflict 2 Feeble, +15 damage\nif target has 6 or less MP");
	SetDialogString(5137, "Attacks first, inflict 4\nPoison");
	SetDialogString(5138, "Inflict 3 Chill");
	SetDialogString(5139, "Inflict 3 Chill");
	SetDialogString(5140, "Top priority\nProtects an ally, take 2\nless damage, attacks after\nbeing attacked");
	SetDialogString(5141, "Cannot act next turn");
	SetDialogString(5142, "Reduces MP cost of all\nskills by 2 (up to 10)");
	SetDialogString(5143, "Final hit steals Paralysis\nfrom target");
	SetDialogString(5144, "It does what you think it\ndoes. It destroys noobs.\nAttacks first");
	SetDialogString(5145, "Attacks first, undodgable,\nuses Speed instead of Attack\nfor damage");
	SetDialogString(5146, "Targets all enemies\nAttacks first, deal max 9\ndamage, inflict 6 Paralysis\nundodgable, unblockable");
	SetDialogString(5147, "Inflict 7 Burn, ignore other\nhits if first deals no\ndamage, last hit targets\nall enemies");
	SetDialogString(5148, "Targets all enemies\nAttacks first, inflict 36\nBurn, undodgable,\nunblockable");
	SetDialogString(5149, "Attacks first, inflict 26\nChill, undodgable,\nunblockable");
	SetDialogString(5150, "Inflict 70 Bind, undodgable");
	SetDialogString(5151, "Targets all enemies\nInflict 6 Feeble");
	SetDialogString(5152, "Restores 20 MP, skills cost\n10 less MP next turn");
	SetDialogString(5153, "Targets all enemies\nTop priority, deal max 47\ndamage, inflict 35 Feeble\nthis turn, undodg., unblock.");
	SetDialogString(5154, "Insta-defeats target if its\nHP is 140 or less");
	SetDialogString(5155, "Heals all allies 40 HP");
	SetDialogString(5156, "Ally restores 12 MP");
	SetDialogString(5157, "Ally restores 30 MP");
	SetDialogString(5158, "Target loses 20 MP");
	SetDialogString(5159, "Targets all enemies\nAttacks first, inflict 29\nBleed, undodgable,\nunblockable, lethal");
	SetDialogString(5160, "Gain 2 Charge");
	SetDialogString(5161, "Gain 3 Charge");
	SetDialogString(5162, "3 Charge required\nTargets all enemies\nTop priority, inflict 11\nParalysis, gain 18 Disarm");
	SetDialogString(5163, "Restores 60 MP, lose 15 HP,\ngain 10 Disarm");
	SetDialogString(5164, "Attacks first, inflict 34\nBurn");
	SetDialogString(5165, "Heals an ally 300 HP");
	SetDialogString(5166, "Restores 120 MP");
	
	SetDialogString(5168, "Attacks first, ignores\ndefense");
	SetDialogString(5169, "Speeds up on every hit,\ncancelled upon dealing no\ndamage or getting deflected");
	SetDialogString(5170, "Attacks first, ignores\ndefense, gain 20 Haste");
	SetDialogString(5171, "Top priority, ignores\ndefense, cancels enemy's\nskill if enemy targets user\nand is slower by 20+ points");
	SetDialogString(5172, "One-use\nTop priority, ignores\ndefense");
	SetDialogString(5173, "Ignore second attack if the\nfirst doesn't deal 16+\ndamage, inflict 66 Bleed,\nsecond hit is lethal");
	SetDialogString(5174, "One-use\nCory's ultimate gauntlet of\nabsolute devastation.\nTop priority, undodgable");
	SetDialogString(5175, "Top priority, redirects all\nenemies' attacks onto self,\nattacks after being attacked");
	SetDialogString(5176, "Inflict 25 Bleed, gain 50\nStrength and Haste");
	SetDialogString(5177, "Attacks first, inflict 7\nParalysis, undodgable, uses\nSpeed instead of Attack for\ndamage");
	SetDialogString(5178, "Inflict 40 Poison, target\nloses 50 MP, undodgable,\nunblockable");
	SetDialogString(5179, "Top priority, take 45 less\ndamage, attacks after being\nattacked, inflict 153 Feeble\nand 51 Disarm to all enemies");
	SetDialogString(5180, "Heals 2667 HP, gain 3\nCharge, skills cost 104 less\nMP next turn");
	SetDialogString(5181, "Targets all enemies\nAttacks first, inflict 151\nBleed and 55 Poison, drain\n100 MP, undodg., unblock.");
	SetDialogString(5182, "9 Charge required\nTargets all enemies\nTop priority, Rubin's\nultimate skill");
	SetDialogString(5183, "Targets all enemies\nAttacks first, inflict 184\nBurn, undodgable,\nunblockable");
	SetDialogString(5184, "Targets all enemies\nAttacks first, inflict 13\nParalysis");
	SetDialogString(5185, "Attacks first, undodgable,\nunblockable");
	SetDialogString(5186, "One-use\nTop priority, target loses\nCharge and 999 MP, undodg.,\nunblock.");
	SetDialogString(5187, "Restores 505 MP, lose 505 HP,\ngain 150 Strength and 50\nHaste");
	SetDialogString(5188, "Reduces MP cost of all\nskills by 10 (up to 50)");
	SetDialogString(5189, "Heals all allies 300 HP");
	SetDialogString(5190, "Gives all allies 150\nStrength, 50 Endurance, 80\nHaste");
	SetDialogString(5191, "??????");
	
	SetDialogString(5193, "Prevents enemy from blocking\nnext turn, inflicts Immobile\nif enemy has 50% or less MP,\ninflict 25 Disarm, undodg.");
	SetDialogString(5194, "Ally restores 150 MP");
	SetDialogString(5195, "1 Charge required\nExtra power equal to MP\ndivided by 8 (rounded down),\nundodgable");
	SetDialogString(5196, "Prevents enemy from\nrecovering HP next turn");
	SetDialogString(5197, "One-use\nAll allies restore 500 MP");
	SetDialogString(5198, "Target loses 160 MP");
	
	SetDialogString(5199, "STORAGE OR USAGE OF THIS\nITEM IS PROHIBITED AND WILL\nBE PROSECUTED BY THE LAW\nOF GEMIA.");
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
	SetDialogString(5211, "Boosts ATK +24, DEF -4,\nSPD +5, heals 303 HP");
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
				Audio_PlaySoundInterrupt(dialogSystem.voiceSoundId);
				dialogSystem.voiceCooldown = 2;
			}
			if (!PlayerButtonPressed(PLAYER_BUTTON_X) && (!PlayerButtonHeld(PLAYER_BUTTON_C) || !game.settings.textSkip)) break;
		}
		else if (c == '\n') {
			dialogSystem.text[dialogSystem.textLength++] = c;
			
			int newLines = 0;
			int firstNewLine = -1;
			for (int i = 0; i < dialogSystem.textLength; i++) {
				if (dialogSystem.text[i] == 0x8f) {
					i++;
					continue;
				}
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
			else if (ca == 0x0a) {
				int id = Dialog_GetChar() - 1;
				int c = 0;
				for (int i = 0; ; i++) {
					if (dialogRandomWordCollection[eventSystem.vars[id].i][i] == 0) {
						game.textBuffer[i] = 0;
						break;
					}
					game.textBuffer[i] = dialogRandomWordCollection[eventSystem.vars[id].i][i] - 0x20;
					c++;
				}
				for (int i = dialogSystem.textLength - 1; i >= 0 && dialogSystem.text[i] != '\n'; i--) {
					c++;
				}
				if (c >= 35) {
					for (int i = dialogSystem.textLength - 1; i >= 0 && dialogSystem.text[i] != '\n'; i--) {
						if (dialogSystem.text[i] == ' ') {
							dialogSystem.text[i] = '\n';
							
							int newLines = 0;
							int firstNewLine = -1;
							for (int i = 0; i < dialogSystem.textLength; i++) {
								if (dialogSystem.text[i] == 0x8f) {
									i++;
									continue;
								}
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
							break;
						}
					}
				}
				Dialog_AppendString(game.textBuffer);
			}
		}
	}
}
