//
//  Box.hpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>

#include <stdio.h>
#include "Model.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace basicgraphics {

	class Box {
	public:

		/*!
		 * Creates an axis aligned box. Min specifies the minimum extents and max specifies the maximum extents.
		 * e.g. to create a 1x1 cube centered on the origin min=(-0.5,-0.5,-0.5) and max=(0.5, 0.5, 0.5)
		 */
		Box(glm::vec3 &_min, glm::vec3 &_max, glm::vec4 &color);
		virtual ~Box();

		virtual void draw(GLSLProgram &shader, glm::mat4 &modelMatrix);

	protected:
		std::unique_ptr<Model> _model;
		glm::vec3 _min;
		glm::vec3 _max;
		glm::vec4 _color;
		glm::mat4 _localMat;
	};

}


#endif /* Box_hpp */
