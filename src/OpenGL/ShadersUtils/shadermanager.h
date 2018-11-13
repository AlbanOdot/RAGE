#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "./src/OpenGL/opengl_stuff.h"
#include <vector>
class ShaderManager
{
public:
    ShaderManager();
    enum SHADER {SSAO,HDR,FXAA,OIT};

    /*
     *
     * BASIC OBJECT DRAW FUNCTION
     *
     */
    //Program add and remove
    void addProgram(const GLuint& newProg);
    //Compute and add the corresponding program
    GLuint computeAddProgramm( const std::string& vs, const std::string& fs);
    //Remove the program of ID prog
    void removeProgram( const GLuint& prog);
    //Remove the i'th programme
    void removeProgram( const int& i);


    //GETTER and SETTER
    GLuint getActiveProg(void) const;
    GLuint setActiveProg(const GLuint& prog);
    GLuint setActiveProg(const int& i);
    GLuint useProg() const { glUseProgram(program_m[active_program]);}
    unsigned int progCount();

    /*
     *
     * POST-PROCESS DRAW FUNCTION
     *
     */
    //Program add and remove
    void addPostProgram(const GLuint& newProg);
    //Compute and add the corresponding postprocess programme
    GLuint computeAddPostProgramm( const std::string& vs, const std::string& fs);
    //Remove the program of ID prog
    void removePostProgram( const GLuint& prog);
    //Remove the i'th programme
    void removePostProgram( const int& i);


    //GETTER and SETTER
    GLuint getActivePostProg(void) const;
    GLuint setActivePostProg(const GLuint& prog);
    GLuint setActivePostProg(const int& i);
    GLuint usePostProg() const { glUseProgram(postProgram_m[active_postprogram]);}
    unsigned int postProgCount();

private:
    std::vector<GLuint> program_m;
    std::vector<GLuint> postProgram_m;
    unsigned int active_program;
    unsigned int active_postprogram;


};

#endif // SHADERMANAGER_H
