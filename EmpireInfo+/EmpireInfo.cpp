#include "stdafx.h"
#include "EmpireInfo.h"

EmpireInfo::EmpireInfo()
{
}


EmpireInfo::~EmpireInfo()
{
}

// For internal use, do not modify.
int EmpireInfo::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int EmpireInfo::Release()
{
	return DefaultRefCounted::Release();
}

void EmpireInfo::Update()
{
	if (!Simulator::IsSpaceGame()) 
	{
		systemsColonized = 0;
		totalSystemsColonized = 0;
		if (win != nullptr && WindowManager.GetMainWindow()->FindWindowByID(id("EmpireInfo")))
		{
			WindowManager.GetMainWindow()->RemoveWindow(WindowManager.GetMainWindow()->FindWindowByID(id("EmpireInfo")));
		}
		win = nullptr;
		return; 
	}
	
	if (win == nullptr) 
	{
		win = new UTFWin::UILayout;
		win->LoadByID(id("EmpireInfoSPUI"));//id("tooltips"));
		
		win->FindWindowByID(0x03754E6C)->SetControlID(id("EmpireInfo"));
	}
	auto anchorWindow = WindowManager.GetMainWindow()->FindWindowByID(0x034C963F);
	if (WindowManager.GetMainWindow()->FindWindowByID(id("EmpireInfo")) && anchorWindow != nullptr)
	{
		UTFWin::IWindow* empInfoWindow = WindowManager.GetMainWindow()->FindWindowByID(id("EmpireInfo"));
		string16 colonyString;
		colonyString.assign_convert(to_string(totalSystemsColonized));
		colonyString = u"Total colonies: " + colonyString;
		empInfoWindow->SetCaption(colonyString.c_str());

		auto colonies = Simulator::SpacePlayerData::Get()->mPlayerColonies.size();
		if (totalSystemsColonized != 0)
		{
			if (totalSystemsColonized < colonies)
			{
				systemsColonized -= totalSystemsColonized - colonies;

			}
		}

		//App::ConsolePrintF(to_string(systemsColonized).c_str());
		//App::ConsolePrintF(to_string(totalSystemsColonized).c_str());
		//auto anchorArea = anchorWindow->GetRealArea();
		win->SetParentWindow(anchorWindow);

		totalSystemsColonized = Simulator::SpacePlayerData::Get()->mPlayerColonies.size();
		string16 allSystemsString;
		allSystemsString.assign_convert(to_string(Simulator::GetPlayerEmpire()->mStars.size()));
		allSystemsString = u"\nTotal systems: " + allSystemsString;

		colonyString += allSystemsString;

		string16 newColonyString;

		newColonyString.assign_convert(to_string(systemsColonized));
		newColonyString = u"\nNew colonies: " + newColonyString;

		colonyString += newColonyString;

		empInfoWindow->SetCaption(colonyString.c_str());
		empInfoWindow->SetArea(Math::Rectangle(25, -32, 220, 26));
		anchorWindow->SetFlag(UTFWin::WindowFlags::kWinFlagClip, false);
		//SporeDebugPrint("%i", 10 + 5 * colonyString.length());
	}
}

// You can extend this function to return any other types your class implements.
void* EmpireInfo::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(EmpireInfo);
	return nullptr;
}
