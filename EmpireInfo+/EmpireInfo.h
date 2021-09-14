#pragma once

#include <Spore\BasicIncludes.h>

#define EmpireInfoPtr intrusive_ptr<EmpireInfo>

class EmpireInfo 
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("EmpireInfo_Object");
	
	EmpireInfo();
	~EmpireInfo();
	int totalSystemsColonized = 0;
	int systemsColonized = 0;
	UILayoutPtr win;

	int AddRef() override;
	int Release() override;
	void Update() override;
	void* Cast(uint32_t type) const override;
};
