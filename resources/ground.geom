#version 330

// You must specify what type of primitive is passed in
layout(triangles) in;

// ... and what type of primitive you are outputing and how many vertices. The geometry shader is run once
// for each primitive so we will output three lines (6 vertices), one for each normal.
layout(line_strip, max_vertices = 500) out;

//uniform int numBladesY;
//uniform int numBladesX;
uniform float normalLength;

uniform mat4 projection_mat, view_mat, model_mat;

// Example of a geometry shader custom input
in vec3 normal[3];

// Example of a geometry shader custom output
out vec3 color;

void main() {
    
    //TODO: Fill me in. For each vertex in the triangle, you need to output a line strip primitive with two vertices to draw the vertex normal.
    //Think carefully about where the vertices should be positioned in world space. The length of the drawn normal should be normalLength.
    //Each vertex needs to have gl_position set by multiplying the world space position by the model matrix, the view matrix, and finally the projection matrix (order matters!).
    //The first vertex should be colored red and the second one blue so it is easy to see what direction the normal is pointing.
    int numBladesX = 16;
	int numBladesY = 15;
	vec3 pointOne = gl_in[0].gl_Position.xyz;
	vec3 pointTwo = gl_in[1].gl_Position.xyz;
	vec3 pointThree = gl_in[2].gl_Position.xyz;
	vec3 oneToTwo = pointTwo-pointOne;
	vec3 oneToThree = pointThree-pointOne;
	vec3 twoToThree = pointThree - pointTwo;
	vec3 twoToOne = pointOne - pointTwo;
	vec3 incrementYVec = oneToTwo / numBladesY;
	vec3 incrementXVec = oneToThree / numBladesX;
	
	for(int i = 0; i < numBladesY; i++){
		vec3 yVec = i * incrementYVec;
		for(int j = 0; j < numBladesX; j++){
			vec3 xVec = j * incrementXVec;
			vec3 currentPos = yVec + xVec + pointOne; //new vector plus position to get new position
			//check if this loop has gone past triangle
			vec3 twoToPos = currentPos - pointTwo;
			float cosTheta = dot(normalize(twoToOne), normalize(twoToThree));
			float theta = acos(cosTheta);
			float cosPhi = dot(normalize(twoToOne), normalize(twoToPos));
			float phi = acos(cosPhi);
			if(phi > theta){ //if gone past, break to outer for loop
				break;
			}
			//else, draw new grass
			vec3 norm = normalize(normal[0]);//vec3(0, 1, 0); //TODO: get rid of magic numbers for grass normal
			gl_Position = vec4(currentPos, 1);
			gl_Position = projection_mat * view_mat * model_mat * gl_Position;
			color = vec3(0.6, 0.8, 0.196);
			EmitVertex();
			gl_Position = gl_Position + vec4(norm, 0);
			color = vec3(0.6, 0.8, 0.196);
			EmitVertex();
			EndPrimitive();
		}
	}
	/*for(int i = 0; i < 3; i++){
		vec3 norm = 0.2*normalize(normal);
		gl_Position = gl_in.gl_Position;
		gl_Position = projection_mat * view_mat * model_mat * gl_Position;
		color = vec3(0, 0.5, 0.0);
		EmitVertex();
		gl_Position = gl_in.gl_Position + vec4(norm, 0);
		gl_Position = projection_mat * view_mat * model_mat * gl_Position;
		color = vec3(0.0, 0.5, 0.0);
		EmitVertex();
		EndPrimitive();
	}*/
		/*
	vec3 norm = normal[0];//vec3(0, 1, 0); //TODO: get rid of magic numbers for grass normal
	gl_Position = vec4(pointOne, 1);
	gl_Position = projection_mat * view_mat * model_mat * gl_Position;
	color = vec3(0, 0.5, 0.0);
	EmitVertex();
	gl_Position = vec4(pointTwo, 1);
	gl_Position = projection_mat * view_mat * model_mat * gl_Position;
	color = vec3(0.0, 0.5, 0.0);
	EmitVertex();
	gl_Position = vec4(pointThree, 1);
	gl_Position = projection_mat * view_mat * model_mat * gl_Position;
	color = vec3(0.0, 0.5, 0.0);
	EmitVertex();
	gl_Position = vec4(pointOne, 1);
	gl_Position = projection_mat * view_mat * model_mat * gl_Position;
	color = vec3(0.0, 0.5, 0.0);
	EmitVertex();
	EndPrimitive();*/
}












