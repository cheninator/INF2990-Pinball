uniform sampler2D laTexture;
void main()
{
	gl_FragColor = gl_LightSource[1].diffuse * texture2D( laTexture, gl_TexCoord[0].st ); // vec4(0.7,0.7,0.7,1.0);
}