#include "Graphics/Graphics.h"
#include "ResourceManager.h"

// ���f�����\�[�X�ǂݍ���[21]
std::shared_ptr<ModelResource> ResourceManager::LoadModelResource(const char* filename)
{
    // ���f������
    // ���������炻��model��Ԃ�
    ModelMap::iterator it = models.find(filename);
    // ���������ꍇ
    if (it != models.end())
    {
        // �����N���؂�Ă��Ȃ��ꍇ
        if (it->second.expired() == false)
        {
            return it->second.lock();
        }
    }

    // �V�K���f�����\�[�X�쐬���ǂݍ���
    std::shared_ptr<ModelResource>	model;
    model = std::make_shared<ModelResource>();
    model->Load(Graphics::Instance().GetDevice(), filename);
 
    // �}�b�v�ɓo�^
    // �L�[���o�^����Ă��Ȃ���Α}�����A����Α������
    models.insert_or_assign(filename, std::weak_ptr<ModelResource>(model));

    return model;
}