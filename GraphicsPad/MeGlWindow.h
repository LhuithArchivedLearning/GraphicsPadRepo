#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <GL\glew.h>
#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>
#include <QtDeclarative\qdeclarativeview.h>
#include <string>

class MyModel;

class MeGlWindow : public QGLWidget
{
	Q_OBJECT
	QTimer mytimer;
	void sendDataToOpenGL();
	bool checkStatus(GLuint objectID,
		PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
		GLenum statusType);
	bool checkShaderStatus(GLint shaderID);
	bool checkProgramStatus(GLint programID);
	std::string readShaderCode(const char* fileName);
	void installShaders();
	MyModel* theModel;
private slots:
	void update();
protected:
	void initializeGL();
	void paintGL();
	void mouseMoveEvent(QMouseEvent*);
	//void keyPressEvent(QKeyEvent*);
	void keyPressEvent();
public:
	MeGlWindow(MyModel* theModel);
	 ~MeGlWindow();

};

#endif
