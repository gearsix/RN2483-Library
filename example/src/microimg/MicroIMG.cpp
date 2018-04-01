/*------------------------------------------
|	Project:		Challenge1-UFCFVK-15-2 
|	File:			MicroIMG.h
|	Authors:		Alexander Collins
|	Description:	A set of MicroBitImages and animations for a 5x5 BBC:MicroBit LED display.
|	Date:			Jan-Feb, 2018
|-----------------------------------------*/
//========
// MACROS
//========
// includes
#include "MicroIMG.h"

//=========
// GLOBALS
//=========
// images
MicroBitImage MicroIMG_blank = MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");
MicroBitImage MicroIMG_A = MicroBitImage("0,1,1,0,0\n1,0,0,1,0\n1,1,1,1,0\n1,0,0,1,0\n1,0,0,1,0\n");
MicroBitImage MicroIMG_B = MicroBitImage("1,1,1,0,0\n1,0,0,1,0\n1,1,1,0,0\n1,0,0,1,0\n1,1,1,0,0\n");
MicroBitImage MicroIMG_uparrow = MicroBitImage("0,0,1,0,0\n0,1,1,1,0\n0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n");
MicroBitImage MicroIMG_downarrow = MicroBitImage("0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n0,1,1,1,0,\n0,0,1,0,0\n");
MicroBitImage MicroIMG_rightarrow = MicroBitImage("0,0,0,0,0\n0,0,0,1,0\n1,1,1,1,1\n0,0,0,1,0\n0,0,0,0,0\n");
MicroBitImage MicroIMG_leftarrow = MicroBitImage("0,0,0,0,0\n0,1,0,0,0\n1,1,1,1,1\n0,1,0,0,0\n0,0,0,0,0\n");
MicroBitImage MicroIMG_rotation0 = MicroBitImage("1,0,0,0,0\n0,1,0,0,0\n0,0,1,0,0\n0,0,0,1,0\n0,0,0,0,1\n");
MicroBitImage MicroIMG_rotation1 = MicroBitImage("0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n");
MicroBitImage MicroIMG_rotation2 = MicroBitImage("0,0,0,0,1\n0,0,0,1,0\n0,0,1,0,0\n0,1,0,0,0\n1,0,0,0,0\n");
MicroBitImage MicroIMG_rotation3 = MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n1,1,1,1,1\n0,0,0,0,0\n0,0,0,0,0\n");
MicroBitImage MicroIMG_square0 = MicroBitImage("1,1,1,1,1\n1,0,0,0,1\n1,0,0,0,1\n1,0,0,0,1\n1,1,1,1,1\n");
MicroBitImage MicroIMG_square1 = MicroBitImage("0,0,0,0,0\n0,1,1,1,0\n0,1,0,1,0\n0,1,1,1,0\n0,0,0,0,0\n");
MicroBitImage MicroIMG_centerdot = MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,1,0,0\n0,0,0,0,0\n0,0,0,0,0\n");
MicroBitImage MicroIMG_tick = MicroBitImage("0,0,0,0,0\n0,0,0,0,1\n0,0,0,1,0\n1,0,1,0,0\n0,1,0,0,0\n");
MicroBitImage MicroIMG_cross = MicroBitImage("1,0,0,0,1\n0,1,0,1,0\n0,0,1,0,0\n0,1,0,1,0\n1,0,0,0,1\n");

//============
// PROTOTYPES
//============
// animations
void MicroIMG_animation_flash(MicroBit *uBit, MicroBitImage img1, MicroBitImage img2, int flashes, unsigned long speed)
{
	if (!speed)
		speed = 100;

	for (int i = 0; i < flashes; i++)
	{
		uBit->display.print(img1);
		uBit->sleep(speed);
		uBit->display.print(img2);
		uBit->sleep(speed);
	}

	uBit->display.clear();
}
void MicroIMG_animation_square(MicroBit *uBit, int loops, unsigned long speed, bool reverse)
{
	if (!speed)
		speed = 200;

	if (reverse == true)
	{
		for (int i = 0; i < loops; i++)
		{
			uBit->display.print(MicroIMG_centerdot);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_square1);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_square0);
			uBit->sleep(speed);
		}
	}
	else
	{
		for (int i = 0; i < loops; i++)
		{
			uBit->display.print(MicroIMG_square0);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_square1);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_centerdot);
			uBit->sleep(speed);
		}
	}

	uBit->display.clear();
}
void MicroIMG_animation_rotation(MicroBit *uBit, int rotations, unsigned long speed, bool reverse)
{
	if (!speed)
		speed = 200;

	if (reverse == true)
	{
		for (int i = 0; i < rotations; i++)
		{
			uBit->display.print(MicroIMG_rotation3);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_rotation2);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_rotation1);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_rotation0);
			uBit->sleep(speed);
		}
	}
	else
	{
		for (int i = 0; i < rotations; i++)
		{
			uBit->display.print(MicroIMG_rotation0);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_rotation1);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_rotation2);
			uBit->sleep(speed);
			uBit->display.print(MicroIMG_rotation3);
			uBit->sleep(speed);
		}
	}

	uBit->display.clear();
}


