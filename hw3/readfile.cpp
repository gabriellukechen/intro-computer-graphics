/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  


// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 

/*****************************************************************************/

// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h"

using namespace std;
#include "variables.h"
#include "readfile.h"

// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, float* values)
{
  mat4 transform = transfstack.top(); 
  vec4 valvec = vec4(values[0],values[1],values[2],values[3]); 
  vec4 newval = transform * valvec; 
  for (int i = 0; i < 4; i++) values[i] = newval[i]; 
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
  mat4 &T = transfstack.top(); 
  T = T * M; 
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values)
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i];
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n";
      return false;
    }
  }
  return true; 
}

bool readvals(stringstream &s, int numvals, float* values, string caller)
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i];
//    cout << "caller: " << caller << " value: " << values[i] << "\n";
    if (s.fail()) {
      cout << "Failed reading value " << i << " " << caller << " will skip\n";
      return false;
    }
  }
  return true;
}
void readlightvals(stringstream &s, int * numused, float * values, light type, string caller) {
  bool validinput = readvals(s, 6, values, caller);
  if (validinput) {
    // NOTE: the number of values per light is hardcoded in variables.h. in raytracer, we have is 3 point
    //  values for position and color RGB and not RBGA
    lighttype[*numused] = type; // set the type to either point or directional

    for (int i = 0; i < 3; i++) {
      lightposn[i + 3 * *numused] = values[i];
      lightcolor[i + 3 * *numused] = values[i + 3] * 255;
    }
  }
  (*numused)++;
}

void readfile(const char* filename) 
{
  string str, cmd; 
  ifstream in;
  in.open(filename); 
  if (in.is_open()) {

    // I need to implement a matrix stack to store transforms.  
    // This is done using standard STL Templates 
    stack <mat4> transfstack; 
    transfstack.push(mat4(1.0));  // identity

    getline (in, str); 
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str);
        s >> cmd; 
        int i; 
        float values[10]; // Position and color for light, colors for others
        // Up to 10 params for cameras.  
        bool validinput; // Validity of input 

        // Material Commands
        // Ambient, diffuse, specular, shininess properties for each object.
        // Filling this in is pretty straightforward, so I've left it in 
        // the skeleton, also as a hint of how to do the more complex ones.
        // Note that no transforms/stacks are applied to the colors. 

        if (cmd == "diffuse") {
          validinput = readvals(s, 3, values, cmd);
          if (validinput) {
            for (i = 0; i < 3; i++) {
              diffuse[i] = values[i]; 
            }
          }
        } else if (cmd == "specular") {
          validinput = readvals(s, 3, values, cmd);
          if (validinput) {
            for (i = 0; i < 3; i++) {
              specular[i] = values[i]; 
            }
          }
        } else if (cmd == "emission") {
          validinput = readvals(s, 3, values, cmd);
          if (validinput) {
            for (i = 0; i < 3; i++) {
              emission[i] = values[i] * 255;
            }
          }
        } else if (cmd == "shininess") {
          validinput = readvals(s, 1, values, cmd);
          if (validinput) {
            shininess = values[0]; 
          }
        }

        /*
         * General Commands
         */
        else if (cmd == "size") {
          validinput = readvals(s,2,values, cmd);
          if (validinput) { 
            w = (int) values[0]; h = (int) values[1]; totalpixels = (int) w * h;
          }
        } else if (cmd == "maxdepth") {
          validinput = readvals(s, 1, values, cmd);
          if (validinput) {
            maxdepth = values[0];
          }
        } else if (cmd == "output") {
          s >> fname;
          if (s.fail()) {
            cout << "Failed reading value filename";
          }
        }

        /*
         * Camera Command(s)
         */
        else if (cmd == "camera") {
          validinput = readvals(s,10, values, cmd); // 10 values eye cen up fov
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE
            // Use all of values[0...9]
            // You may need to use the upvector fn in Transform.cpp
            // to set up correctly. 
            // Set eyeinit upinit spherecenter fovy in variables.h

            // Notes:
            //  - command fromm spec... camera lookfromx lookfromy lookcfromz lookatx lookaty lookatz upx upy upz fovy
            eyeinit = vec3(values[0], values[1], values[2]); // eye initial position

            center = vec3(values[3], values[4], values[5]); // position of spherecenter/eye initial lookat position

            vec3 eyeDirection = center - eyeinit; // vector from eye position to spherecenter

            upinit = Transform::upvector(
              normalize(vec3(values[6], values[7], values[8])),
              eyeDirection
            ); // properly orthogonal normalized up vector

            fovy = values[9];
          }
        }

        /*
         * Lights Commands
         */
        else if (cmd == "directional") {
          readlightvals(s, &lightsused, values, directional, cmd);
        } else if (cmd == "point") {
          readlightvals(s, &lightsused, values, point, cmd);
        } else if (cmd == "attenuation") {
          validinput = readvals(s, 3, values, cmd);
          if (validinput) {
            for (i = 0; i < 3; i++) {
              attenuation[i] = values[i];
            }
          }
        } else if (cmd == "ambient") {
          validinput = readvals(s, 3, values, cmd); // colors
          if (validinput) {
            for (i = 0; i < 3; i++) {
              ambient[i] = values[i] * 255;
            }
          }
        }

        /*
         * Geometry Commands
         */
        // I've left the code for loading objects in the skeleton, so
        // you can get a sense of how this works.  
        // Also look at demo.txt to get a sense of why things are done this way.
        else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot" || cmd == "tri") {
          if (numobjects == maxobjects) { // No more objects 
            cerr << "Reached Maximum Number of Objects " << numobjects << " Will ignore further objects\n";
          } else {
            object * obj = &(objects[numobjects]);

            // Set the object's light properties
            for (i = 0; i < 3; i++) {
              (obj->ambient)[i] = ambient[i];
              (obj->diffuse)[i] = diffuse[i];
              (obj->specular)[i] = specular[i];
              (obj->emission)[i] = emission[i];
            }
            obj->shininess = shininess;

            // Set the object's transform
            obj->transform = transfstack.top();

            // Set the object's type
            if (cmd == "sphere") {
              validinput = readvals(s, 4, values, cmd);
              if (validinput) {
                obj->type = sphere;
                (obj->spherecenter)[0] = values[0];
                (obj->spherecenter)[1] = values[1];
                (obj->spherecenter)[2] = values[2];
                obj->size = values[3];
              }
            } else if (cmd == "tri") {
              validinput = readvals(s, 3, values, cmd);
              if (validinput) {
                obj->type = triangle;
                obj->trianglevertices[0] = values[0];
                obj->trianglevertices[1] = values[1];
                obj->trianglevertices[2] = values[2];
              }

            }
            ++numobjects; 
          }
        } else if (cmd == "maxverts") {
          validinput = readvals(s, 1, values, cmd);
          if (validinput) {
            maxverts = values[0];
          }
        } else if (cmd == "vertex") {
          validinput = readvals(s, 3, values, cmd);
          if (validinput) {
              vertices[verticesused] = vec3(values[0], values[1], values[2]);
          }
          verticesused++;
        }

        /*
         * Transformation Commands
         */

        else if (cmd == "translate") {
          validinput = readvals(s,3,values, cmd);
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE.  
            // Think about how the transformation stack is affected
            // You might want to use helper functions on top of file. 
            // Also keep in mind what order your matrix is!

            rightmultiply(Transform::translate(values[0], values[1], values[2]), transfstack);
          }
        }
        else if (cmd == "scale") {
          validinput = readvals(s,3,values, cmd);
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE.  
            // Think about how the transformation stack is affected
            // You might want to use helper functions on top of file.  
            // Also keep in mind what order your matrix is!

            rightmultiply(Transform::scale(values[0], values[1], values[2]), transfstack);
          }
        }
        else if (cmd == "rotate") {
          validinput = readvals(s,4,values, cmd);
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE. 
            // values[0..2] are the axis, values[3] is the angle.  
            // You may want to normalize the axis (or in Transform::rotate)
            // See how the stack is affected, as above.  
            // Note that rotate returns a mat3. 
            // Also keep in mind what order your matrix is!

            vec3 axis = normalize(vec3(values[0], values[1], values[2]));
            rightmultiply(mat4(Transform::rotate(values[3], axis)), transfstack);
          }
        }

        // I include the basic push/pop code for matrix stacks
        else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()); 
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n"; 
          } else {
            transfstack.pop(); 
          }
        }

        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n"; 
        }
      }
      getline (in, str); 
    }

    // Set up initial position for eye, up and amount
    // As well as booleans

    eye = eyeinit; 
    up = upinit; 
    amount = amountinit;
    sx = sy = 1.0;  // keyboard controlled scales in x and y 
    tx = ty = 0.0;  // keyboard controllled translation in x and y  

  } else {
    cerr << "Unable to Open Input Data File " << filename << "\n"; 
    throw 2; 
  }
}
