
#include "shadericosphere.h"
#include <iostream>
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

#define deg2rad(x) float(M_PI)*(x)/180.f

static const char* vertexshader_source ="#version 410 core\n\
        layout (location = 0) in vec3 Position;\n\
        uniform mat4 model;\n\
        uniform mat4 view;\n\
        uniform mat4 projection;\n\
        out vec3 vPosition;\n\
void main()\n\
{\n\
            // Note that we read the multiplication from right to left\n\
            vec4 p = model*vec4(Position, 1.0f);\n\
            vPosition = (p / p.w).xyz;\n\
}\n";

static const char * tesselationControlShader = "#version 410 core\n\
        layout(vertices = 3) out;\n\
        in vec3 vPosition[];\n\
        out vec3 tcPosition[];\n\
        uniform float subdivision;\n\
\n\
#define ID gl_InvocationID\n\
\n\
void main()\n\
{\n\
            tcPosition[ID] = vPosition[ID];\n\
        if (ID == 0) {\n\
            gl_TessLevelInner[0] = subdivision;\n\
            gl_TessLevelOuter[0] = subdivision;\n\
            gl_TessLevelOuter[1] = subdivision;\n\
            gl_TessLevelOuter[2] = subdivision;\n\
        }\n\
}\n";
//

static const char * tesselationEvaluationShader = "#version 410 core\n\
        layout(triangles, equal_spacing, cw) in;\n\
        in vec3 tcPosition[];\n\
        out vec3 tePosition;\n\
        out vec3 tePatchDistance;\n\
        uniform mat4 model;\n\
        uniform mat4 view;\n\
        uniform mat4 projection;\n\
        \n\
void main()\n\
{\n\
    vec3 p0 = gl_TessCoord.x * tcPosition[0];\n\
    vec3 p1 = gl_TessCoord.y * tcPosition[1];\n\
    vec3 p2 = gl_TessCoord.z * tcPosition[2];\n\
    tePatchDistance = gl_TessCoord;\n\
    tePosition = normalize(p0 + p1 + p2);\n\
    gl_Position = projection * model * view * vec4(tePosition, 1.0f);\n\
}\n";
//

static const char * geometryShader = "#version 410 core\n\
        uniform mat4 model;\n\
        uniform mat4 view;\n\
        uniform mat3 NormalMatrix;\n\
        layout(triangles) in;\n\
        layout(triangle_strip, max_vertices = 3) out;\n\
        in vec3 tePosition[3];\n\
        in vec3 tePatchDistance[3];\n\
        out vec3 gFacetNormal;\n\
        out vec3 gPatchDistance;\n\
        out vec3 gTriDistance;\n\
void main()\n\
{\n\
    vec3 A = tePosition[2] - tePosition[0];\n\
    vec3 B = tePosition[1] - tePosition[0];\n\
    gFacetNormal = NormalMatrix * normalize(cross(A, B));\n\
    \n\
    gPatchDistance = tePatchDistance[0];\n\
    gTriDistance = vec3(1, 0, 0);\n\
    gl_Position = gl_in[0].gl_Position; \n\
    EmitVertex();\n\
\n\
    gPatchDistance = tePatchDistance[1];\n\
    gTriDistance = vec3(0, 1, 0);\n\
    gl_Position = gl_in[1].gl_Position;\n\
    EmitVertex();\n\
\n\
    gPatchDistance = tePatchDistance[2];\n\
    gTriDistance = vec3(0, 0, 1);\n\
    gl_Position = gl_in[2].gl_Position;\n\
    EmitVertex();\n\
\n\
    EndPrimitive();\n\
}\n";
//

static const char* fragmentshader_source ="#version 410 core\n\
        in vec3 gFacetNormal;\n\
        in vec3 gTriDistance;\n\
        in vec3 gPatchDistance;\n\
        in float gPrimitive;\n\
        out vec4 color;\n\
void main()\n\
{\n\
            color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}\n";

static const char* fragmentshadernormal_source ="#version 410 core\n\
        in vec3 gFacetNormal;\n\
        in vec3 gTriDistance;\n\
        in vec3 gPatchDistance;\n\
        in float gPrimitive;\n\
        out vec4 color;\n\
void main()\n\
{\n\
            vec3 n = normalize(gFacetNormal);\n\
            color = vec4(n*0.5+0.5, 1.0f);\n\
}\n";

static const char * fragmentdiffuseColor_source = "#version 410 core\n\
        in vec3 gFacetNormal;\n\
        in vec3 gTriDistance;\n\
        in vec3 gPatchDistance;\n\
        in float gPrimitive;\n\
        out vec4 color;\n\
void main()\n\
{\n\
            vec3 n = normalize(gFacetNormal);\n\
            color = vec4(vec3(clamp(dot(n, vec3(0,0,1)), 0, 1)), 1.0);\n\
}\n";

//Plus c'est noir plus c'est faux
static const char * fragmentErrorDistance = "#version 410 core\n\
        in vec3 gFacetNormal;\n\
        in vec3 gTriDistance;\n\
        in vec3 gPatchDistance;\n\
        in float gPrimitive;\n\
        out vec4 FragColor;\n\
void main()\n\
{\n\
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
}\n";
//

void ShaderICOSphere::ICOinitialisation(){
    _indices = {
                2, 1, 0,
                3, 2, 0,
                4, 3, 0,
                5, 4, 0,
                1, 5, 0,

                11, 6,  7,
                11, 7,  8,
                11, 8,  9,
                11, 9,  10,
                11, 10, 6,

                1, 2, 6,
                2, 3, 7,
                3, 4, 8,
                4, 5, 9,
                5, 1, 10,

                2,  7, 6,
                3,  8, 7,
                4,  9, 8,
                5, 10, 9,
                1, 6, 10
               };

    _vertices = {
                 0.000f,  0.000f,  1.000f,
                 0.894f,  0.000f,  0.447f,
                 0.276f,  0.851f,  0.447f,
                -0.724f,  0.526f,  0.447f,
                -0.724f, -0.526f,  0.447f,
                 0.276f, -0.851f,  0.447f,
                 0.724f,  0.526f, -0.447f,
                -0.276f,  0.851f, -0.447f,
                -0.894f,  0.000f, -0.447f,
                -0.276f, -0.851f, -0.447f,
                 0.724f, -0.526f, -0.447f,
                 0.000f,  0.000f, -1.000f
    };

    // Create the VAO:
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Create the VBO for positions:;
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(GLfloat), _vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    // Create the VBO for indices:
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(GLfloat), _indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void ShaderICOSphere::initShader(GLuint& shader, const char * shaderSource, GLenum  type, const std::string& error){
    // Initialize shaders
    GLint success;
    GLchar infoLog[512]; // warning fixed size ... request for LOG_LENGTH!!!
    /* I. Creation et compilation du shader */
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::"<<error<<":: COMPILATIONFAILED\n"<<infoLog<<std::endl;
    }
}
void ShaderICOSphere::initFragmentShader(GLuint& prog, const char * shaderSource, const std::string& error){

    int success = 0;
    GLchar infoLog[512];
    GLuint fragmentshader;
    initShader( fragmentshader, shaderSource, GL_FRAGMENT_SHADER, error);
    /* II. Instanciation du programme */
    prog = glCreateProgram();
    glAttachShader(prog,_vertexshader);
    glAttachShader(prog,_tessControl);
    glAttachShader(prog,_tessEval);
    glAttachShader(prog,_geomShader);
    glAttachShader(prog, fragmentshader);
    glBindAttribLocation(prog,0,"Position");
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(prog, 512,NULL,infoLog);
        std::cerr << "ERROR::SHADER::"<<error<<"::LINK_FAILED\n"<<infoLog<<std::endl;
    }
    glDeleteShader(fragmentshader);
}


ShaderICOSphere::ShaderICOSphere(const int width, const int height) : Scene(width, height), _activecamera(0), _camera(nullptr) {
    glCullFace(GL_FRONT_AND_BACK);
    ICOinitialisation();
    initShader(_vertexshader,vertexshader_source,GL_VERTEX_SHADER,"VERTEX");
    initShader(_tessControl,tesselationControlShader,GL_TESS_CONTROL_SHADER,"TESSELATION_CONTROL");
    initShader(_tessEval, tesselationEvaluationShader, GL_TESS_EVALUATION_SHADER, "TESSELATION_EVALUATION");
    initShader(_geomShader, geometryShader, GL_GEOMETRY_SHADER, "GEOMETRY");
    initFragmentShader(_program,fragmentshader_source,"ORANGE");
    _programcolor = _program;
    initFragmentShader(_programnormal,fragmentshadernormal_source,"NORMAL");
    initFragmentShader(_programdiffuse,fragmentdiffuseColor_source,"DIFFUSE");
    initFragmentShader(_programerror,fragmentErrorDistance,"ERRORDIST");
    glDeleteShader(_vertexshader);
    glDeleteShader(_tessControl);
    glDeleteShader(_tessEval);
    glDeleteShader(_geomShader);
    _cameraselector.push_back( []()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 2.5));} );
    _cameraselector.push_back( []()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 2.5),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void ShaderICOSphere::resize(int width, int height){
    Scene::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
}

void ShaderICOSphere::draw() {
    Scene::draw();
    glUseProgram(_program);
    glUniform1i(glGetUniformLocation(_program, "subdivision"),subdivisionLevel);
    _view = _camera->viewmatrix();
    _normalMat = glm::mat3(_model * _view);
    glUniformMatrix4fv( glGetUniformLocation(_program, "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(_normalMat));
    glUniformMatrix4fv( glGetUniformLocation(_program, "model"), 1, GL_FALSE, glm::value_ptr(_model));
    glUniformMatrix4fv( glGetUniformLocation(_program, "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(_program, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

    glBindVertexArray(_vao);
    glDrawElements(GL_POINTS, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void ShaderICOSphere::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void ShaderICOSphere::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void ShaderICOSphere::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool ShaderICOSphere::keyboard(unsigned char k) {

    switch(k) {
    case 'p':
        _activecamera = (_activecamera+1)%2;
        _camera.reset(_cameraselector[_activecamera]());
        _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
        return true;
    case 'c' :
        _program = _programcolor;
        return true;
    case 'n' :
        _program = _programnormal;
        return true;
    case 'd' :
        _program = _programdiffuse;
        return true;
    case 'e' :
        _program = _programerror;
        return true;
    case 'm' :
        ++subdivisionLevel;
        return true;
    case 'l' :
        --subdivisionLevel;
        return true;
    default:
        return false;
    }
}
