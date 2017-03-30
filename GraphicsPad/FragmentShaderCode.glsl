	#version 430
	
	out vec4 daColor;
	in vec3 normalWorld;
	in vec3 vertexPositionWorld;
	in vec4 vertexColorOut;

	uniform vec4 ambientLight;
	uniform vec3 eyePositionWorld;
    uniform vec3 lightPositionWorld;

	void main()
	{

	//Diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);
	
	//Specular
	vec3 relfectedLightVector = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = clamp(pow(dot(relfectedLightVector, eyeVectorWorld), 52), 0, 1);
	vec4 specularlight = vec4(0, 0, s, 1.0);

	daColor =  ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularlight, 0, 1);
	
	}
