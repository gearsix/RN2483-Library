/*------------------------------------------
|	Project:		Challenge1-UFCFVK-15-2 
|	File:			MicroIMG.h
|	Authors:		Alexander Collins
|	Description:	A set of extern MicroBitImage s and animations for a 5x5 BBC:MicroBit LED display.
|	Date:			Jan-Feb, 2018
|-----------------------------------------*/
#ifndef _MicroIMG_
#define _MicroIMG_
//========
// MACROS
//========
// includes
#include "MicroBit.h"

//=========
// GLOBALS
//=========
// images
/*	- - - - -
	- - - - -
	- - - - -
	- - - - -
	- - - - -	*/
extern MicroBitImage MicroIMG_blank;

/*	- 1 1 - -
	1 - - 1 -
	1 1 1 1 -
	1 - - 1 -
	1 - - 1 -	*/
extern MicroBitImage MicroIMG_A;

/*	1 1 1 - -
	1 - - 1 -
	1 1 1 - -
	1 - - 1 -
	1 1 1 - -	*/
extern MicroBitImage MicroIMG_B;

/*	- - 1 - -
	- 1 1 1 -
	- - 1 - -
	- - 1 - -
	- - 1 - -	*/
extern MicroBitImage MicroIMG_uparrow;

/*	- - 1 - -
	- - 1 - -
	- - 1 - -
	- 1 1 1 -
	- - 1 - -	*/
extern MicroBitImage MicroIMG_downarrow;

/*	- - - - -
	- - - 1 -
	1 1 1 1 1
	- - - 1 -
	- - - - -	*/
extern MicroBitImage MicroIMG_rightarrow;

/*	- - - - -
	- 1 - - -
	1 1 1 1 1
	- 1 - - -
	- - - - -	*/
extern MicroBitImage MicroIMG_leftarrow;

/*
	1 - - - -
	- 1 - - -
	- - 1 - -
	- - - 1 -
	- - - - 1	*/
extern MicroBitImage MicroIMG_rotation0;

/*	- - 1 - -
	- - 1 - -
	- - 1 - -
	- - 1 - -
	- - 1 - -	*/
extern MicroBitImage MicroIMG_rotation1;

/*	- - - - 1
	- - - 1 -
	- - 1 - -
	- 1 - - -
	1 - - - -	*/
extern MicroBitImage MicroIMG_rotation2;

/*	- - - - -
	- - - - -
	1 1 1 1 1
	- - - - -
	- - - - -	*/
extern MicroBitImage MicroIMG_rotation3;

/*	1 1 1 1 1
	1 - - - 1
	1 - - - 1
	1 - - - 1
	1 1 1 1 1	*/
extern MicroBitImage MicroIMG_square0;

/*	- - - - -
	- 1 1 1 -
	- 1 - 1 -
	- 1 1 1 -
	- - - - -	*/
extern MicroBitImage MicroIMG_square1;

/*	- - - - -
	- - - - -
	- - 1 - -
	- - - - -
	- - - - -	*/
extern MicroBitImage MicroIMG_centerdot;

/*	- - - - -
	- - - - 1
	- - - 1 -
	1 - 1 - -
	- 1 - - -	*/
extern MicroBitImage MicroIMG_tick;

/*	1 - - - 1
	- 1 - 1 -
	- - 1 - -
	- 1 - 1 -
	1 - - - 1	*/
extern MicroBitImage MicroIMG_cross;

//============
// PROTOTYPES
//============
// animations
/* flashes two images 'flashes' times for 'speed' ms	*/
void MicroIMG_animation_flash(MicroBit *uBit, MicroBitImage img1, MicroBitImage img2, int flashes, unsigned long speed);

/* shows a square getting bigger/smaller from center
if ('reverse' == false)...
1.	1 1 1 1 1	2.	- - - - -	3.	- - - - -
	1 - - - 1		- 1 1 1 -		- - - - -
	1 - - - 1		- 1 - 1 -		- - 1 - -
	1 - - - 1		- 1 1 1 -		- - - - -
	1 1 1 1 1		- - - - -		- - - - -
with 'speed' ms between frames	*/
void MicroIMG_animation_square(MicroBit *uBit, int loops, unsigned long speed, bool reverse);

/* shows a rotating straight line
if ('reverse' == false)...
1.	1 - - - -	2.	- - 1 - -	3.	- - - - 1	4.	- - - - -
	- 1 - - -		- - 1 - -		- - - 1 -		- - - - -
	- - 1 - -		- - 1 - -		- - 1 - -		1 1 1 1 1
	- - - 1 -		- - 1 - -		- 1 - - -		- - - - -
	- - - - 1		- - 1 - -		1 - - - -		- - - - -
with 'speed' ms between frames	*/
void MicroIMG_animation_rotation(MicroBit *uBit, int rotations, unsigned long speed, bool reverse);

#endif	//IMG

