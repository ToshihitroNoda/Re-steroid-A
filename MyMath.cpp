#include "MyMath.h"

// ���w�֘A�N���X

const float MyMath::Sqrt2{ 1.41421356237f };
const float MyMath::PI{ 3.14159265356f };
const float MyMath::Deg2Rad{ PI / 180.0f };

/// <summary>
   /// �~�Ɖ~���d�Ȃ��Ă��邩�𒲂ׂ�
   /// </summary>
   /// <param name="x1">�~1�̒��Sx</param>
   /// <param name="y1">�~1�̒��Sy</param>
   /// <param name="radius1">�~1�̔��a</param>
   /// <param name="x2">�~2�̒��Sx</param>
   /// <param name="y2">�~2�̒��Sy</param>
   /// <param name="radius2">�~2�̔��a</param>
   /// <returns>�d�Ȃ��Ă����ture�A�d�Ȃ��Ă��Ȃ����false��ԋp����</returns>
bool MyMath::CircleCircleIntersection(
    float x1, float y1, float radius1,
    float x2, float y2, float radius2) 
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
        < ((radius1 + radius2) * (radius1 + radius2));
};

/// <summary>
    /// �_����_�ւ̊p�x�i���W�A���j�����߂�B
    /// </summary>
    /// <param name="fromX">�n�_x</param>
    /// <param name="fromY">�n�_y</param>
    /// <param name="toX">�I�_x</param>
    /// <param name="toY">�I�_y</param>
    /// <returns></returns>
float MyMath::PointToPointAngle(
    float fromX, float fromY, 
    float toX, float toY)
{
    return (float)atan2(toY - fromY, toX - fromX);
};

