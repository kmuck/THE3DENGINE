project(Engine LANGUAGES CXX)

add_library(Engine STATIC)

target_sources(Engine
    PUBLIC
    FILE_SET modules TYPE CXX_MODULES FILES

        src/Runtime/Runtime.ixx
        src/Runtime/Loop.cppm
        src/Runtime/Config.cppm
        src/Runtime/Context.cppm
        src/Runtime/Scheduler.cppm

        src/ECS/ECS.ixx
        src/ECS/Entity.cppm
        src/ECS/Component.cppm
        src/ECS/System.cppm
        src/ECS/Registry.cppm
#
        src/Graphics/Graphics.ixx
#
#        src/Physics/Physics.ixx
#
#        src/Math/Math.ixx
#        src/Math/Vector/Vector.cppm
#        src/Math/Vector/Vector3.cppm
#
        src/Platform/Platform.ixx

    PRIVATE
        $<$<PLATFORM_ID:Windows>:src/Platform/Windows/Platform.cpp>
)
