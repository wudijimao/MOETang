#ifndef MY_INPUT_H
#define MY_INPUT_H

//class my_Input
//{
//
//};
#define MY_KEYS_UP 38
#define MY_KEYS_DOWN 40
#define MY_KEYS_LEFT 37
#define MY_KEYS_RIGHT 39

#define MY_KEYS_SPACE 0x20

#define MY_KEYS_A 0x41
#define MY_KEYS_B 0x42
#define MY_KEYS_C 0x43
#define MY_KEYS_D 0x44
#define MY_KEYS_E 0x45
#define MY_KEYS_F 0x46
#define MY_KEYS_G 0x47
#define MY_KEYS_H 0x48
#define MY_KEYS_I 0x49
#define MY_KEYS_J 0x4A
#define MY_KEYS_K 0x4B
#define MY_KEYS_L 0x4C
#define MY_KEYS_M 0x4D
#define MY_KEYS_N 0x4E
#define MY_KEYS_O 0x4F
#define MY_KEYS_P 0x50
#define MY_KEYS_Q 0x51
#define MY_KEYS_R 0x52
#define MY_KEYS_S 0x53
#define MY_KEYS_T 0x54
#define MY_KEYS_U 0x55
#define MY_KEYS_V 0x56
#define MY_KEYS_W 0x57
#define MY_KEYS_X 0x58
#define MY_KEYS_Y 0x59
#define MY_KEYS_Z 0x5A
class __declspec(dllimport) my_Keyboard
{
public:
	static bool Keys[256];
	static bool keypress[256];
	static int key[256];
public:
	void sendMessage(int KeyCodes,bool Down);
};
#endif // MY_INPUT_H