#pragma once
#ifndef RAYTRACER_IMAGETEXTURE_H
#define RAYTRACER_IMAGETEXTURE_H

#include "Texture.h"

class ImageTexture : public Texture {
private:
    unsigned char * data;
    int nx;
    int ny;

public:
    ImageTexture() {};
    ImageTexture(unsigned char * data, int A, int B) : data(data), nx(A), ny(B) {};
    virtual Vector3f Value(float u, float v, const Vector3f& p) const override;

};

#endif //RAYTRACER_IMAGETEXTURE_H
