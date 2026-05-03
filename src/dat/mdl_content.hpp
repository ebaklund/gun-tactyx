#pragma once

#include <string>

namespace nyx::dat
{
    struct MdlItem {
        std::string model_name;
        std::string skin_name;
    };

    struct MdlContent
    {
        std::vector<MdlItem> items;
    };
}
