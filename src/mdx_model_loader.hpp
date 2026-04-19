
#pragma once

#include <string>
#include "buffer_reader.hpp"


namespace nyx
{
    class MdxModelLoader
    {
    private:
        ZipReader& _zip_reader;

        static void load_model(MdxModel& mdx_model, const std::vector<uint8_t>& buff)
        {
            BufferReader reader(buff.data(), buff.size());

            reader.read_next_or_throw(&mdx_model.bone.frame_count);

            int32_t num_tags;
            int32_t num_meshes;
            int32_t num_animations;

            reader.read_next_or_throw(&num_tags);
            reader.read_next_or_throw(&num_meshes);
            reader.read_next_or_throw(&num_animations);

            std::cout << std::format("---> Num frames: {}\n", mdx_model.bone.frame_count);
            std::cout << std::format("---> Num tags: {}\n", num_tags);
            std::cout << std::format("---> Num meshes: {}\n", num_meshes);
            std::cout << std::format("---> Num animations: {}\n", num_animations);
            std::cout << "---\n";

            mdx_model.bone.animations.resize(num_animations);
            reader.read_next_or_throw(mdx_model.bone.animations);

            mdx_model.link_names.resize(num_tags);
            for (std::string& name : mdx_model.link_names)
            {
                reader.read_next_or_throw(name, 16);
                std::cout << std::format("---> {}\n", name);
            }

            std::cout << "---\n";

            int num_transforms = mdx_model.bone.frame_count * num_tags;
            mdx_model.bone.transforms.resize(num_transforms);
            reader.read_next_or_throw(mdx_model.bone.transforms);

            std::cout << std::format("---> Num transforms: {}\n", num_transforms);

            mdx_model.bone.meshes.resize(num_meshes);
            for (MdxMesh& mesh : mdx_model.bone.meshes) {
                int32_t num_frames;
                int32_t num_triangles;
                int32_t num_tex_coords;

                reader.read_next_or_throw(&num_frames);
                reader.read_next_or_throw(&num_triangles);
                reader.read_next_or_throw(&num_tex_coords);
                int32_t num_vertices = num_tex_coords * num_frames;

                std::cout << std::format("---> Num frames: {}\n", num_frames);
                std::cout << std::format("---> Num triangles: {}\n", num_triangles);
                std::cout << std::format("---> Num tex coords: {}\n", num_tex_coords);
                std::cout << std::format("---> Num vertices: {}\n", num_vertices);

                mesh.triangles.resize(num_triangles);
                mesh.tex_coords.resize(num_tex_coords);
                mesh.vertices.resize(num_vertices);

                reader.read_next_or_throw(mesh.triangles);
                reader.read_next_or_throw(mesh.tex_coords);
                reader.read_next_or_throw(mesh.vertices);
            }

            if (reader.bytes_left() != 0) {
                constexpr auto fmt = "Buffer is not empty after reading MDX model. Bytes left: {}\n";
                throw std::runtime_error(std::format(fmt, reader.bytes_left()));
            }
        }

    public:
        MdxModelLoader(ZipReader& zip_reader) : _zip_reader(zip_reader) {
        }

        void load(const std::string& model_name, const std::string& skin_name, MdxModel& mdx_model) {
            std::vector<uint8_t> model_data = _zip_reader.fread(model_name);
            std::vector<uint8_t> skin_data = _zip_reader.fread(skin_name);

            load_model(mdx_model, model_data);
        }
    };
}
