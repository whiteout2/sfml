#ifndef HIGH_RES_TIMER_HPP
#define HIGH_RES_TIMER_HPP

#include <chrono>

class HighResTimer {
public:
    using Clock     = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Duration  = std::chrono::duration<double>;

    HighResTimer() 
        : m_running(false), m_paused(false), m_elapsed(0.0) {}

    // Start or restart the timer
    void start() {
        m_running = true;
        m_paused  = false;
        m_elapsed = 0.0;
        m_start   = Clock::now();
    }

    // Pause the timer (keeps elapsed time so far)
    void pause() {
        if (m_running && !m_paused) {
            m_end = Clock::now();
            m_elapsed += std::chrono::duration_cast<Duration>(m_end - m_start).count();
            m_paused = true;
        }
    }

    // Resume from paused state
    void resume() {
        if (m_running && m_paused) {
            m_start = Clock::now();
            m_paused = false;
        }
    }

    // Stop the timer completely
    void stop() {
        if (m_running) {
            if (!m_paused)
                m_end = Clock::now();
            if (!m_paused)
                m_elapsed += std::chrono::duration_cast<Duration>(m_end - m_start).count();
            m_running = false;
            m_paused  = false;
        }
    }

    // Elapsed time in seconds
    double elapsedSeconds() const {
        if (m_running && !m_paused) {
            TimePoint now = Clock::now();
            return m_elapsed + std::chrono::duration_cast<Duration>(now - m_start).count();
        }
        return m_elapsed;
    }

    // Elapsed time in milliseconds
    double elapsedMilliseconds() const {
        return elapsedSeconds() * 1000.0;
    }

private:
    TimePoint m_start{};
    TimePoint m_end{};
    bool      m_running;
    bool      m_paused;
    double    m_elapsed;  // Accumulated elapsed time in seconds
};

#endif // HIGH_RES_TIMER_HPP
