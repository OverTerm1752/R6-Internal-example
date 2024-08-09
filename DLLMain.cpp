
#include <string>
#include "Defentionions.h"
#include "sdk.h"
#include <d3d10.h>
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include <d3d11.h>
#include "Minhook/include/MinHook.h"
#include "outlines.h"
#include "otherstuff.h"



























HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!initonce)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGuiD3D11();




			initonce = true;
		}
		else
			return phookD3D11Present(pSwapChain, SyncInterval, Flags);
	}









	//recreate rendertarget on reset
	if (mainRenderTargetViewD3D11 == NULL)
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
		pBackBuffer->Release();
	}

	//get imgui displaysize
	ImGuiIO io = ImGui::GetIO();
	ViewportWidth = io.DisplaySize.x;
	ViewportHeight = io.DisplaySize.y;
	ScreenCenterX = ViewportWidth / 2.0f;
	ScreenCenterY = ViewportHeight / 2.0f;

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		showmenu = !showmenu;
	}


	auto& Style = ImGui::GetStyle();

	Style.WindowPadding = ImVec2(20.000f, 20.000f);
	Style.WindowRounding = 10.000f;
	Style.ChildRounding = 10.000f;
	Style.FramePadding = ImVec2(20.000f, 5.000f);
	Style.FrameRounding = 8.000f;
	Style.FrameBorderSize = 0.000f;
	Style.TabBorderSize = 8.000f;

	Style.Colors[ImGuiCol_WindowBg] = ImColor(64, 64, 64);
	Style.Colors[ImGuiCol_Border] = ImColor(30, 30, 30, 255);
	Style.Colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255);
	Style.Colors[ImGuiCol_FrameBgHovered] = ImColor(50, 50, 50, 255);
	Style.Colors[ImGuiCol_FrameBgActive] = ImColor(90, 90, 90, 255);
	Style.Colors[ImGuiCol_CheckMark] = ImColor(89, 3, 247, 255);
	Style.Colors[ImGuiCol_SliderGrab] = ImColor(89, 3, 247, 255);
	Style.Colors[ImGuiCol_SliderGrabActive] = ImColor(89, 3, 247, 255);
	Style.Colors[ImGuiCol_Button] = ImColor(50, 50, 50, 255);
	Style.Colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 255);
	Style.Colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
	Style.Colors[ImGuiCol_Separator] = ImColor(89, 3, 247, 255);


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();









	auto overlay = ImGui::GetForegroundDrawList();
	std::string textToShow = "Outlines ";
	overlay->AddText({ 5, 5 }, ImColor(255, 0, 0), textToShow.c_str()); // Red TEXT



	if (outlines) {
		overlay->AddText({ 5, 300 }, ImColor(0, 255, 0), "Outlines Enabled"); // Green for active
	}
	else {
		overlay->AddText({ 5, 300 }, ImColor(255, 0, 0), "Outlines disabled"); // Red for deactivated
	}






	//if (CRoundState::GetInstance().isInGame()) { // round check 

	auto gm = offsets::GetGameManager();


	auto [entity_list, entity_count] = sdk::GetEntity(gm);

	for (size_t i = 0; i < entity_count; i++) {
		auto entity = *(QWORD*)(entity_list + i * 8);
		if (!entity)
			continue; //check if value is valid
		auto pawn = sdk::GetPawn(entity);
		if (!pawn)
			continue;
		auto actor = sdk::GetActor(pawn);
		if (!actor)
			continue;
		auto localPawn = sdk::GetPawn(sdk::GetLocalEntity());
		if (!localPawn)
			continue;
		auto localActor = sdk::GetActor(localPawn);
		if (!localActor)
			continue;





		if (outlines)
		{
			auto outline = outlines12::GetOutline(actor);
			auto glow_value = *reinterpret_cast<uint32_t*>(outline + 0x20); //can be found in cheat engine and ida
			bool is_glow = glow_value & ~(1ul << outlinebit); // must be found in cheat engine or reclass
			if (outline) {
				if (!is_glow) {
					glow_value &= ~(1ul << outlinebit);
					uint32_t* write = reinterpret_cast<uint32_t*>(outline + 0x20, glow_value);
					
				}
			}
			else {
				if (is_glow) {
					glow_value &= ~(1ul << outlinebit);
					uint32_t* write = reinterpret_cast<uint32_t*>(outline + 0x20, glow_value);
					glow_value = outlinebit;
				}
			}
		}








	}



	




	if (showmenu) {











		//background part end
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 1;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(31, 31, 31, 255)));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(ImColor(red, green, blue)));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(24, 24, 24, 255)));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ImColor(red, green, blue)));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(ImColor(red, green, blue)));








		ImGui::SetNextWindowSize(ImVec2(650, 450.000f), ImGuiCond_Once);
		ImGui::Begin("R6 example", NULL, 11);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 0, 24, 0)));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(255, 0, 24, 255)));

		//ImGui::Text("Flux [INSERT]");
		ImGui::SameLine();
		ImGui::SetCursorPosX(625);
		ImGui::SetCursorPosY(5);
		if (ImGui::Button("", ImVec2(20, 20)))
		{
			ExitProcess(0);
		}
		ImGui::PopStyleColor(2);
		ImGui::SetCursorPos(ImVec2(0, 30));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(27, 27, 27, 255)));
		ImGui::BeginChild("##Undertitlebar", ImVec2(650, 415), false);
		ImGui::PopStyleColor();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("##categories", ImVec2(170, 405), false);

		if (ImGui::Button("Aimbot", ImVec2(165, 40)))
		{
			tabb = 1;
		}

		if (ImGui::Button("Visuals", ImVec2(165, 40)))
		{
			tabb = 2;
		}

		if (ImGui::Button("Exploits", ImVec2(165, 40)))
		{
			tabb = 3;
		}

		if (ImGui::Button("Settings", ImVec2(165, 40)))
		{
			tabb = 4;
		}




		if (tabb == 1)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));


			ImGui::SetCursorPos(ImVec2(2, 0));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));


			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 2)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 45));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 3)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 90));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 4)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 130));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		// BOTTOM BAR BELOW TAB BUTTONS


		ImGui::EndChild();


		if (tabb == 1)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);
			ImGui::Text("Aimbot");

			ImGui::Separator();


			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(220, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Rage", 1, true);


			ImGui::Separator();

			ImGui::EndChild();
			ImGui::PopStyleColor();

		}


		if (tabb == 2)
		{

			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);

			ImGui::Text("Visuals", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Checkbox("Outlines", &outlines);
			
			ImGui::Spacing();
			ImGui::SliderInt3("Outline Bit", &outlinebit, 0,20); // max value 20 to make sure we can check every single bit (bit only will be up to 32 or 64 somtimes more than 1 bit change;
			ImGui::PopStyleColor();

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Visual Settings", 1, true);
			ImGui::Separator();

			ImGui::EndChild();
			ImGui::PopStyleColor();

		}



		if (tabb == 3)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);
			ImGui::Text("Exploits", 1, true);
			ImGui::Separator();

			ImGui::PopStyleColor();
			ImGui::EndChild();

			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Range", 1, true);
			ImGui::Separator();

			ImGui::EndChild();
			ImGui::PopStyleColor();
		}

		if (tabb == 4)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);

			ImGui::Text("Settings", 1, true);
			ImGui::Separator();





			ImGui::PopStyleColor();

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Color Settings", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Red", &red, 0, 255);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Green", &green, 0, 255);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Blue", &blue, 0, 255);

			ImGui::EndChild();
			ImGui::PopStyleColor();

		}




		ImGui::EndChild();
		ImGui::End();


	}







	//ImGui::EndFrame();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetViewD3D11, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}




LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD __stdcall InitializeHook(LPVOID)
{
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle("dxgi.dll");
		Sleep(4000);
	} while (!hDXGIDLL);
	Sleep(100);

	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

	IDXGISwapChain* pSwapChain;

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);


	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	// LibOVR 0.4.3 requires that the width and height for the backbuffer is set even if
	// you use windowed mode, despite being optional according to the D3D11 documentation.
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	UINT createFlags = 0;
#ifdef _DEBUG
	// This flag gives you some quite wonderful debug text. Not wonderful for performance, though!
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)
	))
	{
		MessageBox(hWnd, "Failed to create directX device and swapchain!", "Error", MB_ICONERROR);
		return false;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];

	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];

	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], hookD3D11Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { return 1; }


	return true;



	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	while (true) {
		Sleep(10);
	}

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	return NULL;
}

//==========================================================================================================================

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
		AllocConsole();         // create cmd
		FILE* pFile = nullptr;
		freopen_s(&pFile, "CONOUT$", "w", stdout);
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		SetConsoleTitle("R6 Example Source");
		std::cout << "DLL successfully injected." << std::endl; 


		//DisableThreadLibraryCalls(hModule);
		//GetModuleFileName(hModule, dlldir, 512);
		
		CreateThread(NULL, 0, InitializeHook, NULL, 0, NULL);
		break;


	}
	return TRUE;
}