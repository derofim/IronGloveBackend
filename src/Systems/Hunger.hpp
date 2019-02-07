#pragma once

#include "../System.hpp"

#include <memory>
#include <WebSockets/WebSocket.hpp>

class Hunger : public System {
    // Lifecycle Methods
public:
    ~Hunger() noexcept;
    Hunger(const Hunger&) = delete;
    Hunger(Hunger&&) noexcept = delete;
    Hunger& operator=(const Hunger&) = delete;
    Hunger& operator=(Hunger&&) noexcept = delete;

    // Public Methods
public:
    /**
     * This is the constructor of the class.
     */
    Hunger();

    // System
public:
    virtual void Update(
        Components& components,
        size_t tick
    ) override;

    // Private properties
private:
    /**
     * This is the type of structure that contains the private
     * properties of the instance.  It is defined in the implementation
     * and declared here to ensure that it is scoped inside the class.
     */
    struct Impl;

    /**
     * This contains the private properties of the instance.
     */
    std::unique_ptr< Impl > impl_;
};
