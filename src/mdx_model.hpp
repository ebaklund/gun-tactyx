
#pragma once

struct MdxVector {
  float coord[3];
};

struct MdxVertex {
  int16_t coord[3];
  uint8_t normal[2];
};

struct MdxTexCoord {
  float coord[2];
};

struct MdxTriangle {
  int32_t vertex[3];
};

struct MdxRotation {
  float matrix[9];
};

struct MdxTransform {
    MdxVector position;
    MdxRotation rotation;
};

struct MdxAnimation {
    int32_t first_frame;
    int32_t last_frame;
    int32_t back_frame;
    int32_t fps;
};

struct MdxMesh {
  std::vector<MdxVertex> vertices;
  std::vector<MdxTexCoord> tex_coords;
  std::vector<MdxTriangle> triangles;
};

struct MdxModel
{
    std::vector<MdxAnimation> animations;
    std::vector<std::string> link_names;
    std::vector<MdxTransform> transforms;
    std::vector<MdxMesh> meshes;
};
