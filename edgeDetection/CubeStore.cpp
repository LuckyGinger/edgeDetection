#include "CubeStore.h"

CubeStore::CubeStore()
{
}


CubeStore::~CubeStore()
{
}

void CubeStore::saveCube()
{
	ofstream outSaveCube(CubeCube::saveFileName);

	for (int i = 0; i < MAX_FACES; i++)
	{
		for (int j = 0; j < cube[i].getMaxColors(); j++)
		{
			outSaveCube << cube[i].getColors(j).getTypeChar();
		}
		outSaveCube << endl;
	}
	outSaveCube.close();
	return;
}