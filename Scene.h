#pragma once

// �V�[��
class Scene
{
protected:
	// SceneOver��SceneClear�̗����Ŏg���̂�Scene�ɂ����Ă���
	static constexpr float PointPositionX = 1524.0f;    // �ǉ��|�C���g�ʒu(X)
	static constexpr float PointPositionY = 122.0f;      // �ǉ��|�C���g�ʒu(Y)
	static  float AddPointMoveAmount;// �ǉ��|�C���g�ړ���
	static constexpr float rate = 0.005f;
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
	static constexpr char* fileName = "Data/Save/Save.txt";	// �J���t�@�C����

	// �n�C�X�R�A�̍X�V
	static void UpdateHighScore(const int score);

	// �n�C�X�R�A�̃��Z�b�g(�������݂��s��)
	static void ResetHighScore();
public:
	// �Z�[�u�t�@�C���̓ǂݎ��
	static void InputSave();

	// �Z�[�u�t�@�C���̏�������
	static void OutputSave();

private:
	bool	ready = false;
};
