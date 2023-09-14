#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f force = Vector2f::zero();  // zero

  // todo: add here your code code here do make the boid follow the bounded box rule
  // hint: use this->world->engine->window->size() and desiredDistance
  Point2D size = this->world->engine->window->size();
  float distance = desiredDistance;

  // Find the boundry lines of the box
  float minX = distance;
  float maxX = size.x - distance;
  float minY = distance;
  float maxY = size.y - distance;

  // Get the position of the boid
  Vector2f position = boid->getPosition();
  Vector2f tempForce = Vector2f::zero();

  if (position.x <= minX) {
    tempForce = Vector2f(Vector2f::Distance(position, Vector2f(minX, position.y)), 0);
    force += tempForce;
  } else if (position.x >= maxX) {
    tempForce = Vector2f(Vector2f::Distance(position, Vector2f(maxX, position.y)), 0);
    force += (tempForce * -1);
  }
  if (position.y <= minY) {
    tempForce = Vector2f(0, Vector2f::Distance(position, Vector2(position.x, minY)));
    force += tempForce;
  } else if (position.y >= maxY) {
    tempForce = Vector2f(0, Vector2f::Distance(position, Vector2(position.x, maxY)));
    force += (tempForce * -1);
  }
  force = Vector2f::normalized(force);
  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}