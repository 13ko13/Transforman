#pragma once

namespace Graphic
{
	constexpr int screen_width = 1280;
	constexpr int screen_height = 720;
	constexpr int color_bit = 32;
}

namespace Pad
{
	//ƒpƒbƒh“ü—Í
	constexpr int pad_down = 0x1;
	constexpr int pad_left = 0x2;
	constexpr int pad_right = 0x4;
	constexpr int pad_up = 0x8;

	constexpr int pad_a = 0x10;
	constexpr int pad_b = 0x20;
	constexpr int pad_x = 0x40;
	constexpr int pad_y = 0x80;

	constexpr int pad_lt = 0x100;
	constexpr int pad_rt = 0x200;
	constexpr int pad_select = 0x400;
	constexpr int pad_start = 0x800;

}