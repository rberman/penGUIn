#include "Bone.h"

namespace basicgraphics {
    using namespace std;
    using namespace glm;

    Bone::Bone(Inreader &inr, bool dg) {
        constructFromFile(inr, dg);
    }


    void Bone::draw()
    {
        // TOOD: Draw this bone and its children!

    }








    /***  Below this line, all routines are for loading skeleton and animation data from files ***/


    const bool ABORT_ON_ERROR=true;

    void assume(bool b) {
        if (!b && ABORT_ON_ERROR) {
            std::abort();
        }
    }

    void Bone::constructFromFile(Inreader &inr, bool dg)
    {
        deg = dg;
        currentRotation = mat4(1.0f);
        while (!inr.expect("end")) {
    
            if (inr.expect("id")) {
                inr.readInt(id);
            }
    
            if (inr.expect("name")) {
                inr.readToken(name);
            }
    
            if (inr.expect("direction")) {
                inr.readFloat(direction.x);
                inr.readFloat(direction.y);
                inr.readFloat(direction.z);
            }
    
            if (inr.expect("length")) {
                inr.readFloat(length);
                length = amc2meter(length);
            }
    
            if (inr.expect("axis")) {
                float ax, ay, az;
                std::string axisType;
                inr.readFloat(ax);
                inr.readFloat(ay);
                inr.readFloat(az);
                inr.readToken(axisType);
                if (axisType == "XYZ") {
                    initialRotation = eulerAngleXYZ(deg2rad(ax), deg2rad(ay), deg2rad(az));
                } else {
                    std::abort();
                }
      
            }
    
            if (inr.expect("dof")) {
                bool rx, ry, rz;
                rx = inr.expect("rx");
                ry = inr.expect("ry");
                rz = inr.expect("rz");
                rotationBounds.setdof(rx, ry, rz);
            }
    
            if (inr.expect("limits")) {
                for (int dof=0; dof<rotationBounds.dofs; dof++) {
                    assume(inr.expect("("));
                    float min, max;
                    inr.readFloat(min);
                    inr.readFloat(max);
                    assume(inr.expect(")"));
                    rotationBounds.setR(dof, deg2rad(min), deg2rad(max));
                }
            }
    
        } // read "end" token
    }


    std::string Bone::getName()
    {
        return name;
    }

    void Bone::addChild(std::shared_ptr<Bone> child)
    {
        children.push_back(child);
    }

    void Bone::readPose(Inreader &inr)
    {
        float rx=0, ry=0, rz=0;
        if (rotationBounds.dofRX) {
            inr.readFloat(rx);
        }
        if (rotationBounds.dofRY) {
            inr.readFloat(ry);
        }
        if (rotationBounds.dofRZ) {
            inr.readFloat(rz);
        }
        currentRotation = mat4(eulerAngleXYZ(deg2rad(rx), deg2rad(ry), deg2rad(rz)));
    }

    mat4 Bone::getCurrentLocalRotation() {
        return mat4(initialRotation)
        * mat4(currentRotation)
        * inverse(mat4(initialRotation));
    }

    float Bone::deg2rad(float d)
    {
        if (!deg)
            return d;
        else
            return d * glm::pi<float>() / 180;
    }
}
