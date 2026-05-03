
#pragma once

#include "dat/mdx_loader.hpp"

namespace nyx
{
    class RaylibModelLoader
    {
    private:
        nyx::dat::ZipReader& _zip_reader;
        nyx::dat::MdxLoader _mdx_loader;

    public:
        RaylibModelLoader(nyx::dat::ZipReader& zip_reader)
        :   _zip_reader(zip_reader),
            _mdx_loader(zip_reader) {
        }

        void load(const std::string& bone_name, const std::string& skin_name, Model& raylib_model) {
            nyx::dat::MdxBone mdx_bone;
            _mdx_loader.load(bone_name, skin_name, mdx_bone);
        }
    };
}
