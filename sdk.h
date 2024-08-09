#include "GameManager.h"




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



	uint64_t GetReplication(uint64_t localcontroller)
	{


		
	LABEL_54:
		uint64_t v165, Replication, v79, v155, v148, v150, v158, v159, v160, v161, v162, v163, v164, v33, v34, v35, v116, v113;
		auto v123 = get::retaddr;
		auto v118 = v123 & 0xFFFFFFFE00000000ui64;
		v33 = ((unsigned __int64)get::GetPEBAddress() >> 0xC) - 0x2E15D02AFC317581i64;
		LODWORD(v113) = 0xFA3573C3;
		v34 = (unsigned int)((_DWORD)0x5CA8C3E + 1 - 0x5CA8C3D);
		if (HIDWORD(v33))
			v35 = v33 % v34;
		else
			v35 = (unsigned int)v33 % (unsigned int)v34;
		v116 = v35;
		LODWORD(v113) = 0xB6F6672D;
		auto ang123 = *(_QWORD*)(localcontroller + 0x80);
		if (v35)
		{
			v113 = v116;
			Replication = ((((unsigned int)v118 ^ *(uint32_t*)(localcontroller + 0x80)) << 8) & 0xFF000000)
				+ (unsigned __int64)(unsigned __int8)((v118 ^ *(_QWORD*)(localcontroller + 0x80)) >> 0x20)
				+ (((v118 ^ *(_QWORD*)(localcontroller + 0x80)) >> 8) & 0xFF000000000000i64)
				+ ((unsigned int)0xFF0000 & (unsigned int)((v118 ^ *(_QWORD*)(localcontroller + 0x80)) >> 0x18))
				+ (((v118 ^ *(_QWORD*)(localcontroller + 0x80)) << 8) & 0xFF00000000000000ui64)
				+ ((*(_QWORD*)(localcontroller + 0x80) << 0x20) & 0xFFFF00000000i64)
				+ (WORD1(ang123) & 0xFF00)
				- 0x6567D6E2DA8CBC56i64;
			if (!Replication)
				goto LABEL_54;
		}
		else
		{
			Replication = (unsigned __int8)(((v118 ^ *(_QWORD*)(localcontroller + 0x80)) - 0x6567D6E2DA8CBC56i64) >> 0x20) | (unsigned __int64)((unsigned int)0xFF0000 & (unsigned int)(((v118 ^ *(_QWORD*)(localcontroller + 0x80)) - 0x6567D6E2DA8CBC56i64) >> 0x18)) | (((v118 ^ *(_QWORD*)(localcontroller + 0x80)) - 0x6567D6E2DA8CBC56i64) << 8) & 0xFF00000000000000ui64 | ((((unsigned int)v118 ^ *(uint32_t*)(localcontroller + 0x80)) + 0x257343AA) << 8) & 0xFF000000 | (unsigned __int64)(((((unsigned int)v118 ^ *(uint32_t*)(localcontroller + 0x80)) + 0x257343AA) >> 0x10) & 0xFF00) | (((v118 ^ *(_QWORD*)(localcontroller + 0x80)) - 0x6567D6E2DA8CBC56i64) >> 8) & 0xFF000000000000i64 | (((v118 ^ *(_QWORD*)(localcontroller + 0x80)) - 0x6567D6E2DA8CBC56i64) << 0x20) & 0xFFFF00000000i64;
			if (!Replication)
				goto LABEL_54;
		}


		

		return Replication;
	};






	

	uint64_t GetPawn(uint64_t Localplayer)
	{
		uintptr_t v113, v53, v116, Temp, Pawn, v44, v12, v13, v14, v15, v16;
		v12 = __ROR8__(get::GetPEBAddress(), 0xC) + 0x154AC7D939846129i64;
		if (HIDWORD(v12))
			v13 = v12 % 2;
		else
			v13 = (unsigned int)v12 % 2;
		v14 = 0;
		if (v13)
		{
			v16 = *(_QWORD*)(Localplayer + 0x68) ^ get::retaddr & 0xFFFFFFFE00000000ui64;
			Pawn = v16 - 0x6777A8EFD6288071i64;
			if (v16 == 0x6777A8EFD6288071i64)
				return v14 && Pawn != 0;
		}
		else
		{
			Pawn = (*(_QWORD*)(Localplayer + 0x68) - 0x6777A8EFD6288071i64) ^ get::retaddr & 0xFFFFFFFE00000000ui64;
			if (!Pawn)
				return v14 && Pawn != 0;
		}

		return Pawn;
	}



	uint64_t GetActor(uint64_t Pawn)
	{


		auto v3 = Pawn;
		uint64_t v6 = 0;
		uint64_t v5 = 0;
		uint64_t v4 = 0;
		uint64_t v24 = 0;
		uint64_t v23 = (__ROR8__(get::GetPEBAddress(), 0xC) ^ 0x26E100F55EAA2F51ui64) % 4;
		if (!v23 || (v24 = v23, v23 == 1))
		{
			v4 = *(_QWORD*)(v3 + 0x18) - 0x77EF1E5E897ABC87i64;
			v5 = get::retaddr & 0xFFFFFFFE00000000ui64 ^ 0x94DFC2662512AD3Dui64;
		LABEL_5:
			v6 = v4 ^ v5;
			goto LABEL_6;
		}
		v4 = 0x94DFC2662512AD3Dui64;
		if (v24 != 2)
		{
			v5 = (*(_QWORD*)(v3 + 0x18) ^ get::retaddr & 0xFFFFFFFE00000000ui64) - 0x77EF1E5E897ABC87i64;
			goto LABEL_5;
		}
		v6 = (*(_QWORD*)(v3 + 0x18) ^ get::retaddr & 0xFFFFFFFE00000000ui64 ^ 0x94DFC2662512AD3Dui64) - 0x77EF1E5E897ABC87i64;
	LABEL_6:
		return v6;


	}

	vec3_t GetActorPos(uintptr_t Actor)
	{
		return *(vec3_t*)(Actor + 0x50);
	}








	uint32_t GetActorHealth(uint64_t Actor)
	{

		auto v5 = get::retaddr >> 0x21;
		auto DamageComponentID = *reinterpret_cast<uint8_t*>(Actor + 0x216);
		auto a3 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(Actor + 0xD8) + DamageComponentID * 8ul);

		uint32_t Health_1 = 0;
		uint64_t v29 = 0;
		uint64_t v27 = 0;
		uint64_t v26 = 0;
		uint64_t v25 = 0;
		uint64_t v24 = 0;
		uint64_t v23 = 0;
		uint64_t v17 = 0;
		uint64_t v16 = 0x9AB69365354A9C35ui64 - __ROR8__(get::GetPEBAddress(), 0xC);
		if (HIDWORD(v16))
			v17 = v16 % 6;
		else
			v17 = (unsigned int)v16 % 6;
		switch (v17)
		{
		case 0ui64:
			v23 = __ROL4__(*(_DWORD*)(a3 + 0x18C) + 0x5AA97872, 0x1A);
		LABEL_32:
			LOBYTE(v24) = v23 ^ 0x9D;
			v25 = v23 & 0xFF00 ^ 0x1B00;
			v26 = v23 & 0xFFFF0000 ^ 0x1C0000;
			v27 = v23 & 0xFF000000 ^ 0x90000000;
			goto LABEL_75;
		case 1ui64:
			v24 = __ROL4__((*(_DWORD*)(a3 + 0x18C) + 0x5AA97872) ^ 0x901C1B9D, 0x1A);
			goto LABEL_74;
		case 2ui64:
			v29 = __ROL4__(*(_DWORD*)(a3 + 0x18C), 0x1A) ^ 0x901C1B9D;
			break;
		case 3ui64:
			v23 = __ROL4__(*(_DWORD*)(a3 + 0x18C), 0x1A) + 0x5AA97872;
			goto LABEL_32;
		case 4ui64:
			v24 = __ROL4__(
				((*(unsigned __int8*)(a3 + 0x18F) ^ 0x90) << 0x18)
				+ (((*(unsigned __int8*)(a3 + 0x18E) ^ 0x1C) << 0x10) | *(unsigned __int8*)(a3 + 0x18C) ^ 0x9D | ((*(unsigned __int8*)(a3 + 0x18D) ^ 0x1B) << 8))
				+ 0x5AA97872,
				0x1A);
			goto LABEL_74;
		default:
			v29 = __ROL4__(
				*(unsigned __int8*)(a3 + 0x18C) ^ 0x9D | ((*(unsigned __int8*)(a3 + 0x18F) ^ 0x90) << 0x18) | ((*(unsigned __int8*)(a3 + 0x18E) ^ 0x1C) << 0x10) | ((*(unsigned __int8*)(a3 + 0x18D) ^ 0x1B) << 8),
				0x1A);
			break;
		}
		v24 = v29 + 0x5AA97872;
	LABEL_74:
		v25 = v24 & 0xFF00;
		v26 = v24 & 0xFFFF0000;
		v27 = v24 & 0xFF000000;
	LABEL_75:
		Health_1 = v27 & 0xFF000000 | (unsigned int)0xFF0000 & v26 | v25 & 0xFF00 | (unsigned __int8)v24;

		if (Health_1)
			return Health_1;
		return 0;


	}


	char getplayernames(uintptr_t Replication)
	{
		return   (*(char*)(Replication + 0x70));
	}

















}




