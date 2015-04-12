#define LUMIERE0_TOUCHE_PAS 0
#define AMBIANTE 1
#define DIRECTIONNELLE 2
#define SPOT_A 3
#define SPOT_B 4

#define NB_LUMIERES 5

#define NOEUD_NORMAL 0
#define NOEUD_COLOR_SHIFT 1
#define NOEUD_IMPOSSIBLE 2
#define NOEUD_SELECTIONNE 3
#define NOEUD_TRANSPARENT 4
#define NOEUD_ILLUMINE 5
//uniform gl_LightSourceParameters gl_LightSource[5];

uniform sampler2D laTexture;
uniform int colorShift;
uniform int etatNoeud;
uniform int numeroNoeud;

uniform int etatAmbiante;
uniform int etatDirectionnelle;
uniform int etatSpot;
uniform int estTable;

uniform int skybox;

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
	vec3 E = normalize(eyeVec);	// Vecteur pointant du fragment vers la caméra

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
	R[DIRECTIONNELLE] = normalize(reflect(L[DIRECTIONNELLE],N));
	HV[DIRECTIONNELLE] = normalize(-L[DIRECTIONNELLE] + E);

	// Lumiere Spot
	L[SPOT_A] = normalize(lightDir[SPOT_A]);
	R[SPOT_A] = normalize(reflect(L[SPOT_A],N));
	HV[SPOT_A] = normalize(L[SPOT_A] + E);
	distance[SPOT_A] = length(lightDir[SPOT_A]);

	L[SPOT_B] = normalize(lightDir[SPOT_B]);
	R[SPOT_B] = normalize(reflect(L[SPOT_B],N));
	HV[SPOT_B] = normalize(L[SPOT_B] + E);
	distance[SPOT_B] = length(lightDir[SPOT_B]);


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
	composanteSpeculaire = pow(max(NdotHV[DIRECTIONNELLE], 0.0),100.0) * gl_LightSource[DIRECTIONNELLE].specular;
	lumiereReflechie[DIRECTIONNELLE] += clamp(composanteAmbiante, 0.0,1.0);
	lumiereReflechie[DIRECTIONNELLE] += clamp(composanteDiffuse, 0.0,1.0);
	// if(estTable != 1)
	lumiereReflechie[DIRECTIONNELLE] += clamp(composanteSpeculaire, 0.0,1.0);

	// Lumiere SPOT_A
	// ==============

	// Effet spot
	// Cos de l'angle entre le rayon de lumiere et l'axe du spot
	float cosGammaA = dot( -L[SPOT_A], normalize(gl_LightSource[SPOT_A].spotDirection));

	// Variables des formules du TP pour direct3D
	float cA = gl_LightSource[SPOT_A].spotExponent;							// Pour racourcir les formules
	float cosDeltaA = gl_LightSource[SPOT_A].spotCosCutoff;					// cos de l'angle d'ouverture du cone
	float cosInnerA = cosDeltaA;
	float cosOuterA = pow(cosDeltaA, 1.01 + clamp(cA/2.0, 0.0,4.0));	
	float effetSpotA = clamp((cosGammaA - cosOuterA)/(cosInnerA - cosOuterA),0.0,1.0);  // Vaut 0 quand cosGamma == cosOuter, vaut 1 quand cosGamma == cosInner


	float cosChi = 0.9996;
	float cosXi = 0.9995;

	float effetSpotOmbreBilleA = 1.0;
	if(estTable == 1)
	effetSpotOmbreBilleA = clamp((cosChi - cosGammaA)/(cosChi - cosXi),0.0,1.0);



	composanteAmbiante = gl_LightSource[SPOT_A].ambient*textureColor; // ROUGE
	composanteDiffuse = max(NdotL[SPOT_A],0.0) * gl_LightSource[SPOT_A].diffuse*textureColor; 
	composanteSpeculaire = pow(max(NdotHV[SPOT_A], 0.0),50.0) * gl_LightSource[SPOT_A].specular;
	lumiereReflechie[SPOT_A] += effetSpotOmbreBilleA*effetSpotA*clamp(composanteAmbiante, 0.0, 1.0) ;
	lumiereReflechie[SPOT_A] += effetSpotOmbreBilleA*effetSpotA*clamp(composanteDiffuse, 0.0, 1.0);
	// if(estTable != 1)
	lumiereReflechie[SPOT_A] += effetSpotOmbreBilleA*effetSpotA*clamp(composanteSpeculaire, 0.0, 1.0);

	// Lumiere SPOT_B
	// ==============

	// Effet spot
	// Cos de l'angle entre le rayon de lumiere et l'axe du spot
	float cosGammaB = dot( -L[SPOT_B], normalize(gl_LightSource[SPOT_B].spotDirection));

	// Variables des formules du TP pour direct3D
	float cB = gl_LightSource[SPOT_B].spotExponent;							// Pour racourcir les formules
	float cosDeltaB = gl_LightSource[SPOT_B].spotCosCutoff;					// cos de l'angle d'ouverture du cone
	float cosInnerB = cosDeltaB;
	float cosOuterB = pow(cosDeltaB, 1.01 + clamp(cB/2.0, 0.0,4.0));	
	float effetSpotB = clamp((cosGammaB - cosOuterB)/(cosInnerB - cosOuterB),0.0,1.0);  // Vaut 0 quand cosGamma == cosOuter, vaut 1 quand cosGamma == cosInner

	float effetSpotOmbreBilleB = 1.0;
	if(estTable == 1)
	effetSpotOmbreBilleB = clamp((cosChi - cosGammaB)/(cosChi - cosXi),0.0,1.0);

	composanteAmbiante = gl_LightSource[SPOT_B].ambient*textureColor; // ROUGE
	composanteDiffuse = max(NdotL[SPOT_B],0.0) * gl_LightSource[SPOT_B].diffuse*textureColor; 
	composanteSpeculaire = pow(max(NdotHV[SPOT_B], 0.0),50.0) * gl_LightSource[SPOT_B].specular;
	lumiereReflechie[SPOT_B] += effetSpotOmbreBilleB*effetSpotB*clamp(composanteAmbiante, 0.0, 1.0) ;
	lumiereReflechie[SPOT_B] += effetSpotOmbreBilleB*effetSpotB*clamp(composanteDiffuse, 0.0, 1.0);
	if(estTable != 1)
	lumiereReflechie[SPOT_B] += effetSpotOmbreBilleB*effetSpotB*clamp(composanteSpeculaire, 0.0, 1.0);

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
	{
		couleurFinale += lumiereReflechie[SPOT_A];
		couleurFinale += lumiereReflechie[SPOT_B];
	}

	if(skybox == 1)
	{
		gl_FragColor = vec4(0.3,1.0,1.0,1.0)*textureColor;
	}
	else
	{
		gl_FragColor = colorMask*couleurFinale ;
	}
}