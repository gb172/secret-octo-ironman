/*
 * FloorAsset.cpp
 *
 *  Created on: 7 Jan 2013
 *      Author: gb172
 */
#include "FloorAsset.h"

FloorAsset::FloorAsset()

{
  FloorAsset(0, 0, 0);
}

FloorAsset::FloorAsset(float x, float y, float z)

: GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/floor.f.glsl")
	      )
{
  this->li = nullptr;
  this->pos = shared_ptr<Point3>(new Point3(x, y, z));
  // A default "unit" triangular pyramid
  num_vertices = 4;
  num_triangles = 2;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3] { // three points per vertex

// (x,y,z)

  -10.0, 0.0, -10.0,		//0  PLANE
  -10.0, 0.0,  10.0,		//1
   10.0, 0.0,  10.0,		//2
   10.0, 0.0, -10.0,		//3

  };


  g_element_buffer_data = new GLushort[num_triangles * 3] { // three vertices per triangle

  0, 1, 3,		//PLANE
  1, 2, 3,

  };




  mv_matrix = mv_matrix.translation( Vector3(x, y, z));
  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

FloorAsset::~FloorAsset() {
  // TODO: do something nice here.
}

void FloorAsset::update() {
}

void FloorAsset::setInterpolator(shared_ptr<IInterpolator> li) {
  this->li.swap(li);
}

void FloorAsset::draw() {
  GameAsset::draw();
}



