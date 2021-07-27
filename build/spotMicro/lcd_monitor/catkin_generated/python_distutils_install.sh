#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/lbn/ws/ws_python_learn/src/spotMicro/lcd_monitor"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/lbn/ws/ws_python_learn/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/lbn/ws/ws_python_learn/install/lib/python3/dist-packages:/home/lbn/ws/ws_python_learn/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/lbn/ws/ws_python_learn/build" \
    "/usr/bin/python3" \
    "/home/lbn/ws/ws_python_learn/src/spotMicro/lcd_monitor/setup.py" \
    egg_info --egg-base /home/lbn/ws/ws_python_learn/build/spotMicro/lcd_monitor \
    build --build-base "/home/lbn/ws/ws_python_learn/build/spotMicro/lcd_monitor" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/lbn/ws/ws_python_learn/install" --install-scripts="/home/lbn/ws/ws_python_learn/install/bin"
