#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 position;
	vec3 color;
};

varying vec3 v_normal;
varying vec3 v_fragPos;

uniform vec3 u_camPos;
uniform Material u_material;
uniform Light u_light;



void main()
{

    vec3 ambient = u_light.color * u_material.ambient;
	
	// diffuse 
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_light.position - v_fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_light.color * (diff * u_material.diffuse);
	
    vec3 viewDir = normalize(u_camPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_light.color * (spec * u_material.specular); 

	vec3 result = ambient + diffuse + specular;
	gl_FragColor = vec4(result, 1.0);
}
