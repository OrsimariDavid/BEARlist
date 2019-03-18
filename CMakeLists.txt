cmake_minimum_required ( VERSION 3.13 )
project ( BEARlist )

set ( CMAKE_CXX_STANDARD 14 )

add_executable ( BEARlist main.cpp Observer.h Subject.h Task.cpp Task.h Principal_View.cpp Principal_View.h Model.cpp Model.h Controller.cpp Controller.h Intro_img.cpp Intro_img.h List_View.cpp List_View.h Detail_View.cpp Detail_View.h )

find_package(wxWidgets REQUIRED net gl core base xrc adv)
include(${wxWidgets_USE_FILE})

# for each of your dependent executable/library targets:
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})