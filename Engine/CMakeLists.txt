add_library(Engine)

target_sources(Engine
    PUBLIC
        FILE_SET CXX_MODULES FILES
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
        src/Platform/Types.ixx
        src/Platform/Event.ixx
        src/Platform/Host.ixx
        src/Platform/Input.ixx
        src/Platform/Render.ixx

        src/RHI/RHI.ixx
        src/RHI/Device.ixx
        src/RHI/Swapchain.ixx

        src/Graphics/Graphics.ixx
        src/Graphics/Renderer.ixx

        src/Resource/Resource.ixx
        src/Resource/Type.ixx
)

if(WIN32)
    target_sources(Engine
        PUBLIC
            FILE_SET CXX_MODULES FILES
            src/RHI/D3D12/D3D12RHI.ixx
            src/RHI/D3D12/D3D12Device.ixx
            src/RHI/D3D12/D3D12Swapchain.ixx

        PRIVATE
            src/Platform/Win32/Host.cpp
            src/Platform/Win32/Event.cpp
            src/Platform/Win32/Render.cpp
    )
elseif(UNIX AND NOT APPLE)

elseif(APPLE)

endif()