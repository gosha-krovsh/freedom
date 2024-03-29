cmake_minimum_required(VERSION 3.17)
project(Freedom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Multimedia MultimediaWidgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia
        Qt5::MultimediaWidgets)

include_directories(./)

add_executable(${PROJECT_NAME}
        main.cpp

        Resources/resources.qrc

        Model/model.cpp
        Model/image_manager.cpp
        Model/settings.cpp

        View/bar_pack.cpp
        View/item_bar.cpp
        View/game_widget.cpp
        View/view.cpp
        View/conversation_window.cpp
        View/main_menu.cpp
        View/settings_menu.cpp
        View/status_bar.cpp
        View/quest_task_list.cpp

        Controller/action_controller.cpp
        Controller/controller.cpp
        Controller/data_controller.cpp
        Controller/quest_controller.cpp
        Controller/item_controller.cpp

        GameObject/action.cpp
        GameObject/bot.cpp
        GameObject/police.cpp
        GameObject/creature.cpp
        GameObject/destroyable.cpp
        GameObject/dynamic_object.cpp
        GameObject/game_map.cpp
        GameObject/game_time.cpp
        GameObject/hero.cpp
        GameObject/item.cpp
        GameObject/storage.cpp
        GameObject/chest.cpp
        GameObject/object.cpp
        GameObject/point.cpp
        GameObject/schedule.cpp
        GameObject/sound.cpp
        GameObject/shaking_object.cpp
        GameObject/wall.cpp
        GameObject/door.cpp

        Quests/quest.cpp
        Quests/quest_node.cpp

        Conversations/conversation.cpp)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
