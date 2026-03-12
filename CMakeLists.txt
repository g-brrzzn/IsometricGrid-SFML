cmake_minimum_required(VERSION 3.16)
project(IsometricGrid-SFML VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

# Detect where the sources are: either in CMAKE_CURRENT_SOURCE_DIR or in ./IsometricGrid-SFML
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/IsometricGrid-SFML/main.cpp")
    set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/IsometricGrid-SFML")
else()
    message(FATAL_ERROR
        "Cannot find main.cpp. Expected main.cpp either in:\n"
        "  ${CMAKE_CURRENT_SOURCE_DIR}\n"
        "or\n"
        "  ${CMAKE_CURRENT_SOURCE_DIR}/IsometricGrid-SFML\n"
        "Make sure you run cmake from the project root or move this CMakeLists.txt accordingly.")
endif()

# Collect sources (explicit .cpp files expected in the project)
file(GLOB SRC_FILES
    "${SRC_DIR}/*.cpp"
)

if(NOT SRC_FILES)
    message(FATAL_ERROR "No .cpp sources found in ${SRC_DIR}")
endif()

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})

# Try SFML 3 first (capitalized component names), then fallback to SFML 2
set(SFML_LINK_LIBS "")

# Try SFML 3
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(SFML_FOUND)
    set(SFML_LINK_LIBS SFML::Graphics SFML::Window SFML::System)
endif()

# Fallback to SFML 2
if(NOT SFML_LINK_LIBS)
    find_package(SFML 2 COMPONENTS graphics window system QUIET)
    if(SFML_FOUND)
        if(TARGET SFML::Graphics)
            set(SFML_LINK_LIBS SFML::Graphics SFML::Window SFML::System)
        elseif(DEFINED SFML_LIBRARIES AND SFML_LIBRARIES)
            set(SFML_LINK_LIBS ${SFML_LIBRARIES})
        else()
            set(SFML_LINK_LIBS sfml-graphics sfml-window sfml-system)
        endif()
    endif()
endif()

if(NOT SFML_LINK_LIBS)
    message(FATAL_ERROR
        "Could not find SFML (tried SFML 3 and SFML 2).\n"
        "If SFML is installed, set -DSFML_DIR to the folder containing SFMLConfig.cmake\n"
        "Example: -DSFML_DIR=\"C:/libs/SFML-3.0.0/lib/cmake/SFML\" or add SFML's root to CMAKE_PREFIX_PATH.")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LINK_LIBS})



if(DEFINED SFML_DIR)
    # SFML_DIR costuma ser ".../lib/cmake/SFML" -> queremos a raiz (3 níveis acima)
    get_filename_component(_sfml_dir_parent "${SFML_DIR}" DIRECTORY)        # .../lib/cmake
    get_filename_component(_sfml_dir_grand  "${_sfml_dir_parent}" DIRECTORY) # .../lib
    get_filename_component(SFML_ROOT             "${_sfml_dir_grand}" DIRECTORY) # .../SFML-xxx

    # possível local do bin: ${SFML_ROOT}/bin ou ${SFML_ROOT}/bin64
    set(_candidate_bins "${SFML_ROOT}/bin" "${SFML_ROOT}/bin64" "${SFML_ROOT}/bin/win64")

    foreach(_b ${_candidate_bins})
        if(EXISTS "${_b}")
            set(SFML_BIN_DIR "${_b}")
            break()
        endif()
    endforeach()

    if(DEFINED SFML_BIN_DIR)
        file(GLOB SFML_DLLS "${SFML_BIN_DIR}/*.dll")
        foreach(_dll ${SFML_DLLS})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${_dll}"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            )
        endforeach()
        message(STATUS "Will copy SFML DLLs from: ${SFML_BIN_DIR}")
    else()
        message(WARNING "SFML_BIN_DIR not found. DLLs won't be copied automatically. If you used -DSFML_DIR, ensure it points to an SDK with a /bin folder.")
    endif()
endif()


# Put executable in build/bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy PNG assets to runtime directory
file(GLOB ASSETS "${SRC_DIR}/*.png")

foreach(asset ${ASSETS})
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${asset}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endforeach()

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Sources dir: ${SRC_DIR}")
message(STATUS "Found SFML libs: ${SFML_LINK_LIBS}")