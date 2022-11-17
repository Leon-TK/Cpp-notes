#pragma once
namespace LTK
{    
    struct SystemData {
        uint32_t cores = 0;
        uint32_t memory = 4096;
    }

    SystemData GetSystemData() {};    
} // namespace LTK
