/*
 * EnvironmentAsset.h
 *
 *  Created on: 7 Jan 2013
 *      Author: gb172
 */
#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef ENVIRONMENTASSET_H_
#define ENVIRONMENTASSET_H_

class EnvironmentAsset : public GameAsset {
 public:
  EnvironmentAsset();
  EnvironmentAsset(float x, float y, float z);
  ~EnvironmentAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
  shared_ptr<Point3>        pos;
};

#endif // ENVIRONMENTASSET_H_



