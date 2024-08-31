
#pragma once
#include "get.h"
#include "hexarys.h"



namespace offsets
{




    uint64_t GetGameManager()
    {
        uint64_t v165, Replication, v79, v155, v148, v150, v158, v159, v160, v161, v162, v163, v164, v33, v34, v35, v116, v113, v19, v21, v22, v23, v24, v25, v26, v27, v28, v119, v117, v20, v124, v122, Gamemanager123, List, Count, v111, v12, v13, v14, v17, v18, v15, v16, v114, v115, v140, v141, v142, v143, v144, v145, v146;
        auto qword_902D0E0 = image_base + 0x902D0E0;
    LABEL_23:
        v12 = 0x53 - ((unsigned __int64)get::GetPEBAddress() >> 0xC);
        LODWORD(v141) = 0xE59A80EE;
        if (HIDWORD(v12))
            v13 = v12 % 6;
        else
            v13 = (unsigned int)v12 % 6;
        v146 = v13;
        LODWORD(v141) = 0x57014B2B;
        if (!v13)
        {
            v14 = qword_902D0E0;
            v15 = get::retaddr & 0xFFFFFFFE00000000ui64;
        LABEL_12:
            Gamemanager123 = __ROL8__(v14 - v15 - 0x11, 0x3C);
            goto LABEL_23;
        }
        v145 = v146;
        LODWORD(v141) = 0x43409CD7;
        if (v146 == 1)
        {
            Gamemanager123 = __ROL8__(qword_902D0E0 - 0x11, 0x3C) - (get::retaddr & 0xFFFFFFFE00000000ui64);
        }
        else
        {
            v144 = v145;
            LODWORD(v141) = (_DWORD)0x7A02AAF + 3;
            if (v145 == (_DWORD)0x7A02AAF + 3 - 0x7A02AB0)
            {
                v17 = __ROL8__(qword_902D0E0 - (get::retaddr & 0xFFFFFFFE00000000ui64), 0x3C);
            }
            else
            {
                v143 = v144;
                LODWORD(v141) = 0x1188A652;
                if (v144 == 3)
                {
                    v15 = get::retaddr & 0xFFFFFFFE00000000ui64;
                    v14 = qword_902D0E0;
                    goto LABEL_12;
                }
                v142 = v143;
                LODWORD(v141) = 0x76B4D456;
                if (v143 != 4)
                    v141 = v142;
                v17 = __ROL8__(qword_902D0E0, 0x3C) - (get::retaddr & 0xFFFFFFFE00000000ui64);
            }
            Gamemanager123 = v17 - 0x11;
        }


        return Gamemanager123;
    }





}
