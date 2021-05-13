#ifndef MAP_H_
#define MAP_H_

#include <map>
#include <vector>

#include "GameManager.h"
#include "GameObject.h"
#include "DataCsv.h"

#include "Zako0.h"
#include "Zako1.h"
#include "Zako2.h"
#include "Zako3.h"
#include "Boss.h"
#include "Item1.h"

class Map
{
public:
	//���y����҃p�^�[���z�Q�[�����̂��̓��m�̓}�l�[�W����ʂ��Ĉꌳ�����Ă����
	GameManager& gm = GameManager::GetInstance(); //�B��̃Q�[���}�l�[�W���ւ̎Q��(&)�𓾂�

	// �}�X�ڂ�X��Y��ێ�����f�[�^�^
	struct CellXY
	{
		int X = 0;
		int Y = 0;

		CellXY(int X, int Y) : X{ X }, Y{ Y }
		{};
		// ���A�z�z��Ŏg������ < ��r���Z�q(�A�z�z����בւ��̂���)���J�X�^����`
		// http://programming-tips.info/use_struct_as_key_of_map/cpp/index.html
		bool operator < (const CellXY& otherXY) const {
			if (Y < otherXY.Y) return true; // Y�D����בւ�
			if (Y > otherXY.Y) return false;
			if (X < otherXY.X) return true; // Y����������X���r
			if (X > otherXY.X) return false;
			return false; // ���S��v�̂Ƃ���
		}
	};

	int SpawnRangeX = 30; // �G�o���˒��X�|�[�������W�y���ӁIX�̒P�ʂ̓}�X�ځz
	int SpawnRangeY = 30; // �G�o���˒��X�|�[�������W�y���ӁIY�̒P�ʂ̓}�X�ځz
	// ���y�ő����_��?�A�z�z��zhttps://qiita.com/_EnumHack/items/f462042ec99a31881a81
	std::map<CellXY, bool> SpawnDic; // ����:SpawnDic["10,5"]==true�Ȃ�o���͈� 


	const int CellSize = 32; // �}�b�v��1�}�X�̃s�N�Z����

	std::vector<std::vector<int>> terrain; // �n�`�f�[�^
	int TerrainWidth = 0; // �}�b�v�f�[�^�̉��̃}�X��
	int TerrainHeight = 0; // �}�b�v�f�[�^�̏c�̃}�X��

	// ���������z���vector�C��vector��
	// https://atcoder.jp/contests/APG4b/tasks/APG4b_t
	DataCsv enemyData; // �G�z�u�f�[�^

	float positionX = 0; // ���݂̈ʒu�i�}�b�v���[�̍��W�j
	float positionY = 0; // ���݂̈ʒu�i�}�b�v��[�̍��W�j

	float deltaSumX = 0; // deltaX�̕ω������܂��ă}�X�ڂ��ړ����������邩�̔���̌v�Z�Ɏg��
	float deltaSumY = 0; // deltaY�̕ω������܂��ă}�X�ڂ��ړ����������邩�̔���̌v�Z�Ɏg��

	// �R���X�g���N�^
	// startPosition : �J�n�ʒu�i�f�o�b�O�⃊�X�^�[�g���ɁA�ʂ̓r������J�n�ł���悤�Ɂj
	// filePath : CSV�t�@�C���̃p�X
	Map(float startPosition, std::string stageName);

	// �f�X�g���N�^
	~Map()
	{
		// �}�b�v�f�[�^�̂��|��
		enemyData.clear();
		//terrain.clear();
	}

	// �G�o���˒��̎����������y��Ɍv�Z���Ď������z����ƌv�Z���K�v�Ȃ��Ȃ�y����������z
	//�y���ӁIX��Y�̒P�ʂ̓}�X�ځz
	void InitSpawnDic(int rangeCellX, int rangeCellY);

	// ��ʃX�N���[���i�ʒu�̍X�V�j
	//void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL);
	void Scroll(float delta);

	// �I�u�W�F�N�g�𐶐��E�z�u����
	//void SpawnObject(int mapX, int mapY, int objectID);
};

#endif // !MAP_H_
