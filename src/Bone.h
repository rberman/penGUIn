#ifndef Bone_h
#define Bone_h

#include <iostream>
#include <G3D/G3DAll.h>
#include "RotationBounds.h"
#include "Inreader.h"
#include "TaperedCylinder.h"



/** This class holds the data for a single articulated joint and bone of an animated character.  It also
    stores a list of 0 or more child bones.  So, it can be used to create a scenegraph for an animated
    character. */
class Bone : public ReferenceCountedObject {
public:

  // This constructor is setup to read data from the CMU motion capture database files
  Bone(Inreader &inr, bool dg);

  // Bones are named based on parts of the body
  std::string getName();    
  
  // Returns the rotation of this joint in the body.
  CoordinateFrame getCurrentLocalRotation();

  // Returns a vector that is scaled to the length of the bone and points in the direction of the bone.
  // In the bone's local coordinate frame, you can think of the bone as beginning at (0,0,0) and ending
  // at the postion (0,0,0) + getBoneVector().
  Vector3 getBoneVector() { return length * direction; }

  // An array of pointers to the other bones that are children of this one in the scenegraph.  All children
  // attach to the end of the bone.  
  Array< shared_ptr<Bone> > children;


  // This is the key routine that you need to fill in
  void draw(RenderDevice *rd);

 



  /* You should not need to use anything below this line.  These routines are used for reading the
     bone data from files */

  void addChild(shared_ptr<Bone> child);

  void readPose(Inreader &inr);

protected:

  void constructFromFile(Inreader &inr, bool dg);

  float deg2rad(float d);

  std::string name;
  float length;
  Vector3 direction;
  RotationBounds rotationBounds;    
  Vector3 axis;
  Matrix3 initialRotation;
  Matrix3 currentRotation;
  int id;
  bool deg;

};

#endif
