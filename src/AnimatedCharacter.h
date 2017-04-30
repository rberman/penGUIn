#ifndef AnimatedCharacter_h
#define AnimatedCharacter_h

#include <string>
#include "Bone.h"
#include "Inreader.h"

/** This is the root class for the animated character.  You can also think of this as a root node in
    a scene graph.  The class takes care of loading the skeleton file and also animation file(s) needed
    to draw the skeleton.  The key routine that you need to code is the draw(..) routine.  In it, you
    will want to draw all of the character's bones in the correct positions and orientations based on
    the current animation data. */
class AnimatedCharacter : public ReferenceCountedObject {
public:

  AnimatedCharacter(std::string asfFilename, std::string amcFilename);

  // This should be called once per frame to advance through the animation
  void nextFrame();

  // This returns the current coordinate frame of the ROOT NODE of the character, typicaly this is
  // the character's pelvis -- all of the root node bones should be drawn relative to this coordinate
  // frame.  This coordinate frame will change every frame of the animation.
  CoordinateFrame getCurrentCoordinateFrame();

  // This is an array of pointers to bones.  It will contain one or more bones that are attached to the
  // root node of the character, each of these bones will, in turn, have 0 or more child bones.
  Array< shared_ptr<Bone> > rootNodeBones;
  

  // TODO: Implement this routine to draw all the character's bones in the correct pose based on the
  // current animation data
  void draw(RenderDevice *rd);


protected:

  /** Everything below this line is for loading skeleton and animation files **/
  void loadAnimation(std::string amcFilename);

  void loadSkeleton(std::string asfFilename);
  
  void resetFile();
  
  float deg2rad(float d);
  
  void parseUnits(Inreader &inr);
  void parseRoot(Inreader &inr);
  void parseBonedata(Inreader &inr);
  void parseHierarchy(Inreader &inr);
  
  bool deg;
  Vector3 position;
  Vector3 orientation;
  Table< std::string, shared_ptr<Bone> > boneTable;
  std::ifstream *anim;
};

#endif
