#version 330

in vec3 position_world, normal_world;
uniform vec3 eye_world;


vec3 light_position_world  = vec3 (-2.0, 2.0, 4.0);
vec3 Ld = vec3 (0.6, 0.6, 0.6); // dull white diffuse light colour
vec3 Ia = vec3 (0.15, 0.15, 0.15); // grey ambient colour
float specular_exponent = 50.0; // specular 'power'

uniform int hasTexture;
uniform vec4 materialColor;
uniform sampler2D textureSampler;
in vec2 texture_coordinates;

out vec4 fragment_colour;

void main () {
	vec3 distance_to_light_world = light_position_world - position_world;
	vec3 direction_to_light_world = normalize (distance_to_light_world);
	float dot_prod = dot (direction_to_light_world, normalize(normal_world));
	dot_prod = max (dot_prod, 0.0);
    
    vec4 Kd = materialColor * (1 - hasTexture) + hasTexture * texture(textureSampler, texture_coordinates );
	vec3 Id = Ld * Kd.rgb * dot_prod;
	
	vec3 surface_to_viewer_world = normalize (eye_world - position_world);
	vec3 half_way_world = normalize (surface_to_viewer_world + direction_to_light_world);
	float dot_prod_specular = max(dot (half_way_world, normal_world), 0.0);
	float specular_factor = pow (dot_prod_specular, specular_exponent);
	
	vec3 Is = vec3(0.8) * specular_factor;
		
	// final colour
    fragment_colour = vec4(Is + Id + Ia, Kd.a);
	
}