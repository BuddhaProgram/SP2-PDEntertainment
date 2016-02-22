#include "ItemStat.h"

ItemStat::ItemStat()
{
}

ItemStat::ItemStat(float i_Attack)
{
	this->i_Attack = i_Attack;
}


ItemStat::~ItemStat()
{

}

int ItemStat::InsertItemStatSlot(ToolUI::ToolType Tool)
{
	for (std::list<ToolUI>::iterator ITS = TotalTools.begin(); ITS != TotalTools.end(); ++ITS)
	{
		if (Tool == ToolUI::Pickaxe)
		{
			i_Attack = 10;
		}

		else if (Tool == ToolUI::Torchlight)
		{
			i_Attack = 15;
		}

		else if (Tool == ToolUI::Empty)
		{
			i_Attack = 0;
		}
	}

	return (int)i_Attack;
}