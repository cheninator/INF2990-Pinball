#define LUMIERE0_TOUCHE_PAS 0
#define AMBIANTE 1
#define DIRECTIONNELLE 2
#define SPOT_A 3
#define SPOT_B 4
#define NB_LUMIERES 5

// uniform gl_LightSourceParameters gl_LightSource[5];

varying vec3 normal, eyeVec;

varying vec3 rayonReflechi[NB_LUMIERES];
varying vec3 halfVect[NB_LUMIERES];
varying vec3 lightDir[NB_LUMIERES];

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;

	vec3 ecPosition = vec3( gl_ModelViewMatrix * gl_Vertex );

	normal = normalize(gl_NormalMatrix * gl_Normal);
	eyeVec = normalize(-ecPosition);

	lightDir[DIRECTIONNELLE] = -gl_LightSource[DIRECTIONNELLE].spotDirection.xyz;
	lightDir[SPOT_A] = vec3(gl_LightSource[SPOT_A].position.xyz - ecPosition);
	lightDir[SPOT_B] = vec3(gl_LightSource[SPOT_B].position.xyz - ecPosition);

	for(int i = AMBIANTE; i < NB_LUMIERES; i++)
	{
		rayonReflechi[i] = -reflect( lightDir[i], normal);
		halfVect[i] = normalize(normalize(lightDir[i]) + eyeVec);
	}

	gl_TexCoord[0] = gl_MultiTexCoord0;
}