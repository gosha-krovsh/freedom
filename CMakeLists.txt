cmake_minimum_required(VERSION 3.17)
project(Freedom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME}
        main.cpp

        Resources/resources.qrc

        Model/model.cpp
        Model/model.h
        Model/constants.h

        View/view.cpp
        View/view.h

        Controller/controller.cpp
        Controller/controller.h
        Controller/abstract_controller.h

        GameObject/object.cpp
        GameObject/object.h
        GameObject/dynamic_object.cpp
        GameObject/dynamic_object.h
        GameObject/creature.cpp
        GameObject/creature.h
        GameObject/hero.cpp
        GameObject/hero.h
        GameObject/destroyable.h
        GameObject/destroyable.cpp
        GameObject/coordinates.cpp
        GameObject/coordinates.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
