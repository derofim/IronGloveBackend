#include "AI.hpp"

#include <Json/Value.hpp>
#include <memory>
#include <WebSockets/WebSocket.hpp>

namespace {

}

struct AI::Impl {
    std::shared_ptr< WebSockets::WebSocket > ws;
};

AI::~AI() = default;

AI::AI()
    : impl_(new Impl())
{
}

void AI::Update(
    Components& components,
    size_t tick
) {
    if ((tick % 2) == 0) {
        return;
    }
    const auto inputsInfo = components.GetComponentsOfType(Components::Type::Input);
    if (inputsInfo.n != 1) {
        return;
    }
    const auto playerPosition = (Position*)components.GetEntityComponentOfType(Components::Type::Position, inputsInfo.first[0].entityId);
//    const auto positionsInfo = components.GetComponentsOfType(Components::Type::Position);
    const auto collidersInfo = components.GetComponentsOfType(Components::Type::Collider);
    const auto monstersInfo = components.GetComponentsOfType(Components::Type::Monster);
    auto monsters = (Monster*)monstersInfo.first;
    for (size_t i = 0; i < monstersInfo.n; ++i) {
        const auto& monster = monsters[i];
        const auto position = (Position*)components.GetEntityComponentOfType(Components::Type::Position, monster.entityId);
        if (position == nullptr) {
            continue;
        }
        const auto dx = abs(position->x - playerPosition->x);
        const auto dy = abs(position->y - playerPosition->y);
        int mx = 0;
        int my = 0;
        if (position->x < playerPosition->x) {
            ++mx;
        } else if (position->x > playerPosition->x) {
            --mx;
        }
        if (position->y < playerPosition->y) {
            ++my;
        } else if (position->y > playerPosition->y) {
            --my;
        }
        if (
            (dx > dy)
            && !components.IsObstacleInTheWay(
                position->x + mx,
                position->y
            )
        ) {
            position->x += mx;
        } else if (
            !components.IsObstacleInTheWay(
                position->x,
                position->y + my
            )
        ) {
            position->y += my;
        } else if (
            !components.IsObstacleInTheWay(
                position->x + mx,
                position->y
            )
        ) {
            position->x += mx;
        }
    }
}