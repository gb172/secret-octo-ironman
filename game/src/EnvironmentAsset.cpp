/*
 * EnvironmentAsset.cpp
 *
 *  Created on: 7 Jan 2013
 *      Author: gb172
 */
#include "EnvironmentAsset.h"

EnvironmentAsset::EnvironmentAsset()
  : GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/hello-gl.f.glsl")
	      )
{
  EnvironmentAsset(0, 0, 0);
}

EnvironmentAsset::EnvironmentAsset(float x, float y, float z) {
  this->li = nullptr;
  this->pos = shared_ptr<Point3>(new Point3(x, y, z));
  // A default "unit" triangular pyramid
  num_vertices = 10;
  num_triangles = 12;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3] { // three points per vertex

// (x,y,z)

  -10.0, 0.0, -10.0,		//0  PLANE
  -10.0, 0.0,  10.0,		//1
   10.0, 0.0,  10.0,		//2
   10.0, 0.0, -10.0,		//3

  -10.0, 5.0, -10.0,		//4  WALL 1
  -10.0, 5.0, 10.0,			//5

  -10.0, 5.0,  10.0,		//6  WALL 2
   10.0, 5.0,  10.0,		//7

   10.0, 5.0, 10.0,			//8  WALL 3
   10.0, 5.0, -10.0			//9

};


  g_element_buffer_data = new GLushort[num_triangles * 3] { // three vertices per triangle

  0, 1, 3,		//PLANE
  1, 2, 3,

  0, 4, 5,		//WALL 1
  0, 1, 5,

  1, 2, 7,		//WALL 2
  1, 6, 7,

  2, 3, 9,		//WALL 3
  2, 8, 9




  };




  mv_matrix = mv_matrix.translation( Vector3(x, y, z));
  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

EnvironmentAsset::~EnvironmentAsset() {
  // TODO: do something nice here.
}

void EnvironmentAsset::update() {
}

void EnvironmentAsset::setInterpolator(shared_ptr<IInterpolator> li) {
  this->li.swap(li);
}

void EnvironmentAsset::draw() {
  GameAsset::draw();
}




