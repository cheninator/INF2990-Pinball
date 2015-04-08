#define LUMIERE0_TOUCHE_PAS 0
#define AMBIANTE 1
#define DIRECTIONNELLE 2
#define SPOT 3
#define NB_LUMIERES 4

#define NOEUD_NORMAL 0
#define NOEUD_COLOR_SHIFT 1
#define NOEUD_IMPOSSIBLE 2
#define NOEUD_SELECTIONNE 3
#define NOEUD_TRANSPARENT 4
#define NOEUD_ILLUMINE 5

uniform sampler2D laTexture;
uniform int colorShift;
uniform int etatNoeud;
uniform int numeroNoeud;

uniform int etatAmbiante;
uniform int etatDirectionnelle;
uniform int etatSpot;

varying vec3 normal, eyeVec;

varying vec3 rayonReflechi[NB_LUMIERES];
varying vec3 halfVect[NB_LUMIERES];
varying vec3 lightDir[NB_LUMIERES];

void main()
{
	// Calcul de variables geometriques
	// ================================

	// Variables a calculer par fragment:
	vec3 N = (gl_FrontFacing ? normal : -normal) ;
	N = normalize(N);
	vec3 E = eyeVec;	// Vecteur pointant du fragment vers la caméra

	// Variables a calculer par lumiere
	vec3 L[NB_LUMIERES], 
		 R[NB_LUMIERES], 
		 HV[NB_LUMIERES];

	float NdotL[NB_LUMIERES],
	      NdotR[NB_LUMIERES],
		  NdotHV[NB_LUMIERES],
		  distance[NB_LUMIERES];


	// Lumiere Ambiante
	L[AMBIANTE] = vec3(0);
	R[AMBIANTE] = vec3(0);
	HV[AMBIANTE] = vec3(0);

	// Lumiere Directionnelle
	L[DIRECTIONNELLE] = normalize(gl_LightSource[DIRECTIONNELLE].spotDirection);
	R[DIRECTIONNELLE] = normalize(rayonReflechi[DIRECTIONNELLE]);
	HV[DIRECTIONNELLE] = normalize(halfVect[DIRECTIONNELLE]);

	// Lumiere Spot
	L[SPOT] = normalize(lightDir[SPOT]);
	R[SPOT] = normalize(rayonReflechi[SPOT]);
	HV[SPOT] = normalize(halfVect[SPOT]);
	distance[SPOT] = length(lightDir[SPOT]);

	for(int i = AMBIANTE ; i < NB_LUMIERES; i++)
	{
		NdotL[i] = dot(N,L[i]);
		NdotHV[i] = dot(N, HV[i]);
		NdotR[i] = dot(N,R[i]);
	}

	// Obtention de la couleur de la texture
	// =====================================

	vec4 textureColor = texture2D( laTexture, gl_TexCoord[0].st );



	// Calcul de lumiere:
	// ==================

	vec4 lumiereReflechie[NB_LUMIERES];
	for(int i = AMBIANTE; i < NB_LUMIERES ; i++) 
		lumiereReflechie[i] = vec4(0);

	// Lumiere AMBIANTE
	// ================

	vec4 composanteAmbiante = gl_LightSource[AMBIANTE].ambient*textureColor;
	vec4 composanteDiffuse = vec4(0);
	vec4 composanteSpeculaire = vec4(0);
	lumiereReflechie[AMBIANTE] = composanteAmbiante;

	// Lumiere DIRECTIONNELLE
	// ======================

	composanteAmbiante = gl_LightSource[DIRECTIONNELLE].ambient*textureColor;
	composanteDiffuse = max(-NdotL[DIRECTIONNELLE], 0.0) * gl_LightSource[DIRECTIONNELLE].diffuse*textureColor;
	composanteSpeculaire = pow(max(NdotR[DIRECTIONNELLE], 0.0),1000.0) * gl_LightSource[DIRECTIONNELLE].specular;
	lumiereReflechie[DIRECTIONNELLE] += clamp(composanteAmbiante, 0.0,1.0);
	lumiereReflechie[DIRECTIONNELLE] += clamp(composanteDiffuse, 0.0,1.0);
	lumiereReflechie[DIRECTIONNELLE] += clamp(composanteSpeculaire, 0.0,1.0);

	// Lumiere SPOT
	// ============

	// Effet spot
	// Cos de l'angle entre le rayon de lumiere et l'axe du spot
	float cosGamma = dot( -L[SPOT], normalize(gl_LightSource[SPOT].spotDirection));

	// Variables des formules du TP pour direct3D
	float c = gl_LightSource[SPOT].spotExponent;							// Pour racourcir les formules
	float cosDelta = gl_LightSource[SPOT].spotCosCutoff;					// cos de l'angle d'ouverture du cone
	float cosInner = cosDelta;
	float cosOuter = pow(cosDelta, 1.01 + clamp(c/2.0, 0.0,4.0));	
	float effetSpot = clamp((cosGamma - cosOuter)/(cosInner - cosOuter),0.0,1.0);  // Vaut 0 quand cosGamma == cosOuter, vaut 1 quand cosGamma == cosInner

	composanteAmbiante = gl_LightSource[SPOT].ambient*textureColor; // ROUGE
	composanteDiffuse = max(NdotL[SPOT],0.0) * gl_LightSource[SPOT].diffuse*textureColor; 
	composanteSpeculaire = pow(max(NdotHV[SPOT], 0.0),10.0) * gl_LightSource[SPOT].specular;
	lumiereReflechie[SPOT] += effetSpot*clamp(composanteAmbiante, 0.0, 1.0) ;
	lumiereReflechie[SPOT] += effetSpot*clamp(composanteDiffuse, 0.0, 1.0);
	lumiereReflechie[SPOT] += effetSpot*clamp(composanteSpeculaire, 0.0, 1.0);

	// Calcul d'effets a appliquer a la couleur
	// ========================================

	vec4 colorMask = vec4(1.0);
	if(colorShift == 1) colorMask = vec4(0.0,0.5,1.0,1.0);
	if(etatNoeud == NOEUD_IMPOSSIBLE) colorMask = vec4(1.0,0.5,0.5,1.0);
	float colorMultiplier = 1.0;
	if(etatNoeud == NOEUD_SELECTIONNE || etatNoeud == NOEUD_ILLUMINE)
		colorMask *= vec4( 2.5, 3.5, 2.5, 1.0);
	if(etatNoeud == NOEUD_TRANSPARENT)
		colorMask *= vec4(1.0, 0.5, 1.0, 1.0);

	// Calcul de la couleur finale du fragment selon les lumieres et les effets.
	// =========================================================================

	vec4 couleurFinale = vec4(0);

	if(etatAmbiante != 1)
		couleurFinale += lumiereReflechie[AMBIANTE];
	if(etatDirectionnelle != 1)
		couleurFinale += lumiereReflechie[DIRECTIONNELLE];
	if(etatSpot != 1)
		couleurFinale += lumiereReflechie[SPOT];

	gl_FragColor = colorMask*couleurFinale ;
}