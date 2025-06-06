#include "quadDepth.h" 

QDepth::QDepth()
{
	quadMod.load("Assets/quad.obj");
	quadTex.id = gRenderer.depthMap;
	quadTex.width = 1024; 
	quadTex.height = 1024; 
	quadTex.alpha = false;

	quadObj.reference(quadMod); 
	quadObj.reference(quadTex);
	quadObj.shaders.load("Shader/quad_vs.glsl", "Shader/quad_fs.glsl");
	quadObj.transform.scale = 5.0f;  
	quadObj.transform.position = Vector(0, 4.0, -10); 
}

QDepth::~QDepth()
{

}

void QDepth::update()
{
	//quadObj.transform.position = Vector(0, 0, 10);
}

void QDepth::queue()
{
	gRenderer.queue(quadObj, MatrixPath::LE_MAT_3D_TRS);
}
