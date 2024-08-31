#include "GameManager.h"

#include "get.h"

#include "Driver.h"



namespace sdk
{




	std::pair<uint64_t, uint32_t> GetEntity(uintptr_t GameManager)
	{



		auto qword_83E8B28 = offsets::GetGameManager();



		auto enc = *(__m128*)(qword_83E8B28 + 0xF30);

		auto v146 = (get::retaddr >> 0x21);

		enc.m128_u64[0] += v146;
		enc.m128_u64[1] += v146;

		enc.m128_u64[1] -= 0x7AA62F81B156DE31i64;

		enc.m128_u64[0] ^= 0x67;
		enc.m128_u64[1] ^= (0x67 + 0x7F6D38D7A1116C23i64);

		enc.m128_u64[0] = (enc.m128_u64[0] << 0x20) & 0xFF00000000000000ui64 | (enc.m128_u64[0] << 8) & 0xFF0000000000i64 | (enc.m128_u64[0] >> 8) & 0xFF00000000i64 | (enc.m128_u64[0] >> 0x28) & 0xFF00 | ((_DWORD)enc.m128_u64[0] << 8) & 0xFF000000 | (enc.m128_u64[0] << 0x28) & 0xFF000000000000i64 | ((unsigned __int8)enc.m128_u64[0] << 0x10) | HIBYTE(enc.m128_u64[0]);
		enc.m128_u64[1] = (enc.m128_u64[1] >> 0x28) & 0xFF00 | ((_DWORD)enc.m128_u64[1] << 8) & 0xFF000000 | ((unsigned __int8)enc.m128_u64[1] << 0x10) | HIBYTE(enc.m128_u64[1]);

		return { enc.m128_u64[0], enc.m128_u64[1] & 0x3FFFFFFF };

	}



	uint64_t GetLocalEntity() {
		uint64_t LocalPlayer;
		return LocalPlayer = *(_QWORD*)(GetEntity(offsets::GetGameManager()).first);
		
		
	}



	uint64_t GetReplication(uint64_t Entity)
	{

	LABEL_54:
		uint64_t v165, Replication, v79, v155, v148, v150, v158, v159, v160, v161, v162, v163, v164, v33, v34, v35, v116, v113, v111, v37;
	LABEL_58:
		v33 = ((unsigned __int64)get::GetPEBAddress() >> 0xC) - 0x5DFB6CC0C0478F69i64;
		LODWORD(v111) = 0x58B5BDDA;
		if (HIDWORD(v33))
			v34 = v33 % 2;
		else
			v34 = (unsigned int)v33 % 2;
		v113 = v34;
		LODWORD(v111) = 0xC160E7F5;
		if (v34)
		{
			v111 = v113;
			v37 = __ROL8__(driver->read<uint64_t>(Entity + 0x58), 0x23);
			Replication = ((v37 >> 0x18) & 0xFF00000000i64)
				+ ((v37 << 0x28) & 0xFF00000000000000ui64)
				+ ((v37 << 8) & 0xFFFF0000000000i64)
				+ (HIDWORD(v37) & 0xFF0000)
				+ ((unsigned int)v37 & 0xFF00FFFF)
				- 0x5DFB6CC0B2CCD8BEi64;
			if (!Replication)
				goto LABEL_58;
		}
		else
		{
			v35 = __ROL8__(driver->read<uint64_t>(Entity + 0x58), 0x23) - 0x5DFB6CC0B2CCD8BEi64;
			Replication = (v35 << 0x28) & 0xFF00000000000000ui64 | (v35 >> 0x18) & 0xFF00000000i64 | (unsigned int)v35 & 0xFF00FFFF | HIDWORD(v35) & 0xFF0000 | (v35 << 8) & 0xFFFF0000000000i64;
			if (!Replication)
				goto LABEL_58;
		}


		return Replication;

	};


		




	uint64_t GetPawn(uint64_t Entity)
	{
		uintptr_t v113, v53, v116, Temp, Pawn, v44, v12, v13, v14, v15, v16, v7, v6, v98, v107;
	LABEL_146:
		v98 = (((unsigned __int64)get::GetPEBAddress() >> 0xC) ^ 0x291A6AD31A982A77i64) % 2;
		LODWORD(v107) = 0xA0C0A6BF;
		if (v98)
		{
			driver->read<uint64_t>(v107 = v98);
			Pawn = (driver->read<uint64_t>(Entity + 0x100) + 0x38783CFC199BA178i64) ^ 0x1162562F03038B0Fi64;
			if (!Pawn)
				goto LABEL_146;
		}
		else
		{
			v6 = driver->read<uint64_t>(Entity + 0x100) ^ 0x1162562F03038B0Fi64;
			Pawn = v6 + 0x38783CFC199BA178i64;
			if (v6 == 0xC787C303E6645E88ui64)
				goto LABEL_146;
		}


		return Pawn;
	}



	uint64_t GetActor(uint64_t Pawn)
	{
		uintptr_t v105, v7, v98, Temp, v102, v97, Actor, Component, v113, v9, v10, v11, v12, v13, v8, v107, v106, v14, v26, v103;
	LABEL_16:
	LABEL_10:
		v8 = 0x1E5EE2E1i64 - __ROR8__(get::GetPEBAddress(), 0xC);
		LODWORD(v107) = 0xA32C56DF;
		if (HIDWORD(v8))
			v9 = v8 % 6;
		else
			v9 = (unsigned int)v8 % 6;
		v105 = v9;
		LODWORD(v107) = 0x72E8E797;
		if (v9)
		{
			v106 = v105;
			LODWORD(v107) = 0xD6333EED;
			if (v105 == 1)
			{
				v12 = driver->read<uint64_t>(Pawn + 0x18) + 0x11i64;
				v11 = __ROL8__(
					(v12 << 8) & 0xFF00000000000000ui64 | (v12 << 0x10) & 0xFF000000000000i64 | ((unsigned int)(driver->read<uint32_t>(Pawn + 0x18) + 0x11) >> 0x10) & 0xFF00 | ((driver->read<uint32_t>(Pawn + 0x18) + 0x11) << 8) & 0xFF000000 | BYTE1(v12) | ((unsigned __int64)(unsigned __int8)v12 << 0x20) | v12 & 0xFF0000000000i64 | (v12 >> 0x28) & 0xFF0000,
					0xC);
				goto LABEL_16;
			}
			v102 = v106;
			LODWORD(v107) = 0xEC9673DC;
			if (v106 == 2)
			{
				v13 = __ROL8__(driver->read<uint64_t>(Pawn + 0x18), 0xC);
				v14 = (v13 << 8) & 0xFF00000000000000ui64 | (v13 << 0x10) & 0xFF000000000000i64 | WORD1(v13) & 0xFF00 | ((_DWORD)v13 << 8) & 0xFF000000 | BYTE1(v13) | ((unsigned __int64)(unsigned __int8)v13 << 0x20) | v13 & 0xFF0000000000i64 | (v13 >> 0x28) & 0xFF0000;
			}
			else
			{
				v103 = v102;
				LODWORD(v107) = 0x6DE1247C;
				if (v102 == 3)
				{
					Actor = __ROL8__(driver->read<uint64_t>(Pawn + 0x18), 0xC) + 0x11i64;
					goto LABEL_10;
				}
				v98 = v103;
				LODWORD(v107) = 0x66B6F599;
				if (v103 == 4)
				{
					v26 = driver->read<uint64_t>(Pawn + 0x18);
					v11 = __ROL8__(
						((v26 << 8) & 0xFF00000000000000ui64 | (driver->read<uint32_t>(Pawn + 0x18) << 8) & 0xFF000000 | (unsigned __int64)(WORD1(v26) & 0xFF00) | (v26 << 0x10) & 0xFF000000000000i64 | (v26 << 0x20) & 0xFF00000000i64 | v26 & 0xFF0000000000i64 | BYTE1(v26) | (v26 >> 0x28) & 0xFF0000)
						+ 0x11,
						0xC);
					goto LABEL_16;
				}
				driver->read<uint64_t>(v107 = v98);
				v97 = driver->read<uint64_t>(Pawn + 0x18);
				v14 = __ROL8__(
					(v97 << 8) & 0xFF00000000000000ui64 | (driver->read<uint32_t>(Pawn + 0x18) << 8) & 0xFF000000 | (unsigned __int64)(WORD1(v97) & 0xFF00) | (v97 << 0x10) & 0xFF000000000000i64 | (v97 << 0x20) & 0xFF00000000i64 | v97 & 0xFF0000000000i64 | BYTE1(v97) | (v97 >> 0x28) & 0xFF0000,
					0xC);
			}
			v11 = v14 + 0x11;
			goto LABEL_16;
		}
		Actor = __ROL8__(driver->read<uint64_t>(Pawn + 0x18) + 0x11i64, 0xC);

		return Actor;


	}

	vec3_t GetActorPos(uintptr_t Actor)
	{
		return *(vec3_t*)(Actor + 0x50);
	}








	uint32_t GetActorHealth(uint64_t Actor)
	{
		auto v5 = get::retaddr >> 0x21;
		auto DamageComponentID = driver->read<uint8_t>(Actor + 0x216);
		auto Component = driver->read<uint64_t>(driver->read<uint64_t>(Actor + 0xD8) + DamageComponentID * 8ul);
		uintptr_t v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, Health;
		v14 = 0x9AB69365354A9C35ui64 - __ROR8__(get::GetPEBAddress(), 0xC);

		auto overheadbestdev = driver->read<uint32_t>(Component + 0x1BC);
		return Health = (overheadbestdev & 0xFF0000 | (unsigned __int8)BYTE1(overheadbestdev) | (overheadbestdev << 0x18) | HIWORD(overheadbestdev) & 0xFF00) == 0x200;


		return Health & 0xFFFF;
	}


	char getplayernames(uintptr_t Replication)
	{
		return   (*(char*)(Replication + 0x70));
	}

















}




