#version 400 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 modelPos;
in vec4 lightDirection;
// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float attenuation;
uniform int progowanie;
uniform vec3 lightDir;
uniform int oswietlenie;
uniform vec4 lightColor;
uniform bool sun;
uniform mat4 matV;
uniform mat4 matM;
uniform vec3 camerapos;
void main(){
	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, UV ).rgba;
	color = vec4(0.4,0.7,0.5, 1.0);
	//color = vec4(color.r,color.g,color.b,color.a);
	vec3 normals = normalize(modelPos);

	if(attenuation != 0.0f)
		color = vec4(color.r*attenuation, color.g*attenuation, color.b*attenuation, color.a);
	if(progowanie == 1){
		float grey = color.r+color.g+color.b;
		grey /= 3;
		if(grey < 0.7)
			grey = 0.0f;
		else
			grey = 1.0f;
		color = vec4(grey,grey,grey, color.a);
	}
	if(progowanie == 2){
		float threshold = 0.5f;
		if(color.r < threshold)
			color.r = 0.0f;
		else
			color.r = 1.0f;
		if(color.g < threshold)
			color.g = 0.0f;
		else
			color.g = 1.0f;
		if(color.b < threshold)
			color.b = 0.0f;
		else
			color.b = 1.0f;
	}

	if(oswietlenie == 1){
		//cel shading
		float intensity;
		intensity = dot(lightDir, normals);
		intensity = intensity / 5;
		if (intensity > 0.95)
		color = vec4(1.0,0.5,0.5,1.0);
		else if (intensity > 0.5)
			color = vec4(0.6,0.3,0.3,1.0);
		else if (intensity > 0.25)
			color = vec4(0.4,0.2,0.2,1.0);
		else
			color = vec4(0.2,0.1,0.1,1.0);
	}
	else if(oswietlenie == 2){
		//światło rozproszenia (Diffuse)
		float ambientStrength = 0.1;
		vec3 lc = lightColor.rgb;
		vec3 ambient = ambientStrength * lc;
		vec3 lightVector = normalize(lightDir - modelPos);
		float diff = max(dot(normals, lightVector), 0.0);
		vec3 diffuse = diff * lc;
		vec3 result = (ambient + diffuse) * color;
		color = vec4(result, color.a);
	}
	else if(oswietlenie == 3){
		//Odbicie lambertowskie
		float distance = length(lightDir - modelPos);
		vec3 lightVector = normalize(lightDir - modelPos);
		float diffuse = max(dot(normals, lightVector), 0.1);
		diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
		float alpha = color.a;
		color = color * diffuse;
		color.a = alpha;
	}
	else if(oswietlenie == 4){
		//odbicie zwierciadlane (specular)
		float specularStrength = 0.2;
		vec3 viewDir = normalize(camerapos - modelPos);
		vec3 reflectDir = reflect(-lightDir, normals);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 lc = lightColor.rgb;
		vec3 specular = specularStrength * spec * lc;
		color = vec4(color.rgb*specular,color.a);
		
	}
	/*else if(oswietlenie == 5){
		//model oświetlenia Phonga
		float ambientStrength = 0.1;
		vec4 ambient = ambientStrength * lightColor;

		float distance = length(lightDir - modelPos);
		vec3 lightVector = normalize(lightDir - modelPos);
		float diffuse = max(dot(lightVector, normals), 0.0);
		//diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));

		float specularStrength = 0.2;
		vec3 viewDir = normalize(camerapos - modelPos);
		vec3 reflectDir = reflect(-lightDir, normals);
		float spec = pow(max(dot(viewDir, reflectDir), 0.1), 32);
		vec3 lc = lightColor.rgb;
		vec3 specular = specularStrength * spec * lc;
		vec3 objectColor = color.rgb;
		vec3 diff = diffuse*objectColor;
		vec3 phongresult = (ambient.rgb + diff + specular) * objectColor;
		color = vec4(phongresult, color.a);
	}*/
	else if(oswietlenie == 5){
		//model oświetlenia Phonga
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * color.rgb;

		vec3 lightVector = normalize(lightDir - modelPos);
		float diff= max(dot(lightVector, normals), 0.0);
		vec3 diffuse = diff*color.rgb;

		vec3 viewDir = normalize(camerapos - modelPos);
		vec3 reflectDir = reflect(-lightDir, normals);
		float spec = 0.0;

		reflectDir = reflect(-lightDir, normals);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
		
		vec3 specular = vec3(0.3) * spec;

		color = vec4(ambient + diffuse + specular, color.a);
	}
	/*else if(oswietlenie == 6){
		//model Blinna-Phonga
		float ambientStrength = 0.1;
		vec4 ambient = ambientStrength * lightColor;
		vec3 lightVector = normalize(lightDir - modelPos);
		vec3 viewDir = normalize(camerapos - modelPos);
		vec3 halfwayDir = normalize(lightVector + viewDir);

		float distance = length(lightDir - modelPos);
		float diffuse = max(dot(normals, lightVector), 0.1);
		diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));

		float specularStrength = 0.5;
		float spec = pow(max(dot(normals, halfwayDir), 0.1), 32);
		vec3 lc = lightColor.rgb;
		vec3 specular = specularStrength * spec * lc;
		vec3 objectColor = color.rgb;
		vec3 phongresult = (ambient.rgb + diffuse + specular) * objectColor;
		color = vec4(phongresult, color.a);
	}*/
	else if(oswietlenie == 6){
		//model Blinna-Phonga
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * color.rgb;

		vec3 lightVector = normalize(lightDir - modelPos);
		float diff= max(dot(lightVector, normals), 0.0);
		vec3 diffuse = diff*color.rgb;

		vec3 viewDir = normalize(camerapos - modelPos);
		vec3 reflectDir = reflect(-lightDir, normals);
		float spec = 0.0;

		vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(normals, halfwayDir), 0.0), 32.0);
		
		vec3 specular = vec3(0.3) * spec;

		color = vec4(ambient + diffuse + specular, color.a);
	}

	if(sun){
		color = lightColor;
	}
}