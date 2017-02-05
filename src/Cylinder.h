//
//  Cylinder.hpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#ifndef Cylinder_hpp
#define Cylinder_hpp

#include <stdio.h>
#include <Model.h>
#include <GLSLProgram.h>
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace basicgraphics {

	class Cylinder {
	public:

		/*!
		 * Creates a cylinder where the base is centered at point 1 and the top is centered at point2 with the specified radius and color.
		 */
		Cylinder(glm::vec3 &point1, glm::vec3 &point2, float radius, glm::vec4 &color);
		virtual ~Cylinder();

		virtual void draw(GLSLProgram &shader, glm::mat4 &modelMatrix);

	protected:
		std::unique_ptr<Model> _model;
		glm::vec3 _point1;
		glm::vec3 _point2;
		glm::mat4 _localMat;
		float _radius;
		glm::vec4 _color;
	};

}

#endif /* Cylinder_hpp */
