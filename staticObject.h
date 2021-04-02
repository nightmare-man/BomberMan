#pragma once
class Image;
class StaticObject {
public:
	//����
	//��̬��Ʒ ��������ը������ ש�� ը�� ����� ���ߣ����ޣ�
	//��̬��Ʒ ��ɫ

	//����ʱ�Ȼ��Ʊ��� �ٻ��� ��̬��Ʒ/��̬��Ʒ  (��̬��Ʒ�ֲַ� �ȵ��� ��ש��)
	enum Flag {
		F_WALL=(1<<0),//������ ������ը��
		F_BRICK=(1<<1),//ש��
		F_ITEM_BOMB=(1<<2),//ը��
		F_ITEM_POWER=(1<<3)//�����
	};
	enum O_ID {
		I_1P,
		I_2P,
		I_ITEM_BOMB,
		I_ITEM_POWER,
		I_EXPLODE_ROW,
		I_EXPLODE_COL,
		I_ENEMY,
		I_WALL,
		I_BRICK,
		I_BACK,
		I_BOMB,
		I_EXPLODE_CEN
	};
	StaticObject();
	~StaticObject();
	void draw(int x, int y, const Image*)const;
	bool checkFlag(unsigned)const;
	void setFlag(unsigned);
	void resetFlag(unsigned);
private:
	unsigned mFlag;
	static const int OBJECT_LEN = 16;
};
