#pragma once

// �V�[��
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// ������
	virtual void Initialize() = 0;

	// �I����
	virtual void Finalize() = 0;

	// �X�V����
	virtual void Update(float elapsedTime) = 0;

	// �`�揈��
	virtual void Render() = 0;

	// �����������Ă��邩
	bool IsReady() const { return ready; }

	// ���������ݒ�
	void SetReady() { ready = true; }

protected:
	static int HighScore;											//	�n�C�X�R�A
	static int Point;												// �|�C���g
	static constexpr char* fileName = "Data/Save/HighScore.txt";	// �J���t�@�C����

	// �n�C�X�R�A�̓ǂݎ��
	static void InputHighScore();

	// �n�C�X�R�A�̏�������
	static void OutputHighScore();

	// �n�C�X�R�A�̍X�V
	static void UpdateHighScore(const int score);

	// �n�C�X�R�A�̃��Z�b�g(�������݂��s��)
	static void ResetHighScore();

private:
	bool	ready = false;
};
