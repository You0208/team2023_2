#include <fstream>
#include <algorithm>
#include "Scene.h"

int Scene::HighScore = 0;
int Scene::Point = 0;

// セーブファイルの読み取り
void Scene::InputSave()
{
	// ファイルの読み込み
	std::ifstream read;					// 読み出し用変数
	read.open(fileName);
	char command[256];

	// 読み込めた場合
	if (read)
	{
		while (read)
		{
			read >> command;
			if (0 == strcmp(command, "hs"))		// 先頭の文字が"hs"である場合
			{
				read.ignore(1);					// 1行開ける
				read >> HighScore;				// 数値代入
				read.ignore(1024, '\n');		// [\n(改行)]まで文字を削除する(最大1024文字)⇒次の行まで削除
			}
			if (0 == strcmp(command, "p"))		// 先頭の文字が"p"である場合
			{
				read.ignore(1);					// 1行開ける
				read >> Point;					// 数値代入
				read.ignore(1024, '\n');		// [\n(改行)]まで文字を削除する(最大1024文字)⇒次の行まで削除
			}
		}
	}
	read.close();
}

// セーブファイルの書き込み
void Scene::OutputSave()
{
	// ファイルの書き込み
	std::ofstream write;				// 書き出し用変数
	write.open(fileName);
	write << "hs " << HighScore << "\n";
	write << "p " << Point << "\n";
	write.close();
}

// ハイスコアの更新
void Scene::UpdateHighScore(const int score)
{
	HighScore = (std::max)(HighScore, score); 
}

// ハイスコアのリセット(書き込みも行う)
void Scene::ResetHighScore()
{
	HighScore = 0;
	OutputSave();
}