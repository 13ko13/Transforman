#pragma once

/// <summary>
/// 2D�x�N�g���N���X
/// </summary>
struct Vector2
{
	float x, y;
	float Length()const;//�x�N�g���̑傫��
	void Normalize();//�x�N�g���̑傫����1�ɂ���
	Vector2 Normalized() const;///�傫�����P�ɂ����x�N�g����Ԃ�
	Vector2 operator-()const;///�x�N�g���𔽓]�����x�N�g����Ԃ�
	//���Z�q�I�[�o�[���[�h
	void operator+=(const Vector2& val);///���Z
	void operator-=(const Vector2& val);///���Z
	void operator*=(const float scale);///�x�N�g����n�{����
	Vector2 operator+(const Vector2& val)const;///���Z
	Vector2 operator-(const Vector2& val)const;///���Z
	Vector2 operator*(float scale)const;///�x�N�g���̏�Z
};

//���W���x�N�^�[�Ƃ��Ĉ���
using Position2 = Vector2;

/// <summary>
/// 2D�̃T�C�Y���`����\����
/// </summary>
struct Size
{
	int w;///��
	int h;///����
};

struct Circle
{
	Position2 pos;//�~�̒��S�_
	float r;//�~�̔��a
	void Draw();	//�~�̕`��
};

