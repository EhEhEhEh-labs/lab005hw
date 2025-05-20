# Список исходников библиотеки
set(BANKING_SOURCES
    Account.cpp
    Transaction.cpp
)

# Создание статической библиотеки
add_library(banking STATIC ${BANKING_SOURCES})

# Добавляем директорию с заголовками как публичную
target_include_directories(banking PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
