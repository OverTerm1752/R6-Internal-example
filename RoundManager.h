#pragma once
#include "get.h"

namespace offsets
{

//
// Round manager 
//
// v11 = 0x9513E605F0EA337Fui64 - __ROR8__(NtCurrentPeb(), 0xC) - 0x1E;
// LODWORD(v106) = 0x3B0FE0F7;
// if (HIDWORD(v11))
//     v12 = v11 % 2;
// else
//     v12 = (unsigned int)v11 % 2;
// v107 = (_BYTE*)v12;
// LODWORD(v106) = 0x1DD995D2;
// if (v12)
// {
//     v106 = v107;
//     v13 = __ROL8__(qword_85CAB30 - 0x6AEC19FA0F15CC81i64, 0x22);
// }
// else
// {
//     v13 = __ROL8__(qword_85CAB30, 0x22) - 0x6AEC19FA0F15CC81i64;
// }
//
//
//
// Round State
//
// v19 = (retaddr >> 0x21) - 0x1140B03F9705CC4i64;
// LODWORD(v106) = 0x20E24A54;
// if (HIDWORD(v19))
//     v20 = ((retaddr >> 0x21) - 0x1140B03F9705CC4i64) % 5;
// else
//     v20 = (unsigned int)v19 % 5;
// v109 = (_BYTE*)v20;
// LODWORD(v106) = 0x14F4FE12;
// if (!v20)
// {
//     v21 = ((*(_DWORD*)(v13 + 0xF8) + 0x1A633A09) ^ 0xE3136682) + 0x49;
// LABEL_41:
//     LOWORD(v22) = v21 & 0xFF00;
//     v23 = v21 & 0xFFFF0000;
//     v24 = v21 & 0xFF000000;
// LABEL_42:
//     if ((v24 & 0xFF000000 | (unsigned int)sub_FF0000 & v23 | v22 & 0xFF00 | (unsigned __int8)v21) == 2)
//         sub_729FF60(v8, 1i64, 0i64, 0i64);
//     goto LABEL_44;
// }



}
