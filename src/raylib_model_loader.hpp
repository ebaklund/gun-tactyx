
#pragma once

#include "mdx_model_loader.hpp"

namespace nyx
{
    class RaylibModelLoader
    {
    private:
        ZipReader& _zip_reader;
        MdxModelLoader _mdx_model_loader;

    public:
        RaylibModelLoader(ZipReader& zip_reader)
        :   _zip_reader(zip_reader),
            _mdx_model_loader(zip_reader) {
        }

        void load(const std::string& model_name, const std::string& skin_name, Model& raylib_model) {
            MdxModel mdx_model;
            _mdx_model_loader.load(model_name, skin_name, mdx_model);
        }
    };
}
