#ifndef IWINDOW_H
#define IWINDOW_H

#include <string>
#include "../Utility/Vector.hpp"
namespace sf
{
    class Event;
    class RenderWindow;
}

namespace tank {

/*!
 * \brief Base virtual class (interface) for windows
 */
class IWindow
{
public:
    IWindow() = default;
    virtual ~IWindow() = default;

    virtual Vector<unsigned int> const& getSize() = 0;
    virtual std::string getCaption() = 0;

    virtual void flipDisplay() = 0;

    virtual sf::RenderWindow& SFMLWindow() = 0;

    /*!
     * \brief SFML-specific polling code (temporary)
     */
    virtual bool pollEvent(sf::Event&) = 0;

    virtual void setBackgroundColor(float r, float g, float b, float a = 1.f) = 0;
    virtual void resize(Vector<unsigned int> const& size) = 0;
    virtual void setCaption(std::string caption) = 0;
    virtual void setIcon(std::string path) = 0;
private:
    IWindow(IWindow const&);
    IWindow& operator=(IWindow const&);
};

}

#endif /* IWINDOW_H */
