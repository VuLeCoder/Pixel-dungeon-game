#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    virtual ~Scene() {}
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif