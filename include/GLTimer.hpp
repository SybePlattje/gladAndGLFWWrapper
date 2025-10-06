#ifndef GLTIMER_HPP
# define GLTIMER_HPP

# include "externalLib/glad/include/glad/glad.h"

class GLTimer
{
    public:
        GLTimer();
        void update();
        float getDeltaTime() const;
    private:
        double m_lastTime;
        double m_deltaTime;
};

#endif