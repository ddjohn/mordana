#ifndef KEYS_H
#define KEYS_H

static char keyboard[] =
//   0123456789abcdef 
	"................" //0x0x
	".....q1...zsaw2." //0x1x
	".cxde43...vftr5." //0x2x
	".nbhgy6...mju78." //0x3x
	"..kio09....l.p.." //0x4x
	"..........\n....." //0x5x
	"................" //0x6x
	"................" //0x7x
	"................" //0x8x
	"................" //0x9x
	"................" //0xax
	"................" //0xbx
	"................" //0xcx
	"................" //0xdx
	"................" //0xex
	"................" //0xfx
	;

#define GETCHAR_WAITING -1337
#define GETCHAR_NOTWAITING -1234

int kernel_getchar();
extern "C" void handleScanCode(unsigned char scancode);

#endif //KEYS_H
