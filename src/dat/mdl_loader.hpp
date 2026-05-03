
#pragma once

#include <string>
#include <cctype>
#include "buffer_reader.hpp"
#include "mdl_content.hpp"


namespace nyx::dat
{
    class MdlLoader
    {
    private:
        ZipReader& _zip_reader;

    public:
        MdlLoader(ZipReader& zip_reader)
        : _zip_reader(zip_reader){
        }

        void load(const std::string& mdl_name, MdlContent& mdl_content) {
            std::string model_name;
            std::string skin_name;

            std::vector<uint8_t> model_data = _zip_reader.fread(mdl_name);
            const uint8_t* p = model_data.data();
            const uint8_t* p_end = p + model_data.size();

            while (p < p_end) {
                model_name = "";
                skin_name = "";

                // Skip space
                while ((p < p_end) && isspace(*p))
                    ++p;

                // Read model name
                while ((p < p_end) && isgraph(*p))
                    model_name += *(p++);

                if (model_name.size() == 0)
                    throw std::runtime_error("Failed to load mdl model name.");

                std::cout << std::format("model name: {}\n", model_name);

                // Skip whitespace
                while ((p < p_end) && isspace(*p))
                    ++p;

                // Read skin name
                while ((p < p_end) && isgraph(*p))
                    skin_name += *(p++);

                if (skin_name.size() == 0)
                    throw std::runtime_error("Failed to load mdl skin name.");

                std::cout << std::format(" skin name: {}\n", skin_name);

                // Store mdl item
                mdl_content.items.push_back(MdlItem(model_name, skin_name));

                // Skip whilespace
                while ((p < p_end) && isspace(*p))
                    ++p;
            }
        }
    };
}
