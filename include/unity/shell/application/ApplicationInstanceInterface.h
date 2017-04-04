/*
 * Copyright 2017 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNITY_SHELL_APPLICATION_APPLICATIONINSTANCEINTERFACE_H
#define UNITY_SHELL_APPLICATION_APPLICATIONINSTANCEINTERFACE_H

#include <QObject>

namespace unity {
namespace shell {
namespace application {

class ApplicationInfoInterface;
class MirSurfaceListInterface;

/**
 * @brief An application instance.
 *
 * Represents an instance of an application. An application might have multiple instances
 * running simultaneously.
 */
class ApplicationInstanceInterface : public QObject
{
    Q_OBJECT

    /**
     * @brief The instance's state.
     *
     * Holds the current state of this application instance
     */
    Q_PROPERTY(State state READ state NOTIFY stateChanged)

    /**
     * @brief The requested running state of this application instance
     */
    Q_PROPERTY(RequestedState requestedState READ requestedState WRITE setRequestedState NOTIFY requestedStateChanged)

    /**
     * @brief List of the top-level surfaces created by this application instance
     */
    Q_PROPERTY(unity::shell::application::MirSurfaceListInterface* surfaceList READ surfaceList CONSTANT)

    /**
     * @brief The list of top-level prompt surfaces for this application instance
     */
    Q_PROPERTY(unity::shell::application::MirSurfaceListInterface* promptSurfaceList READ promptSurfaceList CONSTANT)

    /**
     * @brief Information about this application
     */
    Q_PROPERTY(unity::shell::application::ApplicationInfoInterface* application READ application CONSTANT)

    /**
     * @brief The application instance's focus state.
     *
     * Holds the current application instance focus state. True if focused, false otherwise.
     */
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)

public:
    /**
     * @brief State of an application instance.
     *
     * Starting: The instance  was launched and is currently starting up.
     * Running: The instance is running and ready to be used.
     * Suspended: The instance is in the background and has been suspended by
     * the system in order to save resources.
     * Stopped: The instance is in the background and has been stopped by
     * the system in order to save resources. From a programmers point of view,
     * the instance is closed, but it's state has been stored to disk and
     * can be restored upon next launch.
     */
    enum State {
        Starting,
        Running,
        Suspended,
        Stopped
    };
    Q_ENUM(State)

    /**
     * @brief The desired state of an application instance
     *
     * RequestedRunning: If state is Suspended or Stopped, the application instance will be resumed
     *                   or restarted, respectively.
     * RequestedSuspended: If state is Running, the application instance will be suspended.
     */
    enum RequestedState {
        RequestedRunning = Running,
        RequestedSuspended = Suspended
    };
    Q_ENUMS(RequestedState)

    /**
     * @brief Closes this application instance
     */
    virtual void close() = 0;

    /// @cond
    ApplicationInstanceInterface(QObject* parent = 0): QObject(parent) {}
    /// @endcond

    /// @cond
    virtual State state() const = 0;
    virtual RequestedState requestedState() const = 0;
    virtual void setRequestedState(RequestedState) = 0;
    virtual MirSurfaceListInterface* surfaceList() const = 0;
    virtual MirSurfaceListInterface* promptSurfaceList() const = 0;
    virtual ApplicationInfoInterface* application() const = 0;
    virtual bool focused() const = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void stateChanged(State state);
    void requestedStateChanged(RequestedState value);
    void focusedChanged(bool focused);
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_APPLICATIONINSTANCEINTERFACE_H
