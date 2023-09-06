#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
  Vector2f totalPosition = Vector2f::zero();
  Vector2f centerOfMass = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;
 
  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  
  // todo: find and apply force only on the closest mates


  if (!neighborhood.empty()) {
    // Get position of current boid for later and start counting the close flockmates
    Vector2f position = boid->transform.position;
    int countCloseFlockmates = 0;
    // Iterate through the neighborhood
    for (int i = 0; i < neighborhood.size(); i++) {
      // Store current neighbor position in a temp vector
      Vector2 temp = neighborhood[i]->getPosition();
      // Get the distance from the neighbor and check the magnitude
      // If it is closer than our desired distance count it as a close flockmate and add temp to the total position
      if (Vector2f::Distance(position, temp) <= desiredMinimalDistance) {
        countCloseFlockmates++;
        totalPosition += temp;
      }
    }
    // If we have close flockmates calculate the Center of Mass and the seperating force
    if (countCloseFlockmates != 0) {
      centerOfMass = (totalPosition / countCloseFlockmates);
      separatingForce = centerOfMass - position;
      separatingForce = Vector2f::normalized(separatingForce);
      separatingForce *= -1.0f;
    }
  }  // If the neighborhood is empty make sure that the separating force is zero
  else if (neighborhood.empty()) {
    separatingForce = Vector2f::zero();
  }

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
