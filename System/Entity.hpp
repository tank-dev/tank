#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include <vector>
#include <string>
#include <memory>
#include "../Graphics/Graphic.hpp"
#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"

namespace tank
{

class State;

/*!
 * \brief Base class for all in-game entities.
 *
 * Entities should be added to gamestates via State::addEntity(Entity)
 *
 * All derived classes contain a Vectorf position and a reference to a
 * texture (loaded via IRender), as well as a string type.
 * visible determines whether the entity will be drawn
 * Every Entity has a unique actorID
 * Every Entity added to a State will automatically have its state
 * set accordingly.
 *
 * Derived classes must override update, to define the entity's per-frame
 * behaviour
 *
 * Draw may be overridden, but should work as-is for all non-animated
 * entities.
 * \see Animation
 * \see IRender
 */
class Entity
{
public:
    /*!
     * \brief Run entity's per-frame game logic
     */
    virtual void update() {}

    /*!
     * \brief Render the entity
     *
     * Render the entity for the current frame
     * \param render The Render instance with which to render the entity
     */
    virtual void draw();

    /*!
     * \brief Check for collisions with the entity (deprecated?)
     *
     * Render the entity for the current frame
     * \param type The type of entity with which to detect collisions (defaults
     * to all)
     * \return A list of all colliding entitities of type.
     * \see setType()
     */
    std::vector<Entity*> collide(std::string type = "");

    /*!
     * \brief Returns the entity's vector position
     *
     * \return Entity's position
     */
    Vectorf const& getPos() const
    {
        return pos_;
    }

    /*!
     * \brief Returns the entity's rotation
     *
     * \return Entity's rotation in degrees
     */
    float getRotation() const
    {
        return rot_;
    }

    /*!
     * \brief Returns the entity's hitbox
     *
     * Returns the entity's hitbox in the format
     * (x-offset, y-offset, width, height), the offset being a translation to
     * the bottom right from the entity's position vector.
     *
     * \return Entity's hitbox
     */
    Rect const& getHitbox() const
    {
        return hitbox_;
    }

    /*!
     * \brief Returns the entity's type
     *
     * \return The entity's type
     */
    std::string getType() const
    {
        return type_;
    }

    /*!
     * \brief Returns whether the entity is solid (deprecated)
     *
     * \return Whether or not the entity is solid
     */
    bool isSolid() const
    {
        return solid_;
    }

    /*!
     * \brief Returns whether the entity is visible (deprecated)
     *
     * \return Whether or not the entity is visible
     */
    bool isVisible() const
    {
        return visible_;
    }

    /*!
     * \brief Returns the entity's z-layer
     *
     * \return Entity's z-layer
     */
    int getLayer() const
    {
        return layer_;
    }

    /*!
     * \brief Returns a pointer to the entity's Texture
     *
     * \return Entity's texture
     */
    Graphic& getGraphic() const
    {
        // TODO: Check pointer
        return *graphic_;
    }

    /*!
     * \brief Returns a pointer to the entity's parent State
     *
     * \return Entity's parent state
     */
    State* getState() const
    {
        return state_;
    }

    /*!
     * \brief Returns the entity's unique id (deprecated)
     *
     * \return Entity ID
     */
    int getActorID() const
    {
        return actorID_;
    }

    /*!
     * \brief Returns the number of entities (deprecated)
     *
     * \return The number of entities that have been constructed
     */
    static int getNumEnts()
    {
        return numEnts_;
    }

    /*!
     * \brief Sets the entity's position
     *
     * \param pos The position to which to move
     */
    virtual void setPos(Vectorf pos);

    /*!
     * \brief Sets the entity's rotation
     *
     * \param pos The entity's new rotation in degrees
     */
    virtual void setRotation(float rot);

    /*!
     * \brief Sets the entity's hitbox
     *
     * \param hitbox The new hitbox
     */
    virtual void setHitbox(Rect hitbox);

    /*!
     * \brief Sets the entity's type
     *
     * \param type The new type
     */
    void setType(std::string type) { type_ = type; }

    /*!
     * \brief Sets the entity's solidity (deprecated)
     *
     * \param solid Whether the entity should be solid or not
     */
    void setSolid(bool solid);

    /*!
     * \brief Sets the entity's z-layer (deprecated)
     *
     * \param visible Whether the entity should be visible or not
     */
    void setVisible(bool visible);

    /*!
     * \brief Sets the entity's z-layer
     *
     * \param layer The new layer
     */
    void setLayer(int layer);

    /*!
     * \brief Sets the entity's graphic
     *
     * \tparam T Type of Graphic to create
     * \tparam Args Arguments to send to T's constructor
     * \param args The arguments to T's constructor
     * \return A pointer of type T to the created Graphic
     */
    template <typename T, typename... Args>
    T* setGraphic(Args&&... args);

    /*!
     * \brief Sets the entity's parent state
     *
     * Typically set by the state on addition. Don't change it unless you know
     * what you're doing.
     *
     * \param state A pointer to the parent state
     */
    void setState(State* const state);

    /*!
     * \brief Constructs an entity at position pos
     *
     * \param pos The position of the entity
     */
    Entity(Vectorf const& pos);

    /*!
     * \brief Remove the entity from the world.
     */
    void remove() { removed_ = true; }

    /*!
     * \return if the entity has been removed.
     */
    bool isRemoved() {return removed_;}

    /*!
     * \brief Called when the entitiy is added to the world.
     */
    virtual void onAdded() {}

    /*!
     * \brief Called when the entity is removed from the world.
     */
    virtual void onRemoved() {}

    virtual ~Entity();
private:
    //Member variables
    Vectorf pos_;
    float rot_;
    Rect hitbox_;     //(0,0,0,0)
    std::string type_;//""
    bool solid_;      //false
    bool visible_;    //true
    int layer_;       //0

    State* state_;          //Set by parent State
    std::unique_ptr<Graphic> graphic_;

    static int numEnts_;
    const  int actorID_;

    bool removed_ = false;
};

template <typename T, typename... Args>
T* Entity::setGraphic(Args&&... args)
{
    static_assert(std::is_base_of<Graphic,T>::value,
                  "Type must derive from Graphic");

    T* g = new T(std::forward<Args>(args)...);
    graphic_.reset(g);
    return g;
}

}
#endif
