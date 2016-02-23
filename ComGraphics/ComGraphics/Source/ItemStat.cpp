#include "ItemStat.h"

ItemStat::ItemStat()
{
	i_Attack = 0;
	for (int i = 0; i < 4; ++i)
	{
		stats.push_back(ItemStat::i_Attack);
	}
}

ItemStat::ItemStat(float i_Attack)
{
	this->i_Attack = i_Attack;
}


ItemStat::~ItemStat()
{

}

void ItemStat::InsertItemStatSlot(ToolUI::ToolType Tool)
{
	for (std::list<ToolUI>::iterator it = TotalTools.begin(); it != TotalTools.end(); ++it)
	{
		for (std::list<ItemStat>::iterator ITS = stats.begin(); ITS != stats.end(); ++ITS)
		{
			if (Tool == ToolUI::Pickaxe)
			{
				ITS->i_Attack = 10;
			}

			else if (Tool == ToolUI::BaseballBat)
			{
				ITS->i_Attack = 15;
				break;
			}
		}

		if (it->tool = ToolUI::Empty)
		{
			break;
		}
	}

}

ItemStat ItemStat::StoreAttack(int SlotIndex)
{
	std::list<ItemStat>::iterator it = stats.begin();
	switch (SlotIndex)
	{
		case 1:
			/*this->i_Attack = 10;*/
			return it->i_Attack;
			break;
		case 2:
			std::advance(it, 1);
			/*this->i_Attack = 15;*/
			return it->i_Attack;
			break;
		case 3:
			std::advance(it, 2);
			/*this->i_Attack = 0;*/
			return it->i_Attack;
			break;
	}
}