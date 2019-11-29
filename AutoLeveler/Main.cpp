#include "Main.h"

namespace MainSpace
{
	IMenu* MainMenu = nullptr;
	IMenuElement* SpellOrder = nullptr;
	IMenuElement* Enabled = nullptr;
	void Main::Load()
	{
		CreateMenu();
		Enabled->SetBool(false);
		CreateEvents();
		g_Common->ChatPrint("AutoLeveler loaded by xDreamms.");
	}

	void Main::UnLoad()
	{
		EventHandler<Events::GameUpdate>::RemoveEventHandler(GameOnUpdate);
		MainMenu->Remove();
		g_Log->Print("xDreamms AutoLeveler unloaded.");
	}

	void CreateMenu()
	{
		MainMenu = g_Menu->CreateMenu("Auto Leveler by xDreamms", "AutoLeveler");

		const auto SettingsMenu = MainMenu->AddSubMenu("Settings", "Settings");
		SpellOrder = SettingsMenu->AddComboBox("Spell order: ", "SpellOrder", std::vector<std::string>{"Q-E-W", "Q-W-E", "W-Q-E", "W-E-Q", "E-Q-W", "E-W-Q"}, 0);
		Enabled = SettingsMenu->AddCheckBox("Enabled", "Enabled", false);
	}

	void CreateEvents()
	{
		EventHandler<Events::GameUpdate>::AddEventHandler(GameOnUpdate);
	}
	std::vector<std::string> QEW{ "Q","E","W","Q","Q","R","Q","E","Q","E","R","E","E","W","W","R","W","W" };
	std::vector<std::string> QWE{ "Q","W","E","Q","Q","R","Q","W","Q","W","R","W","W","E","E","R","E","E" };
	std::vector<std::string> WQE{ "W","Q","E","W","W","R","W","Q","W","Q","R","Q","Q","E","E","R","E","E" };
	std::vector<std::string> WEQ{ "W","E","Q","W","W","R","W","E","W","E","R","E","E","Q","Q","R","Q","Q" };
	std::vector<std::string> EQW{ "E","Q","W","E","E","R","E","Q","E","Q","R","Q","Q","W","W","R","W","W" };
	std::vector<std::string> EWQ{ "E","W","Q","E","E","R","E","W","E","W","R","W","W","Q","Q","R","Q","Q" };
	void GameOnUpdate()
	{
		if (Enabled->GetBool())
		{
			for (int i = 19 - g_LocalPlayer->Level(); i > 0; i--)
			{
				std::string levelUpSkill = "";
				switch (SpellOrder->GetInt())
				{
				case 0:
					levelUpSkill = QEW.at(g_LocalPlayer->Level() - 1);
					break;
				case 1:
					levelUpSkill = QWE.at(g_LocalPlayer->Level() - 1);
					break;
				case 2:
					levelUpSkill = WQE.at(g_LocalPlayer->Level() - 1);
					break;
				case 3:
					levelUpSkill = WEQ.at(g_LocalPlayer->Level() - 1);
					break;
				case 4:
					levelUpSkill = EQW.at(g_LocalPlayer->Level() - 1);
					break;
				case 5:
					levelUpSkill = EWQ.at(g_LocalPlayer->Level() - 1);
					break;
				}

				if (levelUpSkill == "Q")
					g_LocalPlayer->LevelUpSpell(SpellSlot::Q);
				if (levelUpSkill == "W")
					g_LocalPlayer->LevelUpSpell(SpellSlot::W);
				if (levelUpSkill == "E")
					g_LocalPlayer->LevelUpSpell(SpellSlot::E);
				if (levelUpSkill == "R")
					g_LocalPlayer->LevelUpSpell(SpellSlot::R);
			}
		}
	}


}
