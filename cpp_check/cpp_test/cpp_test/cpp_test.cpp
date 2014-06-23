// cpp_test.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <list>
#include <algorithm>
#include <array>

void new_random_test();
void new_random_test2();
void new_random_test3();
void iterator_test();
void loop_test();
void lambda_test();
void emplacement_test();
void enum_class_test();
void array_test();

// enum class
// �����^�t���ƃX�R�[�v�̎w�肪�o����
enum class COLOR{
	Red,
	White
};

enum class NUMBER{
	ONE = 1,
	TWO = 2	
};

enum class ALIGN : char{
	Left = 'L',
	Center = 'C',
	Right = 'R',
};

int _tmain(int argc, _TCHAR* argv[])
{
	new_random_test();
	new_random_test2();
	new_random_test3();
	iterator_test();
	loop_test();
	lambda_test();
	emplacement_test();
	enum_class_test();
	array_test();
	return 0;
}

void new_random_test()
{
	std::cout << "-----new_random_test-----" << '\n';

	// �V����random�N���X���o�����炵���̂ŁA����̃e�X�g
	// �����āA�����������\�����������炵��
	std::mt19937 rng;
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng() << '\n';
	}

	std::cout << '\n';

	// �V�[�h�l�����߂ăe�X�g
	std::mt19937 rng2(1234);
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng2() << '\n';
	}

	std::cout << '\n';

	// �V�����z
	// ���S�ȗ��������A�x��
	std::random_device rng3;
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng3() << '\n';
	}
}

void new_random_test2()
{
	std::cout << "-----new_random_test2-----" << '\n';
	
	// ���p�I�Ȏg����
	// �V�[�h��random_device�ō���āA�����mt19937�̃V�[�h�ɂ���
	std::random_device rd;
	std::mt19937 rng(rd());
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng() << '\n';
	}
}

void new_random_test3()
{
	std::cout << "-----new_random_test3-----" << '\n';
	
	// ���p�I�Ȏg����
	// �w��͈͓��̕��z
	std::mt19937 rng;
	std::uniform_int_distribution<int> dist(1, 6);
	for(int i = 0; i < 10; i++)
	{
		std::cout << dist(rng) << '\n';
	}
		
	std::cout << '\n';
	
	std::uniform_real_distribution<double> dist2(-100.0, 100.0);
	for(int i = 0; i < 10; i++)
	{
		std::cout << dist2(rng) << '\n';
	}

	// �w��m����true��false���Ԃ�
	std::bernoulli_distribution dist3(0.5);
	if(dist3(rng))
	{
		std::cout << "true" << '\n';
	}
	else
	{
		std::cout << "false" << '\n';
	}

}

void iterator_test()
{
	// auto�́A�߂�ǂ������L�q�̂Ƃ��Ɏg�����B�������肷��
	std::cout << "-----iterator_test-----" << '\n';
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	auto ite = vec.begin();// �C�e���[�^�Ƃ��߂�ǂ��������ˁB

	for(ite; ite != vec.end(); ite++)
	{
		std::cout << *ite << '\n';
	}
}

void loop_test()
{
	std::cout << "-----loop_test-----" << '\n';
	// �P����for���[�v
	int scores[5] = {40, 60, 80, 100, 120};

	for(auto& score : scores)
	{
		score += 10;
	}

	for(const auto& score : scores)
	{
		std::cout << score << '\n';
	}

	// �C�e���[�^�����Ă�Ύg����炵����
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	std::list<int> list;
	list.push_back(50);
	list.push_back(55);
	list.push_back(60);
	
	std::string str = "test_string";

	// �R�s�[����������ꍇ�͎Q�Ƃ��\
	//for(auto n : vec)
	for(auto& n : vec)
	{
		std::cout << n << '\n';
	}

	for(auto n2 : list)
	{
		std::cout << n2 << '\n';
	}

	for(auto s : str)
	{
		std::cout << s << '\n';
	}
}

void lambda_test()
{
	std::cout << "-----lambda_test-----" << '\n';
	std::vector<int> v;
	for(int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	// �����_�̊�{�̏������͂����炵��
	// []()->T{}

	// count_if�͂�����������@�\�B�����ɐݒ肷��֐��Ƀ����_�����g���Ă���񂾂Ǝv��
	size_t x = std::count_if(v.begin(), v.end(), [](int n){ return n%2==0; });
	std::cout << x << '\n';

	// �֐��|�C���^�����ɂ��ł���񂾂�
	auto func = [](int n){ return n*n; };
	std::cout << func(9) << '\n';

	// �O���ɏ������ϐ�(y)���g����񂾂��āi�R�s�[�L���v�`���Ƃ������炵���j
	int y = 10;
	auto func2 = [=](int n){ return n*y; };
	std::cout << func2(11) << '\n';

	// �������́A�O�����Q�Ɠn���ł���炵��
	int z = 10;
	auto func3 = [&](int n){ return z*10; };
	std::cout << func3(0) << '\n';

	// �����_���o������łɁA�A���S���Y���ŕ֗��Ȃ��̂��o�����ق����悳��������ˁH
	// ��������ȉ��̂��̂�����
	std::vector<int> enemyhp;
	for(int i = 0; i < 10; i++)
	{
		enemyhp.push_back(i*5);
	}

	int delnum = 20;
	for(auto n : enemyhp)
	{
		std::cout << n << '\n';
	}

	// HP20�ȉ��̃f�[�^������
	enemyhp.erase(
		std::remove_if(
			enemyhp.begin(), enemyhp.end(), 
			[=](int n){ return n < delnum; }
		),
		enemyhp.end()
	);

	std::cout << '\n';

	for(auto n : enemyhp)
	{
		std::cout << n << '\n';
	}

}

void emplacement_test()
{
	std::cout << "-----emplacement_test-----" << '\n';

	// push_back���ƁA���Ԃ�����Ă���R�s�[�ɂȂ�炵��
	// ���������ƁA���ڂԂ����߂�炵��
	std::vector<std::string> vec;
	vec.emplace_back("10");
		
	const std::string str = "hello";
	vec.push_back(str);
	vec.emplace_back("hello");
	vec.emplace_back();
	vec.emplace_back(10, 'a');
	
	for(auto n : vec)
	{
		std::cout << n.c_str() << '\n';
	}
}
	
void enum_class_test()
{
	std::cout << "-----enum_class_test-----" << '\n';
	// �Öق̌^�ϊ�������Ȃ��B�ꍇ�ɂ���Ă͕s�ւ����H
	COLOR color = COLOR::Red;
	color = COLOR::White;
	//std::cout << color << '\n';// �G���[

	NUMBER number = NUMBER::ONE;
	number = NUMBER::TWO;
	//std::cout << number << '\n';// �G���[

	ALIGN align = ALIGN::Left;
	//char str = ALIGN::Center;// �G���[
	//std::cout << align << '\n';// �G���[
}
	
void array_test()
{
	std::cout << "-----array_test-----" << '\n';
	// �z��ɃC���^�[�t�F�[�X��񋟂��Ă����̂�array�炵��
	std::array<int, 5> ar1 = { 5, 10, 15, 20, 25 };
	std::array<int, 5> ar2;

	ar2.fill(100);// �v�f�S������
	ar1 = ar2;// �v�f���������Ȃ�A����\�炵��

	ar1[0] = 0;

	for(auto n : ar1)
	{
		std::cout << n << '\n';
	}
}
