#ifndef SPHERE_H
#define SPHERE_H


class Sphere
{
    public:
        Sphere(float x, float y, float z, float radius);
        virtual ~Sphere();

        float GetX(){return x;}
        float GetY(){return y;}
        float GetZ(){return z;}
        float GetRadius(){return radius;}

        void SetX(float x){this->x=x;}
        void SetY(float y){this->y=y;}
        void SetZ(float z){this->z=z;}
        void SetRadius(float radius){this->radius=radius;}


    protected:

    private:
    float x,y,z,radius;
};

#endif // SPHERE_H
