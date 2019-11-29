#pragma once
#include "SDK/PluginSDK.h"
#include "SDK/EventHandler.h"
#include "SDK/clipper.hpp"
#include "SDK/EventArgs.h"
#include "SDK/Geometry.h"
#include "SDK/PluginSDK_Enums.h"
#include "SDK/Vector.h"
namespace MainSpace
{
	class Main
	{
	public:
		static void Load();
		static void UnLoad();
	};
	void CreateMenu();
	void CreateEvents();
	void GameOnUpdate();
}


