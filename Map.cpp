#include "Map.h"

Map::Map(float startPosition, std::string stageName)
{
	positionX = startPosition;

	enemyData.Load("Map/" + stageName + ".csv");

	assert(SpawnRangeX > 0 && SpawnRangeY > 0); // �����ƓG�o���˒���ݒ肵�Ă�
	// �G�o���˒��̎���������
	InitSpawnDic(SpawnRangeX, SpawnRangeY);
}

// �G�o���˒��̎����������y��Ɍv�Z���Ď������z����ƌv�Z���K�v�Ȃ��Ȃ�y����������z
   //�y���ӁIX��Y�̒P�ʂ̓}�X�ځz
void Map::InitSpawnDic(int rangeCellX, int rangeCellY)
{
	SpawnDic.clear();//��U�������N���A����̂ŃQ�[�����̍Đݒ����(�����������Ԃ͂�����)
	// �G�o���˒��̎���������
	// �� X = A cos�� Y = B sin��(���ȉ~�̕�����)
	// �� �ȉ~�̔��a r = ��(A�~A�~cos�Ɓ~cos�� + B�~B�~sin�Ɓ~sin��)
	// �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
	float A2 = (float)(rangeCellX * rangeCellX); // 2��
	float B2 = (float)(rangeCellY * rangeCellY); // 2��
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{   //��[�t�O�p�֐�] https://cpprefjp.github.io/reference/cmath/atan2.html
			float theta = (float)std::atan2(y, x); // ��[�t�O�p�֐�]
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t * cos_t + B2 * sin_t * sin_t;
			if (x * x + y * y <= r2) // �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
			{   //�ȉ~�̓����Ȃ玫��SpawnDic[(x,y)] = true;�Ƃ��ēo�^
				//�y���ȉ~�ɂ������Ƃ��͂�����zSpawnDic[CellXY(x,y)] = true; //�y��zSpawnDic[(3,2)] = true;
			}
			//�y���l�p�`�ɂ������Ƃ��͂�����z
			SpawnDic[CellXY(x, y)] = true;
		}
	}
}

void Map::Scroll(float delta)
{
	// �X�N���[������O�́A��ʉE�[�̃Z���̗�ԍ��ix�j
	int prevRightCell = (int)(Map::positionX + Screen::Width) / CellSize;

	positionX += delta; // �X�N���[������

	// �X�N���[��������́A��ʉE�[�̃Z���̗�ԍ��ix�j
	int currentRightCell = (int)(positionX + Screen::Width) / CellSize;

	// �X�N���[��������̉�ʉE�[�̃Z�����}�b�v�͈̔͊O�ɏo��������牽�����Ȃ��ŏI��
	if (currentRightCell >= enemyData.Width)
		return;

	// �X�N���[������O�ƌ�ŁA��ʉE�[�̃Z���������ꍇ�́A�������Ȃ��ŏI��
	if (prevRightCell == currentRightCell)
		return;

	// ��ʉE�[�̃Z���̍��[��x���W
	float x = currentRightCell * CellSize - positionX;

	// ��[�̃Z�����牺�[�̃Z���܂��r�߂āA�G�f�[�^���z�u����Ă�����A�G�𐶐�����
	for (int cellY = 0; cellY < enemyData.Height; cellY++)
	{
		float y = float(cellY * CellSize);

		int id = enemyData.Data[cellY][currentRightCell];


		// �ԍ��ɉ����ēG�𐶐�����
		if (id == -1) continue; // -1�͋󔒂Ȃ̂ŁA�������Ȃ�
		else if (id == 0) gm.enemies.push_back(std::make_shared<Zako0>(x + 32, y + 32));
		else if (id == 1) gm.enemies.push_back(std::make_shared <Zako1>(x + 32, y + 32));
		else if (id == 2) gm.enemies.push_back(std::make_shared <Zako2>(x + 32, y + 32));
		else if (id == 3) gm.enemies.push_back(std::make_shared <Zako3>(x + 32, y + 32));
		else if (id == 50) gm.items.push_back(std::make_shared<Item1>(x + 32, y + 32));
		else if (id == 100) gm.enemies.push_back(std::make_shared <Boss>(x + 90, y + 32)); // �{�X�͉���180px������90px�E�ɐ���	
	}

}