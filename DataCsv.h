#ifndef DATACSV_H_
#define DATACSV_H_

#include <memory>
#include <vector>
#include <string>

#include <fstream> // �t�@�C���ǂݏo��ifstream�ɕK�v
#include <string> //������ɕK�v
#include <sstream> // ������X�g���[���ɕK�v

#include <assert.h> // �}�b�v�Ǎ��ݎ��s�\���p

// CSV�t�@�C����Ǎ��ݕ��⍂���ƃf�[�^�{�̂�ێ�����f�[�^�^
struct DataCsv
{   // �Ǎ��񂾃f�[�^�t�@�C���̏��
    std::string FilePath = "";
    int Width = 0; // csv�t�@�C���̕\�̕�
    int Height = 0;// csv�t�@�C���̕\�̍���
    std::vector<std::vector<int>> Data;// csv�f�[�^
    // ���X���[�Y��[][]�ŃA�N�Z�X�ł���悤��[]���Z�q��Ǝ���`����
    std::vector<int>& operator[](std::size_t index) { // �� &�Q�Ƃɂ��Ȃ��Ƃ��������f�[�^�̃R�s�[��Ԃ��̂Œx���Ȃ��
        return Data[index]; // ��������
    }
    std::vector<int> operator[](std::size_t index) const { // ��const�͓Y����[]�ǂݎ��̏������`
        return Data[index]; // �ǂݎ��
    }

    std::size_t size()
    {   // size()�֐��̖��O��vector�Ɣ�点�邱�ƂŎg������vector�C��vector�̂܂܂̃R�[�h�Ŏg����
        return Data.size();
    }
    // �������R���X�g���N�^�Ńt�@�C�������w�肵�ď������Ɠ����Ƀt�@�C���Ǎ�
    DataCsv(std::string FilePath = "") :FilePath{ FilePath }
    {// csv�t�@�C���̓Ǎ��݁��y�������Ɠ����Ȃ̂Ńt�@�C���ƃf�[�^�^����S���̂Ŏg���₷���z
        if (FilePath != "") Load(FilePath); // �t�@�C���Ǎ���
    };
    virtual ~DataCsv()
    {// ���z�f�X�g���N�^
        Data.clear();// 2�����z��f�[�^�̂��|��
    };

    // �f�[�^���N���A���ă�������ߖ񂷂�
    virtual void clear()
    {   // �f�[�^���N���A���ă�������ߖ񂷂�
        Data.clear();// 2�����z��f�[�^�̂��|��
    }

    // csv�t�@�C���̓ǂݍ���
    void Load(std::string filePath)
    {
        if (filePath == "") return; //�t�@�C�������Ȃ�
        FilePath = filePath; // �t�@�C������ۊ�
        Data.clear(); //�f�[�^����U�N���A
        // �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
        std::ifstream ifs_csv_file(filePath);
        std::string line; //1�s�P�ʂ̓Ǎ��ݕ�����

        int readWidth = 0; //�Ǎ��݃f�[�^�̕�
        int maxWidth = 0; //������ǂݍ��񂾎���MAX�̕�
        int readHeight = 0; //������
        while (std::getline(ifs_csv_file, line)) // �t�@�C�����s���Ƃɓǂݍ���
        {
            std::vector<int> numlist; // 1�s�̐������X�g
            std::istringstream linestream(line); // �e�s�̕�����X�g���[��
            std::string splitted; // �J���}����������
            int widthCount = 0; //���̍s�̕����J�E���g
            while (std::getline(linestream, splitted, { ',' }))
            {
                std::istringstream ss; //������X�g���[���̏�����
                ss = std::istringstream(splitted); //������X�g���[��
                int num; // �����P��
                ss >> num; // ������X�g���[�����琔���ւ̕ϊ�
                numlist.push_back(num); // �����𐔎��̃��X�g(1�s���X�g)�ɒǉ�
                widthCount++; //���̍s�̕����J�E���g�A�b�v
            }
            if (widthCount > maxWidth) maxWidth = widthCount; //�b��Max�����X�V

            // 1�s����vector�ɒǉ�
            if (numlist.size() != 0) Data.push_back(numlist);
            readHeight++; //�}�b�v�̍������J�E���g�A�b�v
        }
        readWidth = maxWidth; //MAX���̉��҂��m��

        assert(readWidth > 0); // �}�b�v������������
        assert(readHeight > 0); // �}�b�v��������������

        this->Width = readWidth; // �Ǎ��ݐ��������f�[�^�̕����L�^
        this->Height = readHeight; // �Ǎ��ݐ��������f�[�^�̍������L�^

        return;
    }
};

#endif // !DATACSV_H_
