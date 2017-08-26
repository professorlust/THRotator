﻿// (c) 2017 massanoori

#include "stdafx.h"
#include "THRotatorImGui.h"

#ifdef TOUHOU_ON_D3D8
#include "imgui_impl_dx8.h"
#define ImGui_IMPLFUNC(suffix) ImGui_ImplDX8_ ## suffix 
#else
#include <imgui_impl_dx9.h>
#define ImGui_IMPLFUNC(suffix) ImGui_ImplDX9_ ## suffix 
#endif

namespace
{

// Successive offsets from codepoint 0x4E00 like the way imgui_draw.cpp does.
// Generated from kanji from JMDict plus the following:
//   佶俛兪凊匱厦厲囹圀圄垠堯娥嫖嫦孚宕屨嶇徇很徙愒
//   戢挈摶擺敝旙桀椛殢汨洽涇淒渭璋睚矣砺礪秉翊翦聱
//   脯舜蔌裎裼褫襄諏跎跖蹐軼輭郢鄂醯鈇闈驤驪鷁
static const short offsetsFrom0x4E00[] =
{
	-1,0,1,3,0,0,0,0,1,0,1,0,2,1,1,0,4,2,4,3,2,4,5,0,1,0,6,0,0,2,2,1,0,0,6,0,0,0,3,0,0,17,1,10,1,1,3,1,0,1,0,1,2,0,1,0,2,0,1,0,1,2,0,1,
	0,0,1,2,0,0,0,4,6,0,4,0,2,1,0,2,0,1,1,4,0,0,0,0,0,3,0,0,3,0,0,7,0,1,1,3,4,5,7,0,2,0,0,0,0,8,1,0,17,0,3,1,1,1,1,0,5,2,0,5,0,0,0,0,
	1,1,1,1,0,0,0,0,0,10,5,0,2,1,0,4,0,2,3,2,1,2,1,1,1,6,2,1,2,0,9,1,0,0,5,0,8,2,0,0,5,3,0,0,0,5,0,1,0,1,1,0,0,1,0,0,8,0,3,1,2,1,10,0,
	2,1,1,4,1,1,1,0,0,1,2,1,1,0,0,0,1,0,0,0,1,8,2,9,3,0,0,5,3,1,0,3,1,8,6,5,1,0,0,1,4,2,4,7,3,6,0,0,17,0,4,0,0,0,1,6,3,2,4,2,1,1,3,4,
	8,1,1,5,0,6,3,1,4,0,0,1,13,1,0,2,1,3,0,1,8,7,4,2,0,0,2,0,0,1,0,0,0,0,0,0,1,0,0,0,1,3,5,1,5,2,2,1,0,0,0,3,3,0,0,0,3,3,1,2,0,2,0,1,
	0,1,1,0,2,0,0,1,6,1,1,0,0,1,1,1,3,0,0,1,0,0,0,5,6,1,2,0,0,0,0,13,0,0,2,0,4,0,1,0,2,2,0,4,1,0,0,2,0,1,2,2,0,0,1,3,2,0,3,0,5,6,0,3,
	0,3,1,2,2,0,0,0,0,0,7,0,2,2,0,0,0,6,0,0,0,3,1,5,0,0,4,4,0,1,0,0,0,7,1,3,3,0,4,4,0,7,3,0,2,5,0,0,5,2,4,4,2,1,1,1,1,8,2,2,0,3,0,0,
	2,1,1,0,10,7,3,0,1,0,2,0,1,4,1,0,4,0,0,1,0,1,3,0,1,6,6,6,0,0,0,3,0,0,1,1,0,0,0,0,0,2,3,0,0,0,2,0,1,1,3,5,2,4,0,0,0,1,0,0,2,6,2,1,
	17,1,1,4,0,4,0,1,0,3,4,0,0,6,6,0,4,0,0,0,0,0,0,5,1,0,1,1,3,1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,2,0,0,1,6,1,0,3,0,0,0,0,0,0,0,0,0,9,1,
	0,0,0,5,4,0,0,0,7,1,0,1,0,0,0,3,3,1,0,0,2,0,2,13,8,1,6,1,1,0,0,3,0,0,2,3,1,5,1,3,3,5,7,0,2,2,0,5,0,4,4,2,0,2,2,0,0,23,3,2,0,3,0,3,
	7,9,1,0,6,1,5,24,1,1,4,5,1,3,1,8,3,2,5,1,4,23,0,1,1,2,0,2,1,0,0,12,0,0,1,0,0,0,7,0,0,0,0,0,1,1,5,13,0,1,1,10,5,1,2,3,0,4,15,3,0,7,1,0,
	10,1,0,0,2,13,5,1,0,1,1,1,8,0,9,1,4,7,8,3,1,0,0,2,4,3,1,5,5,0,2,4,4,4,6,1,2,6,1,13,3,0,0,0,4,0,0,6,1,3,2,0,2,1,2,10,1,1,0,5,0,2,2,2,
	0,6,3,2,0,1,0,1,6,7,0,4,2,15,1,2,1,2,3,0,0,0,15,2,1,2,0,12,10,8,7,8,3,1,0,0,30,2,4,2,3,0,0,7,2,0,19,0,1,1,0,1,3,1,2,0,3,0,9,3,3,3,2,5,
	4,0,0,2,0,4,5,0,8,1,4,0,1,2,2,3,2,2,4,1,9,3,4,4,15,3,4,0,1,8,0,9,6,0,2,2,3,1,2,1,1,2,3,6,2,11,0,1,1,0,0,4,1,0,0,0,0,11,0,4,4,0,0,2,
	0,1,5,2,1,1,0,0,1,0,2,5,6,5,2,0,0,4,0,0,0,2,0,1,2,5,1,2,1,0,1,3,4,0,3,4,3,0,0,0,5,2,5,2,2,9,1,2,3,12,1,2,7,2,1,4,0,1,0,4,2,8,0,0,
	2,0,15,3,1,1,13,6,3,2,0,4,3,5,5,0,5,3,0,4,2,16,7,3,3,1,18,18,7,0,23,8,0,0,2,0,6,1,0,9,0,9,1,2,2,11,19,1,0,21,2,4,1,3,1,3,7,1,0,1,12,0,2,0,
	1,0,1,1,0,1,3,0,1,2,1,4,2,1,2,1,2,2,4,1,0,0,1,0,0,1,5,1,0,0,0,0,0,0,1,2,0,0,0,0,7,1,2,0,0,0,1,0,5,2,0,0,0,0,0,4,3,1,0,0,6,1,0,0,
	1,3,0,0,0,0,1,2,4,1,0,1,1,3,0,1,0,1,1,0,0,0,0,0,2,0,1,4,3,5,1,1,3,4,3,6,0,0,0,0,0,0,0,0,0,3,0,1,1,0,1,0,0,1,1,1,8,1,0,0,1,0,2,3,
	2,1,7,18,3,16,6,0,2,6,4,32,6,0,6,4,1,0,5,4,1,9,6,7,0,3,13,34,3,24,2,2,20,2,3,34,11,1,0,11,1,0,0,5,2,4,1,0,2,1,1,0,0,0,2,2,2,0,0,0,0,1,3,1,
	0,3,0,2,5,4,4,2,0,0,1,7,5,1,1,0,2,2,0,0,4,2,3,0,1,4,7,0,9,1,0,0,14,0,0,1,1,0,0,0,0,0,0,0,1,1,0,2,2,4,5,0,0,2,1,3,5,0,3,1,7,0,0,0,
	8,0,0,4,0,0,4,0,2,6,4,0,1,0,4,0,2,7,1,0,2,0,0,2,1,2,4,0,0,0,2,0,0,1,0,0,0,0,0,2,3,5,0,0,1,3,1,1,3,1,4,0,0,11,1,1,2,1,3,1,3,3,0,3,
	2,1,0,0,2,0,1,3,1,2,2,0,0,2,0,1,0,0,0,0,0,3,1,0,3,0,0,2,1,2,6,0,0,2,0,4,0,4,3,5,0,0,3,2,0,8,0,0,0,2,0,2,10,4,4,2,2,1,1,15,2,3,2,2,
	0,2,0,3,1,0,0,0,0,3,1,8,8,7,1,2,1,2,3,0,4,2,0,0,0,2,0,0,0,0,0,1,0,4,14,4,1,0,0,4,1,1,3,0,3,0,2,2,0,1,0,7,1,1,1,3,0,7,1,9,6,1,1,2,
	1,1,3,0,7,0,1,2,0,0,0,1,5,6,0,3,0,0,2,2,4,0,3,7,12,9,3,1,2,0,1,0,0,1,6,3,0,4,0,1,0,1,1,0,2,2,1,2,0,1,0,6,3,7,3,1,0,2,1,3,9,2,1,1,
	0,1,3,3,3,3,4,3,0,0,0,5,18,2,11,3,0,0,1,1,1,1,7,1,1,0,0,1,0,0,3,3,0,2,0,2,3,3,3,0,0,1,1,3,2,3,0,0,5,0,0,1,1,5,1,2,2,2,1,2,4,5,2,4,
	2,2,2,0,2,0,4,0,6,0,0,0,0,1,0,2,0,1,12,5,3,3,2,0,7,0,0,0,0,2,0,1,0,1,0,3,0,0,1,0,0,2,0,10,0,0,2,1,1,0,0,4,1,0,1,0,4,0,0,2,4,6,0,5,
	8,2,3,5,4,2,0,0,9,2,0,1,0,4,1,4,8,1,0,0,4,3,4,2,0,7,4,0,2,2,2,3,1,2,3,0,0,0,0,1,1,0,0,0,1,5,1,6,7,0,1,2,5,0,1,3,3,0,5,1,10,5,1,3,
	18,1,4,2,10,3,1,3,0,12,3,3,14,6,14,1,5,6,1,0,0,8,4,9,0,6,3,5,0,3,1,1,0,1,1,6,1,0,4,0,2,7,4,5,1,5,0,0,0,0,1,5,2,1,0,7,2,0,1,23,10,5,0,0,
	0,2,2,1,0,1,1,1,2,0,5,7,1,1,5,1,3,4,0,2,5,3,1,1,0,1,0,9,0,3,1,4,1,0,5,1,1,0,2,1,2,0,1,3,0,0,1,0,6,1,2,0,3,3,0,4,0,2,2,4,1,1,4,1,
	2,0,0,0,0,2,0,3,8,7,3,0,4,1,0,3,0,10,0,4,1,0,4,1,4,0,5,0,5,0,7,3,2,10,6,1,0,0,0,4,0,0,3,1,3,6,5,0,0,7,4,0,5,4,3,4,2,5,4,13,1,12,2,0,
	1,0,2,8,6,1,0,0,3,0,2,0,0,0,0,2,4,0,1,1,6,0,1,3,1,1,6,0,0,1,0,0,0,0,2,2,1,3,2,8,2,4,0,0,0,1,2,2,2,1,0,0,0,0,2,4,2,0,0,1,1,1,1,4,
	1,0,7,1,1,4,4,1,0,1,1,0,2,0,0,12,3,2,0,0,0,1,7,0,5,4,0,0,1,0,3,1,2,0,3,6,2,1,0,1,0,0,0,0,3,1,2,0,2,0,0,14,2,0,6,2,7,0,7,1,3,0,2,0,
	2,0,0,0,2,1,5,1,0,1,0,4,1,0,0,1,7,3,6,1,1,0,7,1,0,0,1,9,3,0,2,0,2,1,1,0,1,0,3,0,4,1,0,0,0,0,1,0,3,0,8,3,0,0,0,1,4,2,1,0,1,4,0,2,
	3,6,3,6,0,5,4,2,2,1,0,0,2,6,0,0,0,6,4,1,5,3,1,2,3,1,2,7,8,0,0,4,2,0,1,0,0,0,0,5,0,1,0,0,2,0,1,1,0,3,0,0,1,1,7,3,2,2,0,5,0,3,6,0,
	5,2,0,1,6,2,2,1,3,3,0,0,2,2,4,0,13,0,4,4,2,5,1,1,2,2,5,3,2,0,3,1,3,1,1,1,5,0,0,9,2,0,0,2,6,0,1,0,0,1,12,0,5,1,0,28,0,3,4,3,0,1,6,4,
	0,0,4,7,0,1,4,4,2,6,0,13,1,6,0,2,0,7,0,1,15,0,8,0,9,2,3,6,2,0,1,3,10,4,1,0,2,0,8,1,2,1,4,0,10,2,0,0,1,2,0,4,3,0,3,0,1,3,3,0,1,2,0,0,
	10,11,7,2,1,1,0,0,0,0,1,2,0,0,2,0,4,5,1,0,3,1,2,0,2,3,11,0,1,0,3,20,6,0,0,1,3,11,16,0,1,0,5,1,0,0,11,1,6,2,2,0,0,0,7,1,5,1,7,2,3,1,4,3,
	3,1,0,2,2,1,5,0,8,2,2,1,4,0,1,0,0,0,0,1,2,4,0,1,8,5,1,3,0,0,1,2,1,0,4,2,23,6,4,3,2,0,5,3,0,6,0,2,2,2,1,0,2,2,0,19,0,1,6,2,2,0,1,1,
	5,2,0,12,1,0,3,1,5,0,3,1,0,18,2,2,2,3,3,5,4,5,0,5,0,7,4,3,0,0,4,1,1,1,1,0,0,9,1,0,0,0,0,7,1,3,0,0,3,0,0,1,1,0,2,1,0,0,1,8,1,3,4,6,
	2,8,1,2,11,6,0,2,11,0,0,1,9,3,5,1,3,0,1,2,7,4,2,3,0,2,2,4,1,0,5,0,4,1,0,8,0,19,1,2,0,5,0,1,0,3,2,5,1,1,0,0,10,1,0,7,0,4,0,5,6,5,11,2,
	3,2,0,2,4,8,0,1,9,6,2,1,7,8,12,5,6,1,5,6,0,1,20,2,3,0,0,2,6,3,3,2,3,3,7,2,5,1,3,2,1,0,1,0,0,6,0,4,3,13,13,4,6,18,0,2,0,7,3,0,11,0,3,3,
	6,18,0,0,0,7,0,0,0,0,12,6,9,3,1,17,7,3,11,10,4,0,1,4,4,7,1,5,5,9,2,2,1,6,0,2,6,1,1,0,1,1,4,14,6,2,2,4,4,0,3,5,8,3,4,1,10,4,4,5,1,1,1,0,
	1,8,4,0,0,4,0,7,3,1,0,2,6,20,12,1,1,3,1,2,0,3,0,0,0,0,0,0,5,0,0,3,5,3,1,0,1,0,0,1,1,0,4,1,8,1,4,3,0,1,1,4,10,13,1,9,2,0,5,11,1,1,7,1,
	1,4,1,1,5,0,6,2,0,5,3,0,3,0,12,11,0,3,0,2,5,2,0,0,0,2,5,1,7,0,4,0,9,7,11,2,1,1,5,0,0,5,1,9,2,1,1,10,18,8,0,7,4,1,5,1,2,0,15,1,4,4,2,0,
	15,4,2,2,24,2,12,0,0,0,0,3,4,1,19,3,0,0,0,1,0,0,2,6,4,3,2,7,4,2,4,18,8,3,4,12,12,4,4,7,3,1,0,0,1,2,1,2,2,0,3,12,8,0,3,3,2,1,1,1,0,3,1,0,
	1,2,4,0,0,0,3,0,1,0,16,2,1,2,4,0,1,0,2,1,2,0,3,5,2,2,0,0,6,6,0,2,0,2,0,1,0,1,5,2,5,1,5,5,0,0,1,2,0,2,0,0,1,1,2,1,5,4,1,0,2,0,1,2,
	3,0,0,4,6,1,0,0,5,1,1,2,9,1,11,6,0,0,1,1,0,5,2,3,6,6,3,0,0,2,0,5,3,1,3,4,0,1,2,1,0,1,0,2,1,3,1,1,0,0,0,0,1,0,2,1,0,6,1,2,5,20,1,3,
	3,0,0,4,2,0,2,1,1,7,4,3,0,1,0,1,1,0,0,1,2,3,3,1,3,5,2,2,2,0,0,1,0,14,2,0,0,4,0,2,10,2,0,1,1,3,6,18,0,5,1,1,0,1,2,14,3,0,11,5,12,0,0,4,
	6,0,2,2,7,0,0,1,7,5,13,0,3,1,0,1,1,1,3,0,0,3,14,9,4,0,1,0,15,0,0,8,1,1,5,10,23,10,2,0,1,0,4,7,4,5,4,0,3,1,1,1,11,3,1,5,0,9,1,1,2,3,2,1,
	0,4,0,2,5,9,2,0,3,2,2,10,3,12,2,0,6,12,3,0,0,13,1,1,1,6,0,0,6,2,2,0,2,2,0,0,0,1,2,2,4,9,7,0,0,2,0,4,2,0,0,22,3,3,1,0,7,3,0,0,0,0,7,1,
	5,0,2,2,6,1,1,0,1,0,1,3,2,10,4,2,4,2,1,0,5,2,2,1,2,0,12,0,3,4,3,0,0,1,0,1,3,6,0,0,7,9,0,0,7,4,3,1,2,0,2,1,1,1,0,3,9,0,1,0,0,0,6,0,
	8,0,3,0,6,3,4,3,0,0,2,2,1,1,5,3,2,2,0,2,1,0,3,2,1,6,2,0,2,1,4,1,1,1,0,3,1,7,1,2,1,4,0,1,3,12,11,0,1,0,1,0,0,1,0,0,0,1,1,6,7,1,4,1,
	0,5,4,11,0,3,1,1,2,1,0,1,1,2,0,3,8,2,3,2,1,1,7,0,2,1,0,1,0,0,0,2,13,2,3,0,0,2,3,5,2,0,8,6,6,2,0,0,0,2,6,0,1,1,3,2,0,7,2,0,5,0,0,0,
	2,8,0,2,8,5,0,0,2,0,6,6,1,3,4,2,1,5,1,1,4,1,0,1,0,2,3,4,0,1,0,5,2,0,0,9,0,1,1,7,3,3,2,0,0,4,0,0,0,0,1,4,3,3,2,1,0,0,1,1,0,2,1,3,
	0,0,0,2,0,1,2,3,0,1,0,0,0,0,4,0,0,8,0,1,0,0,1,0,5,0,6,0,0,0,1,5,1,0,0,5,4,2,2,0,0,2,1,5,2,0,2,0,2,3,11,5,3,5,0,0,0,2,2,8,0,0,0,0,
	0,0,0,1,0,2,1,0,1,0,0,7,2,0,3,1,0,5,1,1,0,0,1,0,6,0,2,2,2,1,6,5,2,0,3,0,0,5,0,8,2,0,1,0,0,2,4,2,3,2,1,1,0,0,1,0,2,1,2,3,0,1,6,0,
	0,2,0,2,0,2,4,0,1,1,1,2,8,1,1,4,5,4,0,0,0,1,0,0,6,0,153,3,10,6,0,0,1,3,11,7,0,0,0,2,1,1,2,1,1,8,0,1,0,0,0,1,1,1,5,2,2,2,0,5,3,0,4,0,
	6,1,0,3,3,3,4,1,5,1,0,10,0,4,2,1,4,2,5,1,0,3,0,1,0,0,0,5,3,1,2,1,0,3,9,1,10,2,4,1,8,3,11,1,1,3,0,1,0,12,0,0,0,0,0,2,5,0,0,6,0,1,1,0,
	6,2,1,1,0,1,3,0,2,3,0,2,1,1,0,1,5,8,0,1,5,1,7,2,0,0,1,0,2,2,0,7,1,1,2,3,3,0,4,2,0,0,0,0,0,15,0,7,5,5,1,1,5,4,6,5,2,1,0,1,0,0,9,5,
	0,4,1,0,1,0,2,3,0,0,4,0,1,0,4,1,4,5,4,1,0,2,2,4,0,6,2,1,4,3,0,0,1,3,1,4,3,1,4,0,0,4,0,2,1,1,0,1,2,5,0,5,1,1,2,0,2,1,0,1,1,0,0,1,
	6,0,2,0,1,0,9,0,0,0,6,1,0,0,0,0,6,6,16,0,5,4,1,1,1,0,2,0,1,0,3,0,0,0,4,8,3,1,0,3,6,3,1,5,0,4,0,0,1,1,1,3,0,0,1,1,7,11,0,0,0,2,3,0,
	1,0,3,1,0,0,3,5,1,0,4,0,3,3,1,0,3,4,8,0,2,0,6,4,2,3,1,0,1,0,0,1,0,15,0,4,2,5,26,1,1,3,0,12,4,4,2,3,3,0,2,4,0,1,0,5,11,2,0,3,4,1,1,4,
	2,1,3,0,1,0,8,1,3,0,0,0,1,8,5,0,7,0,0,17,8,2,4,3,2,3,0,10,0,4,8,3,0,4,1,2,2,1,0,0,1,1,3,1,1,0,9,0,10,3,4,2,2,1,11,4,1,3,2,0,2,4,1,2,
	0,0,1,2,0,4,2,0,17,1,5,7,2,0,11,4,1,0,0,1,0,1,4,4,1,5,0,7,7,3,1,4,0,0,0,2,4,3,1,10,3,0,0,2,9,2,3,1,3,2,0,1,5,0,2,4,10,1,1,0,0,0,0,1,
	0,9,0,6,7,1,1,1,0,4,6,0,6,0,0,2,0,12,1,0,0,3,2,3,0,2,11,0,2,3,14,17,14,1,3,0,4,1,1,0,7,3,0,2,1,7,1,14,0,0,6,1,6,6,0,4,0,0,3,0,5,10,2,1,
	0,1,1,1,0,2,2,4,1,2,0,4,4,2,0,0,0,8,0,0,0,2,1,1,0,2,1,0,0,2,3,0,0,4,1,1,8,3,7,2,2,3,2,0,9,1,0,1,4,1,1,1,5,0,2,0,0,0,1,5,2,0,1,1,
	1,6,2,5,4,17,0,1,8,1,1,3,6,0,1,2,3,1,0,3,2,1,1,3,8,0,11,2,2,3,0,1,1,2,4,1,0,3,2,0,0,1,2,0,0,8,2,0,3,9,4,9,3,1,5,0,4,0,3,1,1,1,3,0,
	0,4,2,4,4,1,5,0,0,2,5,2,1,4,3,0,0,0,4,3,1,6,5,2,0,1,7,1,0,0,0,0,8,0,1,2,0,2,0,2,0,1,1,6,9,0,4,0,2,0,0,5,2,2,1,3,1,0,10,6,4,0,10,1,
	2,5,2,0,16,7,0,0,3,1,8,2,1,2,7,1,4,0,0,1,0,3,6,0,0,1,6,5,2,4,2,0,6,2,1,0,17,7,1,0,5,2,13,11,1,0,4,1,1,1,4,3,0,2,1,1,3,1,4,2,3,1,0,1,
	3,0,0,4,6,7,0,2,0,5,2,1,1,0,2,2,1,1,0,1,0,0,0,14,2,1,1,2,0,3,1,1,2,5,1,0,1,0,1,1,3,0,2,1,4,1,2,2,2,1,2,3,0,0,1,2,3,3,0,0,3,0,0,1,
	1,0,3,1,0,2,1,3,0,1,3,1,0,0,1,9,1,3,2,1,0,0,1,3,4,1,2,0,6,5,7,1,5,4,0,8,1,1,2,6,4,0,3,1,1,2,8,2,6,1,1,1,1,0,2,3,156,2,4,1,4,0,0,0,
	0,1,1,6,4,6,8,1,11,0,0,1,5,2,3,2,0,10,2,1,0,1,0,0,4,0,0,0,0,0,1,0,0,2,0,1,0,0,2,0,0,1,0,1,0,0,2,2,2,0,2,1,6,0,0,1,1,1,0,0,1,3,2,12,
	1,0,6,0,2,2,1,1,0,2,0,1,77,1,0,3,1,2,2,0,2,13,4,24,4,10,6,3,3,3,4,0,1,0,1,4,3,0,1,1,1,1,4,1,0,3,3,1,6,12,0,4,0,12,0,1,9,5,4,12,1,2,0,0,
	0,0,0,3,4,3,5,0,2,0,13,1,1,5,4,2,0,1,2,2,3,1,5,7,8,0,0,2,0,0,12,1,7,1,0,0,0,4,8,3,2,8,12,2,0,0,5,5,0,1,5,0,0,6,0,0,8,2,0,2,1,3,4,2,
	2,0,2,1,0,0,2,2,0,9,7,1,0,1,54,0,1,0,3,2,1,4,0,0,0,0,0,2,0,0,2,0,0,2,2,1,0,8,2,2,5,11,3,0,1,1,0,6,0,0,0,2,2,0,1,1,0,6,1,0,0,1,0,0,
	1,1,0,2,0,0,0,0,0,0,8,1,2,0,5,0,2,4,0,2,1,1,0,0,1,0,0,1,1,0,0,0,2,2,3,0,1,1,3,3,0,0,2,2,1,0,1,1,0,1,0,0,0,0,0,2,0,1,1,2,1,17,2,3,
	4,8,8,8,3,18,0,5,4,7,1,5,4,22,19,2,1,22,0,0,0,0,0,3,1,1,4,6,0,1,3,0,1,8,1,0,9,4,3,1,2,1,4,4,5,1,3,1,1,2,4,0,0,1,1,1,4,4,0,0,0,2,0,0,
	0,0,0,6,3,0,5,2,0,13,9,7,5,0,2,2,0,8,21,2,1,5,4,3,0,1,3,7,3,2,3,1,1,10,6,5,1,2,1,11,1,4,1,0,0,16,9,1,21,2,6,10,4,0,2,4,0,4,1,1,9,8,0,7,
	1,5,1,0,2,1,2,0,1,0,2,7,0,15,1,6,6,16,1,1,4,6,1,13,7,1,0,2,12,4,1,10,0,8,4,8,4,0,0,4,3,2,3,43,3,0,0,16,9,0,1,1,9,12,0,0,6,0,2,1,1,13,4,1,
	4,0,1,247,8,1,0,3,1,0,0,3,1,1,0,3,9,0,0,0,0,1,4,4,6,1,0,1,4,3,0,1,0,0,0,6,0,0,1,3,4,0,2,54,4,6,1,3,3,8,3,0,3,6,0,0,2,10,2,0,2,0,0,0,
	4,1,3,2,1,0,1,1,2,7,0,1,1,0,1,0,0,4,0,1,0,0,1,0,3,2,3,0,8,2,2,1,1,0,3,0,2,0,0,0,1,1,0,0,0,2,3,0,2,1,6,0,4,1,0,4,1,3,0,1,1,4,3,1,
	0,2,2,1,1,1,2,2,2,1,8,8,1,6,3,0,3,1,1,1,0,8,3,2,1,0,1,1,0,0,5,0,1,1,3,2,5,1,7,0,0,4,1,1,0,7,3,3,2,2,1,2,1,5,0,5,8,2,4,7,4,2,0,16,
	0,3,0,7,3,1,0,0,1,0,1,3,2,0,0,0,0,3,0,1,6,2,7,0,2,6,0,2,0,0,8,4,0,0,0,0,4,0,0,1,1,0,2,8,3,0,3,0,1,0,51,1,4,1,4,13,22,0,2,2,6,3,0,0,
	2,0,0,7,0,0,4,1,3,0,1,3,1,0,4,2,1,0,1,0,0,1,3,3,1,12,2,3,2,3,1,0,3,0,0,2,1,62,0,0,0,11,2,3,0,0,4,0,12,1,0,0,0,1,7,0,0,2,2,4,1,13,0,2,
	6,2,3,14,0,2,0,5,6,7,7,6,0,5,1,12,0,6,4,0,3,2,1,0,3,0,61,4,2,5,1,3,3,3,10,1,2,3,0,8,0,6,2,0,0,1,2,2,3,10,17,1,4,2,0,1,1,0,0,4,2,0,8,0,
	4,0,0,0,0,7,0,0,1,2,3,1,0,2,4,4,3,2,3,0,4,9,0,9,1,0,0,0,3,6,0,0,7,1,0,0,0,0,2,2,3,0,7,7,0,3,0,1,0,1,1,4,1,3,0,0,0,0,1,0,6,0,0,3,
	2,1,11,1,0,0,1,0,2,1,0,1,0,2,4,2,1,0,0,1,1,3,0,0,0,0,4,0,1,0,0,2,8,0,6,2,0,3,0,1,0,0,0,1,0,6,0,1,0,2,1,1,2,0,1,108,1,1,6,1,0,0,1,12,
	2,0,0,0,4,3,2,5,3,3,2,1,2,0,14,2,0,4,1,9,0,7,2,0,0,0,0,0,2,7,2,2,4,2,1,10,1,3,1,10,14,1,3,2,1,0,2,1,0,5,0,1,4,9,3,14,6,1,2,1,3,0,0,2,
	12,15,0,2,86,2,0,2,0,1,1,5,0,2,6,0,1,1,5,0,0,5,0,1,0,0,1,0,7,2,0,0,0,2,0,4,7,0,0,0,0,1,1,4,1,0,0,0,1,4,9,4,1,6,1,8,5,4,1,10,0,10,2,9,
	0,0,2,11,3,3,12,1,0,0,2,0,2,1,5,3,0,21,7,1,4,
};

static ImWchar baseUnicodeRanges[] =
{
	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	0x3000, 0x30FF, // Punctuations, Hiragana, Katakana
	0x31F0, 0x31FF, // Katakana Phonetic Extensions
	0xFF00, 0xFFEF, // Half-width characters
};

}

bool THRotatorImGui_Initialize(HWND hWnd, THRotatorImGui_D3DDeviceInterface* device)
{
	bool bInitSuccessful = ImGui_IMPLFUNC(Init)(hWnd, device);
	if (!bInitSuccessful)
	{
		return false;
	}

	using GUIFontSource = std::pair<std::string, int>;

	// Japanese font candidates for ImGui
	const std::vector<GUIFontSource> fontSources
	{
		//{ "C:\\Windows\\Fonts\\YuGothB.ttc", 1 }, // Yu Gothic UI Bold (path of .ttc differs on different Windows OS)
		{ "C:\\Windows\\Fonts\\meiryo.ttc", 2 }, // Meiryo UI
		{ "C:\\Windows\\Fonts\\msgothic.ttc", 1 }, // MS UI Gothic
	};

	ImGuiIO& io = ImGui::GetIO();
	for (const auto& fontSource : fontSources)
	{
		if (boost::filesystem::exists(fontSource.first))
		{
			static bool bKanjiRangeUnpacked = false;
			static ImWchar japaneseRanges[_countof(baseUnicodeRanges) + _countof(offsetsFrom0x4E00) * 2 + 1];
			if (!bKanjiRangeUnpacked)
			{
				// Unpack
				int codepoint = 0x4e00;
				memcpy(japaneseRanges, baseUnicodeRanges, sizeof(baseUnicodeRanges));
				ImWchar* dst = japaneseRanges + _countof(baseUnicodeRanges);
				for (int n = 0; n < _countof(offsetsFrom0x4E00); n++, dst += 2)
				{
					dst[0] = dst[1] = (ImWchar)(codepoint += (offsetsFrom0x4E00[n] + 1));
				}

				dst[0] = 0;
				bKanjiRangeUnpacked = true;
			}

			ImFontConfig fontConfig;
			fontConfig.FontNo = fontSource.second;

			io.Fonts->AddFontFromFileTTF(fontSource.first.c_str(), 16.0f, &fontConfig, japaneseRanges);

			break;
		}
	}

	return true;
}

void THRotatorImGui_Shutdown()
{
	ImGui_IMPLFUNC(Shutdown)();
}

void THRotatorImGui_NewFrame()
{
	ImGui_IMPLFUNC(NewFrame)();
}

void THRotatorImGui_InvalidateDeviceObjects()
{
	ImGui_IMPLFUNC(InvalidateDeviceObjects)();
}

void THRotatorImGui_CreateDeviceObjects()
{
	ImGui_IMPLFUNC(CreateDeviceObjects)();
}

LRESULT THRotatorImGui_WindowProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	extern LRESULT ImGui_IMPLFUNC(WndProcHandler)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	return ImGui_IMPLFUNC(WndProcHandler)(hWnd, msg, wParam, lParam);
}
