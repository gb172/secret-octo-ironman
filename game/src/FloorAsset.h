/*
 * FloorAsset.h
 *
 *  Created on: 7 Jan 2013
 *      Author: gb172
 */
#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef FLOORASSET_H_
#define FLOORASSET_H_

class FloorAsset : public GameAsset {
 public:
  FloorAsset();
  FloorAsset(float x, float y, float z);
  ~FloorAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
  shared_ptr<Point3>        pos;
};

#endif // FLOORASSET_H_






