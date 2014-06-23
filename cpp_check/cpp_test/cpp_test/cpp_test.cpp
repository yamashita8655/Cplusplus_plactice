// cpp_test.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
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
// 強く型付けとスコープの指定が出来る
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

	// 新しいrandomクラスが出来たらしいので、それのテスト
	// 早くて、そこそこ性能がいい乱数らしい
	std::mt19937 rng;
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng() << '\n';
	}

	std::cout << '\n';

	// シード値を決めてテスト
	std::mt19937 rng2(1234);
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng2() << '\n';
	}

	std::cout << '\n';

	// 新しい奴
	// 完全な乱数だが、遅い
	std::random_device rng3;
	for(int i = 0; i < 10; i++)
	{
		std::cout << rng3() << '\n';
	}
}

void new_random_test2()
{
	std::cout << "-----new_random_test2-----" << '\n';
	
	// 実用的な使い方
	// シードをrandom_deviceで作って、それをmt19937のシードにする
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
	
	// 実用的な使い方
	// 指定範囲内の分布
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

	// 指定確立でtrueかfalseが返る
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
	// autoは、めんどくさい記述のときに使おう。すっきりする
	std::cout << "-----iterator_test-----" << '\n';
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	auto ite = vec.begin();// イテレータとかめんどくさい物ね。

	for(ite; ite != vec.end(); ite++)
	{
		std::cout << *ite << '\n';
	}
}

void loop_test()
{
	std::cout << "-----loop_test-----" << '\n';
	// 単純なforループ
	int scores[5] = {40, 60, 80, 100, 120};

	for(auto& score : scores)
	{
		score += 10;
	}

	for(const auto& score : scores)
	{
		std::cout << score << '\n';
	}

	// イテレータ持ってれば使えるらしいよ
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	std::list<int> list;
	list.push_back(50);
	list.push_back(55);
	list.push_back(60);
	
	std::string str = "test_string";

	// コピーを避けたい場合は参照も可能
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
	// ラムダの基本の書き方はこうらしい
	// []()->T{}

	// count_ifはそもそもある機能。そこに設定する関数にラムダ式を使っているんだと思う
	size_t x = std::count_if(v.begin(), v.end(), [](int n){ return n%2==0; });
	std::cout << x << '\n';

	// 関数ポインタ扱いにもできるんだね
	auto func = [](int n){ return n*n; };
	std::cout << func(9) << '\n';

	// 外部に書いた変数(y)も使えるんだって（コピーキャプチャとかいうらしい）
	int y = 10;
	auto func2 = [=](int n){ return n*y; };
	std::cout << func2(11) << '\n';

	// こっちは、外部を参照渡しできるらしい
	int z = 10;
	auto func3 = [&](int n){ return z*10; };
	std::cout << func3(0) << '\n';

	// ラムダ式覚えるついでに、アルゴリズムで便利なものを覚えたほうがよさそうじゃね？
	// 特定条件以下のものを消す
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

	// HP20以下のデータを消す
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

	// push_backだと、実態を作ってからコピーになるらしい
	// こっちだと、直接ぶっこめるらしい
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
	// 暗黙の型変換がされない。場合によっては不便かも？
	COLOR color = COLOR::Red;
	color = COLOR::White;
	//std::cout << color << '\n';// エラー

	NUMBER number = NUMBER::ONE;
	number = NUMBER::TWO;
	//std::cout << number << '\n';// エラー

	ALIGN align = ALIGN::Left;
	//char str = ALIGN::Center;// エラー
	//std::cout << align << '\n';// エラー
}
	
void array_test()
{
	std::cout << "-----array_test-----" << '\n';
	// 配列にインターフェースを提供してくれるのがarrayらしい
	std::array<int, 5> ar1 = { 5, 10, 15, 20, 25 };
	std::array<int, 5> ar2;

	ar2.fill(100);// 要素全初期化
	ar1 = ar2;// 要素数が同じなら、代入可能らしい

	ar1[0] = 0;

	for(auto n : ar1)
	{
		std::cout << n << '\n';
	}
}
