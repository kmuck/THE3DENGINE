project(Engine LANGUAGES CXX)

add_library(Engine STATIC)

target_sources(Engine
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        src/ECS/ECS.ixx
        src/ECS/Entity.ixx
        src/ECS/Component.ixx
        src/ECS/Archetype.ixx
        src/ECS/Registry.ixx

        src/Math/Math.ixx
        src/Math/Matrix.ixx
        src/Math/Quaternion.ixx
        src/Math/Vector.ixx

        src/Event/Event.ixx
        src/Event/Types.ixx
        src/Event/Bus.ixx

        src/Log/Log.ixx

        src/Platform/Platform.ixx

    PRIVATE
        $<$<PLATFORM_ID:Windows>:src/Platform/Windows/Platform.cpp>
)
