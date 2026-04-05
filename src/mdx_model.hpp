
#pragma once

struct MdxVector {
  float coord[3];
};

struct MdxRotation {
  float matrix[9];
};

struct MdxTransform {
    MdxVector position;
    MdxRotation rotation;
};

// class GLAnimationData {
// public:
//   int firstFrame;
//   int lastFrame;
//   int backFrames;
//   int fps;
//   float invFPS;
// public:
//   GLAnimationData();
//   GLAnimationData(int ff, int lf, int bf, int iFps);
// };

struct MdxAnimation {
    int32_t first;
    int32_t last;
    int32_t back;
    int32_t fps;
};

// class GLBone: public DMReference {
// public:
//   int framesCount;
//   int animationsCount;
//   GLAnimationData* animations;
//   int shapesCount;
//   GLAnimatedShape* shapes;
//   int linksCount;
//   char** linkNames;
//   int transformsCount;
//   MD3Transform* transforms;
// public:
//   GLBone();
//   void setAnimations(int animsCount, GLAnimationData* anims)
//     {animationsCount = animsCount; animations = anims;}
//   virtual void destroyObject();
// };

struct MdxBone
{
    std::vector<MdxAnimation> animations;
    std::vector<std::string> link_names;
};
