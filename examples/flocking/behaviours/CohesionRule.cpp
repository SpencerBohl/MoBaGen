#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f centerOfMass = Vector2f::zero();
  Vector2f totalPosition = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  if (!neighborhood.empty()) {
    for (int i = 0; i < neighborhood.size(); i++) {
      Vector2f temp = neighborhood[i]->getPosition();
      totalPosition += temp;
    }
    centerOfMass = (totalPosition / neighborhood.size());
    cohesionForce = centerOfMass - boid->getPosition();
    cohesionForce = Vector2f::normalized(cohesionForce);
  } else if (neighborhood.empty()) {
    cohesionForce = Vector2f::zero();
  }

  return cohesionForce;
}