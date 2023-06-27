#pragma once
#include <memory>
#include <string>
#include <map>
#include "Graphics/ModelResource.h"

// ���\�[�X�}�l�[�W���[[21]
class ResourceManager
{
private:
    ResourceManager(){}
    ~ResourceManager(){}
    
public:
    // �B��̃C���X�^���X�擾[21]
    static ResourceManager& Instance()
    {
        static ResourceManager instance;
        return instance;
    }

    // ���f�����\�[�X�ǂݍ���[21]
    std::shared_ptr<ModelResource> LoadModelResource(const char* filename);

private:
    // �p�͐V�����^����Ă�
    using ModelMap = std::map<std::string, std::weak_ptr<ModelResource>>;

    ModelMap models;
};