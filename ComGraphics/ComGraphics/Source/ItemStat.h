#ifndef ITEMSTAT_H
#define ITEMSTAT_H

#include "ToolSection.h"

class ItemStat : public ToolSection
{
public:
	ItemStat();
	ItemStat(float i_Attack);
	~ItemStat();

	void InsertItemStatSlot(ToolUI::ToolType Tool);
	ItemStat ItemStat::StoreAttack(int SlotIndex);

	int i_Attack;

	std::list<ItemStat> stats;
};

#endif