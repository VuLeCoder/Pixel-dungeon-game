#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../scenes/scene.h"

class SceneManager {
private:
    static Scene* currScene;

public:
    static void Init(Scene* scene);
    static void ChangeScene(Scene* scene);
    static void Update();
    static void Draw();
};

#endif