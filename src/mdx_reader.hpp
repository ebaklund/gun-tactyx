
#pragma once

#include <iostream>
#include "buffer_reader.hpp"
#include "mdx_model.hpp"

struct MdxHeader
{
    int32_t num_frames;
    int32_t num_tags;
    int32_t num_meshes;
    int32_t num_animations;
};


void do_mdx(const std::vector<uint8_t>& buff)
{
    BufferReader reader(buff.data(), buff.size());
    MdxHeader mdx_header;

    reader.read_next_or_throw(&mdx_header);

    std::cout << std::format("NUM_FRAMES: {}\n", mdx_header.num_frames);
    std::cout << std::format("NUM_TAGS: {}\n", mdx_header.num_tags);
    std::cout << std::format("NUM_MESHES: {}\n", mdx_header.num_meshes);
    std::cout << std::format("NUM_ANIMATIONS: {}\n", mdx_header.num_animations);

    MdxBone mdx_bone;
    mdx_bone.animations.resize(mdx_header.num_animations);

    for (auto& anim : mdx_bone.animations)
        reader.read_next_or_throw(&anim);

    mdx_bone.link_names.resize(mdx_header.num_tags);

    for (auto& name : mdx_bone.link_names)
        reader.read_next_or_throw(name, 16);

    for (auto& name : mdx_bone.link_names)
        std::cout << std::format("- {}\n", name);

    //fread(bone->transforms,sizeof(MD3Transform),bone->transformsCount,file);


    // reader.read_next_or_throw(&header.num_frames);
    // reader.read_next_or_throw(&header.num_tags);
    // reader.read_next_or_throw(&header.num_meshes);
    // reader.read_next_or_throw(&header.num_animations);

}
