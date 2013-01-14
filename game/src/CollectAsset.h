/*
 * CollectAsset.h
 *
 *  Created on: 14 Jan 2013
 *      Author: gb172
 */
#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef COLLECTASSET_H_
#define COLLECTASSET_H_

class CollectAsset : public GameAsset {
 public:
  CollectAsset();
  CollectAsset(float x, float y, float z);
  ~CollectAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
  shared_ptr<Point3>        pos;
};

#endif // COLLECTASSET_H_





