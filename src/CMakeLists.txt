add_library(client OBJECT client.cpp)
target_include_directories(client PRIVATE ../include PUBLIC ../asio/asio/include)

add_library(connection OBJECT connection.cpp)
target_include_directories(connection PRIVATE ../include PUBLIC ../asio/asio/include)

add_library(server OBJECT server.cpp)
target_include_directories(server PRIVATE ../include PUBLIC ../asio/asio/include)

add_library(window OBJECT window.cpp clientwindow.cpp serverwindow.cpp)
target_include_directories(window PRIVATE ../include PUBLIC ../FTXUI/include PUBLIC ../asio/asio/include)
