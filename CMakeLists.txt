cmake_minimum_required(VERSION 3.17)
project(Freedom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(./)

add_executable(${PROJECT_NAME}
        main.cpp

        Resources/resources.qrc

        Model/model.cpp

        View/view.cpp

        Controller/controller.cpp
        Controller/action_controller.cpp
        Controller/data_controller.cpp

        GameObject/point.cpp
        GameObject/object.cpp
        GameObject/dynamic_object.cpp
        GameObject/destroyable.cpp
        GameObject/creature.cpp
        GameObject/hero.cpp
        GameObject/wall.cpp
        GameObject/game_time.cpp
        GameObject/schedule.cpp
        GameObject/action.cpp
        GameObject/game_map.cpp
        )

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
