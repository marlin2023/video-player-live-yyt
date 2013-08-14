//#include <jni.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//#include <stdlib.h>
//#include <android/log.h>
////#include "common.h"
//#include "com_chris_triangle_GLLib.h"
//// 全局变量
//GLuint _gProgramObject;
//
////
////
//GLuint loadShader(GLenum shaderType, const char* pSource) {
//    GLuint shader;
//    GLint compiled;
//
//
//    //  创建着色器
//    shader = glCreateShader(shaderType);
//    if (shader) {
//        glShaderSource(shader, 1, &pSource, NULL);
//        glCompileShader(shader);
//        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//        if (!compiled) {
//            GLint infoLen = 0;
//            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
//            if (infoLen > 1) {
//                char* infoLog = (char*) malloc(infoLen);
//                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
//
//                __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"Could not compile shader %d:\n%s\n",
//                				shaderType, infoLog);
//                free(infoLog);
//                glDeleteShader(shader);
//                shader = 0;
//            }
//        }
//    }
//    return shader;
//}
//
//int init()
//{
//	const char vShaderStr[] =
//	"attribute vec4 vPosition;                   \n"
//	"void main()                                 \n"
//	"{                                           \n"
//	"    gl_Position = vPosition;                \n"
//	"}                                           \n";
//
//	const char fShaderStr[] =
//	"precision mediump float;                    \n"
//	"void main()                                 \n"
//	"{                                           \n"
//	"    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
//	"}                                           \n";
//
//	 GLuint vertexShader;
//	 GLuint fragmentShader;
//	 GLuint programObject;
//	 GLint linked;
//
//	 // load vetex / fragment shaders
//	 vertexShader = loadShader(GL_VERTEX_SHADER, vShaderStr);
//	 fragmentShader = loadShader(GL_FRAGMENT_SHADER, fShaderStr);
//
//	 //
//	 programObject = glCreateProgram();
//
//	 glAttachShader(programObject, vertexShader);
//	 glAttachShader(programObject, fragmentShader);
//
//	 //
//	 glBindAttribLocation(programObject, 0, "vPosition");
//
//	 //
//	 glLinkProgram(programObject);
//
//	 glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
//	 if (!linked) {
//		//  LOGE("error when link program");
//		  __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"error when link program");
//		  glDeleteProgram(programObject);
//	 }
//
//	 _gProgramObject = programObject;
//	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//}
//
////
////
////
//void draw()
//{
//	 GLfloat vVertices[] =
//	 {
//		0.0f,  0.5f,  0.0f,
//	   -0.5f, -0.5f,  0.0f,
//		0.5f, -0.5f,  0.0f
//	 };
//
//	 glClear(GL_COLOR_BUFFER_BIT);
//
//	 glUseProgram(_gProgramObject);
//
//	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
//	 glEnableVertexAttribArray(0);
//	 glDrawArrays(GL_TRIANGLES, 0, 3);
//}

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum {
    ATTRIB_VERTEX,
    ATTRIB_TEXTURE,
};


static GLuint g_texYId;
static GLuint g_texUId;
static GLuint g_texVId;
static GLuint simpleProgram;

static char *              g_buffer = NULL;
static int                 g_width = 0;
static int                 g_height = 0;


static void checkGlError(const char* op)
{
    GLint error;
    for (error = glGetError(); error; error = glGetError())
    {
//        log("error::after %s() glError (0x%x)\n", op, error);
        __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"error::after %s() glError (0x%x)\n", op, error);
    }
}

static GLuint bindTexture(GLuint texture, const char *buffer, GLuint w , GLuint h)
{
//  GLuint texture;
//  glGenTextures ( 1, &texture );
    checkGlError("glGenTextures");
    glBindTexture ( GL_TEXTURE_2D, texture );
    checkGlError("glBindTexture");
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
    checkGlError("glTexImage2D");
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    checkGlError("glTexParameteri");
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    checkGlError("glTexParameteri");
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    checkGlError("glTexParameteri");
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    checkGlError("glTexParameteri");
    //glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}



static void renderFrame()
{
#if 0
    // Galaxy Nexus 4.2.2
    static GLfloat squareVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
    };

    static GLfloat coordVertices[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
    };
#else
 // HUAWEIG510-0010 4.1.1
    static GLfloat squareVertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
    };

    static GLfloat coordVertices[] = {
            -1.0f, 1.0f,
            1.0f, 1.0f,
            -1.0f,  -1.0f,
            1.0f,  -1.0f,
    };
#endif

    glClearColor(1.0f, 0.0f, 0.0f, 1);
    checkGlError("glClearColor");
    glClear(GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");
    //PRINTF("setsampler %d %d %d", g_texYId, g_texUId, g_texVId);
    GLint tex_y = glGetUniformLocation(simpleProgram, "SamplerY");
    checkGlError("glGetUniformLocation");
    GLint tex_u = glGetUniformLocation(simpleProgram, "SamplerU");
    checkGlError("glGetUniformLocation");
    GLint tex_v = glGetUniformLocation(simpleProgram, "SamplerV");
    checkGlError("glGetUniformLocation");


    glBindAttribLocation(simpleProgram, ATTRIB_VERTEX, "vPosition");
    checkGlError("glBindAttribLocation");
    glBindAttribLocation(simpleProgram, ATTRIB_TEXTURE, "a_texCoord");
    checkGlError("glBindAttribLocation");

    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    checkGlError("glEnableVertexAttribArray");

    glVertexAttribPointer(ATTRIB_TEXTURE, 2, GL_FLOAT, 0, 0, coordVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(ATTRIB_TEXTURE);
    checkGlError("glEnableVertexAttribArray");

    glActiveTexture(GL_TEXTURE0);
    checkGlError("glActiveTexture");
    glBindTexture(GL_TEXTURE_2D, g_texYId);
    checkGlError("glBindTexture");
    glUniform1i(tex_y, 0);
    checkGlError("glUniform1i");

    glActiveTexture(GL_TEXTURE1);
    checkGlError("glActiveTexture");
    glBindTexture(GL_TEXTURE_2D, g_texUId);
    checkGlError("glBindTexture");
    glUniform1i(tex_u, 1);
    checkGlError("glUniform1i");

    glActiveTexture(GL_TEXTURE2);
    checkGlError("glActiveTexture");
    glBindTexture(GL_TEXTURE_2D, g_texVId);
    checkGlError("glBindTexture");
    glUniform1i(tex_v, 2);
    checkGlError("glUniform1i");

    //glEnable(GL_TEXTURE_2D);
    //checkGlError("glEnable");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays");
}

static GLuint buildShader(const char* source, GLenum shaderType)
{
    GLuint shaderHandle = glCreateShader(shaderType);

    if (shaderHandle)
    {
        glShaderSource(shaderHandle, 1, &source, 0);
        glCompileShader(shaderHandle);

        GLint compiled = 0;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shaderHandle, infoLen, NULL, buf);
//                    log_easy("error::Could not compile shader %d:\n%s\n", shaderType, buf);
                    __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"error::Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shaderHandle);
                shaderHandle = 0;
            }
        }

    }

    return shaderHandle;
}

static GLuint buildProgram(const char* vertexShaderSource,
        const char* fragmentShaderSource)
{
    GLuint vertexShader = buildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = buildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    GLuint programHandle = glCreateProgram();

    if (programHandle)
    {
        glAttachShader(programHandle, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(programHandle, fragmentShader);
        checkGlError("glAttachShader");
        glLinkProgram(programHandle);

        GLint linkStatus = GL_FALSE;
        glGetProgramiv(programHandle, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(programHandle, bufLength, NULL, buf);
//                    log_easy("error::Could not link program:\n%s\n", buf);
                    __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"error::Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(programHandle);
            programHandle = 0;
        }

    }

    return programHandle;
}

static  char * readYUV(const char *path)
{

    FILE *fp;
    char * buffer;
    long size = 1280 * 720 * 3 / 2;

    if((fp=fopen(path,"rb"))==NULL)
    {
//        log("cant open the file");
    	 __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"cant open the file");
       exit(0);
    }

    buffer = (char *)malloc(size);
    memset(buffer,'\0',size);
    long len = fread(buffer,1,size,fp);
    //PRINTF("read data size:%ld", len);
    fclose(fp);
    return buffer;
}

void gl_initialize()
{
    g_buffer = NULL;

    static const char* FRAG_SHADER =
        "varying lowp vec2 tc;\n"
        "uniform sampler2D SamplerY;\n"
        "uniform sampler2D SamplerU;\n"
        "uniform sampler2D SamplerV;\n"
        "void main(void)\n"
        "{\n"
            "mediump vec3 yuv;\n"
            "lowp vec3 rgb;\n"
            "yuv.x = texture2D(SamplerY, tc).r;\n"
            "yuv.y = texture2D(SamplerU, tc).r - 0.5;\n"
            "yuv.z = texture2D(SamplerV, tc).r - 0.5;\n"
            "rgb = mat3( 1,   1,   1,\n"
                        "0,       -0.39465,  2.03211,\n"
                        "1.13983,   -0.58060,  0) * yuv;\n"
            "gl_FragColor = vec4(rgb, 1);\n"
        "}\n";

    static const char* VERTEX_SHADER =
          "attribute vec4 vPosition;    \n"
          "attribute vec2 a_texCoord;   \n"
          "varying vec2 tc;     \n"
          "void main()                  \n"
          "{                            \n"
          "   gl_Position = vPosition;  \n"
          "   tc = a_texCoord;  \n"
          "}                            \n";


    simpleProgram = buildProgram(VERTEX_SHADER, FRAG_SHADER);
    glUseProgram(simpleProgram);
    glGenTextures(1, &g_texYId);
    glGenTextures(1, &g_texUId);
    glGenTextures(1, &g_texVId);
}

void gl_uninitialize()
{

    g_width = 0;
    g_height = 0;

    if (g_buffer)
    {
        free(g_buffer);
        g_buffer = NULL;
    }
}
//设置图像数据
void gl_set_framebuffer(const char* buffer, int buffersize, int width, int height)
{

    if (g_width != width || g_height != height)
    {
        if (g_buffer)
            free(g_buffer);

        g_width = width;
        g_height = height;

        g_buffer = (char *)malloc(buffersize);
    }

    if (g_buffer)
        memcpy(g_buffer, buffer, buffersize);

}
//画屏
void gl_render_frame()
{
//    if (0 == g_width || 0 == g_height)
//        return;

	g_width = 176;
	g_height = 144;
#if 1
    int width = 176;
    int height = 144;
    static char *buffer = NULL;

    if (NULL == buffer)
    {
        char filename[128] = {0};
        strcpy(filename, "/sdcard/176x144.yuv");
        buffer = readYUV(filename);
    }

#else
    const char *buffer = g_buffer;
    int width = g_width;
    int height = g_height;
#endif
//    glViewport(0, 0, width, height);
//    glViewport(10, 50, 640, 360); //Android 缺省将viewport 设置成和显示屏幕大小一致
    bindTexture(g_texYId, buffer, width, height);
    bindTexture(g_texUId, buffer + width * height, width/2, height/2);
    bindTexture(g_texVId, buffer + width * height * 5 / 4, width/2, height/2);
   renderFrame();
}



int init()
{
	gl_initialize();
}

//
//
//
void draw()
{

	gl_render_frame();

//
//	 GLfloat vVertices[] =
//	 {
//		0.0f,  0.5f,  0.0f,
//	   -0.5f, -0.5f,  0.0f,
//		0.5f, -0.5f,  0.0f
//	 };
//
//	 glClear(GL_COLOR_BUFFER_BIT);
//
//	 glUseProgram(_gProgramObject);
//
//	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
//	 glEnableVertexAttribArray(0);
//	 glDrawArrays(GL_TRIANGLES, 0, 3);
}


#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_opengl_1_GLLib
 * Method:    init
 * Signature: (II)V
 */
//JNIEXPORT void JNICALL Java_com_example_opengl_11_GLLib_init
JNIEXPORT void JNICALL Java_com_chris_triangle_GLLib_init
  (JNIEnv * env, jclass object, jint width, jint height)
{
// LOGI("init: %d , %d", width, height);
 __android_log_print(ANDROID_LOG_ERROR ,"chris_magic" ,"init: %d , %d", width, height);
 glViewport(0, 0, width, height);
 init();
}

/*
 * Class:     com_example_opengl_1_GLLib
 * Method:    draw
 * Signature: ()V
 */
//JNIEXPORT void JNICALL Java_com_example_opengl_11_GLLib_draw
JNIEXPORT void JNICALL Java_com_chris_triangle_GLLib_draw
  (JNIEnv * env, jclass object)
{
 __android_log_print(ANDROID_LOG_WARN ,"chris_magic" ,"GLib_draw");  //ANDROID_LOG_INFO
 draw();
}

#ifdef __cplusplus
}

#endif
