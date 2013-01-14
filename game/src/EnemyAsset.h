/*
 * EnemyAsset.h
 *
 *  Created on: 14 Jan 2013
 *      Author: gb172
 */
#include "GameAsset.h"
#include "IInterpolator.h"

#ifndef ENEMYASSET_H_
#define ENEMYASSET_H_

class EnemyAsset : public GameAsset {
 public:
  EnemyAsset();
  EnemyAsset(float x, float y, float z);
  ~EnemyAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
  shared_ptr<Point3>        pos;
};

#endif // ENEMYASSET_H_





