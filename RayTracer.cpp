#include <windows.h>
#include <iostream>
#include <math.h>
#define MAX_RAY_DEPTH 3
using namespace std;
float pixelSize;

class Vec3f
{
public:
    float i,j,k; // vector in 3D
    void setvec(float a, float b, float c){
        i=a;
        j=b;
        k=c;
    }
    void SetVector(Vec3f v1, Vec3f v2){
        i=v2.i-v1.i;
        j=v2.j-v1.j;
        k=v2.k-v1.k;
    }
};


// returns dot product of the given 2 vectors
float dotProduct(Vec3f v1, Vec3f v2){
    return v1.i*v2.i + v1.j*v2.j + v1.k*v2.k;
}

// returns vector which is cross product of given 2 vectors
Vec3f crossProduct(Vec3f v1, Vec3f v2){
    Vec3f R;
    R.i= v1.j*v2.k - v2.j*v1.k;
    R.j= v1.k*v2.i - v2.k*v1.i;
    R.k= v1.i*v2.j - v2.i*v1.j;
    return R;
}

// Evaluates distance between two vectors
float dist(Vec3f v1, Vec3f v2){
    return sqrt(pow(v1.i-v2.i,2) + pow(v1.j-v2.j,2) + pow(v1.k-v2.k,2));
}

// Prints any vector on the screen
void printVec(Vec3f v){
    cout<< v.i<<"i + "<<v.j<<"j + "<<v.k<<"k\n";
}

//normalize vector
Vec3f normalize(Vec3f v1){
        float a= v1.i*v1.i + v1.j*v1.j + v1.k*v1.k;
        a=sqrt(a);
        v1.i=v1.i/a;
        v1.j=v1.j/a;
        v1.k=v1.k/a;
        return v1;
}

class Col3f
{
public:
    float r,g,b; // For color
    void setcol(float i, float j, float k){
        r=i;
        g=j;
        b=k;
    }
    void norm(){
        if(r>1)
            r=1;
        if(g>1)
            g=1;
        if(b>1)
            b=1;
    }
};
Col3f img[500][500];
Col3f ambient;
Col3f multiplyColor(Col3f C, float Q){
    Col3f col;
    col.r=C.r*Q; col.g=C.g*Q; col.b=C.b*Q;
    return col;
}

Col3f addColor(Col3f c1, Col3f c2){
    Col3f col;
    col.r=c1.r+ c2.r;
    col.g=c2.g+ c1.g;
    col.b=c1.b+ c2.b;
    return col;
}
Col3f Mult(Col3f c1, Col3f c2){
    Col3f col;
    col.r=c1.r*c2.r;
    col.g=c1.g*c2.g;
    col.b=c1.b*c2.b;
    return col;
}

class ray
{
public:
    Vec3f drxn; //Direction of the ray
    Vec3f point; // Point through which it passes by
    ray(Vec3f d, Vec3f p){
        drxn=d;
        point=p;
        //cout<<"Constructor for ray is working\n";
    }
    ray(Vec3f v1, Vec3f p, int a){  // construct for making ray passing through 2 points with origin ass p
        drxn.i=v1.i-p.i;
        drxn.j=v1.j-p.j;
        drxn.k=v1.k-p.k;
        drxn=normalize(drxn);
        point=p;
    }
    ray(){};
};

class plane
{
public:
    Vec3f normal;
    float distance;
};


class lightSource
{
public:
    Vec3f Source;
    Col3f Color;
    bool isInShadow;
    void setsrc(Vec3f v1, Col3f c1){
        Source=v1;
        Color=c1;
    }
};


Vec3f img_centre;
Vec3f eye;
Vec3f v;
Vec3f u;
Vec3f n;




// class containing sphere
class Object
{
public:
    Vec3f center; // position of the center of the sphere
    float radius; // radius of the sphere
    Col3f surfaceColor; // surface color and emission color
    float indexOfRefraction, reflection; // surface transparency and reflection coefficient
    int type;
    int isGlass;
    float Ka, Kd, Ks;
    Col3f Color;
    Vec3f V1,V2,V3;
    void setobject(float x, float y, float z, float rad, int typ, int glass){
        center.i=x;
        center.j=y;
        center.k=z;
        radius=rad;
        type=typ;
        isGlass=glass;
        indexOfRefraction=.5;
        Ka=0.5;
        Kd=0.4;
        Ks=0.8;
        Color.setcol(0,.7,1);
        //cout<<"Constructor for sphere working\n";
    }
    void setobject(float x1, float y1, float z1,float x2, float y2, float z2,float x3, float y3, float z3, int typ, int glass){
        V1.setvec(x1,y1,z1);
        V2.setvec(x2,y2,z2);
        V3.setvec(x3,y3,z3);
        type=typ;
        isGlass=glass;
        indexOfRefraction=.5;
        Ka=0.5;
        Kd=0.4;
        Ks=1;
        Color.setcol(0,1,0);
        //cout<<"Constructor for sphere working\n";
    }

};
Object objects[2];

Col3f Trace(const ray &Ray, int depth);
int Intersect(Object O, ray R, Vec3f* P, Vec3f* N);
ray computeReflectionRay(Vec3f L,Vec3f Pt, Vec3f N);
ray computeRefractionRay(float nt, Vec3f I, Vec3f Pt, Vec3f N);



// view plane description
void camera(){
    img_centre.i=2.5;
    img_centre.j=2.5;
    img_centre.k=2.5;
    v.i=0;
    v.j=0;
    v.k=1;
    v=normalize(v);
    eye.i=0;
    eye.j=0;
    eye.k=2.5;
    float height=sizeof(img)/sizeof(img[0]);
    pixelSize=5/height;
    n.i=img_centre.i-eye.i;
    n.j=img_centre.j-eye.j;
    n.k=img_centre.k-eye.k;
    n=normalize(n);
    u=crossProduct(v,n);
    ambient.setcol(.2,.2,.2);
    //cout<<"Camera function Working\n";
}

//********************************************************************************************************//
lightSource Light[2];
void SetColor()
{
    camera();
    int height=sizeof(img)/sizeof(img[0]);
    int width= sizeof(img[0])/sizeof(img[0][0]);
    //cout<< height << " X "<< width <<"\n";

    objects[0].setobject(5,5,-2,3,1,0);
    objects[1].setobject(15,10,2.5,3,1,0);

    Vec3f l1; l1.setvec(0,5,-1);
    Col3f L1; L1.setcol(1,1,1);
    Light[0].setsrc(l1,L1);
    l1.setvec(5,0,-1);
    L1.setcol(1,1,1);
    Light[1].setsrc(l1,L1);

    Vec3f currentpixel;
    for(int a=0;a<height;a++){
        for(int b=0;b<width;b++){
            currentpixel.i= img_centre.i - (u.i*(a-height/2) + v.i*(b-width/2))*pixelSize;
            currentpixel.j= img_centre.j - (u.j*(a-height/2) + v.j*(b-width/2))*pixelSize;
            currentpixel.k= img_centre.k - (u.k*(a-height/2) + v.k*(b-width/2))*pixelSize;
            // compute primary ray direction
            ray primRay(currentpixel, eye, 1);

            // shoot prim ray in the scene and search for intersection
            img[a][b]= Trace(primRay, 0);
            if(img[a][b].r<0||img[a][b].g<0||img[a][b].b<0)
                cout<<"--";
        }
        //cout<<"\n";
    }
    cout<<"|";
}


//*****************************************************************************//

int Intersect(Object O, ray R, Vec3f* P, Vec3f* N){
    if(O.type==1){
    Vec3f v1=R.drxn;
    Vec3f c=R.point;
    Vec3f s=O.center;
    Vec3f nHit;
    float rad=O.radius;
    float A= v1.i*v1.i + v1.j*v1.j + v1.k*v1.k;
    float B= 2.0*(c.i*v1.i + c.j*v1.j + c.k*v1.k - s.i*v1.i - s.j*v1.j - s.k*v1.k);
    float C= c.i*c.i + c.j*c.j + c.k*c.k + s.i*s.i + s.j*s.j + s.k*s.k - 2*c.i*s.i - 2*c.j*s.j - 2*c.k*s.k - rad*rad;
    float D = B*B -4.0*A*C;
    if(D<=0)
        return 0;
    if(D>0){
        float k1=(-B + sqrt(D))/(2*A);
        float k2=(-B - sqrt(D))/(2*A);
        if(k1<=0&&k2<=0)
            return 0;
        Vec3f result1, result2;
        result1.i=c.i+v1.i*k1;
        result2.i=c.i+v1.i*k2;
        result1.j=c.j+v1.j*k1;
        result2.j=c.j+v1.j*k2;
        result1.k=c.k+v1.k*k1;
        result2.k=c.k+v1.k*k2;
        if(k1>0&&k2>0){
            if(k1<k2){
                *P= result1;
                nHit.SetVector(O.center, result1);
                *N=nHit;
            }
            else{
                *P= result2;
                nHit.SetVector(O.center, result2);
                *N=nHit;
            }
        }
        else if(k1>0){
                *P= result1;
                nHit.SetVector(O.center, result1);
                *N=nHit;
        }
        else if(k2>0){
                *P= result2;
                nHit.SetVector(O.center, result2);
                *N=nHit;
        }
        else
            return 1;
        return 1;
        }
    }
    else if(O.type==2){
        return 0;
    }
}


Col3f Trace(const ray &Ray, int depth)
{
    Object object;
    object.type=0;
    float minDistance = INFINITY;
    Vec3f pHit;
    Vec3f nHit;
    for (int k = 0; k <(sizeof(objects)/sizeof(objects[0])); ++k) {
        if (Intersect(objects[k], Ray, &pHit, &nHit)) {
            // ray origin = eye position of it's the prim ray
            float distance = dist(Ray.point, pHit);
            //cout<<"- ";
            if (distance < minDistance) {
                object = objects[k];
                minDistance = distance;
            }
        }
    }
    nHit=normalize(nHit);
    if (object.type==0){
        return multiplyColor(ambient,0.2);
    }

    // if the object material is glass, split the ray into a reflection and a refraction ray.
    if (object.isGlass==1 && depth < MAX_RAY_DEPTH) {
        // compute reflection
        ray reflectionRay;
        reflectionRay = computeReflectionRay(Ray.drxn, pHit, nHit);
        // recurse
        Col3f reflectionColor = Trace(reflectionRay, depth + 1);
        ray refractionRay;
        refractionRay = computeRefractionRay(object.indexOfRefraction, Ray.drxn,pHit, nHit);
        // recurse
        Col3f refractionColor = Trace(refractionRay, depth + 1);
        float Kr=1, Kt=0.5; ////////////////////////////
        //fresnel(object.indexOfRefraction, nHit, Ray.drxn, &Kr, &Kt);
        //return reflectionColor * Kr + refractionColor * (1-Kr); /////////////////////////////////
        return reflectionColor;
    }

    // object is a diffuse opaque object
    // compute illumination
    Col3f col;
    col=multiplyColor(ambient,object.Ka);
    for(int m=0;m<(sizeof(Light)/sizeof(Light[0]));m++){
        Light[m].isInShadow = false;
        ray shadowRay(pHit, Light[m].Source,1);
        float dis=dist(Light[m].Source,pHit);
        Vec3f p;
        Vec3f n;
        for (int k=0; k<(sizeof(objects)/sizeof(objects[0])); k++) {
            if ((Intersect(objects[k], shadowRay, &p, &n))&&(dis>dist(Light[m].Source,p))) {
                Light[m].isInShadow = true;
            }
        }

        //point is illuminated
        //Diffusion Reflection
        if(!Light[m].isInShadow){
            ray L3(Light[m].Source,pHit,1);
            Vec3f temp=  L3.drxn;
            temp=normalize(temp);
            float Q=dotProduct(temp,nHit);
            Q= object.Kd*Q;
            if(Q<0)
                cout<<"*";

            col=addColor(col,multiplyColor(Light[m].Color,Q));
            //Specular Reflection ////////////////////////////////////////////////
            ray Reflected= computeReflectionRay(Ray.drxn,pHit,nHit);
            Q= dotProduct(Reflected.drxn,nHit);
            if(Q<0)
                cout<<"-";
            Q=object.Ks*Q;
            Q=pow(Q,5);
            col=addColor(col,multiplyColor(Light[m].Color,Q));
        }
    }
        col.norm();

    return Mult(col, object.Color);
}


ray computeReflectionRay(Vec3f L,Vec3f Pt, Vec3f N){
    L=normalize(L);
    N=normalize(N);
    Vec3f R;
    float k= dotProduct(L,N);
    R.i= L.i- 2*k*N.i;
    R.j= L.j- 2*k*N.j;
    R.k= L.k- 2*k*N.k;
    R=normalize(R);
    ray R0(R,Pt);
    return R0;
}

ray computeRefractionRay(float nt, Vec3f I, Vec3f Pt, Vec3f N){
    I=normalize(I);
    N=normalize(N);
    float cosQ=-dotProduct(I,N);
    Vec3f R;
    R.i=I.i/nt + cosQ*N.i*(1/nt-1);
    R.j=I.j/nt + cosQ*N.j*(1/nt-1);
    R.k=I.k/nt + cosQ*N.k*(1/nt-1);
    R=normalize(R);
    ray R0(R,Pt);
    return R0;
}

float retCol(int i,int j,int k){
    if(k==0)
        return img[i][j].r;
    if(k==1)
        return img[i][j].g;
    return img[i][j].b;
}

