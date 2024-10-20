#ifndef OBJECTS_H
#define OBJECTS_H

class RenderObject {
public:
    virtual void update(){} ;   // Pure virtual update method
    virtual void render(){} ;   // Pure virtual render method

};


#endif // OBJECTS_H
