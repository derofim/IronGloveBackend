#include "PlayerMovement.hpp"

#include <Json/Value.hpp>
#include <memory>
#include <WebSockets/WebSocket.hpp>

struct PlayerMovement::Impl {
    std::shared_ptr< WebSockets::WebSocket > ws;
};

PlayerMovement::~PlayerMovement() = default;

PlayerMovement::PlayerMovement()
    : impl_(new Impl())
{
}

void PlayerMovement::Update(
    Components& components,
    size_t tick
) {
    const auto inputsInfo = components.GetComponentsOfType(Components::Type::Input);
    auto inputs = (Input*)inputsInfo.first;
    for (size_t i = 0; i < inputsInfo.n; ++i) {
        auto& input = inputs[i];
        if (input.moveCooldown) {
            --input.moveCooldown;
            continue;
        }
        const auto position = (Position*)components.GetEntityComponentOfType(Components::Type::Position, input.entityId);
        if (position == nullptr) {
            continue;
        }
        switch (input.move) {
            case 'j': {
                if (!components.IsObstacleInTheWay(position->x - 1, position->y)) {
                    --position->x;
                }
            } break;

            case 'l': {
                if (!components.IsObstacleInTheWay(position->x + 1, position->y)) {
                    ++position->x;
                }
            } break;

            case 'i': {
                if (!components.IsObstacleInTheWay(position->x, position->y - 1)) {
                    --position->y;
                }
            } break;

            case 'k': {
                if (!components.IsObstacleInTheWay(position->x, position->y + 1)) {
                    ++position->y;
                }
            } break;

            default: {
            }
        }
        input.moveCooldown = 1;
        input.moveThisTick = false;
        if (input.moveReleased) {
            input.move = 0;
        }
    }
}
