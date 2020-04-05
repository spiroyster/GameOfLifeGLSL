#include "..\..\include\cgol.hpp"

#include <Windows.h>
#include <gl\GL.h>
#include "glext.h"
#include "wglext.h"

#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace
{
const char* vertexShaderSyntax = R"(
	#version 410 core

    in vec3 inP;
    in vec2 inUV;
    out vec2 UV;

    void main()
    {
	    gl_Position = vec4(inP, 1.0);
	    UV = inUV;
    }
)";

const char* fragmentShaderSyntax = R"(
	#version 430 core

	uniform sampler2D frame;

	in vec2 UV;
	out vec4 frag;

	void main()
	{
		frag = vec4(1.0, 0, 0, 0);
	}
)";

class GLFunc
{
public:
	GLFunc()
	{
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");

		
		/*glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
		glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
		glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
		glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
		glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
		glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
		glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)wglGetProcAddress("glFramebufferTexture");
		glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers");
		glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
		glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)wglGetProcAddress("glUniformMatrix2fv");
		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
		glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
		glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
		glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
		glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
		glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
		glUniform2i = (PFNGLUNIFORM2IPROC)wglGetProcAddress("glUniform2i");
		glUniform3i = (PFNGLUNIFORM3IPROC)wglGetProcAddress("glUniform3i");
		glUniform4i = (PFNGLUNIFORM4IPROC)wglGetProcAddress("glUniform4i");
		glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");*/

	}

	PFNGLCREATEPROGRAMPROC glCreateProgram;
	PFNGLCREATESHADERPROC glCreateShader;
	PFNGLSHADERSOURCEPROC glShaderSource;
	PFNGLCOMPILESHADERPROC glCompileShader;
	PFNGLATTACHSHADERPROC glAttachShader;
	PFNGLDETACHSHADERPROC glDetachShader;
	PFNGLLINKPROGRAMPROC glLinkProgram;
	PFNGLUSEPROGRAMPROC glUseProgram;
	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
	PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
	PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
	PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
	PFNGLDRAWBUFFERSPROC glDrawBuffers;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	PFNGLBINDBUFFERPROC glBindBuffer;
	PFNGLBUFFERDATAPROC glBufferData;
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
	PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
	PFNGLGETSHADERIVPROC glGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	PFNGLGETPROGRAMIVPROC glGetProgramiv;
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	PFNGLGENBUFFERSPROC glGenBuffers;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
	PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
	PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
	PFNGLUNIFORM1FPROC glUniform1f;
	PFNGLUNIFORM2FPROC glUniform2f;
	PFNGLUNIFORM3FPROC glUniform3f;
	PFNGLUNIFORM4FPROC glUniform4f;
	PFNGLUNIFORM1IPROC glUniform1i;
	PFNGLUNIFORM2IPROC glUniform2i;
	PFNGLUNIFORM3IPROC glUniform3i;
	PFNGLUNIFORM4IPROC glUniform4i;
	PFNGLACTIVETEXTUREPROC glActiveTexture;
	PFNGLDELETESHADERPROC glDeleteShader;
};

	void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

}

int main(void)
{
	unsigned int width = 1024, height = 1024;

	// Create our CGOL field...
	cgol::field f(width, height);

	
	GLFWwindow* window;
	GLuint vertexBuffer, uvBuffer, indexBuffer, vertexShader, fragmentShader, shaderProgram, vertexAttributeObject, frameTexture;
	
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(width, height, "Game of Life", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	//gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);


	// Create our GL extensions...
	std::unique_ptr<GLFunc> gl = std::make_unique<GLFunc>();
	
	// Create our geometry...
	std::vector<float> vertices({ -1.0, -1.0, 0, 1.0, -1.0, 0, 1.0, 1.0, 0, -1.0, 1.0, 0 });
	std::vector<float> uvs({ 0, 0, 1.0, 0, 1.0, 1.0, 0, 1.0 });
	std::vector<unsigned int> indices({ 0, 1, 2, 2, 3, 0 });

	gl->glGenVertexArrays(1, &vertexAttributeObject);
	gl->glBindVertexArray(vertexAttributeObject);

	// Cache the points...
	gl->glGenBuffers(1, &vertexBuffer);
	gl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	gl->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	gl->glEnableVertexAttribArray(0);
	gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Cache the UVs...
	gl->glGenBuffers(1, &uvBuffer);
	gl->glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	gl->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
	gl->glEnableVertexAttribArray(1);
	gl->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Cache the geometry...
	gl->glGenBuffers(1, &indexBuffer);
	gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	gl->glBindBuffer(GL_ARRAY_BUFFER, NULL);
	gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	gl->glBindVertexArray(NULL);

	// Create our shaders...
	vertexShader = gl->glCreateShader(GL_VERTEX_SHADER);
	gl->glShaderSource(vertexShader, 1, &vertexShaderSyntax, NULL);
	gl->glCompileShader(vertexShader);

	fragmentShader = gl->glCreateShader(GL_FRAGMENT_SHADER);
	gl->glShaderSource(fragmentShader, 1, &fragmentShaderSyntax, NULL);
	gl->glCompileShader(fragmentShader);

	shaderProgram = gl->glCreateProgram();
	gl->glAttachShader(shaderProgram, vertexShader);
	gl->glAttachShader(shaderProgram, fragmentShader);
	gl->glLinkProgram(shaderProgram);

	//// Create the texture...
	//glGenTextures(1, &frameTexture);
	//glBindTexture(GL_TEXTURE_2D, frameTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, f.width(), f.height(), 0, GL_RED, GL_UNSIGNED_BYTE, &f.data()[0]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glBindTexture(GL_TEXTURE_2D, NULL);

	//// Assign the frame uniform...
	//int location = gl->glGetUniformLocation(shaderProgram, "frame");
	//if (location < 0)
	//	OutputDebugString("Unable to find uniform location :(");
	//else
	//	gl->glUniform1i(location, frameTexture);

	// Main loop...
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		// Calculate the projection matrix...

		// assign the uniform...
		gl->glUseProgram(shaderProgram);
		gl->glBindVertexArray(vertexAttributeObject);
		gl->glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		// Assign the texture...
		//gl->glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, frameTexture);
		
		//SetUniform("quadTexture", calibrationTexture_);

		// draw!
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		gl->glBindVertexArray(NULL);
		gl->glUseProgram(NULL);
		


		// iterate field...
		//f.iterate();

		// update texutre



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);

}