//
// Created by sodino on 2021/6/17.
//
#include "jni.h"
#include <string>
#include "AppOpenGL.h"
#include <GLES3/gl3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// begin : GLSL code, constant string
const char* gVertexShader =
        // Shaders shall always begin with a version declaration. Otherwise it defaults `version 100`.
        // When some new features are used, corresponding errors will be thrown.
        // For example, `in` `out` features : 0:1: L0001: Storage qualifier not allowed in GLSL ES version 100
        "#version 320 es\n"                                 // NOTE: add \n as a line separator
        "layout(location=0) in vec4 vPosition;"
        "layout(location=1) in vec3 vColor;"
        "layout(location=2) in vec2 vTexCoordinate;"
        "out vec3 tmpColor;"                                // Just as a value transfer, so naming it with 'tmp'
        "out vec2 tmpTexCoordinate;"
        "void main() {"
        "  gl_Position = vPosition;"
        "  tmpColor = vColor;"
        "  tmpTexCoordinate = vec2(vTexCoordinate.x, vTexCoordinate.y);"
        "}\0";                                              // NOTE: Ending with '\0' indicates that this is the end of a C string.

const char* gFragmentShader =
        "#version 320 es\n"                                 // NOTE: add \n as a line separator
        "precision mediump float;"
        "in vec3 tmpColor;"
        "in vec2 tmpTexCoordinate;"
        "out vec4 fragColor;"
        "uniform sampler2D texture1;"
        "void main() {"
        "  fragColor = texture(texture1, tmpTexCoordinate);"
        "}\0";                                              // NOTE: Ending with '\0' indicates that this is the end of a C string.
// end : GLSL code

// begin : gl vertex
#define FLOAT_NUM_PER_POSITION 2  // the number of 'float' to define each position
#define FLOAT_NUM_PER_COLOR    3  // the number of 'float' to define each color
#define FLOAT_NUM_PER_TEXTURE  2  // the number of 'float' to define each texture
#define VERTEX_COUNT           6  // 2 triangles have 6 vertices
const GLfloat gTriangleVertices[] =
        {
            // positions        // colors               // textures
            -0.5f,  0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,            // top left vertex      index : 0
            -0.5f, -0.5f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,            // bottom left vertex   index : 1
             0.5f, -0.5f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f,            // bottom right vertex  index : 2
             0.5f,  0.5f,       0.0f, 0.0f, 0.0f,       0.0f, 1.0f             // top right vertex     index : 3
        };

unsigned int gIndices[] = {
        0, 1, 2, // first triangle vertex indices
        0, 2, 3  // second triangle vertex indices
};
// end : gl vertex

// begin : gl variable
GLuint gProgram;
GLuint gLocation_vPosition;
GLuint gLocation_vColor;
GLuint gLocation_vTexCoordinate;

unsigned int VAO = 0;           // vertex array object
unsigned int VBO = 0;           // vertex buffer object
unsigned int IBO = 0;           // index buffer object
unsigned int texture = 0;       //
// end : gl variable

// begin : logic variable
bool onlyDrawLine = false;
// end : logic variable

static void checkGLError(const char* tag) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        logD("%s : glError=0x%x", tag, error);
    }
}

GLuint loadGLShader(GLenum shaderType, const char* shaderCode) {
    std::string log = "glCreateShader : " + std::to_string(shaderType);
    const char* tag = log.c_str();
    // 1. create shader
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        checkGLError(tag);
        return shader;
    }

    // 2. specify shader code then compile shader code
    // the third parameter is char**, an character array, so the second parameter must specifiy the length of the array.
    glShaderSource(shader, 1, &shaderCode, NULL);
    checkGLError("glShaderSource");
    glCompileShader(shader);

    // optional : check the result of compilation, read error message
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_TRUE) {
        // do nothing
        return shader;
    }

    GLint infoLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
    if (infoLength != 0) {
        char* buf = (char*) malloc(infoLength);
        if (buf) {
            glGetShaderInfoLog(shader, infoLength, NULL, buf);
            logD("%s, compile error info : %s", tag, buf);
        }
        free(buf);
    }
    glDeleteShader(shader); // important! Delete the 'shader' that failed to compile.
    shader = 0;
    return shader;
}

GLuint createGLProgram(const char* codeVertex, const char* codeFragment) {
    GLuint shaderVertex = loadGLShader(GL_VERTEX_SHADER, gVertexShader);
    if (shaderVertex == 0) {
        logD("loadGLShader GL_VERTEX_SHADER failed.");
        return 0;
    }

    GLuint shaderFragment = loadGLShader(GL_FRAGMENT_SHADER, gFragmentShader);
    if (shaderFragment == 0) {
        logD("loadGLShader GL_FRAGMENT_SHADER failed.");
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program == 0) {
        checkGLError("glCreateProgram failed.");
        return 0;
    }

    glAttachShader(program, shaderVertex);
    checkGLError("glAttachShader shaderVertex");
    glAttachShader(program, shaderFragment);
    checkGLError("glAttachShader shaderFragment");
    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        GLint bufLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
        if (bufLength) {
            char* buf = (char*) malloc(bufLength);
            if (buf) {
                glGetProgramInfoLog(program, bufLength, NULL, buf);
                logD("Could not link program : %s", buf);
                free(buf); // Important! 'free' and 'malloc' appear in pairs.
            }
        }
        glDeleteProgram(program); // Important! Delete the 'program' that failed to link.
        program = 0;
    }

    // Delete the objects that are no longer need.
    glDeleteShader(shaderVertex);
    glDeleteShader(shaderFragment);
    return program;
}


void app_resizeGL(jint width, jint height) {
    glViewport(0, 0, width, height);
}

void app_renderClearColor() {
    static float rgb = 0.0f;
    static bool isAdd = true;
    rgb += (isAdd) ? 0.01f : -0.01f;
    if (rgb > 1.0f) {
        isAdd = false;
        rgb = 1.0f;
    } else if (rgb < 0.0f) {
        isAdd = true;
        rgb = 0.0f;
    }
    // 'glClearColor' a confusing function name. specify color value for 'glClear' action
    glClearColor(rgb, rgb, rgb, 1.0f);
    // write color specified by 'glClearColor'
    glClear(GL_COLOR_BUFFER_BIT);
}

void app_renderTriangle() {
    if (gProgram == 0) {
        return;
    }
    // as we only have a single VAO,
    // there's no need to `glUseProgram` `glBindBuffer` `glBindVertexArray` every time,
    // but we'll do so just keep things a bit more organized.

    // activate gProgram, every shader and rendering call use this program
    glUseProgram(gProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBindVertexArray(VAO);

    // draw primitives using the currently active shader,
    // the previously defined vertex attribute configuration
    GLenum glEnum = onlyDrawLine ? GL_LINE_LOOP : GL_TRIANGLES;
    // invoke `glDrawElements` instead of `glDrawArrays`
//    glDrawArrays(glEnum, 0, VERTEX_COUNT);
    glDrawElements(glEnum, VERTEX_COUNT, GL_UNSIGNED_INT, 0);
}

void app_renderGLFrame() {
    app_renderClearColor();
    app_renderTriangle();
}

// legacy way to initGL
void app_initGL() {
    if (gProgram != 0) {
        logD("app_initGL has been completed. Repeat call and return.");
        return;
    }
    gProgram = createGLProgram(gVertexShader, gFragmentShader);
    if (gProgram == 0) {
        logD("createGLProgram failed.");
        return;
    }

    // start : configuration for VAO & VBO

    // generate VAO first then VBO, because any subsequent vertex attribute calls after `glGenVertexArrays` wil be stored inside the VAO
    glGenVertexArrays(1, &VAO);
    checkGLError("glGenVertexArray");
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    checkGLError("glGenBuffers");
    // bind the VAO first, then bind and set vertex buffers(s), and then configure vertex attribute(s).
    glBindVertexArray(VAO);
    checkGLError("glBindVertexArray");

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_STATIC_DRAW);
    checkGLError("VBO glBindBuffer & glBufferData");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndices), gIndices, GL_STATIC_DRAW);
    checkGLError("IBO glBindBuffer & glBufferData");

    gLocation_vPosition = glGetAttribLocation(gProgram, "vPosition");
    checkGLError("glGetAttribLocation vPosition");
    logD("glGetAttribLocation(vPosition)=%d", gLocation_vPosition);
    glVertexAttribPointer(gLocation_vPosition,
                          FLOAT_NUM_PER_POSITION,
                          GL_FLOAT, GL_FALSE,
                          // each row has 5 float numbers to define position(s) and color(s).
                          (FLOAT_NUM_PER_POSITION + FLOAT_NUM_PER_COLOR + FLOAT_NUM_PER_TEXTURE) * sizeof(float),
                          // Beginning with position(s) float data each row, so offset is 0.
                          0);
    glEnableVertexAttribArray(gLocation_vPosition);

    gLocation_vColor = glGetAttribLocation(gProgram, "vColor");
    checkGLError("glGetAttribLocation vColor");
    logD("glGetAttribLocation(vColor)=%d", gLocation_vColor);
    glVertexAttribPointer(gLocation_vColor,
                          FLOAT_NUM_PER_COLOR,
                          GL_FLOAT, GL_FALSE,
                          // each row has 5 float numbers to define position(s) and color(s).
                          (FLOAT_NUM_PER_POSITION + FLOAT_NUM_PER_COLOR + FLOAT_NUM_PER_TEXTURE) * sizeof(float),
                          // read position(s) float data first at each row, then color's data.
                          // so offset is (positionNum * float.size)
                          (void*)(FLOAT_NUM_PER_POSITION * sizeof(float)));
    glEnableVertexAttribArray(gLocation_vColor);

    gLocation_vTexCoordinate = glGetAttribLocation(gProgram, "vTexCoordinate");
    checkGLError("glGetAttribLocation vTexCoordinate");
    logD("glGetAttribLocation(vTexCoordinate)=%d", gLocation_vTexCoordinate);
    glVertexAttribPointer(gLocation_vTexCoordinate,
                          FLOAT_NUM_PER_TEXTURE,
                          GL_FLOAT, GL_FALSE,
                          (FLOAT_NUM_PER_POSITION + FLOAT_NUM_PER_COLOR + FLOAT_NUM_PER_TEXTURE) * sizeof(float),
                          (void*)((FLOAT_NUM_PER_POSITION + FLOAT_NUM_PER_COLOR) * sizeof(float)));
    glEnableVertexAttribArray(gLocation_vTexCoordinate);

    // load and create texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    int width, height, nrChannels;
//    unsigned char *pixelData = stbi_load("/data/user/0/sodino.open.gl/cache/wall.jpg", &width, &height, &nrChannels, 0);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    stbi_image_free(pixelData);

    // unbind
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // end : configuration for VAO & VBO
}

void app_destroyGL() {
    if (gProgram != 0) {
        glDeleteProgram(gProgram);
        gProgram = 0;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    VAO = 0;
    VBO = 0;
    IBO = 0;
}

void app_onlyDrawLine(jboolean onlyLine) {
    onlyDrawLine = onlyLine;
}