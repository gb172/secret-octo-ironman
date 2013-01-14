/*
 * EnemyAsset.cpp
 *
 *  Created on: 14 Jan 2013
 *      Author: gb172
 */
#include "EnemyAsset.h"

EnemyAsset::EnemyAsset()

{
	EnemyAsset(0, 0, 0);
}

EnemyAsset::EnemyAsset(float x, float y, float z)   :

			GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/enemy.f.glsl")
	      ){
  this->li = nullptr;
  this->pos = shared_ptr<Point3>(new Point3(x, y, z));
  // A default "unit" triangular pyramid
  num_vertices = 8;
  num_triangles = 12;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3] { // three points per vertex

  0.0, 0.0, 0.0,
  1.0, 0.0, 0.0,
  0.0, 1.0, 0.0,
  1.0, 1.0, 0.0,

  0.0, 0.0, 1.0,
  1.0, 0.0, 1.0,
  0.0, 1.0, 1.0,
  1.0, 1.0, 1.0  };


  g_element_buffer_data = new GLushort[num_triangles * 3] { // three vertices per triangle

  0, 1, 2,
  2, 1, 3,

  5, 4, 6,
  7, 5, 6,

  3, 1, 5,
  3, 5, 7,

  4, 0, 2,
  6, 4, 2,

  2, 3, 6,
  6, 3, 7,

  1, 0, 4,
  5, 1, 4
  };




  mv_matrix = mv_matrix.translation( Vector3(x, y, z));
  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

EnemyAsset::~EnemyAsset() {
  // TODO: do something nice here.
}

void EnemyAsset::update() {
}

void EnemyAsset::setInterpolator(shared_ptr<IInterpolator> li) {
  this->li.swap(li);
}

void EnemyAsset::draw() {
  GameAsset::draw();
}




