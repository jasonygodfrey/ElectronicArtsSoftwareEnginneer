// GameSystem.h
// Header file defining core classes for the EA kickball game simulation
// Includes Game logic, Player customization, Marketplace system, and Ball behavior

#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <string>
#include <vector>

// Forward declarations to allow referencing before full definitions
class MarketplaceItem;
class KickAnimation;
class Player;
class Ball;
class Marketplace;

// --------------------------- MarketplaceItem ---------------------------
// Base class for all items that can be bought in the Marketplace
class MarketplaceItem {
protected:
    double price;  // Price of the item

public:
    virtual ~MarketplaceItem() = default;

    // Get the price of the item
    virtual double getPrice() const = 0;
};

// --------------------------- KickAnimation ---------------------------
// A type of item that modifies how a player performs a kick
class KickAnimation : public MarketplaceItem {
private:
    std::string animationType;  // Style/type of the kick animation

public:
    // Apply this kick animation to the specified player
    void applyToPlayer(Player* player);

    // Return the price of the kick animation
    double getPrice() const override;
};

// --------------------------- Ball ---------------------------
// Abstract base class representing a game ball
class Ball {
protected:
    std::string color;  // Color of the ball

public:
    virtual ~Ball() = default;

    // Perform a kick action on the ball
    virtual void kick() = 0;
};

// --------------------------- PurpleKickBall ---------------------------
// A specialized version of Ball with a predefined color (e.g., purple)
class PurpleKickBall : public Ball {
public:
    // Perform a custom kick action for the purple ball
    void kick() override;
};

// --------------------------- Player ---------------------------
// Represents a player in the game who can perform actions and equip kick animations
class Player {
private:
    std::string name;  // Player's name
    KickAnimation* kickAnimation;  // Currently equipped kick animation

public:
    // Perform a kick using the current animation
    void performKick();

    // Upgrade the player's kick animation
    void upgradeKickAnimation(KickAnimation* newAnimation);
};

// --------------------------- Marketplace ---------------------------
// Allows players to buy items (like kick animations)
class Marketplace {
private:
    std::vector<MarketplaceItem*> items;  // All items available for purchase

public:
    // Allow a player to purchase an item from the marketplace
    void purchaseItem(Player* player, MarketplaceItem* item);
};

// --------------------------- Game ---------------------------
// Manages the core gameplay loop, players, ball, and marketplace
class Game {
private:
    std::vector<Player*> players;  // All players in the game
    Marketplace* marketplace;      // Marketplace used in the game
    Ball* ball;                    // The ball used in gameplay

public:
    // Start the game logic
    void startGame();

    // End the game logic
    void endGame();
};

#endif // GAMESYSTEM_H


#pragma once

#include <vector>

/////////////////////////
// Locomotion Strategy //
/////////////////////////

// This is the first of the strategy patterns - if you are unfamiliar with
// the strategy design pattern, consult this reference:
// https://refactoring.guru/design-patterns/strategy

class Locomotion {
public:
    virtual void move() = 0;
};

class Swim : Locomotion {
public:
    void move() override;
};

class Crawl : Locomotion {
public:
    void move() override;
};

class Stationary : Locomotion {
public:
    void move() override;
};

/////////////////////
// Action Strategy //
/////////////////////

// Another implementation of a strategy pattern - here we delegate the various ways
// a sea creature can behave to their own classes. That way multiple creatures can
// depend on the same behavior - several fish can blow bubbles, for example.

class Action {
public:
    virtual void act() = 0;
};

class BlowBubble : Action {
public:
    void act() override;
};

class PuffUp : Action {
public:
    void act() override;
};

class ChangeColor : Action {
public:
    void act() override;
};

///////////////////////
// Resource Strategy //
///////////////////////

// the final implementation of the strategy pattern

class Resource {
public:
    virtual void collect() = 0;
};

class Pearl : Resource {
public:
    void collect() override;
};

class Shell : Resource {
public:
    void collect() override;
};

class FishFillet : Resource {
public:
    void collect() override;
};

//////////////////////////////
// Sea Creature Composition //
//////////////////////////////

// Here we tie everything we've built together in a single class.
// Note that in order to reference an interface such as locomotion in C++
// we need to use a pointer. We are not savages, so we use a smart pointer.

class SeaCreature {
private:
    std::unique_ptr<Locomotion> locomotion;
    std::vector<Action> actions;
    std::vector<Resource> contained_resources;
public:
    void move();

    void act();

    void collect_resources();
};