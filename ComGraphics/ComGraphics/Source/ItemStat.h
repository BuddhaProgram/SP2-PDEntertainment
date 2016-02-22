#ifndef ITEMSTAT_H
#define ITEMSTAT_H

#include "ToolSection.h"

class ItemStat : public ToolSection
{
public:
	ItemStat();
	ItemStat(float i_Attack);
	~ItemStat();

	int InsertItemStatSlot(ToolUI::ToolType Tool);


	float i_Attack;
};

#endif