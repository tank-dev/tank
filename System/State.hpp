#ifndef TANK_GAMESTATE_HPP
#define TANK_GAMESTATE_HPP

#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace tank {

class Entity;
class Game;

/*!
 * \brief Base class for game states ("Worlds")
 *
 * Handles Entity creation, destruction, rendering and updating. You can derive
 * from this class to add your own state-specific logic - it can also be useful
 * to handle state initialization in the constructor as opposed to from the
 * outside (e.g. in main).
 *
 * States should be created via Game::makeState<T>(Args... args) for memory
 * safety. All states are stored within Game as a stack.
 *
 * All entities should be created using the similar method available from
 * State, makeEntity<T>(Args... args).
 *
 * \see Game
 * \see Entity
 * \see EventHandler
 */
class State
{
public:
	/*!
	 * \brief Creates an Entity and adds it to the State
	 *
     * Creates an Entity, setting its state pointer to point to it.
     * Adds a unique_ptr to the entity to the entity list.
     * Returns a raw pointer of type T* to the Entity created.
     *
	 * \tparam T The type of Entity to construct
     * \param args the arguments to send to the entity's constructor
	 * \return A raw pointer to the created Entity (NEVER DELETE IT)
	 */
    template <typename T, typename... Args>
    T* makeEntity(Args&&... args)
    {
        static_assert(std::is_base_of<Entity,T>::value,
                      "Type must derive from Entity");

        T* ent = new T(std::forward<Args>(args)...);
        ent->setState(this);
        entities_.emplace_back(ent);
        return ent;
    }

    /*!
     * \brief Inserts a unique_ptr to an Entity into the entity list
     *
     * This is a way to add entities that have 
     * * been removed from their original State or 
     * * been created independently of State::makeEntity()
     *
     * \param entity A unique_ptr to the Entity to be inserted
     * \see makeEntity()
     */
    void insertEntity(std::unique_ptr<Entity>&&);

    /*!
     * \brief Moves an Entity from one State to another
     *
     * This is essentially a shorthand for state->insertEntity(this->releaseEntity(entity))
     *
     * \param state The State to which to move the Entity
     * \param entity A raw pointer to the Entity to be moved
     * \see insertEntity()
     * \see releaseEntity()
     */
    void moveEntity(State*, Entity*);

    /*!
     * \brief Removes an Entity from the entity list and returns a unique_ptr
     * to it
     *
     * \param entity A raw pointer to the Entity to be released
     * \see insertEntity()
     */
    std::unique_ptr<Entity> releaseEntity(Entity*);

    /*!
     * \brief Removes an Entity from the entity list, deleting it
     *
     * \param entity A raw pointer to the Entity to be removed
     */
    void removeEntity(Entity*);

    /*!
     * \brief Handle keyboard input on a per-frame basis (deprecated)
     *
     * When State is the active state, Game calls this once per frame, before
     * update() and draw().
     *
     * Override this to send keyboard input to entities that need it
     *
     * \param key SDL_KeyboardEvent representing the change in keyboard state
     * \see update()
     * \see draw()
     * \see Game
     */
    virtual void handleEvents(sf::Keyboard::Key const&) {}

    /*!
     * \brief Update all entities in the state's entities list
     *
     * When State is the active state, Game calls this once per frame, between
     * handleEvents() and draw()
     *
     * Override this to specify new logic for updates, but be sure to update the
     * entity list, either by looping over and calling update, or by calling
     * State::update()
     *
     * \see handleEvents()
     * \see draw()
     * \see Game
     */
    virtual void update();

    /*!
     * \brief Draw all entities in the state's entities list
     *
     * When State is the active state, Game calls this once per frame, after
     * handleEvents() and update()
     *
     * Override this to specify new drawing operations, or to sort the entities
     * list before drawing, but be sure to then draw all entities by either
     * looping over the entities list or calling State::draw()
     *
     * \param render The render context to draw to
     *
     * \see handleEvents()
     * \see update()
     * \see Game
     */
    virtual void draw();

    /*!
     * \brief Get the list of entities
     *
     * \return A reference to the list of unique_ptrs to entities
     */
    virtual std::vector<std::unique_ptr<Entity>> const& getEntities() { return entities_; }

    State();
    virtual ~State();
protected:
    std::vector<std::unique_ptr<Entity>> entities_;
private:
    State(State const&);
    State& operator=(State const&);
};

}

#endif
