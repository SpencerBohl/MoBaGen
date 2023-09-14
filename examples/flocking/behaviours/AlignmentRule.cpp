#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  Vector2f totalVelocity = Vector2f::zero();

  // Iterate over the neighborhood to get average velocity
  if (!neighborhood.empty()) {
    for (int i = 0; i < neighborhood.size(); i++) {
      Vector2f temp = neighborhood[i]->getVelocity();
      totalVelocity += temp;
    }
    averageVelocity = (totalVelocity / neighborhood.size());
  }

  return Vector2f::normalized(averageVelocity);
}