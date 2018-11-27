#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "./src/OpenGL/opengl_stuff.h"
#include <vector>
#include <string>
class ShaderManager
{
public:
    ShaderManager();
    enum POSTPROCESS {SSAO,SSAOBLUR,HDR,BLOOM,BLOOMBLUR,FXAA,OIT,DRAW};
    enum PREPROCESS {GBUFFER,RENDER};
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
    void useProg() const { glUseProgram(program_m[active_program]);}
    void useProg( PREPROCESS p ) { setActiveProg(p);useProg();}
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
    GLuint get(POSTPROCESS pp) { return postProgram_m[pp];}
    GLuint setActivePostProg(const GLuint& prog);
    GLuint setActivePostProg(const int& i);
    void usePostProg() const { glUseProgram(postProgram_m[active_postprogram]);}
    void usePostProg( POSTPROCESS pp) { glUseProgram(postProgram_m[pp]); active_postprogram = pp;}
    unsigned int postProgCount();

private:
    std::vector<GLuint> program_m;
    std::vector<GLuint> postProgram_m;
    unsigned int active_program;
    unsigned int active_postprogram;


};

#endif // SHADERMANAGER_H
