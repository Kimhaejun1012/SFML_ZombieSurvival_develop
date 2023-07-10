#include "stdafx.h"
#include "ZombieTable.h"
#include "rapidcsv.h"


const ZombieInfo& ZombieTable::Get(Zombie::Types id)
{
	auto find = table.find(id);
	if(find == table.end())
	{
		std::cout << "좀비 못찾았음" << std::endl;
	}

	return find->second;
}

bool ZombieTable::Load()
{
	std::string zombiefile = "tables/ZombieTypes.csv";
	ZombieInfo zombieinfo;

	rapidcsv::Document doc(zombiefile);
	std::vector<int> ids = doc.GetColumn<int>(0);
	std::vector<std::string> zombieID = doc.GetColumn<std::string>(1);
	std::vector<float> zombieSpeed = doc.GetColumn<float>(2);
	std::vector<int> zombieHP = doc.GetColumn<int>(3);
	std::vector<int> zombieDamage = doc.GetColumn<int>(4);
	std::vector<float> attactRate = doc.GetColumn<float>(5);

	for (int i = 0; i < ids.size(); ++i)
	{
		zombieinfo.zombieType = (Zombie::Types)ids[i];
		zombieinfo.textureId = zombieID[i];
		zombieinfo.speed = zombieSpeed[i];
		zombieinfo.maxHP = zombieHP[i];
		zombieinfo.damage = zombieDamage[i];
		zombieinfo.attackRate = attactRate[i];
		
		table.insert({(Zombie::Types)ids[i] ,zombieinfo});
	}
	return true;
}

void ZombieTable::Release()
{
	table.clear();
}

