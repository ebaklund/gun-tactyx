
#pragma once

namespace nyx::dat
{
    struct MdxVector {
    float coord[3];
    };

    struct MdxVertex {
        int16_t coord[3];
        uint8_t normal[2];

        static float* get_coord_f3(const int16_t* in, float* out) {
            *(out++) = *(in++);
            *(out++) = *(in++);
            *(out++) = *(in++);
            return out;
        }

        static float* get_normal_f3(const uint8_t* in, float* out) {
            const static float delta_deg = 2.f*M_PI/255.f;
            float    alpha = in[0] * delta_deg;
            float     beta = in[1] * delta_deg;
            float sinAlpha = sinf(alpha);
            *(out++) = cosf(beta)*sinAlpha;
            *(out++) = sinf(beta)*sinAlpha;
            *(out++) = cosf(alpha);
            return out;
        }

        void get_vertex_f3(float* coord_out, float* normal_out) {
            get_coord_f3(coord, coord_out);
            get_normal_f3(normal, normal_out);
        }
    };

    struct MdxTexCoord {
        float coord[2];
    };

    struct MdxTriangle {
        int32_t vertex[3];

        template<typename T>
        static T* get_indices(const int32_t* in, T* out) {
            *(out++) = (T)*(in++);
            *(out++) = (T)*(in++);
            *(out++) = (T)*(in++);
            return out;
        }
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
        std::vector<MdxVertex>   vertices;
        std::vector<MdxTexCoord> tex_coords;
        std::vector<MdxTriangle> triangles;
    };

    struct MdxBone
    {
        int                       frame_count;
        std::vector<MdxAnimation> animations;
        std::vector<MdxTransform> transforms;
        std::vector<MdxMesh>      meshes;
        std::vector<std::string>  link_names;
    };
}
