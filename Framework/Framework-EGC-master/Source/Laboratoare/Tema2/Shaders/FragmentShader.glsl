#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int type_of_light;
uniform float cut_off_angle;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));

	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	// TODO: compute light
	float light = 0.f;

	if (type_of_light == 0)
	{
		float d	= distance(light_position, world_position);
		float attenuation_factor = 1.f / max(d * d, 1.f);
		light = ambient_light + attenuation_factor * (diffuse_light + specular_light);
	
	} else {
		float cut_off_rad = radians(cut_off_angle);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cut_off_rad);
		
		if (spot_light > spot_light_limit)
		{
			float linear_att = (spot_light - spot_light_limit) / (1.f - spot_light_limit);
			float light_att_factor = linear_att * linear_att;
			light = ambient_light + light_att_factor * (diffuse_light + specular_light);
		} else {
			light = ambient_light;
		}
	}


	// TODO: write pixel out color
	vec3 colour = object_color;

	out_color = vec4(colour, 1.f);
}