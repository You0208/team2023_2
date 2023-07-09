#include <fstream>
#include <algorithm>
#include "Scene.h"

int Scene::HighScore = 0;
int Scene::Point = 0;

// �Z�[�u�t�@�C���̓ǂݎ��
void Scene::InputSave()
{
	// �t�@�C���̓ǂݍ���
	std::ifstream read;					// �ǂݏo���p�ϐ�
	read.open(fileName);
	char command[256];

	// �ǂݍ��߂��ꍇ
	if (read)
	{
		while (read)
		{
			read >> command;
			if (0 == strcmp(command, "hs"))		// �擪�̕�����"hs"�ł���ꍇ
			{
				read.ignore(1);					// 1�s�J����
				read >> HighScore;				// ���l���
				read.ignore(1024, '\n');		// [\n(���s)]�܂ŕ������폜����(�ő�1024����)�ˎ��̍s�܂ō폜
			}
			if (0 == strcmp(command, "p"))		// �擪�̕�����"p"�ł���ꍇ
			{
				read.ignore(1);					// 1�s�J����
				read >> Point;					// ���l���
				read.ignore(1024, '\n');		// [\n(���s)]�܂ŕ������폜����(�ő�1024����)�ˎ��̍s�܂ō폜
			}
		}
	}
	read.close();
}

// �Z�[�u�t�@�C���̏�������
void Scene::OutputSave()
{
	// �t�@�C���̏�������
	std::ofstream write;				// �����o���p�ϐ�
	write.open(fileName);
	write << "hs " << HighScore << "\n";
	write << "p " << Point << "\n";
	write.close();
}

// �n�C�X�R�A�̍X�V
void Scene::UpdateHighScore(const int score)
{
	HighScore = (std::max)(HighScore, score); 
}

// �n�C�X�R�A�̃��Z�b�g(�������݂��s��)
void Scene::ResetHighScore()
{
	HighScore = 0;
	OutputSave();
}