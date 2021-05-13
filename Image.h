#ifndef IMAGE_H_
#define IMAGE_H_

#include "Game.h"
#include <assert.h>

class DivImage
{   // 3D�ɕ���Div�摜���g���Ɖ摜�S�̂��g���Ă��܂��̂�������邽�߂̏��
public:
    int XNum = 0;
    int YNum = 0;
    int XSize = 0;
    int YSize = 0;
    int* HandleArray = NULL;
    int AllNum = 0;
    DivImage(int XNum, int YNum, int XSize, int YSize)
    {   // �������R���X�g���N�^
        this->XNum = XNum;
        this->YNum = YNum;
        this->XSize = XSize;
        this->YSize = YSize;
        AllNum = XNum * YNum;
        // ��div�����摜�Ǎ��n���h���ۑ��p��int�z�񃁃������m�ۂ�-1�ŏ�����
        this->HandleArray = new int[AllNum]; // �z����m�ۂ�-1�ŏ�����
        for (int i = 0; i < AllNum; i++) HandleArray[i] = -1;
        //�����K����������̓��I�z����f�o�b�K�Ō��Ă݂悤[ary,256�Ƃ��čĕ]���{�^��]
        // http://visualstudiostudy.blog.fc2.com/blog-entry-17.html
        int* ary = HandleArray;
#ifdef _DEBUG // �f�o�b�O�@�\(�f�o�b�O�̎����� _DEBUG ����`)
        ImagePowCheck((*this)); // *(this)��this�|�C���^�̎����ϐ����e��\��
#endif
    };
    ~DivImage()
    {   // �f�X�g���N�^�Ń����������
        if (this->HandleArray != NULL)
            delete[] this->HandleArray;
    };
#ifdef _DEBUG // �f�o�b�O�@�\(�f�o�b�O�̎����� _DEBUG ����`)
    bool is_pow2(unsigned int x) // 2�ׂ̂��悩�v�Z
    {   // https://programming-place.net/ppp/contents/c/rev_res/math012.html
        return (x != 0) && (x & (x - 1)) == 0;
    }
    void ImagePowCheck(DivImage& divImage)
    {   // ��3D�Ɏg���摜��2�ׂ̂���łȂ���Ύ󂯕t���Ȃ��悤�ɂ���
        // https://yttm-work.jp/gmpg/gmpg_0031.html
        // https://yappy-t.hatenadiary.org/entry/20100110/1263138881
        if (divImage.XSize > 0 && divImage.YSize > 0
            && is_pow2(divImage.XSize) && is_pow2(divImage.YSize)) return;
        else assert("3D�Ɏg���Ȃ�2�ׂ̂���̉摜�T�C�Y�ɂ��Ȃ���" == "");
    }
#endif
private: // �R�s�[�Ƒ�����v���C�x�[�g�ɂ��ċ֎~����
    //�R�s�[�R���X�g���N�^
    DivImage(const DivImage& divImage) {};

    //������Z�q�̃I�[�o�[���[�h
    DivImage& operator=(const DivImage& divImage) {};
};

class Image
{
public:
	Image() {}; // �����R���X�g���N�^�̒�`����
	~Image() {}; // �j�����鏈���f�X�g���N�^�̒�`����
	static void Load();
    static int LoadDivGraph(const TCHAR* FileName, DivImage& divImage, int NotUse3DFlag = FALSE);

    static int player; // �v���C���[
    static int playerBullet; // �v���C���[�̒e
    static int zako0; // �U�R0
    static int zako1; // �U�R1
    static int zako2; // �U�R2
    static int zako3; // �U�R3
    static int enemyBullet16; // �G�e
    static DivImage explosion; // �����G�t�F�N�g
    static int boss1; // �{�X�ʏ펞
    static int boss2; // �{�X�C��
    static int boss3; // �{�X����
    static int back;  // �w�i
    static int title; // �^�C�g��
    static int gameover; // �Q�[���I�[�o�[
    static int gameclear; // �Q�[���N���A
    static int pushbuttontostart; // �X�^�[�g�{�^��
    static int life1; // ���C�t
    static int item1; // �A�C�e��
    static int messagewindow; // ���b�Z�[�W�E�B���h�E
    static int character; // �v���C���[�����G
    static int kyokan; // ���������G
    static int cutin; // �J�b�g�C�� 
};

#endif // !IMAGE_H_

